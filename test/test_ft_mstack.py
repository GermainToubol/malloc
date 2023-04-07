import ctypes
import pytest
import resource

class T_MStack(ctypes.Structure):
    pass

T_MStack._fields_ = [
    ("previous", ctypes.c_void_p), #POINTER(T_MStack)),
    ("next", ctypes.c_void_p), #POINTER(T_MStack)),
    ("size", ctypes.c_size_t)
    ]

@pytest.fixture
def libmalloc(request):
    """ Provide the libft_malloc library

    """
    lib = ctypes.cdll.LoadLibrary(f'{request.config.rootdir}/libft_malloc.so')
    lib.ft_mstack_init.argtypes = [ctypes.POINTER(T_MStack), ctypes.c_size_t]
    if hasattr(lib, '_ft_mstack_resize'):
        lib._ft_mstack_resize.argtypes = [ctypes.c_size_t]
        lib._ft_mstack_resize.restype = ctypes.c_size_t
    if hasattr(lib, '_ft_mstack_insert'):
        lib._ft_mstack_insert.argtypes = [
            ctypes.POINTER(T_MStack),
            ctypes.POINTER(T_MStack)
            ]
    if hasattr(lib, '_ft_mstack_merge'):
        lib._ft_mstack_merge.argtypes = [ctypes.POINTER(T_MStack)]
        lib._ft_mstack_merge.restype = ctypes.c_ushort
    lib.ft_mstack_extend.argtypes = [
        ctypes.POINTER(T_MStack),
        ctypes.c_size_t
        ]
    lib.ft_mstack_extend.restype = ctypes.POINTER(T_MStack)

    return (lib)

class TestMStack:
    def test_mstack_init(self, libmalloc):
        stack = T_MStack()
        libmalloc.ft_mstack_init(ctypes.pointer(stack), 17)
        assert not stack.previous
        assert not stack.next
        assert stack.size == 17

    def test_mstack_resize(self, libmalloc):
        if not hasattr(libmalloc, '_ft_mstack_resize'):
            pytest.skip("static function test")
        assert libmalloc._ft_mstack_resize(4096) == 4096
        assert libmalloc._ft_mstack_resize(4000) == 4096
        assert libmalloc._ft_mstack_resize(68719476735) == 68719476736
        assert libmalloc._ft_mstack_resize(68719473000) == 68719476736

    def test_mstack_insert(self, libmalloc):
        if not hasattr(libmalloc, '_ft_mstack_insert'):
            pytest.skip("static function test")
        r1 = T_MStack()
        r2 = T_MStack()
        r3 = T_MStack()
        lst = [i for i in sorted([r1, r2, r3], key=lambda x:ctypes.addressof(x), reverse=True)]

        # Insert in order
        libmalloc.ft_mstack_init(ctypes.pointer(r1), 0)
        libmalloc.ft_mstack_init(ctypes.pointer(r2), 0)
        libmalloc.ft_mstack_init(ctypes.pointer(r3), 0)
        libmalloc._ft_mstack_insert(ctypes.pointer(lst[0]), ctypes.pointer(lst[1]))
        libmalloc._ft_mstack_insert(ctypes.pointer(lst[0]), ctypes.pointer(lst[2]))
        assert lst[0].next == ctypes.addressof(lst[1])
        assert lst[1].next == ctypes.addressof(lst[2])
        assert lst[1].previous == ctypes.addressof(lst[0])
        assert lst[2].previous == ctypes.addressof(lst[1])

        # Insert middle
        libmalloc.ft_mstack_init(ctypes.pointer(r1), 0)
        libmalloc.ft_mstack_init(ctypes.pointer(r2), 0)
        libmalloc.ft_mstack_init(ctypes.pointer(r3), 0)
        libmalloc._ft_mstack_insert(ctypes.pointer(lst[0]), ctypes.pointer(lst[2]))
        libmalloc._ft_mstack_insert(ctypes.pointer(lst[0]), ctypes.pointer(lst[1]))
        assert lst[0].next == ctypes.addressof(lst[1])
        assert lst[1].next == ctypes.addressof(lst[2])
        assert lst[1].previous == ctypes.addressof(lst[0])
        assert lst[2].previous == ctypes.addressof(lst[1])

        # Insert reverse
        libmalloc.ft_mstack_init(ctypes.pointer(r1), 0)
        libmalloc.ft_mstack_init(ctypes.pointer(r2), 0)
        libmalloc.ft_mstack_init(ctypes.pointer(r3), 0)
        libmalloc._ft_mstack_insert(ctypes.pointer(lst[2]), ctypes.pointer(lst[1]))
        libmalloc._ft_mstack_insert(ctypes.pointer(lst[1]), ctypes.pointer(lst[0]))
        assert lst[0].next == ctypes.addressof(lst[1])
        assert lst[1].next == ctypes.addressof(lst[2])
        assert lst[1].previous == ctypes.addressof(lst[0])
        assert lst[2].previous == ctypes.addressof(lst[1])

    def test_ft_mstack_merge(self, libmalloc):
        if not hasattr(libmalloc, '_ft_mstack_merge'):
            pytest.skip('static function test')
        r1 = T_MStack()
        r2 = T_MStack()
        r3 = T_MStack()
        lst = [i for i in sorted([r1, r2, r3], key=lambda x:ctypes.addressof(x), reverse=True)]
        # Merge forward
        lst[0].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1])
        lst[1].size = ctypes.addressof(lst[1]) - ctypes.addressof(lst[2])
        lst[2].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1])
        lst[0].next = ctypes.addressof(lst[1])
        lst[1].next = ctypes.addressof(lst[2])
        lst[1].previous = ctypes.addressof(lst[0])
        lst[2].previous = ctypes.addressof(lst[1])
        res = libmalloc._ft_mstack_merge(ctypes.pointer(lst[0]))
        assert lst[0].next == ctypes.addressof(lst[2])
        assert lst[0].size == ctypes.addressof(lst[0]) - ctypes.addressof(lst[2])
        assert lst[2].previous == ctypes.addressof(lst[0])
        assert res == 1

        # No merge forward
        lst[0].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1]) - 5
        lst[1].size = ctypes.addressof(lst[1]) - ctypes.addressof(lst[2]) - 5
        lst[2].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1]) - 5
        lst[0].next = ctypes.addressof(lst[1])
        lst[1].next = ctypes.addressof(lst[2])
        lst[1].previous = ctypes.addressof(lst[0])
        lst[2].previous = ctypes.addressof(lst[1])
        s0 = lst[0].size
        res = libmalloc._ft_mstack_merge(ctypes.pointer(lst[0]))
        assert lst[0].next == ctypes.addressof(lst[1])
        assert lst[0].size == s0
        assert lst[2].previous == ctypes.addressof(lst[1])
        assert res == 0

        # Merge backward
        lst[0].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1])
        lst[1].size = ctypes.addressof(lst[1]) - ctypes.addressof(lst[2])
        lst[2].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1])
        lst[0].next = ctypes.addressof(lst[1])
        lst[1].next = ctypes.addressof(lst[2])
        lst[1].previous = ctypes.addressof(lst[0])
        lst[2].previous = ctypes.addressof(lst[1])
        s1, s2 = lst[1].size, lst[2].size
        res = libmalloc._ft_mstack_merge(ctypes.pointer(lst[2]))
        assert lst[1].next is None
        assert lst[1].size == s1 + s2
        assert res == 2

        # Merge both
        lst[0].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1])
        lst[1].size = ctypes.addressof(lst[1]) - ctypes.addressof(lst[2])
        lst[2].size = ctypes.addressof(lst[0]) - ctypes.addressof(lst[1])
        lst[0].next = ctypes.addressof(lst[1])
        lst[1].next = ctypes.addressof(lst[2])
        lst[1].previous = ctypes.addressof(lst[0])
        lst[2].previous = ctypes.addressof(lst[1])
        s0, s1, s2 = lst[0].size, lst[1].size, lst[2].size
        res = libmalloc._ft_mstack_merge(ctypes.pointer(lst[1]))
        assert lst[0].next is None
        assert lst[0].size == s0 + s1 + s2
        assert res == 3

    def test_ft_mstack_extend(self, libmalloc):
        root = ctypes.POINTER(T_MStack)()
        for i in range(10):
            root = libmalloc.ft_mstack_extend(root, 4096 * (i + 1))
        base = ctypes.cast(root, ctypes.c_void_p)
        tot_size = 0
        while base:
            tot_size += ctypes.cast(base, ctypes.POINTER(T_MStack)).contents.size
            base = ctypes.cast(base, ctypes.POINTER(T_MStack)).contents.next
        assert tot_size == 4096 * 55      # Sum i + 1 for i in range(10)
