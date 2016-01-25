%{

%}


%%
^([^a\n]*a){3}[^a\n]*$	{ printf("%s : found type 1\n", yytext); }
^(1|(0.))(..)*\n		{ printf("%s : found type 2\n", yytext); }
^.*"//"[^\n]*\n			{ printf("%s : found type 3\n", yytext); }
"/*"((\*+[^/*])|([^*]))*\**"*/" { printf("%s : found type 4\n", yytext); }
%%

/*======================================================*
 * yylex calls yywrap() when it encounters the end of   *
 * the file.  Returned value 1 tells yylex to return 0, *
 * which is yylex's way of saying 'end of file'.        *
 *======================================================*/

int yywrap()
{
  return 1;
}

int main(int argc, char *argv[])
{
  	if(argc == 2)
	{
    	yyin = fopen(argv[1], "r");
    	
		if(yyin == NULL)
			return 1;
	}
	else
		yyin = stdin;

    yylex();
	return 0;
}
