import ctypes as c
from _ctypes import dlclose
import pytest

class T_GData(c.Structure):
    _fields_ = [
        ('prevsize', c.c_uint64),
        ('size', c.c_uint64),
        ('data', c.c_uint8 * 240)         # 256 - 8 (prevsize already allocated)
        ]

class T_FREE(c.Structure):
    _fields_ = [
        ('previous', c.POINTER(T_GData)),
        ('next', c.POINTER(T_GData)),
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
    yield (lib)
    dlclose(lib._handle)

class TestFtGData:
    # ______________________________________________________________________
    def _init_tab(self, tab):
        for i, elm in enumerate(tab):
            tab[i].size = 256 | 1 | 0b110
            tab[i].prevsize = 17
        tab[0].prevsize = 0
        tab[0].size = 256 | 0b110
        tab[-1].size = 0 | 1

    # ______________________________________________________________________
    def test_ft_gdata_init(self, libmalloc):
        gdata = T_GData()
        assert libmalloc.ft_gdata_init(c.pointer(gdata), 0) == False
        assert gdata.size == 0
        assert libmalloc.ft_gdata_init(c.pointer(gdata), 64) == False
        assert gdata.size == 64
        assert libmalloc.ft_gdata_init(c.pointer(gdata), 43) == True

        assert libmalloc.ft_gdata_init(c.POINTER(T_GData)(), 0) == True

    # ______________________________________________________________________
    def test_ft_gdata_init2(self, libmalloc):
        tab = (T_GData * 5)()
        tab[0].prevsize = 0;
        for i, elm in enumerate(tab[:-1]):
            libmalloc.ft_gdata_init(c.pointer(elm), 256)
            assert tab[i].size == tab[i + 1].prevsize

    # ______________________________________________________________________
    def test_ft_gdata_free_nomerge(self, libmalloc):
        tab = (T_GData * 5)()
        self._init_tab(tab)
        libmalloc.ft_gdata_free(c.pointer(tab[2]))
        assert tab[2].size & 0b110 == 0
        assert tab[3].prevsize == 256
        assert tab[3].size & 1 == 0

        libmalloc.ft_gdata_free(c.pointer(tab[4]))
        assert tab[4].size == 1

        libmalloc.ft_gdata_free(c.POINTER(T_GData)())

    # ______________________________________________________________________
    def test_ft_gdata_free_merge(self, libmalloc):
        tab = (T_GData * 7)()
        self._init_tab(tab)
        libmalloc.ft_gdata_free(c.pointer(tab[1]))
        libmalloc.ft_gdata_free(c.pointer(tab[2]))
        assert tab[1].size == 256 * 2 + 1
        assert tab[3].prevsize == 256 * 2

        libmalloc.ft_gdata_free(c.pointer(tab[5]))
        libmalloc.ft_gdata_free(c.pointer(tab[4]))
        assert tab[4].size == 256 * 2 + 1
        assert tab[6].prevsize == 256 * 2

        libmalloc.ft_gdata_free(c.pointer(tab[3]))
        assert tab[1].size == 5 * 256 + 1
        assert tab[6].prevsize == 256 * 5

    # ______________________________________________________________________
    def test_ft_gdata_alloc(self, libmalloc):
        tab = (T_GData * 7)()
        self._init_tab(tab)
        assert libmalloc.ft_gdata_alloc(c.pointer(tab[1]), 256, 1) is None

        libmalloc.ft_gdata_free(c.pointer(tab[1]))
        assert libmalloc.ft_gdata_alloc(c.pointer(tab[1]), 248, 1) == c.addressof(tab[1].data)
        assert tab[1].size == 256 | 1 | 0b010
        assert tab[2].size == 256 + 7

        libmalloc.ft_gdata_free(c.pointer(tab[1]))
        assert libmalloc.ft_gdata_alloc(c.pointer(tab[1]), 249, 1) is None

    def test_ft_gdata_alloc2(self, libmalloc):
        tab = (T_GData * 7)()
        self._init_tab(tab)
        libmalloc.ft_gdata_free(c.pointer(tab[1]))
        libmalloc.ft_gdata_free(c.pointer(tab[2]))
        libmalloc.ft_gdata_free(c.pointer(tab[3]))
        tab[3].size = 0
        tab[3].prevsize = 0
        assert libmalloc.ft_gdata_alloc(c.pointer(tab[1]), 248, 2) == c.addressof(tab[3].data)
        assert tab[3].prevsize == 512
        assert tab[1].size == 513
        assert tab[3].size == 256 | 0b100

    def test_ft_gdata_alloc3(self, libmalloc):
        tab = (T_GData * 7)()
        self._init_tab(tab)
        libmalloc.ft_gdata_free(c.pointer(tab[1]))
        libmalloc.ft_gdata_free(c.pointer(tab[2]))
        libmalloc.ft_gdata_free(c.pointer(tab[3]))
        assert libmalloc.ft_gdata_alloc(c.pointer(tab[1]), 504, 3) == c.addressof(tab[1].data)
        assert tab[1].size == 256 * 3 | 0b110 | 1

    # ______________________________________________________________________
    def test_ft_gdata_merge(self, libmalloc):
        if not hasattr(libmalloc, '_ft_gdata_merge'):
            pytest.skip('static function test')
        tab = (T_GData * 5)()
        self._init_tab(tab)

        # No merge
        tab[3].size = 257
        tab[4].prevsize = 256
        tab[4].size = 256 | 0b110
        res = libmalloc._ft_gdata_merge(c.pointer(tab[3]))
        assert res == 0
        for i, j in zip(tab[2].data, tab[1].data):
            assert i == j
        assert tab[2].size == 256 + 7
        assert tab[2].prevsize == 17
        assert tab[4].prevsize == 256

        # Merge backward
        self._init_tab(tab)
        libmalloc.ft_gdata_init(c.pointer(tab[2]), 256)
        libmalloc.ft_gdata_init(c.pointer(tab[3]), 256)
        res = libmalloc._ft_gdata_merge(c.pointer(tab[3]))
        assert res == 1
        assert tab[2].size == 512
        assert tab[4].prevsize == 512

        self._init_tab(tab)
        libmalloc.ft_gdata_init(c.pointer(tab[2]), 256)
        libmalloc.ft_gdata_init(c.pointer(tab[3]), 256)
        tab[2].size = 257
        res = libmalloc._ft_gdata_merge(c.pointer(tab[3]))
        assert res == 1
        assert tab[2].size == 513
        assert tab[4].prevsize == 512

        self._init_tab(tab)
        libmalloc.ft_gdata_init(c.pointer(tab[0]), 256)
        res = libmalloc._ft_gdata_merge(c.pointer(tab[0]))
        assert res == 0
        assert tab[0].size == 256

        # Merge forward
        self._init_tab(tab)
        libmalloc.ft_gdata_init(c.pointer(tab[2]), 256)
        libmalloc.ft_gdata_init(c.pointer(tab[3]), 256)
        tab[2].size = 257
        res = libmalloc._ft_gdata_merge(c.pointer(tab[2]))
        assert res == 2
        assert tab[2].size == 513
        assert tab[4].prevsize == 512

        self._init_tab(tab)
        libmalloc.ft_gdata_init(c.pointer(tab[4]), 0)
        tab[4].size = 1
        res = libmalloc._ft_gdata_merge(c.pointer(tab[4]))
        assert res == 0
        assert tab[4].size == 1
        assert tab[4].prevsize == 17

        # Merge both
        self._init_tab(tab)
        libmalloc.ft_gdata_init(c.pointer(tab[1]), 256)
        tab[1].size = 257
        tab[2].prevsize = 256
        tab[2].size = 256
        tab[3].prevsize = 256
        tab[3].size = 256
        tab[4].prevsize = 256
        tab[4].size = 0
        res = libmalloc._ft_gdata_merge(c.pointer(tab[2]))
        assert res == 3
        assert tab[1].size == 256 * 3 + 1
        assert tab[4].prevsize == 256 * 3

    # ----------------------------------------------------------------------
    def test_ft_gdata_set_area(self, libmalloc):
        area = (c.c_uint8 * 4096)()
        for i, _ in enumerate(area):
            area[i] = 12
        libmalloc.ft_gdata_set_area(area, 512, False, False)
        start0 = c.cast(area, c.POINTER(T_GData)).contents
        assert start0.prevsize == 0
        assert start0.size == 512 - 16
        end0 = c.cast(c.addressof(area) + 512 - 16, c.POINTER(T_GData)).contents
        assert end0.prevsize == 512 - 16
        assert end0.size == 0

        libmalloc.ft_gdata_set_area(c.addressof(area) + 1024, 512, False, False)
        libmalloc.ft_gdata_set_area(c.addressof(area) + 512, 512, False, False)
        start1 = c.cast(c.addressof(area) + 512, c.POINTER(T_GData)).contents
        end1 = c.cast(c.addressof(area) + 1024 - 16, c.POINTER(T_GData)).contents
        start2 = c.cast(c.addressof(area) + 1024, c.POINTER(T_GData)).contents
        end2 = c.cast(c.addressof(area) + 1024 + 512 - 16, c.POINTER(T_GData)).contents
        assert start1.prevsize == 0
        assert start1.size == 512 - 16
        assert end1.prevsize == 512 - 16
        assert end1.size == 0
        assert start2.prevsize == 0
        assert start2.size == 512 - 16

    def test_ft_gdata_set_area2(self, libmalloc):
        area = (c.c_uint8 * 4096)()
        for i, _ in enumerate(area):
            area[i] = 12
        libmalloc.ft_gdata_set_area(area, 512, False, False)
        start0 = c.cast(area, c.POINTER(T_GData)).contents
        libmalloc.ft_gdata_alloc(c.pointer(start0), 400, 1)
        end0 = c.cast(c.addressof(area) + 512 - 16, c.POINTER(T_GData)).contents
        assert end0.size == 1
        libmalloc.ft_gdata_set_area(c.addressof(area) + 512, 512, True, False)
        start1 = c.cast(c.addressof(area) + 512, c.POINTER(T_GData)).contents
        end1 = c.cast(c.addressof(area) + 1024 - 16, c.POINTER(T_GData)).contents
        assert end0.prevsize == 512 - 16
        assert end0.size == 513
        assert end1.prevsize == 512
        assert end1.size == 0

    def test_ft_gdata_set_area3(self, libmalloc):
        area = (c.c_uint8 * 4096)()
        for i, _ in enumerate(area):
            area[i] = 12
        start0 = c.cast(area, c.POINTER(T_GData)).contents
        end0 = c.cast(c.addressof(area) + 512 - 16, c.POINTER(T_GData)).contents
        start1 = c.cast(c.addressof(area) + 512, c.POINTER(T_GData)).contents
        end1 = c.cast(c.addressof(area) + 1024 - 16, c.POINTER(T_GData)).contents
        start2 = c.cast(c.addressof(area) + 1024, c.POINTER(T_GData)).contents
        end2 = c.cast(c.addressof(area) + 1024 + 512 - 16, c.POINTER(T_GData)).contents

        libmalloc.ft_gdata_set_area(c.addressof(area) + 1024, 512, False, False)
        libmalloc.ft_gdata_set_area(c.addressof(area), 512, False, False)
        start2.size = 496 | 0b010
        libmalloc.ft_gdata_set_area(c.addressof(area) + 512, 512, False, True)
        assert start1.size == 512
        assert start2.size == 496 | 0b010

    def test_ft_gdata_set_area4(self, libmalloc):
        area = (c.c_uint8 * 4096)()
        for i, _ in enumerate(area):
            area[i] = 12
        start0 = c.cast(area, c.POINTER(T_GData)).contents
        end0 = c.cast(c.addressof(area) + 512 - 16, c.POINTER(T_GData)).contents
        start1 = c.cast(c.addressof(area) + 512, c.POINTER(T_GData)).contents
        end1 = c.cast(c.addressof(area) + 1024 - 16, c.POINTER(T_GData)).contents
        start2 = c.cast(c.addressof(area) + 1024, c.POINTER(T_GData)).contents
        end2 = c.cast(c.addressof(area) + 1024 + 512 - 16, c.POINTER(T_GData)).contents

        libmalloc.ft_gdata_set_area(c.addressof(area) + 1024, 512, False, False)
        libmalloc.ft_gdata_set_area(c.addressof(area), 512, False, False)
        libmalloc.ft_gdata_set_area(c.addressof(area) + 512, 512, True, True)
        assert start0.prevsize == 0
        assert start0.size == 3 * 512 - 16
        assert end2.prevsize == 3 * 512 - 16
        assert end2.size == 0

    def test_ft_gdata_set_area5(self, libmalloc):
        area = (c.c_uint8 * 4096)()
        for i, _ in enumerate(area):
            area[i] = 12
        start0 = c.cast(area, c.POINTER(T_GData)).contents
        end0 = c.cast(c.addressof(area) + 512 - 16, c.POINTER(T_GData)).contents
        start1 = c.cast(c.addressof(area) + 512, c.POINTER(T_GData)).contents
        end1 = c.cast(c.addressof(area) + 1024 - 16, c.POINTER(T_GData)).contents
        start2 = c.cast(c.addressof(area) + 1024, c.POINTER(T_GData)).contents
        end2 = c.cast(c.addressof(area) + 1024 + 512 - 16, c.POINTER(T_GData)).contents

        libmalloc.ft_gdata_set_area(c.addressof(area) + 1024, 512, False, False)
        libmalloc.ft_gdata_set_area(c.addressof(area), 512, False, False)
        start2.size = 496 | 0b010
        end0.size = 1
        libmalloc.ft_gdata_set_area(c.addressof(area) + 512, 512, True, True)
        assert start0.prevsize == 0
        assert start0.size == 512 - 16
        assert end2.prevsize == 512 - 16
        assert end2.size == 0
