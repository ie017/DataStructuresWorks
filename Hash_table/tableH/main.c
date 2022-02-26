#include<stdio.h>
#include<stdlib.h>
#include "tableH.h"
#include<stdbool.h>

bool test(char *s){
    bool value = false;
    if(*s == ' '){
        value = true;
    }
    if(*s == '\n'){
        value = true;
    }
    if(*s == '.'){
        value = true;
    }
    if(*s == ','){
        value = true;
    }
    if(*s == '\0'){
        value = true;
    }
    return value;
}

int main(void){
    int sizetext;
    FILE *fichier = NULL;
    FILE *fichier1 = NULL;
    fichier1 = fopen("text.txt","r");
    fichier = fopen("Text.txt","r");
    fseek(fichier, 0, SEEK_END);
    sizetext = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);
    TableHachage table = cree_table_hachage(sizetext);
    TableHachage tableAlpha = cree_table_hachage(sizetext);
    if (fichier != NULL){
        char *str = (char*)malloc((sizetext+2)*sizeof(char));

        while(fgets(str,sizetext,fichier) != NULL)
        {   char *p;
            char *cp = (char*)malloc(sizetext*sizeof(char));
            int i = 0;
            for(p=str;*p;p++){
                if((test(p) == false)){
                    *(cp+i) = *p;
                    i++;
               }
               else{
                   if(test(cp) == false){
                       insere(table,cp,cp);
                       i = 0;
                       cp = malloc(sizetext*sizeof(char));
                   }

               }
            }

        }
    }
    fclose(fichier);
    if (fichier1 != NULL){
        char *str = (char*)malloc((sizetext+2)*sizeof(char));

        while(fgets(str,sizetext,fichier1) != NULL)
        {   char *p;
            char *cp = (char*)malloc(sizetext*sizeof(char));
            int i = 0;
            for(p=str;*p;p++){
                if((test(p) == false)){
                    *(cp+i) = *p;
                    i++;
               }
               else{
                   if(test(cp) == false){
                       insereAlpha(tableAlpha,cp,cp);
                       i = 0;
                       cp = malloc(sizetext*sizeof(char));
                   }

               }
            }

        }
    }
    fclose(fichier);
    printf("Les mots avec les frequences :\n");
    for(int i = 0;i < table->taille;i++){
        while(table->alveoles[i]){
            printf("%s , %d\n",table->alveoles[i]->valeur,table->alveoles[i]->freq);
            table->alveoles[i] = table->alveoles[i]->suivant;
        }
    }
    printf("\n\n");
    printf("Les mots avec l'ordre alphaetique :\n");
    for(int i = 0;i < table->taille;i++){
        while(tableAlpha->alveoles[i]){
            printf("%s , %d, %d\n",tableAlpha->alveoles[i]->valeur,tableAlpha->alveoles[i]->freq,i);
            tableAlpha->alveoles[i] = tableAlpha->alveoles[i]->suivant;
        }
    }
    return 0;
}

