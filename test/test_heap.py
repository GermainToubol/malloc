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

@pytest.fixture
def libmalloc(request):
    lib = c.cdll.LoadLibrary(f'{request.config.rootdir}/libft_malloc.so')
    lib.ft_queue_push.argtypes = [c.POINTER(T_Queue), c.POINTER(T_Heap)]
    lib.ft_heap_swap_nodes.argtypes = [
        c.POINTER(T_Queue),
        c.POINTER(T_Heap),
        c.POINTER(T_Heap)
    ]
    lib.ft_queue_pop.argtypes = [c.POINTER(T_Queue)]
    yield(lib)
    dlclose(lib._handle)

class TestHeap:
    def test_ft_heap_insert_init(self, libmalloc):
        queue = T_Queue()
        tab = (T_Heap * 25)()
        tab[0].left = c.addressof(tab[0])
        tab[0].prev = 17
        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[0]))
        assert tab[0].left is None
        assert tab[0].prev is None

    def test_ft_heap_insert_inorder(self, libmalloc):
        queue = T_Queue()
        tab = (T_Heap * 25)()
        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[20]))
        assert queue.head == c.addressof(tab[20])
        assert queue.tail == c.addressof(tab[20])

        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[19]))
        assert queue.head == c.addressof(tab[20])
        assert queue.tail == c.addressof(tab[19])
        assert tab[20].parent is None
        assert tab[20].left == c.addressof(tab[19])
        assert tab[20].right is None
        assert tab[20].prev is None
        assert tab[20].next == c.addressof(tab[19])
        assert tab[19].parent == c.addressof(tab[20])
        assert tab[19].left is None
        assert tab[19].right is None
        assert tab[19].prev == c.addressof(tab[20])
        assert tab[19].next is None

        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[18]))
        assert queue.head == c.addressof(tab[20])
        assert queue.tail == c.addressof(tab[18])
        assert tab[20].parent is None
        assert tab[20].left == c.addressof(tab[19])
        assert tab[20].right == c.addressof(tab[18])
        assert tab[20].prev is None
        assert tab[20].next == c.addressof(tab[19])
        assert tab[19].parent == c.addressof(tab[20])
        assert tab[19].left is None
        assert tab[19].right is None
        assert tab[19].prev == c.addressof(tab[20])
        assert tab[19].next == c.addressof(tab[18])
        assert tab[18].parent == c.addressof(tab[20])
        assert tab[18].left is None
        assert tab[18].right is None
        assert tab[18].prev == c.addressof(tab[19])
        assert tab[18].next is None

        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[17]))
        assert queue.head == c.addressof(tab[20])
        assert queue.tail == c.addressof(tab[17])
        assert tab[20].parent is None
        assert tab[20].left == c.addressof(tab[19])
        assert tab[20].right == c.addressof(tab[18])
        assert tab[20].prev is None
        assert tab[20].next == c.addressof(tab[19])
        assert tab[19].parent == c.addressof(tab[20])
        assert tab[19].left == c.addressof(tab[17])
        assert tab[19].right is None
        assert tab[19].prev == c.addressof(tab[20])
        assert tab[19].next == c.addressof(tab[18])
        assert tab[18].parent == c.addressof(tab[20])
        assert tab[18].left is None
        assert tab[18].right is None
        assert tab[18].prev == c.addressof(tab[19])
        assert tab[18].next == c.addressof(tab[17]);

    def test_swap_nodes(self, libmalloc):
        def setup():
            for i in range(5):
                if i != 0:
                    tab[i].prev = c.addressof(tab[i - 1])
                else:
                    tab[i].prev = 0
                if (i != 5):
                    tab[i].next = c.addressof(tab[i + 1])
                else:
                    tab[i].next = 0
                if (2 * i + 1 < 5):
                    tab[i].left = c.addressof(tab[2 * i + 1])
                    tab[i].right = c.addressof(tab[2 * (i + 1)])
                else:
                    tab[i].left = 0
                    tab[i].right = 0

            queue.head = c.addressof(tab[0])
            queue.tail = c.addressof(tab[4])

        queue = T_Queue()
        tab = (T_Heap *25)()

        setup()
        libmalloc.ft_heap_swap_nodes(c.pointer(queue), c.pointer(tab[0]), c.pointer(tab[1]))
        assert tab[0].next == c.addressof(tab[2])
        assert tab[0].prev == c.addressof(tab[1])
        assert tab[0].left == c.addressof(tab[3])
        assert tab[0].right == c.addressof(tab[4])
        assert tab[1].right == c.addressof(tab[2])
        assert tab[1].left == c.addressof(tab[0])

        assert tab[2].prev == c.addressof(tab[0]);

        assert queue.head == c.addressof(tab[1])


    def test_ft_heap_insert_inreverse(self, libmalloc):
        queue = T_Queue()
        tab = (T_Heap * 25)()

        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[0]))
        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[1]))
        assert queue.head == c.addressof(tab[1])
        assert queue.tail == c.addressof(tab[0])

        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[2]))
        assert queue.head == c.addressof(tab[2])
        assert queue.tail == c.addressof(tab[1])

        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[3]))
        libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[4]))

        order = [4, 3, 1, 0, 2]
        for i, j in zip(order[:-1], order[1:]):
            assert tab[i].next == c.addressof(tab[j])

    def test_ft_heap_pop(self, libmalloc):
        queue = T_Queue()
        tab = (T_Heap * 25)()
        for i in range(len(tab)):
            libmalloc.ft_queue_push(c.pointer(queue), c.pointer(tab[i]))

        for i in range(len(tab)):
            assert queue.head == c.addressof(tab[len(tab) -1 - i])
            libmalloc.ft_queue_pop(c.pointer(queue))
        assert queue.head is None
        assert queue.tail is None
