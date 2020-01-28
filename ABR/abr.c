#include <stdio.h>
#include <stdlib.h>
#include <math.h>  

#include "abr.h"
#include "pile.h"
#include "file.h"


#define max(a,b) ((a)>(b)?(a):(b))


int feuille (Arbre_t a)
{
  if (a == NULL)
    return 0 ;
  else
    {
      if ((a->fgauche == NULL) && (a->fdroite == NULL))
	return 1 ;
      else
	return 0 ;
    }
}

Arbre_t ajouter_noeud (Arbre_t a, Arbre_t n)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else if (n->cle < a->cle)
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  else
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  return a ;
  
}  

Arbre_t rechercher_cle_arbre (Arbre_t a, int valeur)
{
  if (a == NULL)
    return NULL ;
  else
    {
      if (a->cle == valeur)
	return a ;
      else
	{
	  if (a->cle < valeur)
	    return rechercher_cle_arbre (a->fdroite, valeur) ;
	  else
	    return rechercher_cle_arbre (a->fgauche, valeur) ;
	}
    }
}

Arbre_t ajouter_cle (Arbre_t a, int cle)
{
  Arbre_t n ;
  Arbre_t ptrouve ;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre_t) malloc (sizeof(noeud_t)) ;
      n->cle = cle;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n) ;
      return a ;
    }
  else
    return a ;
}


Arbre_t lire_arbre (char *nom_fichier)
{
  FILE *f ;
  int cle;
  Arbre_t a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

void afficher_arbre (Arbre_t a, int niveau)
{
  /*
    affichage de l'arbre a
    on l'affiche en le penchant sur sa gauche
    la partie droite (haute) se retrouve en l'air
  */
  
  int i ;
  
  if (a != NULL)
      {
	afficher_arbre (a->fdroite,niveau+1) ;
	
	for (i = 0; i < niveau; i++)
	  printf ("\t") ;
	printf (" %d (%d)\n\n", a->cle, niveau) ;

	afficher_arbre (a->fgauche, niveau+1) ;
      }
  return ;
}


int hauteur_arbre_r (Arbre_t a)
{
  if(a==NULL)return -1;
  return max(hauteur_arbre_r(a->fdroite),hauteur_arbre_r(a->fgauche))+1;
}

int hauteur_arbre_nr (Arbre_t a)
{
<<<<<<< HEAD
  if(a==NULL){
    return -1;
  }
  ppile_t p = creer_pile();
  int h = -1;
  int res = empiler(p,a); //sert à rien de tester si pile pleine
  while(!pile_vide(p)){
    a = depiler(p);
    res = empiler(p,a->fdroite); //le cas des feuilles est géré par empiler
    res = empiler(p,a->fgauche);

  }
  return h;
=======
  return 0;
>>>>>>> master
}


void parcourir_arbre_largeur (Arbre_t a)
{
  pfile_t f=creer_file();
  enfiler(f,a);
  while(!file_vide(f)){
    Arbre_t tmp=defiler(f);
    enfiler(f,tmp->fdroite);
    enfiler(f,tmp->fgauche);
    //Instruction a faire sur le parcour en largeur (Exemple afficher la clef)
  }
}

void afficher_nombre_noeuds_par_niveau (Arbre_t a)
{
  
}


int nombre_cles_arbre_r (Arbre_t a)
{
<<<<<<< HEAD
  return 0;
=======
  if(a==NULL)return 0;
  return nombre_cles_arbre_r(a->fgauche)+nombre_cles_arbre_r(a->fdroite)+1;
>>>>>>> master
}

int nombre_cles_arbre_nr (Arbre_t a)
{
  return ((int)pow((float)2,(float)hauteur_arbre_r(a))-1);
}

int trouver_cle_min (Arbre_t a)
{
  if(a->fgauche==NULL)return a->cle;
  return trouver_cle_min(a->fgauche);
}

 

void imprimer_liste_cle_triee_r (Arbre_t a)
{
  /*
    a completer
  */

  
  return ;
}

void imprimer_liste_cle_triee_nr (Arbre_t a)
{
  /*
    a completer
  */

  
  return ;
}


int arbre_plein (Arbre_t a)
{
  /*
    a completer
  */
  
  return 0 ;
}

int arbre_parfait (Arbre_t a)
{
  /*
    a completer
  */
  
  return 0 ;
}




Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur)
{
  if(a==NULL){
    return NULL;
  }
}

Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur)
{
  /*
    a completer
  */

  return NULL ;
  
}


Arbre_t detruire_cle_arbre (Arbre_t a, int cle)
{
  /*
    a completer
  */

  return NULL ;
}



Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  /*
    a completer
  */

  return NULL ;
  
}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  /*
    a completer
  */

  return NULL ;
}

