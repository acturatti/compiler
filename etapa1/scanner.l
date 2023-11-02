%{
  #include "tokens.h"
  #include "hash.h"
  int running = 1;
  int lineNumber = 1;

  int getLineNumber(void){
    return lineNumber;
  }

  int isRunning(void){
    return running;
  }

  void initMe(void){
    hashInit();
  }
%}

%x COMMENT

%%

"///"    { BEGIN(COMMENT); }
"//".*  

"\n"     { lineNumber++; }
[ \t]

"char"   { return KW_CHAR; }
"int"    { return KW_INT; }
"float"  { return KW_FLOAT; }

"code"   { return KW_CODE; }

"if"     { return KW_IF; }
"else"   { return KW_ELSE; }
"while"  { return KW_WHILE; }
"input"  { return KW_INPUT; }
"print"  { return KW_PRINT; }
"return" { return KW_RETURN; }

[-,;()\[\]{}=+*/%<>&|~]  { return yytext[0]; }

"<="     { return OPERATOR_LE; }
">="     { return OPERATOR_GE; }
"=="     { return OPERATOR_EQ; }
"!="     { return OPERATOR_DIF; }

[a-zA-Z0-9_]*[a-zA-Z_]+[a-zA-Z0-9_]* { return TK_IDENTIFIER; }

[0-9]+          { hashInsert(yytext, LIT_INT); return LIT_INT; }
[0-9]+\.[0-9]+  { hashInsert(yytext, LIT_REAL); return LIT_REAL; }
'[^']'          { hashInsert(yytext, LIT_CHAR); return LIT_CHAR; }
\"[^\"]*\"      { hashInsert(yytext, LIT_STRING); return LIT_STRING; }

.               { return TOKEN_ERROR; }


<COMMENT>"\n"     { lineNumber++; }
<COMMENT>"\\\\\\" { BEGIN(INITIAL); }
<COMMENT>.        

%%

#include "hash.c"
#include "main.c"

int yywrap(){
  running = 0;
  return 1;
}
