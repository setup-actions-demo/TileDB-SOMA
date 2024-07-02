
suppressMessages(library(bit64))

sapply(dir("../../tests/testthat", "^help.*R$", full.names=TRUE), source)

is_arrow_table <- tiledbsoma:::is_arrow_table
nnz <- tiledbsoma:::nnz
shape <- tiledbsoma:::shape
arrow_field_from_tiledb_dim <- tiledbsoma:::arrow_field_from_tiledb_dim
example_data_dir <- tiledbsoma:::example_data_dir
.MINIMUM_SCE_VERSION <- tiledbsoma:::.MINIMUM_SCE_VERSION
.MINIMUM_SEURAT_VERSION <- tiledbsoma:::.MINIMUM_SEURAT_VERSION
is_scalar_character <- rlang:::is_scalar_character
soma_array_reader <- tiledbsoma:::soma_array_reader
soma_array_to_arrow_table <- tiledbsoma:::soma_array_to_arrow_table
is_arrow_record_batch <- tiledbsoma:::is_arrow_record_batch
sr_setup <- tiledbsoma:::sr_setup
sr_next <- tiledbsoma:::sr_next
sr_complete <- tiledbsoma:::sr_complete
#sr_finalize <- tiledbsoma:::sr_finalize
## .default_dataframe_dim_zstd_level <- tiledbsoma:::.default_dataframe_dim_zstd_level
## .default_sparse_nd_array_dim_zstd_level <- tiledbsoma:::.default_sparse_nd_array_dim_zstd_level
## .default_write_x_chunked <- tiledbsoma:::.default_write_x_chunked
## .default_goal_chunk_nnz <- tiledbsoma:::.default_goal_chunk_nnz
## .default_cell_order <- tiledbsoma:::.default_cell_order
## .default_tile_extent <- tiledbsoma:::.default_tile_extent
## .default_offsets_filters <- tiledbsoma:::.default_offsets_filters
## .default_tile_order <- tiledbsoma:::.default_tile_order
## .default_validity_filters <- tiledbsoma:::.default_validity_filters
validate_read_coords <- tiledbsoma:::validate_read_coords
file_path <- tiledbsoma:::file_path
uri_scheme <- tiledbsoma:::uri_scheme
uri_scheme_remove <- tiledbsoma:::uri_scheme_remove
make_uri_relative <- tiledbsoma:::make_uri_relative
#extended_tests <- function() {
#    ## check if at CI, if so extended test
#    ## could add if pre-release number ie 1.4.3.1 instead of 1.4.3
#    Sys.getenv("CI", "") != ""
#}
is_arrow_field <- tiledbsoma:::is_arrow_field
check_arrow_schema_data_types <- tiledbsoma:::check_arrow_schema_data_types
check_arrow_data_types <- tiledbsoma:::check_arrow_data_types
tiledb_type_from_arrow_type <- tiledbsoma:::tiledb_type_from_arrow_type
arrow_field_from_tiledb_attr <- tiledbsoma:::arrow_field_from_tiledb_attr
arrow_schema_from_tiledb_schema <- tiledbsoma:::arrow_schema_from_tiledb_schema
is_arrow_schema <- tiledbsoma:::is_arrow_schema
TileDBURI <- tiledbsoma:::TileDBURI
uns_hint <- tiledbsoma:::uns_hint
unlist64 <- tiledbsoma:::unlist64

## missing testthat helpers
skip_if <- function(f) if (f) exit_file()
skip_if_not_installed <- function(f) if (!requireNamespace(f, quietly=TRUE)) exit_file()

expect_output <- function(...) expect_stdout(...)
expect_no_condition <- function(...) expect_silent(...)
expect_mapequal <- function(...) expect_equal(...)
