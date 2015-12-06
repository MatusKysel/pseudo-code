typedef struct VarNode{
  char *name;
  int index;
  int len;
} VarNode;

typedef struct ConstNode{
  int value;
} ConstNode;

typedef struct OpNode{
  int type;
  int n;
  struct Node **operands;
} OpNode;

typedef struct BlockNode{
  int n;
  struct Node **statements;
} BlockNode;

typedef struct StringNode{
  char *s;
} StringNode;

typedef struct ParamNode{
  int n;
  struct Node **params;
} ParamNode;

typedef enum { tConst, tVar, tOp, tBlock, tString, tParam, tFnCall} NodeType;

typedef struct Node{
  NodeType type;
  union {
    VarNode *var; // reference to variable or function name
    ConstNode con;
    OpNode op;
    BlockNode block;
    StringNode str;
    ParamNode par;
  };
} Node;

typedef struct Function{
  char *name;
  int param_count;
  int var_count;
  VarNode **variables; //return value, params, internal variables
  Node *body;
} Function;

typedef struct FnList{
  int fn_count;
  Function **functions;
} FnList;

VarNode *StrToVar(char *name);
FnList *ReadFunctions(char *file_name, FnList *x);
void FreeFunctions(FnList *x);
