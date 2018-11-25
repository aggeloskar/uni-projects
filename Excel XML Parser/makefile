all:
	bison -y -d xml_parser.y
	flex xml_parser.l
	gcc -c y.tab.c lex.yy.c
	gcc y.tab.o lex.yy.o -o parser
