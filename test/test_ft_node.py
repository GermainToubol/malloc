import ctypes as c
from _ctypes import dlclose
import numpy as np
import pytest

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
    lib = c.cdll.LoadLibrary(f'{request.config.rootdir}/libft_malloc.so')
    lib.ft_tree_insert.argtypes = [c.POINTER(T_Node), c.POINTER(T_Node)]
    lib.ft_tree_insert.restype = c.c_void_p
    lib.ft_tree_delete.argtypes = [c.POINTER(T_Node), c.POINTER(T_Node)]
    lib.ft_tree_delete.restype = c.c_void_p
    lib.ft_tree_search.argtypes = [c.POINTER(T_Node), c.c_uint64]
    lib.ft_node_init.argtypes = [c.POINTER(T_Node), c.c_uint64]
    yield lib
    dlclose(lib._handle)

class TestTree:
    def test_ft_tree_insert(self, libmalloc):
        root = c.POINTER(T_Node)()
        node = T_Node()
        node.size = 17
        ret = libmalloc.ft_tree_insert(root, c.pointer(node))
        assert ret == c.addressof(node)
        node2 = T_Node()
        node2.size = 18
        ret = libmalloc.ft_tree_insert(c.pointer(node), c.pointer(node2))
        assert ret == c.addressof(node)
        assert node.right == c.addressof(node2)
        assert node2.parent == c.addressof(node)

    def test_ft_tree_insert_multiple(self, libmalloc):
        def validate_rb(root):
            if root == 0 or root is None:
                return True, 1
            node = c.cast(root, c.POINTER(T_Node)).contents
            t, left = validate_rb(node.left)
            t2, right = validate_rb(node.right)
            if not t or not t2 or left != right:
                return False, -1
            if node.color == 0:
                return True, left + 1
            return True, left

        root = 0
        ntab = (T_Node * 55)()
        for i in range(len(ntab)):
            node = ntab[i]
            node.size = i + 1
            node.parent = 0
            node.left = 0
            node.right = 0
            root = libmalloc.ft_tree_insert(c.cast(root, c.POINTER(T_Node)), c.pointer(node));
            res, _ = validate_rb(root)
            assert res

        root = 0
        for i in range(len(ntab)):
            node = ntab[i]
            node.size = 500 - i
            node.parent = 0
            node.left = 0
            node.right = 0
            node.color = 1
            #libmalloc.ft_node_init(c.pointer(node), 500 - i)
            root = libmalloc.ft_tree_insert(c.cast(root, c.POINTER(T_Node)), c.pointer(node));
            res, _ = validate_rb(root)
            assert res

        root = 0
        arr = np.arange(len(ntab))
        np.random.shuffle(arr)
        for i in range(len(ntab)):
            node = ntab[i]
            node.size = arr[i]
            node.parent = 0
            node.left = 0
            node.right = 0
            root = libmalloc.ft_tree_insert(c.cast(root, c.POINTER(T_Node)), c.pointer(node));
            res, _ = validate_rb(root)
            assert res
            assert c.cast(root, c.POINTER(T_Node)).contents.parent is None

    def test_ft_tree_delete(self, libmalloc):
        def validate_rb(root):
            if root == 0 or root is None:
                return True, 1
            node = c.cast(root, c.POINTER(T_Node)).contents
            t, left = validate_rb(node.left)
            t2, right = validate_rb(node.right)
            if not t or not t2 or left != right:
                return False, -1
            if node.color == 0:
                return True, left + 1
            return True, left

        root = 0
        ntab = (T_Node * 55)()
        for i in range(len(ntab)):
            node = ntab[i]
            node.size = i + 1
            node.parent = 0
            node.left = 0
            node.right = 0
            root = libmalloc.ft_tree_insert(c.cast(root, c.POINTER(T_Node)), c.pointer(node));

        for i in range(len(ntab)):
            node = ntab[i]
            root = libmalloc.ft_tree_delete(c.cast(root, c.POINTER(T_Node)), c.pointer(node));
            res, _ = validate_rb(root)
            assert res
        assert root is None

    def test_ft_tree_delete2(self, libmalloc):
        def validate_rb(root):
            if root == 0 or root is None:
                return True, 1
            node = c.cast(root, c.POINTER(T_Node)).contents
            t, left = validate_rb(node.left)
            t2, right = validate_rb(node.right)
            if not t or not t2 or left != right:
                return False, -1
            if node.color == 0:
                return True, left + 1
            return True, left

        root = 0
        ntab = (T_Node * 55)()
        arr = np.arange(len(ntab))
        np.random.shuffle(arr)
        for i in range(len(ntab)):
            node = ntab[i]
            node.size = arr[i]
            node.parent = 0
            node.left = 0
            node.right = 0
            root = libmalloc.ft_tree_insert(c.cast(root, c.POINTER(T_Node)), c.pointer(node));

        for i in range(len(ntab)):
            node = ntab[i]
            root = libmalloc.ft_tree_delete(c.cast(root, c.POINTER(T_Node)), c.pointer(node));
        assert root is None

    def test_ft_tree_search(self, libmalloc):
        root = 0
        ntab = (T_Node * 55)()
        for i in range(len(ntab)):
            node = ntab[i]
            node.size = (i + 1) * 256
            node.parent = 0
            node.left = 0
            node.right = 0
            root = libmalloc.ft_tree_insert(c.cast(root, c.POINTER(T_Node)), c.pointer(node));
        node = libmalloc.ft_tree_search(c.cast(root, c.POINTER(T_Node)), 200)
        assert node == c.addressof(ntab[0])
        node = libmalloc.ft_tree_search(c.cast(root, c.POINTER(T_Node)), 18 * 256)
        assert node == c.addressof(ntab[17])
        node = libmalloc.ft_tree_search(c.cast(root, c.POINTER(T_Node)), 51 * 256 - 7)
        assert node == c.addressof(ntab[50])
        node = libmalloc.ft_tree_search(c.cast(root, c.POINTER(T_Node)), 25600)
        assert node == 0
