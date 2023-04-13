#include "ft_tree.h"

#include <stddef.h>

int main(void) {
    char    buffer[1024];
    t_node *node;
    t_node *root;

    node = (t_node *)buffer;
    root = NULL;
    ft_node_init(node, 256);
    root = ft_tree_insert(root, node);
    ft_node_init(node + 1, 256);
    root = ft_tree_insert(root, node + 1);
}
