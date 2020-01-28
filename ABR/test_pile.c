#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"

void afficher_pile(ppile_t p){
	//printf("sommet = %d\n",p->sommet);
	for (int i=0;i<p->sommet;i++){
		afficher_arbre(p->Tab[i],0);
	}
	printf("fin_pile\n");
}


int main (int argc, char**argv)
{
	ppile_t p = creer_pile();
	afficher_pile(p);
	printf("\n\n\n\n");
	pnoeud_t noeud = malloc(sizeof(noeud_t));
	noeud->cle = 5;
	noeud->fdroite=NULL;
	noeud->fgauche=NULL;
	for (int i=0;i<5;i++){
		empiler(p,noeud);
		afficher_pile(p);
		printf("\n\n\n\n");
		
	}
	empiler(p,noeud);
	printf("On a passé les empiler \n\n");
	while(!pile_vide(p)){
		depiler(p);
		printf("sommet %d\n",p->sommet);
		printf("pile vide ? %d\n",pile_vide(p));
		printf("pile pleine ? %d\n",pile_pleine(p));
		printf("\n\n\n\n");
		//afficher_pile(p);
		printf("\n\n\n\n");
		
	}
	depiler(p);
	afficher_pile(p);
	printf("\n\n\n\n");
}

