grammar Expr;

options {
    output=AST;

    ASTLabelType=CommonTree;
}

prog: ( stat {System.out.println($stat.tree.toStringTree()); })+;

stat: expr NEWLINE          -> expr
    | ID '=' expr NEWLINE   -> ^('=' ID expr)
    | NEWLINE               -> 
    ;

expr: multExpr (('+'^|'-'^) multExpr)*
    ;

multExpr: atom ('*'^ atom)*
        ;

atom: INT
    | ID
    | '('! expr ')'!
    ;

ID : ('a'..'z'|'A'..'Z')+ ;
INT : '0'..'9'+ ;
NEWLINE : '\r'? '\n' ;
WS : (' ' | '\t' | '\n' | '\r')+ {skip();};
