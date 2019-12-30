#ifndef __avl_arbre_H
#define __avl_arbre_H

#define FALSE 0
#define TRUE 1
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )

#include <stddef.h>



typedef struct avl_arbre_s
{
  int cle; 
  int height; // la hauteur du AVL
  struct avl_arbre_s *gauche; // fils gauche
  struct avl_arbre_s *droite; // fils droite
}avl_arbre_t;

avl_arbre_t* avl_noeud_create(int cle);

avl_arbre_t* avl_arbre_recherche(avl_arbre_t* avl, int cle);

avl_arbre_t* gauche_gauche_rotation(avl_arbre_t* avl1);

avl_arbre_t* droite_droite_rotation(avl_arbre_t* avl1);

avl_arbre_t* droite_gauche_rotation(avl_arbre_t* avl1);

avl_arbre_t* gauche_droite_rotation(avl_arbre_t* avl1);

avl_arbre_t* avl_arbre_inserer(avl_arbre_t* avl,int cle);

avl_arbre_t* avl_arbre_maximum(avl_arbre_t* avl);

avl_arbre_t* avl_noeud_supprimer(avl_arbre_t* avl1, avl_arbre_t* avl2);

avl_arbre_t* avl_arbre_supprimer(avl_arbre_t* avl1, int cle);

void avl_arbre_destroy(avl_arbre_t* avl);

int avl_arbre_size(avl_arbre_t* avl);

int avl_arbre_capacity(avl_arbre_t* avl);




/**
   Fonction d'initialisation d'un tableau dynamique.
   Complexité en temps/espace, pire et meilleur cas : O(1)  
   @return Un pointeur sur un tableau dynamique nouvellement alloué.
*/

/**
   Fonction de libération de la mémoire occupée par un tableau dynamique.
   Complexité en temps/espace, pire et meilleur cas : O(1)  
   @param a est un pointeur vers l'espace mémoire que la fonction va libérer.
*/
//void tas_binaire_destroy(tas_binaire_t * a);

/**
   Ajoute une valeur dans le tableau.
   Complexité en temps/espace, pire cas : O(size)
   Complexité en temps/espace, meilleur cas : O(1)
   Complexité amortie : O(1)
   @param a est le tableau  auquel on souhaite ajouter une valeur.
   @param x est la valeur que l'on souhaite ajouter.
   @returns VRAI si le tableau a été agrandit, FAUX sinon
*/
//char tas_binaire_append(tas_binaire_t * a, int x);

/**
   Supprime la dernière valeur du tableau.
   Complexité en temps, pire cas : O(size)
   Complexité en temps, meilleur cas : O(1)
   Complexité amortie : O(1)
   @param a est le tableau  auquel on souhaite ajouter une valeur.
   @returns VRAI si le tableau a été réduit, FAUX sinon
*/
//char tas_binaire_pop_back(tas_binaire_t * a);

/**
   Renvoie la valeur située à la position donnée par l'utilisateur.
   Complexité en temps/espace, pire cas : O(1)
   @param a est un pointeur vers un tableau.
   @param pos est la l'indice de la case on l'utilisateur veut connaître la valeur.
   @returns la valeur située à la position donnée par l'utilisateur.
 */
//int tas_binaire_get(tas_binaire_t * a, int pos);


/**
   Renvoie le nombre d'éléments stockés dans le tableau.
   Complexité en temps/espace, pire cas : O(1)
   @param a est un pointeur vers un tableau.
   @returns le nombre d'éléments stockés dans le tableau.
 */
//size_t tas_binaire_size(tas_binaire_t * a);

/**
   Renvoie la capacité de stockage du tableau.
   Complexité en temps/espace, pire cas : O(1)
   @param a est un pointeur vers un tableau.
   @returns la capacité de stockage du tableau.
 */
//size_t tas_binaire_capacity(tas_binaire_t * a);

/**
   Cette fonction détermine la règle selon laquelle un espace mémoire plus grand sera alloué ou non.
   @param a est un pointeur vers un tableau.
   @returns VRAI si le tableau doit être agrandi, FAUX sinon.
*/
//char tas_binaire_do_we_need_to_enlarge_capacity(tas_binaire_t * a);

/**
   Cette fonction augmente la capacité du tableau.
   @param a est un pointeur vers un tableau.
*/
//void tas_binaire_enlarge_capacity(tas_binaire_t * a);

/**
   Cette fonction détermine la règle selon laquelle un espace mémoire plus petit sera alloué ou non.
   @param a est un pointeur vers un tableau.
   @returns VRAI si le tableau doit être réduit, FAUX sinon.
*/
//char tas_binaire_do_we_need_to_reduce_capacity(tas_binaire_t * a);

/**
   Cette fonction réduit la capacité du tableau.
   @param a est un pointeur vers un tableau.
*/
//  void tas_binaire_reduce_capacity(tas_binaire_t * a);
 

#endif
 
 
