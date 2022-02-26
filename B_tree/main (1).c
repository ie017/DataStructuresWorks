/******************************************************************************

                            Online C Compiler.
                Code, Compile, Run and Debug C program online.
Write your code in this editor and press "Run" button to compile and execute it.

*******************************************************************************/
#include <stdbool.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "arbreBR.h"
bool test(char *);
int i = 0;
Arbre_binaireR Ajoute(Arbre_binaireR,char *);
Arbre_binaireR arbre_vide(void);
mot afficheInfixe(Arbre_binaireR);
Arbre_binaireR AG,AD;
Arbre_binaireR Add(Arbre_binaireR, char *, freq);
Arbre_binaireR AjouteParFreq(Arbre_binaireR,Arbre_binaireR);
void AfficheInfixe(Arbre_binaireR);

int main(int argc, char const *argv[]){
    int r;int position;
    int sizetext;
    bool value = false;
    Arbre_binaireR R = arbre_vide();
    Arbre_binaireR Rfreq = arbre_vide();
    FILE *fichier = NULL;
    fichier = fopen("text2.txt","r");
    fseek(fichier, 0, SEEK_END);
    sizetext = ftell(fichier);
    fseek(fichier, 0, SEEK_SET);
    mot T = (mot)malloc(sizeof(PNoeud));
    mot G = (mot)malloc(sizeof(PNoeud));
    if (fichier != NULL){
        char *str = (char*)malloc((sizetext+2)*sizeof(char));
        
        while(fgets(str,sizetext,fichier) != NULL)
        {  
            char *p;
            char *cp = (char*)malloc(sizetext*sizeof(char));
            int i = 0;
            for(p=str;*p;p++){
                if((test(p) == false)){
                    *(cp+i) = *p;
                    i++;
               }
               else{
                   if(test(cp) == false){
                       R = Ajoute(R,cp);
                       i = 0;
                       cp = malloc(sizetext*sizeof(char));
                   }
               
               }
            }
            
        }
        printf("Affichage par ordre alpha :\n");
        AfficheInfixe(R);
        printf("Affichage par freq :\n");
        Rfreq = AjouteParFreq(R,Rfreq);
        AfficheInfixe(Rfreq);
    }
    fclose(fichier);
    return 0;
    
}

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
Arbre_binaireR Ajoute(Arbre_binaireR R, char *e){

    if (R == NULL)
    {   R = creerNoeud(e);
        R = construireArbre(NULL,NULL,R);
    }
    else{

                if (strcmp((R->str),e) == 0)
        {
            R->f++;
        }
        else{
            if (strcmp((R->str),e) < 0)
            {
                R->fd = Ajoute(R->fd,e);
            }
            else{
                R->fg = Ajoute(R->fg,e);
            }
        }
    }
    
    return R;
    
}

Arbre_binaireR arbre_vide(){
    return NULL;
}
void AfficheInfixe(Arbre_binaireR A){
    int i = 0;
	if(A){
		AfficheInfixe(A->fg);
		printf("%s , %d\n",A->str,A->f);
		AfficheInfixe(A->fd);
	}
}
Arbre_binaireR AjouteParFreq(Arbre_binaireR R, Arbre_binaireR NV){
    if (R == NULL){
        return NULL;
    }
    else{
        NV = Add(NV,R->str,R->f);
        if(R->fd != NULL){
            NV = AjouteParFreq(R->fd, NV);
        }
        if(R->fg != NULL){
            NV = AjouteParFreq(R->fg, NV);
        }
    }
    return NV;
}
Arbre_binaireR Add(Arbre_binaireR R,char *s, freq f){
    if (R == NULL)
    {   R = CreerNoeud(s,f);
        R = construireArbre(NULL,NULL,R);
    }
    else{
            if (f <= R->f)
            {
                R->fg = Add(R->fg,s,f);
            }
            else{
                
                R->fd = Add(R->fd,s,f);
            }
    }
    
    return R;
}
