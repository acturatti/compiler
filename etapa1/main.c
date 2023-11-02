int main(int argc, char **argv){
  int tok;
  if (argc < 2){
    fprintf(stderr, "Call: ./a.out file_name\n");
    exit(1);
  }

  if((yyin = fopen(argv[1], "r")) == 0){
    fprintf(stderr, "File not found: %s\n", argv[1]);
    exit(1);
  }

  hashInit();

  while (running){
    tok = yylex();
    switch(tok){
      case KW_CHAR:   printf("%d: keyword char found\n", getLineNumber()); break;
      case KW_INT:    printf("%d: keyword int found\n", getLineNumber()); break;
      case KW_FLOAT:  printf("%d: keyword float found\n", getLineNumber()); break;

      case KW_CODE:   printf("%d: keyword code found\n", getLineNumber()); break;

      case KW_IF:     printf("%d: keyword if found\n", getLineNumber()); break;
      case KW_ELSE:   printf("%d: keyword else found\n", getLineNumber()); break;
      case KW_WHILE:  printf("%d: keyword while found\n", getLineNumber()); break;
      case KW_INPUT:  printf("%d: keyword input found\n", getLineNumber()); break;
      case KW_PRINT:  printf("%d: keyword print found\n", getLineNumber()); break;
      case KW_RETURN: printf("%d: keyword return found\n", getLineNumber()); break;

      case OPERATOR_LE: printf("%d: operator less equal found\n", getLineNumber()); break;
      case OPERATOR_GE: printf("%d: operator great equal found\n", getLineNumber()); break;
      case OPERATOR_EQ: printf("%d: operator equal found\n", getLineNumber()); break;
      case OPERATOR_DIF: printf("%d: operator different found\n", getLineNumber()); break;

      case TK_IDENTIFIER: printf("%d: identifier \"%s\" found \n", getLineNumber(), yytext); break;

      case LIT_INT: printf("%d: integer %s found\n", getLineNumber(), yytext); break;
      case LIT_REAL: printf("%d: real %s found\n", getLineNumber(), yytext); break;
      case LIT_CHAR: printf("%d: char %s found\n", getLineNumber(), yytext); break;
      case LIT_STRING: printf("%d: string %s found\n", getLineNumber(), yytext); break;

      case TOKEN_ERROR: printf("%d: ERRO TOKEN DESCONHECIDO\n", getLineNumber()); break;
      // printf("%d: \n", getLineNumber()); 
    }
  }

  printf("\n%d linhas\n", lineNumber);
  hashPrint();
}
