#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int read_M1 (FILE *fp,double* matriz,int filas, int colum){
  char linea[1024];
  int contador = 0;
  while (fgets(linea,1024,fp) != NULL){
    char *aux = linea;
    double num2 = strtod(aux,&aux);
    while (num2 != 0){
    matriz[contador] = num2;
    contador++;
    num2 = strtod(aux,&aux);
    }            
 }   
  if(contador < colum*filas)
    return -3;
  fclose(fp);
  return 0;
}

int read_M2 (char* nombre,double* matriz,int filas, int colum, long pos){
   FILE *fp = fopen(nombre,"rb"); //Abro el archivo en la ultima posicion
   fseek(fp,pos,SEEK_SET); //Me posiciono al principio de la matriz
   int i = 0;
   double aux;
   while ((fread(&aux,sizeof(double),1,fp)) == 1){
     matriz[i] = aux;
     i++;
   }     
   if (i+1 < filas*colum)
     return -4;
   fclose(fp);
   return 0;
}
