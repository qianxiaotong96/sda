#include<stdio.h>
#include <time.h>
#include<stdlib.h>
#include "../include/structures/b_arbre.h"
#include "analysis/analyzer.h"


int main(int argc, char ** argv){
  int i;
  // Tableau dynamique.
  BTree b;
  btree_create(b);
  // Analyse du temps pris par les opérations.
  analyzer_t * time_analysis = analyzer_create();
  // Analyse du nombre de copies faites par les opérations.
  analyzer_t * copy_analysis = analyzer_create();
  // Analyse de l'espace mémoire inutilisé.
  analyzer_t * memory_analysis = analyzer_create(); 
  // Mesure de la durée d'une opération.
  struct timespec before, after;
  clockid_t clk_id = CLOCK_REALTIME;
  // utilisé comme booléen pour savoir si une allocation a été effectuée.
  char memory_allocation; 
  srand(0);

  float p;
  p = 0.5; // p=1, inserer propre
           // p=0.5 la moitie inserer et la moitie supprimer

  for(i = 0; i < 1000000 ; i++){
    if(rand()%100<p*100){  //car rand()%100 représente 0-99 
      // Ajout d'un élément et mesure du temps pris par l'opération.    
      clock_gettime(clk_id, &before);
      btree_insert(b, rand()%1000000);
      memory_allocation = FALSE;
      clock_gettime(clk_id, &after);
    }else{       
      // Suppression du dernier élément et mesure du temps pris par l'opération.    
      timespec_get(&before, TIME_UTC);
      btree_delete(b, rand()%1000000);
      memory_allocation = FALSE;
      timespec_get(&after, TIME_UTC);
    }
    // Enregistrement du temps pris par l'opération
    analyzer_append(time_analysis, after.tv_nsec - before.tv_nsec);
    // Enregistrement du nombre de copies efféctuées par l'opération.
    // S'il y a eu réallocation de mémoire, il a fallu recopier tout le tableau.
    analyzer_append(copy_analysis, (memory_allocation)? btree_size(b->root):1 );
    // Enregistrement de l'espace mémoire non-utilisé.
    analyzer_append(memory_analysis,btree_capacity(b->root)-btree_size(b->root));

  }

  // Affichage de quelques statistiques sur l'expérience.
  fprintf(stderr, "Total cost: %Lf\n", get_total_cost(time_analysis));
  fprintf(stderr, "Average cost: %Lf\n", get_average_cost(time_analysis));
  fprintf(stderr, "Variance: %Lf\n", get_variance(time_analysis));
  fprintf(stderr, "Standard deviation: %Lf\n", get_standard_deviation(time_analysis));

  // Sauvegarde les données de l'expérience.
  save_values(time_analysis, "../plots/dynamic_array_add_and_delete_sqrt_time_c.plot");
  save_values(copy_analysis, "../plots/dynamic_array_add_and_delete_sqrt_copy_c.plot");
  save_values(memory_analysis, "../plots/dynamic_array_add_and_delete_sqrt_memory_c.plot");

  // Nettoyage de la mémoire avant la sortie du programme
  btree_destroy(a);
  analyzer_destroy(time_analysis);
  analyzer_destroy(copy_analysis);
  analyzer_destroy(memory_analysis);
  return EXIT_SUCCESS;
}
