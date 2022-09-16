#!/usr/bin/env python

import tiledbsoma.libtiledbsoma as sc
import tiledbsoma.util
import pyarrow as pa
import tiledb
from tiledbsoma.query_condition import QueryCondition

use_cloud = True
stream_count = 2
verbose = False

if verbose:
    sc.config_logging("debug")

soma = "krasnow"
soma = "tabula-sapiens-immune"

if use_cloud:
    obs_uri = f"tiledb://george.powley/{soma}-obs"
    var_uri = f"tiledb://george.powley/{soma}-var"
    x_data_uri = f"tiledb://george.powley/{soma}-x-data"
else:
    obs_uri = f"s3://tiledb-gspowley/data/sc/{soma}/obs"
    var_uri = f"s3://tiledb-gspowley/data/sc/{soma}/ms/mRNA/var"
    x_data_uri = f"s3://tiledb-gspowley/data/sc/{soma}/ms/mRNA/X/data"


obs_schema = tiledb.open(obs_uri).schema


def read_x_slice(value_filter, config={}):

    qc = QueryCondition(value_filter)

    obs_reader = sc.SOMAReader(
        obs_uri,
        name="obs",
        column_names=["soma_rowid", "cell_type"],
        query_condition=qc,
        schema=obs_schema,
        platform_config=config,
    )

    var_reader = sc.SOMAReader(
        var_uri, name="var", column_names=["soma_rowid"], platform_config=config
    )

    obs_reader.submit()
    var_reader.submit()

    obs = obs_reader.read_next()
    var = var_reader.read_next()

    if verbose:
        print("obs")
        print(obs)
        print(obs.to_pandas())
        print("var")
        print(var)
        print(var.to_pandas())

    assert obs_reader.results_complete() and var_reader.results_complete()

    s = tiledbsoma.util.get_start_stamp()

    x_reader = sc.SOMAReader(x_data_uri, name="X/data", platform_config=config)
    x_reader.set_dim_points("__dim_0", obs.column("soma_rowid"))
    # x_reader.set_dim_points("__dim_1", var.column("soma_rowid"))

    x_reader.submit()

    tables = []
    while batch := x_reader.read_next():
        tables.append(batch)
        if verbose:
            print(batch)

    full_table = pa.concat_tables(tables)

    print(tiledbsoma.util.format_elapsed(s, "Read X/data"))

    print(f"obs {obs.shape}")
    print(f"var {var.shape}")

    if verbose:
        print(full_table)
    print(f"X/data {full_table.shape} (batches = {len(tables)})")

    return full_table, obs


cond = "cell_type == 'pulmonary ionocyte'"
cond = "cell_type == 'alveolar macrophage'"
cond = "cell_type == 'macrophage'"

config = {}
config["soma.init_buffer_bytes"] = f"{4 * 1024**3}"
if verbose:
    config["config.logging_level"] = "5"

print(f"Read from {x_data_uri}")
print(f"  value_filter: {cond}")

x_large_buffers, obs = read_x_slice(cond, config)
# x_small_buffers, _ = read_x_slice(cond)

# exit(0)

# assert x_large_buffers == x_small_buffers


def read_partition(uri, name, config, partition_index, partition_count, obs):
    reader = sc.SOMAReader(
        uri,
        name=name,
        platform_config=config,
    )
    reader.set_dim_points(
        "__dim_0",
        obs.column("soma_rowid"),
        partition_index=partition_index,
        partition_count=partition_count,
    )
    reader.submit()

    return reader


readers = []

print(f"\nRead with {stream_count} streams")

s = tiledbsoma.util.get_start_stamp()

for i in range(stream_count):
    reader = read_partition(x_data_uri, f"X/data.{i}", config, i, stream_count, obs)
    readers.append(reader)

done = False
tables = []
while not done:
    done = True
    for i in range(stream_count):
        if batch := readers[i].read_next():
            tables.append(batch)
            done = False

full_table = pa.concat_tables(tables)

print(tiledbsoma.util.format_elapsed(s, f"Read X/data ({stream_count} streams)"))

print(f"X/data {full_table.shape} (batches = {len(tables)})")

assert x_large_buffers == full_table
print("[PASS] Results equal.")
