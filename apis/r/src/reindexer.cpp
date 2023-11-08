#include <Rcpp.h>               // for R interface to C++
#include <RcppInt64>            // for fromInteger64

#include <tiledbsoma/tiledbsoma>
#if TILEDB_VERSION_MAJOR == 2 && TILEDB_VERSION_MINOR >= 4
#include <tiledb/tiledb_experimental>
#endif
#include <tiledbsoma/soma/reindexer.h>

namespace tdbs = tiledbsoma;

#include "xptr-utils.h"         // xptr taggging utilitie


// [[Rcpp::export]]
void reindex_demo() {
    std::vector<int64_t> vec = { 1, 11, 101, 1001, 10001, 100001, 1000001, 10000001 };
    const int64_t* pvec = vec.data();
    int sz = vec.size();
    constexpr int nthrd = 4;

    auto p1 = new tdbs::IntIndexer(pvec, sz, nthrd);
    Rcpp::Rcout << "Allocated p1." << std::endl;
    delete p1;

    auto p2 = new tdbs::IntIndexer();
    Rcpp::Rcout << "Allocated p2." << std::endl;
    delete p2;
}

// [[Rcpp::export]]
Rcpp::XPtr<tdbs::IntIndexer> reindex_create() {
    auto p = new tdbs::IntIndexer();
    return make_xptr<tdbs::IntIndexer>(p);
}

// [[Rcpp::export]]
Rcpp::XPtr<tdbs::IntIndexer> reindex_map(Rcpp::XPtr<tdbs::IntIndexer> idx,
                                         const Rcpp::NumericVector nvec,
                                         const int nthreads = 4) {
    check_xptr_tag<tdbs::IntIndexer>(idx);
    std::vector<int64_t> vec = Rcpp::fromInteger64(nvec);
    idx->map_locations(vec.data(), vec.size(), nthreads);
    return idx;
}

// [[Rcpp::export]]
Rcpp::NumericVector reindex_lookup(Rcpp::XPtr<tdbs::IntIndexer> idx,
                                   const Rcpp::NumericVector kvec) {
    check_xptr_tag<tdbs::IntIndexer>(idx);
    std::vector<int64_t> keys = Rcpp::fromInteger64(kvec);
    int sz = keys.size();
    std::vector<int64_t> res(sz);
    idx->lookup(keys.data(), res.data(), sz);
    return Rcpp::toInteger64(res);
}
