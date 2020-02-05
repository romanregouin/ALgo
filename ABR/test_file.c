#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "abr.h"
#include "file.h"

int main (int argc, char**argv)
{
	pfile_t f = creer_file();
	assert(file_vide(f));
	assert(!file_pleine(f));
	assert(f->tete==-1);
	assert(f->queue==0);
	
	/* enfilements successifs */
	for (int i=0; i<MAX_FILE_SIZE-1; i++){
		pnoeud_t noeud = malloc(sizeof(noeud_t));
		noeud->cle = i;
		enfiler(f,noeud);
		assert(!file_vide(f));
		assert(!file_pleine(f));
		assert(f->tete==0);
		assert(f->queue==i+1);
		assert(f->Tab[i]==noeud);
	}
	//dernier enfilement : apres ça la file est pleine
	pnoeud_t noeud = malloc(sizeof(noeud_t));
	noeud->cle = MAX_FILE_SIZE-1;
	enfiler(f,noeud);
	assert(!file_vide(f));
	assert(file_pleine(f));
	assert(f->tete==0);
	assert(f->queue==0);
	assert(f->Tab[MAX_FILE_SIZE-1]==noeud);
	
	assert(enfiler(f,noeud)==1); //erreur lors de l'enfilement car file pleine
	
	/* verification du caractère cyclique de la file */
	// defilement de quelques elements
	for (int i=0; i < 5;i++){
		pnoeud_t elem = defiler(f);
		assert(!file_pleine(f));
		assert(!file_vide(f));
		assert(elem->cle==i);
		assert(f->tete==i+1);
		assert(f->queue==0);
		free(elem);
	}
	
	//nouveaux enfilements
	for (int i=0; i<4; i++){
		pnoeud_t noeud = malloc(sizeof(noeud_t));
		noeud->cle = i;
		enfiler(f,noeud);
		assert(!file_vide(f));
		assert(!file_pleine(f));
		assert(f->tete==5);
		assert(f->queue==i+1);
		assert(f->Tab[i]==noeud);
	}
	
	pnoeud_t noeud2 = malloc(sizeof(noeud_t));
	noeud2->cle = 4;
	enfiler(f,noeud2);
	assert(!file_vide(f));
	assert(file_pleine(f));
	assert(f->tete==5);
	assert(f->queue==5);
	assert(f->Tab[4]==noeud2);
	
	/* defilements successifs */
	for (int i=0; i < MAX_FILE_SIZE-1;i++){
		pnoeud_t elem = defiler(f);
		assert(!file_pleine(f));
		assert(!file_vide(f));
		assert(f->tete!=-1);
		assert(f->queue==5);
		free(elem);
	}
	
	//dernier defilement : apres ça la file est vide
	pnoeud_t elem = defiler(f);
	assert(!file_pleine(f));
	assert(file_vide(f));
	assert(f->tete==-1);
	assert(f->queue==5);
	free(elem);
	
	assert(defiler(f)==NULL); //defilement sur une file vide

}

