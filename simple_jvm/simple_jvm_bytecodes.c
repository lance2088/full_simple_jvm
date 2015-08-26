#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "simple_jvm.h"

extern SimpleInterfacePool simpleInterfacePool;
extern SimpleFieldPool simpleFieldPool;
extern SimpleConstantPool simpleConstantPool;
extern SimpleMethodPool simpleMethodPool; 
extern StackFrame stackFrame; 
extern LocalVariables localVariables;

static int run = 1;

// aload_0
int op_aload_0( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    pushInt(stack, 0);
#if SIMPLE_JVM_DEBUG
    printf("push 0 into stack\n");
#endif
    *opCode = *opCode + 1;
    return 0;
}
//bipush
int op_bipush( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = opCode[0][1];
    pushInt(stack, value);
#if SIMPLE_JVM_DEBUG
    printf("push a byte %d onto the stack \n", value);
#endif
    *opCode = *opCode + 2;
    return 0;
}
//dup
int op_dup( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    StackEntry *entry = popEntry(stack);
    int value = 0;
    value = EntryToInt(entry);
    if ( entry->type == STACK_ENTRY_INT ) {

        pushInt(stack, value);
        pushInt(stack, value);
    } else {
        pushRef(stack, value);
        pushRef(stack, value);
    }
    *opCode = *opCode + 1;
    return 0;
}
//getstatic
int op_getstatic( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    u2 field_index ;
    unsigned char tmp[2];
    tmp[0] = opCode[0][1];
    tmp[1] = opCode[0][2];
    field_index = tmp[0] << 8 | tmp[1];
#if SIMPLE_JVM_DEBUG
    printf("getstatic %d\n", field_index );
#endif
    pushRef(stack, field_index);
    *opCode = *opCode + 3;
    return 0;
}
// iadd
int op_iadd( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value1 = popInt(stack);
    int value2 = popInt(stack);
    int result = 0;
    result = value1 + value2;
#if SIMPLE_JVM_DEBUG
    printf("iadd: %d + %d = %d\n",value1, value2, result);
#endif
    pushInt(stack, result); 
    *opCode = *opCode + 1;
    return 0;
}
// iconst_0
int op_iconst_0( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    pushInt(stack, 0);
#if SIMPLE_JVM_DEBUG
    printf("iconst_0: push 0 into stack\n");
#endif
    *opCode = *opCode + 1;
    return 0;
}
// iconst_1
int op_iconst_1( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    pushInt(stack, 1);
#if SIMPLE_JVM_DEBUG
    printf("iconst_1: push 1 into stack\n");
#endif
    *opCode = *opCode + 1;
    return 0;
}
// iconst_2
int op_iconst_2( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    pushInt(stack, 2);
#if SIMPLE_JVM_DEBUG
    printf("iconst_2: push 1 into stack\n");
#endif
    *opCode = *opCode + 1;
    return 0;
}
// iconst_3
int op_iconst_3( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    pushInt(stack, 3);
#if SIMPLE_JVM_DEBUG
    printf("iconst_3: push 1 into stack\n");
#endif
    *opCode = *opCode + 1;
    return 0;
}
// iconst_4
int op_iconst_4( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    pushInt(stack, 4);
#if SIMPLE_JVM_DEBUG
    printf("iconst_4: push 1 into stack\n");
#endif
    *opCode = *opCode + 1;
    return 0;
}
// iconst_5
int op_iconst_5( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    pushInt(stack, 5);
#if SIMPLE_JVM_DEBUG
    printf("iconst_5: push 5 into stack\n");
#endif
    *opCode = *opCode + 1;
    return 0;
}
// idiv
int op_idiv( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value2 = popInt(stack);
    int value1 = popInt(stack);
    int result = 0;
    result = value1 / value2;
    pushInt(stack, result); 
    *opCode = *opCode + 1;
    return 0;
}

//iload
int op_iload( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int index = opCode[0][1];
    int value = localVariables.integer[index];
#if SIMPLE_JVM_DEBUG
    printf("iload: load value from local variable %d(%d)\n", index, localVariables.integer[index]);
#endif
    pushInt(stack, value);
    *opCode = *opCode + 2;
    return 0;
}

//iload_1
int op_iload_1( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = localVariables.integer[1];
#if SIMPLE_JVM_DEBUG
    printf("iload_1: load value from local variable 1(%d)\n", localVariables.integer[1]);
#endif
    pushInt(stack, value);
    *opCode = *opCode + 1;
    return 0;
}

//iload_2
int op_iload_2( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = localVariables.integer[2];
#if SIMPLE_JVM_DEBUG
    printf("iload_2: load value from local variable 2(%d)\n", localVariables.integer[2]);
#endif
    pushInt(stack, value);
    *opCode = *opCode + 1;
    return 0;
}
//iload_3
int op_iload_3( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = localVariables.integer[3];
#if SIMPLE_JVM_DEBUG
    printf("iload_3: load value from local variable 3(%d)\n",localVariables.integer[3]);
#endif
    pushInt(stack, value);
    *opCode = *opCode + 1;
    return 0;
}
// imul
int op_imul( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value1 = popInt(stack);
    int value2 = popInt(stack);
    int result = 0;
    result = value1 * value2;
    pushInt(stack, result); 
    *opCode = *opCode + 1;
    return 0;
}
//istore
int op_istore( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = popInt(stack);
    int index = opCode[0][1];
#if SIMPLE_JVM_DEBUG
    printf("istore: store value into local variable %d(%d)\n", index, value);
#endif
    localVariables.integer[index] = value;
    *opCode = *opCode + 2;
    return 0;
}
//istore_1
int op_istore_1( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = popInt(stack);
#if SIMPLE_JVM_DEBUG
    printf("istore_1: store value into local variable 1(%d)\n", value);
#endif
    localVariables.integer[1] = value;
    *opCode = *opCode + 1;
    return 0;
}
//istore_2
int op_istore_2( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = popInt(stack);
#if SIMPLE_JVM_DEBUG
    printf("istore_2: store value into local variable 2(%d)\n", value);
#endif
    localVariables.integer[2] = value;
    *opCode = *opCode + 1;
    return 0;
}
//istore_3
int op_istore_3( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = popInt(stack);
#if SIMPLE_JVM_DEBUG
    printf("istore_3: store value into local variable 3(%d)\n", value);
#endif
    localVariables.integer[3] = value;
    *opCode = *opCode + 1;
    return 0;
}
// isub
int op_isub( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value2 = popInt(stack);
    int value1 = popInt(stack);
    int result = 0;
    result = value1 - value2;
#if SIMPLE_JVM_DEBUG
    printf("isub : %d - %d = %d\n", value1, value2, result);
#endif
    pushInt(stack, result); 
    *opCode = *opCode + 1;
    return 0;
}
//invokespecial
int op_invokespecial( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    u2 method_index ;
    unsigned char tmp[2];
    tmp[0] = opCode[0][1];
    tmp[1] = opCode[0][2];
    method_index = tmp[0] << 8 | tmp[1];
#if SIMPLE_JVM_DEBUG
    printf("call method_index %d\n", method_index);
#endif
    *opCode = *opCode + 3;
    if ( method_index < simpleMethodPool.method_used ) {
        MethodInfo *method = &simpleMethodPool.method[method_index];
        executeMethod( method, &stackFrame, &simpleConstantPool );
    }
    return 0;
}
static char *clzNamePrint="java/io/PrintStream";
static char *clzNameStrBuilder="java/lang/StringBuilder";
static char stringBuilderBuffer[1024];
static int stringBuilderUsed = 0;
//invokevirtual
int op_invokevirtual( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    u2 object_ref;
    unsigned char tmp[2];
    char clsName[255];
    char utf8[255];
    int len = 0;
    tmp[0] = opCode[0][1];
    tmp[1] = opCode[0][2];
    object_ref= tmp[0] << 8 | tmp[1];
#if SIMPLE_JVM_DEBUG
    printf("call object_ref %d\n", object_ref );
#endif
    *opCode = *opCode + 3;
    ConstantMethodRef *mRef = findMethodRef(p, object_ref );
    if ( mRef != 0 ) {
        ConstantClassRef *clasz = findClassRef(p, mRef->classIndex );
        ConstantNameAndType *nat = findNameAndType(p, mRef->nameAndTypeIndex );
        if ( clasz == 0 || nat == 0 ) return -1;
        getUTF8String(p, clasz->stringIndex, 255, clsName);
#if SIMPLE_JVM_DEBUG
        printf("call object ref class %s\n", clsName);
#endif
        if ( strcmp(clzNamePrint, clsName) == 0 ) {
            StackEntry *entry = popEntry(stack);
            int index = EntryToInt(entry);
#if SIMPLE_JVM_DEBUG
            printf("call Println with index = %d\n", index);
#endif
            if ( entry->type == STACK_ENTRY_REF ) {
                ConstantStringRef *strRef = findStringRef(p, index);
                if ( strRef != 0 ) {
                    getUTF8String(p, strRef->stringIndex, 255, utf8);
                    len = strlen(utf8);
                    memcpy( stringBuilderBuffer + stringBuilderUsed, utf8, len);
                    stringBuilderUsed += len;
                    stringBuilderBuffer[stringBuilderUsed] = 0;
                }
            } else if ( entry->type == STACK_ENTRY_INT ) {
                sprintf(utf8,"%d",index);
                len = strlen(utf8);
                memcpy( stringBuilderBuffer + stringBuilderUsed, utf8, len);
                stringBuilderUsed += len;
                stringBuilderBuffer[stringBuilderUsed] = 0;
            }
            // printf out the result
            printf("%s\n", stringBuilderBuffer); 
            memset(stringBuilderBuffer, 0, 1024);
            stringBuilderUsed = 0;
        } else if ( strcmp(clzNameStrBuilder, clsName) == 0 ){
            StackEntry *entry = popEntry(stack);
            int index = EntryToInt(entry);
#if SIMPLE_JVM_DEBUG
            printf("call StringBuilder with index = %d\n", index);
#endif
            if ( entry->type == STACK_ENTRY_REF ) {
                ConstantStringRef *strRef = findStringRef(p, index);
                if ( strRef != 0 ) {
                    getUTF8String(p, strRef->stringIndex, 255, utf8);
                    len = strlen(utf8);
                    memcpy( stringBuilderBuffer + stringBuilderUsed, utf8, len);
                    stringBuilderUsed += len;
                }
            } else if ( entry->type == STACK_ENTRY_INT ) {
                sprintf(utf8,"%d",index);
                len = strlen(utf8);
                memcpy( stringBuilderBuffer + stringBuilderUsed, utf8, len);
                stringBuilderUsed += len;
#if SIMPLE_JVM_DEBUG
                printf("%s\n", stringBuilderBuffer); 
#endif
            } 

        }
    }
    return 0;
}
//ldc
int op_ldc( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    int value = opCode[0][1];
    pushRef(stack, value);
#if SIMPLE_JVM_DEBUG
    printf("ldc: push a constant index %d onto the stack \n", value);
#endif
    *opCode = *opCode + 2;
    return 0;
}
//op_new
int op_new( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
    u2 object_ref;
    unsigned char tmp[2];
    tmp[0] = opCode[0][1];
    tmp[1] = opCode[0][2];
    object_ref= tmp[0] << 8 | tmp[1];
#if SIMPLE_JVM_DEBUG
    printf("new: new object_ref %d\n", object_ref );
#endif
    *opCode = *opCode + 3;
    return 0;
}

// return
int op_return( unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p ) {
#if SIMPLE_JVM_DEBUG
    printf("return: \n");
#endif
    *opCode = *opCode + 1;
    return -1;
}

byteCode byteCodes[] = {
    { "aload_0"         , 0x2A, 1,  op_aload_0          },
    { "bipush"          , 0x10, 2,  op_bipush           },
    { "dup"             , 0x59, 1,  op_dup              },
    { "getstatic"       , 0xB2, 3,  op_getstatic        },
    { "iadd"            , 0x60, 1,  op_iadd             },
    { "iconst_0"        , 0x03, 1,  op_iconst_0         },
    { "iconst_1"        , 0x04, 1,  op_iconst_1         },
    { "iconst_2"        , 0x05, 1,  op_iconst_2         },
    { "iconst_3"        , 0x06, 1,  op_iconst_3         },
    { "iconst_4"        , 0x07, 1,  op_iconst_4         },
    { "iconst_5"        , 0x08, 1,  op_iconst_5         },
    { "idiv"            , 0x6C, 1,  op_idiv             },
    { "imul"            , 0x68, 1,  op_imul             },
    { "invokespecial"   , 0xB7, 3,  op_invokespecial    },
    { "invokevirtual"   , 0xB6, 3,  op_invokevirtual    },
    { "iload"           , 0x15, 2,  op_iload            },
    { "iload_1"         , 0x1B, 1,  op_iload_1          },
    { "iload_2"         , 0x1C, 1,  op_iload_2          },
    { "iload_3"         , 0x1D, 1,  op_iload_3          },
    { "istore"          , 0x36, 2,  op_istore           },
    { "istore_1"        , 0x3C, 1,  op_istore_1         },
    { "istore_2"        , 0x3D, 1,  op_istore_2         },
    { "istore_3"        , 0x3E, 1,  op_istore_3         },
    { "isub"            , 0x64, 1,  op_isub             },
    { "ldc"             , 0x12, 2,  op_ldc              },
    { "new"             , 0xBB, 3,  op_new              },
    { "return"          , 0xB1, 1,  op_return           }
};
static byteCode_size = sizeof(byteCodes)/ sizeof(byteCode);

char *findOpCode( unsigned char op ) {
    int i = 0;
    for ( i = 0 ; i < byteCode_size ; i++ ) {
        if ( op == byteCodes[i].opCode )
            return byteCodes[i].name;
    } 
    return 0;
}
opCodeFunc findOpCodeFunc( unsigned char op ) {
    int i = 0;
    for ( i = 0 ; i < byteCode_size ; i++ ) {
        if ( op == byteCodes[i].opCode )
            return byteCodes[i].func;
    } 
    return 0;
}
int findOpCodeOffset( unsigned char op ) {
    int i = 0;
    for ( i = 0 ; i < byteCode_size ; i++ ) {
        if ( op == byteCodes[i].opCode )
            return byteCodes[i].offset;
    } 
    return 0;
}
int convertToCodeAttribute( CodeAttribute *ca, AttributeInfo *attr) {
    int info_p = 0;
    unsigned char tmp[4];
    ca->attribute_name_index = attr->attribute_name_index;
    ca->attribute_length = attr->attribute_length;
    tmp[0] = attr->info[info_p++];
    tmp[1] = attr->info[info_p++];
    ca->max_stack = tmp[0] << 8 | tmp[1]; 
    tmp[0] = attr->info[info_p++];
    tmp[1] = attr->info[info_p++];
    ca->max_locals = tmp[0] << 8 | tmp[1]; 
    tmp[0] = attr->info[info_p++];
    tmp[1] = attr->info[info_p++];
    tmp[2] = attr->info[info_p++];
    tmp[3] = attr->info[info_p++];
    ca->code_length = tmp[0] << 24 | tmp[1] << 16 | tmp[2] << 8 | tmp[3];
    ca->code = (unsigned char*)malloc(sizeof(unsigned char) * ca->code_length);
    memcpy( ca->code, attr->info + info_p, ca->code_length ); 
}

int executeMethod( MethodInfo *startup, StackFrame *stack, SimpleConstantPool *p ) {
    int i = 0;
    int j = 0;
    int tmp = 0;
    char name[255];
    CodeAttribute ca;
    memset( &ca, 0 , sizeof(CodeAttribute));
    for ( j = 0 ; j < startup->attributes_count ; j++ ) { 
        convertToCodeAttribute(&ca, &startup->attributes[j]);
        getUTF8String(p,ca.attribute_name_index,255,name);
        if ( memcmp( name, "Code", 4 ) != 0 ) continue;
#if SIMPLE_JVM_DEBUG
        printf("----------------------------------------\n");
        printf("code dump\n");
        printCodeAttribute(&ca, p);
        printf("----------------------------------------\n");
#endif
        unsigned char *pc = ca.code;
        //printf(" run = %d\n", run );
        if ( run == 0 ) {
            exit(1);
        }
        do {
#if 1
            opCodeFunc func= findOpCodeFunc(pc[0]);
            if ( func != 0 ) {
                //printf(" pc = %d\n", pc);
                i = func( &pc , &stackFrame, p);
                //printf(" pc = %d\n", pc);
            }
            if ( i < 0 ) break;
#endif
        } while (1) ;
    }
}

void printCodeAttribute( CodeAttribute *ca, SimpleConstantPool *p ) {
    int i = 0;
    int tmp = 0;
    char name[255];
    unsigned char opCode = 0;
    getUTF8String(p,ca->attribute_name_index,255,name);
    printf("attribute name : %s\n", name );
    printf("attribute length: %d\n", ca->attribute_length );

    printf("max_stack: %d\n", ca->max_stack );
    printf("max_locals: %d\n", ca->max_locals );
    printf("code_length: %d\n", ca->code_length );
    unsigned char *pc = ca->code;
    i = 0;
    do {
        char *opName = findOpCode( pc[0] );
        if ( opName == 0 ) {
            printf("Unknow OpCode %02X\n", pc[0] );
            exit(1);
        }
        printf("%s \n", opName);
#if 0
        opCodeFunc func= findOpCodeFunc(pc);
        if ( func != 0 ) 
            func(opCode, &stackFrame );
#endif
        tmp = findOpCodeOffset(pc[0]);
        pc += tmp;
        i += tmp;
    } while ( i < ca->code_length ) ;
}
