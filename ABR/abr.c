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

Arbre_t   ajouter_cle (Arbre_t a, int cle)
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
  detruire_pile(p);
  return max;
}


void parcourir_arbre_largeur (Arbre_t a)
{
  pfile_t f=creer_file();
  enfiler(f,a);
  while(!file_vide(f)){
    Arbre_t tmp=defiler(f);
    enfiler(f,tmp->fgauche);
    enfiler(f,tmp->fdroite);
    printf("%d  ",tmp->cle);
  }
  detruire_file(f);
  printf("\n");
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
  detruire_pile(p);
  printf("Nb noeud au niveau 0 : 1\n");
  for(int i=1;i<20 && tab2[i]!=0;i++)printf("Nb noeud au niveau %d : %d\n",i,tab2[i]);
  free(tab2);
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
  detruire_pile(p);
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

 int trouver_cle_max (Arbre_t a)
{
  if(a==NULL){
    return -1;
  }
  if(a->fdroite==NULL)return a->cle;
  return trouver_cle_min(a->fdroite);
}



void imprimer_liste_cle_triee_r (Arbre_t a)
{
  if(a==NULL)return;
  imprimer_liste_cle_triee_r(a->fgauche);
  printf("%d ",a->cle);
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
    printf("%d ",a->cle);
    if(a->fdroite!=NULL){
      a=a->fdroite;
      while(a->fgauche!=NULL){
        empiler(p,a);
        a=a->fgauche;
      }
      empiler(p,a);
    }
  }
  detruire_pile(p);
  printf("\n");
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
  detruire_pile(p);
  int drapeau=0;
  for(int i=0;i<20 && tab2[i]!=0;i++){
    if(tab2[i]!=puissance(2,i))drapeau++;
  }
  free(tab2);
  if(drapeau>1)return 0;
  return 1;
}

int arbre_parfait (Arbre_t a)
{
  if(a==NULL)return 1;
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
  detruire_pile(p);
  for(int i=0;i<20 && tab2[i]!=0;i++){
    if(tab2[i]!=puissance(2,i)){
      free(tab2);
      return 0;
    }
  }
  free(tab2);
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

Arbre_t trouver_arbre_min(Arbre_t a){
  if(a==NULL){
    return NULL;
  }
  if(a->fgauche==NULL)return a;
  return trouver_arbre_min(a->fgauche);
}

Arbre_t trouver_arbre_max(Arbre_t a){
  if(a==NULL){
    return NULL;
  }
  if(a->fdroite==NULL)return a;
  return trouver_arbre_min(a->fdroite);
}

Arbre_t rechercher_cle_sup_arbre (Arbre_t a, int valeur,Arbre_t max)
{
  if(a==NULL)return max;
  if(a->cle==valeur){
    if(a->fdroite!=NULL)return trouver_arbre_min(a->fdroite);
    else return max;
  }
  else if(a->cle<valeur)return rechercher_cle_sup_arbre(a->fdroite,valeur,max); 
  else {
    if(max==NULL)return rechercher_cle_sup_arbre(a->fgauche,valeur,a);
    else if(a->cle<max->cle)return rechercher_cle_sup_arbre(a->fgauche,valeur,a);
    else return rechercher_cle_inf_arbre(a->fgauche,valeur,max);
  }
}



Arbre_t rechercher_cle_inf_arbre (Arbre_t a, int valeur,Arbre_t max)
{ 
  if(a==NULL)return max;
  if(a->cle==valeur){
    if(a->fgauche!=NULL)return trouver_arbre_max(a->fgauche);
    else return max;
  }
  else if(a->cle<valeur){
    if(max==NULL)return rechercher_cle_inf_arbre(a->fdroite,valeur,a); 
    else if (a->cle>max->cle)return rechercher_cle_inf_arbre(a->fdroite,valeur,a); 
    else return rechercher_cle_inf_arbre(a->fdroite,valeur,max); 
  }else return rechercher_cle_inf_arbre(a->fgauche,valeur,max);
}



Arbre_t detruire_cle_arbre(Arbre_t a,int cle){
  if(a==NULL)return NULL;
  if(feuille(a) && a->cle==cle){
    free(a);
    return NULL;
  }else if(a->cle<cle)a->fdroite=detruire_cle_arbre(a->fdroite,cle);
  else if(a->cle>cle)a->fgauche=detruire_cle_arbre(a->fgauche,cle);
  else{
    Arbre_t tmp;
    if(a->fdroite!=NULL){
      tmp=a->fdroite;
      if(tmp->fgauche==NULL){
        a->cle=tmp->cle;
        a->fdroite=detruire_cle_arbre(a->fdroite,a->cle);
      }else{
        while(tmp->fgauche->fgauche!=NULL)tmp=tmp->fgauche;
        a->cle=tmp->fgauche->cle;
        tmp->fgauche=detruire_cle_arbre(tmp->fgauche,tmp->fgauche->cle);
      }
    }else{
      tmp=a->fgauche;
      if(tmp->fdroite==NULL){
        a->cle=tmp->cle;
        a->fgauche=detruire_cle_arbre(a->fgauche,a->cle);
      }else{
        while(tmp->fdroite->fdroite!=NULL)tmp=tmp->fdroite;
        a->cle=tmp->fdroite->cle;
        tmp->fdroite=detruire_cle_arbre(tmp->fdroite,tmp->fdroite->cle);
      }
    }
  }
  return a;
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
  detruire_file(f);
  return res; 
}

Arbre_t union_deux_arbres (Arbre_t a1, Arbre_t a2)
{
  Arbre_t res=NULL,tmp;

  pfile_t f=creer_file();
  enfiler(f,a1);
  enfiler(f,a2);
  while(!file_vide(f)){
    tmp=defiler(f);
    enfiler(f,tmp->fdroite);
    enfiler(f,tmp->fgauche);
    res = ajouter_cle(res,tmp->cle);
  }
  detruire_file(f);
  return res;
}

int inclusion_arbre(Arbre_t a1, Arbre_t a2){    // Cherche uniquement pour les valeurs
  pfile_t f=creer_file();
  enfiler(f,a1);
  Arbre_t tmp;
  while(!file_vide(f)){
    tmp=defiler(f);
    enfiler(f,tmp->fgauche);
    enfiler(f,tmp->fdroite);
    if(tmp!=NULL && rechercher_cle_arbre(a2,tmp->cle)==NULL){
      detruire_file(f);
      return 0;
    }
  }
  detruire_file(f);
  return 1;
}

int inclusion_arbre2(Arbre_t a1, Arbre_t a2){  // Regarde uniquement la structure 
  if(a1==NULL && a2==NULL)return 1;
  else if(a1==NULL || a2==NULL)return 0;
  if(a1->cle>a2->cle)return inclusion_arbre2(a1,a2->fdroite);
  else if(a1->cle<a2->cle)return inclusion_arbre2(a1,a2->fgauche);
  else if(a1->fdroite->cle==a2->fdroite->cle && a1->fgauche->cle==a2->fgauche->cle)return inclusion_arbre2(a1->fdroite,a2->fdroite) && inclusion_arbre2(a1->fgauche,a2->fgauche);
  return 0;
}


void liberer_arbre (Arbre_t a)
{
  pfile_t f=creer_file();
  enfiler(f,a);
  while(!file_vide(f)){
    Arbre_t tmp=defiler(f);
    enfiler(f,tmp->fgauche);
    enfiler(f,tmp->fdroite);
    free(tmp);
  }
  detruire_file(f);
}