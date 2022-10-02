%{
#include "file.hh"
#include <stdio.h>
#include<string.h>
int linenum=1;
%}

%%

[ \t]+   ;
[\n]    {linenum++;}	

"module" return MODULE;
"endmodule" return ENDMODULE;
"wire" return wire;
"input" return INPUT;
"output" return OUTPUT;


(32'h)[a-f|0-9]{8}     yylval.string=strdup(yytext); return hexa_32;
(64'h)[a-f|0-9]{16}     yylval.string=strdup(yytext); return hexa_64;

[0-9]+             yylval.number=atoi(yytext); return NUM;
[a-zA-Z][_a-zA-Z0-9]*    yylval.string=strdup(yytext); return identifier;



. {return yytext[0];}

%%



