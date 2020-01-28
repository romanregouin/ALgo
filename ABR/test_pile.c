#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"


//void afficher_pile(ppile_t p);

int main (int argc, char**argv)
{
	ppile_t p = creer_pile();
	//afficher_pile(p);
	printf("pile vide ? %d\n",pile_vide(p));
	printf("pile pleine ? %d\n",pile_pleine(p));
	/*pnoeud_t noeud = malloc(sizeof(noeud_t));
	noeud->cle = 5;
	noeud->fdroite=NULL;
	noeud->fgauche=NULL;
	empiler(p,noeud);
	afficher_pile(p);*/
}

/*void afficher_pile(ppile_t p){
	printf("sommet = %d\n",p->sommet);
	for (int i=0;i<p->sommet;i++){
		afficher_arbre(p->Tab[i],2);
	}
}
*/
