#' Reindexer Class
#'
#' @keywords internal
#' @export

Reindexer <- R6::R6Class(
    classname = "Reindexer",
    public = list(

        #' @description Initialize a Reindexer object
        #'
        #' @param map_keys An integer64 vector with keys to be mapped by the class
        #' @param nb_threads The number of threads to use, defaults to four
        initialize = function(map_keys, nb_threads = 4) {
            stopifnot("Keys must be 'integer64'" = bit64::is.integer64(map_keys))
            private$idxptr <- reindex_create()
            private$threadcount <- nb_threads
            reindex_map(private$idxptr, map_keys)
        },

        #' @description Lookup a vector of keys
        #'
        #' @param lookup_keys An integer64 vector with values to be looked up
        #' @return A vector of the same length with index positions
        lookup = function(lookup_keys) {
            ## catch vulnerability in indexer
            stopifnot("Keys must outnumber thread count" = length(lookup_keys) > private$threadcount,
                      "Keys must be 'integer64'" = bit64::is.integer64(lookup_keys))
            reindex_lookup(private$idxptr, lookup_keys)
        }
    ),

    private = list(
        ## Internal 'external pointer object holding an Reindexer class instance
        idxptr = NULL,
        ## Internal thread counter
        threadcount = NULL
    )
)
