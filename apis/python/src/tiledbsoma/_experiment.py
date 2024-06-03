# Copyright (c) 2021-2023 The Chan Zuckerberg Initiative Foundation
# Copyright (c) 2021-2023 TileDB, Inc.
#
# Licensed under the MIT License.

"""Implementation of a SOMA Experiment.
"""
import functools
from typing import Any, Optional

from somacore import experiment, options, query
from typing_extensions import Self

from . import _tdb_handles
from . import pytiledbsoma as clib
from ._collection import Collection, CollectionBase
from ._dataframe import DataFrame
from ._exception import SOMAError, map_exception_for_create
from ._indexer import IntIndexer
from ._measurement import Measurement
from ._tdb_handles import Wrapper
from ._soma_object import AnySOMAObject
from ._types import OpenTimestamp
from .options import SOMATileDBContext
from .options._soma_tiledb_context import _validate_soma_tiledb_context


class Experiment(  # type: ignore[misc]  # __eq__ false positive
    CollectionBase[AnySOMAObject],
    experiment.Experiment[  # type: ignore[type-var]
        DataFrame,
        Collection[Measurement],
        AnySOMAObject,
    ],
):
    """A collection subtype that combines observations and measurements
    from an individual experiment.

    In single cell biology, this can represent multiple modes of measurement
    across a single collection of cells (i.e., a "multimodal dataset").
    Within an experiment, a set of measurements on a single set of variables
    (i.e., features) is represented as a :class:`Measurement`.

    Attributes:
        obs (DataFrame):
            Primary annotations on the observation axis. The contents of the
            ``soma_joinid`` column define the observation index domain,
            AKA ``obs_id``. All observations for the Experiment must be
            defined in this dataframe.
        ms (Collection):
            A collection of named measurements.

    Example:
        >>> import tiledbsoma
        >>> with tiledbsoma.open("/path/to/experiment") as exp:
        ...     # While users can interact directly with an Experiment's fields:
        ...     obs_df = exp.obs
        ...
        ...     # the primary use case is to run queries on the experiment data.
        ...     q = exp.query(
        ...         "mtdna",
        ...         obs_query=tiledbsoma.AxisQuery(value_filter="tissue == 'lung'"),
        ...         var_query=tiledbsoma.AxisQuery(coords=(slice(50, 100),)),
        ...     )
        ...     query_obs = q.obs().concat().to_pandas()
        ...     query_var = q.var().concat().to_pandas()

    Lifecycle:
        Experimental.
    """

    __slots__ = ()
    _wrapper_type = _tdb_handles.ExperimentWrapper

    _subclass_constrained_soma_types = {
        "obs": ("SOMADataFrame",),
        "ms": ("SOMACollection",),
    }

    @classmethod
    def create(
        cls,
        uri: str,
        *,
        platform_config: Optional[options.PlatformConfig] = None,
        context: Optional[SOMATileDBContext] = None,
        tiledb_timestamp: Optional[OpenTimestamp] = None,
    ) -> Self:
        context = _validate_soma_tiledb_context(context)
        try:
            timestamp_ms = context._open_timestamp_ms(tiledb_timestamp)
            clib.SOMAGroup.create(
                uri=uri,
                soma_type="SOMAExperiment",
                ctx=context.native_context,
                timestamp=(0, timestamp_ms),
            )
            handle = cls._wrapper_type.open(uri, "w", context, tiledb_timestamp)
            return cls(
                handle,
                _dont_call_this_use_create_or_open_instead="tiledbsoma-internal-code",
            )
        except SOMAError as e:
            raise map_exception_for_create(e, uri) from None

    @classmethod
    def _set_create_metadata(cls, handle: Wrapper[Any]) -> None:
        # Root SOMA objects include a `dataset_type` entry to allow the
        # TileDB Cloud UI to detect that they are SOMA datasets.
        handle.metadata["dataset_type"] = "soma"
        return super()._set_create_metadata(handle)

    def axis_query(  # type: ignore
        self,
        measurement_name: str,
        *,
        obs_query: Optional[query.AxisQuery] = None,
        var_query: Optional[query.AxisQuery] = None,
    ) -> query.ExperimentAxisQuery[Self]:  # type: ignore
        """Creates an axis query over this experiment.
        Lifecycle: maturing
        """
        # mypy doesn't quite understand descriptors so it issues a spurious
        # error here.
        return query.ExperimentAxisQuery(  # type: ignore
            self,
            measurement_name,
            obs_query=obs_query or query.AxisQuery(),
            var_query=var_query or query.AxisQuery(),
            index_factory=functools.partial(
                IntIndexer,
                context=self.context,
            ),
        )
