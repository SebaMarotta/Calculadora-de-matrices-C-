#ifndef MATRIX_H
#define MATRIX_H
#include <stdio.h>
#include <inttypes.h>
#include "list.h"
struct matrix{
    double* matriz;
    int fila;
    int colum;
};

typedef struct matrix matrix_t;
int8_t read_matrix(char*,matrix_t*);
int8_t write_matrix (char* nombre,matrix_t* mc);
int8_t dup_matrix(const matrix_t *m_src, matrix_t *m_dst);
int8_t sum_inplace (const matrix_t *ma, matrix_t *mb);
int8_t sum (const matrix_t *ma,const matrix_t *mb,matrix_t *mc);
int8_t mult_scalar_inplace (double a,matrix_t *mc);
int8_t mult_scalar(double a, const matrix_t *mb, matrix_t *mc);
int8_t mult(const matrix_t *ma, const matrix_t *mb, matrix_t *mc);
int8_t idty_matrix (unsigned int n, matrix_t *mc);
int8_t null_matrix (unsigned int n, matrix_t *mc);
int8_t create_and_fill_matrix (unsigned int rows, unsigned int cols,double a, matrix_t *mc);
unsigned int get_cols (const matrix_t *ma);
unsigned int get_rows (const matrix_t *ma);
int8_t get_row (unsigned int pos, const matrix_t *ma, lista_t *l);
int8_t get_col (unsigned int pos, const matrix_t *ma, lista_t *l);
int8_t matrix2list (const matrix_t *ma, lista_t *l);
int8_t resize_matrix(unsigned int newrows, unsigned int newcols,matrix_t *ma);
int8_t set_elem_matrix(unsigned int row, unsigned int col,double value, matrix_t* mc);
int8_t get_elem_matrix(unsigned int row, unsigned int col,double *value,const matrix_t* mc);
int cmp_matrix (const matrix_t *ma,const matrix_t *mb);
int8_t free_matrix (matrix_t *m);
#endif