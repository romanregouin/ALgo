#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "abr.h"
#include "pile.h"

int main (int argc, char**argv)
{
	ppile_t p = creer_pile();
	assert(pile_vide(p));
	assert(!pile_pleine(p));
	assert(p->sommet==0);
	
	/* empilements successifs */
	for (int i=0; i<MAX_PILE_SIZE-1; i++){
		pnoeud_t noeud = malloc(sizeof(noeud_t));
		noeud->cle = i;
		empiler(p,noeud);
		assert(!pile_vide(p));
		assert(!pile_pleine(p));
		assert(p->sommet==i+1);
		assert(p->Tab[i]==noeud);
	}
	//dernier empilement : apres ça la pile est pleine
	pnoeud_t noeud = malloc(sizeof(noeud_t));
	noeud->cle = MAX_PILE_SIZE-1;
	empiler(p,noeud);
	assert(!pile_vide(p));
	assert(pile_pleine(p));
	assert(p->sommet==MAX_PILE_SIZE);
	assert(p->Tab[MAX_PILE_SIZE-1]==noeud);
	
	assert(empiler(p,noeud)==1); //erreur lors de l'empilement car pile pleine
	
	/* depilements successifs */
	for (int i=MAX_PILE_SIZE-1;i>0;i--){
		pnoeud_t elem = depiler(p);
		assert(!pile_pleine(p));
		assert(!pile_vide(p));
		assert(elem->cle==i);
		assert(p->sommet==i);
		free(elem);
	}
	
	//dernier depilement : apres ça la pile est vide
	pnoeud_t elem = depiler(p);
	assert(!pile_pleine(p));
	assert(pile_vide(p));
	assert(elem->cle==0);
	assert(p->sommet==0);
	free(elem);
	
	assert(depiler(p)==NULL); //depilement sur une pile vide
	
}

