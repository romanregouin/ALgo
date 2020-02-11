#include <stdio.h>
#include <stdlib.h>

#include "abr.h"
#include "pile.h"


int egalite_arbre(Arbre_t a1, Arbre_t a2){
  if(a1==NULL && a2==NULL)return 1;
  else if(a1==NULL || a2==NULL)return 0;
  if(a1->cle!=a2->cle)return 0;
  return egalite_arbre(a1->fgauche,a2->fgauche)== egalite_arbre(a1->fdroite,a2->fdroite);
}




int main (int argc, char**argv)
{
  Arbre_t a ;

  if (argc != 2)
    {
      fprintf (stderr, "il manque le parametre nom de fichier\n") ;
      exit (-1) ;
    }

  a = lire_arbre ("arbre1") ;
  
  afficher_arbre (a,0) ;

  int h1,h2,succes=0;
  h1 =hauteur_arbre_nr(a);
  h2 = hauteur_arbre_r(a);
  if(h1!=h2){
    printf("Erreur les hauteurs sont différentes sur un meme arbre !\n");
  }else succes++;
  if(h1!=4){
    printf("Erreur les hauteurs sont différentes, elle devrait être de hauteur 4 mais ici %d !\n",h1);
  }else succes++;
  if(succes==2)printf("Succes fonction Hauteur !\n");
  else printf("Au moins une fonction hauteur n'est pas passé !\n");
  
  
  parcourir_arbre_largeur(a);
  printf("Succes fonction parcours largeur !\n"); // A verifier lors de l'affichage
  succes++;



  afficher_nombre_noeuds_par_niveau(a);
  printf("Succes fonction parcours largeur !\n"); // A verifier lors de l'affichage en copmparant a l'arbre
  succes++;



  h1=nombre_cles_arbre_r(a);
  h2=nombre_cles_arbre_nr(a);
   if(h1!=h2){
    printf("Erreur le nombre de clé est différent sur un meme arbre !\n");
  }else succes++;
  if(h1!=10){
    printf("Erreur le nombre de clé est pas le bon, il devrait y en avoir 10 mais on en compte %d !\n",h1);
  }else succes++;
  if(succes==6)printf("Succes fonction nombre_cles !\n");
  else printf("Au moins une fonction nombre_cles n'est pas passé !\n");
  


  h1=trouver_cle_min(a);
  if(h1==1){
    printf("Succes trouver_cle_min !\n");
    succes++;
  }
  else printf("Erreur sur trouver_cle_min !\n");


  printf("======================================\n");
  imprimer_liste_cle_triee_r(a);
  printf("\n-------------\n");
  imprimer_liste_cle_triee_nr(a);
  printf("Les deux affichages devrait être identique.\n");
  succes++;

  int err=0;
  if(arbre_plein(a)){
    printf("Erreur l'arbre n'est pas plein  !\n");
    err++;
  }
  if(arbre_parfait(a)){
    printf("Erreur l'arbre n'est pas parfait !\n");
    err++;
  }
  if(err==0){
    printf("Succes fonction arbre_plein et arbre_parfait !\n");
    succes++;
  }


  err=0;
  Arbre_t test=rechercher_cle_inf_arbre(a,11,NULL);
  if(test==NULL || test->cle!=10){
    printf("Erreur 1; ");
    err++;
  }
  test=rechercher_cle_inf_arbre(a,4,NULL);
  if(test==NULL || test->cle!=3){
    printf("Erreur 2; ");
    err++;
  }
  test=rechercher_cle_sup_arbre(a,4,NULL);
  if(test==NULL || test->cle!=5){
    printf("Erreur 3; ");
    err++;
  }
  test=rechercher_cle_sup_arbre(a,7,NULL);
  if(test==NULL || test->cle!=8){
    printf("Erreur 4; ");
    err++;
  }
  test=rechercher_cle_inf_arbre(a,7,NULL);
  if(test==NULL || test->cle!=6){
    printf("Erreur 5; ");
    err++;
  }
  test=rechercher_cle_sup_arbre(a,16,NULL);
  if(test!=NULL){
    printf("%d",test->cle);
    printf("Erreur 6; ");
    err++;
  }
  test=rechercher_cle_inf_arbre(a,16,NULL);
  if(test==NULL || test->cle!=15){
    printf("Erreur 7; ");
    err++;
  }
  test=rechercher_cle_inf_arbre(a,1,NULL);
  if(test!=NULL){
    printf("Erreur 8; ");
    err++;
  }
  test=rechercher_cle_sup_arbre(a,1,NULL);
  if(test==NULL || test->cle!=2){
    printf("Erreur 9; ");
    err++;
  }
  test=rechercher_cle_sup_arbre(a,0,NULL);
  if(test==NULL || test->cle!=1){
    printf("Erreur 9; ");
    err++;
  }
  test=rechercher_cle_inf_arbre(a,0,NULL);
  if(test!=NULL){
    printf("Erreur 9; ");
    err++;
  }
  printf("\n");
  if(err==0){
    succes++;
    printf("Succes fonction recherche_cle_inf et sup !\n");
  }else printf("Erreur: %d erreurs dans les tests des fonctions rechercher_cle_inf et sup !\n",err);



  Arbre_t b=lire_arbre("arbre2");
  Arbre_t tmp=union_deux_arbres(a,a);
  err=0;
  if(!egalite_arbre(a,tmp)){
    err++;
    printf("Err 1:arbre1/1;  ");
  }
  int err2=0;
  Arbre_t tmp2;
  tmp=union_deux_arbres(a,b);
  ppile_t p = creer_pile();
  empiler(p,tmp);
  while(!pile_vide(p)){
    tmp2 = depiler(p);
    if(tmp2!=NULL){
      if(rechercher_cle_arbre(a,tmp2->cle)==NULL && rechercher_cle_arbre(b,tmp2->cle)==NULL)err2++;
      empiler(p,tmp2->fdroite);
      empiler(p,tmp2->fgauche);
    }
  }

  if(err2>0){
    printf("Err2: Arbre1/2; ");
    err++;
  }

  err2=0;
  b=lire_arbre("arbre3");
  a=lire_arbre("arbre4");
  tmp=union_deux_arbres(a,b);
  empiler(p,tmp);
  while(!pile_vide(p)){
    tmp2 = depiler(p);
    if(tmp2!=NULL){
      if(rechercher_cle_arbre(a,tmp2->cle)==NULL && rechercher_cle_arbre(b,tmp2->cle)==NULL)err2++;
      empiler(p,tmp2->fdroite);
      empiler(p,tmp2->fgauche);
    }
  }



  if(err2>0){
    printf("Err3: Arbre3/4;  ");
    err++;
    printf("Err2");
  }



  
  printf("\n");
  if(err==0){
    succes++;
    printf("Succes fonction Union_arbre !\n");
  }else printf("Erreur: %d erreurs dans les tests des fonctions Union_arbre !\n",err);


  err=0;
  err2=0;
  b=lire_arbre("arbre3");
  a=lire_arbre("arbre4");
  tmp=intersection_deux_arbres(a,b);
  empiler(p,tmp);
  while(!pile_vide(p)){
    tmp2 = depiler(p);
    if(tmp2!=NULL){
      if(rechercher_cle_arbre(a,tmp2->cle)==NULL || rechercher_cle_arbre(b,tmp2->cle)==NULL)err2++;
      empiler(p,tmp2->fdroite);
      empiler(p,tmp2->fgauche);
    }
  }


  if(err2>0){
    printf("Err1: Arbre3/4;  ");
    err++;
  }


  err2=0;
  b=lire_arbre("arbre2");
  a=lire_arbre("arbre1");
  tmp=intersection_deux_arbres(a,b);
  empiler(p,tmp);
  while(!pile_vide(p)){
    tmp2 = depiler(p);
    if(tmp2!=NULL){
      if(rechercher_cle_arbre(a,tmp2->cle)==NULL || rechercher_cle_arbre(b,tmp2->cle)==NULL)err2++;
      empiler(p,tmp2->fdroite);
      empiler(p,tmp2->fgauche);
    }
  }


  if(err2>0){
    printf("Err1: Arbre1/2;  ");
    err++;
  }



  printf("\n");
  if(err==0){
    succes++;
    printf("Succes fonction Intersection_arbre !\n");
  }else printf("Erreur: %d erreurs dans les tests des fonctions Intersection_arbre !\n",err);


  //CE TEST NE MARCHE QUE SI LARBRE A EST LE FICHIER arbre1.txt!!
  err=0;
  b=lire_arbre("test_delet_cle");
  afficher_arbre(a,0);
  afficher_arbre(b,0);
  a=detruire_cle_arbre(a,8);
  if(!egalite_arbre(a,b))err++;
  else succes++;
  afficher_arbre(a,0);

  Arbre_t c=lire_arbre("arbre3");
  if(!inclusion_arbre(a,b))err++;
  else if (inclusion_arbre(a,c))err++;
  else succes++;
  printf("\nPassé %d/14 Tests !\n",succes);
  //TEST DES AVLS
}
