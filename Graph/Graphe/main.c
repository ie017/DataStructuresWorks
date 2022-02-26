#include <stdbool.h>
#include <stdio.h>
#include "Graphe.h"

int afficher_menu();

Liste File;
bool sommet[MAX_N];

// LISTE FUNCTIONS
Liste liste_vide()
{
  return NULL;
}

bool est_vide(Liste L){
  if (L == NULL)
    return true;
  return false;
}
int longueur(Liste L)
{
  if (est_vide(L)) return 0;

  int size = 0;
  Place cellule = L;
  while (cellule) {
    size++;
    cellule = cellule->suivant;
  }

  return size;
}

Place acces(Liste L, int position)
{
  if (position < 0 || position > longueur(L)) {
    printf("position invalide!\n");
    exit(-1);
  }

  if (position == 0) return L;

  Place ptr = L;
  int  i;
  for (i = 0; i < position - 1; i++) {
    ptr = ptr->suivant;
  }

  return ptr;
}

Liste inserer(Liste L, int position, element e)
{
  if (position < 0 || position > longueur(L) + 1) {
    printf("position non valide!\n");
    exit(-1);
  }

  Place cellule = malloc(sizeof(*cellule));
  cellule->valeur = e;
  cellule->suivant = NULL;

  if (position == 0) {
    cellule->suivant = L;
    L = cellule;
  } else {
    Place ptr = acces(L, position);

    cellule->suivant = ptr->suivant;
    ptr->suivant = cellule;
  }

  return L;
}

Liste supprimer(Liste L, int position)
{
  if (position < 0 || position > longueur(L)) {
    printf("position non valide!\n");
    exit(-1);
  }

  Place ptr = L;

  if (position == 0) {
    L = L->suivant;
  } else {
    Place pos = acces(L, position);
    ptr = pos->suivant;
    pos->suivant = ptr->suivant;
  }

  free(ptr);
  return L;
}

void afficher_liste(Liste L){
  if(L == NULL){
    printf("Liste Vide");
    exit(-1);
  }
  else{
    printf("[");
    while(L){
        printf(" %d ",L->valeur);
        L = L->suivant;
    }
    printf("]");
  }
  printf("\n");
}

element contenu(Liste liste, Place place)
{
  if (est_vide(liste)) {
    printf("Erreur: La liste est vide!\n");
    exit(-1);
  }

  return place->valeur;
}

// GRAPHE FUNCTIONS

GrapheL graphe_vide()
{
  GrapheL G = malloc(sizeof(*G));
  G->nb_sommet = 0;
  int  i;
  for (i = 0; i < MAX_N; i++) {
    G->liste_ad[i] = liste_vide();
  }

  return G;
}

bool est_sommet(int e1){
  if(sommet[e1] == false){
    return false;
  }
  return true;
}

void add_sommet(GrapheL *G,int e1){
  if(est_sommet(e1) == false){
    sommet[e1] = true;
    (*G)->nb_sommet++;
  }
}

void suppression_sommet(GrapheL *G,int e1){
   if(est_sommet(e1) == true){
    sommet[e1] = false;
    (*G)->nb_sommet--;
  }
}

void add_arc(GrapheL *G, int e1, int e2)
{
  if (G != NULL) {
    if(est_sommet(e1) == false){
        printf("sommet %d n'existe pas !!\n",e1);
    }else{
        if(est_sommet(e2) == false){
            printf("sommet %d n'existe pas !!\n",e2);
        }
        else{
            Liste L = (*G)->liste_ad[e1];
            (*G)->liste_ad[e1] = inserer(L, longueur(L), e2);
        }
    }
  }
}
void afficher_graphe(GrapheL *G){
   if (G != NULL){
      for(int i = 0;i < MAX_N;i++){
        if(est_sommet(i) == true){
            printf("Sommet(%d) -> ",i);
            afficher_liste((*G)->liste_ad[i]);
         }
      }
   }
}

void suppression_arc(GrapheL *G, int e1, int e2){
    if(G != NULL){
       if(est_sommet(e1) == false){
        printf("Sommet %d n'est pas inserer !!\n",e1);
        }
       else
        {
        bool supp = false;
        Liste L = (*G)->liste_ad[e1];
        int i = 1;
        while(supp != true || i < longueur(L)){
            if(e2 == contenu(L,acces(L,i))){
                (*G)->liste_ad[e1] = supprimer(L, i-1);
                supp = true;
                break;
            }
            i++;
        }
        if(supp == false)
            printf("L'arc deja supprimer !!\n");
        }
    }
}

void parcours_profondeur(GrapheL *G,int sommet){
   if(est_sommet(sommet) == true){
    if(atteints[sommet] == false){
       atteints[sommet] = true;
       printf(" %d ",sommet);
       Liste L = (*G)->liste_ad[sommet];
       while(L){
        parcours_profondeur(G,L->valeur);
        L = L->suivant;
       }
    }
   }
}

void parcours_largeur(GrapheL *G,int sommet){
    if(est_sommet(sommet) == true){
            if(atteints[sommet] == false){
            File = inserer(File,0,sommet);
            }
            if(!est_vide(File)){
            element element = contenu(File,acces(File,longueur(File)));
            File = supprimer(File,longueur(File)-1);
            atteints[element] = true;
            printf(" %d ",element);
            Liste L = (*G)->liste_ad[element];
            while(L){
               if(atteints[L->valeur] == false){
                    File = inserer(File,0,L->valeur);
                    atteints[L->valeur] = true;
               }
                L = L->suivant;
            }

         }
    }
    if(!est_vide(File)){
    parcours_largeur(G,contenu(File,acces(File,longueur(File))));
    }

}

int afficher_menu(){
    printf("1-Add Sommet\n2-Add arc\n3-suppression Sommet\n4-suppression d'arc\n5-Parcours en profondeur\n6-Parcours Largeur\n7-Quitter\n");
    int i = 0;
    printf("\nEnter votre choix !!\n");
    scanf("%d",&i);
    return i;
}

int main(){
  for(int i = 0;i < MAX_N;i++){
    sommet[i] = false;
  }
  GrapheL G = graphe_vide();
  int j = afficher_menu(&G);
  while(j != 7){
    if(j == 1){printf("Les sommets entre 0 et 49 !!\n");
             printf("Entrez le nombre des sommets\n");
             int e0;
             scanf("%d,",&e0);
             for(int i = 0;i < e0;i++){
                int s;
                printf("Add sommet nombre %d :\t",i+1);
                scanf("%d,",&s);
                add_sommet(&G,s);
             }
             j = afficher_menu(&G);
             }
    if(j == 2){printf("Les sommets entre 0 et 49 !!\n");
               printf("Entrez le nombre des arcs\n");
               int nbarcs;
             scanf("%d,",&nbarcs);
             for(int i = 0;i < nbarcs;i++){
             printf("arc %d :\n",i+1);
             printf("Predecesseur :\t");
             int e1,e2;
             scanf("%d",&e1);
             printf("\n");
             printf("Successeur :\t");
             scanf("%d",&e2);
             printf("\n");
             add_arc(&G,e1,e2);
             }
             j = afficher_menu(&G);
    }
    if(j == 3){printf("Les sommets entre 0 et 49 !!\n");
               printf("Entrez le nombre des sommets\n");
               int nb;
               scanf("%d,",&nb);
               for(int i = 0;i < nb;i++){
                int s1;
                printf("supp sommet nombre %d :\t",i+1);
                scanf("%d,",&s1);
                suppression_sommet(&G,s1);
             }
             j = afficher_menu(&G);
    }
    if(j == 4){printf("Les sommets entre 0 et 49 !!\n");
             printf("Entrez le nombre des arcs\n");
             int nbarcs2;
             scanf("%d,",&nbarcs2);
             for(int i = 0;i < nbarcs2;i++){
             printf("arc %d :\n",i+1);
             printf("Predecesseur :\t");
             int e3,e4;
             scanf("%d",&e3);
             printf("\n");
             printf("Successeur :\t");
             scanf("%d",&e4);
             printf("\n");
             suppression_arc(&G,e3,e4);
             }
             j = afficher_menu(&G);
    }
    if(j == 5){printf("Parcours en profondeur : \n");
             for(int i = 0;i < MAX_N;i++ ){
               atteints[i] = false;
             }
             for(int i = 0;i < MAX_N;i++ ){
                parcours_profondeur(&G,i);
             }
             printf("\n");
             j = afficher_menu(&G);
    }
    if(j == 6){printf("Parcours en Largeur : \n");
             for(int i = 0;i < MAX_N;i++ ){
               atteints[i] = false;
             }
             for(int i = 0;i < MAX_N;i++ ){
                parcours_largeur(&G,i);
             }
             printf("\n");
             j = afficher_menu(&G);
    }
    if(j == 7)
        break;
  }
  return 0;
}


