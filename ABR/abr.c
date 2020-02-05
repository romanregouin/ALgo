#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <limits.h>
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
  else if (n->cle < a->cle){
  n->h++;
	a->fgauche = ajouter_noeud (a->fgauche, n) ;
  }else{
	a->fdroite = ajouter_noeud (a->fdroite, n) ;
  n->h++;
  }
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
      n->h=0;
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
  if(a==NULL){
    return -1;
  }
  ppile_t p = creer_pile();
  int max=0;
  empiler(p,a);
  while(!pile_vide(p)){
    a = depiler(p);
    if(a!=NULL){
      if(a->h>max)max=a->h;
      empiler(p,a->fdroite);
      empiler(p,a->fgauche);
    }
  }
  return max;
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
  if(a==NULL){
    printf("Arbre vide (aucune noeud a afficher)\n");
  }
  //pile stockant les arbres
  ppile_t p = creer_pile();
  empiler(p,a);
  int* tab2=malloc(sizeof(int)*20);
  for(int i=0;i<20;i++)tab2[i]=0;
  while(!pile_vide(p)){
    a = depiler(p);
    if(a!=NULL){
      tab2[a->h]++;
      empiler(p,a->fdroite);
      empiler(p,a->fgauche);
    }
  }
  printf("Nb noeud au niveau 0 : 1\n");
  for(int i=1;i<20 && tab2[i]!=0;i++)printf("Nb noeud au niveau %d : %d\n",i,tab2[i]);
}


int nombre_cles_arbre_r (Arbre_t a)
{
  if(a==NULL)return 0;
  return nombre_cles_arbre_r(a->fgauche)+nombre_cles_arbre_r(a->fdroite)+1;
}

int nombre_cles_arbre_nr (Arbre_t a)
{
  if(a==NULL){
    return 0;
  }
  ppile_t p = creer_pile();
  int nb=0;
  empiler(p,a);
  while(!pile_vide(p)){
    a = depiler(p);
    if(a!=NULL){
      nb++;
      empiler(p,a->fdroite);
      empiler(p,a->fgauche);
    }
  }
  return nb;
}

int trouver_cle_min (Arbre_t a)
{
  if(a==NULL){
    return -1;
  }
  if(a->fgauche==NULL)return a->cle;
  return trouver_cle_min(a->fgauche);
}

 

void imprimer_liste_cle_triee_r (Arbre_t a)
{
  if(a==NULL)return;
  imprimer_liste_cle_triee_r(a->fgauche);
  printf(" %d ",a->cle);
  imprimer_liste_cle_triee_r(a->fdroite);
}

void imprimer_liste_cle_triee_nr (Arbre_t a)
{
 if(a==NULL){
    return ;
  }
  ppile_t p = creer_pile();
  while(a->fgauche!=NULL){
    empiler(p,a);
    a=a->fgauche;
  }
  empiler(p,a);
  while(!pile_vide(p)){
    a = depiler(p);
    printf("%d \n",a->cle);
    if(a->fdroite!=NULL){
      a=a->fdroite;
      while(a->fgauche!=NULL){
        empiler(p,a);
        a=a->fgauche;
      }
      empiler(p,a);
    }
  }
}


int puissance(int a,int n){
  if(n==0)return 1;
  if(n==1)return a;
  if(n%2==0)return puissance(a*a,n/2);
  else return n*puissance(n*n,(n-1)/2);
}

int arbre_plein (Arbre_t a)
{
  if(a==NULL)return 1;
  ppile_t p = creer_pile();
  int h =0;
  int n=0;
  empiler(p,a);
  int* tab2=malloc(sizeof(int)*100);
  for(int i=0;i<20;i++)tab2[i]=0;
  while(!pile_vide(p)){
    a = depiler(p);
    if(a!=NULL){
      tab2[a->h]++;
      empiler(p,a->fdroite);
      empiler(p,a->fgauche);
    }
  }
  int drapeau=0;
  for(int i=0;i<20 && tab2[i]!=0;i++){
    if(drapeau>1)return 0;
    if(tab2[i]!=puissance(2,i))drapeau++;
  }
  return 1;
}

int arbre_parfait (Arbre_t a)
{
  if(a==NULL)return 1;
  ppile_t p = creer_pile();
  int h =0;
  int n=0;
  empiler(p,a);
  int* tab2=malloc(sizeof(int)*20);
  for(int i=0;i<20;i++)tab2[i]=0;
  while(!pile_vide(p)){
    a = depiler(p);
    if(a!=NULL){
      tab2[a->h]++;
      empiler(p,a->fdroite);
      empiler(p,a->fgauche);
    }
  }
  for(int i=0;i<20 && tab2[i]!=0;i++){
    if(tab2[i]!=puissance(2,i))return 0;
  }
  return 1;
}



/*
Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur)
{
  if(a==NULL)return NULL;
  Arbre_t res;
  if(a->cle==valeur)return a->fdroite;
  else if(a->cle<valeur)res=rechercher_cle_inf_arbre(a->fdroite,valeur); 
  else res=rechercher_cle_inf_arbre(a->fgauche,valeur);
  if(res==NULL && a->cle>valeur)return a;
  if(res!=NULL && a->cle>valeur && a->cle<res->cle)return a;
  return res;
}
*/
Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur,Arbre_t max)
{
  if(a==NULL)return max;
  if(a->cle==valeur)return a->fdroite;
  else if(a->cle<valeur)return rechercher_cle_inf_arbre(a->fdroite,valeur,max); 
  else {
    if(max==NULL)return rechercher_cle_inf_arbre(a->fgauche,valeur,a);
    else if(a->cle<max->cle)return rechercher_cle_inf_arbre(a->fgauche,valeur,a);
    else return rechercher_cle_inf_arbre(a->fgauche,valeur,max);
  }
}



Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur,Arbre_t max)
{ 
  if(a==NULL)return NULL;
  if(a->cle==valeur)return a->fgauche;
  else if(a->cle<valeur){
    if(max==NULL)return rechercher_cle_inf_arbre(a->fdroite,valeur,a); 
    else if (a->cle>max->cle)return rechercher_cle_inf_arbre(a->fdroite,valeur,a); 
    else return rechercher_cle_inf_arbre(a->fdroite,valeur,max); 
  }else return rechercher_cle_inf_arbre(a->fgauche,valeur,max);
}


Arbre_t detruire_cle_arbre (Arbre_t a, int cle)
{
  Arbre_t elem;
  if(a==NULL){
    return NULL;
  }
  elem = rechercher_cle_arbre(a,cle);
  if(elem==NULL){
    return a;
  }else{
    if(feuille(elem)){
      elem=NULL;
      return a;
    }else{
      if((elem->fdroite!=NULL)&&(elem->fgauche!=NULL)){
        if(elem->fgauche->fdroite!=NULL){
          elem->fdroite = ajouter_noeud(elem->fdroite,elem->fgauche->fdroite);
          free(elem->fgauche->fdroite);
          elem = elem->fgauche;
        }
      }else if(elem->fdroite==NULL){
        elem = elem->fgauche;
        return a;
      }else if(elem->fgauche==NULL){
        elem = elem->fdroite;
        return a;
      }
    }
  }
  
}



Arbre_t intersection_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  Arbre_t res=NULL,tmp;

  pfile_t f=creer_file();
  enfiler(f,a1);
  while(!file_vide(f)){
    tmp=defiler(f);
    enfiler(f,tmp->fdroite);
    enfiler(f,tmp->fgauche);
    if(rechercher_cle_arbre(a2,tmp->cle)!=NULL){
      res = ajouter_cle(res,tmp->cle);
    }
  }
  return res; 
}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  Arbre_t res,tmp;

  pfile_t f=creer_file();
  enfiler(f,a1);
  enfiler(f,a2);
  while(!file_vide(f)){
    tmp=defiler(f);
    enfiler(f,tmp->fdroite);
    enfiler(f,tmp->fgauche);
    res = ajouter_cle(res,tmp->cle);
  }
  
  return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////                AVL               ////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

Arbre_avl rotation_gauche(Arbre_avl a){
  if(a==NULL){
    return a;
  }
  
}