#ifndef __b_arbre_H
#define __b_arbre_H

#define FALSE 0
#define TRUE 1

  
#define MIN_T 3 
#define MAX_T (MIN_T * 2)
#include <stddef.h>

typedef struct BTreeNodedata BTreeNodedata;
typedef struct BTreeNodedata *BTreeNode;
typedef struct BTreedata BTreedata;
typedef struct BTreedata *BTree;

/*
 * structure du noeud de b_arbre
 */
struct BTreeNodedata
{
 int n; //nombre des clés
 int leaf;  //bool 1 -- feuille; 0 sinon
 int key[MAX_T - 1];  //clés
 BTreeNode child[MAX_T];  //enfant
};

/*
 * structure du noeud de b_arbre
 */
struct BTreedata
{
 BTreeNode  root; //la racine du b_arbre
};

#define BTREE_NODE_SIZE sizeof(BTreeNodedata)
#define BTREE_SIZE sizeof(BTreedata)

BTreeNode allocate_node(); 

void btree_create(BTree tree);  

int btree_search(BTreeNode node, int key); 

void btree_split_child(BTreeNode node, int location);

void btree_insert_nonfull(BTreeNode node, int key); 

void btree_insert(BTree tree, int key); 

void display_node(BTreeNode *node_first, int n); 

void display_btree(BTree tree);

BTreeNode btree_minimum(BTreeNode node); 

BTreeNode btree_maximum(BTreeNode node);  

void btree_min(BTree tree); 

void btree_max(BTree tree); 

void btree_left(BTreeNode parent, BTreeNode node, BTreeNode othernode, int location); 

void btree_right(BTreeNode parent, BTreeNode node, BTreeNode othernode, int location); 

int btree_merge_child(BTreeNode parent, int location); 

void btree_delete_leaf(BTreeNode node, int location);

int btree_delete_node_in(BTreeNode r_node, int i);  

void btree_delete_node(BTreeNode r_node, int key); 

void btree_delete(BTree tree, int key); 

int btree_size(BTreeNode t);

int btree_capacity(BTreeNode t);

void btree_destroy(BTree a);

#endif
 
 
