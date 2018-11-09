#include "math_ops.h"
#include <string.h>
#include <stdio.h>

void math_ops_init(math_ops_t* arg1){
    arg1->a = 0;
    arg1->b = 0;
    arg1->result = 0;
    arg1->operator = ADD;
}

void math_ops_update(math_ops_t * arg1){
    if(arg1->operator == ADD){
        arg1->result = arg1->a + arg1->b;
    }else if(arg1->operator == SUBTRACT){
        arg1->result = arg1->a - arg1->b;
    }else if(arg1->operator == MULTIPLY){
        arg1->result = arg1->a * arg1->b;
    }
}
void math_ops_display(math_ops_t * arg1, char * arg2){

    //char op;

    if(arg1->operator == ADD){
        sprintf(arg2,"%d+%d=%d",arg1->a,arg1->b,arg1->result);
        //op = '+';
    }else if(arg1->operator == SUBTRACT){
        sprintf(arg2,"%d-%d=%d",arg1->a,arg1->b,arg1->result);
        //op = '-';
    }else if(arg1->operator == MULTIPLY){
        sprintf(arg2,"%dx%d=%d",arg1->a,arg1->b,arg1->result);
        //op = 'x';
    }
    //sprintf(arg2, "%d%c%d",arg1->a,op,arg1->b);

}

