#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define MAX 3
typedef int element;

typedef struct noeud{
  int nbrCles;
  element cles[MAX];
  struct noeud *sousArbres[MAX + 1];
} Noeud, *PNoeud;

typedef PNoeud ArbreB;

PNoeud creerNoeud(element e){
  PNoeud noeud = (PNoeud)malloc(sizeof(Noeud));
  noeud->cles[0] = e;
  noeud->nbrCles = 1;
  noeud->sousArbres[0] = NULL;
  noeud->sousArbres[1] = NULL;
  return noeud;
}

bool est_vide(ArbreB AB){
  return AB == NULL;
}


ArbreB createArbreB(PNoeud p,ArbreB enfant1,ArbreB enfant2){
  if(p == NULL){
      return NULL;
  }else{
    p->sousArbres[0] = enfant1;
    p->sousArbres[1] = enfant2;
    return p;
  }
}

bool recherche(ArbreB AB,element e){
  if(est_vide(AB) == true){
    return false;
  }
    if(e < (AB->cles[0])){
        return recherche(AB->sousArbres[0],e);
    }
    else{if(e > (AB->cles[AB->nbrCles - 1])){
            return recherche(AB->sousArbres[AB->nbrCles],e);
        }
        else{
            bool estpresent;
            ArbreB sArbre;
            int pre,der,median;
            pre = 0;
            der = AB->nbrCles - 1;
            while(pre < der){
             median = (pre + der)/2;
             if(AB->cles[median] >= e){
               der = median;
             }
             else{
               pre = median+1;
             }
             }
             if(AB->cles[pre] == e){
                  estpresent = true;
                  sArbre = NULL;
             }
            else{
                  estpresent = false;
                  sArbre = AB->sousArbres[pre];
            }
            if(estpresent == true){
                return true;
            }
            else{
                return recherche(sArbre,e);
            }
        }
    }

  }


int position(ArbreB AB,element e){
   int i;
   if(e <= AB->cles[0]){
    i = 0;
   }else{
    if(e >= AB->cles[AB->nbrCles - 1]){
        i = AB->nbrCles;
    }else{
        for(int j = 1;j < AB->nbrCles - 1;j++){
            if(e >= AB->cles[j] && e <= AB->cles[j+1]){
                i = j+1;
                break;
            }
        }
    }
   }
   return i;
}
bool estFeuille(ArbreB AB){
 if(est_vide(AB) == true){
    return false;
 }else{
    for(int j = 0;j < AB->nbrCles + 1;j++){
        if(AB->sousArbres[j] != NULL){
            return false;
        }
    }
    return true;
 }
}

ArbreB insererUneCleDansNoeud(ArbreB AB,element e,int pos){
  AB->nbrCles++;
  for(int i = AB->nbrCles - 1;i > pos;i--){
    AB->cles[i] = AB->cles[i-1];
  }
  AB->sousArbres[AB->nbrCles] = NULL;
  AB->cles[pos] = e;
  return AB;
}

ArbreB insererUnArbreDansNoeud(ArbreB p,ArbreB AB,int position){
  /*p = insererUneCleDansNoeud(p,AB->cles[0],position);
  for(int i = p->nbrCles + 1;i > position+1;i--){
    p->sousArbres[i] = AB->sousArbres[i-1];
  }*/
  p = insererUneCleDansNoeud(p,AB->cles[0],position);
  p->sousArbres[position + 1] = AB->sousArbres[1];
  p->sousArbres[position] = AB->sousArbres[0];


  /*p->sousArbres[position + 1] = AB->sousArbres[1];
  p->sousArbres[position] = AB->sousArbres[0];*/
  return p;

}

ArbreB eclatement(ArbreB AB,int ordre){
  if(AB->nbrCles > 2*ordre){
  int pre,der,median;
  pre = 0;
  der = AB->nbrCles - 1;
  median = (pre + der)/2;
  PNoeud enfant1 = creerNoeud(AB->cles[0]);
  PNoeud enfant2 = creerNoeud(AB->cles[AB->nbrCles-1]);
  enfant1->sousArbres[0] = AB->sousArbres[0];
  for(int i = 1;i < median;i++){
  enfant1 = insererUneCleDansNoeud(enfant1,AB->cles[i],i);
  enfant1->sousArbres[i] = AB->sousArbres[i];
  }
  enfant1->sousArbres[median] = AB->sousArbres[median];
  enfant2->sousArbres[0] = AB->sousArbres[median + 1];
  for(int i = median + 1;i < AB->nbrCles - 1;i++){
  enfant2 = insererUneCleDansNoeud(enfant2,AB->cles[i],i);
  enfant2->sousArbres[i - median] = AB->sousArbres[i+1];
  }
  enfant2->sousArbres[median] = AB->sousArbres[AB->nbrCles];
  ArbreB res = createArbreB(creerNoeud(AB->cles[median]),enfant1,enfant2);
  return res;
  }
}

ArbreB insertion(ArbreB AB,element e,int ordre){
   if(est_vide(AB) == true){
     return creerNoeud(e);
   }
   else{
     int pos = position(AB,e);
     if(estFeuille(AB)){
       AB = insererUneCleDansNoeud(AB,e,pos);
       if(AB->nbrCles <= 2*ordre){
        return AB;
       }else{
        return eclatement(AB,ordre);
       }
     }else{
       ArbreB sArbre = AB->sousArbres[pos];
       ArbreB NV = insertion(sArbre,e,ordre);
       if(NV == sArbre){
        return AB;
       }else{
        AB = insererUnArbreDansNoeud(AB,NV,pos);
        if(AB->nbrCles <= 2*ordre){
            return AB;
        }else{
            return eclatement(AB,ordre);
        }
       }
     }
   }
}
