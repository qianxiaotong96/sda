#include "../../include/structures/avl.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX(a, b)    ( (a) > (b) ? (a) : (b) )

avl_arbre_t* avl_noeud_create(int cle){
  avl_arbre_t* p;

  if((p = (avl_arbre_t*)malloc(sizeof(avl_arbre_t))) == NULL){
    return NULL;
  }

  p->cle = cle;
  p->height = 0;
  p->gauche = NULL;
  p->droite = NULL;

  return p;
}

avl_arbre_t* avl_arbre_recherche(avl_arbre_t* avl, int cle){
  if(avl == NULL || avl->cle == cle)
    return avl;
  
  if(cle < avl->cle)
    return avl_arbre_recherche(avl->gauche,cle);
  else
    return avl_arbre_recherche(avl->droite,cle);
}

avl_arbre_t* gauche_gauche_rotation(avl_arbre_t* avl1){
  avl_arbre_t* avl2;

  avl2 = avl1 -> gauche;
  avl1 -> gauche = avl2 -> droite;
  avl2 -> droite = avl1;

  avl1 -> height = MAX(avl1->gauche->height,avl1->droite->height) +1;
  avl2 -> height = MAX(avl2->gauche->height,avl1->height) + 1;

  return avl2;
}

avl_arbre_t* droite_droite_rotation(avl_arbre_t* avl1){
  avl_arbre_t* avl2;

  avl2 = avl1 -> droite;
  avl1 -> droite = avl2 -> gauche;
  avl2 -> gauche = avl1;

  avl1 -> height = MAX(avl1->gauche->height,avl1->droite->height) + 1;
  avl2 -> height = MAX(avl2->droite->height, avl1->height) + 1;

  return avl2; 
}

avl_arbre_t* droite_gauche_rotation(avl_arbre_t* avl1){
  avl1 -> droite = gauche_gauche_rotation(avl1->droite);
  return droite_droite_rotation(avl1);
}

avl_arbre_t* gauche_droite_rotation(avl_arbre_t* avl1){
  avl1 -> gauche = droite_droite_rotation(avl1->gauche);

  return gauche_gauche_rotation(avl1);
}

avl_arbre_t* avl_arbre_inserer(avl_arbre_t* avl,int cle){
  if(avl == NULL){
    avl = avl_noeud_create(cle);
    if(avl == NULL){
      printf("erreur avec d'insertion\n");
      return NULL;
    }
  }
  else if(cle < avl->cle){
        avl->gauche = avl_arbre_inserer(avl->gauche,cle);
        if((avl->gauche->height - avl->droite->height) == 2){
          if(cle < avl->gauche->cle)
            avl = gauche_gauche_rotation(avl);
          else 
            avl = gauche_droite_rotation(avl);
        }
  }
  else if(cle > avl->cle){
        avl -> droite = avl_arbre_inserer(avl->droite,cle);
        if((avl->droite->height - avl->gauche->height) == 2){
          if(cle > avl->droite->cle)
            avl = droite_droite_rotation(avl);
          else
            avl = droite_gauche_rotation(avl);
        }
  }
  else{
    printf("cela existe deja\n");
  }

  avl->height = MAX(avl->gauche->height,avl->droite->height) + 1;

  return avl;
}

avl_arbre_t* avl_arbre_maximum(avl_arbre_t* avl){
	if(avl == NULL)
		return NULL;
	while(avl->droite != NULL)
		avl = avl->droite;
	return avl;
}

avl_arbre_t* avl_noeud_supprimer(avl_arbre_t* avl1, avl_arbre_t* avl2){
	if(avl1 == NULL || avl2 == NULL)
		return NULL;
	if(avl2->cle < avl1->cle){
		avl1 -> gauche = avl_noeud_supprimer(avl1 -> gauche, avl2);
		if((avl1->droite->height - avl1->gauche->height) == 2){
			avl_arbre_t* r = avl1->droite;
			if (r->gauche->height > r->droite->height)
				avl1 = droite_gauche_rotation(avl1);
			else
				avl1 = droite_droite_rotation(avl1);
		}
	}
	else if(avl2->cle > avl1->cle){
		avl1->droite = avl_noeud_supprimer(avl1->droite,avl2);
		if((avl1->gauche->height - avl1->droite->height) == 2){
			avl_arbre_t* l = avl1->gauche;
			if(l->droite->height > l->gauche->height)
				avl1 = gauche_droite_rotation(avl1);
			else
				avl1 = gauche_gauche_rotation(avl1);
		}
	}
	else{
		if((avl1->gauche && avl1->droite)){
			if(avl1->gauche->height > avl1->droite->height){
				avl_arbre_t* max = avl_arbre_maximum(avl1->gauche);
				avl1->cle = max->cle;
				avl1->gauche = avl_noeud_supprimer(avl1->gauche,max);
			}
			else{
				avl_arbre_t* min = avl_arbre_maximum(avl1->droite);
				avl1->cle = min->cle;
				avl1->droite = avl_noeud_supprimer(avl1->droite,min);
			}
		}
		else{
			avl_arbre_t* tmp = avl1;
			avl1 = avl1->gauche ? avl1->gauche : avl1->droite;
			free(tmp);
		}
	}

	return avl1;

}

avl_arbre_t* avl_arbre_supprimer(avl_arbre_t* avl1, int cle){
	avl_arbre_t* avl2;

	if((avl2 = avl_arbre_recherche(avl1,cle)) != NULL)
		 avl1 = avl_noeud_supprimer(avl1,avl2);
	return avl1;
}

void avl_arbre_destroy(avl_arbre_t* avl){
	if(avl == NULL)
		return;
	if(avl->gauche != NULL)
		avl_arbre_destroy(avl->gauche);
	if(avl->droite != NULL)
		avl_arbre_destroy(avl->droite);

	free(avl);
}

int avl_arbre_size(avl_arbre_t* avl){
  if(avl == NULL)
    return 0;
  else 
    return 1+avl_arbre_size(avl->gauche)+avl_arbre_size(avl->droite);
  
}

int avl_arbre_capacity(avl_arbre_t* avl){
  return avl_arbre_size(avl);
}

