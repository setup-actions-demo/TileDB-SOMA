## .onLoad is called whether code from the package is used and the packages is 'loaded'. An
## example is calling `tiledbsoma::show_package_versions()`. So this is most elementary check,
## .onAttach is also called when the package is 'attached' via 'library(tiledbsoma)'
## During package build and byte-code compilation and load check, both are called.
.onLoad <- function(libname, pkgname) {
    ## this returns a package_version
    rpkg_lib_version <- tiledb::tiledb_version(compact=TRUE)
    ## this returns a character similar to a formatted package version
    soma_lib_version <- libtiledbsoma_version(compact=TRUE)
    ## extract vector underlying package version, pick first two elements
    rpkg_maj_min <-  unlist(unclass(rpkg_lib_version))[1:2]
    ## split formatted package version at 'dots', turn to integer, pick first two
    soma_maj_min <-  as.integer(strsplit(soma_lib_version, "\\.")[[1]])[1:2]
    print(rpkg_lib_version)
    print(soma_lib_version)
    print(rpkg_maj_min)
    print(soma_maj_min)
    if (!all.equal(rpkg_maj_min, soma_maj_min)) {
        msg <- sprintf("TileDB Core version %s used by TileDB-R package, but TileDB-SOMA uses %s",
                       sQuote(rpkg_lib_version), sQuote(soma_lib_version))
        stop(msg, call. = FALSE)
    }
}

## An .onAttach() function is not allowed to use cat() etc but _must_ communicate via
## packageStartupMessage() as this function can be 'muzzled' as desired. See Writing R Extensions.
.onAttach <- function(libname, pkgname) {
    if (interactive()) {
        packageStartupMessage("TileDB-SOMA R package ", packageVersion(pkgname),
                              " with TileDB Embedded ", format(tiledb::tiledb_version(TRUE)),
                              " on ", utils::osVersion,
                              ".\nSee https://github.com/single-cell-data for more information ",
                              "about the SOMA project.")
    }
}
