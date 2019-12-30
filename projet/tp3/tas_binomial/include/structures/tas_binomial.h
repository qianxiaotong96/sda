#ifndef __tas_binomial_H
#define __tas_binomial_H

#define FALSE 0
#define TRUE 1

#include <stddef.h>

typedef struct tas_binomial_s{
	int cle;
	int degre;
	struct tas_binomial_s *enfant;
        struct tas_binomial_s *pere;
	struct tas_binomial_s *frere;
}tas_binomial_t;

tas_binomial_t* creer_tas(int x);

tas_binomial_t* binomial_merge(tas_binomial_t* t1,tas_binomial_t* t2);

void binomial_link(tas_binomial_t* y,tas_binomial_t* z);

tas_binomial_t* fusionner(tas_binomial_t* t1,tas_binomial_t* t2);

tas_binomial_t* insertion(tas_binomial_t* t, int val);

tas_binomial_t* chercher_element(tas_binomial_t* t, int x);

tas_binomial_t* inverse(tas_binomial_t* t);

tas_binomial_t* supprimer(tas_binomial_t* t, int val);

tas_binomial_t* extraire_min(tas_binomial_t* t);

void _afficher_tas_binomial(tas_binomial_t *node, tas_binomial_t *prev, int direction);

void afficher_tas_binomial(tas_binomial_t *t);

size_t tas_binomial_size(tas_binomial_t * t);

size_t tas_binomial_capacity(tas_binomial_t * a);


char tas_binomial_do_we_need_to_enlarge_capacity(tas_binomial_t * a);

void tas_binomial_enlarge_capacity(tas_binomial_t * a);

char tas_binomial_do_we_need_to_reduce_capacity(tas_binomial_t * a);

void tas_binomial_reduce_capacity(tas_binomial_t * a);

void tas_binomial_destroy(tas_binomial_t * a);

#endif
 
 
