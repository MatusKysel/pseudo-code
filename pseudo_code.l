%top{
#include "pseudo_code.h"
#include "pseudo_code.tab.h"
#include <stdlib.h>
#include <string.h>
}

%option noyywrap
%option case-insensitive
%option yylineno
%option nounput
%option noinput

%x STRING
%x COMMENT

%%

"IF"		    	{ return IF; }
"THEN"		    	{ return THEN; }
"ELSE"		    	{ return ELSE; }
"END IF"			{ return ENDIF; }
"FOR"				{ return FOR; }
"FROM"				{ return FROM; }
"TO"				{ return TO; }
"DO"				{ return DO; }
"END FOR"			{ return ENDFOR; }
"READ"				{ return READ; }
"PRINT"				{ return PRINT; }
"SWAP"				{ return SWAP; }
"LEN"				{ return LEN; }
"FUNC"				{ return FUNC; }
"END FUNC"			{ return ENDFUNC; }
"NOT"				{ return NOT; }
[0-9]+				{ yylval.val = atoi(yytext); return INT; }
[A-Z][A-Z0-9]*		{ yylval.var = StrToVar(yytext); return VAR; }
[+\-*/(){};=,<>!]	{ return yytext[0]; }
\"					{ BEGIN(STRING); }
<STRING>[^\"]+		{ yylval.s = strdup(yytext); return STR; }
<STRING>\"			{ BEGIN(INITIAL); }
"//"				{ BEGIN(COMMENT); }
<COMMENT>.+			{ ; }
<COMMENT>\n			{ BEGIN(INITIAL); }
[\r{0,1}\n]+		{ return NEWLINE; }
<<EOF>>				{ return NEWLINE; }
.					{ ; }
%%