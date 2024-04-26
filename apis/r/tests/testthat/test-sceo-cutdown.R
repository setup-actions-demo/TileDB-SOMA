# ================================================================
# REPRO INSTRUCTIONS
#
# MacOS 14.4.*
#
# Run this:
#
#   devtools::load_all()
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#   testthat::test_file("tests/testthat/test-sceo-cutdown.R")
#
# Look for this:
#   <tiledb::TileDBError/C++Error/error/condition>
#   Error in `eval(ei, envir)`: [TileDB::C++API] Error: Failed to create context
#
# ================================================================

test_that("Load SCE object from ExperimentQuery mechanics", {

  skip_if(!extended_tests() || covr_tests())
  skip_if_not_installed('SingleCellExperiment', .MINIMUM_SCE_VERSION('c'))

  cat("\n---- TSCEO ENTER\n")

  uri <- withr::local_tempdir("sce-experiment-query-whole")
  n_obs <- 20L
  n_var <- 10L
  n_pcs <- 50L
  n_ics <- 30L
  n_umaps <- 2L

  cat("\n----   TSCEO CREATE\n")
  experiment <- create_and_populate_experiment(
    uri = uri,
    n_obs = n_obs,
    n_var = n_var,
    X_layer_names = c('counts', 'logcounts'),
    obsm_layers = c(X_pca = n_pcs, 'dense:X_ica' = n_ics, X_umap = n_umaps),
    # No varm in SingleCellExperiment
    obsp_layer_names = 'connectivities',
    varp_layer_names = 'network',
    mode = 'READ'
  )
  #on.exit(experiment$close())

  cat("\n----   TSCEO CLOSE1\n")
  experiment$close()
  cat("\n----   TSCEO OPEN\n")
  experiment <- SOMAExperimentOpen(uri)
  ##on.exit(experiment$close())

  # Create the query
  cat("\n----   TSCEO QUERY\n")
  query <- SOMAExperimentAxisQuery$new(experiment = experiment, measurement_name = "RNA")

  cat("\n----   TSCEO TOSCE1\n")
  expect_warning(obj <- query$to_single_cell_experiment())
  cat("\n----   TSCEO TOSCE2\n")
  expect_warning(obj <- query$to_single_cell_experiment())

  cat("\n---- TSCEO CLOSE2\n")
  experiment$close()
  cat("\n---- TSCEO EXIT\n")

})
