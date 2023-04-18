import ctypes as c
from _ctypes import dlclose
import pytest

class T_Heap(c.Structure):
    _fields_ = [
        ("parent", c.c_void_p),
        ("left", c.c_void_p),
        ("right", c.c_void_p),
        ("next", c.c_void_p)
        ]

class T_Queue(c.Structure):
    _fields_ = [
        ("head", c.POINTER(T_Heap)),
        ("tail", c.POINTER(T_Heap))
        ]

@pytest.fixture
def libmalloc(request):
    lib = c.cdll.LoadLibrary(f'{request.config.rootdir}/libft_malloc.so')
    yield(lib)
    dlclose(lib._handle)

class TestHeap:
    def test_ft_heap_insert(self, libmalloc):
        ...
