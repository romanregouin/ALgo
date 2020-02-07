#ifndef _ABR_H_
#define _ABR_H_

/* structure noeud presentee en cours */

typedef struct n {
  int cle;
  int h;
  struct n *fgauche, *fdroite;
} noeud_t, *pnoeud_t ;

typedef struct avl {
  int cle;
  int h;
  int bal;
  struct avl *fgauche, *fdroite;
} noeud_avl, *pnoeud_avl;

/* type Arbre, pointeur vers un noeud */

typedef pnoeud_t Arbre_t;

typedef pnoeud_avl Arbre_avl;

Arbre_t lire_arbre (char *nom_fichier) ;

Arbre_t rechercher_cle_arbre (Arbre_t a, int valeur);

void afficher_arbre (Arbre_t a, int niveau) ;

int hauteur_arbre_r (Arbre_t a) ;

int hauteur_arbre_nr (Arbre_t a) ;

void parcourir_arbre_largeur (Arbre_t a) ;

void afficher_nombre_noeuds_par_niveau (Arbre_t a) ;

int nombre_cles_arbre_r (Arbre_t a) ;

int nombre_cles_arbre_nr (Arbre_t a) ;

int trouver_cle_min (Arbre_t a) ;

int trouver_cle_max (Arbre_t a) ;

void imprimer_liste_cle_triee_r (Arbre_t a) ;

void imprimer_liste_cle_triee_nr (Arbre_t a) ;

int arbre_plein (Arbre_t a) ;

int arbre_parfait (Arbre_t a) ;

Arbre_t trouver_arbre_min(Arbre_t a);

Arbre_t trouver_arbre_max(Arbre_t a);

Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur,Arbre_t max) ;

Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur,Arbre_t max) ;

Arbre_t detruire_cle_arbre (Arbre_t a, int cle) ;

Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2) ;

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2) ;

//ALV

int calcul_balances(Arbre_avl a);

Arbre_avl rotation_gauche(Arbre_avl a);

Arbre_avl rotation_droite(Arbre_avl a);

Arbre_avl double_rotation_gauche(Arbre_avl a);

Arbre_avl double_rotation_droite(Arbre_avl a);



#endif