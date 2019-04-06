grammar Blue; 

@header {
#include "wci/intermediate/TypeSpec.h"
using namespace wci::intermediate;
}

program :   header mainBlock ;

header    : FILE IDENTIFIER;
mainBlock : START block TERMINATE;
block     :  (|declarationList) (|func_list) main;


declarationList  : declarations ';' ( declarations ';')* ;
declarations : type_id var_list;
var_list     : var_id ( ',' var_id )* ;
var_id       : IDENTIFIER ;
type_id      : IDENTIFIER ;

func_list  : func (func)* ;
func	   : FUNC (|type_id) func_name '(' (|param_list) ')' func_block (|func_ret);
func_block : (|declarationList) compound_stmt;
func_name  : IDENTIFIER ;
func_ret   : RETURN variable;
param_list : param (',' param)*;
param	   : declarations;

main   :  MAIN compound_stmt ;

stmt : compound_stmt    # compoundStmt
     | assignment_stmt (|';') # assignmentStmt
     | loop_stmt   (|';')# loopStmt 
     | when_stmt   (|';')  # whenStmt
     | funcCall_stmt (|';')	# funcCallStmt
     | printf	(|';')			#printfStmt
     |                 # emptyStmt
     ;
        
compound_stmt : BEGIN ( stmt ';')* END ;     
funcCall_stmt   : (|(variable '=')) expr '(' (|(expr (',' expr)*)) ')';     
assignment_stmt : variable '=' expr ;
loop_stmt  		: LOOP expr stmt ;
when_stmt       : WHEN expr stmt ;
printf	   		: 'printf' '(' expr (',' expr)* ')';

variable : IDENTIFIER ;

expr locals [ TypeSpec *type = nullptr ]
     : expr mul_div_operation expr     # mulDivExpr
     | expr add_sub_operation expr     # addSubExpr
     | expr rel_operation expr         # relExpr
     | number               # unsignedNumberExpr
     | signedNumber         # signedNumberExpr
     | variable               # identifier
     | BOOLEAN					# boolean
     | STRING					# string
     | '(' expr ')'             # parens
     ;
     
     
signedNumber locals [ TypeSpec *type = nullptr ] 
    : sign number 
    ;     
     
number locals [ TypeSpec *type = nullptr ]
    : INTEGER    # integerConst
    | FLOAT      # floatConst
    ;
    
sign   : ADD_operation | SUB_operation ;
     
mul_div_operation : MUL_operation | DIV_operation ;
add_sub_operation : ADD_operation | SUB_operation ;
rel_operation     : EQEQ_operation | NE_operation | LT_operation | LE_operation | GT_operation | GE_operation ;

FILE : 'FILE' ;
MAIN : 'MAIN' ;
FUNC: 'FUNC' ;
START : 'START' ;
TERMINATE : 'TERMINATE' ;
BEGIN   : '{' ;
END     : '}' ;
VAR     : 'VAR' ;
LOOP   : 'LOOP' ;
WHEN    : 'WHEN' ;
RETURN    : 'RETURN' ;

IDENTIFIER : [a-zA-Z][a-zA-Z0-9]* ;
INTEGER    : [0-9]+ ;
FLOAT      : [0-9]+ '.' [0-9]+ ;
BOOLEAN	   : [TF] ;
STRING	: '"' .*? '"' ;

MUL_operation :   '*' ;
DIV_operation :   '/' ;
ADD_operation :   '+' ;
SUB_operation :   '-' ;

EQ_operation  : '=' ;
EQEQ_operation: '==';
NE_operation  : '!=' ;
LT_operation  : '<' ;
LE_operation  : '<=' ;
GT_operation  : '>' ;
GE_operation  : '>=' ;

NEWLINE : '\r'? '\n' -> skip  ;
WS      : [ \t]+ -> skip ; 
