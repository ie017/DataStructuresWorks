#include<stdio.h>
#include<stdlib.h>
#include"ArbreB.h"

int main(){
 ArbreB AB = createArbreB(NULL,NULL,NULL);
 AB = insertion(AB,20,1);
 AB = insertion(AB,40,1);
 AB = insertion(AB,60,1);
 AB = insertion(AB,43,1);
 AB = insertion(AB,80,1);
 AB = insertion(AB,90,1);
 AB = insertion(AB,100,1);
 AB = insertion(AB,200,1);
 AB = insertion(AB,95,1);
 bool value = recherche(AB,200);
 printf("%d , %d",AB->sousArbres[1]->sousArbres[2]->cles[0],value);
 return 0;
}
