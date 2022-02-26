#include<stdio.h>

typedef struct matrice{
   int ordre,dim1,dim2;
}Matrice;
int min(int table[],int size){
   int min = table[0];
   for(int i = 1;i <size;i++){
    if(table[i] < min){
        min = table[i];
    }
   }
   return min;

}
void mcmPD(int size,Matrice m[size+1],int result[size][size]){
  int dimensions[size+2];
  for(int i = 1;i < size+1;i++){
    result[i][i] = 0;
  }
  for(int i = 1;i <= size+1; i++){
    if(i==1){
        dimensions[i-1] = m[i-1].dim1;
    }
    else{
        if(i == size+1){
            dimensions[i-1] = m[i-1].dim2;
        }else{
            dimensions[i-1] = m[i].dim1;
        }
    }
  }

  for(int i = 1;i < size;i++){
        result[i][i+1] = dimensions[i-1]*dimensions[i]*dimensions[i+1];
    }
  for(int s = 2;s < size;s++){
        int values[s];
  for(int i = 1;i < size - s+1; i++){
        for(int j = 0;j < s;j++){
            values[j] = result[i][i+j]+result[i+j+1][i+s]+dimensions[i-1]*dimensions[i+j]*dimensions[i+s];
        }
        result[i][i+s] = min(values,s);
    }
  }

}
int main(){
 Matrice m0,m5,m2,m3,m4;
 m0.ordre = 0;m5.ordre = 1;m2.ordre = 2;m3.ordre =3;m4.ordre =4;
 m0.dim1 = 13;m5.dim1 = 13;m2.dim1 = 5;m3.dim1 =89;m4.dim1 =3;
 m0.dim2 = 0;m5.dim2 = 5;m2.dim2 = 89;m3.dim2 =3;m4.dim2 =34;
 Matrice m[5] = {m0,m5,m2,m3,m4};
 int result[4][4];
 mcmPD(4,m,result);
 printf("Multiplication chainée de matrices :\n\n");
 for(int i = 1;i < 5;i++){
    for(int j =i;j < 5;j++){
       printf("result[%d][%d] : %d\t",i,j,result[i][j]);
 }
 printf("\n");
 }
 return 0;
}
