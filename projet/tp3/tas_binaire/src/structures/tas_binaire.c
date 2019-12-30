#include "../../include/structures/tas_binaire.h"
#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 1000010

tas_binaire_t * tas_binaire_create(){
  tas_binaire_t * res = (tas_binaire_t *) malloc( sizeof(tas_binaire_t) );
  res->data = (int *) malloc( sizeof(int) * (4 + 1) );
  res->capacity = 4;
  res->size = 0;
  return res;
}

void tas_binaire_destroy(tas_binaire_t * a){
  if( a != NULL ){
    if( a->data != NULL )
      free( a->data );
    free( a );
  }
}

char tas_binaire_append(tas_binaire_t * a, int x){
  char memory_allocation = FALSE;
  if( a!=NULL ){
    if( tas_binaire_do_we_need_to_enlarge_capacity(a) ){
      memory_allocation = TRUE;
      tas_binaire_enlarge_capacity(a);
    }
    a->size++;
    int y=a->size;
    a->data[y] = x;
    while((y > 1) && (a->data[y] < a->data[y/2])){
        int p;
        p = a->data[y];
	a->data[y] = a->data[y/2];
	a->data[y/2] = p;
	y = y/2;
	} 
  }
  return memory_allocation;
}

char tas_binaire_pop_back(tas_binaire_t * a){
  char memory_reduction = FALSE;
  if( a!=NULL && a->size>0 ){
    if( tas_binaire_do_we_need_to_reduce_capacity(a) ){
      memory_reduction = TRUE;
      tas_binaire_reduce_capacity(a);
    }
    	//int tete = a->data[1];
	int y;
	int z;
	a->data[1] = a->data[a->size];
	a->size --;
	y = 1;
	while(1==1){
		z = y * 2;
		if (z > a->size)
			break;
		if (z < a->size){
			if ( a->data[z] > a->data[z+1]){
				z++;
			}
		}
		if (a->data[y] > a->data[z]){
			int p;
			p = a->data[y];
			a->data[y] = a->data[z];
			a->data[z] = p;
		}
		else 
			break;
		y = z;
	}
  }
  return memory_reduction;
}


int tas_binaire_get(tas_binaire_t * a, int pos){
  if( a != NULL && pos >=0 && pos < a->size ){
    return a->data[pos];
  }
  printf("Wrong parameter pos=%d or NULL list", pos);
  return -1;
}

size_t tas_binaire_size(tas_binaire_t * a){
  return ( a!=NULL) ? a->size : -1;
}

size_t tas_binaire_capacity(tas_binaire_t * a){
  return ( a!=NULL) ? a->capacity : -1;
}

char tas_binaire_do_we_need_to_enlarge_capacity(tas_binaire_t * a){
  //return ( a->size >= (a->capacity*2/3) )? TRUE: FALSE;
  return ( a->size == a->capacity )? TRUE: FALSE;
}

void tas_binaire_enlarge_capacity(tas_binaire_t * a){
  a->capacity *=2; 
//a->capacity +=sqrt( a->capacity );
  a->data = (int *) realloc(a->data, sizeof(int) * (a->capacity+1));
}

char tas_binaire_do_we_need_to_reduce_capacity(tas_binaire_t * a){
  return ( a->size <= a->capacity/4 && a->size >4 )? TRUE: FALSE;
  //return ( a->size <= a->capacity - 2*sqrt( a->capacity ) && a->size >4 )? TRUE: FALSE;
}

void tas_binaire_reduce_capacity(tas_binaire_t * a){
  a->capacity = a->capacity / 2;
  //a->capacity -=sqrt( a->capacity ); 
  a->data = (int *) realloc(a->data, sizeof(int) * (a->capacity+1));
}
