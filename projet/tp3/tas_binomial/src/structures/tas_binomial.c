#include "../../include/structures/tas_binomial.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 1000010

tas_binomial_t* creer_tas(int x){
	tas_binomial_t* t;
	t = (tas_binomial_t*)malloc(sizeof(tas_binomial_t));
	
	if(t == NULL){
		printf("malloc refuse");
		return NULL;
	}
	t->cle = x;
	t->degre = 0;
	t->pere = NULL;
	t->enfant = NULL;
	t->frere = NULL;
	

	return t;
}

tas_binomial_t* binomial_merge(tas_binomial_t* t1,tas_binomial_t* t2){
	tas_binomial_t* tete = NULL;
	tas_binomial_t** pos = &tete;
	while (t1 && t2){
		if(t1 -> degre < t2 -> degre)
		{
			*pos = t1;
			t1 = t1 -> frere;
		}
		else
		{
			*pos = t2;
			t2 = t2 -> frere;
		}
		pos = &(*pos) -> frere;
	}
	if(t1)
		*pos = t1;
	else 
		*pos = t2;
	return tete;
}

void binomial_link(tas_binomial_t* y,tas_binomial_t* z){
	y -> pere = z;
	y -> frere  = z -> enfant;
	z -> enfant = y;
	z -> degre++;
}


tas_binomial_t* fusionner(tas_binomial_t* t1,tas_binomial_t* t2){
	tas_binomial_t *tas;
	tas_binomial_t *prev_x,*x,*next_x;

	tas = binomial_merge(t1,t2);
	if(tas == NULL){
		return NULL;
	}

	prev_x = NULL;
	x = tas;
	next_x = x -> frere;

	while(next_x != NULL){
		if ((x->degre != next_x -> degre) || ((next_x->frere != NULL)&&(next_x ->degre == next_x -> frere ->degre))){
			// case 1 ou case 2
			prev_x = x;
			x = next_x;
		}
		else if(x->cle <= next_x ->cle){
			// case 3
			x->frere = next_x-> frere;
			binomial_link(next_x,x);
		}
		else{
			// case 4
			if(prev_x == NULL){
				tas = next_x;
			}
			else{
				prev_x -> frere = next_x;
			}
			binomial_link(x,next_x);
			x = next_x;
		}
		next_x = x->frere;
	}
	return tas;
}


tas_binomial_t* insertion(tas_binomial_t* t, int val){
	tas_binomial_t* noeud;
	noeud = creer_tas(val);
	if(noeud == NULL){
		return t;
	}
	
	return fusionner(t,noeud);
}

tas_binomial_t* chercher_element(tas_binomial_t* t, int x){
	tas_binomial_t* enfant;
	tas_binomial_t* pere = t;

	pere = t;
	while(pere != NULL){
		if(pere->cle == x)
			return pere;
		else{
			if((enfant = chercher_element(pere->enfant,x)) != NULL)
				return enfant;
			pere = pere->frere;
		} 
	}
	return NULL;
}

tas_binomial_t* inverse(tas_binomial_t* t){
	tas_binomial_t* next;
	tas_binomial_t* tail = NULL;

	if(!t)
		return t;
	t->pere = NULL;
	while(t -> frere)
	{
		next = t -> frere;
		t->frere = tail;
		tail = t;
		t = next;
		t->pere = NULL;
	}
	t -> frere = tail;
	return t;
}

tas_binomial_t* supprimer(tas_binomial_t* t, int val){
	tas_binomial_t* noeud;
	tas_binomial_t	*pere,*prev,*pos;

	if(t == NULL){
		return t;
	}

	if((noeud = chercher_element(t,val)) == NULL )
		return t;

	pere = noeud -> pere;
	while (pere != NULL){
		int p;
		p = noeud-> cle,
		noeud -> cle = pere -> cle;
		pere -> cle = p;
	}

	prev = NULL;
	pos = t;
	while(pos != noeud){
		prev = pos;
		pos = pos ->frere;
	}

	if(prev){
		prev->frere = noeud->frere;
	}
	else{
		t = noeud -> frere;
	}

	t = fusionner(t,inverse(noeud->enfant));

	free(noeud);
	return t;
}


tas_binomial_t* extraire_min(tas_binomial_t* t){	
	tas_binomial_t* x;
	if(t == NULL)
		return t;
	else{ 
		x = t;
		int min = x->cle;
		while(x->frere!= NULL){
			x = x-> frere;
			if(x->cle < min)
				min = x->cle;
		}
		t = supprimer(t,min);
		return t;
	}
}
/*
void _afficher_tas_binomial(tas_binomial_t *node, tas_binomial_t *prev, int direction){
	while(node != NULL){
		if (direction == 1)
			printf("\t%2d(%d) is %2d's child\n", node->cle,node->degre,prev->cle);
		else 
			printf("\t%2d(%d) is %2d's brother\n",node->cle,node->degre,prev->cle);

		if(node->enfant != NULL)
			_afficher_tas_binomial(node->enfant,node,1);

		prev = node;
		node = node -> frere;
		direction = 2;
	} 
}

void afficher_tas_binomial(tas_binomial_t *t){
	if(t ==NULL)
		return ;

	tas_binomial_t *p = t;
	printf("== tas binomial（ ");
	while(p != NULL){
		printf("B%d ", p->degre);
		p = p->frere;
	}
	printf(") information: \n");

	int i=0;
	while(t != NULL){
		i++;
		printf("%d. tas binomial B%d: \n", i, t->degre);
		printf("\t%2d(%d) is root\n",t->cle,t->degre);

		_afficher_tas_binomial(t->enfant, t, 1);
		t = t->frere;
	}
	printf("\n");
}*/

size_t tas_binomial_size(tas_binomial_t * t){
  	tas_binomial_t* x;
	if(t == NULL)
		return -1;
	else{ 
		x = t;
		int size=0;
		while(x->frere!= NULL){
			x = x-> frere;
       			size = (size + (2^(x->degre)));
		}
		return size;
	}
}

size_t tas_binomial_capacity(tas_binomial_t * a){
  return tas_binomial_size(a);
}

char tas_binomial_do_we_need_to_enlarge_capacity(tas_binomial_t * a){
  return FALSE;
}

void tas_binomial_enlarge_capacity(tas_binomial_t * a){

}

char tas_binomial_do_we_need_to_reduce_capacity(tas_binomial_t * a){
  return FALSE;
  //return ( a->size <= a->capacity - 2*sqrt( a->capacity ) && a->size >4 )? TRUE: FALSE;
}

void tas_binomial_reduce_capacity(tas_binomial_t * a){

}

void tas_binomial_destroy(tas_binomial_t * a){
  if( a != NULL ){
    free( a );
  }
}


/*
int main(){
	
	tas_binomial_t *t;
	int taille;
	int nb;
	printf("Entrez la taille du tas:\n");
	scanf("%d",&taille);
	printf("Entrez un nombre:\n");
	scanf("%d",&nb);
	t = creer_tas(nb);
	for(int i=1;i<taille;i++){
		printf("Entrez un nombre:\n");
		scanf("%d",&nb);
		t = insertion(t,nb);
	}
	afficher_tas_binomial(t);
	printf("\n");
	printf("maintenant on fait une extraire_min:\n");
	t = extraire_min(t);
	afficher_tas_binomial(t);
	t = extraire_min(t);
	afficher_tas_binomial(t);
	
	return 0;
}*/















