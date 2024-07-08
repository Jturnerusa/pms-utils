import enum
import os
import pms_utils.atom
import pms_utils.depend
from typing import Callable, ClassVar, Iterator

class Metadata:
    def __init__(self, *args, **kwargs) -> None: ...
    def __eq__(self, arg0: Metadata) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: Metadata) -> bool: ...
    @property
    def BDEPEND(self) -> pms_utils.depend.DependExpr: ...
    @property
    def DEFINED_PHASES(self) -> defined_phases: ...
    @property
    def DEPEND(self) -> pms_utils.depend.DependExpr: ...
    @property
    def DESCRIPTION(self) -> str: ...
    @property
    def EAPI(self) -> eapi: ...
    @property
    def HOMEPAGE(self) -> homepage: ...
    @property
    def IDEPEND(self) -> pms_utils.depend.DependExpr: ...
    @property
    def INHERITED(self) -> inherited: ...
    @property
    def IUSE(self) -> iuse: ...
    @property
    def KEYWORDS(self) -> keywords: ...
    @property
    def LICENSE(self) -> license: ...
    @property
    def PDEPEND(self) -> pms_utils.depend.DependExpr: ...
    @property
    def PROPERTIES(self) -> properties: ...
    @property
    def RDEPEND(self) -> pms_utils.depend.DependExpr: ...
    @property
    def REQUIRED_USE(self) -> required_use: ...
    @property
    def RESTRICT(self) -> restrict: ...
    @property
    def SLOT(self) -> pms_utils.atom.Slot: ...
    @property
    def SRC_URI(self) -> src_uri: ...

class URI:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: URI) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: URI) -> bool: ...

class defined_phases:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: defined_phases) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[phases]: ...
    def __ne__(self, arg0: defined_phases) -> bool: ...

class eapi:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: eapi) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: eapi) -> bool: ...

class homepage:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: homepage) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[URI | homepage]: ...
    def __ne__(self, arg0: homepage) -> bool: ...
    @property
    def conditional(self) -> pms_utils.depend.UseConditional | pms_utils.depend.GroupHeaderOp | None: ...
    @property
    def nodes(self) -> list[URI | homepage]: ...

class inherited:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: inherited) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[inherited_elem]: ...
    def __ne__(self, arg0: inherited) -> bool: ...

class inherited_elem:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: inherited_elem) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: inherited_elem) -> bool: ...

class iuse:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: iuse) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[iuse_elem]: ...
    def __ne__(self, arg0: iuse) -> bool: ...

class iuse_elem:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: iuse_elem) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: iuse_elem) -> bool: ...
    @property
    def default_enabled(self) -> bool: ...
    @property
    def useflag(self) -> pms_utils.atom.Useflag: ...

class keyword:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: keyword) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: keyword) -> bool: ...

class keywords:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: keywords) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[keyword]: ...
    def __ne__(self, arg0: keywords) -> bool: ...

class license:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: license) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[license_elem | license]: ...
    def __ne__(self, arg0: license) -> bool: ...
    @property
    def conditional(self) -> pms_utils.depend.UseConditional | pms_utils.depend.GroupHeaderOp | None: ...
    @property
    def nodes(self) -> list[license_elem | license]: ...

class license_elem:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: license_elem) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: license_elem) -> bool: ...

class phases(enum.Enum):
    __new__: ClassVar[Callable] = ...
    _generate_next_value_: ClassVar[Callable] = ...
    _member_map_: ClassVar[dict] = ...
    _member_names_: ClassVar[list] = ...
    _member_type_: ClassVar[type[object]] = ...
    _unhashable_values_: ClassVar[list] = ...
    _use_args_: ClassVar[bool] = ...
    _value2member_map_: ClassVar[dict] = ...
    _value_repr_: ClassVar[None] = ...
    compile: ClassVar[phases] = ...
    config: ClassVar[phases] = ...
    configure: ClassVar[phases] = ...
    info: ClassVar[phases] = ...
    install: ClassVar[phases] = ...
    nofetch: ClassVar[phases] = ...
    postinst: ClassVar[phases] = ...
    postrm: ClassVar[phases] = ...
    preinst: ClassVar[phases] = ...
    prepare: ClassVar[phases] = ...
    prerm: ClassVar[phases] = ...
    pretend: ClassVar[phases] = ...
    setup: ClassVar[phases] = ...
    test: ClassVar[phases] = ...
    unpack: ClassVar[phases] = ...

class properties:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: properties) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[properties_elem | properties]: ...
    def __ne__(self, arg0: properties) -> bool: ...
    @property
    def conditional(self) -> pms_utils.depend.UseConditional | pms_utils.depend.GroupHeaderOp | None: ...
    @property
    def nodes(self) -> list[properties_elem | properties]: ...

class properties_elem:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: properties_elem) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: properties_elem) -> bool: ...
    @property
    def string(self) -> str: ...
    @property
    def type(self) -> properties_elem_type: ...

class properties_elem_type(enum.Enum):
    __new__: ClassVar[Callable] = ...
    UNKNOWN: ClassVar[properties_elem_type] = ...
    _generate_next_value_: ClassVar[Callable] = ...
    _member_map_: ClassVar[dict] = ...
    _member_names_: ClassVar[list] = ...
    _member_type_: ClassVar[type[object]] = ...
    _unhashable_values_: ClassVar[list] = ...
    _use_args_: ClassVar[bool] = ...
    _value2member_map_: ClassVar[dict] = ...
    _value_repr_: ClassVar[None] = ...
    interactive: ClassVar[properties_elem_type] = ...
    live: ClassVar[properties_elem_type] = ...
    test_network: ClassVar[properties_elem_type] = ...

class required_use:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: required_use) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[pms_utils.atom.Usedep | required_use]: ...
    def __ne__(self, arg0: required_use) -> bool: ...
    @property
    def conditional(self) -> pms_utils.depend.UseConditional | pms_utils.depend.GroupHeaderOp | None: ...
    @property
    def nodes(self) -> list[pms_utils.atom.Usedep | required_use]: ...

class restrict:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: restrict) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[restrict_elem | restrict]: ...
    def __ne__(self, arg0: restrict) -> bool: ...
    @property
    def conditional(self) -> pms_utils.depend.UseConditional | pms_utils.depend.GroupHeaderOp | None: ...
    @property
    def nodes(self) -> list[restrict_elem | restrict]: ...

class restrict_elem:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: restrict_elem) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: restrict_elem) -> bool: ...
    @property
    def string(self) -> str: ...
    @property
    def type(self) -> restrict_elem_type: ...

class restrict_elem_type(enum.Enum):
    __new__: ClassVar[Callable] = ...
    UNKNOWN: ClassVar[restrict_elem_type] = ...
    _generate_next_value_: ClassVar[Callable] = ...
    _member_map_: ClassVar[dict] = ...
    _member_names_: ClassVar[list] = ...
    _member_type_: ClassVar[type[object]] = ...
    _unhashable_values_: ClassVar[list] = ...
    _use_args_: ClassVar[bool] = ...
    _value2member_map_: ClassVar[dict] = ...
    _value_repr_: ClassVar[None] = ...
    fetch: ClassVar[restrict_elem_type] = ...
    mirror: ClassVar[restrict_elem_type] = ...
    strip: ClassVar[restrict_elem_type] = ...
    test: ClassVar[restrict_elem_type] = ...
    userpriv: ClassVar[restrict_elem_type] = ...

class src_uri:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: src_uri) -> bool: ...
    def __hash__(self) -> int: ...
    def __iter__(self) -> Iterator[uri_elem | src_uri]: ...
    def __ne__(self, arg0: src_uri) -> bool: ...
    @property
    def conditional(self) -> pms_utils.depend.UseConditional | pms_utils.depend.GroupHeaderOp | None: ...
    @property
    def nodes(self) -> list[uri_elem | src_uri]: ...

class uri_elem:
    def __init__(self, arg0: str) -> None: ...
    def __eq__(self, arg0: uri_elem) -> bool: ...
    def __hash__(self) -> int: ...
    def __ne__(self, arg0: uri_elem) -> bool: ...
    @property
    def filename(self) -> os.PathLike | None: ...
    @property
    def uri(self) -> URI | os.PathLike: ...
