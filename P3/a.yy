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
%parse-param { a_lang::ProgramNode** root }
%code{
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

/* Terminals 
 *  No need to touch these, but do note the translation type
 *  of each node. Most are just Token pointers, 
 *  and thus have no fields (other than line and column).
 *  Some terminals, like ID, have the translation type IDToken *,
 *  meaning the translation also has a name field. 
*/
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

/* Nonterminals
*  The specifier in angle brackets
*  indicates the type of the translation attribute.
*/
/*       (attribute type)    (nonterminal)    */
%type <a_lang::ProgramNode *> program
%type <std::list<a_lang::DeclNode *> *> globals
%type <a_lang::DeclNode *> decl
%type <a_lang::VarDeclNode *> varDecl
%type <a_lang::TypeNode *> type
%type <a_lang::TypeNode *> datatype
%type <a_lang::TypeNode *> primType
%type <a_lang::LocNode *> loc
%type <a_lang::IDNode *> name
%type <a_lang::FnDeclNode *> fnDecl
%type <a_lang::StmtNode *> stmt
%type <std::list<a_lang::StmtNode *> *> stmtList
%type <std::list<a_lang::FormalDeclNode *> *> formalList
%type <a_lang::FormalDeclNode *> formalDecl
%type <a_lang::ExpNode *> exp
%type <a_lang::CallExpNode *> callExp
%type <std::list<a_lang::FormalDeclNode *> *> maybeFormals
%type <a_lang::ClassDefnNode *> classTypeDecl
%type <std::list<a_lang::DeclNode *> *> classBody
%type <a_lang::ExpNode *> term
%type <std::list<a_lang::ExpNode *> *> actualList
%type <a_lang::StmtNode *> blockStmt

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
		  DEBUG_PRINT("program\n");
		  $$ = new ProgramNode($1);
		  *root = $$;
		  DEBUG_PRINT("program done\n");
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
		| classTypeDecl
		  {
	      $$ = $1;
		  }
		| fnDecl
		  {
		  $$ = $1;
		  }

varDecl		: name COLON type
		  {
		  const Position * p;
		  p = new Position($1->pos(), $2->pos());
		  $$ = new VarDeclNode(p, $1, $3);
		  }
		| name COLON type ASSIGN exp
		  {
		  const Position * p;
		  p = new Position($1->pos(), $2->pos());
		  $$ = new VarDeclNode(p, $1, $3, $5);
		  }

type		: IMMUTABLE datatype
		  {
		  $$ = new ImmutableTypeNode($1->pos(), $2);
		  }
		| datatype
		  {
		  $$ = $1;
		  }

datatype	: REF primType
		  {
	      $$ = new RefTypeNode($1->pos(), $2);
		  }
		| primType
		  {
		  $$ = $1;
		  }
		| REF name
		  {
	      $$ = new RefTypeNode($1->pos(), $2);
		  }
		| name
		  {
		  $$ = new ClassTypeNode($1->pos(), $1);
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

classTypeDecl 	: name COLON CUSTOM LCURLY classBody RCURLY SEMICOL
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new ClassDefnNode(p, $1, $5);
		  }

classBody 	: classBody varDecl SEMICOL
		  {
		  $1->push_back($2);
		  $$ = $1;
		  }
		| classBody fnDecl
		  {
		  $1->push_back($2);
		  $$ = $1;
		  }
		| /* epsilon */
		  {
		  $$ = new std::list<DeclNode *>();
		  }

fnDecl 		: name COLON LPAREN maybeFormals RPAREN ARROW type LCURLY stmtList RCURLY
		  {
		  DEBUG_PRINT("fnDecl\n");
		  const Position * p;
		  p = new Position($1->pos(), $2->pos());
		  $$ = new FnDeclNode(p, $1, $7, $4, $9);
		  DEBUG_PRINT("fnDecl done\n");
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
		  $1->push_back($3);
		  $$ = $1;
		  }

formalDecl	: name COLON type
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new FormalDeclNode(p, $1, $3);
		  }

stmtList	: /* epsilon */
		  {
		  $$ = new std::list<StmtNode *>();
		  }
		| stmtList stmt SEMICOL
		  {
		  DEBUG_PRINT("stmtList stmt\n");
		  $1->push_back($2);
		  $$ = $1;
		  DEBUG_PRINT("stmtList stmt done\n");
		  }
		| stmtList blockStmt
		  {
		  $1->push_back($2);
		  $$ = $1;
		  }

blockStmt	: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
		  $$ = new WhileStmtNode($1->pos(), $3, $6);
		  }
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY
		  {
		  $$ = new IfStmtNode($1->pos(), $3, $6);
		  }
		| IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
		  {
		  $$ = new IfElseStmtNode($1->pos(), $3, $6, $10);
		  }

stmt		: varDecl
		  {
		  $$ = $1;
		  }
		| loc ASSIGN exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
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
		  $$ = new ToConsoleStmtNode($1->pos(), $2);
		  }
		| FROMCONSOLE loc
		  {
		  $$ = new FromConsoleStmtNode($1->pos(), $2);
		  }
		| MAYBE exp MEANS exp OTHERWISE exp
		  {
		  $$ = new MaybeStmtNode($1->pos(), $2, $4, $6);
		  }
		| RETURN exp
		  {
		  $$ = new ReturnStmtNode($1->pos(), $2);
		  }
		| RETURN
		  {
		  $$ = new ReturnStmtNode($1->pos());
		  }


exp		: exp DASH exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new MinusNode(p, $1, $3);
		  }
		| exp CROSS exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new PlusNode(p, $1, $3);
		  }
		| exp STAR exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new TimesNode(p, $1, $3);
		  }
		| exp SLASH exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new DivideNode(p, $1, $3);
		  }
		| exp AND exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new AndNode(p, $1, $3);
		  }
		| exp OR exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new OrNode(p, $1, $3);
		  }
		| exp EQUALS exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new EqualsNode(p, $1, $3);
		  }
		| exp NOTEQUALS exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new NotEqualsNode(p, $1, $3);
		  }
		| exp GREATER exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new GreaterNode(p, $1, $3);
		  }
		| exp GREATEREQ exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new GreaterEqNode(p, $1, $3);
		  }
		| exp LESS exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new LessNode(p, $1, $3);
		  }
		| exp LESSEQ exp
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new LessEqNode(p, $1, $3);
		  }
		| NOT exp
		  {
		  $$ = new NotNode($1->pos(), $2);
		  }
		| DASH term
		  {
		  $$ = new NegNode($1->pos(), $2);
		  }
		| term
		  {
		  $$ = $1;
		  }

callExp		: loc LPAREN RPAREN
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new CallExpNode(p, $1, new std::list<ExpNode *>());
		  }
		| loc LPAREN actualList RPAREN
		  {
		  const Position * p = new Position($1->pos(), $2->pos());
		  $$ = new CallExpNode(p, $1, $3);
		  }

actualList	: exp
		  {
		  $$ = new std::list<ExpNode *>();
		  $$->push_back($1);
		  }
		| actualList COMMA exp
		  {
		  $1->push_back($3);
		  $$ = $1;
		  }

term 		: loc
		  {
		  DEBUG_PRINT("term loc\n");
		  $$ = $1;
		  DEBUG_PRINT("term loc done\n");
		  }
		| INTLITERAL 
		  {
		  $$ = new IntLitNode($1->pos(), $1->num());
		  }
		| STRINGLITERAL
		  {
		  $$ = new StrLitNode($1->pos(), $1->str());
		  }
		| TRUE
		  {
		  $$ = new TrueNode($1->pos());
		  }
		| FALSE
		  {
		  $$ = new FalseNode($1->pos());
		  }
		| EH
		  {
		  $$ = new EhNode($1->pos());
		  }
		| LPAREN exp RPAREN
		  {
		  $2->setParenthesis(true);
		  $$ = $2;
		  }
		| callExp
		  {
		  $$ = $1;
		  }

loc		: name
		  {
		  $$ = $1;
		  }
		| loc ARROW name
		  {
		  DEBUG_PRINT("loc ARROW name\n");
		  $$ = new MemberFieldExpNode($1->pos(), $1, $3);
		  DEBUG_PRINT("loc ARROW name done\n");
		  }

name		: ID
		  {
                  const Position * pos = $1->pos();
	 	  $$ = new IDNode(pos, $1->value());
		  }
	
%%

void a_lang::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
