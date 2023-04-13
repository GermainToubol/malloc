import ctypes as c
from _ctypes import dlclose
import pytest

class T_GData(c.Structure):
    _fields_ = [
        ('prevsize', c.c_uint64),
        ('size', c.c_uint64),
        ('data', c.c_uint8 * 240)         # 256 - 8 (prevsize already allocated)
        ]

class T_Node(c.Structure):
    _fields_ = [
        ('parent', c.c_void_p),
        ('left', c.c_void_p),
        ('right', c.c_void_p),
        ('color', c.c_uint64),
        ('size', c.c_uint64)
        ]

@pytest.fixture
def libmalloc(request):
    """ Provide the libft_malloc library

    """
    lib = c.cdll.LoadLibrary(f'{request.config.rootdir}/libft_malloc.so')
    lib.ft_gdata_init.argtypes = [c.POINTER(T_GData), c.c_size_t]
    lib.ft_gdata_init.restype = c.c_bool
    lib.ft_gdata_free.argtypes = [c.POINTER(T_GData)]
    lib.ft_gdata_alloc.argtypes = [c.POINTER(T_GData), c.c_size_t, c.c_uint8]
    lib.ft_gdata_alloc.restype = c.c_void_p
    if (hasattr(lib, '_ft_gdata_merge')):
        lib._ft_gdata_merge.argtypes = [c.POINTER(T_GData)]
        lib._ft_gdata_merge.restype = c.c_uint8
    lib.ft_gdata_set_area.argtypes = [c.c_void_p, c.c_size_t, c.c_bool, c.c_bool]
    lib.ft_tree_insert.argtypes = [c.POINTER(T_Node), c.POINTER(T_Node)]
    lib.ft_tree_insert.restype = c.c_void_p
    lib.ft_tree_delete.argtypes = [c.POINTER(T_Node), c.POINTER(T_Node)]
    lib.ft_tree_delete.restype = c.c_void_p
    lib.ft_tree_search.argtypes = [c.POINTER(T_Node), c.c_uint64]
    lib.restype = c.c_void_p
    yield (lib)
    dlclose(lib._handle)

class TestIntegrate:
    def test_on_gdata_init(self, libmalloc):
        data = (T_GData * 5)()
        libmalloc.ft_gdata_init(c.pointer(data[0]), 256)
        a = c.POINTER(T_Node).in_dll(libmalloc, "g_root")
        assert c.addressof(data[0].data) == c.addressof(a.contents)

    def test_on_libmalloc_reinit(self, libmalloc):
        data = (T_GData * 5)()
        libmalloc.ft_gdata_init(c.pointer(data[0]), 256)
        a = c.POINTER(T_Node).in_dll(libmalloc, "g_root")
        assert a.contents.parent is None
        assert a.contents.left is None
        assert a.contents.right is None

        libmalloc.ft_gdata_init(c.pointer(data[1]), 512)
        assert a.contents.parent is None
        assert a.contents.left is None
        assert a.contents.right == c.addressof(data[1].data)
