#include <iostream>
#include <algorithm>

template <typename T>
class AvlTree
{

protected:

  class Node
  {
  public:
    T value;

    Node *left = nullptr;
    Node *right = nullptr;

    int height = 0;
    int bf = 0; // balance factor, how balanced is this node.

    Node(T&& value) :
      value(std::forward<T>(value))
    {
    }
  };

public:

  AvlTree() = default;

  AvlTree(const AvlTree& other) = delete;

  AvlTree(AvlTree&& other) = default;

  AvlTree& operator=(const AvlTree& other) = delete;

  AvlTree& operator=(AvlTree&& other) = default;

  ~AvlTree()
  {
    ClearTree(root);
  }

#ifdef DEBUG
  void PrintTree()
  {
    PrintTree(root);
  }

  void PrintTree(Node *node)
  {
    if (node == nullptr)
      return;

    if (node->left != nullptr)
    {
      PrintTree(node->left);
      std::cout << node->value << " ";
      PrintTree(node->right);
    }
    else
    {
      std::cout << node->value << " ";
      PrintTree(node->right);
    }
  }
#endif

  bool Insert(T&& value)
  {
    root = Insert(std::forward<T>(value), root);
    return root != nullptr;
  }

protected:

  void Update(Node *node)
  {
    int left_node_height = (node->left == nullptr) ? -1 : node->left->height;
    int right_node_height = (node->right == nullptr) ? -1 : node->right->height;

    node->height = 1 + std::max(left_node_height, right_node_height);

    node->bf = right_node_height - left_node_height;
  }

  Node *Insert(T&& value, Node *node)
  {
    if (node == nullptr)
    {
      return new Node(std::forward<T>(value));
    }

    if (value < node->value)
    {
      node->left = Insert(std::forward<T>(value), node->left);
    }
    else if (value > node->value)
    {
      node->right = Insert(std::forward<T>(value), node->right);
    }

    Update(node);

    return Balance(node);
  }

  Node *Balance(Node *node)
  {
    if (node == nullptr)
      return nullptr;

    if (node->bf == -2)
    {
      if (node->left->bf < 0)
      {
        return LeftLeftBalance(node);
      }
      else
      {
        return LeftRightBalance(node);
      }
    }
    else if (node->bf == 2)
    {
      if (node->right->bf > 0)
      {
        return RightRightBalance(node);
      }
      else
      {
        return RightLeftBalance(node);
      }
    }
    else
    {
      return node; // already balanced
    }
  }

  Node *RightRightBalance(Node *node)
  {
    return LeftRotate(node);
  }

  Node *RightLeftBalance(Node *node)
  {
    node->right = RightRotate(node->right);
    return RightRightBalance(node);
  }

  Node *LeftLeftBalance(Node *node)
  {
    return RightRotate(node);
  }

  Node *LeftRightBalance(Node *node)
  {
    node->left = LeftRotate(node->left);
    return LeftLeftBalance(node);
  }

  Node *RightRotate(Node *node)
  {
    if (node == nullptr)
      return nullptr;

    Node *new_parent = node->left;
    node->left = new_parent->right;
    new_parent->right = node;
    Update(node);
    Update(new_parent);
    return new_parent;
  }

  Node *LeftRotate(Node *node)
  {
    if (node == nullptr)
      return nullptr;

    Node *new_parent = node->right;
    node->right = new_parent->left;
    new_parent->left = node;
    Update(node);
    Update(new_parent);
    return new_parent;
  }

  void ClearTree(Node *&node)
  {
    if (node == nullptr)
      return;

    ClearTree(node->left);
    ClearTree(node->right);

    delete node;
    node = nullptr;
  }

protected:

  Node *root = nullptr;
};
