#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_jvm.h"

extern SimpleInterfacePool simpleInterfacePool;
extern SimpleFieldPool simpleFieldPool;
extern SimpleConstantPool simpleConstantPool;
extern SimpleMethodPool simpleMethodPool; 
/*
 * Stack Initialization
 */
void stackInit(StackFrame *stack, int entry_size ) {
    memset(stack,0,sizeof(StackFrame));
    stack->store = (StackEntry*) malloc(sizeof(StackEntry) * entry_size );
    stack->size = 0;
}
/*
 * push Integer 
 */
void pushInt( StackFrame *stack, int value ) {
    unsigned char *tmp = stack->store[stack->size].entry; 
    tmp[0] = (value >> 24) & 0xFF ;
    tmp[1] = (value >> 16) & 0xFF ;
    tmp[2] = (value >>  8) & 0xFF ;
    tmp[3] = (value      ) & 0xFF ;
    stack->store[stack->size].type= STACK_ENTRY_INT ;
    stack->size++;

}
/*
 * push Ref 
 */
void pushRef( StackFrame *stack, int value ) {
    unsigned char *tmp = stack->store[stack->size].entry; 
    tmp[0] = (value >> 24) & 0xFF ;
    tmp[1] = (value >> 16) & 0xFF ;
    tmp[2] = (value >>  8) & 0xFF ;
    tmp[3] = (value      ) & 0xFF ;
    stack->store[stack->size].type= STACK_ENTRY_REF ;
    stack->size++;

}
/*
 * pop Integer 
 */
int popInt( StackFrame *stack ) {
    stack->size--;
    unsigned char *tmp = stack->store[stack->size].entry; 
    int value = 0;
    value = ( tmp[0] << 24 ) | ( tmp[1] << 16 ) | tmp[2] << 8 | tmp[3];
    return value;
}
/*
 * Pop Stack Entry
 */
StackEntry* popEntry( StackFrame *stack ) {
    stack->size--;
    return &stack->store[stack->size]; 
}
/*
 * Entry to Int
 */
int EntryToInt( StackEntry *entry ) {
    int value = 0;
    value = ( entry->entry[0] << 24 ) | 
            ( entry->entry[1] << 16 ) | 
            ( entry->entry[2] << 8  ) | 
            ( entry->entry[3]       );

}
