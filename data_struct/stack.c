#include<stdlib.h>
#include<stdio.h>

#define null (int)-1000
struct stack{
    int * stack, sp, maxsize;
};

struct stack stack(int size){
    struct stack st;
    st.maxsize = size;
    st.stack = (int*) malloc(sizeof(int)*size);
    st.sp = (int) 0;
    return st;
}

int pop(struct stack *st){
    if(st->sp!=0){
        //printf("\nPopped %d",st->stack[st->sp]);
        return st->stack[st->sp--];
    }
    else
        return null;
}

void push(struct stack *st, int n){
    st->stack[++st->sp] = n;
    //printf("\nPushed %d",n);
}
