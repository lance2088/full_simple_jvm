/*
 * Simple Java Virtual Machine Project
 * This Project is created for elementary class
 * to help student to understand How it works.
 *
 * Auther : Chun-Yu Wang
 * Email  : wicanr2@gmail.com
 * Created Date : 2013/11/05
 */
#ifndef SIMPLE_JVM_H
#define SIMPLE_JVM_H
typedef short u2;
typedef unsigned char byte;

//---------------------------------
/*
 Simple Java Class File 
 */
typedef struct _ClassFileFormat { 
    byte magic_number[4];
    u2   minor_version;
    u2   major_version;
    u2   constant_pool_count;
    // constant pool
    u2   access_flags;
    u2   this_class;
    u2   super_class;

    u2   interface_count;
    // interface pool
    u2   fields_count;
    // fields pool
    u2   methods_count;
    // method pool
    u2   attributes_count;
    // attributes pool

} ClassFileFormat;
//---------------------------------
//-----------------------------------
/*
 *  TAG 
 *  1 UTF-8 String
 *  3 Integer
 *  4 Float
 *  5 Long
 *  6 Double
 *  7 Class reference
 *  8 String reference
 *  9 Field reference
 *  10 Method reference
 *  11 Interface method reference
 *  12 Name and type descriptor
 * */
#define CONSTANT_UTF8  1  
#define CONSTANT_INTEGER  3  
#define CONSTANT_FLOAT  4  
#define CONSTANT_LONG  5  
#define CONSTANT_DOUBLE  6  

#define CONSTANT_CLASS  7  
#define CONSTANT_STRING_REF  8  
#define CONSTANT_FIELD_REF  9  
#define CONSTANT_METHOD_REF  10  
#define CONSTANT_INTERFACE_REF  11  
#define CONSTANT_NAME_AND_TYPE  12


typedef struct _ConstantUTF8 {
    int index;
    unsigned char tag;
    int additional_byte_size;
    u2 string_size;
    unsigned char *ptr;
} ConstantUTF8;

typedef struct _ConstantInteger{
    int index;
    unsigned char tag;
    int additional_byte_size;
    int value;
} ConstantInteger;

typedef struct _ConstantFloat{
    int index;
    unsigned char tag;
    int additional_byte_size;
    float value;
} ConstantFloat;

typedef struct _ConstantLong{
    int index;
    unsigned char tag;
    int additional_byte_size;
    long long value;
} ConstantLong;

typedef struct _ConstantDouble{
    int index;
    unsigned char tag;
    int additional_byte_size;
    double value;
} ConstantDouble;

typedef struct _ConstantClassRef{
    int index;
    unsigned char tag;
    int additional_byte_size;
    u2 stringIndex;
} ConstantClassRef;

typedef struct _ConstantStringRef{
    int index;
    unsigned char tag;
    int additional_byte_size;
    u2 stringIndex;
} ConstantStringRef;

typedef struct _ConstantFieldRef{
    int index;
    unsigned char tag;
    int additional_byte_size;
    u2 classIndex;
    u2 nameAndTypeIndex;
} ConstantFieldRef;

typedef struct _ConstantMethodRef{
    int index;
    unsigned char tag;
    int additional_byte_size;
    u2 classIndex;
    u2 nameAndTypeIndex;
} ConstantMethodRef;

typedef struct _ConstantInterfaceRef{
    int index;
    unsigned char tag;
    int additional_byte_size;
    u2 classIndex;
    u2 nameAndTypeIndex;
} ConstantInterfaceRef;

typedef struct _ConstantNameAndType{
    int index;
    unsigned char tag;
    int additional_byte_size;
    u2 nameIndex;
    u2 typeIndex;
} ConstantNameAndType;

typedef struct _SimpleConstantPool {
    // UTF-8 String
    ConstantUTF8       utf8CP[100];
    int utf8_used; 

    // Integer
    ConstantInteger      integerCP[100];
    int integer_used;

    // Float
    ConstantFloat        floatCP[100];
    int float_used; 

    // Long
    ConstantLong         longCP[100];
    int long_used;
    
    // Double
    ConstantDouble       doubleCP[100];
    int double_used;

    // Class Reference
    ConstantClassRef     clasz[100];
    int clasz_used;

    // String Reference
    ConstantStringRef    stringRef[100];
    int stringRef_used;  

    // Field Reference
    ConstantFieldRef     field[100];
    int field_used;

    // Method Reference
    ConstantMethodRef    method[100];
    int method_used;

    // Interface Reference
    ConstantInterfaceRef interface[100];
    int interface_used;

    // Name And Type Reference
    ConstantNameAndType  name_and_type[100];
    int name_and_type_used;
} SimpleConstantPool;

//-----------------------------------
typedef struct _SimpleInterfacePool {
    // Class Reference
    ConstantClassRef     clasz[100];
    int clasz_used;
} SimpleInterfacePool;
/*
 * Attribute Info
 */
typedef struct _AttributeInfo {
    u2 attribute_name_index;
    int attribute_length;
    unsigned char *info;
} AttributeInfo;

/*
 * Code Attributes 
 */
typedef struct _CodeAttribute {
        u2 attribute_name_index;
        int attribute_length;
        u2 max_stack;
        u2 max_locals;
        int code_length;
        unsigned char* code;//[code_length];
        /*
        u2 exception_table_length;
        Exception_table* exception_table;//[exception_table_length];
        u2 attributes_count;
        attribute_info* attributes;//[attributes_count];
        */
} CodeAttribute ;


/*
 * Field Info
 */
typedef struct _FieldInfo {
    u2   access_flags;
    u2   name_index;
    u2   descriptor_index;
    u2   attributes_count;
    AttributeInfo *attributes;
} FieldInfo;
/*
 * Simple Field Pool
 */
typedef struct _SimpleFieldPool {
    FieldInfo field[100];
    int field_used;
}SimpleFieldPool ;
/*
 * Method Info
 */
typedef struct _MethodInfo {
    u2 access_flags; 
    u2 name_index; 
    u2 descriptor_index; 
    u2 attributes_count; 
    AttributeInfo *attributes;
} MethodInfo;
/*
 * Simple Method Pool
 */
typedef struct _SimpleMethodPool {
    MethodInfo method[100];
    int method_used;
}SimpleMethodPool ;
//-----------------------------------
// constant pool parser 
int parseConstantPool(FILE *fp, int count);
void printConstantPool( SimpleConstantPool *p );
ConstantUTF8 *findUTF8( SimpleConstantPool *p , int index );
ConstantStringRef *findStringRef( SimpleConstantPool *p , int index );
int getUTF8String( SimpleConstantPool *p, int index, int size, char *out ); 
ConstantClassRef *findClassRef( SimpleConstantPool *p , int index );
ConstantMethodRef *findMethodRef( SimpleConstantPool *p , int index );
ConstantNameAndType *findNameAndType( SimpleConstantPool *p , int index );
/*
 *  Interface Pool Parser
 */
int parseInterfacePool(FILE *fp, int count);
void printInterfacePool( SimpleConstantPool *p, SimpleInterfacePool *ip);
/*
 *  Field Pool Parser
 */
int parseFieldPool(FILE *fp, int count);
void printFieldPool( SimpleConstantPool *p, SimpleFieldPool *fp);
/*
 *  Method Pool Parser
 */
int parseMethodPool(FILE *fp, int count);
void printMethodPool( SimpleConstantPool *p, SimpleMethodPool *fp);
MethodInfo *findMethodInPool(
        SimpleConstantPool *p,
        SimpleMethodPool *mp,
        char *method_name, int size );
void printMethodAttributes( SimpleConstantPool *p,
        MethodInfo *method ) ;
/*
 * Attributes
 */
void printCodeAttribute( CodeAttribute *ca, SimpleConstantPool *p );
/*
 * Java Class File Parser
 */
int parseJavaClassFile( char *file, ClassFileFormat *cff );
void printClassFileFormat(ClassFileFormat *cff);
char* getMajorVersionString(u2 major_number);
/*
 * Free Pools 
 */
void free_pools();
//-----------------------------------
/*
 * Stack Frame
 */
#define STACK_ENTRY_INT 1
#define STACK_ENTRY_REF 2
typedef struct _StackEntry {
    unsigned char entry[4];
    int type;
} StackEntry;

typedef struct _StackFrame {
    int max_size;
    int size;
    StackEntry *store;
}StackFrame;
void stackInit(StackFrame *stack, int entry_size );
void pushInt( StackFrame *stack, int value );
int popInt( StackFrame *stack );
void pushRef( StackFrame *stack, int value );
StackEntry* popEntry( StackFrame *stackFrame );
int EntryToInt( StackEntry *entry );
//-----------------------------------
// local variable
typedef struct _LocalVariables{
    int integer[10];
}LocalVariables;
//-----------------------------------
// byte Codes
typedef int (*opCodeFunc) (unsigned char **opCode, StackFrame *stack, SimpleConstantPool *p );


typedef struct _byteCode {
    char *name;
    unsigned char opCode;
    int offset;
    opCodeFunc func; 
} byteCode;
int executeMethod( MethodInfo *startup, StackFrame *stack, SimpleConstantPool *p );
char *findOpCode( unsigned char op );
opCodeFunc findOpCodeFunc( unsigned char op ) ;
int findOpCodeOffset( unsigned char op );
//-----------------------------------
#endif
