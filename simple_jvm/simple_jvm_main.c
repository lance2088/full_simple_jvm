/*
 * Simple Java Virtual Machine Project
 * This Project is created for elementary class
 * to help student to understand How it works.
 *
 * Auther : Chun-Yu Wang
 * Email  : wicanr2@gmail.com
 * Created Date : 2013/11/05
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_jvm.h"

/*
 * Simple JVM stores integer-only intrinsically, 
 * and parses one class file called Foo.class in the same Folder.
 *
 * We limit its capability for quickly implementation. 
 */
SimpleConstantPool  simpleConstantPool;
SimpleInterfacePool simpleInterfacePool ;
SimpleFieldPool     simpleFieldPool; 
SimpleMethodPool    simpleMethodPool; 
StackFrame          stackFrame; 
LocalVariables      localVariables;

int main(int argc, char* argv[]) {
    ClassFileFormat cff;

    /*
     * Initialize All Pools
     */
    memset(&cff                 , 0, sizeof(ClassFileFormat)    );
    memset(&simpleConstantPool  , 0, sizeof(SimpleConstantPool) );
    memset(&simpleInterfacePool , 0, sizeof(SimpleInterfacePool));
    memset(&simpleFieldPool     , 0, sizeof(SimpleFieldPool)    );
    memset(&simpleMethodPool    , 0, sizeof(SimpleMethodPool )  );
    memset(&localVariables      , 0, sizeof(LocalVariables )    );

    parseJavaClassFile("Foo.class", &cff); 
    
#if SIMPLE_JVM_DEBUG
    printConstantPool( &simpleConstantPool );
    printMethodPool( &simpleConstantPool, &simpleMethodPool);
    printClassFileFormat(&cff);
#endif

    //TODO list method attributes
    printf("-------------------------------------\n");
    printf("Execute Simple JVM\n");
    printf("-------------------------------------\n");
    MethodInfo *init = findMethodInPool(
            &simpleConstantPool, 
            &simpleMethodPool,
            "<init>",6
            );   
    if ( init != 0 ) { 
        printf("-------------------------------------\n");
        printf("find and execute <init> method\n");
        printf("-------------------------------------\n");
#if SIMPLE_JVM_DEBUG
        printMethodAttributes(&simpleConstantPool, init);
#endif
        stackInit( &stackFrame, 500 );
        executeMethod( init, &stackFrame, &simpleConstantPool );
    }
    printf("-------------------------------------\n");
    printf("Terminate Simple JVM\n");
    printf("-------------------------------------\n");
    free_pools();
    return 0;
}
