// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton implementation for Bison LALR(1) parsers in C++

// Copyright (C) 2002-2015, 2018-2021 Free Software Foundation, Inc.

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

// As a special exception, you may create a larger work that contains
// part or all of the Bison parser skeleton and distribute that work
// under terms of your choice, so long as that work isn't itself a
// parser generator using the skeleton or a modified version thereof
// as a parser skeleton.  Alternatively, if you modify or redistribute
// the parser skeleton itself, you may (at your option) remove this
// special exception, which will cause the skeleton and the resulting
// Bison output files to be licensed under the GNU General Public
// License without this special exception.

// This special exception was added by the Free Software Foundation in
// version 2.2 of Bison.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.





#include "frontend.hh"


// Unqualified %code blocks.
#line 35 "a.yy"

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

#line 63 "parser.cc"


#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> // FIXME: INFRINGES ON USER NAME SPACE.
#   define YY_(msgid) dgettext ("bison-runtime", msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(msgid) msgid
# endif
#endif


// Whether we are compiled with exception support.
#ifndef YY_EXCEPTIONS
# if defined __GNUC__ && !defined __EXCEPTIONS
#  define YY_EXCEPTIONS 0
# else
#  define YY_EXCEPTIONS 1
# endif
#endif



// Enable debugging if requested.
#if YYDEBUG

// A pseudo ostream that takes yydebug_ into account.
# define YYCDEBUG if (yydebug_) (*yycdebug_)

# define YY_SYMBOL_PRINT(Title, Symbol)         \
  do {                                          \
    if (yydebug_)                               \
    {                                           \
      *yycdebug_ << Title << ' ';               \
      yy_print_ (*yycdebug_, Symbol);           \
      *yycdebug_ << '\n';                       \
    }                                           \
  } while (false)

# define YY_REDUCE_PRINT(Rule)          \
  do {                                  \
    if (yydebug_)                       \
      yy_reduce_print_ (Rule);          \
  } while (false)

# define YY_STACK_PRINT()               \
  do {                                  \
    if (yydebug_)                       \
      yy_stack_print_ ();                \
  } while (false)

#else // !YYDEBUG

# define YYCDEBUG if (false) std::cerr
# define YY_SYMBOL_PRINT(Title, Symbol)  YY_USE (Symbol)
# define YY_REDUCE_PRINT(Rule)           static_cast<void> (0)
# define YY_STACK_PRINT()                static_cast<void> (0)

#endif // !YYDEBUG

#define yyerrok         (yyerrstatus_ = 0)
#define yyclearin       (yyla.clear ())

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab
#define YYRECOVERING()  (!!yyerrstatus_)

#line 5 "a.yy"
namespace a_lang {
#line 137 "parser.cc"

  /// Build a parser object.
  Parser::Parser (a_lang::Scanner &scanner_yyarg, a_lang::ProgramNode** root_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg),
      root (root_yyarg)
  {}

  Parser::~Parser ()
  {}

  Parser::syntax_error::~syntax_error () YY_NOEXCEPT YY_NOTHROW
  {}

  /*---------.
  | symbol.  |
  `---------*/

  // basic_symbol.
  template <typename Base>
  Parser::basic_symbol<Base>::basic_symbol (const basic_symbol& that)
    : Base (that)
    , value ()
  {
    switch (this->kind ())
    {
      case symbol_kind::S_callExp: // callExp
        value.copy< a_lang::CallExpNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classTypeDecl: // classTypeDecl
        value.copy< a_lang::ClassDefnNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
        value.copy< a_lang::DeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
        value.copy< a_lang::ExpNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fnDecl: // fnDecl
        value.copy< a_lang::FnDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formalDecl: // formalDecl
        value.copy< a_lang::FormalDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.copy< a_lang::IDNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.copy< a_lang::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< a_lang::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.copy< a_lang::LocNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.copy< a_lang::ProgramNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_blockStmt: // blockStmt
      case symbol_kind::S_stmt: // stmt
        value.copy< a_lang::StmtNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.copy< a_lang::StrToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AND: // AND
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_CUSTOM: // CUSTOM
      case symbol_kind::S_DASH: // DASH
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_EH: // EH
      case symbol_kind::S_EQUALS: // EQUALS
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FROMCONSOLE: // FROMCONSOLE
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQ: // GREATEREQ
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_IMMUTABLE: // IMMUTABLE
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQ: // LESSEQ
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_MAYBE: // MAYBE
      case symbol_kind::S_MEANS: // MEANS
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_NOTEQUALS: // NOTEQUALS
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_OTHERWISE: // OTHERWISE
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTDEC: // POSTDEC
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_REF: // REF
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_TOCONSOLE: // TOCONSOLE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_WHILE: // WHILE
        value.copy< a_lang::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_datatype: // datatype
      case symbol_kind::S_primType: // primType
        value.copy< a_lang::TypeNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.copy< a_lang::VarDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_globals: // globals
      case symbol_kind::S_classBody: // classBody
        value.copy< std::list<a_lang::DeclNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actualList: // actualList
        value.copy< std::list<a_lang::ExpNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_maybeFormals: // maybeFormals
      case symbol_kind::S_formalList: // formalList
        value.copy< std::list<a_lang::FormalDeclNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmtList: // stmtList
        value.copy< std::list<a_lang::StmtNode *> * > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

  }




  template <typename Base>
  Parser::symbol_kind_type
  Parser::basic_symbol<Base>::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }


  template <typename Base>
  bool
  Parser::basic_symbol<Base>::empty () const YY_NOEXCEPT
  {
    return this->kind () == symbol_kind::S_YYEMPTY;
  }

  template <typename Base>
  void
  Parser::basic_symbol<Base>::move (basic_symbol& s)
  {
    super_type::move (s);
    switch (this->kind ())
    {
      case symbol_kind::S_callExp: // callExp
        value.move< a_lang::CallExpNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_classTypeDecl: // classTypeDecl
        value.move< a_lang::ClassDefnNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_decl: // decl
        value.move< a_lang::DeclNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
        value.move< a_lang::ExpNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_fnDecl: // fnDecl
        value.move< a_lang::FnDeclNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_formalDecl: // formalDecl
        value.move< a_lang::FormalDeclNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_name: // name
        value.move< a_lang::IDNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< a_lang::IDToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< a_lang::IntLitToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_loc: // loc
        value.move< a_lang::LocNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_program: // program
        value.move< a_lang::ProgramNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_blockStmt: // blockStmt
      case symbol_kind::S_stmt: // stmt
        value.move< a_lang::StmtNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.move< a_lang::StrToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_AND: // AND
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_CUSTOM: // CUSTOM
      case symbol_kind::S_DASH: // DASH
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_EH: // EH
      case symbol_kind::S_EQUALS: // EQUALS
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FROMCONSOLE: // FROMCONSOLE
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQ: // GREATEREQ
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_IMMUTABLE: // IMMUTABLE
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQ: // LESSEQ
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_MAYBE: // MAYBE
      case symbol_kind::S_MEANS: // MEANS
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_NOTEQUALS: // NOTEQUALS
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_OTHERWISE: // OTHERWISE
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTDEC: // POSTDEC
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_REF: // REF
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_TOCONSOLE: // TOCONSOLE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_WHILE: // WHILE
        value.move< a_lang::Token * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_datatype: // datatype
      case symbol_kind::S_primType: // primType
        value.move< a_lang::TypeNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.move< a_lang::VarDeclNode * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_globals: // globals
      case symbol_kind::S_classBody: // classBody
        value.move< std::list<a_lang::DeclNode *> * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_actualList: // actualList
        value.move< std::list<a_lang::ExpNode *> * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_maybeFormals: // maybeFormals
      case symbol_kind::S_formalList: // formalList
        value.move< std::list<a_lang::FormalDeclNode *> * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_stmtList: // stmtList
        value.move< std::list<a_lang::StmtNode *> * > (YY_MOVE (s.value));
        break;

      default:
        break;
    }

  }

  // by_kind.
  Parser::by_kind::by_kind () YY_NOEXCEPT
    : kind_ (symbol_kind::S_YYEMPTY)
  {}

#if 201103L <= YY_CPLUSPLUS
  Parser::by_kind::by_kind (by_kind&& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {
    that.clear ();
  }
#endif

  Parser::by_kind::by_kind (const by_kind& that) YY_NOEXCEPT
    : kind_ (that.kind_)
  {}

  Parser::by_kind::by_kind (token_kind_type t) YY_NOEXCEPT
    : kind_ (yytranslate_ (t))
  {}



  void
  Parser::by_kind::clear () YY_NOEXCEPT
  {
    kind_ = symbol_kind::S_YYEMPTY;
  }

  void
  Parser::by_kind::move (by_kind& that)
  {
    kind_ = that.kind_;
    that.clear ();
  }

  Parser::symbol_kind_type
  Parser::by_kind::kind () const YY_NOEXCEPT
  {
    return kind_;
  }


  Parser::symbol_kind_type
  Parser::by_kind::type_get () const YY_NOEXCEPT
  {
    return this->kind ();
  }



  // by_state.
  Parser::by_state::by_state () YY_NOEXCEPT
    : state (empty_state)
  {}

  Parser::by_state::by_state (const by_state& that) YY_NOEXCEPT
    : state (that.state)
  {}

  void
  Parser::by_state::clear () YY_NOEXCEPT
  {
    state = empty_state;
  }

  void
  Parser::by_state::move (by_state& that)
  {
    state = that.state;
    that.clear ();
  }

  Parser::by_state::by_state (state_type s) YY_NOEXCEPT
    : state (s)
  {}

  Parser::symbol_kind_type
  Parser::by_state::kind () const YY_NOEXCEPT
  {
    if (state == empty_state)
      return symbol_kind::S_YYEMPTY;
    else
      return YY_CAST (symbol_kind_type, yystos_[+state]);
  }

  Parser::stack_symbol_type::stack_symbol_type ()
  {}

  Parser::stack_symbol_type::stack_symbol_type (YY_RVREF (stack_symbol_type) that)
    : super_type (YY_MOVE (that.state))
  {
    switch (that.kind ())
    {
      case symbol_kind::S_callExp: // callExp
        value.YY_MOVE_OR_COPY< a_lang::CallExpNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classTypeDecl: // classTypeDecl
        value.YY_MOVE_OR_COPY< a_lang::ClassDefnNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
        value.YY_MOVE_OR_COPY< a_lang::DeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
        value.YY_MOVE_OR_COPY< a_lang::ExpNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fnDecl: // fnDecl
        value.YY_MOVE_OR_COPY< a_lang::FnDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formalDecl: // formalDecl
        value.YY_MOVE_OR_COPY< a_lang::FormalDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.YY_MOVE_OR_COPY< a_lang::IDNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.YY_MOVE_OR_COPY< a_lang::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.YY_MOVE_OR_COPY< a_lang::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.YY_MOVE_OR_COPY< a_lang::LocNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.YY_MOVE_OR_COPY< a_lang::ProgramNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_blockStmt: // blockStmt
      case symbol_kind::S_stmt: // stmt
        value.YY_MOVE_OR_COPY< a_lang::StmtNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.YY_MOVE_OR_COPY< a_lang::StrToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AND: // AND
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_CUSTOM: // CUSTOM
      case symbol_kind::S_DASH: // DASH
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_EH: // EH
      case symbol_kind::S_EQUALS: // EQUALS
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FROMCONSOLE: // FROMCONSOLE
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQ: // GREATEREQ
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_IMMUTABLE: // IMMUTABLE
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQ: // LESSEQ
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_MAYBE: // MAYBE
      case symbol_kind::S_MEANS: // MEANS
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_NOTEQUALS: // NOTEQUALS
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_OTHERWISE: // OTHERWISE
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTDEC: // POSTDEC
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_REF: // REF
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_TOCONSOLE: // TOCONSOLE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_WHILE: // WHILE
        value.YY_MOVE_OR_COPY< a_lang::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_datatype: // datatype
      case symbol_kind::S_primType: // primType
        value.YY_MOVE_OR_COPY< a_lang::TypeNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.YY_MOVE_OR_COPY< a_lang::VarDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_globals: // globals
      case symbol_kind::S_classBody: // classBody
        value.YY_MOVE_OR_COPY< std::list<a_lang::DeclNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actualList: // actualList
        value.YY_MOVE_OR_COPY< std::list<a_lang::ExpNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_maybeFormals: // maybeFormals
      case symbol_kind::S_formalList: // formalList
        value.YY_MOVE_OR_COPY< std::list<a_lang::FormalDeclNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmtList: // stmtList
        value.YY_MOVE_OR_COPY< std::list<a_lang::StmtNode *> * > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

#if 201103L <= YY_CPLUSPLUS
    // that is emptied.
    that.state = empty_state;
#endif
  }

  Parser::stack_symbol_type::stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) that)
    : super_type (s)
  {
    switch (that.kind ())
    {
      case symbol_kind::S_callExp: // callExp
        value.move< a_lang::CallExpNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_classTypeDecl: // classTypeDecl
        value.move< a_lang::ClassDefnNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_decl: // decl
        value.move< a_lang::DeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
        value.move< a_lang::ExpNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_fnDecl: // fnDecl
        value.move< a_lang::FnDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_formalDecl: // formalDecl
        value.move< a_lang::FormalDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_name: // name
        value.move< a_lang::IDNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_ID: // ID
        value.move< a_lang::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< a_lang::IntLitToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_loc: // loc
        value.move< a_lang::LocNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_program: // program
        value.move< a_lang::ProgramNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_blockStmt: // blockStmt
      case symbol_kind::S_stmt: // stmt
        value.move< a_lang::StmtNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.move< a_lang::StrToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_AND: // AND
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_CUSTOM: // CUSTOM
      case symbol_kind::S_DASH: // DASH
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_EH: // EH
      case symbol_kind::S_EQUALS: // EQUALS
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FROMCONSOLE: // FROMCONSOLE
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQ: // GREATEREQ
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_IMMUTABLE: // IMMUTABLE
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQ: // LESSEQ
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_MAYBE: // MAYBE
      case symbol_kind::S_MEANS: // MEANS
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_NOTEQUALS: // NOTEQUALS
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_OTHERWISE: // OTHERWISE
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTDEC: // POSTDEC
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_REF: // REF
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_TOCONSOLE: // TOCONSOLE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_WHILE: // WHILE
        value.move< a_lang::Token * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_datatype: // datatype
      case symbol_kind::S_primType: // primType
        value.move< a_lang::TypeNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.move< a_lang::VarDeclNode * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_globals: // globals
      case symbol_kind::S_classBody: // classBody
        value.move< std::list<a_lang::DeclNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_actualList: // actualList
        value.move< std::list<a_lang::ExpNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_maybeFormals: // maybeFormals
      case symbol_kind::S_formalList: // formalList
        value.move< std::list<a_lang::FormalDeclNode *> * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_stmtList: // stmtList
        value.move< std::list<a_lang::StmtNode *> * > (YY_MOVE (that.value));
        break;

      default:
        break;
    }

    // that is emptied.
    that.kind_ = symbol_kind::S_YYEMPTY;
  }

#if YY_CPLUSPLUS < 201103L
  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (const stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_callExp: // callExp
        value.copy< a_lang::CallExpNode * > (that.value);
        break;

      case symbol_kind::S_classTypeDecl: // classTypeDecl
        value.copy< a_lang::ClassDefnNode * > (that.value);
        break;

      case symbol_kind::S_decl: // decl
        value.copy< a_lang::DeclNode * > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
        value.copy< a_lang::ExpNode * > (that.value);
        break;

      case symbol_kind::S_fnDecl: // fnDecl
        value.copy< a_lang::FnDeclNode * > (that.value);
        break;

      case symbol_kind::S_formalDecl: // formalDecl
        value.copy< a_lang::FormalDeclNode * > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.copy< a_lang::IDNode * > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.copy< a_lang::IDToken * > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< a_lang::IntLitToken * > (that.value);
        break;

      case symbol_kind::S_loc: // loc
        value.copy< a_lang::LocNode * > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.copy< a_lang::ProgramNode * > (that.value);
        break;

      case symbol_kind::S_blockStmt: // blockStmt
      case symbol_kind::S_stmt: // stmt
        value.copy< a_lang::StmtNode * > (that.value);
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.copy< a_lang::StrToken * > (that.value);
        break;

      case symbol_kind::S_AND: // AND
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_CUSTOM: // CUSTOM
      case symbol_kind::S_DASH: // DASH
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_EH: // EH
      case symbol_kind::S_EQUALS: // EQUALS
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FROMCONSOLE: // FROMCONSOLE
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQ: // GREATEREQ
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_IMMUTABLE: // IMMUTABLE
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQ: // LESSEQ
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_MAYBE: // MAYBE
      case symbol_kind::S_MEANS: // MEANS
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_NOTEQUALS: // NOTEQUALS
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_OTHERWISE: // OTHERWISE
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTDEC: // POSTDEC
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_REF: // REF
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_TOCONSOLE: // TOCONSOLE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_WHILE: // WHILE
        value.copy< a_lang::Token * > (that.value);
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_datatype: // datatype
      case symbol_kind::S_primType: // primType
        value.copy< a_lang::TypeNode * > (that.value);
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.copy< a_lang::VarDeclNode * > (that.value);
        break;

      case symbol_kind::S_globals: // globals
      case symbol_kind::S_classBody: // classBody
        value.copy< std::list<a_lang::DeclNode *> * > (that.value);
        break;

      case symbol_kind::S_actualList: // actualList
        value.copy< std::list<a_lang::ExpNode *> * > (that.value);
        break;

      case symbol_kind::S_maybeFormals: // maybeFormals
      case symbol_kind::S_formalList: // formalList
        value.copy< std::list<a_lang::FormalDeclNode *> * > (that.value);
        break;

      case symbol_kind::S_stmtList: // stmtList
        value.copy< std::list<a_lang::StmtNode *> * > (that.value);
        break;

      default:
        break;
    }

    return *this;
  }

  Parser::stack_symbol_type&
  Parser::stack_symbol_type::operator= (stack_symbol_type& that)
  {
    state = that.state;
    switch (that.kind ())
    {
      case symbol_kind::S_callExp: // callExp
        value.move< a_lang::CallExpNode * > (that.value);
        break;

      case symbol_kind::S_classTypeDecl: // classTypeDecl
        value.move< a_lang::ClassDefnNode * > (that.value);
        break;

      case symbol_kind::S_decl: // decl
        value.move< a_lang::DeclNode * > (that.value);
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
        value.move< a_lang::ExpNode * > (that.value);
        break;

      case symbol_kind::S_fnDecl: // fnDecl
        value.move< a_lang::FnDeclNode * > (that.value);
        break;

      case symbol_kind::S_formalDecl: // formalDecl
        value.move< a_lang::FormalDeclNode * > (that.value);
        break;

      case symbol_kind::S_name: // name
        value.move< a_lang::IDNode * > (that.value);
        break;

      case symbol_kind::S_ID: // ID
        value.move< a_lang::IDToken * > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< a_lang::IntLitToken * > (that.value);
        break;

      case symbol_kind::S_loc: // loc
        value.move< a_lang::LocNode * > (that.value);
        break;

      case symbol_kind::S_program: // program
        value.move< a_lang::ProgramNode * > (that.value);
        break;

      case symbol_kind::S_blockStmt: // blockStmt
      case symbol_kind::S_stmt: // stmt
        value.move< a_lang::StmtNode * > (that.value);
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.move< a_lang::StrToken * > (that.value);
        break;

      case symbol_kind::S_AND: // AND
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_CUSTOM: // CUSTOM
      case symbol_kind::S_DASH: // DASH
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_EH: // EH
      case symbol_kind::S_EQUALS: // EQUALS
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FROMCONSOLE: // FROMCONSOLE
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQ: // GREATEREQ
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_IMMUTABLE: // IMMUTABLE
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQ: // LESSEQ
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_MAYBE: // MAYBE
      case symbol_kind::S_MEANS: // MEANS
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_NOTEQUALS: // NOTEQUALS
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_OTHERWISE: // OTHERWISE
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTDEC: // POSTDEC
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_REF: // REF
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_TOCONSOLE: // TOCONSOLE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_WHILE: // WHILE
        value.move< a_lang::Token * > (that.value);
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_datatype: // datatype
      case symbol_kind::S_primType: // primType
        value.move< a_lang::TypeNode * > (that.value);
        break;

      case symbol_kind::S_varDecl: // varDecl
        value.move< a_lang::VarDeclNode * > (that.value);
        break;

      case symbol_kind::S_globals: // globals
      case symbol_kind::S_classBody: // classBody
        value.move< std::list<a_lang::DeclNode *> * > (that.value);
        break;

      case symbol_kind::S_actualList: // actualList
        value.move< std::list<a_lang::ExpNode *> * > (that.value);
        break;

      case symbol_kind::S_maybeFormals: // maybeFormals
      case symbol_kind::S_formalList: // formalList
        value.move< std::list<a_lang::FormalDeclNode *> * > (that.value);
        break;

      case symbol_kind::S_stmtList: // stmtList
        value.move< std::list<a_lang::StmtNode *> * > (that.value);
        break;

      default:
        break;
    }

    // that is emptied.
    that.state = empty_state;
    return *this;
  }
#endif

  template <typename Base>
  void
  Parser::yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const
  {
    if (yymsg)
      YY_SYMBOL_PRINT (yymsg, yysym);
  }

#if YYDEBUG
  template <typename Base>
  void
  Parser::yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const
  {
    std::ostream& yyoutput = yyo;
    YY_USE (yyoutput);
    if (yysym.empty ())
      yyo << "empty symbol";
    else
      {
        symbol_kind_type yykind = yysym.kind ();
        yyo << (yykind < YYNTOKENS ? "token" : "nterm")
            << ' ' << yysym.name () << " (";
        YY_USE (yykind);
        yyo << ')';
      }
  }
#endif

  void
  Parser::yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym)
  {
    if (m)
      YY_SYMBOL_PRINT (m, sym);
    yystack_.push (YY_MOVE (sym));
  }

  void
  Parser::yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym)
  {
#if 201103L <= YY_CPLUSPLUS
    yypush_ (m, stack_symbol_type (s, std::move (sym)));
#else
    stack_symbol_type ss (s, sym);
    yypush_ (m, ss);
#endif
  }

  void
  Parser::yypop_ (int n) YY_NOEXCEPT
  {
    yystack_.pop (n);
  }

#if YYDEBUG
  std::ostream&
  Parser::debug_stream () const
  {
    return *yycdebug_;
  }

  void
  Parser::set_debug_stream (std::ostream& o)
  {
    yycdebug_ = &o;
  }


  Parser::debug_level_type
  Parser::debug_level () const
  {
    return yydebug_;
  }

  void
  Parser::set_debug_level (debug_level_type l)
  {
    yydebug_ = l;
  }
#endif // YYDEBUG

  Parser::state_type
  Parser::yy_lr_goto_state_ (state_type yystate, int yysym)
  {
    int yyr = yypgoto_[yysym - YYNTOKENS] + yystate;
    if (0 <= yyr && yyr <= yylast_ && yycheck_[yyr] == yystate)
      return yytable_[yyr];
    else
      return yydefgoto_[yysym - YYNTOKENS];
  }

  bool
  Parser::yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yypact_ninf_;
  }

  bool
  Parser::yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT
  {
    return yyvalue == yytable_ninf_;
  }

  int
  Parser::operator() ()
  {
    return parse ();
  }

  int
  Parser::parse ()
  {
    int yyn;
    /// Length of the RHS of the rule being reduced.
    int yylen = 0;

    // Error handling.
    int yynerrs_ = 0;
    int yyerrstatus_ = 0;

    /// The lookahead symbol.
    symbol_type yyla;

    /// The return value of parse ().
    int yyresult;

#if YY_EXCEPTIONS
    try
#endif // YY_EXCEPTIONS
      {
    YYCDEBUG << "Starting parse\n";


    /* Initialize the stack.  The initial state will be set in
       yynewstate, since the latter expects the semantical and the
       location values to have been already stored, initialize these
       stacks with a primary value.  */
    yystack_.clear ();
    yypush_ (YY_NULLPTR, 0, YY_MOVE (yyla));

  /*-----------------------------------------------.
  | yynewstate -- push a new symbol on the stack.  |
  `-----------------------------------------------*/
  yynewstate:
    YYCDEBUG << "Entering state " << int (yystack_[0].state) << '\n';
    YY_STACK_PRINT ();

    // Accept?
    if (yystack_[0].state == yyfinal_)
      YYACCEPT;

    goto yybackup;


  /*-----------.
  | yybackup.  |
  `-----------*/
  yybackup:
    // Try to take a decision without lookahead.
    yyn = yypact_[+yystack_[0].state];
    if (yy_pact_value_is_default_ (yyn))
      goto yydefault;

    // Read a lookahead token.
    if (yyla.empty ())
      {
        YYCDEBUG << "Reading a token\n";
#if YY_EXCEPTIONS
        try
#endif // YY_EXCEPTIONS
          {
            yyla.kind_ = yytranslate_ (yylex (&yyla.value));
          }
#if YY_EXCEPTIONS
        catch (const syntax_error& yyexc)
          {
            YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
            error (yyexc);
            goto yyerrlab1;
          }
#endif // YY_EXCEPTIONS
      }
    YY_SYMBOL_PRINT ("Next token is", yyla);

    if (yyla.kind () == symbol_kind::S_YYerror)
    {
      // The scanner already issued an error message, process directly
      // to error recovery.  But do not keep the error token as
      // lookahead, it is too special and may lead us to an endless
      // loop in error recovery. */
      yyla.kind_ = symbol_kind::S_YYUNDEF;
      goto yyerrlab1;
    }

    /* If the proper action on seeing token YYLA.TYPE is to reduce or
       to detect an error, take that action.  */
    yyn += yyla.kind ();
    if (yyn < 0 || yylast_ < yyn || yycheck_[yyn] != yyla.kind ())
      {
        goto yydefault;
      }

    // Reduce or error.
    yyn = yytable_[yyn];
    if (yyn <= 0)
      {
        if (yy_table_value_is_error_ (yyn))
          goto yyerrlab;
        yyn = -yyn;
        goto yyreduce;
      }

    // Count tokens shifted since error; after three, turn off error status.
    if (yyerrstatus_)
      --yyerrstatus_;

    // Shift the lookahead token.
    yypush_ ("Shifting", state_type (yyn), YY_MOVE (yyla));
    goto yynewstate;


  /*-----------------------------------------------------------.
  | yydefault -- do the default action for the current state.  |
  `-----------------------------------------------------------*/
  yydefault:
    yyn = yydefact_[+yystack_[0].state];
    if (yyn == 0)
      goto yyerrlab;
    goto yyreduce;


  /*-----------------------------.
  | yyreduce -- do a reduction.  |
  `-----------------------------*/
  yyreduce:
    yylen = yyr2_[yyn];
    {
      stack_symbol_type yylhs;
      yylhs.state = yy_lr_goto_state_ (yystack_[yylen].state, yyr1_[yyn]);
      /* Variants are always initialized to an empty instance of the
         correct type. The default '$$ = $1' action is NOT applied
         when using variants.  */
      switch (yyr1_[yyn])
    {
      case symbol_kind::S_callExp: // callExp
        yylhs.value.emplace< a_lang::CallExpNode * > ();
        break;

      case symbol_kind::S_classTypeDecl: // classTypeDecl
        yylhs.value.emplace< a_lang::ClassDefnNode * > ();
        break;

      case symbol_kind::S_decl: // decl
        yylhs.value.emplace< a_lang::DeclNode * > ();
        break;

      case symbol_kind::S_exp: // exp
      case symbol_kind::S_term: // term
        yylhs.value.emplace< a_lang::ExpNode * > ();
        break;

      case symbol_kind::S_fnDecl: // fnDecl
        yylhs.value.emplace< a_lang::FnDeclNode * > ();
        break;

      case symbol_kind::S_formalDecl: // formalDecl
        yylhs.value.emplace< a_lang::FormalDeclNode * > ();
        break;

      case symbol_kind::S_name: // name
        yylhs.value.emplace< a_lang::IDNode * > ();
        break;

      case symbol_kind::S_ID: // ID
        yylhs.value.emplace< a_lang::IDToken * > ();
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        yylhs.value.emplace< a_lang::IntLitToken * > ();
        break;

      case symbol_kind::S_loc: // loc
        yylhs.value.emplace< a_lang::LocNode * > ();
        break;

      case symbol_kind::S_program: // program
        yylhs.value.emplace< a_lang::ProgramNode * > ();
        break;

      case symbol_kind::S_blockStmt: // blockStmt
      case symbol_kind::S_stmt: // stmt
        yylhs.value.emplace< a_lang::StmtNode * > ();
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        yylhs.value.emplace< a_lang::StrToken * > ();
        break;

      case symbol_kind::S_AND: // AND
      case symbol_kind::S_ASSIGN: // ASSIGN
      case symbol_kind::S_ARROW: // ARROW
      case symbol_kind::S_BOOL: // BOOL
      case symbol_kind::S_COLON: // COLON
      case symbol_kind::S_COMMA: // COMMA
      case symbol_kind::S_CUSTOM: // CUSTOM
      case symbol_kind::S_DASH: // DASH
      case symbol_kind::S_ELSE: // ELSE
      case symbol_kind::S_EH: // EH
      case symbol_kind::S_EQUALS: // EQUALS
      case symbol_kind::S_FALSE: // FALSE
      case symbol_kind::S_FROMCONSOLE: // FROMCONSOLE
      case symbol_kind::S_GREATER: // GREATER
      case symbol_kind::S_GREATEREQ: // GREATEREQ
      case symbol_kind::S_IF: // IF
      case symbol_kind::S_INT: // INT
      case symbol_kind::S_IMMUTABLE: // IMMUTABLE
      case symbol_kind::S_LCURLY: // LCURLY
      case symbol_kind::S_LESS: // LESS
      case symbol_kind::S_LESSEQ: // LESSEQ
      case symbol_kind::S_LPAREN: // LPAREN
      case symbol_kind::S_MAYBE: // MAYBE
      case symbol_kind::S_MEANS: // MEANS
      case symbol_kind::S_NOT: // NOT
      case symbol_kind::S_NOTEQUALS: // NOTEQUALS
      case symbol_kind::S_OR: // OR
      case symbol_kind::S_OTHERWISE: // OTHERWISE
      case symbol_kind::S_CROSS: // CROSS
      case symbol_kind::S_POSTDEC: // POSTDEC
      case symbol_kind::S_POSTINC: // POSTINC
      case symbol_kind::S_RETURN: // RETURN
      case symbol_kind::S_RCURLY: // RCURLY
      case symbol_kind::S_REF: // REF
      case symbol_kind::S_RPAREN: // RPAREN
      case symbol_kind::S_SEMICOL: // SEMICOL
      case symbol_kind::S_SLASH: // SLASH
      case symbol_kind::S_STAR: // STAR
      case symbol_kind::S_TOCONSOLE: // TOCONSOLE
      case symbol_kind::S_TRUE: // TRUE
      case symbol_kind::S_VOID: // VOID
      case symbol_kind::S_WHILE: // WHILE
        yylhs.value.emplace< a_lang::Token * > ();
        break;

      case symbol_kind::S_type: // type
      case symbol_kind::S_datatype: // datatype
      case symbol_kind::S_primType: // primType
        yylhs.value.emplace< a_lang::TypeNode * > ();
        break;

      case symbol_kind::S_varDecl: // varDecl
        yylhs.value.emplace< a_lang::VarDeclNode * > ();
        break;

      case symbol_kind::S_globals: // globals
      case symbol_kind::S_classBody: // classBody
        yylhs.value.emplace< std::list<a_lang::DeclNode *> * > ();
        break;

      case symbol_kind::S_actualList: // actualList
        yylhs.value.emplace< std::list<a_lang::ExpNode *> * > ();
        break;

      case symbol_kind::S_maybeFormals: // maybeFormals
      case symbol_kind::S_formalList: // formalList
        yylhs.value.emplace< std::list<a_lang::FormalDeclNode *> * > ();
        break;

      case symbol_kind::S_stmtList: // stmtList
        yylhs.value.emplace< std::list<a_lang::StmtNode *> * > ();
        break;

      default:
        break;
    }



      // Perform the reduction.
      YY_REDUCE_PRINT (yyn);
#if YY_EXCEPTIONS
      try
#endif // YY_EXCEPTIONS
        {
          switch (yyn)
            {
  case 2: // program: globals
#line 147 "a.yy"
                  {
		  DEBUG_PRINT("program\n");
		  yylhs.value.as < a_lang::ProgramNode * > () = new ProgramNode(yystack_[0].value.as < std::list<a_lang::DeclNode *> * > ());
		  *root = yylhs.value.as < a_lang::ProgramNode * > ();
		  DEBUG_PRINT("program done\n");
		  }
#line 1507 "parser.cc"
    break;

  case 3: // globals: globals decl
#line 155 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::DeclNode *> * > () = yystack_[1].value.as < std::list<a_lang::DeclNode *> * > ();
		  DeclNode * declNode = yystack_[0].value.as < a_lang::DeclNode * > ();
		  yylhs.value.as < std::list<a_lang::DeclNode *> * > ()->push_back(declNode);
		  }
#line 1517 "parser.cc"
    break;

  case 4: // globals: %empty
#line 161 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::DeclNode *> * > () = new std::list<DeclNode *>();
		  }
#line 1525 "parser.cc"
    break;

  case 5: // decl: varDecl SEMICOL
#line 166 "a.yy"
                  {
		  yylhs.value.as < a_lang::DeclNode * > () = yystack_[1].value.as < a_lang::VarDeclNode * > ();
		  }
#line 1533 "parser.cc"
    break;

  case 6: // decl: classTypeDecl
#line 170 "a.yy"
                  {
	      yylhs.value.as < a_lang::DeclNode * > () = yystack_[0].value.as < a_lang::ClassDefnNode * > ();
		  }
#line 1541 "parser.cc"
    break;

  case 7: // decl: fnDecl
#line 174 "a.yy"
                  {
		  yylhs.value.as < a_lang::DeclNode * > () = yystack_[0].value.as < a_lang::FnDeclNode * > ();
		  }
#line 1549 "parser.cc"
    break;

  case 8: // varDecl: name COLON type
#line 179 "a.yy"
                  {
		  const Position * p;
		  p = new Position(yystack_[2].value.as < a_lang::IDNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::VarDeclNode * > () = new VarDeclNode(p, yystack_[2].value.as < a_lang::IDNode * > (), yystack_[0].value.as < a_lang::TypeNode * > ());
		  }
#line 1559 "parser.cc"
    break;

  case 9: // varDecl: name COLON type ASSIGN exp
#line 185 "a.yy"
                  {
		  const Position * p;
		  p = new Position(yystack_[4].value.as < a_lang::IDNode * > ()->pos(), yystack_[3].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::VarDeclNode * > () = new VarDeclNode(p, yystack_[4].value.as < a_lang::IDNode * > (), yystack_[2].value.as < a_lang::TypeNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1569 "parser.cc"
    break;

  case 10: // type: IMMUTABLE datatype
#line 192 "a.yy"
                  {
		  yylhs.value.as < a_lang::TypeNode * > () = new ImmutableTypeNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::TypeNode * > ());
		  }
#line 1577 "parser.cc"
    break;

  case 11: // type: datatype
#line 196 "a.yy"
                  {
		  yylhs.value.as < a_lang::TypeNode * > () = yystack_[0].value.as < a_lang::TypeNode * > ();
		  }
#line 1585 "parser.cc"
    break;

  case 12: // datatype: REF primType
#line 201 "a.yy"
                  {
	      yylhs.value.as < a_lang::TypeNode * > () = new RefTypeNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::TypeNode * > ());
		  }
#line 1593 "parser.cc"
    break;

  case 13: // datatype: primType
#line 205 "a.yy"
                  {
		  yylhs.value.as < a_lang::TypeNode * > () = yystack_[0].value.as < a_lang::TypeNode * > ();
		  }
#line 1601 "parser.cc"
    break;

  case 14: // datatype: REF name
#line 209 "a.yy"
                  {
	      yylhs.value.as < a_lang::TypeNode * > () = new RefTypeNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::IDNode * > ());
		  }
#line 1609 "parser.cc"
    break;

  case 15: // datatype: name
#line 213 "a.yy"
                  {
		  yylhs.value.as < a_lang::TypeNode * > () = new ClassTypeNode(yystack_[0].value.as < a_lang::IDNode * > ()->pos(), yystack_[0].value.as < a_lang::IDNode * > ());
		  }
#line 1617 "parser.cc"
    break;

  case 16: // primType: INT
#line 218 "a.yy"
                  {
		  yylhs.value.as < a_lang::TypeNode * > () = new IntTypeNode(yystack_[0].value.as < a_lang::Token * > ()->pos());
		  }
#line 1625 "parser.cc"
    break;

  case 17: // primType: BOOL
#line 222 "a.yy"
                  {
		  yylhs.value.as < a_lang::TypeNode * > () = new BoolTypeNode(yystack_[0].value.as < a_lang::Token * > ()->pos());
		  }
#line 1633 "parser.cc"
    break;

  case 18: // primType: VOID
#line 226 "a.yy"
                  {
		  yylhs.value.as < a_lang::TypeNode * > () = new VoidTypeNode(yystack_[0].value.as < a_lang::Token * > ()->pos());
		  }
#line 1641 "parser.cc"
    break;

  case 19: // classTypeDecl: name COLON CUSTOM LCURLY classBody RCURLY SEMICOL
#line 231 "a.yy"
                  {
		  const Position * p = new Position(yystack_[6].value.as < a_lang::IDNode * > ()->pos(), yystack_[5].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ClassDefnNode * > () = new ClassDefnNode(p, yystack_[6].value.as < a_lang::IDNode * > (), yystack_[2].value.as < std::list<a_lang::DeclNode *> * > ());
		  }
#line 1650 "parser.cc"
    break;

  case 20: // classBody: classBody varDecl SEMICOL
#line 237 "a.yy"
                  {
		  yystack_[2].value.as < std::list<a_lang::DeclNode *> * > ()->push_back(yystack_[1].value.as < a_lang::VarDeclNode * > ());
		  yylhs.value.as < std::list<a_lang::DeclNode *> * > () = yystack_[2].value.as < std::list<a_lang::DeclNode *> * > ();
		  }
#line 1659 "parser.cc"
    break;

  case 21: // classBody: classBody fnDecl
#line 242 "a.yy"
                  {
		  yystack_[1].value.as < std::list<a_lang::DeclNode *> * > ()->push_back(yystack_[0].value.as < a_lang::FnDeclNode * > ());
		  yylhs.value.as < std::list<a_lang::DeclNode *> * > () = yystack_[1].value.as < std::list<a_lang::DeclNode *> * > ();
		  }
#line 1668 "parser.cc"
    break;

  case 22: // classBody: %empty
#line 247 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::DeclNode *> * > () = new std::list<DeclNode *>();
		  }
#line 1676 "parser.cc"
    break;

  case 23: // fnDecl: name COLON LPAREN maybeFormals RPAREN ARROW type LCURLY stmtList RCURLY
#line 252 "a.yy"
                  {
		  DEBUG_PRINT("fnDecl\n");
		  const Position * p;
		  p = new Position(yystack_[9].value.as < a_lang::IDNode * > ()->pos(), yystack_[8].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::FnDeclNode * > () = new FnDeclNode(p, yystack_[9].value.as < a_lang::IDNode * > (), yystack_[3].value.as < a_lang::TypeNode * > (), yystack_[6].value.as < std::list<a_lang::FormalDeclNode *> * > (), yystack_[1].value.as < std::list<a_lang::StmtNode *> * > ());
		  DEBUG_PRINT("fnDecl done\n");
		  }
#line 1688 "parser.cc"
    break;

  case 24: // maybeFormals: %empty
#line 261 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::FormalDeclNode *> * > () = new std::list<FormalDeclNode *>();
		  }
#line 1696 "parser.cc"
    break;

  case 25: // maybeFormals: formalList
#line 265 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::FormalDeclNode *> * > () = yystack_[0].value.as < std::list<a_lang::FormalDeclNode *> * > ();
		  }
#line 1704 "parser.cc"
    break;

  case 26: // formalList: formalDecl
#line 270 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::FormalDeclNode *> * > () = new std::list<FormalDeclNode *>();
		  yylhs.value.as < std::list<a_lang::FormalDeclNode *> * > ()->push_back(yystack_[0].value.as < a_lang::FormalDeclNode * > ());
		  }
#line 1713 "parser.cc"
    break;

  case 27: // formalList: formalList COMMA formalDecl
#line 275 "a.yy"
                  {
		  yystack_[2].value.as < std::list<a_lang::FormalDeclNode *> * > ()->push_back(yystack_[0].value.as < a_lang::FormalDeclNode * > ());
		  yylhs.value.as < std::list<a_lang::FormalDeclNode *> * > () = yystack_[2].value.as < std::list<a_lang::FormalDeclNode *> * > ();
		  }
#line 1722 "parser.cc"
    break;

  case 28: // formalDecl: name COLON type
#line 281 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::IDNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::FormalDeclNode * > () = new FormalDeclNode(p, yystack_[2].value.as < a_lang::IDNode * > (), yystack_[0].value.as < a_lang::TypeNode * > ());
		  }
#line 1731 "parser.cc"
    break;

  case 29: // stmtList: %empty
#line 287 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::StmtNode *> * > () = new std::list<StmtNode *>();
		  }
#line 1739 "parser.cc"
    break;

  case 30: // stmtList: stmtList stmt SEMICOL
#line 291 "a.yy"
                  {
		  DEBUG_PRINT("stmtList stmt\n");
		  yystack_[2].value.as < std::list<a_lang::StmtNode *> * > ()->push_back(yystack_[1].value.as < a_lang::StmtNode * > ());
		  yylhs.value.as < std::list<a_lang::StmtNode *> * > () = yystack_[2].value.as < std::list<a_lang::StmtNode *> * > ();
		  DEBUG_PRINT("stmtList stmt done\n");
		  }
#line 1750 "parser.cc"
    break;

  case 31: // stmtList: stmtList blockStmt
#line 298 "a.yy"
                  {
		  yystack_[1].value.as < std::list<a_lang::StmtNode *> * > ()->push_back(yystack_[0].value.as < a_lang::StmtNode * > ());
		  yylhs.value.as < std::list<a_lang::StmtNode *> * > () = yystack_[1].value.as < std::list<a_lang::StmtNode *> * > ();
		  }
#line 1759 "parser.cc"
    break;

  case 32: // blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 304 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new WhileStmtNode(yystack_[6].value.as < a_lang::Token * > ()->pos(), yystack_[4].value.as < a_lang::ExpNode * > (), yystack_[1].value.as < std::list<a_lang::StmtNode *> * > ());
		  }
#line 1767 "parser.cc"
    break;

  case 33: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 308 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new IfStmtNode(yystack_[6].value.as < a_lang::Token * > ()->pos(), yystack_[4].value.as < a_lang::ExpNode * > (), yystack_[1].value.as < std::list<a_lang::StmtNode *> * > ());
		  }
#line 1775 "parser.cc"
    break;

  case 34: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 312 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new IfElseStmtNode(yystack_[10].value.as < a_lang::Token * > ()->pos(), yystack_[8].value.as < a_lang::ExpNode * > (), yystack_[5].value.as < std::list<a_lang::StmtNode *> * > (), yystack_[1].value.as < std::list<a_lang::StmtNode *> * > ());
		  }
#line 1783 "parser.cc"
    break;

  case 35: // stmt: varDecl
#line 317 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = yystack_[0].value.as < a_lang::VarDeclNode * > ();
		  }
#line 1791 "parser.cc"
    break;

  case 36: // stmt: loc ASSIGN exp
#line 321 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::LocNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::StmtNode * > () = new AssignStmtNode(p, yystack_[2].value.as < a_lang::LocNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1800 "parser.cc"
    break;

  case 37: // stmt: callExp
#line 326 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new CallStmtNode(yystack_[0].value.as < a_lang::CallExpNode * > ()->pos(), yystack_[0].value.as < a_lang::CallExpNode * > ());
		  }
#line 1808 "parser.cc"
    break;

  case 38: // stmt: loc POSTDEC
#line 330 "a.yy"
                  {
		  const Position * p = new Position(yystack_[1].value.as < a_lang::LocNode * > ()->pos(), yystack_[0].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::StmtNode * > () = new PostDecStmtNode(p, yystack_[1].value.as < a_lang::LocNode * > ());
		  }
#line 1817 "parser.cc"
    break;

  case 39: // stmt: loc POSTINC
#line 335 "a.yy"
                  {
		  const Position * p = new Position(yystack_[1].value.as < a_lang::LocNode * > ()->pos(), yystack_[0].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::StmtNode * > () = new PostIncStmtNode(p, yystack_[1].value.as < a_lang::LocNode * > ());
		  }
#line 1826 "parser.cc"
    break;

  case 40: // stmt: TOCONSOLE exp
#line 340 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new ToConsoleStmtNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1834 "parser.cc"
    break;

  case 41: // stmt: FROMCONSOLE loc
#line 344 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new FromConsoleStmtNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::LocNode * > ());
		  }
#line 1842 "parser.cc"
    break;

  case 42: // stmt: MAYBE exp MEANS exp OTHERWISE exp
#line 348 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new MaybeStmtNode(yystack_[5].value.as < a_lang::Token * > ()->pos(), yystack_[4].value.as < a_lang::ExpNode * > (), yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1850 "parser.cc"
    break;

  case 43: // stmt: RETURN exp
#line 352 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new ReturnStmtNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1858 "parser.cc"
    break;

  case 44: // stmt: RETURN
#line 356 "a.yy"
                  {
		  yylhs.value.as < a_lang::StmtNode * > () = new ReturnStmtNode(yystack_[0].value.as < a_lang::Token * > ()->pos());
		  }
#line 1866 "parser.cc"
    break;

  case 45: // exp: exp DASH exp
#line 362 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new MinusNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1875 "parser.cc"
    break;

  case 46: // exp: exp CROSS exp
#line 367 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new PlusNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1884 "parser.cc"
    break;

  case 47: // exp: exp STAR exp
#line 372 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new TimesNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1893 "parser.cc"
    break;

  case 48: // exp: exp SLASH exp
#line 377 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new DivideNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1902 "parser.cc"
    break;

  case 49: // exp: exp AND exp
#line 382 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new AndNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1911 "parser.cc"
    break;

  case 50: // exp: exp OR exp
#line 387 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new OrNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1920 "parser.cc"
    break;

  case 51: // exp: exp EQUALS exp
#line 392 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new EqualsNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1929 "parser.cc"
    break;

  case 52: // exp: exp NOTEQUALS exp
#line 397 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new NotEqualsNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1938 "parser.cc"
    break;

  case 53: // exp: exp GREATER exp
#line 402 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new GreaterNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1947 "parser.cc"
    break;

  case 54: // exp: exp GREATEREQ exp
#line 407 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new GreaterEqNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1956 "parser.cc"
    break;

  case 55: // exp: exp LESS exp
#line 412 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new LessNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1965 "parser.cc"
    break;

  case 56: // exp: exp LESSEQ exp
#line 417 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::ExpNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::ExpNode * > () = new LessEqNode(p, yystack_[2].value.as < a_lang::ExpNode * > (), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1974 "parser.cc"
    break;

  case 57: // exp: NOT exp
#line 422 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = new NotNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1982 "parser.cc"
    break;

  case 58: // exp: DASH term
#line 426 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = new NegNode(yystack_[1].value.as < a_lang::Token * > ()->pos(), yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 1990 "parser.cc"
    break;

  case 59: // exp: term
#line 430 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = yystack_[0].value.as < a_lang::ExpNode * > ();
		  }
#line 1998 "parser.cc"
    break;

  case 60: // callExp: loc LPAREN RPAREN
#line 435 "a.yy"
                  {
		  const Position * p = new Position(yystack_[2].value.as < a_lang::LocNode * > ()->pos(), yystack_[1].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::CallExpNode * > () = new CallExpNode(p, yystack_[2].value.as < a_lang::LocNode * > (), new std::list<ExpNode *>());
		  }
#line 2007 "parser.cc"
    break;

  case 61: // callExp: loc LPAREN actualList RPAREN
#line 440 "a.yy"
                  {
		  const Position * p = new Position(yystack_[3].value.as < a_lang::LocNode * > ()->pos(), yystack_[2].value.as < a_lang::Token * > ()->pos());
		  yylhs.value.as < a_lang::CallExpNode * > () = new CallExpNode(p, yystack_[3].value.as < a_lang::LocNode * > (), yystack_[1].value.as < std::list<a_lang::ExpNode *> * > ());
		  }
#line 2016 "parser.cc"
    break;

  case 62: // actualList: exp
#line 446 "a.yy"
                  {
		  yylhs.value.as < std::list<a_lang::ExpNode *> * > () = new std::list<ExpNode *>();
		  yylhs.value.as < std::list<a_lang::ExpNode *> * > ()->push_back(yystack_[0].value.as < a_lang::ExpNode * > ());
		  }
#line 2025 "parser.cc"
    break;

  case 63: // actualList: actualList COMMA exp
#line 451 "a.yy"
                  {
		  yystack_[2].value.as < std::list<a_lang::ExpNode *> * > ()->push_back(yystack_[0].value.as < a_lang::ExpNode * > ());
		  yylhs.value.as < std::list<a_lang::ExpNode *> * > () = yystack_[2].value.as < std::list<a_lang::ExpNode *> * > ();
		  }
#line 2034 "parser.cc"
    break;

  case 64: // term: loc
#line 457 "a.yy"
                  {
		  DEBUG_PRINT("term loc\n");
		  yylhs.value.as < a_lang::ExpNode * > () = yystack_[0].value.as < a_lang::LocNode * > ();
		  DEBUG_PRINT("term loc done\n");
		  }
#line 2044 "parser.cc"
    break;

  case 65: // term: INTLITERAL
#line 463 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = new IntLitNode(yystack_[0].value.as < a_lang::IntLitToken * > ()->pos(), yystack_[0].value.as < a_lang::IntLitToken * > ()->num());
		  }
#line 2052 "parser.cc"
    break;

  case 66: // term: STRINGLITERAL
#line 467 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = new StrLitNode(yystack_[0].value.as < a_lang::StrToken * > ()->pos(), yystack_[0].value.as < a_lang::StrToken * > ()->str());
		  }
#line 2060 "parser.cc"
    break;

  case 67: // term: TRUE
#line 471 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = new TrueNode(yystack_[0].value.as < a_lang::Token * > ()->pos());
		  }
#line 2068 "parser.cc"
    break;

  case 68: // term: FALSE
#line 475 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = new FalseNode(yystack_[0].value.as < a_lang::Token * > ()->pos());
		  }
#line 2076 "parser.cc"
    break;

  case 69: // term: EH
#line 479 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = new EhNode(yystack_[0].value.as < a_lang::Token * > ()->pos());
		  }
#line 2084 "parser.cc"
    break;

  case 70: // term: LPAREN exp RPAREN
#line 483 "a.yy"
                  {
		  yystack_[1].value.as < a_lang::ExpNode * > ()->setParenthesis(true);
		  yylhs.value.as < a_lang::ExpNode * > () = yystack_[1].value.as < a_lang::ExpNode * > ();
		  }
#line 2093 "parser.cc"
    break;

  case 71: // term: callExp
#line 488 "a.yy"
                  {
		  yylhs.value.as < a_lang::ExpNode * > () = yystack_[0].value.as < a_lang::CallExpNode * > ();
		  }
#line 2101 "parser.cc"
    break;

  case 72: // loc: name
#line 493 "a.yy"
                  {
		  yylhs.value.as < a_lang::LocNode * > () = yystack_[0].value.as < a_lang::IDNode * > ();
		  }
#line 2109 "parser.cc"
    break;

  case 73: // loc: loc ARROW name
#line 497 "a.yy"
                  {
		  DEBUG_PRINT("loc ARROW name\n");
		  yylhs.value.as < a_lang::LocNode * > () = new MemberFieldExpNode(yystack_[2].value.as < a_lang::LocNode * > ()->pos(), yystack_[2].value.as < a_lang::LocNode * > (), yystack_[0].value.as < a_lang::IDNode * > ());
		  DEBUG_PRINT("loc ARROW name done\n");
		  }
#line 2119 "parser.cc"
    break;

  case 74: // name: ID
#line 504 "a.yy"
                  {
                  const Position * pos = yystack_[0].value.as < a_lang::IDToken * > ()->pos();
	 	  yylhs.value.as < a_lang::IDNode * > () = new IDNode(pos, yystack_[0].value.as < a_lang::IDToken * > ()->value());
		  }
#line 2128 "parser.cc"
    break;


#line 2132 "parser.cc"

            default:
              break;
            }
        }
#if YY_EXCEPTIONS
      catch (const syntax_error& yyexc)
        {
          YYCDEBUG << "Caught exception: " << yyexc.what() << '\n';
          error (yyexc);
          YYERROR;
        }
#endif // YY_EXCEPTIONS
      YY_SYMBOL_PRINT ("-> $$ =", yylhs);
      yypop_ (yylen);
      yylen = 0;

      // Shift the result of the reduction.
      yypush_ (YY_NULLPTR, YY_MOVE (yylhs));
    }
    goto yynewstate;


  /*--------------------------------------.
  | yyerrlab -- here on detecting error.  |
  `--------------------------------------*/
  yyerrlab:
    // If not already recovering from an error, report this error.
    if (!yyerrstatus_)
      {
        ++yynerrs_;
        context yyctx (*this, yyla);
        std::string msg = yysyntax_error_ (yyctx);
        error (YY_MOVE (msg));
      }


    if (yyerrstatus_ == 3)
      {
        /* If just tried and failed to reuse lookahead token after an
           error, discard it.  */

        // Return failure if at end of input.
        if (yyla.kind () == symbol_kind::S_YYEOF)
          YYABORT;
        else if (!yyla.empty ())
          {
            yy_destroy_ ("Error: discarding", yyla);
            yyla.clear ();
          }
      }

    // Else will try to reuse lookahead token after shifting the error token.
    goto yyerrlab1;


  /*---------------------------------------------------.
  | yyerrorlab -- error raised explicitly by YYERROR.  |
  `---------------------------------------------------*/
  yyerrorlab:
    /* Pacify compilers when the user code never invokes YYERROR and
       the label yyerrorlab therefore never appears in user code.  */
    if (false)
      YYERROR;

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYERROR.  */
    yypop_ (yylen);
    yylen = 0;
    YY_STACK_PRINT ();
    goto yyerrlab1;


  /*-------------------------------------------------------------.
  | yyerrlab1 -- common code for both syntax error and YYERROR.  |
  `-------------------------------------------------------------*/
  yyerrlab1:
    yyerrstatus_ = 3;   // Each real token shifted decrements this.
    // Pop stack until we find a state that shifts the error token.
    for (;;)
      {
        yyn = yypact_[+yystack_[0].state];
        if (!yy_pact_value_is_default_ (yyn))
          {
            yyn += symbol_kind::S_YYerror;
            if (0 <= yyn && yyn <= yylast_
                && yycheck_[yyn] == symbol_kind::S_YYerror)
              {
                yyn = yytable_[yyn];
                if (0 < yyn)
                  break;
              }
          }

        // Pop the current state because it cannot handle the error token.
        if (yystack_.size () == 1)
          YYABORT;

        yy_destroy_ ("Error: popping", yystack_[0]);
        yypop_ ();
        YY_STACK_PRINT ();
      }
    {
      stack_symbol_type error_token;


      // Shift the error token.
      error_token.state = state_type (yyn);
      yypush_ ("Shifting", YY_MOVE (error_token));
    }
    goto yynewstate;


  /*-------------------------------------.
  | yyacceptlab -- YYACCEPT comes here.  |
  `-------------------------------------*/
  yyacceptlab:
    yyresult = 0;
    goto yyreturn;


  /*-----------------------------------.
  | yyabortlab -- YYABORT comes here.  |
  `-----------------------------------*/
  yyabortlab:
    yyresult = 1;
    goto yyreturn;


  /*-----------------------------------------------------.
  | yyreturn -- parsing is finished, return the result.  |
  `-----------------------------------------------------*/
  yyreturn:
    if (!yyla.empty ())
      yy_destroy_ ("Cleanup: discarding lookahead", yyla);

    /* Do not reclaim the symbols of the rule whose action triggered
       this YYABORT or YYACCEPT.  */
    yypop_ (yylen);
    YY_STACK_PRINT ();
    while (1 < yystack_.size ())
      {
        yy_destroy_ ("Cleanup: popping", yystack_[0]);
        yypop_ ();
      }

    return yyresult;
  }
#if YY_EXCEPTIONS
    catch (...)
      {
        YYCDEBUG << "Exception caught: cleaning lookahead and stack\n";
        // Do not try to display the values of the reclaimed symbols,
        // as their printers might throw an exception.
        if (!yyla.empty ())
          yy_destroy_ (YY_NULLPTR, yyla);

        while (1 < yystack_.size ())
          {
            yy_destroy_ (YY_NULLPTR, yystack_[0]);
            yypop_ ();
          }
        throw;
      }
#endif // YY_EXCEPTIONS
  }

  void
  Parser::error (const syntax_error& yyexc)
  {
    error (yyexc.what ());
  }

  /* Return YYSTR after stripping away unnecessary quotes and
     backslashes, so that it's suitable for yyerror.  The heuristic is
     that double-quoting is unnecessary unless the string contains an
     apostrophe, a comma, or backslash (other than backslash-backslash).
     YYSTR is taken from yytname.  */
  std::string
  Parser::yytnamerr_ (const char *yystr)
  {
    if (*yystr == '"')
      {
        std::string yyr;
        char const *yyp = yystr;

        for (;;)
          switch (*++yyp)
            {
            case '\'':
            case ',':
              goto do_not_strip_quotes;

            case '\\':
              if (*++yyp != '\\')
                goto do_not_strip_quotes;
              else
                goto append;

            append:
            default:
              yyr += *yyp;
              break;

            case '"':
              return yyr;
            }
      do_not_strip_quotes: ;
      }

    return yystr;
  }

  std::string
  Parser::symbol_name (symbol_kind_type yysymbol)
  {
    return yytnamerr_ (yytname_[yysymbol]);
  }



  // Parser::context.
  Parser::context::context (const Parser& yyparser, const symbol_type& yyla)
    : yyparser_ (yyparser)
    , yyla_ (yyla)
  {}

  int
  Parser::context::expected_tokens (symbol_kind_type yyarg[], int yyargn) const
  {
    // Actual number of expected tokens
    int yycount = 0;

    const int yyn = yypact_[+yyparser_.yystack_[0].state];
    if (!yy_pact_value_is_default_ (yyn))
      {
        /* Start YYX at -YYN if negative to avoid negative indexes in
           YYCHECK.  In other words, skip the first -YYN actions for
           this state because they are default actions.  */
        const int yyxbegin = yyn < 0 ? -yyn : 0;
        // Stay within bounds of both yycheck and yytname.
        const int yychecklim = yylast_ - yyn + 1;
        const int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
        for (int yyx = yyxbegin; yyx < yyxend; ++yyx)
          if (yycheck_[yyx + yyn] == yyx && yyx != symbol_kind::S_YYerror
              && !yy_table_value_is_error_ (yytable_[yyx + yyn]))
            {
              if (!yyarg)
                ++yycount;
              else if (yycount == yyargn)
                return 0;
              else
                yyarg[yycount++] = YY_CAST (symbol_kind_type, yyx);
            }
      }

    if (yyarg && yycount == 0 && 0 < yyargn)
      yyarg[0] = symbol_kind::S_YYEMPTY;
    return yycount;
  }






  int
  Parser::yy_syntax_error_arguments_ (const context& yyctx,
                                                 symbol_kind_type yyarg[], int yyargn) const
  {
    /* There are many possibilities here to consider:
       - If this state is a consistent state with a default action, then
         the only way this function was invoked is if the default action
         is an error action.  In that case, don't check for expected
         tokens because there are none.
       - The only way there can be no lookahead present (in yyla) is
         if this state is a consistent state with a default action.
         Thus, detecting the absence of a lookahead is sufficient to
         determine that there is no unexpected or expected token to
         report.  In that case, just report a simple "syntax error".
       - Don't assume there isn't a lookahead just because this state is
         a consistent state with a default action.  There might have
         been a previous inconsistent state, consistent state with a
         non-default action, or user semantic action that manipulated
         yyla.  (However, yyla is currently not documented for users.)
       - Of course, the expected token list depends on states to have
         correct lookahead information, and it depends on the parser not
         to perform extra reductions after fetching a lookahead from the
         scanner and before detecting a syntax error.  Thus, state merging
         (from LALR or IELR) and default reductions corrupt the expected
         token list.  However, the list is correct for canonical LR with
         one exception: it will still contain any token that will not be
         accepted due to an error action in a later state.
    */

    if (!yyctx.lookahead ().empty ())
      {
        if (yyarg)
          yyarg[0] = yyctx.token ();
        int yyn = yyctx.expected_tokens (yyarg ? yyarg + 1 : yyarg, yyargn - 1);
        return yyn + 1;
      }
    return 0;
  }

  // Generate an error message.
  std::string
  Parser::yysyntax_error_ (const context& yyctx) const
  {
    // Its maximum.
    enum { YYARGS_MAX = 5 };
    // Arguments of yyformat.
    symbol_kind_type yyarg[YYARGS_MAX];
    int yycount = yy_syntax_error_arguments_ (yyctx, yyarg, YYARGS_MAX);

    char const* yyformat = YY_NULLPTR;
    switch (yycount)
      {
#define YYCASE_(N, S)                         \
        case N:                               \
          yyformat = S;                       \
        break
      default: // Avoid compiler warnings.
        YYCASE_ (0, YY_("syntax error"));
        YYCASE_ (1, YY_("syntax error, unexpected %s"));
        YYCASE_ (2, YY_("syntax error, unexpected %s, expecting %s"));
        YYCASE_ (3, YY_("syntax error, unexpected %s, expecting %s or %s"));
        YYCASE_ (4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
        YYCASE_ (5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
#undef YYCASE_
      }

    std::string yyres;
    // Argument number.
    std::ptrdiff_t yyi = 0;
    for (char const* yyp = yyformat; *yyp; ++yyp)
      if (yyp[0] == '%' && yyp[1] == 's' && yyi < yycount)
        {
          yyres += symbol_name (yyarg[yyi++]);
          ++yyp;
        }
      else
        yyres += *yyp;
    return yyres;
  }


  const signed char Parser::yypact_ninf_ = -82;

  const signed char Parser::yytable_ninf_ = -1;

  const short
  Parser::yypact_[] =
  {
     -82,     3,   -11,   -82,   -82,   -82,   -13,   -82,   -82,    21,
     -82,    65,   -82,    27,   -82,   104,   -11,     2,   -82,    49,
     -82,   -82,   -82,   -82,   -82,    22,    55,   -82,    57,   -82,
     -82,   304,    -8,    60,   -11,    99,   338,   -82,   -82,   -82,
     304,   304,   -82,   -82,   268,   -82,   -82,    -3,   -82,    26,
      28,   -82,    63,    99,   -82,   -82,   -82,   131,   -82,   304,
     304,   304,   304,   304,   304,   304,   304,   304,   304,   304,
     304,   -11,   303,   -82,   -82,    80,    52,   -82,   344,   -30,
     363,   363,   363,   363,   363,   363,   270,   -30,   -82,   -82,
     -82,   -82,   268,    17,   -82,   304,   -82,   376,   268,   -11,
      50,   304,   304,   -82,   304,    51,   -82,   -82,    40,   -82,
       0,    75,    79,   304,   150,   268,   268,   304,   -82,   304,
     -82,   -82,    99,   183,   304,   202,   268,    66,   235,    69,
     -82,   304,   -82,   382,   268,   406,    77,   -82,    70,   -82,
     412,   -82
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     2,     1,    74,     3,     0,     6,     7,     0,
       5,     0,    17,     0,    16,     0,    24,     0,    18,     8,
      11,    13,    15,    22,    10,     0,    25,    26,     0,    12,
      14,     0,     0,     0,     0,     0,     0,    69,    68,    65,
       0,     0,    66,    67,     9,    71,    59,    64,    72,     0,
       0,    21,     0,     0,    27,    28,    58,     0,    57,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    19,    20,     0,     0,    70,    49,    45,
      51,    53,    54,    55,    56,    52,    50,    46,    48,    47,
      73,    60,    62,     0,    29,     0,    61,     0,    63,     0,
       0,     0,    44,    23,     0,     0,    35,    31,     0,    37,
       0,    72,    41,     0,     0,    43,    40,     0,    30,     0,
      38,    39,     0,     0,     0,     0,    36,     0,     0,     0,
      29,     0,    29,     0,    42,     0,    33,    32,     0,    29,
       0,    34
  };

  const signed char
  Parser::yypgoto_[] =
  {
     -82,   -82,   -82,   -82,    -1,   -29,    82,    87,   -82,   -82,
      67,   -82,   -82,    73,   -72,   -82,   -82,   -23,   -81,   -82,
      76,   -78,    -2
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     5,   106,    19,    20,    21,     7,    32,
       8,    25,    26,    27,    97,   107,   108,    44,    45,    93,
      46,    47,    48
  };

  const short
  Parser::yytable_[] =
  {
       9,     6,    71,     3,   119,    71,    55,     4,    12,    22,
       4,    69,    70,    22,    28,    30,   109,    57,    58,   110,
       4,   112,    14,    72,    76,    95,    72,    10,    11,    49,
      52,    50,    28,    22,   120,   121,    78,    79,    80,    81,
      82,    83,    84,    85,    86,    87,    88,    89,    18,    92,
      23,    22,   109,    31,   109,   110,    96,   110,   133,   109,
     135,    33,   110,    34,    35,    53,    73,   140,    74,    90,
      75,    12,    98,    22,    13,    94,   113,   117,   114,   115,
     118,   116,   122,     4,    71,    14,    12,    15,   138,   130,
     123,    16,   132,   139,   125,   111,   126,    24,     4,    51,
      14,   128,    15,    17,    29,    12,    16,    54,   134,     0,
      12,    18,    56,     0,     0,     0,     0,     4,    17,    14,
      22,    15,     4,     0,    14,     0,    18,     0,     0,     0,
       0,   111,     0,   111,    59,     0,     0,    17,   111,     0,
       0,    60,    17,     0,    61,    18,     0,    62,    63,     0,
      18,     0,     0,    59,     0,    64,    65,     0,     0,     0,
      60,    66,    67,    61,    68,     0,    62,    63,     0,     0,
      77,     0,    69,    70,    64,    65,     0,     0,   124,     0,
      66,    67,     0,    68,     0,     0,    59,     0,     0,     0,
       0,    69,    70,    60,     0,     0,    61,     0,     0,    62,
      63,     0,     0,     0,     0,    59,     0,    64,    65,     0,
       0,     0,    60,    66,    67,    61,    68,     0,    62,    63,
       0,     0,   127,     0,    69,    70,    64,    65,     0,     0,
       0,     0,    66,    67,     0,    68,     0,     0,    59,     0,
       0,   129,     0,    69,    70,    60,     0,     0,    61,     0,
       0,    62,    63,     0,     0,     0,     0,     0,     0,    64,
      65,     0,     0,     0,     0,    66,    67,   131,    68,     0,
       0,    59,     0,    59,     0,     0,    69,    70,    60,     0,
      60,    61,     0,    61,    62,    63,    62,    63,     0,     0,
       0,     0,    64,    65,    64,    65,     0,     0,    66,    67,
      66,    68,     0,    68,     0,     0,     0,     0,     0,    69,
      70,    69,    70,    36,    36,    37,    37,    38,    38,     0,
       0,     4,     4,     0,    39,    39,     0,     0,     0,    40,
      40,     0,    41,    41,     0,     0,     0,     0,     0,     0,
       0,     0,    91,     0,     0,     0,    42,    42,    43,    43,
      37,     0,    38,     0,    60,     0,     4,    61,     0,    39,
      62,    63,     0,     0,    40,     0,     0,     0,    64,    65,
       0,     0,     0,    60,    66,     0,    -1,    68,     0,    -1,
      -1,    42,     0,    43,     0,    69,    70,    -1,    -1,     0,
       0,    99,     0,    -1,     4,   100,    68,    99,     0,     0,
       4,   100,     0,   101,    69,    70,     0,     0,     0,   101,
       0,     0,   102,   103,     0,     0,     0,     0,   102,   136,
     104,    99,     0,   105,     4,   100,   104,    99,     0,   105,
       4,   100,     0,   101,     0,     0,     0,     0,     0,   101,
       0,     0,   102,   137,     0,     0,     0,     0,   102,   141,
     104,     0,     0,   105,     0,     0,   104,     0,     0,   105
  };

  const short
  Parser::yycheck_[] =
  {
       2,     2,     5,     0,     4,     5,    35,    18,     6,    11,
      18,    41,    42,    15,    16,    17,    97,    40,    41,    97,
      18,    99,    20,    26,    53,     8,    26,    40,     7,    37,
      32,    32,    34,    35,    34,    35,    59,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    46,    72,
      23,    53,   133,     4,   135,   133,    39,   135,   130,   140,
     132,    39,   140,     8,     7,     5,    40,   139,    40,    71,
       7,     6,    95,    75,     9,    23,    26,    26,   101,   102,
      40,   104,     7,    18,     5,    20,     6,    22,    11,    23,
     113,    26,    23,    23,   117,    97,   119,    15,    18,    32,
      20,   124,    22,    38,    17,     6,    26,    34,   131,    -1,
       6,    46,    36,    -1,    -1,    -1,    -1,    18,    38,    20,
     122,    22,    18,    -1,    20,    -1,    46,    -1,    -1,    -1,
      -1,   133,    -1,   135,     3,    -1,    -1,    38,   140,    -1,
      -1,    10,    38,    -1,    13,    46,    -1,    16,    17,    -1,
      46,    -1,    -1,     3,    -1,    24,    25,    -1,    -1,    -1,
      10,    30,    31,    13,    33,    -1,    16,    17,    -1,    -1,
      39,    -1,    41,    42,    24,    25,    -1,    -1,    28,    -1,
      30,    31,    -1,    33,    -1,    -1,     3,    -1,    -1,    -1,
      -1,    41,    42,    10,    -1,    -1,    13,    -1,    -1,    16,
      17,    -1,    -1,    -1,    -1,     3,    -1,    24,    25,    -1,
      -1,    -1,    10,    30,    31,    13,    33,    -1,    16,    17,
      -1,    -1,    39,    -1,    41,    42,    24,    25,    -1,    -1,
      -1,    -1,    30,    31,    -1,    33,    -1,    -1,     3,    -1,
      -1,    39,    -1,    41,    42,    10,    -1,    -1,    13,    -1,
      -1,    16,    17,    -1,    -1,    -1,    -1,    -1,    -1,    24,
      25,    -1,    -1,    -1,    -1,    30,    31,    32,    33,    -1,
      -1,     3,    -1,     3,    -1,    -1,    41,    42,    10,    -1,
      10,    13,    -1,    13,    16,    17,    16,    17,    -1,    -1,
      -1,    -1,    24,    25,    24,    25,    -1,    -1,    30,    31,
      30,    33,    -1,    33,    -1,    -1,    -1,    -1,    -1,    41,
      42,    41,    42,    10,    10,    12,    12,    14,    14,    -1,
      -1,    18,    18,    -1,    21,    21,    -1,    -1,    -1,    26,
      26,    -1,    29,    29,    -1,    -1,    -1,    -1,    -1,    -1,
      -1,    -1,    39,    -1,    -1,    -1,    43,    43,    45,    45,
      12,    -1,    14,    -1,    10,    -1,    18,    13,    -1,    21,
      16,    17,    -1,    -1,    26,    -1,    -1,    -1,    24,    25,
      -1,    -1,    -1,    10,    30,    -1,    13,    33,    -1,    16,
      17,    43,    -1,    45,    -1,    41,    42,    24,    25,    -1,
      -1,    15,    -1,    30,    18,    19,    33,    15,    -1,    -1,
      18,    19,    -1,    27,    41,    42,    -1,    -1,    -1,    27,
      -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    36,    37,
      44,    15,    -1,    47,    18,    19,    44,    15,    -1,    47,
      18,    19,    -1,    27,    -1,    -1,    -1,    -1,    -1,    27,
      -1,    -1,    36,    37,    -1,    -1,    -1,    -1,    36,    37,
      44,    -1,    -1,    47,    -1,    -1,    44,    -1,    -1,    47
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    49,    50,     0,    18,    51,    52,    56,    58,    70,
      40,     7,     6,     9,    20,    22,    26,    38,    46,    53,
      54,    55,    70,    23,    54,    59,    60,    61,    70,    55,
      70,     4,    57,    39,     8,     7,    10,    12,    14,    21,
      26,    29,    43,    45,    65,    66,    68,    69,    70,    37,
      52,    58,    70,     5,    61,    53,    68,    65,    65,     3,
      10,    13,    16,    17,    24,    25,    30,    31,    33,    41,
      42,     5,    26,    40,    40,     7,    53,    39,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      70,    39,    65,    67,    23,     8,    39,    62,    65,    15,
      19,    27,    36,    37,    44,    47,    52,    63,    64,    66,
      69,    70,    69,    26,    65,    65,    65,    26,    40,     4,
      34,    35,     7,    65,    28,    65,    65,    39,    65,    39,
      23,    32,    23,    62,    65,    62,    37,    37,    11,    23,
      62,    37
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    48,    49,    50,    50,    51,    51,    51,    52,    52,
      53,    53,    54,    54,    54,    54,    55,    55,    55,    56,
      57,    57,    57,    58,    59,    59,    60,    60,    61,    62,
      62,    62,    63,    63,    63,    64,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    65,    65,    65,    65,    65,
      65,    65,    65,    65,    65,    65,    65,    65,    65,    65,
      66,    66,    67,    67,    68,    68,    68,    68,    68,    68,
      68,    68,    69,    69,    70
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     1,     1,     3,     5,
       2,     1,     2,     1,     2,     1,     1,     1,     1,     7,
       3,     2,     0,    10,     0,     1,     1,     3,     3,     0,
       3,     2,     7,     7,    11,     1,     3,     1,     2,     2,
       2,     2,     6,     2,     1,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     2,     2,     1,
       3,     4,     1,     3,     1,     1,     1,     1,     1,     1,
       3,     1,     1,     3,     1
  };


#if YYDEBUG || 1
  // YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
  // First, the terminals, then, starting at \a YYNTOKENS, nonterminals.
  const char*
  const Parser::yytname_[] =
  {
  "\"end file\"", "error", "\"invalid token\"", "AND", "ASSIGN", "ARROW",
  "BOOL", "COLON", "COMMA", "CUSTOM", "DASH", "ELSE", "EH", "EQUALS",
  "FALSE", "FROMCONSOLE", "GREATER", "GREATEREQ", "ID", "IF", "INT",
  "INTLITERAL", "IMMUTABLE", "LCURLY", "LESS", "LESSEQ", "LPAREN", "MAYBE",
  "MEANS", "NOT", "NOTEQUALS", "OR", "OTHERWISE", "CROSS", "POSTDEC",
  "POSTINC", "RETURN", "RCURLY", "REF", "RPAREN", "SEMICOL", "SLASH",
  "STAR", "STRINGLITERAL", "TOCONSOLE", "TRUE", "VOID", "WHILE", "$accept",
  "program", "globals", "decl", "varDecl", "type", "datatype", "primType",
  "classTypeDecl", "classBody", "fnDecl", "maybeFormals", "formalList",
  "formalDecl", "stmtList", "blockStmt", "stmt", "exp", "callExp",
  "actualList", "term", "loc", "name", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const short
  Parser::yyrline_[] =
  {
       0,   146,   146,   154,   161,   165,   169,   173,   178,   184,
     191,   195,   200,   204,   208,   212,   217,   221,   225,   230,
     236,   241,   247,   251,   261,   264,   269,   274,   280,   287,
     290,   297,   303,   307,   311,   316,   320,   325,   329,   334,
     339,   343,   347,   351,   355,   361,   366,   371,   376,   381,
     386,   391,   396,   401,   406,   411,   416,   421,   425,   429,
     434,   439,   445,   450,   456,   462,   466,   470,   474,   478,
     482,   487,   492,   496,   503
  };

  void
  Parser::yy_stack_print_ () const
  {
    *yycdebug_ << "Stack now";
    for (stack_type::const_iterator
           i = yystack_.begin (),
           i_end = yystack_.end ();
         i != i_end; ++i)
      *yycdebug_ << ' ' << int (i->state);
    *yycdebug_ << '\n';
  }

  void
  Parser::yy_reduce_print_ (int yyrule) const
  {
    int yylno = yyrline_[yyrule];
    int yynrhs = yyr2_[yyrule];
    // Print the symbols being reduced, and their result.
    *yycdebug_ << "Reducing stack by rule " << yyrule - 1
               << " (line " << yylno << "):\n";
    // The symbols being reduced.
    for (int yyi = 0; yyi < yynrhs; yyi++)
      YY_SYMBOL_PRINT ("   $" << yyi + 1 << " =",
                       yystack_[(yynrhs) - (yyi + 1)]);
  }
#endif // YYDEBUG

  Parser::symbol_kind_type
  Parser::yytranslate_ (int t) YY_NOEXCEPT
  {
    // YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to
    // TOKEN-NUM as returned by yylex.
    static
    const signed char
    translate_table[] =
    {
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47
    };
    // Last valid token kind.
    const int code_max = 302;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "a.yy"
} // a_lang
#line 2805 "parser.cc"

#line 509 "a.yy"


void a_lang::Parser::error(const std::string& msg){
	std::cout << msg << std::endl;
	std::cerr << "syntax error" << std::endl;
}
