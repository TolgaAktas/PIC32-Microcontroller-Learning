/* 
 * File:   math_ops.h
 * Author: taktas
 *
 * Created on October 4, 2018, 2:27 PM
 */

#ifndef MATH_OPS_H
#define	MATH_OPS_H

typedef enum {ADD,SUBTRACT,MULTIPLY} operator_t;
typedef struct{
    int a;
    int b;
    int result;
    operator_t operator;
}math_ops_t;

void math_ops_init(math_ops_t* arg1);
void math_ops_update(math_ops_t * arg1);
void math_ops_display(math_ops_t * arg1, char * arg2);

#endif
