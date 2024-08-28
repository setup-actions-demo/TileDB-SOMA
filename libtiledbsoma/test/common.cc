/**
 * @file   common.cc
 *
 * @section LICENSE
 *
 * The MIT License
 *
 * @copyright Copyright (c) 2024 TileDB, Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 *
 * @section DESCRIPTION
 *
 * This file manages common headers and helper classes for the unit test files.
 */

#include "common.h"

namespace helper {

static std::unique_ptr<ArrowArray> _create_index_cols_info_array(
    int64_t dim_max, bool use_current_domain);
static std::unique_ptr<ArrowSchema> _create_index_cols_info_schema(
    std::string dim_name);

// This non-obvious number is:
// * Something that fits into signed 32-bit integer for R-friendliness;
// * Is a comfortable tile-extent distance away from 2^31-1 for default
//   core tile extent. (Using 2^31-1 exactly would result in a core
//   array-creation error.)
const int CORE_DOMAIN_MAX = 2147483646;

// Notes:
//
// * This is multi-purpose code used for generic SOMASparseNDArray,
//   SOMADenseNDArray, and SOMADataFrame
// * The NDArrays always have:
//   o int64 dims soma_dim_0, soma_dim_1, ..., soma_dim_n
//   o a single attr of varying numeric type -- float32, float32, int16, etc.
// * Default-indexed (i.e. what almost everyone uses) SOMADataFrame has
//   o int64 dims soma_joinid
//   o arbitrary number of attrs of arbitrary type -- int, float, bool, string,
//     categorical-of-string, you name it
// * But SOMADataFrame, in the SOMA spec, just needs to have soma_joinid
//   present, as a dim or attr.
//   o soma_joinid can be a dim, along with others
//   o soma_joinid can be an attr only, with something else being the dim
//
// Given this context, create_arrow_schema_and_index_columns is a factory
// for creating schema information for ND arrays and default-indexed
// dataframes.
//
// * This returns a pair of ArrowSchema and ArrowTable
// * ArrowTable, in turn, is a pair of ArrowArray and ArrowSchema
// * So this is
//    o ArrowSchema -- schema for the array
//      - ArrowArray  -- information about the tile extent, domain, and
//        current domain for the index columns
//      - ArrowSchema -- information about the datatypes for the index columns
//    o Confusingly, there's even more nesting: for an n-attr dataframe, there
//      is an ArrowSchema with its n_children being n -- and each of those
//      n entries in its children[] array are also of type ArrowSchema
// * The data structures conform to arrow_adapter
// * The Python and R bindings prepare similar Arrow information when
//   passing a create-array request to libtiledbsoma.

std::pair<std::unique_ptr<ArrowSchema>, ArrowTable>
create_arrow_schema_and_index_columns(
    int64_t dim_max, bool use_current_domain) {
    // Create ArrowSchema for the entire SOMAArray: dims and attrs both
    auto arrow_schema = std::make_unique<ArrowSchema>();
    arrow_schema->format = "+s";
    arrow_schema->n_children = 2;  // non-leaf node
    arrow_schema->dictionary = nullptr;
    arrow_schema->release = &ArrowAdapter::release_schema;
    arrow_schema->children = new ArrowSchema*[arrow_schema->n_children];

    ArrowSchema* dim = arrow_schema->children[0] = new ArrowSchema;
    dim->format = "l";
    dim->name = "d0";
    dim->n_children = 0;  // leaf node
    dim->dictionary = nullptr;
    dim->release = &ArrowAdapter::release_schema;

    ArrowSchema* attr = arrow_schema->children[1] = new ArrowSchema;
    attr->format = "l";
    attr->name = "a0";
    attr->n_children = 0;  // leaf node
    attr->flags = 0;
    attr->dictionary = nullptr;
    attr->release = &ArrowAdapter::release_schema;

    auto index_cols_info_schema = _create_index_cols_info_schema("d0");
    auto index_cols_info_array = _create_index_cols_info_array(
        dim_max, use_current_domain);

    return std::pair(
        std::move(arrow_schema),
        ArrowTable(
            std::move(index_cols_info_array),
            std::move(index_cols_info_schema)));
}

ArrowTable create_column_index_info(int64_t dim_max, bool use_current_domain) {
    auto index_cols_info_schema = _create_index_cols_info_schema("soma_dim_0");
    auto index_cols_info_array = _create_index_cols_info_array(
        dim_max, use_current_domain);

    return ArrowTable(
        std::move(index_cols_info_array), std::move(index_cols_info_schema));
}

static std::unique_ptr<ArrowSchema> _create_index_cols_info_schema(
    std::string dim_name) {
    auto index_cols_info_schema = std::make_unique<ArrowSchema>();
    index_cols_info_schema->format = "+s";
    index_cols_info_schema->n_children = 1;  // non-leaf node
    index_cols_info_schema->dictionary = nullptr;
    index_cols_info_schema->release = &ArrowAdapter::release_schema;
    index_cols_info_schema
        ->children = new ArrowSchema*[index_cols_info_schema->n_children];

    ArrowSchema* dim = index_cols_info_schema->children[0] = new ArrowSchema;
    dim->format = "l";
    dim->name = strdup(dim_name.c_str());
    dim->n_children = 0;  // leaf node
    dim->dictionary = nullptr;
    dim->release = &ArrowAdapter::release_schema;

    return index_cols_info_schema;
}

static std::unique_ptr<ArrowArray> _create_index_cols_info_array(
    int64_t dim_max, bool use_current_domain) {
    auto index_cols_info_array = std::make_unique<ArrowArray>();
    index_cols_info_array->length = 0;
    index_cols_info_array->null_count = 0;
    index_cols_info_array->offset = 0;
    index_cols_info_array->n_buffers = 0;
    index_cols_info_array->buffers = nullptr;
    index_cols_info_array->n_children = 1;
    index_cols_info_array->release = &ArrowAdapter::release_array;
    index_cols_info_array->children = new ArrowArray*[1];

    int n = use_current_domain ? 5 : 3;

    auto d0_info = index_cols_info_array->children[0] = new ArrowArray;
    d0_info->length = n;
    d0_info->null_count = 0;
    d0_info->offset = 0;
    d0_info->n_buffers = 2;
    d0_info->release = &ArrowAdapter::release_array;
    d0_info->buffers = new const void*[2];
    d0_info->buffers[0] = nullptr;
    d0_info->buffers[1] = malloc(sizeof(int64_t) * n);
    d0_info->n_children = 0;

    if (use_current_domain) {
        // domain big; current_domain small
        int64_t dom[] = {0, CORE_DOMAIN_MAX, 1, 0, dim_max};
        std::memcpy((void*)d0_info->buffers[1], &dom, sizeof(int64_t) * n);
    } else {
        // domain small; current_domain feature not being used
        int64_t dom[] = {0, dim_max, 1};
        std::memcpy((void*)d0_info->buffers[1], &dom, sizeof(int64_t) * n);
    }

    return index_cols_info_array;
}

}  // namespace helper
