test_that("Reindexing", {
    skip_if(!extended_tests())

    expect_error(Reindexer$new())
    expect_error(Reindexer$new(c(1,3,5), 4))

    init_map <- bit64::as.integer64(c(32, 10 ,12, 5))
    expect_silent(reind <- Reindexer$new(init_map))

    init_keys <- bit64::as.integer64(c(5, 12, 10, 32, 10 ,12, 5, 5, 5))
    exp_res <- bit64::as.integer64(c(3, 2, 1, 0, 1, 2, 3, 3, 3))

    expect_error(reind$lookup(init_keys[c(1:2)]))  			# shorter than thread count --> error
    expect_error(reind$lookup(1:10))

    expect_silent(res <- reind$lookup(init_keys))
    expect_true(bit64::is.integer64(res))
    expect_equal(length(init_keys), length(res))
    expect_equal(res, exp_res)
})
