%{
	#include "y.tab.h"  
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>
%}

%option noyywrap
%option yylineno
%x comment 

str  [a-zA-Z0-9_]*[a-zA-Z_][a-zA-Z0-9_]*
quote [\"]
digit [0-9]
integer {digit}+  
whitespace [ \t\n]
boolean [true false]


%%

"<!--" BEGIN(comment);
<comment>{
     [^-\n]*
     "-"+[^->\n]*
     \n
     "-->" BEGIN(INITIAL);
}

"ss:Workbook"			{printf("%s", yytext); return (WORKBOOK);}
"ss:Worksheet"			{printf("%s", yytext); return (WORKSHEET);}
"ss:Styles"				{printf("%s", yytext); return (STYLES);}
"ss:Style"				{printf("%s ", yytext); return (STYLE);}
"ss:Table"				{printf("%s", yytext); return (TABLE);}
"ss:ExpandedRowCount"		{printf(" %s", yytext); return (EXPANDEDROW);}
"ss:ExpandedColumnCount"	{printf(" %s", yytext); return (EXPANDEDCOLUMN);}
"ss:StyleID"			{printf(" %s", yytext); return (STYLEID);}
"ss:Name"				{printf("%s", yytext); return (NAME);}
"ss:Column"				{printf("%s", yytext); return (COLUMN);}
"ss:Row"				{printf("%s", yytext); return (ROW);}
"ss:Cell"				{printf("%s", yytext); return (CELL);}
"ss:Data"				{printf("%s ", yytext); return (DATA);}
"ss:ID"            	    {printf(" %s", yytext); return (ID);}
"ss:Height"        	    {printf("%s", yytext); return (HEIGHT);}
"ss:Hidden"         	{printf("%s", yytext); return (HIDDEN);}
"ss:MergeAcross"    	{printf("%s", yytext); return (MERGEACROSS);}
"ss:Width"          	{printf("%s", yytext); return (WIDTH);}
"ss:MergeDown"      	{printf("%s", yytext); return (MERGEDOWN);}
"ss:Type"           	{printf("%s", yytext); return (TYPE);}
"ss:Protected"      	{printf("%s", yytext); return (PROTECTED);}
"=" 					{printf("%s", yytext); return (EQUAL);}
"<"  					{printf("%s", yytext); return (OPEN);}
">"   					{printf("%s\n", yytext); return (CLOSE);}
"</" 					{printf("%s", yytext); return (OPEN_SLASH);}
"/>" 					{printf("%s\n", yytext); return (SLASH_CLOSE);}
{whitespace} 			{}
{str}          			{printf("%s", yytext);return (STRING);} 
{quote}{str}{quote} 	{printf("%s", yytext);return (STRVALUE);} 
{quote}{integer}{quote} {printf("%s", yytext);return (INTVALUE);}
{quote}{boolean}{quote} {printf("%s", yytext);return (BOOLVALUE);} 
{integer}               {printf("%s", yytext);return (NUMBER);}
