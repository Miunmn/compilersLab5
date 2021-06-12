%{
#include <iostream>
using namespace std;
int number_lines = 1;
%}

%option noyywrap c++
%option yylineno

ws      [ \t]+

DIGITO [0-9]
LETRA [a-zA-Z]
ESPACIO [" "]
INI_COMENTARIO ["/*"]
FIN_COMENTARIO ["*/"]
GUIONES [-_]
CHAR_COMA [","]
CHAR_PUNTO ["."]
CHAR_PUNTOYCOMA [";"]
CHAR_DOSPUNTOS [":"]

IDENTIFICADOR {LETRA}({LETRA}|{DIGITO}|{GUIONES})*
CONST_INTEGER (-?[1-9][0-9]{0,4})|0
CONST_FLOAT {DIGITO}{0,8}{CHAR_PUNTO}{DIGITO}{1,9}

CONST_CADENA \"[^\n"]*\"

OP_SUMA ["+"]
OP_RESTA ["-"]
OP_MULT ["*"]
OP_DIV ["/"]
OP_IGUAL ["="]
OP_MAYOR [">"]
OP_MENOR ["<"]
OP_MAYORIGUAL ">="
OP_MENORIGUAL "<="
OP_COMP_IGUAL "=="
OP_NEGACION "!"
OP_DISTINTO "!="

OP_DOSPUNTOS [":"]

LLAVE_A ["{"]
LLAVE_B ["}"]
PARENTESIS_A ["("]
PARENTESIS_B [")"]
FIN_SENTENCIA [";"]

IF "if"|"IF"
WHILE "while"|"WHILE"
DECVAR "DECVAR"
ENDDEC "DECVAR"
INTEGER "int"|"Integer"
FLOAT "float"|"FLOAT"
DOUBLE "double"|"Double"
STRING "string"|"STRING"
CHAR "char"|"CHAR"
WRITE "write"|"WRITE" 


%%

{ws}    /* skip blanks and tabs */

"/*"    {
        int c;

        while((c = yyinput()) != 0)
            {
            if(c == '\n')
                ++number_lines;

            else if(c == '*')
                {
                if((c = yyinput()) == '/')
                    break;
                else
                    unput(c);
                }
            }
        }

{IF} {printf("<IF> ");}
{WHILE} {printf("<WHILE> ");}

{FLOAT} {printf("<FLOAT_TYPE> ");}
{INTEGER} {printf("<INT_TYPE> ");}
{DOUBLE} {printf("<DOUBLE_TYPE> ");}
{STRING} {printf("<STRING_TYPE> ");}
{CHAR} {printf("<CHAR_TYPE> ");}

{PARENTESIS_A} {printf("<PAR_BEGIN> ");}
{PARENTESIS_B} {printf("<PAR_END> ");}
{LLAVE_A} {printf("<BRACE_BEGIN> ");}
{LLAVE_B} {printf("<BRACE_END> ");}


{OP_IGUAL} {printf("<ASSIGN_OP> ");}
{OP_SUMA} {printf("<SUM_OP> ");}
{OP_RESTA} {printf("<MIN_OP> ");}
{OP_MULT} {printf("<MUL_OP> ");}
{OP_DIV} {printf("<DIV_OP> ");}
{OP_MAYOR} {printf("<REL_OP,'>'> ");}
{OP_MENOR} {printf("<REL_OP,'<'> ");}
{OP_MAYORIGUAL} {printf("<REL_OP,'>='> ");}
{OP_MENORIGUAL} {printf("<REL_OP,'<='> ");}
{OP_COMP_IGUAL} {printf("<REL_OP,'=='> ");} 
{OP_NEGACION} {printf("<NEGATION> ");}
{OP_DISTINTO} {printf("<DISTINCT> ");}
{FIN_SENTENCIA} {printf("<ENDOFSENTENCE> ");}
{OP_DOSPUNTOS} {printf("<TWOPOINTS> ");}

{CONST_INTEGER} {printf("<NUMBER,%s> ", yytext);}
{CONST_FLOAT} {printf("<NUMBER,%s> ", yytext);}
{IDENTIFICADOR} {printf("<ID,%s> ", yytext);}

\n number_lines++;
"." {printf("\nError en línea %d, caracter '%s' no soportado ", number_lines, yytext);}
"@" {printf("\nError en línea %d, caracter '%s' no soportado ", number_lines, yytext);}
"#" {printf("\nError en línea %d, caracter '%s' no soportado ", number_lines, yytext);}
"$" {printf("\nError en línea %d, caracter '%s' no soportado ", number_lines, yytext);}
"Ç" {printf("\nError en línea %d, caracter '%s' no soportado ", number_lines, yytext);}

%%