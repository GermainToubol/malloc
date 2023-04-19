import ctypes as c
from _ctypes import dlclose
import pytest

class T_Heap(c.Structure):
    _fields_ = [
        ("parent", c.c_void_p),
        ("left", c.c_void_p),
        ("right", c.c_void_p),
        ("prev", c.c_void_p),
        ("next", c.c_void_p)
        ]

class T_Queue(c.Structure):
    _fields_ = [
        ("head", c.c_void_p),
        ("tail", c.c_void_p)
        ]

class T_Tiny(c.Structure):
    _fields_ = [
        ("node", T_Heap),
        ("table", c.c_uint64 * 2)
        ]

@pytest.fixture
def libmalloc(request):
    lib = c.cdll.LoadLibrary(f'{request.config.rootdir}/libft_malloc.so')
    lib.ft_tiny_init.argtypes = [c.POINTER(T_Tiny)]
    lib.ft_tiny_alloc.argtypes = [c.POINTER(T_Tiny)]
    lib.ft_tiny_alloc.restype = c.c_void_p
    lib.ft_tiny_free.argtypes = [c.POINTER(T_Tiny), c.c_void_p]
    yield(lib)
    dlclose(lib._handle)


class TestTiny:
    def test_tiny_init(self, libmalloc):
        buff = (c.c_uint8 * 4096)()
        for i in range(len(buff)):
            buff[i] = 17
        node = c.cast(c.pointer(buff), c.POINTER(T_Tiny)).contents
        libmalloc.ft_tiny_init(c.pointer(node))
        assert node.node.parent is None
        assert node.node.left is None
        assert node.node.right is None
        assert node.node.prev is None
        assert node.node.next is None
        assert node.table[0] == 0xffffffffffffffff
        assert node.table[1] == 0b1111111111111111111111111111111111111

    def test_tiny_alloc_small(self, libmalloc):
        buff = (c.c_uint8 * 4096)()
        for i in range(len(buff)):
            buff[i] = 17
        node = c.cast(c.pointer(buff), c.POINTER(T_Tiny)).contents
        libmalloc.ft_tiny_init(c.pointer(node))

        assert libmalloc.ft_tiny_alloc(c.pointer(node)) == c.addressof(buff) + 56
        assert node.table[0] == 0xfffffffffffffffe
        assert libmalloc.ft_tiny_alloc(c.pointer(node)) == c.addressof(buff) + 56 + 40
        assert node.table[0] == 0xfffffffffffffffc

    def test_tiny_alloc_all(self, libmalloc):
        buff = (c.c_uint8 * 4096)()
        for i in range(len(buff)):
            buff[i] = 17
        node = c.cast(c.pointer(buff), c.POINTER(T_Tiny)).contents
        libmalloc.ft_tiny_init(c.pointer(node))

        for i in range(101):
            assert libmalloc.ft_tiny_alloc(c.pointer(node)) == c.addressof(buff) + 56 + 40 * i
        assert node.table[0] == 0
        assert node.table[1] == 0

        assert libmalloc.ft_tiny_alloc(c.pointer(node)) is None

    def test_tiny_free(self, libmalloc):
        buff = (c.c_uint8 * 4096)()
        for i in range(len(buff)):
            buff[i] = 17
        node = c.cast(c.pointer(buff), c.POINTER(T_Tiny)).contents
        node.table[0] = 0
        node.table[1] = 0

        libmalloc.ft_tiny_free(c.pointer(node), c.addressof(buff) + 56 + 1)
        assert node.table[0] == 0
        assert node.table[1] == 0
        libmalloc.ft_tiny_free(c.pointer(node), c.addressof(buff) + 56 + 40 * 101)
        assert node.table[0] == 0
        assert node.table[1] == 0
        libmalloc.ft_tiny_free(c.pointer(node), c.addressof(buff) + 56)
        assert node.table[0] == 1
        assert node.table[1] == 0
        libmalloc.ft_tiny_free(c.pointer(node), c.addressof(buff) + 56 + 40 * 3)
        assert node.table[0] == 0b1001
        assert node.table[1] == 0
        libmalloc.ft_tiny_free(c.pointer(node), c.addressof(buff) + 56 + 40 * 63)
        assert node.table[0] == 0b1001 | (1 << 63)
        assert node.table[1] == 0
        libmalloc.ft_tiny_free(c.pointer(node), c.addressof(buff) + 56 + 40 * 64)
        assert node.table[0] == 0b1001 | (1 << 63)
        assert node.table[1] == 1
        libmalloc.ft_tiny_free(c.pointer(node), c.addressof(buff) + 56 + 40 * 100)
        assert node.table[0] == 0b1001 | (1 << 63)
        assert node.table[1] == 1 | (1 << 36)
