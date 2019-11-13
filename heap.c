#include <stdio.h>
#include <stdlib.h>

typedef struct Tree
{
  int item;
  struct Tree *left, *right;
} Tree;

Tree *insert_node (Tree * tree, int val);
void show_infix_tree (Tree * tree);
void show_pre_tree (Tree * tree);

Tree *
insert_node (Tree * tree, int val)
{
  Tree *node;

  if (tree == NULL)
    {
      node = (Tree *) malloc (sizeof (Tree));
      node->item = val;
      node->left = node->right = NULL;
      return node;
    }
  if (tree->item > val)
    {
      node = insert_node (tree->left, val);
      tree->left = node;
    }
  else
    {
      node = insert_node (tree->right, val);
      tree->right = node;
    }
  return tree;
}

void
show_infix_tree (Tree * tree)
{
  if (tree != NULL)
    {
      printf ("Item %d\n", tree->item);
      show_infix_tree (tree->left);
      show_infix_tree (tree->right);
    }
  return;
}

void
release_tree (Tree * tree)
{
  if (tree != NULL)
    {
      release_tree (tree->left);
      tree->left = NULL;
      release_tree (tree->right);
      tree->right = NULL;
      free ((void *) tree);
    }
  return;
}

void
show_pre_tree (Tree * tree)
{
  if (tree != NULL)
    {
      show_pre_tree (tree->left);
      tree->left = NULL;
      printf ("Item %d\n", tree->item);
      show_pre_tree (tree->right);
      tree->right = NULL;
    }
  return;
}

int
main ()
{
  int val;
  Tree *heap = NULL;

  do
    {
      scanf ("%d", &val);
      printf ("%d\n", val);
      heap = insert_node (heap, val);
    }
  while (!feof (stdin));
  printf ("Display in-order binary tree\n");
  show_infix_tree (heap);
  printf ("Display pre-order binary tree\n");
  show_pre_tree (heap);
  printf ("Release allocated binary tree\n");
  release_tree (heap);
  return 0;
}
