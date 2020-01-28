#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"


void afficher_pile(ppile_t p);

int main (int argc, char**argv)
{
	ppile_t p = creer_pile();
	afficher_pile(p);
	printf("sommet %d\n",p->sommet);
	printf("pile vide ? %d\n",pile_vide(p));
	printf("pile pleine ? %d\n",pile_pleine(p));
	pnoeud_t noeud = malloc(sizeof(noeud_t));
	noeud->cle = 5;
	noeud->fdroite=NULL;
	noeud->fgauche=NULL;
	for (int i=0;i<5;i++){
		empiler(p,noeud);
		printf("sommet %d\n",p->sommet);
		printf("pile vide ? %d\n",pile_vide(p));
		printf("pile pleine ? %d\n",pile_pleine(p));
		afficher_pile(p);
		
	}
	empiler(p,noeud);
	for (int i=0;i<4;i++){
		depiler(p);
		printf("sommet %d\n",p->sommet);
		printf("pile vide ? %d\n",pile_vide(p));
		printf("pile pleine ? %d\n",pile_pleine(p));
		afficher_pile(p);
		
	}
	depiler(p);
	afficher_pile(p);
}

void afficher_pile(ppile_t p){
	printf("sommet = %d\n",p->sommet);
	for (int i=0;i<p->sommet;i++){
		afficher_arbre(p->Tab[i],0);
	}
	printf("fin_pile\n");
}

