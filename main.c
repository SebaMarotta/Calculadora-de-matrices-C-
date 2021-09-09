#include "matrix.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main (int argc,char **argv){
enum operaciones {duplicar = 10,sumar = 11,multScalar = 12,multiplicar = 13,ident = 14,null = 15,comp = 16} op;
matrix_t m1;   //Matriz archivo 1
matrix_t m2;   //Matriz archivo 2
matrix_t m3;   //Matriz auxiliar
char salida [10];
double numDouble;
int opValida = 1;int valor; 
if(argc == 1){
  puts("No hay argumentos, si necesita ayuda coloque --help");
}
else{
int ok = 0;
int ret;
for (int i = 1;i<argc;i++){
  switch(ok){
    case (0) :
             if ((strcmp(argv[i],"--in1") == 0) || (strcmp(argv[i],"-1") == 0)){
                ret = read_matrix(argv[i+1],&m1);
                if (ret != 0){
                    puts("Se produjo un error al leer el archivo 1");
                    ok = 1;
                }
                i++;
                break;
             }
             if ((strcmp(argv[i],"--in2") == 0) || (strcmp(argv[i],"-2") == 0)){
                ret = read_matrix(argv[i+1],&m2);
                if (ret != 0){
                    puts("Se produjo un error al leer el archivo 2");
                    ok = 1;
                }
                i++;
                break;
             }
             if ((strcmp(argv[i],"--out") == 0) || (strcmp(argv[i],"-o") == 0)){
                strcpy(salida,argv[i+1]);
                i++;
                break;
             }
             if ((strcmp(argv[i],"--scalar") == 0) || (strcmp(argv[i],"-s") == 0)){
                char* aux;
                numDouble = strtod(argv[i+1],&aux);
                if (numDouble == 0){
                    ok = 1;
                    i = argc;
                    puts ("Error, luego de --scalar se coloca un numero flotante, si necesita ayuda coloque --help");
                }
                i++;
                break;
             }
             if ((strcmp(argv[i],"--op") == 0) || (strcmp(argv[i],"-p") == 0)){
                int aux = -1;
                if (strcmp(argv[i+1],"dup") == 0) {op = duplicar; aux = op;}
                if (strcmp(argv[i+1],"sum") == 0) {op = sumar; aux = op;}
                if (strcmp(argv[i+1],"mult_scalar") == 0) {op = multScalar; aux = op;}
                if (strcmp(argv[i+1],"mult") == 0) {op = multiplicar; aux = op;}
                if (strcmp(argv[i+1],"idty") == 0) {op = ident; aux = op;}
                if (strcmp(argv[i+1],"null") == 0) {op = null; aux = op;}
                if (strcmp(argv[i+1],"cmp") == 0) {op = comp; aux = op;}
                if (aux == -1){
                    ok = 1;
                    i = argc;
                    puts("Operacion no valida, verifique los comandos con --help");
                    break;
                }
                i++;
                break;
             }
             if (strcmp(argv[i],"--help") == 0) {
                puts("--in1|-1 ​nombre_archivo -> Indica la primera matriz a cargar en memoria.\n");
                puts("--in2|-2 ​nombre_archivo -> Indica la segunda matriz a cargar en memoria.(Obligatorio,excepto que se use ​dup​,idty​ o ​mult_scalar​)\n");
                puts("--out|-o ​nombre_archivo -> Nombre del archivo donde se guardará el resultado\n");
                puts("--scalar|-s ​número -> Número en punto flotante por el que se multiplicarán los elementos de la matriz cargada con ​--in1​. (Obligatorio si se usa ​mult_scalar​).\n");
                puts("--op|-p ​(dup|sum|mult_scalar|mult|idty|null|cmp)\n");
                puts("      .sum : suma --in1 y --in2 y lo coloca en --out");
                puts("      .mult_scalar : multiplica --in1 por --scalar y lo coloca en --out");
                puts("      .mult : multiplica --in1 por --in2 y lo coloca en --out");
                puts("      .idty : Genera la matriz identidad de --in1 y la coloca en --out");
                puts("      .null : Genera la matriz nula compatible  con --in1, se aloca en --out");
                puts("      .dup : duplica el archivo --in1 y lo coloca en out");
                puts("      .cmp : Compara --in1 con --in2 almacenando el resultado en una matriz 1x1 en --out");
                ok = 1;
                break;
             }
             ok = 1;
             puts("Error al ingresar argumentos, si necesita ayuda coloque --help");
             i = argc;
             break;
}
}
opValida = ok;
}
if (opValida == 0){
  switch (op){
        case(duplicar) : 
                    valor = dup_matrix(&m1,&m3); 
                    if (valor == 0){
                      write_matrix(salida,&m3);
                    }
                    else
                      puts ("Se produjo un error al duplicar, verifique lo valores de la matriz");
                    break;
       case (sumar) : 
                    valor = sum(&m1,&m2,&m3);
                    if (valor == 0)
                      write_matrix(salida,&m3);
                    else
                      puts("ERROR_INCOMPATIBLE_MATRICES");
                    break;

case(multScalar) : 
                   valor = mult_scalar(numDouble,&m1,&m3);
                   if (valor != 0)
                      puts("Valores fuera de rango");           
                   else
                     write_matrix(salida,&m3);
                   break;
      
case (multiplicar) : 
                   valor = mult (&m1,&m2,&m3);
                   if (valor == 0)
                     write_matrix(salida,&m3);
                   else
                      puts("ERROR_INCOMPATIBLE_MATRICES");
                   break;
    
    case (ident) :
                    idty_matrix(m1.fila,&m3);
                    write_matrix(salida,&m3);
                    break;                                      

    case(null)   :
                  null_matrix(m1.colum,&m3);
                  write_matrix(salida,&m3);
                  break;
    case (comp)  :
                   m3.matriz = malloc(sizeof(double));
                   m3.matriz[0] = cmp_matrix(&m1,&m2);
                   m3.colum = 1;
                   m3.fila = 1; 
                   write_matrix(salida,&m3);
                   break;
        default : puts ("Operacion no encontrada");
                  break;
  }  
  
  free_matrix(&m1);
  free_matrix(&m2);
  free_matrix(&m3);
}
}