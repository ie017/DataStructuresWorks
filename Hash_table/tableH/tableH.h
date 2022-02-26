#include<stdbool.h>
#define MAX 15
typedef struct cellule{
 char cle[MAX];
 char valeur[MAX];
 int freq;
 struct cellule *suivant;
}Cellule;

typedef Cellule *Liste;
typedef Cellule *Place;

Liste insererListe(Liste , int ,Liste );
Place acces(Liste , int );

typedef struct tableH{
 int taille;
 Liste *alveoles;
}TableH;

typedef TableH *TableHachage;

int hachage(TableHachage table, char *cle){
int codeh = 0;
for (cle; *cle; cle++){
        codeh += *cle;
}
return (codeh % table->taille);
}

TableHachage cree_table_hachage(int taille) {
int i;
TableHachage table = (TableHachage)malloc(sizeof(TableH));
table->taille = taille;
table->alveoles = (Liste*)malloc(table->taille * sizeof(Liste));
for (i = 0; i < table->taille; i++){
    table->alveoles[i] = NULL;
}

return table;
}

void insere(TableHachage table, char *cle, char* valeur) {
int codeh;
Liste liste = NULL;
codeh = hachage(table, cle);
liste = table->alveoles[codeh];
while (liste) {
if (strcmp(liste->cle, cle) == 0){
  liste->freq++;
  break;
}
liste = liste->suivant;
}
if (liste == NULL) {
liste = (Liste)malloc(sizeof(Cellule));
strcpy(liste->cle, cle);
strcpy(liste->valeur,valeur);
liste->freq = 1;
liste->suivant = table->alveoles[codeh];
table->alveoles[codeh] = liste;
}
}
int recherche(TableHachage table, char *cle, char *valeur){
Liste liste = table->alveoles[hachage(table, cle)];
for (; liste; liste = liste->suivant)
if (strcmp(cle, liste->cle) == 0) {
strcpy(valeur,liste->valeur);
return 1;
}
return 0;
}

void supprime(TableHachage table, char *cle) {
int codeh;
Liste liste, *precedent;
codeh = hachage(table, cle);
liste = table->alveoles[codeh];
precedent = &table->alveoles[codeh];
for (; liste; precedent = &liste->suivant, liste = liste->suivant){
   if (strcmp(cle, liste->cle) == 0) {
   *precedent = liste->suivant;
   free(liste);
   }
}
}

int hachageAlpha(TableHachage table, char *cle){
int codeh = 0;
codeh += *cle;
return (codeh % table->taille);
}

void insereAlpha(TableHachage table, char *cle, char* valeur) {
int codeh;
Liste liste = NULL;
codeh = hachageAlpha(table, cle);
liste = table->alveoles[codeh];
bool test = false;
while(liste) {
test = true;
if (strcmp(liste->valeur, valeur) == 0){
  liste->freq++;
  break;
}
liste = liste->suivant;
}

if (liste == NULL && test == false) {
liste = (Liste)malloc(sizeof(Cellule));
strcpy(liste->cle, cle);
strcpy(liste->valeur,valeur);
liste->freq = 1;
liste->suivant = table->alveoles[codeh];
table->alveoles[codeh] = liste;
}else{
   if(liste == NULL && test == true){
       liste = (Liste)malloc(sizeof(Cellule));
       strcpy(liste->cle, cle);
       strcpy(liste->valeur,valeur);
       liste->freq = 1;
       Liste liste2 = NULL;
       Liste suivant = NULL;
       liste2 = table->alveoles[codeh];
       suivant = liste2->suivant;
       if(strcmp(liste2->valeur, valeur) >= 0){
         liste->suivant = table->alveoles[codeh];
         table->alveoles[codeh] = liste;
       }else{
          int i = 1;
          while(suivant){
            if (strcmp(liste2->valeur, valeur) <= 0 && strcmp(suivant->valeur, valeur) >= 0){
              break;
            }
           liste2 = liste2->suivant;
           suivant = liste2->suivant;
           i++;
          }
         table->alveoles[codeh] = insererListe(table->alveoles[codeh],i,liste);
      }
   }
}
}

Liste insererListe(Liste Lst, int position,Liste l){
    Place ptr = acces(Lst, position);
    l->suivant = ptr->suivant;
    ptr->suivant = l;
return Lst;
}

Place acces(Liste L, int position)
{
  Place ptr = L;
  int  i;
  for (i = 0; i < position - 1; i++) {
    ptr = ptr->suivant;
  }

  return ptr;
}
