#include "../../include/structures/b_arbre.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <memory.h>
#include <assert.h>

//Allouer de l'espace pour de nouveaux nœuds
BTreeNode allocate_node()
{  
  BTreeNode node = (BTreeNode) malloc (BTREE_NODE_SIZE);

  return node;
}

void btree_create(BTree tree)
{
  BTreeNode r_node = allocate_node();

  (r_node)->n = 0;
  (r_node)->leaf = 1;

  (tree)->root = r_node;
}


int btree_search(BTreeNode node, int key)
{
  
  int j = 0;


  while(j < node->n && key > node->key[j])
    j++;
    if(j < node->n && key == node->key[j])
    {
      return 1;
    }
    else if(node->leaf)
          {
              return 0;
          }
    else  
      return btree_search(node->child[j], key);
  
} 


//Fractionner le nœud complet du nœud enfant à l'emplacement du nœud du nœud parent
void btree_split_child(BTreeNode node, int location)
{
  BTreeNode newnode = allocate_node();
  BTreeNode childnode = node->child[location];

  int i = 0;

  /* 
   * Initialiser le noeud nouveau du noeud vide 
   * et copier les informations du noeud enfant du noeud enfant 
   * sur le nouveau noeud 
   */
  newnode->leaf = childnode->leaf;
  newnode->n = MIN_T - 1;

  
  for(i = 0;i <= MIN_T - 2;i++)
    newnode->key[i] = childnode->key[i + MIN_T];

  childnode->n = MIN_T - 1;

  
  if(!childnode->leaf)
    for(i = 0;i <= MIN_T - 1;i++)
      newnode->child[i] = childnode->child[i + MIN_T];

  
  for(i = node->n;i > location;i--)
  {
    node->key[i] = node->key[i - 1];
    node->child[i+1] = node->child[i];
  }

  
  node->child[location + 1] = newnode;
  node->key[location] = childnode->key[MIN_T - 1];
  node->n = node->n + 1;

}


void btree_insert_nonfull(BTreeNode node, int key)
{
  int i = node->n - 1;

  if(node->leaf)
  {
    
    while(i >=0 && key < node->key[i])
    {
      node->key[i+1] = node->key[i];
      i--;
    }

    node->key[i+1] = key;
    node->n = node->n + 1;
  }
  else
  {
    
    while(i >=0 && key < node->key[i])
      i--;
    i++;
    if(node->child[i]->n == MAX_T - 1)
    {
      btree_split_child(node, i);
      if(key > node->key[i])
        i++;
    }

    btree_insert_nonfull(node->child[i], key);
  }
}


void btree_insert(BTree tree, int key)
{
  BTreeNode r_node = tree->root;

  if(r_node->n == MAX_T - 1)
  {
    BTreeNode r_node_new = allocate_node();

    r_node_new->leaf = 0;
    r_node_new->n = 0;
    r_node_new->child[0] = r_node;
    tree->root = r_node_new;
    btree_split_child(r_node_new, 0);
    btree_insert_nonfull(r_node_new, key);
  }
  else btree_insert_nonfull(r_node, key);
}

/*
void display_node(BTreeNode *node_first, int n)
{
  int i = 0, j = 0, k = 0,all = 0;
  BTreeNode *node = node_first;

  
  for(i = 0; i < n; i++)
  {
    for(j = 0; j < (*(node + i))->n; j++)
    {
      printf("%d ", (*(node + i))->key[j]);
    }
    all = all + (*(node + i))->n + 1;
    //printf(" %p ", *(node + i));
    printf("  ");
  }
  printf("$$\n");

  if(!(*node)->leaf)
  {
    BTreeNode nodes[all];
    i = 0;
    for(j = 0; j < n; j++)
    {
      for(k = 0; k <= (*(node + j))->n; k++)
      {
        nodes[i] = (*(node + j))->child[k];
        i++;
      }
    }
    display_node(nodes, all);
  }
}



void display_btree(BTree tree)
{
  BTreeNode r_node = tree->root;
  
  display_node(&r_node, 1);
}
*/

/*
 * Renvoie le nœud avec le plus petit mot clé avec nœud comme arbre de nœud racine, 
 * la position du mot clé doit être 0
 */
BTreeNode btree_minimum(BTreeNode node)
{
  BTreeNode newnode = node;

  if(newnode->n < 1)
  {
    printf("this is null tree\n");
    return NULL;
  }

  if(node->leaf)
    return newnode;
  else
    newnode = btree_minimum(node->child[0]);

  return newnode;
}


/*
 * Renvoie le nœud avec le plus grand mot-clé de l'arborescence de nœuds enraciné au nœud, 
 * la position du mot-clé doit être la valeur n-1 du nœud
 */
BTreeNode btree_maximum(BTreeNode node)
{
  BTreeNode newnode = node;

  if(newnode->n < 1)
  {
    printf("this is null tree\n");
    return NULL;
  }

  if(node->leaf)
    return newnode;
  else
    newnode = btree_maximum(node->child[node->n]);

  return newnode;
}

//Afficher la plus petite clé de l'arbre entière
void btree_min(BTree tree)
{
  BTreeNode r_node = tree->root;
  BTreeNode n_node = btree_minimum(r_node);

  printf("the min is %d\n", n_node->key[0]);
}

//Afficher le plus grand mot-clé de l'arbre entière
void btree_max(BTree tree)
{
  BTreeNode r_node = tree->root;
  BTreeNode n_node = btree_maximum(r_node);

  printf("the max is %d\n", n_node->key[n_node->n - 1]);
}

/* 
 * Lorsque le nombre de mots clés du nœud de nœud descendant est T-1,
 * Afin de répondre au processus de descente, 
 * le nombre de mots-clés des nœuds rencontrés est supérieur ou égal à T,
 * Ajuster les mots-clés des trois nœuds: parent, nœud et autre nœud.
 * Lorsque le nœud est à gauche de l'autre, 
 * c'est-à-dire le nœud droit du nœud (le nœud enfant droit du nœud parent), 
 * À T + 1, ajouter un mot-clé dont la valeur est la valeur du mot-clé correspondant au nœud parent.
 * Attribuer la valeur du mot clé correspondant au nœud parent au premier mot clé du nœud enfant droit.
 * Déplacer les mots clés et les nœuds enfants (le cas échéant) du nœud enfant droit vers l'avant
 * Modifier le nœud enfant droit et la valeur n du nœud
 */
void btree_left(BTreeNode parent, BTreeNode node, BTreeNode othernode, int location)
{
  int i = 0;
  node->key[node->n] = parent->key[location];
  parent->key[location] = othernode->key[0];

  for(i = 0; i <= othernode->n - 2; i++)
    othernode->key[i] = othernode->key[i + 1];

  if(!othernode->leaf)
  {
    node->child[node->n + 1] = othernode->child[0];
    for(i = 0; i <= othernode->n - 1; i++)
      othernode->child[i] = othernode->child[i + 1];
    
  }

  node->n = node->n + 1;
  othernode->n = othernode->n - 1;
}

/* 
 * Lorsque le nombre de mots-clés du nœud de nœud descendant est T-1,
 * Afin de répondre au processus de descente, 
 * le nombre de mots-clés des nœuds rencontrés est supérieur ou égal à T,
 * Ajuster les mots-clés des trois nœuds: parent, nœud et autre nœud.
 * Lorsque le nœud est à droite de l'autre, 
 * c'est-à-dire le nœud gauche du nœud (l'enfant gauche du nœud parent),
 * Les mots clés et les nœuds enfants du nœud (le cas échéant) sont reculés d'un,
 * Ajouter un mot-clé en première position, dont la valeur est la valeur du mot-clé correspondant au nœud parent.
 * Attribuer la valeur de mot clé correspondante du nœud parent au dernier mot clé du nœud enfant gauche.
 * Modifier le nœud enfant gauche et la valeur n du nœud
 */
void btree_right(BTreeNode parent, BTreeNode node, BTreeNode othernode, int location)
{
  int i = 0;

  for(i = node->n - 1; i >= 0; i--)
    othernode->key[i+1] = othernode->key[i];

  node->key[0] = parent->key[location];
  parent->key[location] = othernode->key[othernode->n];

  if(!node->leaf)
  {
    node->child[0] = othernode->child[othernode->n + 1];
    for(i = othernode->n; i >= 0; i--)
      othernode->child[i + 1] = othernode->child[i];
    
  }

  node->n = node->n + 1;
  othernode->n = othernode->n - 1;
}

/*
 * Fusionner deux mots clés avec le nœud enfant T-1 dont le nœud parent est parent
 * Connecter les deux nœuds enfants avec la clé correspondant au nœud parent comme valeur intermédiaire
 * Et retourner la position du nœud enfant qui doit être supprimé
 */
int btree_merge_child(BTreeNode parent, int location)
{
  int i;
  BTreeNode lnode = NULL;
  BTreeNode rnode = NULL;

  if(location == parent->n)
    location--;
  
  lnode = parent->child[location];
  rnode = parent->child[location + 1];

  lnode->key[lnode->n] = parent->key[location];
  for(i = 0; i < rnode->n; i++)
  {
    lnode->key[MIN_T + i] = rnode->key[i];
    lnode->n++;
  }

  if(!rnode->leaf)
    for(i = 0; i <= rnode->n; i++)
      lnode->child[MIN_T + i] = rnode->child[i];

  rnode->n= 0;
  lnode->n = MAX_T - 1;

  for(i = location; i < parent->n - 1; i++)
  {
    parent->key[i] = parent->key[i + 1];
    parent->child[i + 1] = parent->child[i + 2];
  }


  parent->n = parent->n - 1;
  rnode = NULL;

  return location;
}

/*
 * Supprimer les mots clés avec l'emplacement du nœud du nœud feuille
 * Déplacer directement les mots clés après la localisation de un
 */
void btree_delete_leaf(BTreeNode node, int location)
{
  int i = 0;

  for(i = location; i < node->n - 1; i++)
    node->key[i] = node->key[i + 1];

  node->n = node->n - 1;
}

/*
 * Supprimer la clé dont la coordonnée est i dans le tableau 
 */
int btree_delete_node_in(BTreeNode r_node, int i)
{

  BTreeNode lnode = r_node->child[i];
  BTreeNode rnode = r_node->child[i + 1];
  int temp = 0;


  if(lnode->n >= MIN_T)
  {
    BTreeNode newnode = btree_maximum(lnode);
    temp = r_node->key[i];
    r_node->key[i] = newnode->key[newnode->n - 1];
    newnode->key[newnode->n - 1] = temp;
  }

  else if(rnode->n >= MIN_T)
  {
    BTreeNode newnode = btree_minimum(rnode);
    temp = r_node->key[i];
    r_node->key[i] = newnode->key[0];
    newnode->key[0] = temp;

    i++;
  }

  else  i = btree_merge_child(r_node, i);

  return i;
}


void btree_delete_node(BTreeNode r_node, int key)
{
  int i = 0;


  while(i < r_node->n && key > r_node->key[i])
    i++;

  if(i < r_node->n && key == r_node->key[i])
    if(r_node->leaf)
      btree_delete_leaf(r_node, i);
    else
    {
      i = btree_delete_node_in(r_node, i);
      
      btree_delete_node(r_node->child[i], key);
    }
  else
  {
    if(r_node->leaf)
      printf("there is no the key %d!!\n", key);
    else
    {
      if(r_node->child[i]->n >= MIN_T){
        btree_delete_node(r_node->child[i], key);}
      else
      {
        if(i > 0 && r_node->child[i - 1]->n >= MIN_T)
        {
          btree_right(r_node, r_node->child[i], r_node->child[i - 1], i);}
        else if(i < r_node->n && r_node->child[i + 1]->n >= MIN_T)
          btree_left(r_node, r_node->child[i], r_node->child[i + 1], i);
        else
          i = btree_merge_child(r_node, i);

        btree_delete_node(r_node->child[i], key);
      }
    }
  }
}

void btree_delete(BTree tree, int key)
{
 BTreeNode r_node = tree->root;
 btree_delete_node(r_node, key);
 if(tree->root->n == 0 && tree->root->leaf == 0)
   tree->root = tree->root->child[0];
}


int btree_size(BTreeNode t){
  int sum=t->n;
  if (!t->leaf){
    for (int i=0;i<=t->n;i++)
      sum+=btree_size(t->child[i]);
  }
  return sum;
}

int btree_capacity(BTreeNode t){
  int sum=MAX_T;
  if (!t->leaf){
    for (int i=0;i<=t->n;i++)
   sum+=btree_capacity(t->child[i]);
  }
  return sum;
}

void btree_destroy(BTree a){
  if( a != NULL ){
    if( a->root != NULL )
      free( a->root );
    free( a );
  }
}

