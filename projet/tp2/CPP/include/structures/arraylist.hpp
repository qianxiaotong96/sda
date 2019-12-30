#ifndef __ARRAYLIST_HPP
#define __ARRAYLIST_HPP

#include<iostream>
#include<vector>
#include<cmath>
#include<cstring>

namespace structures {

  /**
     Cette classe est un proxy pour les vecteurs, c'est à dire les tableaux dynamiques en C++.
     On utilise cette classe afin d'avoir le contrôle sur la gestion de la mémoire.
  */
  template <typename P>
  class ArrayList{
  public:
    /**
       Constructeur de la classe des tableaux dynamiques.
       Complexité en temps/espace, pire et meilleur cas : O(1)  
    */
    ArrayList(){
      data = new P[4];
      capacity = 4;
      size = 4;
    }

    /**
       Ajoute une valeur dans le tableau.
       Complexité en temps/espace, pire cas : O(size)
       Complexité en temps/espace, meilleur cas : O(1)
       Complexité amortie : O(1)
       @param x est la valeur que l'on souhaite ajouter.
       @returns true si le tableau a été agrandit, false sinon
    */
    bool append(P x){
      bool memory_allocation = do_we_need_to_enlarge_capacity();
      if( memory_allocation ){
	memory_allocation = true;
	enlarge_capacity();
      }
      data[size++] = x;
      return memory_allocation;
    }

    /**
       Supprime la dernière valeur du tableau.
       Complexité en temps, pire cas : O(size)
       Complexité en temps, meilleur cas : O(1)
       Complexité amortie : O(1)
       @returns true si le tableau a été réduit, false sinon
    */
    bool pop_back(){
      if( size == 0 )
	throw std::runtime_error("Cannot pop an empty stack");
      bool memory_reduction = do_we_need_to_reduce_capacity();
      if( memory_reduction ){
	memory_reduction = true;
	reduce_capacity();
      }
      size--;
      return memory_reduction;
    }
  
    /**
       Renvoie la valeur située à la position donnée par l'utilisateur.
       Complexité en temps/espace, pire cas : O(1)
       @param pos est la l'indice de la case on l'utilisateur veut connaître la valeur.
       @returns la valeur située à la position donnée par l'utilisateur.
    */
    P get(const int & pos){
      if( pos < 0 || pos > size )
	throw std::runtime_error(pos+" is out of bound");
      return data[pos];
    }

    /**
       Renvoie le nombre d'éléments stockés dans le tableau.
       Complexité en temps/espace, pire cas : O(1)
       @returns le nombre d'éléments stockés dans le tableau.
    */
    const bool empty(){ return size == 0; }

    /**
       Renvoie le nombre d'éléments stockés dans le tableau.
       Complexité en temps/espace, pire cas : O(1)
       @returns le nombre d'éléments stockés dans le tableau.
    */
    const size_t get_size(){ return size; }

    /**
       Renvoie la capacité de stockage du tableau.
       Complexité en temps/espace, pire cas : O(1)
       @returns le nombre d'éléments stockés dans le tableau.
    */
    const size_t get_capacity(){ return capacity; }
  
  private:
    // Vecteur contenant les données.
    P * data;
    int size;
    int capacity;


    inline void realloc(int new_capacity){
      P * tmp = new P[new_capacity];
      std::memcpy( tmp, data, sizeof(P) * size );
      delete [] data;
      data = tmp;
    }
    
    /**
       Cette fonction détermine la règle selon laquelle un espace mémoire plus grand sera alloué ou non.
       @returns true si le tableau doit être agrandi, false sinon.
    */
    bool do_we_need_to_enlarge_capacity(){
      return size == capacity;
    }

    /**
       Cette fonction augmente la capacité du tableau.
    */
    void enlarge_capacity(){
      capacity += std::sqrt(capacity);
      realloc(capacity);
    }

    /**
       Cette fonction détermine la règle selon laquelle un espace mémoire plus petit sera alloué ou non.
       @returns true si le tableau doit être réduit, false sinon.
    */
    bool do_we_need_to_reduce_capacity(){
      return size <= capacity/4 && size > 4;
    }
  
    /**
       Cette fonction reduit la capacité du tableau.
    */
    void reduce_capacity(){
      capacity /= 2;
      realloc(capacity);      
    }
  
  };

}// namespace structures

#endif
