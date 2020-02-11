#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc,char** argv){

  printf("Test AVL :\n");
  //Test de la rotation gauche
  Arbre_avl a1,a2;
  a1=lire_arbre("avl_rot_gauche_test");
  
  afficher_arbre(a1,0);
  printf("----------------------------------------------------------------\n");
  a2=lire_arbre("avl_rot_gauche_res");
  afficher_arbre(a2,0);
}