#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <limits.h>
#include "avl.h"


#define max(a,b) ((a)>(b)?(a):(b))

Arbre_avl lire_arbre (char *nom_fichier){
  FILE *f ;
  int cle;
  Arbre_avl a = NULL;
 // Arbre_avl* min = malloc(sizeof(Arbre_avl));

  f = fopen (nom_fichier, "r") ;
  while (fscanf (f, "%d", &cle) != EOF){
      a=ajouter_cle (a, cle) ;
  }
  fclose (f) ;
  calcul_balances(a);
  return a ;
}

void afficher_arbre (Arbre_avl a, int niveau){
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


int calcul_balances(Arbre_avl a){
	int hg=-1,hd=-1;
  if(a==NULL)return 0;
	if(a->fgauche!=NULL){ hg=calcul_balances(a->fgauche); }
	if(a->fdroite!=NULL){ hd=calcul_balances(a->fdroite); }
	int diffH=hg-hd;
	switch(diffH){
		case 0:
			a->bal=0;
			break;
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
  if(a==NULL)return NULL;
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

Arbre_avl rechercher_cle_arbre (Arbre_avl a, int valeur)
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

Arbre_avl ajouter_noeud (Arbre_avl a, Arbre_avl n, Arbre_avl des)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else {
	if (a->bal!=0) {des = a;}
	if (n->cle < a->cle){
		a->fgauche = ajouter_noeud (a->fgauche, n, des) ;
	}else{
		a->fdroite = ajouter_noeud (a->fdroite, n, des) ;
	}
  } 
  return a ;
  
} 

Arbre_avl   ajouter_cle (Arbre_avl a, int cle)
{
  Arbre_avl n ;
  Arbre_avl ptrouve ;
  Arbre_avl desequilibre=NULL;
  
  /* 
     ajout de la clé. Creation du noeud n qu'on insere 
    dans l'arbre a
  */

  ptrouve = rechercher_cle_arbre (a, cle) ;

  if (ptrouve == NULL)
    {
      n = (Arbre_avl) malloc (sizeof(noeud_avl)) ;
      n->cle = cle;
      n->bal=0;
      n->fgauche = NULL ;
      n->fdroite = NULL ;

      a = ajouter_noeud (a, n, desequilibre) ;
      calcul_balances(a);
      equilibrer(desequilibre);
      calcul_balances(a);
      return a ;
    }
  else
    return a ;
}



Arbre_avl ajouter_cle2(Arbre_avl a,int val,Arbre_avl* min){
  if(a==NULL)return a;
  if(a->cle==val)return a;
  Arbre_avl res;
  if(a->cle<val){
    if(a->bal<0){
      *min=a;
      res=ajouter_cle2(a->fgauche,val,min);
    }
    else res=ajouter_cle2(a->fgauche,val,min);
    if(res==NULL){
      Arbre_avl new=malloc(sizeof(noeud_avl));
      new->cle=val;
      new->bal=0;
      new->fdroite=NULL;
      new->fgauche=NULL;
      a->fgauche=new;
    };
    if(*min==a && res->bal!=0){
      if(res->bal==1)rotation_gauche(a);
      if(res->bal==-1)double_rotation_gauche(a);
    }
  }else{
    if(a->bal>0){
      *min=a;
      res=ajouter_cle2(a->fdroite,val,min);
    }
    else res=ajouter_cle2(a->fdroite,val,min);
    if(res==NULL){
      Arbre_avl new=malloc(sizeof(noeud_avl));
      new->cle=val;
      new->bal=0;
      new->fdroite=NULL;
      new->fgauche=NULL;
      a->fdroite=new;
    };
    if(*min==a && res->bal!=0){
      if(res->bal==1)rotation_droite(a);
      if(res->bal==-1)double_rotation_droite(a);
    }
  }
  return res;
}