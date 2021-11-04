#include "AvlTree.h"

int main()
{
  AvlTree<int> avl_tree;
  avl_tree.Insert(10);
  avl_tree.Insert(5);
  avl_tree.Insert(15);
  avl_tree.Insert(1);
  avl_tree.Insert(30);
  avl_tree.Insert(3);
  avl_tree.Insert(20);
  avl_tree.Insert(0);

  avl_tree.PrintTree();
  return 0;
}