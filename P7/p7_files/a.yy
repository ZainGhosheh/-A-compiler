%skeleton "lalr1.cc"
%require "3.0"
%debug
%defines
%define api.namespace{a_lang}
%define api.parser.class {Parser}
%define api.value.type variant
%define parse.error verbose
%output "parser.cc"
%token-table

%code requires{
	#include <list>
	#include "tokens.hpp"
	#include "ast.hpp"
	namespace a_lang {
		class Scanner;
	}

//The following definition is required when 
// we don't use the %locations directive (which we won't)
# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

//End "requires" code
}

%parse-param { a_lang::Scanner &scanner }
%parse-param { a_lang::ProgramNode** root}
%code {
   // C std code for utility functions
   #include <iostream>
   #include <cstdlib>
   #include <fstream>

   // Our code for interoperation between scanner/parser
   #include "scanner.hpp"
   #include "ast.hpp"
   #include "tokens.hpp"

  //Request tokens from our scanner member, not 
  // from a global function
  #undef yylex
  #define yylex scanner.yylex
}

//%define parse.assert

/* Terminals */


%token                     END   0 "end file"
%token	<a_lang::Token *>       AND
%token	<a_lang::Token *>       ASSIGN
%token	<a_lang::Token *>       ARROW
%token	<a_lang::Token *>       BOOL
%token	<a_lang::Token *>       COLON
%token	<a_lang::Token *>       COMMA
%token	<a_lang::Token *>       CUSTOM
%token	<a_lang::Token *>       DASH
%token	<a_lang::Token *>       ELSE
%token	<a_lang::Token *>       EH
%token	<a_lang::Token *>       EQUALS
%token	<a_lang::Token *>       FALSE
%token	<a_lang::Token *>       FROMCONSOLE
%token	<a_lang::Token *>       GREATER
%token	<a_lang::Token *>       GREATEREQ
%token	<a_lang::IDToken *>     ID
%token	<a_lang::Token *>       IF
%token	<a_lang::Token *>       INT
%token	<a_lang::IntLitToken *> INTLITERAL
%token	<a_lang::Token *>       IMMUTABLE
%token	<a_lang::Token *>       LCURLY
%token	<a_lang::Token *>       LESS
%token	<a_lang::Token *>       LESSEQ
%token	<a_lang::Token *>       LPAREN
%token	<a_lang::Token *>       MAYBE
%token	<a_lang::Token *>       MEANS
%token	<a_lang::Token *>       NOT
%token	<a_lang::Token *>       NOTEQUALS
%token	<a_lang::Token *>       OR
%token	<a_lang::Token *>       OTHERWISE
%token	<a_lang::Token *>       CROSS
%token	<a_lang::Token *>       POSTDEC
%token	<a_lang::Token *>       POSTINC
%token	<a_lang::Token *>       RETURN
%token	<a_lang::Token *>       RCURLY
%token	<a_lang::Token *>       REF
%token	<a_lang::Token *>       RPAREN
%token	<a_lang::Token *>       SEMICOL
%token	<a_lang::Token *>       SLASH
%token	<a_lang::Token *>       STAR
%token	<a_lang::StrToken *>    STRINGLITERAL
%token	<a_lang::Token *>       TOCONSOLE
%token	<a_lang::Token *>       TRUE
%token	<a_lang::Token *>       VOID
%token	<a_lang::Token *>       WHILE

%type <a_lang::ProgramNode *> program
%type <std::list<a_lang::DeclNode *> *> globals
%type <a_lang::DeclNode *> decl
%type <a_lang::VarDeclNode *> varDecl
%type <a_lang::FnDeclNode *> fnDecl
%type <a_lang::ExpNode *> term
%type <a_lang::ExpNode *> exp
%type <std::list<a_lang::ExpNode *> *> actualsList
%type <a_lang::CallExpNode *> callExp

%type <a_lang::IDNode *> name
%type <a_lang::LocNode *> loc
%type <a_lang::StmtNode *> stmt
%type <a_lang::StmtNode *> blockStmt
%type <std::list<a_lang::StmtNode *> *> stmtList
%type <a_lang::TypeNode *> type
%type <a_lang::FormalDeclNode *> formalDecl
%type <std::list<a_lang::FormalDeclNode *> *> maybeFormals
%type <std::list<a_lang::FormalDeclNode *> *> formalList

%type <a_lang::TypeNode *> primType

/* NOTE: Make sure to add precedence and associativity 
 * declarations
 */
%right ASSIGN
%left OR
%left AND
%nonassoc LESS GREATER LESSEQ GREATEREQ EQUALS NOTEQUALS
%left DASH CROSS
%left STAR SLASH
%left NOT 

%%

program		: globals
		  {
		  $$ = new ProgramNode($1);
		  *root = $$;
		  }

globals		: globals decl
		  {
		  $$ = $1;
		  DeclNode * declNode = $2;
		  $$->push_back(declNode);
		  }
		| /* epsilon */
		  {
		  $$ = new std::list<DeclNode *>();
		  }

decl		: varDecl SEMICOL
		  {
		  $$ = $1;
		  }
		| fnDecl
		  {
		  $$ = $1;
		  }

varDecl		: name COLON type
		  {
		  Position * p = new Position($1->pos(), $3->pos());
		  $$ = new VarDeclNode(p,$1, $3, nullptr);
		  }
		| name COLON type ASSIGN exp
		  {
		  Position * p = new Position($1->pos(), $5->pos());
		  $$ = new VarDeclNode(p,$1, $3, $5);
		  }

type		: IMMUTABLE primType
		  {
		  Position * p = new Position($1->pos(), $2->pos());
		  $$ = new ImmutableTypeNode(p, $2);
		  }
		| primType
		  {
		  $$ = $1;
		  }

primType	: INT
		  {
		  $$ = new IntTypeNode($1->pos());
		  }
		| BOOL
		  {
		  $$ = new BoolTypeNode($1->pos());
		  }
		| VOID
		  {
		  $$ = new VoidTypeNode($1->pos());
		  }

fnDecl 		: name COLON LPAREN maybeFormals RPAREN ARROW type LCURLY stmtList RCURLY
		  {
		  auto pos = new Position($1->pos(), $10->pos());
		  $$ = new FnDeclNode(pos, $1, $4, $7, $9);
		  }

maybeFormals	: /* epsilon */
		  {
		  $$ = new std::list<FormalDeclNode *>();
		  }
		| formalList
		  {
		  $$ = $1;
		  }

formalList	: formalDecl
		  {
		  $$ = new std::list<FormalDeclNode *>();
		  $$->push_back($1);
		  }
		| formalList COMMA formalDecl
		  {
		  $$ = $1;
		  $$->push_back($3);
		  }

formalDecl	: name COLON type
		  {
		  auto pos = new Position($1->pos(), $2->pos());
		  $$ = new FormalDeclNode(pos, $1, $3);
		  }

stmtList	: /* epsilon */
		  {
		  $$ = new std::list<StmtNode *>();
		  }
		| stmtList stmt SEMICOL
		  {
		  $$ = $1;
		  $$->push_back($2);
		  }
		| stmtList blockStmt
		  {
		  $$ = $1;
		  $$->push_back($2);
		  }

blockStmt	: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
		  const Position * p = new Position($1->pos(), $7->pos());
		  $$ = new WhileStmtNode(p, $3, $6);
		  }
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
		  const Position * p = new Position($1->pos(), $7->pos());
		  $$ = new IfStmtNode(p, $3, $6);
		  }
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
		  {
		  const Position * p = new Position($1->pos(), $11->pos());
		  $$ = new IfElseStmtNode(p, $3, $6, $10);
		  }

stmt		: varDecl
		  {
		  $$ = $1;
		  }
		| loc ASSIGN exp
		  {
		  const auto p = new Position($1->pos(), $3->pos());
		  $$ = new AssignStmtNode(p, $1, $3); 
		  }
		| callExp
		  {
		  $$ = new CallStmtNode($1->pos(), $1);
		  }
		| loc POSTDEC
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new PostDecStmtNode(p, $1);
		  }
		| loc POSTINC
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new PostIncStmtNode(p, $1);
		  }
		| TOCONSOLE exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new ToConsoleStmtNode(p, $2);
		  }
		| FROMCONSOLE loc
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new FromConsoleStmtNode(p, $2);
		  }
		| MAYBE loc MEANS exp OTHERWISE exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new MaybeStmtNode(p, $2, $4, $6);
		  }
		| RETURN exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new ReturnStmtNode(p, $2);
		  }
		| RETURN
		  {
		  const Position * p = $1->pos();
		  $$ = new ReturnStmtNode(p, nullptr);
		  }

exp		: exp DASH exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new MinusNode(p, $1, $3);
		  }
		| exp CROSS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new PlusNode(p, $1, $3);
		  }
		| exp STAR exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new TimesNode(p, $1, $3);
		  }
		| exp SLASH exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new DivideNode(p, $1, $3);
		  }
		| exp AND exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new AndNode(p, $1, $3);
		  }
		| exp OR exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new OrNode(p, $1, $3);
		  }
		| exp EQUALS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new EqualsNode(p, $1, $3);
		  }
		| exp NOTEQUALS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new NotEqualsNode(p, $1, $3);
		  }
		| exp GREATER exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new GreaterNode(p, $1, $3);
		  }
		| exp GREATEREQ exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new GreaterEqNode(p, $1, $3);
		  }
		| exp LESS exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new LessNode(p, $1, $3);
		  }
		| exp LESSEQ exp
	  	  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  $$ = new LessEqNode(p, $1, $3);
		  }
		| NOT exp
	  	  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new NotNode(p, $2);
		  }
		| DASH term
	  	  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new NegNode(p, $2);
		  }
		| term
	  	  { $$ = $1; }


callExp		: loc LPAREN RPAREN
		  {
		  const Position * p = new Position($1->pos(), $3->pos());
		  std::list<ExpNode *> * noargs =
		    new std::list<ExpNode *>();
		  $$ = new CallExpNode(p, $1, noargs);
		  }
		| loc LPAREN actualsList RPAREN
		  {
		  const Position * p = new Position($1->pos(), $4->pos());
		  $$ = new CallExpNode(p, $1, $3);
		  }

actualsList	: exp
		  {
		  std::list<ExpNode *> * list =
		    new std::list<ExpNode *>();
		  list->push_back($1);
		  $$ = list;
		  }
		| actualsList COMMA exp
		  {
		  $$ = $1;
		  $$->push_back($3);
		  }

term 		: loc
		  { $$ = $1; }
		| INTLITERAL 
		  { $$ = new IntLitNode($1->pos(), $1->num()); }
		| STRINGLITERAL 
		  { $$ = new StrLitNode($1->pos(), $1->str()); }
		| TRUE
		  { $$ = new TrueNode($1->pos()); }
		| FALSE
		  { $$ = new FalseNode($1->pos()); }
		| EH
		  { $$ = new EhNode($1->pos()); }
		| LPAREN exp RPAREN
		  { $$ = $2; }
		| callExp
		  { $$ = $1; } 

loc		: name
		  {
		  $$ = $1;
		  }

name		: ID
		  {
		  $$ = new IDNode($1->pos(), $1->value());
		  }
	
%%

void a_lang::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
