#include "M1M2.h"
#include "matrix.h"
#include "list.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>


int8_t read_matrix (char* nombre,matrix_t* mc) {
   FILE* fp = fopen(nombre,"r");
   if (fp == NULL) return -1;
   int colum = 0, fila = 0;
   char modo[1024];
   char linea [1024];
   double* matriz;  
   fscanf(fp,"%s",modo);   //Leo la primer linea
   if ((strcmp(modo,"M1") != 0) && (strcmp(modo,"M2") != 0)){
      fclose(fp);
      return -1; 
   }
   fseek(fp,1,SEEK_CUR); //Posiciono a la siguiente linea
   fgets(linea,1024,fp);
   while (linea[0] == '#')  //Leo las lineas que empiezan con #
      fgets(linea,1024,fp);
   int num = sscanf(linea,"%d %d",&fila,&colum); 
   if (num != 2){
     fclose(fp); 
     return -2;
   }
   matriz = malloc(sizeof(double)*fila*colum);
   long pos = ftell(fp); //Guardo la posicion actual para mas adelante
   int8_t retorno;
   if (strcmp(modo,"M1") == 0)
      retorno = read_M1(fp,matriz,fila,colum);
   else
      retorno = read_M2(nombre,matriz,fila,colum,pos);
   if (retorno != 0){
     free(mc->matriz);
     return retorno;
   }
   mc->fila = fila;
   mc->colum = colum;
   mc->matriz = matriz;
  return 0;
}

int8_t write_matrix (char* nombre,matrix_t* mc) {
   char linea[1024];
   char modo[3];
   FILE* fp = fopen(nombre,"w");
   puts ("Formato de guardado de archivo (M1,M2)");
   scanf("%s",modo);
   if ((strcmp(modo,"M1") != 0) && (strcmp(modo,"M2") != 0)){
      fclose(fp);
      puts("Error formato no admitido");
      return -1; 
   }
   fprintf(fp,"%s\n",modo);
   puts("Ingrese comentarios al archivo, para finalizar coloque  0 unicamente");
   scanf("%s",linea);
   while((strcmp(linea,"0") != 0)){
      fprintf(fp,"#%s\n",linea);
      scanf("%s",linea);
   }
   fprintf (fp,"%d %d\n",mc->fila,mc->colum);
   long pos = ftell(fp);
   if (strcmp(modo,"M1") == 0){
      for (int i = 0;i < mc->fila*mc->colum;i++)
        fprintf (fp,"%lf ",mc->matriz[i]);
   }
   else {
     fclose(fp);
     fp = fopen(nombre,"r+b");
     fseek(fp,pos,SEEK_SET);
     fwrite(mc->matriz,sizeof(double),mc->colum*mc->fila,fp);
   }
  fclose(fp); 
  return 0;
}
int8_t dup_matrix(const matrix_t *m_src, matrix_t *m_dst) { 
   m_dst->colum =m_src->colum;
   m_dst->fila = m_src->fila;
   m_dst->matriz = malloc(sizeof(double)*m_src->colum*m_src->fila);
   int i = 0;
   for (i = 0;i < m_src->colum*m_src->fila;i++){
     m_dst->matriz[i] = m_src->matriz[i];
   }
   if (i+1 < m_src->colum*m_src->fila){
     free(m_dst->matriz);
     return -5;
   }
   return 0;
}


int8_t sum_inplace (const matrix_t *ma, matrix_t *mb){
  if ((ma->colum == mb->colum) && (ma->fila == mb->fila)){
     for (int i = 0;i < ma->fila*ma->colum;i++){
        double aux = mb->matriz[i];
        mb->matriz[i] = mb->matriz[i] + ma->matriz[i];
        if (mb->matriz[i] != aux + ma->matriz[i]){
           return -6;
        } 
     }
  }
  else
    return -7;
return 0;
}



int8_t sum (const matrix_t *ma,const matrix_t *mb,matrix_t *mc) {
  if ((ma->colum == mb->colum) && (ma->fila == mb->fila)){
     mc->matriz = malloc(sizeof(double)*ma->colum*ma->fila);
     for (int i = 0;i < ma->fila*ma->colum;i++){
        mc->matriz[i] = mb->matriz[i] + ma->matriz[i];
     }
  }
  else {
    return -9;
  }
  mc->colum = ma->colum;
  mc->fila = ma->fila;
  return 0;
}

int8_t mult_scalar_inplace (double a,matrix_t *mc){
     for (int i = 0;i < mc->fila * mc->colum;i++){
        double aux = mc->matriz[i];
        mc->matriz[i] = aux*a; 
        if (mc->matriz[i] != aux*a){ //Si la mult esta fuera de rango
           free(mc->matriz);
           return -10;
        } 
     }
return 0;
}
int8_t mult_scalar(double a, const matrix_t *mb, matrix_t *mc){
   mc->colum = mb->colum;
   mc->fila = mb->fila;
   mc->matriz = malloc(sizeof(double) * mc->fila * mc->colum);
   for (int i = 0;i < mb->fila * mb->colum; i++){
        mc->matriz[i] = mb->matriz[i] * a; 
        if (mc->matriz[i] != mb->matriz[i] * a){ //Si la mult esta fuera de rango
           free(mc->matriz);
           return -11;
        } 
     }
 return 0;
}


int8_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t *mc){
   if (ma->colum == mb->fila){  //Propiedad de multiplicacion de matrices
     mc->fila = ma->fila;
     mc->colum = mb->colum;
     mc->matriz = malloc(mc->fila*mc->colum*sizeof(double));
     int pos = 0;
     for (int i = 0; i < ma->fila;i++){
       for(int j = 0; j < mb->colum;j++){
         double aux = 0;
         for (int k = 0; k < ma->colum;k++){
           aux += ma->matriz[(i*ma->colum) + k] * mb->matriz[(k*mb->colum) + j];
         }
         mc->matriz[pos] = aux;
         pos++;
       } 
     }
     }
   else
     return -12;
   return 0;
   }

int8_t idty_matrix (unsigned int n, matrix_t *mc){
   mc->colum = n;
   mc->fila = n;
   mc->matriz = calloc(sizeof(double),n*n);
   for (int i = 0;i < n;i++){
      mc->matriz[(i*n) + i] = 1;
   }
   return 0;
}
int8_t null_matrix (unsigned int n, matrix_t *mc){
   mc->colum = n;
   mc->fila = n;
   mc->matriz = calloc(sizeof(double),n*n);
   return 0;
}
int8_t create_and_fill_matrix (unsigned int rows, unsigned int cols,double a, matrix_t *mc){
   mc->colum = cols;
   mc->fila = rows;
   mc->matriz = calloc(sizeof(double),rows*cols);
   for (int i = 0;i < rows*cols;i++){
      mc->matriz[i] = a;
   }
   return 0;
}

unsigned int get_rows (const matrix_t *ma){
   return ma->fila;
}

unsigned int get_cols (const matrix_t *ma){
   return ma->colum;
}
int8_t get_row (unsigned int pos, const matrix_t *ma, lista_t *l){
  if ((ma->fila < pos) || (pos <= 0)) return -13;
  unsigned int fila = pos - 1;
  lista_inicializar(l);
  for (int i = 0;i < ma->colum;i++){
     double aux;
     aux = ma->matriz[(fila*ma->colum)+i];
    lista_agregarAtras(l,aux);
  }
  return 0;
}

int8_t get_col (unsigned int pos, const matrix_t *ma, lista_t *l){
   if ((ma->colum < pos) || (pos <= 0)) return -14;
  unsigned int colum = pos - 1;
  lista_inicializar(l);
  for (int i = 0;i < ma->fila;i++){
     double aux;
     aux = ma->matriz[(ma->colum*i)+colum];
    lista_agregarAtras(l,aux);
  
  }
  return 0;
}

int8_t matrix2list (const matrix_t *ma, lista_t *l){
   for (int i = 0; i < ma->colum*ma->fila;i++){
      lista_agregarAtras(l,ma->matriz[i]);
   }
   return 0;
}
int8_t resize_matrix(unsigned int newrows, unsigned int newcols,matrix_t *ma){
   if ((newcols != ma->colum) || (newrows != ma->fila)){
      ma->matriz = realloc(ma->matriz,sizeof(double)*newcols*newrows);
      ma->colum = newcols;
      ma->fila = newrows;
   }
   return 0;
}
int8_t set_elem_matrix(unsigned int row, unsigned int col,double value, matrix_t* mc){
  int unsigned colum = col-1;
  int unsigned filas = row-1;
  if ((mc->colum >= col) && (mc->fila >= row)){
    mc->matriz[(filas*mc->colum)+colum] = value;
  }
  else
     return -15;
  return 0;
}


int8_t get_elem_matrix(unsigned int row, unsigned int col,double *value,const matrix_t* mc){
   int unsigned colum = col-1;
   int unsigned filas = row-1;
   if ((mc->colum >= col) && (mc->fila >= row)){
    *value = mc->matriz[(filas*mc->colum)+colum];
  }
  else
     return -16;
  return 0;
}

int cmp_matrix (const matrix_t *ma,const matrix_t *mb){   
   if ((ma->colum == mb->colum) && (ma->fila == mb->fila)){
      for(int i = 0;i < ma->colum*ma->fila;i++){
         if (ma->matriz[i] != mb->matriz[i])
            return 0;
      }
   return 1;   
    }
   else
     return 0;
}
   
int8_t free_matrix (matrix_t *m) {
   free(m->matriz);
   return 0;
}
