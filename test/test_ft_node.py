import ctypes as c
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
    lib.ft_tree_insert.restype = c.POINTER(T_Node)
    return lib

class TestTree:
    def test_ft_tree_insert(self, libmalloc):
        root = c.POINTER(T_Node)()
        node = T_Node()
        node.size = 17
        ret = libmalloc.ft_tree_insert(root, c.pointer(node))
        assert c.addressof(ret.contents) == c.addressof(node)
        node2 = T_Node()
        node2.size = 18
        ret = libmalloc.ft_tree_insert(c.pointer(node), c.pointer(node2))
        assert c.addressof(ret.contents) == c.addressof(node)
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
