#ifndef GRAPHE_H
#define GRAPHE_H

#include <stdbool.h>
#define MAX_N 50

//Liste

typedef int element;

typedef struct cellule
{
  element valeur;
  struct cellule *suivant;
} cellule;

typedef cellule* Liste;   //  Pointeur sur une cellule
typedef cellule* Place;   //  Adresse cellule

Liste liste_vide();
int longueur(Liste);
Liste inserer(Liste, int, element);
Liste supprimer(Liste, int);
Place acces(Liste, int);
bool est_vide(Liste);
void afficher_liste(Liste);
element contenu(Liste, Place);

//Graphe

typedef struct graphe {
  int nb_sommet;                // Le nombre des noeuds
  Liste liste_ad[MAX_N];   // La liste d'adjacence
} Graphe;

typedef Graphe *GrapheL;

// D�finir un type Tableau des bool�ens de taille MAX_N
typedef bool value[MAX_N];

// Variable globale
value atteints;          // Tableau des noeuds d�j� visit�


GrapheL graphe_vide();
void add_sommet(GrapheL*,int );
void suppression_sommet(GrapheL*,int );
void add_arc(GrapheL*, int, int);
void suppression_arc(GrapheL*, int, int);
bool est_sommet(int);
void parcours_profondeur(GrapheL*, int);
void parcours_largeur(GrapheL*, int);
void afficher_graphe(GrapheL*);

#endif
