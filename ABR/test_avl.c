#include <stdio.h>
#include <stdlib.h>
#include "avl.h"

int main(int argc,char** argv){

  printf("Test AVL :\n");
  //Test de la rotation gauche
  Arbre_avl a1;
  a1=lire_arbre("avl_test_suppression");
  
  afficher_arbre(a1,0);

  //Test de suppression sur chaque clé de l'arbre
  // fontion testée : detruire_cle_arbre (Sophie)
  printf("-----------------------------Suppression 10-------------------------\n");
  afficher_arbre(detruire_cle_arbre2(a1,10),0);
  printf("-----------------------------Suppression 5-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,5),0);
  printf("-----------------------------Suppression 2-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,2),0);
  printf("-----------------------------Suppression 1-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,1),0);
  printf("-----------------------------Suppression 3-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,3),0);
  printf("-----------------------------Suppression 4-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,4),0);
  printf("-----------------------------Suppression 8-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,8),0);
  printf("-----------------------------Suppression 7-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,7),0);
  printf("-----------------------------Suppression 9-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,9),0);
  printf("-----------------------------Suppression 14-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,14),0);
  printf("-----------------------------Suppression 11-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,11),0);
  printf("-----------------------------Suppression 12-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,12),0);
  printf("-----------------------------Suppression 15-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,15),0);
  printf("-----------------------------Suppression 16-------------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,16),0);
  printf("-----------------------Suppression 100 (inexistante)------------------\n");
  a1=lire_arbre("avl_test_suppression");
  afficher_arbre(detruire_cle_arbre2(a1,100),0);
  printf("-----------------------------Suppression 10-------------------------\n");
  afficher_arbre(a1=detruire_cle_arbre2(a1,10),0);
  printf("-----------------------------Suppression 5-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,5),0);
  printf("-----------------------------Suppression 2-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,2),0);
  printf("-----------------------------Suppression 1-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,1),0);
  printf("-----------------------------Suppression 3-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,3),0);
  printf("-----------------------------Suppression 4-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,4),0);
  printf("-----------------------------Suppression 8-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,8),0);
  printf("-----------------------------Suppression 7-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,7),0);
  printf("-----------------------------Suppression 9-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,9),0);
  printf("-----------------------------Suppression 14-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,14),0);
  printf("-----------------------------Suppression 11-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,11),0);
  printf("-----------------------------Suppression 12-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,12),0);
  printf("-----------------------------Suppression 15-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,15),0);
  printf("-----------------------------Suppression 16-------------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,16),0);
  printf("-----------------------Suppression 100 (inexistante)------------------\n");
  //a1=lire_arbre("avl_test_suppression");
  afficher_arbre(a1=detruire_cle_arbre2(a1,100),0);
}

