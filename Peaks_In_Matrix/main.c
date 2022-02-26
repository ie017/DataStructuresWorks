#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 20

void picsColonnes(int Table[MAX][MAX],int col,int column,int median_ligne){
    int median_column = column;
      if(column <= col){
        if((median_column == col || Table[median_ligne][median_column] >= Table[median_ligne][median_column + 1]) && (median_column == 0 || Table[median_ligne][median_column - 1] <= Table[median_ligne][median_column])){
            printf("[%d][%d]: %d\n",median_ligne,median_column,Table[median_ligne][median_column]);
        }
      }
    }


void picsLignes(int Table[MAX][MAX],int firstL,int lignes,int lastCol,int colonnes,int i){
    int median_Lignes = (firstL+lignes)/2;
  if(firstL <= lignes){
    if((median_Lignes == i || Table[median_Lignes][colonnes] >= Table[median_Lignes + 1][colonnes]) && (median_Lignes == 0 || Table[median_Lignes - 1][colonnes] <= Table[median_Lignes][colonnes])){
        picsColonnes(Table,lastCol,colonnes,median_Lignes);
    }
    picsLignes(Table,firstL,median_Lignes-1,lastCol,colonnes,i);
    picsLignes(Table,median_Lignes+1,lignes,lastCol,colonnes,i);
    }

   }



int main(){
  int Matrice[MAX][MAX];
  int d1,d2;
  do{
    printf("Entrez dimension 1 de matrice :\n");
    scanf("%d",&d1);
    printf("Entrez dimension 2 de matrice :\n");
    scanf("%d",&d2);
  }while((d2<0 || d1<0) ||(d2>MAX || d1>MAX));

  for(int i = 0;i < d1;i++){
    for(int j = 0;j < d2;j++){
        printf("M[%d][%d] = \t",i,j);
        scanf("%d",&Matrice[i][j]);
  }
  }

  for(int i = 0;i < d2;i++){
       picsLignes(Matrice,0,d1-1,d2-1,i,d1-1);
  }

  }

