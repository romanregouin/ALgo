#include <stdio.h>
#include <stdlib.h>
#include <math.h>  
#include <limits.h>
#include "avl.h"


#define max(a,b) ((a)>(b)?(a):(b))



int feuille (Arbre_avl a)
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



Arbre_avl lire_arbre (char *nom_fichier){
  FILE *f ;
  int cle;
  Arbre_avl a = NULL;
  //Arbre_avl* min = malloc(sizeof(Arbre_avl)); //Version Liam

  f = fopen (nom_fichier, "r") ;
  while (fscanf (f, "%d", &cle) != EOF){
    //*min=NULL;                    //Version Liam
    //a=ajouter_cle2 (a, cle,min) ; //Version Liam
    a=ajouter_cle (a, cle) ;    //Version Sophie
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
	printf (" %d (%d)(%d)\n\n", a->cle,a->bal, niveau) ;

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

Arbre_avl ajouter_noeud (Arbre_avl a, Arbre_avl n, Arbre_avl* des)
{
  /* ajouter le noeud n dans l'arbre a */
  
  if (a == NULL)
    return n ;
  else {
	if (a->bal!=0) {*des = a;}
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

      a = ajouter_noeud (a, n, &desequilibre) ;
      calcul_balances(a);
      if (desequilibre!=NULL){
		  if(desequilibre==a){
			  a=equilibrer(desequilibre);
			  calcul_balances(a);
			  return a;
		  }
		  Arbre_avl tmp=a;
		  while(tmp->fdroite != desequilibre && tmp->fgauche!=desequilibre){
			  if (desequilibre->cle > tmp->cle){ tmp = tmp->fdroite;}
			  else{tmp=tmp->fgauche;}
		  }
		  if (tmp->fdroite == desequilibre){ tmp->fdroite=equilibrer(tmp->fdroite);}
		  else{ tmp->fgauche=equilibrer(tmp->fgauche);}
		  calcul_balances(a);
		  return a;		
	  }
      return a ;
    }
  else
    return a ;
}



Arbre_avl ajouter_cle2(Arbre_avl a,int val,Arbre_avl* min){
  int tmp=-3;  // la variable tmp sert a garder une trace de l'ancienne balance du fgauche ou fdroite -3 si le fils est null (-3 choisie arbritrairement)
  if(a==NULL){
      Arbre_avl new=malloc(sizeof(noeud_avl));  // cette partie correspond a la création du nouveau noeud
      new->cle=val;
      new->bal=0;
      new->h=0;
      new->fdroite=NULL;
      new->fgauche=NULL;
      return new;
  };
  if(a->cle==val)return a;  // si le noeud(cle) existe deja on s'arrete la
  Arbre_avl res;
  if(a->cle>val){                      // sinon on recherche a droite ou a gauche selon la valeur
    if(a->fgauche!=NULL)tmp=a->fgauche->bal;       // c'est ici qu'on assigne la valeur de l'ancienne balance
    if(a->bal<0)*min=a;             // ici on garde a l'aide d'un pointeur d'arbre le dernier arbre qui penche du coté ou on cherche 
    res=ajouter_cle2(a->fgauche,val,min);  // on recupere le resultat de l'ajout clef recursif 
    a->fgauche=res;                       // on l'ajoute en tant que nouveau filsgauche (si il y a eut une rotation cela permet de refaire le bon chainage)
    if(feuille(res) && res->cle==val){    // on vérifie s'il s'agit d'un fils et plus précisement d'un nouveau fils
      res->h=a->h+1;        // si c'est le cas on incremente ça hauteur selon celle précédente +1
      a->bal--;             // on ajuste la balance du noeud actuel
    }
    if(*min==a && res->bal!=0){   // c'est ici que l'on vérifie si l'on doit faire une rotation ou non
      if(res->bal==-1)a=rotation_droite(a);  // Une rotation s'opere lorsque a= valeur pointé par le min (min etant le meme partout car pointeur)
      if(res->bal==1)a=double_rotation_droite(a); //si on se trouve au min et que la balance de son fils d/g et différent de 0 alors on doit faire une rotation (car sinon le min serait le fils du noeud actuel car balance !=0)
    } // si le fils balance a a l'opposé du noeud actuel alors on fait une double rotation sinon rotation simple
    if(tmp!=-3 && tmp!=res->bal && res->bal!=0)a->bal--; // Enfin si tmp(val ancienne bal) a changé alors on doit ajuster la balance actuel en remontant l'arbre
  }else{ // On fait de meme pour le fils droit si oncherche a droite
    if(a->fdroite!=NULL)tmp=a->fdroite->bal;     // c'est ici qu'on assigne la valeur de l'ancienne balance
    if(a->bal>0)*min=a;         // ici on garde a l'aide d'un pointeur d'arbre le dernier arbre qui penche du coté ou on cherche 
    res=ajouter_cle2(a->fdroite,val,min);
    a->fdroite=res;
    if(feuille(res) && res->cle==val){
      res->h=a->h+1;
      a->bal++;
    }
    if(*min==a && res->bal!=0){
      if(res->bal==1)a=rotation_gauche(a);
      if(res->bal==-1)a=double_rotation_gauche(a);
    }
    if(tmp!=-3 && tmp!=res->bal && res->bal!=0)a->bal++;
  }
  return a; // on retourne le noeud actuel avec les chainages modifié ou non 
}


Arbre_avl detruire_cle_arbre(Arbre_avl a,int cle){
  a=detruire_cle_arbre_r(a,cle);
  a=equilibrer(a);
  return a;
}

Arbre_avl detruire_cle_arbre_r(Arbre_avl a,int cle){
  int tmp=-3;
  if(feuille(a) && a->cle==cle)return NULL;
  else if(a->cle<cle){
    if(a->fdroite!=NULL)tmp=a->fdroite->bal;
    a->fdroite=detruire_cle_arbre_r(a->fdroite,cle);
    if(tmp!=-3){
      if(a->fdroite==NULL)a->bal--;
      else if(tmp!=0 && a->fdroite->bal==0)a->bal--;
    }
  }else if(a->cle>cle){
    if(a->fgauche!=NULL)tmp=a->fgauche->bal;
    a->fgauche=detruire_cle_arbre_r(a->fgauche,cle);
    if(tmp!=-3){
      if(a->fgauche==NULL)a->bal++;
      else if(tmp!=0 && a->fgauche->bal==0)a->bal++;
    }
  }
  else{
    if(a->fdroite!=NULL){
      tmp=a->fdroite->bal;
      a->cle=a->fdroite->cle;
      a->fdroite=detruire_cle_arbre_r(a->fdroite,a->cle);
      if(a->fdroite==NULL)a->bal--;
      else if(tmp!=0 && a->fdroite->bal==0)a->bal--;
    }else{
      tmp=a->fgauche->bal;
      a->cle=a->fgauche->cle;
      a->fgauche=detruire_cle_arbre_r(a->fgauche,a->cle);
      if(a->fgauche==NULL)a->bal++;
      else if(tmp!=0 && a->fgauche->bal==0)a->bal++;
    }
  }
  return a;
}


//Toutes les fonctions suivante servent pour la destruction (version Sophie)
Arbre_avl detruire_cle_arbre2(Arbre_avl a,int cle){
  if(a==NULL) { return NULL; }
  Arbre_avl sa = rechercher_cle_arbre(a,cle); //on recupère l'arbre dont le noeud à supprimer est la racine
  Arbre_avl suppr = sa; //variable pour réutiliser ce noeud plus tard
  if(sa!=NULL){ //on va chercher à supprimer le noeud sa de son arbre (=supprimer la racine de sa)
	  if (feuille(sa)){sa = NULL;} //si sa est une feuille le nouvel arbre est vide
	  else{ 
		sa = detruire_racine(sa); //sinon on supprime la racine
		calcul_balances(sa);
		sa = equilibrer(sa); //on équilibre le nouvel arbre
	  }
	  if(a->cle==cle){a=sa;} //si le noeud à supprimer etait la racine de a le nouvel arbre a est directement donné par sa
	  else{ //sinon on parcourt l'arbre a pour raccrocher le sous-arbre sa au bon endroit
		  Arbre_avl tmp=a;
		  while(tmp->fdroite != suppr && tmp->fgauche!=suppr){
			  if (cle > tmp->cle){ tmp = tmp->fdroite;}
			  else{tmp=tmp->fgauche;}
		  }
		  if (tmp->fdroite != NULL && tmp->fdroite->cle == cle){ tmp->fdroite=sa;}
		  else{tmp->fgauche=sa;}
		  calcul_balances(tmp);
		  
		  // au besoin on réequilibre le noeud auquel on a accroché sa
		  Arbre_avl tmp2 = pere(a,tmp);
		  if(tmp2!=NULL){
			if (tmp->cle<tmp2->cle){tmp2->fgauche = equilibrer(tmp2->fgauche);}
			else{tmp2->fdroite = equilibrer(tmp2->fdroite);}
		  } else { a=tmp;}
	  }
	  calcul_balances(a);
	  return equilibrer(a); //enfin au réequilibre a si besoin
  }
  return a;
}

//fonction détruisant la racine de l'arbre passé en paramètre
Arbre_avl detruire_racine(Arbre_avl a){
	if (a->fdroite==NULL) //si la racine n'a pas de fils droit il suffit de renvoyer le fils gauche
	  return a->fgauche;
	else if(a->fgauche==NULL)
		return a->fdroite;
	else if(feuille(a->fgauche)){ //si le fils gauche de la racine est une feuille on le transforme en nouvelle racine en lui accrochant le fils droit de l'ancienne racine
		a->fgauche->fdroite=a->fdroite;
		return a->fgauche;
	}
	else { //sinon on va parcourir l'arbre récursivement pour trouver la nouvelle racine et construire le nouvel arbre
		a->fgauche = echanger_max_r(a->fgauche,&a);
		return a;
	}
  
}

//supprime la racine de l'arbre "pere" en mettant comme nouvelle racine 
//le noeud de clé directement inférieure à celle de la racine d'origine.
//fonction récursive, réequilibrant l'arbre petit à petit si besoin
Arbre_avl echanger_max_r(Arbre_avl a,Arbre_avl* pere){
	if(a->fdroite==NULL){
		//si la clé directement inférieure à la racine est sur un noeud n possédant un fils gauche,
		//la nouvelle racine devient ce noeud n et son fils prend l'ancienne place de n dans l'arbre
		Arbre_avl tmp = a->fgauche;
		a->fdroite = (*pere)->fdroite;
		a->fgauche = (*pere)->fgauche;
		*pere = a->fdroite;
		return tmp;
	}
	else if (feuille(a->fdroite)){
		//si la clé directement inférieure à la racine est une feuille, 
		//il suffit de les échanger et de supprimer la "nouvelle" feuille 
		a->fdroite->fdroite = (*pere)->fdroite;
		a->fdroite->fgauche = (*pere)->fgauche;
		*pere = a->fdroite;
		a->fdroite=NULL;
		calcul_balances(a);
		return equilibrer(a);
	} else {
		//si on a pas atteint la clé la plus proche de la racine on continue à chercher sur le sous-arbre droit suivant
		a->fdroite = echanger_max_r(a->fdroite,pere);
		calcul_balances(a);
		return equilibrer(a);
	}
}

// fonction renvoyant le père du noeud "fils", les 2 faisant partie de l'arbre a
Arbre_avl pere(Arbre_avl a, Arbre_avl fils){
	if (a==NULL) return NULL;
	if (a==fils) return NULL;
	if (rechercher_cle_arbre(a,fils->cle)==NULL) return NULL;
	Arbre_avl tmp=a;
	while(tmp->fdroite != fils && tmp->fgauche!=fils){
		if (fils->cle > tmp->cle){ tmp = tmp->fdroite;}
		else{tmp=tmp->fgauche;}
	}
	return tmp;
}
