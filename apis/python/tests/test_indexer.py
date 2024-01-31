import numpy as np
import pandas as pd

from tiledbsoma._index_util import tiledbsoma_build_index
from tiledbsoma.options import SOMATileDBContext
from tiledbsoma.options._soma_tiledb_context import _validate_soma_tiledb_context


def indexer_test(keys: np.array, lookups: np.array, fail: bool):
    if fail:
        indexer_test_fail(keys, lookups)
    else:
        indexer_test_pass(keys, lookups)


def indexer_test_fail(keys: np.array, lookups: np.array):
    try:
        context = _validate_soma_tiledb_context(SOMATileDBContext())
        index = tiledbsoma_build_index(keys, context=context)
        index.get_indexer(lookups)
        raise AssertionError("should have failed")
    except pd.errors.InvalidIndexError:
        pass
    except Exception as e:
        if str(e) == "RuntimeError: There are duplicate keys.":
            pass

    try:
        pd_index = pd.Index(keys)
        pd_index.get_indexer(lookups)
        raise AssertionError("should have failed")
    except pd.errors.InvalidIndexError:
        pass
    except Exception as e:
        if str(e) == "RuntimeError: There are duplicate keys.":
            pass


def indexer_test_pass(keys: np.array, lookups: np.array):
    context = _validate_soma_tiledb_context(SOMATileDBContext())
    indexer = tiledbsoma_build_index(keys, context=context)
    results = indexer.get_indexer(lookups)
    panda_indexer = pd.Index(keys)
    panda_results = panda_indexer.get_indexer(lookups)
    assert np.equal(results.all(), panda_results.all())


test_data = [
    {"keys": [1], "lookups": [1, 1, 1, 1], "pass": True},
    {
        "keys": [-1, -1, -1, 0, 0, 0],
        "lookups": [1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5, 1, 2, 3, 4, 5],
        "pass": False,
    },
    {
        "keys": [
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
        ],
        "lookups": [-10000, 1, 2, 3, 5, 6],
        "pass": False,
    },
    {
        "keys": [-1, 1, 2, 3, 4, 5],
        "lookups": [
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
        ],
        "pass": True,
    },
    {
        "keys": [-10000, -100000, 200000, 5, 1, 7],
        "lookups": [
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
        ],
        "pass": True,
    },
    {
        "keys": [-10000, -200000, 1000, 3000, 1, 2],
        "lookups": [
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
            -1,
            1,
            2,
            3,
            4,
            5,
        ],
        "pass": True,
    },
    {
        "keys": [i for i in range(1, 10000)],
        "lookups": [i for i in range(1, 10)],
        "pass": True,
    },
    {
        "keys": [i for i in range(1, 10000)],
        "lookups": [
            525,
            1293,
            1805,
            5802,
            7636,
            7754,
            7791,
            7957,
            7959,
            8067,
            8340,
            8736,
            8806,
            9329,
            9377,
            9653,
        ],
        "pass": True,
    },
    {
        "keys": [i for i in range(1, 10000)],
        "lookups": [i for i in range(1, 10000)],
        "pass": True,
    },
]


def test_indexer():
    for data in test_data:
        indexer_test(data["keys"], data["lookups"], not data["pass"])
