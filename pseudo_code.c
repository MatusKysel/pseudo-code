#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pseudo_code.h"
#include "pseudo_code.tab.h"

#define STACKSIZE 64000
void *stack;
void *sp;
void *fp;
FnList *functions;
#define BUFSIZE 1000
char buf[BUFSIZE];
void FncList(Node *p);

Function *FindFunction(char *s){
	int i;
	for(i = 0; i < functions->fn_count; i++)
		if(strcasecmp(functions->functions[i]->name, s) == 0)
			return functions->functions[i];
	return NULL;
}

int Add(int *a, int *b) 	{ return *a + *b; }
int Sub(int *a, int *b) 	{ return *a - *b; }
int Mul(int *a, int *b)		{ return (*a) * (*b); }
int Div(int *a, int *b)	{ return (*a) / (*b); }
//int leq(int *a, int *b)		{ return (*a) <= (*b); }

void Op2(OpNode *op, int (*fn)(int *a, int *b))
{
	FncList(op->operands[0]);
	sp = sp + sizeof(int);
	FncList(op->operands[1]);
	sp = sp - sizeof(int);
	*(int*)sp = fn(sp, sp + sizeof(int));
}

void ExecuteFunction(Function *fn){
	*(void**)sp = fp;//store reference to previous fncalls variables
	sp = sp + sizeof(void*);//move sp forward to a free spot
	fp = sp;//assign new functions variable space from this location
	sp = sp + fn->var_count * sizeof(int);//move sp forward to space after fn variables
	FncList(fn->body); 
	int retvalue = *(int*)fp;
	sp = (void*)fp - sizeof(void*);//restore sp to old value
	fp = *(void**)sp;//restore fp
	*(int*)sp = retvalue;//put fn return value at top of stack
}

void FncList(Node *p){
	if(p == NULL)
		return;
	int i;
	Function *tmp;
	switch(p->type){
		case tConst: 
			*(int*)sp = p->con.value;
			break;
		case tVar:
			//printf("%s %p\n", p->var->name, fp + p->var->index * sizeof(int));
			*(int*)sp = *(int*)(fp + p->var->index * sizeof(int));
			break;
		case tString:
			*(char**)sp = p->str.s;
		case tOp:
			switch(p->op.type){
				case '+':
					Op2(&p->op, Add);
					break;
				case '-':
					Op2(&p->op, Sub);
					break;
				case '*':
					Op2(&p->op, Mul);
					break;
				case '/':
					Op2(&p->op, Div);
					break;
				case '=':
					FncList(p->op.operands[1]);//execute right half and have it stored at sp
					*(int*)(fp + p->op.operands[0]->var->index * sizeof(int)) = *(int*)sp;
					break;
				case PRINT: 
					FncList(p->op.operands[0]);
					if(p->op.operands[0]->type == tString)
						printf("%s\n", *(char**)sp);
					else
						printf("%d\n", *(int*)sp);
					break;
				case READ:
					fgets(buf, BUFSIZE, stdin);
					*(int*)(fp + p->op.operands[0]->var->index * sizeof(int)) = atoi(buf);
					break;
				case IF:
					FncList(p->op.operands[0]);
					if( *(int*)sp )
						FncList(p->op.operands[1]);
					break;
				case ELSE:
					FncList(p->op.operands[0]);
					if( *(int*)sp )
						FncList(p->op.operands[1]);
					else
						FncList(p->op.operands[2]);
					break;
				case FUNC:
					tmp = FindFunction(p->op.operands[0]->var->name);
					if(tmp == NULL || tmp->param_count != p->op.operands[1]->par.n){
						printf("couldn't find function %s (%d)\n", p->op.operands[0]->var->name, 
						p->op.operands[1]->par.n);
						exit(0);
						break;
					}else{
						//printf("%p\n", sp);
						sp = sp + sizeof(void*);
						for(i = 0; i < p->op.operands[1]->par.n; i++){
							sp = sp + sizeof(int);
							//printf("%p\n", sp);
							FncList(p->op.operands[1]->par.params[i]);
						}
						sp = sp - sizeof(void*) - p->op.operands[1]->par.n * sizeof(int);
						//printf("%p\n", sp);
						ExecuteFunction(tmp);
					}
			}
			break;
		case tBlock: 
			for(i = 0; i < p->block.n; i++)
				FncList(p->block.statements[i]);
			break;
	}
} 

int main(int argc, char **argv){
	if(argc < 2){
		printf("No input files!\n");
		return 0;
	}
	int i;
	functions = NULL;
	for(i = 1; i < argc; i++){
		functions = ReadFunctions(argv[i], functions);
	}
	Function *main_fn = FindFunction("MAIN");
	if(main_fn == NULL){
		printf("No main function!\n");
	}else{
		stack = malloc(STACKSIZE);
		sp = stack;
		fp = NULL;
		ExecuteFunction(main_fn);
	}
	FreeFunctions(functions);
	return 0;
}