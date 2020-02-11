#ifndef _AVL_H_
#define _AVL_H_

typedef struct avl {
  int cle;
  int h;
  int bal;
  struct avl *fgauche, *fdroite;
} noeud_avl, *pnoeud_avl;

typedef pnoeud_avl Arbre_avl;

Arbre_avl lire_arbre (char *nom_fichier) ;

void afficher_arbre (Arbre_avl a, int niveau) ;

int calcul_balances(Arbre_avl a);

Arbre_avl rotation_gauche(Arbre_avl a);

Arbre_avl rotation_droite(Arbre_avl a);

Arbre_avl double_rotation_gauche(Arbre_avl a);

Arbre_avl double_rotation_droite(Arbre_avl a);

#endif