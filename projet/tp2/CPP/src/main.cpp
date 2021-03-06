#include<iostream>
#include <chrono>
#include<cstdlib>	
#include "structures/arraylist.hpp"
#include "analysis/analyzer.hpp"

using namespace structures;
using namespace analysis;
using namespace std::chrono;

int main(int argc, char ** argv){
  int i;
  // Tableau dynamique.
  ArrayList<int> a;
  // Analyse du temps pris par les opérations.
  Analyzer time_analysis;
  // Analyse du nombre de copies faites par les opérations.
  Analyzer copy_analysis;
  // Analyse de l'espace mémoire inutilisé.
  Analyzer memory_analysis;
  high_resolution_clock::time_point before, after;
  // Booléen permettant de savoir si une allocation a été effectuée.
  bool memory_allocation;
  srand(0);


  for(i = 0; i < 1000000 ; i++){
    if(a.empty() || rand()%2){
      // Ajout d'un élément et mesure du temps pris par l'opération.
      before = high_resolution_clock::now();
      memory_allocation = a.append(i);
      after = high_resolution_clock::now();
    } else{
      // Suppression du dernier élément et mesure du temps pris par l'opération.
      before = high_resolution_clock::now();
      memory_allocation = a.pop_back();
      after = high_resolution_clock::now();
    }

    // Enregistrement du temps pris par l'opération
    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(after - before);    
    time_analysis.append(static_cast<double>(duration.count()));
    // Enregistrement du nombre de copies efféctuées par l'opération.
    // S'il y a eu réallocation de mémoire, il a fallu recopier tout le tableau.
    copy_analysis.append( (memory_allocation)? a.get_size():1 );
    // Enregistrement de l'espace mémoire non-utilisé.
    memory_analysis.append( a.get_capacity() - a.get_size() );
  }

  // Affichage de quelques statistiques sur l'expérience.
  std::cerr<<"Total cost :"<<time_analysis.get_total_cost()<<std::endl;
  std::cerr<<"Average cost :"<<time_analysis.get_average_cost()<<std::endl;
  std::cerr<<"Variance :"<<time_analysis.get_variance()<<std::endl;
  std::cerr<<"Standard deviation :"<<time_analysis.get_standard_deviation()<<std::endl;    

  // Sauvegarde les données de l'expérience.
  time_analysis.save_values("../plots/dynamic_array_add_and_delete_sqrt_time_cpp.plot");
  copy_analysis.save_values("../plots/dynamic_array_add_and_delete_sqrt_copy_cpp.plot");
  memory_analysis.save_values("../plots/dynamic_array_add_and_delete_sqrt_memory_cpp.plot");
  
  return 0;
}
