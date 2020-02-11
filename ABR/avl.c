#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <limits.h>
#include "avl.h"
#include "pile.h"
#include "file.h"


#define max(a,b) ((a)>(b)?(a):(b))

Arbre_avl lire_arbre (char *nom_fichier){
  FILE *f ;
  int cle;
  Arbre_avl a = NULL;
  
  f = fopen (nom_fichier, "r") ;

  while (fscanf (f, "%d", &cle) != EOF)
    {
      a = ajouter_cle (a, cle) ;
    }
    
  fclose (f) ;

  return a ;
}

int calcul_balances(Arbre_avl a){
	int hg=-1,hd=-1;
	if(a->fgauche!=NULL){ hg=calcul_balances(a->fgauche); }
	if(a->fdroite!=NULL){ hd=calcul_balances(a->fdroite); }
	if(hg==hd) { a->bal=0; }
	int diffH=hg-hd;
	switch(diffH){
		case 1:
			a->bal=-1;
			break;
		case 2:
			a->bal=-2;
			break;
		case -1:
			a->bal=1;
			break;
		case -2:
			a->bal=2;
			break;
		default:
			break;
	}
	return (max(hg,hd)+1);
}

Arbre_avl rotation_gauche(Arbre_avl a){
  if(a==NULL){
    return a;
  }
  Arbre_avl newArbre = a->fdroite;
  a->fdroite=newArbre->fgauche;
  newArbre->fgauche=a;
  calcul_balances(newArbre);
  return newArbre;
}
Arbre_avl rotation_droite(Arbre_avl a){
  if(a==NULL){
    return a;
  }
  Arbre_avl newArbre = a->fgauche;
  a->fgauche=newArbre->fdroite;
  newArbre->fdroite=a;
  calcul_balances(newArbre);
  return newArbre;
}

Arbre_avl double_rotation_gauche(Arbre_avl a){
  if(a==NULL){
    return a;
  }
  a->fdroite=rotation_droite(a->fdroite);
  return rotation_gauche(a);
}

Arbre_avl double_rotation_droite(Arbre_avl a){
  if(a==NULL){
    return a;
  }
  a->fgauche=rotation_gauche(a->fgauche);
  return rotation_droite(a);
}

Arbre_avl equilibrer(Arbre_avl a){
	if(a->bal == 2){
		if(a->fdroite->bal >= 0)
			return rotation_gauche(a);
		else
			return double_rotation_gauche(a);
	} else if (a->bal == -2){
		if (a->fgauche->bal <= 0)
			return rotation_droite(a);
		else
			return double_rotation_droite(a);
	} else
		return a;
}



Arbre_avl ajouter_cle(Arbre_avl a,int val,Arbre_avl* min){
  if(a==NULL)return NULL;
  if(a->cle==val)return a;
  Arbre_avl res;
  int tmp;
  if(a->cle<val){
    tmp=a->fgauche->bal;
    if(a->bal<0){
      *min=a;
      res=ajouter_cle(a->fgauche,val,min);
    }
    else res=ajouter_cle(a->fgauche,val,min);
    if(*min==a && res->bal!=0){
      if(res->bal==1)rotation_gauche(a);
      if(res->bal==-1)double_rotation_gauche(a);
    }
  }else{
    if(a->bal>0){
      *min=a;
      res=ajouter_cle(a->fdroite,val,min);
    }
    else res=ajouter_cle(a->fdroite,val,min);
    if(*min==a && res->bal!=0){
      if(res->bal==1)rotation_droite(a);
      if(res->bal==-1)double_rotation_droite(a);
    }
  }
}