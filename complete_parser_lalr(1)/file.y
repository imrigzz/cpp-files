/*
	Compile in terminal
	lex file.l
	yacc --verbose --debug -d file.y -o file.cc
	cc -c lex.yy.c -o lex.yy.o
	c++ lex.yy.o file.c -o a.out
	./a.out	
*/

%{
#include<iostream>
#include<stdio.h>
#include<string>
#include<vector>
#include "struct.h"
parseTree m;
module_header temp_module;
module_instantiation temp_instance;
Port temp_port;
string temp_size="";
extern "C"{
int yylex(void); 
void yyerror( char *s);
int yyparse(void); 
int yywrap()
{
return 1;
}
using namespace std;	
}
%}



%token MODULE ENDMODULE wire INPUT OUTPUT
%union 
{
	int number;
        char * string;
}
%token <string> identifier
%token <string> hexa_32
%token <string> hexa_64
%token <number> NUM
%left identifier


%%

source_code: statement {cout << "Valid\n";};
statement: statement module_declaration
	|module_declaration
	;
	
module_declaration: MODULE identifier '(' parameter_port_list ')' ';' module_items ENDMODULE {
			temp_module.add_name($2);
			m.add_module(temp_module);
			temp_module.reset();

		}; 

parameter_port_list: input_ports ',' output_ports
	|input_ports
	|output_ports
	|
	;
input_ports: input_ports ',' INPUT port identifier {
			temp_port.add_name($5);
			temp_module.add_input(temp_port);
			temp_port.reset();
			}
	|INPUT port identifier {
			temp_port.add_name($3);
			temp_module.add_input(temp_port);
			temp_port.reset();
			}
	;
output_ports: output_ports ',' OUTPUT port identifier{
			temp_port.add_name($5);
			temp_module.add_output(temp_port);
			temp_port.reset();
			}
	|OUTPUT port identifier{
			temp_port.add_name($3);
			temp_module.add_output(temp_port);
			temp_port.reset();
			}
	;
module_items: module_items module_item 
	|
	;
module_item: wire identifier ';' {temp_module.add_wire($2);}
	|module_instantiation ';'
	;
port: port_range
	|single_wire_port
	|
	;

port_range: '['NUM':'NUM']' {temp_port.add_start($2); temp_port.add_end($4);};
single_wire_port : '['NUM']' {temp_port.add_start($2); temp_port.add_end(-1);};

module_instantiation: identifier parameter_value identifier '(' list_of_parameter_assignments ')' {
			temp_instance.add_module_name($1);
			temp_instance.add_instantiation_name($3);
			temp_module.add_module_instantiation(temp_instance);
			temp_instance.reset();
		};

parameter_value: '#' '(' parameters ')'
	|
	;
parameters: '.' identifier '(' size ')' {
			temp_instance.add_parameters($2,temp_size);
			temp_size="";
		}
	;

list_of_parameter_assignments: ordered_parameter_assignment
	|named_parameter_assignment
	;
	
named_parameter_assignment: named_parameter_assignment ',' '.' identifier '(' identifier port ')'{
		temp_port.add_name($6);
		temp_instance.add_net($4,temp_port);
		temp_port.reset();
		}
	|'.' identifier '(' identifier port ')' {
		temp_port.add_name($4);
		temp_instance.add_net($2,temp_port);
		temp_port.reset();
		}
	;

ordered_parameter_assignment: ordered_parameter_assignment ',' identifier port {
		temp_port.add_name($3);
		temp_instance.add_net("",temp_port);
		temp_port.reset();
		}
	| identifier port {
		temp_port.add_name($1);
		temp_instance.add_net("",temp_port);
		temp_port.reset();
		}
	; 

size : hexa_32 {temp_size=$1;temp_size="";}
	|hexa_64 {temp_size=$1;temp_size="";}
	;

%%


parseTree parse(char filename[100]){
	extern FILE *yyin;
	yyin= fopen(filename,"r");
	if(yyin == NULL)
   		{
      			printf("Error File Not found!");   
      			exit(1);            
   		}
	yyparse();
	return m;

}

void yyerror (char *s) {
   	fprintf (stderr, "%s\n", s);
}
