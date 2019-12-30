#include <stdio.h>
#include <stdlib.h>

#include "b_arbre.h"

b_arbre_t* b_arbre_create(){
	b_arbre_t* b;
	b = (b_arbre_t*)malloc(sizeof(b_arbre_t));
	b->NbEle = 0;
	b->cle = NULL;
	b->feuille = 1;
	b->racine = 1;
	b->parent = NULL;
	b->enfant = calloc(b->NbEle+1,sizeof(b_arbre_t*));
	return b;
}


int b_arbre_recherche(b_arbre_t *arb, int x){
	int i;
	for (i = 0; i < arb->NbEle;i++){
		if (x == arb->cle[i]){
			return 1;
		}
		if (x < arb->cle[i]){
			if(arb->leaf == 0)
				return b_arbre_recherche(arb->enfant[i],x);
			else
				return 0;
		}
	}
	if(arb->leaf == 0)
		return b_arbre_recherche(arb->enfant[i+1],x);
	else 
		return 0;
}

// return 1 -> insertion success
// return 0 -> insertion failed
int b_arbre_inserer(b_arbre_t * b, int x){
	int milieu;
	if(b == NULL)
		return NULL;
	if(b == b_arbre_create()){
		b->NbEle = 1;
		b->cle[0] = x;
		return b;
	}
	else if(b->racine == 1){
			if(b->NbEle <= m-1){
				b->cle[NbEle] = x
			}
			else{
				if(m%2 == 0)
					milieu = b->cle[m/2];
				else
					milieu = b->cle[m/2+1];
				b = b_arbre_create(),
				b = b_arbre_create(b,milieu);
				b -> enfant[0] = 
			}
	     }
}












