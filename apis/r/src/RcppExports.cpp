// Generated by using Rcpp::compileAttributes() -> do not edit by hand
// Generator token: 10BE3573-1514-4C36-9D1C-5A225CD40393

#include "../inst/include/tiledbsoma_types.h"
#include <Rcpp.h>

using namespace Rcpp;

#ifdef RCPP_USE_GLOBAL_ROSTREAM
Rcpp::Rostream<true>&  Rcpp::Rcout = Rcpp::Rcpp_cout_get();
Rcpp::Rostream<false>& Rcpp::Rcerr = Rcpp::Rcpp_cerr_get();
#endif

// createSchemaFromArrow
void createSchemaFromArrow(const std::string& uri, naxpSchema nasp, naxpArray nadimap, naxpSchema nadimsp, bool sparse, std::string datatype, Rcpp::List pclst, Rcpp::Nullable<Rcpp::XPtr<ctx_wrap_t>> ctxptr);
RcppExport SEXP _tiledbsoma_createSchemaFromArrow(SEXP uriSEXP, SEXP naspSEXP, SEXP nadimapSEXP, SEXP nadimspSEXP, SEXP sparseSEXP, SEXP datatypeSEXP, SEXP pclstSEXP, SEXP ctxptrSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type uri(uriSEXP);
    Rcpp::traits::input_parameter< naxpSchema >::type nasp(naspSEXP);
    Rcpp::traits::input_parameter< naxpArray >::type nadimap(nadimapSEXP);
    Rcpp::traits::input_parameter< naxpSchema >::type nadimsp(nadimspSEXP);
    Rcpp::traits::input_parameter< bool >::type sparse(sparseSEXP);
    Rcpp::traits::input_parameter< std::string >::type datatype(datatypeSEXP);
    Rcpp::traits::input_parameter< Rcpp::List >::type pclst(pclstSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::XPtr<ctx_wrap_t>> >::type ctxptr(ctxptrSEXP);
    createSchemaFromArrow(uri, nasp, nadimap, nadimsp, sparse, datatype, pclst, ctxptr);
    return R_NilValue;
END_RCPP
}
// writeArrayFromArrow
void writeArrayFromArrow(const std::string& uri, naxpArray naap, naxpSchema nasp, const std::string arraytype, Rcpp::Nullable<Rcpp::CharacterVector> config);
RcppExport SEXP _tiledbsoma_writeArrayFromArrow(SEXP uriSEXP, SEXP naapSEXP, SEXP naspSEXP, SEXP arraytypeSEXP, SEXP configSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type uri(uriSEXP);
    Rcpp::traits::input_parameter< naxpArray >::type naap(naapSEXP);
    Rcpp::traits::input_parameter< naxpSchema >::type nasp(naspSEXP);
    Rcpp::traits::input_parameter< const std::string >::type arraytype(arraytypeSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::CharacterVector> >::type config(configSEXP);
    writeArrayFromArrow(uri, naap, nasp, arraytype, config);
    return R_NilValue;
END_RCPP
}
// reindex_create
Rcpp::XPtr<tdbs::IntIndexer> reindex_create();
RcppExport SEXP _tiledbsoma_reindex_create() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(reindex_create());
    return rcpp_result_gen;
END_RCPP
}
// reindex_map
Rcpp::XPtr<tdbs::IntIndexer> reindex_map(Rcpp::XPtr<tdbs::IntIndexer> idx, const Rcpp::NumericVector nvec);
RcppExport SEXP _tiledbsoma_reindex_map(SEXP idxSEXP, SEXP nvecSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<tdbs::IntIndexer> >::type idx(idxSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector >::type nvec(nvecSEXP);
    rcpp_result_gen = Rcpp::wrap(reindex_map(idx, nvec));
    return rcpp_result_gen;
END_RCPP
}
// reindex_lookup
Rcpp::NumericVector reindex_lookup(Rcpp::XPtr<tdbs::IntIndexer> idx, const Rcpp::NumericVector kvec);
RcppExport SEXP _tiledbsoma_reindex_lookup(SEXP idxSEXP, SEXP kvecSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<tdbs::IntIndexer> >::type idx(idxSEXP);
    Rcpp::traits::input_parameter< const Rcpp::NumericVector >::type kvec(kvecSEXP);
    rcpp_result_gen = Rcpp::wrap(reindex_lookup(idx, kvec));
    return rcpp_result_gen;
END_RCPP
}
// soma_array_reader
SEXP soma_array_reader(const std::string& uri, Rcpp::Nullable<Rcpp::CharacterVector> colnames, Rcpp::Nullable<Rcpp::XPtr<tiledb::QueryCondition>> qc, Rcpp::Nullable<Rcpp::List> dim_points, Rcpp::Nullable<Rcpp::List> dim_ranges, std::string batch_size, std::string result_order, const std::string& loglevel, Rcpp::Nullable<Rcpp::CharacterVector> config);
RcppExport SEXP _tiledbsoma_soma_array_reader(SEXP uriSEXP, SEXP colnamesSEXP, SEXP qcSEXP, SEXP dim_pointsSEXP, SEXP dim_rangesSEXP, SEXP batch_sizeSEXP, SEXP result_orderSEXP, SEXP loglevelSEXP, SEXP configSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type uri(uriSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::CharacterVector> >::type colnames(colnamesSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::XPtr<tiledb::QueryCondition>> >::type qc(qcSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::List> >::type dim_points(dim_pointsSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::List> >::type dim_ranges(dim_rangesSEXP);
    Rcpp::traits::input_parameter< std::string >::type batch_size(batch_sizeSEXP);
    Rcpp::traits::input_parameter< std::string >::type result_order(result_orderSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type loglevel(loglevelSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::CharacterVector> >::type config(configSEXP);
    rcpp_result_gen = Rcpp::wrap(soma_array_reader(uri, colnames, qc, dim_points, dim_ranges, batch_size, result_order, loglevel, config));
    return rcpp_result_gen;
END_RCPP
}
// set_log_level
void set_log_level(const std::string& level);
RcppExport SEXP _tiledbsoma_set_log_level(SEXP levelSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type level(levelSEXP);
    set_log_level(level);
    return R_NilValue;
END_RCPP
}
// get_column_types
Rcpp::CharacterVector get_column_types(const std::string& uri, const std::vector<std::string>& colnames);
RcppExport SEXP _tiledbsoma_get_column_types(SEXP uriSEXP, SEXP colnamesSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type uri(uriSEXP);
    Rcpp::traits::input_parameter< const std::vector<std::string>& >::type colnames(colnamesSEXP);
    rcpp_result_gen = Rcpp::wrap(get_column_types(uri, colnames));
    return rcpp_result_gen;
END_RCPP
}
// nnz
double nnz(const std::string& uri, Rcpp::Nullable<Rcpp::CharacterVector> config);
RcppExport SEXP _tiledbsoma_nnz(SEXP uriSEXP, SEXP configSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type uri(uriSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::CharacterVector> >::type config(configSEXP);
    rcpp_result_gen = Rcpp::wrap(nnz(uri, config));
    return rcpp_result_gen;
END_RCPP
}
// check_arrow_schema_tag
bool check_arrow_schema_tag(Rcpp::XPtr<ArrowSchema> xp);
RcppExport SEXP _tiledbsoma_check_arrow_schema_tag(SEXP xpSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<ArrowSchema> >::type xp(xpSEXP);
    rcpp_result_gen = Rcpp::wrap(check_arrow_schema_tag(xp));
    return rcpp_result_gen;
END_RCPP
}
// check_arrow_array_tag
bool check_arrow_array_tag(Rcpp::XPtr<ArrowArray> xp);
RcppExport SEXP _tiledbsoma_check_arrow_array_tag(SEXP xpSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<ArrowArray> >::type xp(xpSEXP);
    rcpp_result_gen = Rcpp::wrap(check_arrow_array_tag(xp));
    return rcpp_result_gen;
END_RCPP
}
// shape
Rcpp::NumericVector shape(const std::string& uri, Rcpp::Nullable<Rcpp::CharacterVector> config);
RcppExport SEXP _tiledbsoma_shape(SEXP uriSEXP, SEXP configSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type uri(uriSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::CharacterVector> >::type config(configSEXP);
    rcpp_result_gen = Rcpp::wrap(shape(uri, config));
    return rcpp_result_gen;
END_RCPP
}
// sr_setup
Rcpp::List sr_setup(const std::string& uri, Rcpp::CharacterVector config, Rcpp::Nullable<Rcpp::CharacterVector> colnames, Rcpp::Nullable<Rcpp::XPtr<tiledb::QueryCondition>> qc, Rcpp::Nullable<Rcpp::List> dim_points, Rcpp::Nullable<Rcpp::List> dim_ranges, std::string batch_size, std::string result_order, Rcpp::Nullable<Rcpp::Datetime> timestamp_end, const std::string& loglevel);
RcppExport SEXP _tiledbsoma_sr_setup(SEXP uriSEXP, SEXP configSEXP, SEXP colnamesSEXP, SEXP qcSEXP, SEXP dim_pointsSEXP, SEXP dim_rangesSEXP, SEXP batch_sizeSEXP, SEXP result_orderSEXP, SEXP timestamp_endSEXP, SEXP loglevelSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type uri(uriSEXP);
    Rcpp::traits::input_parameter< Rcpp::CharacterVector >::type config(configSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::CharacterVector> >::type colnames(colnamesSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::XPtr<tiledb::QueryCondition>> >::type qc(qcSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::List> >::type dim_points(dim_pointsSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::List> >::type dim_ranges(dim_rangesSEXP);
    Rcpp::traits::input_parameter< std::string >::type batch_size(batch_sizeSEXP);
    Rcpp::traits::input_parameter< std::string >::type result_order(result_orderSEXP);
    Rcpp::traits::input_parameter< Rcpp::Nullable<Rcpp::Datetime> >::type timestamp_end(timestamp_endSEXP);
    Rcpp::traits::input_parameter< const std::string& >::type loglevel(loglevelSEXP);
    rcpp_result_gen = Rcpp::wrap(sr_setup(uri, config, colnames, qc, dim_points, dim_ranges, batch_size, result_order, timestamp_end, loglevel));
    return rcpp_result_gen;
END_RCPP
}
// sr_complete
bool sr_complete(Rcpp::XPtr<tdbs::SOMAArray> sr);
RcppExport SEXP _tiledbsoma_sr_complete(SEXP srSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<tdbs::SOMAArray> >::type sr(srSEXP);
    rcpp_result_gen = Rcpp::wrap(sr_complete(sr));
    return rcpp_result_gen;
END_RCPP
}
// create_empty_arrow_table
SEXP create_empty_arrow_table();
RcppExport SEXP _tiledbsoma_create_empty_arrow_table() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(create_empty_arrow_table());
    return rcpp_result_gen;
END_RCPP
}
// sr_next
SEXP sr_next(Rcpp::XPtr<tdbs::SOMAArray> sr);
RcppExport SEXP _tiledbsoma_sr_next(SEXP srSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<tdbs::SOMAArray> >::type sr(srSEXP);
    rcpp_result_gen = Rcpp::wrap(sr_next(sr));
    return rcpp_result_gen;
END_RCPP
}
// sr_reset
void sr_reset(Rcpp::XPtr<tdbs::SOMAArray> sr);
RcppExport SEXP _tiledbsoma_sr_reset(SEXP srSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<tdbs::SOMAArray> >::type sr(srSEXP);
    sr_reset(sr);
    return R_NilValue;
END_RCPP
}
// sr_set_dim_points
void sr_set_dim_points(Rcpp::XPtr<tdbs::SOMAArray> sr, std::string dim, Rcpp::NumericVector points);
RcppExport SEXP _tiledbsoma_sr_set_dim_points(SEXP srSEXP, SEXP dimSEXP, SEXP pointsSEXP) {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< Rcpp::XPtr<tdbs::SOMAArray> >::type sr(srSEXP);
    Rcpp::traits::input_parameter< std::string >::type dim(dimSEXP);
    Rcpp::traits::input_parameter< Rcpp::NumericVector >::type points(pointsSEXP);
    sr_set_dim_points(sr, dim, points);
    return R_NilValue;
END_RCPP
}
// tiledbsoma_stats_enable
void tiledbsoma_stats_enable();
RcppExport SEXP _tiledbsoma_tiledbsoma_stats_enable() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    tiledbsoma_stats_enable();
    return R_NilValue;
END_RCPP
}
// tiledbsoma_stats_disable
void tiledbsoma_stats_disable();
RcppExport SEXP _tiledbsoma_tiledbsoma_stats_disable() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    tiledbsoma_stats_disable();
    return R_NilValue;
END_RCPP
}
// tiledbsoma_stats_reset
void tiledbsoma_stats_reset();
RcppExport SEXP _tiledbsoma_tiledbsoma_stats_reset() {
BEGIN_RCPP
    Rcpp::RNGScope rcpp_rngScope_gen;
    tiledbsoma_stats_reset();
    return R_NilValue;
END_RCPP
}
// tiledbsoma_stats_dump
std::string tiledbsoma_stats_dump();
RcppExport SEXP _tiledbsoma_tiledbsoma_stats_dump() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(tiledbsoma_stats_dump());
    return rcpp_result_gen;
END_RCPP
}
// libtiledbsoma_version
std::string libtiledbsoma_version(const bool compact);
RcppExport SEXP _tiledbsoma_libtiledbsoma_version(SEXP compactSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const bool >::type compact(compactSEXP);
    rcpp_result_gen = Rcpp::wrap(libtiledbsoma_version(compact));
    return rcpp_result_gen;
END_RCPP
}
// tiledb_embedded_version
Rcpp::IntegerVector tiledb_embedded_version();
RcppExport SEXP _tiledbsoma_tiledb_embedded_version() {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    rcpp_result_gen = Rcpp::wrap(tiledb_embedded_version());
    return rcpp_result_gen;
END_RCPP
}
// tiledb_datatype_max_value
size_t tiledb_datatype_max_value(const std::string& datatype);
RcppExport SEXP _tiledbsoma_tiledb_datatype_max_value(SEXP datatypeSEXP) {
BEGIN_RCPP
    Rcpp::RObject rcpp_result_gen;
    Rcpp::RNGScope rcpp_rngScope_gen;
    Rcpp::traits::input_parameter< const std::string& >::type datatype(datatypeSEXP);
    rcpp_result_gen = Rcpp::wrap(tiledb_datatype_max_value(datatype));
    return rcpp_result_gen;
END_RCPP
}

static const R_CallMethodDef CallEntries[] = {
    {"_tiledbsoma_createSchemaFromArrow", (DL_FUNC) &_tiledbsoma_createSchemaFromArrow, 8},
    {"_tiledbsoma_writeArrayFromArrow", (DL_FUNC) &_tiledbsoma_writeArrayFromArrow, 5},
    {"_tiledbsoma_reindex_create", (DL_FUNC) &_tiledbsoma_reindex_create, 0},
    {"_tiledbsoma_reindex_map", (DL_FUNC) &_tiledbsoma_reindex_map, 2},
    {"_tiledbsoma_reindex_lookup", (DL_FUNC) &_tiledbsoma_reindex_lookup, 2},
    {"_tiledbsoma_soma_array_reader", (DL_FUNC) &_tiledbsoma_soma_array_reader, 9},
    {"_tiledbsoma_set_log_level", (DL_FUNC) &_tiledbsoma_set_log_level, 1},
    {"_tiledbsoma_get_column_types", (DL_FUNC) &_tiledbsoma_get_column_types, 2},
    {"_tiledbsoma_nnz", (DL_FUNC) &_tiledbsoma_nnz, 2},
    {"_tiledbsoma_check_arrow_schema_tag", (DL_FUNC) &_tiledbsoma_check_arrow_schema_tag, 1},
    {"_tiledbsoma_check_arrow_array_tag", (DL_FUNC) &_tiledbsoma_check_arrow_array_tag, 1},
    {"_tiledbsoma_shape", (DL_FUNC) &_tiledbsoma_shape, 2},
    {"_tiledbsoma_sr_setup", (DL_FUNC) &_tiledbsoma_sr_setup, 10},
    {"_tiledbsoma_sr_complete", (DL_FUNC) &_tiledbsoma_sr_complete, 1},
    {"_tiledbsoma_create_empty_arrow_table", (DL_FUNC) &_tiledbsoma_create_empty_arrow_table, 0},
    {"_tiledbsoma_sr_next", (DL_FUNC) &_tiledbsoma_sr_next, 1},
    {"_tiledbsoma_sr_reset", (DL_FUNC) &_tiledbsoma_sr_reset, 1},
    {"_tiledbsoma_sr_set_dim_points", (DL_FUNC) &_tiledbsoma_sr_set_dim_points, 3},
    {"_tiledbsoma_tiledbsoma_stats_enable", (DL_FUNC) &_tiledbsoma_tiledbsoma_stats_enable, 0},
    {"_tiledbsoma_tiledbsoma_stats_disable", (DL_FUNC) &_tiledbsoma_tiledbsoma_stats_disable, 0},
    {"_tiledbsoma_tiledbsoma_stats_reset", (DL_FUNC) &_tiledbsoma_tiledbsoma_stats_reset, 0},
    {"_tiledbsoma_tiledbsoma_stats_dump", (DL_FUNC) &_tiledbsoma_tiledbsoma_stats_dump, 0},
    {"_tiledbsoma_libtiledbsoma_version", (DL_FUNC) &_tiledbsoma_libtiledbsoma_version, 1},
    {"_tiledbsoma_tiledb_embedded_version", (DL_FUNC) &_tiledbsoma_tiledb_embedded_version, 0},
    {"_tiledbsoma_tiledb_datatype_max_value", (DL_FUNC) &_tiledbsoma_tiledb_datatype_max_value, 1},
    {NULL, NULL, 0}
};

RcppExport void R_init_tiledbsoma(DllInfo *dll) {
    R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
    R_useDynamicSymbols(dll, FALSE);
}
