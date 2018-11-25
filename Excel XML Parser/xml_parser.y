%{

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


extern int yylineno;
extern char* yytext;
extern FILE *yyin;
extern FILE *yyout;

int errors = 0;

%}

%define parse.error verbose

%union {
	int int_t;
	char *str_t;
	int bool_t;
}

%token WORKBOOK 
%token DATA
%token STYLES
%token STYLE
%token WORKSHEET 
%token TABLE
%token COLUMN
%token CELL
%token ROW
%token ID 
%token PROTECTED
%token NAME
%token EXPANDEDROW 
%token EXPANDEDCOLUMN
%token STYLEID 
%token WIDTH 
%token HIDDEN 
%token HEIGHT 
%token MERGEACROSS 
%token MERGEDOWN 
%token TYPE 
%token BOOL 
%token STRING
%token NUMBER 
%token STRVALUE 
%token INTVALUE 
%token BOOLVALUE

%left CLOSE SLASH_CLOSE 
%right EQUAL OPEN OPEN_SLASH ROW

%type <int_t> INTVALUE
%type <str_t> STRVALUE

%%

Workbook : OPEN WORKBOOK CLOSE Styles Worksheet OPEN_SLASH WORKBOOK CLOSE ;
Worksheet : OPEN WORKSHEET Protected NAME EQUAL STRVALUE Protected CLOSE Table OPEN_SLASH WORKSHEET CLOSE;
Protected : /*empty*/ | PROTECTED EQUAL BOOLVALUE;
Styles : /*empty*/ | Styles OPEN STYLES CLOSE Style OPEN_SLASH STYLES CLOSE  ; 
Style : /*empty*/ | Style OPEN STYLE ID EQUAL STRVALUE CLOSE OPEN_SLASH STYLE CLOSE Style; 
Table :/*empty*/ |  OPEN TABLE ExpandedColumnCount ExpandedRowCount StyleID CLOSE Table_elements OPEN_SLASH TABLE CLOSE ;
ExpandedColumnCount : /*empty*/ |  EXPANDEDCOLUMN EQUAL INTVALUE ;
ExpandedRowCount : /*empty*/ |   EXPANDEDROW EQUAL INTVALUE ;
StyleID : /*empty*/ |  STYLEID EQUAL STRVALUE ;
Table_elements : Column Row ;
Column : /*empty*/ |  Column OPEN COLUMN Hidden Width StyleID  SLASH_CLOSE ;
Hidden : /*empty*/ |  HIDDEN EQUAL BOOLVALUE  ;
Width : /*empty*/ |  WIDTH EQUAL INTVALUE;
Row : /*empty*/ |  OPEN ROW Height Hidden StyleID  CLOSE Cell OPEN_SLASH ROW CLOSE Row ;
Height : /*empty*/ | HEIGHT EQUAL INTVALUE;
Cell : /*empty*/ | Cell OPEN CELL MergeAcross MergeDown StyleID CLOSE Data OPEN_SLASH CELL CLOSE ;
MergeAcross : /*empty*/ | MERGEACROSS EQUAL INTVALUE ;
MergeDown : /*empty*/ | MERGEDOWN EQUAL INTVALUE ;
Data : /*empty*/ | Data OPEN DATA TYPE EQUAL Type_Value  CLOSE Content OPEN_SLASH DATA CLOSE  ;
Content : /*empty*/ | STRING Content | NUMBER Content;
Type_Value : BOOLVALUE | STRVALUE | INTVALUE ;

%%

int yywrap(void)
{
   return 0;
}

void yyerror(char *s){
        errors++;
	printf("\nError at line #%d: %s. \n", yylineno,s);	
}
								
int main (int argc, char **argv){
	argv++;
	argc--;
	
	errors=0;
	  
	if(argc>0)
		yyin=fopen(argv[0], "r");
	else
		yyin=stdin;
			
	yyparse();

	if(errors==0) 
	    printf("Parsing successful. No errors.\n"); 
    	
	return 0;
} 
