
suppressMessages({
    library(bit64)
    library(tiledbsoma)
})
#set_log_level("debug")
init_map <- as.integer64(c(32, 10 ,12, 5))
#print(init_map)
init_keys <- as.integer64(c(5, 12, 10, 32, 10 ,12, 5, 5, 5))

cat("** Calling reindex_create()\n")
idxptr <- tiledbsoma:::reindex_create()

cat("** Calling reindex_map()\n")
idxptr <- tiledbsoma:::reindex_map(idxptr, init_map, 4)

cat("** Calling reindex_lookup()\n")
cat("** Results from reindex_lookup()\n")
print(tiledbsoma:::reindex_lookup(idxptr, init_keys))
print(tiledbsoma:::reindex_lookup(idxptr, init_keys[1:4]))
print(tiledbsoma:::reindex_lookup(idxptr, rep(init_keys[1:2],2)))
print(tiledbsoma:::reindex_lookup(idxptr, as.integer64(40:50)))
