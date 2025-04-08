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
	#include "tokens.hpp"

	//Request tokens from our scanner member, not 
	// from a global function
	#undef yylex
	#define yylex scanner.yylex



#line 64 "parser.cc"


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
#line 138 "parser.cc"

  /// Build a parser object.
  Parser::Parser (a_lang::Scanner &scanner_yyarg)
#if YYDEBUG
    : yydebug_ (false),
      yycdebug_ (&std::cerr),
#else
    :
#endif
      scanner (scanner_yyarg)
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
      case symbol_kind::S_ID: // ID
        value.copy< a_lang::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< a_lang::IntLitToken * > (YY_MOVE (that.value));
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
      case symbol_kind::S_ID: // ID
        value.move< a_lang::IDToken * > (YY_MOVE (s.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< a_lang::IntLitToken * > (YY_MOVE (s.value));
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
      case symbol_kind::S_ID: // ID
        value.YY_MOVE_OR_COPY< a_lang::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.YY_MOVE_OR_COPY< a_lang::IntLitToken * > (YY_MOVE (that.value));
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
      case symbol_kind::S_ID: // ID
        value.move< a_lang::IDToken * > (YY_MOVE (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< a_lang::IntLitToken * > (YY_MOVE (that.value));
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
      case symbol_kind::S_ID: // ID
        value.copy< a_lang::IDToken * > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.copy< a_lang::IntLitToken * > (that.value);
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
      case symbol_kind::S_ID: // ID
        value.move< a_lang::IDToken * > (that.value);
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< a_lang::IntLitToken * > (that.value);
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
      case symbol_kind::S_ID: // ID
        yylhs.value.emplace< a_lang::IDToken * > ();
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        yylhs.value.emplace< a_lang::IntLitToken * > ();
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
#line 123 "a.yy"
                  {
		  //For the project, we will only be checking std::cerr for 
		  // correctness. You might choose to uncomment the following
		  // Line to help you debug, which will print when this
		  // production is applied
		  }
#line 1010 "parser.cc"
    break;

  case 3: // globals: globals decl
#line 131 "a.yy"
                  {
	  	  }
#line 1017 "parser.cc"
    break;

  case 4: // globals: %empty
#line 135 "a.yy"
                  {
		  }
#line 1024 "parser.cc"
    break;

  case 5: // decl: varDecl SEMICOL
#line 138 "a.yy"
                                  {}
#line 1030 "parser.cc"
    break;

  case 6: // decl: classTypeDecl
#line 139 "a.yy"
                                         {}
#line 1036 "parser.cc"
    break;

  case 7: // decl: fnDecl
#line 140 "a.yy"
                          {}
#line 1042 "parser.cc"
    break;

  case 8: // fnDecl: id COLON LPAREN maybeformals RPAREN ARROW type LCURLY stmtList RCURLY
#line 144 "a.yy"
                                                                                   {}
#line 1048 "parser.cc"
    break;

  case 9: // varDecl: id COLON type
#line 147 "a.yy"
                  {
		  /* There are other rules for varDecl to add as well */
		  }
#line 1056 "parser.cc"
    break;

  case 10: // varDecl: id COLON type ASSIGN exp
#line 150 "a.yy"
                                             {}
#line 1062 "parser.cc"
    break;

  case 11: // varDecl: id COLON type ASSIGN term
#line 151 "a.yy"
                                              {}
#line 1068 "parser.cc"
    break;

  case 12: // type: datatype
#line 155 "a.yy"
                        {}
#line 1074 "parser.cc"
    break;

  case 13: // type: IMMUTABLE datatype
#line 156 "a.yy"
                                          {}
#line 1080 "parser.cc"
    break;

  case 14: // datatype: REF primType
#line 158 "a.yy"
                                     {}
#line 1086 "parser.cc"
    break;

  case 15: // datatype: primType
#line 159 "a.yy"
                                 {}
#line 1092 "parser.cc"
    break;

  case 16: // datatype: REF id
#line 160 "a.yy"
                               {}
#line 1098 "parser.cc"
    break;

  case 17: // datatype: id
#line 161 "a.yy"
                                {}
#line 1104 "parser.cc"
    break;

  case 18: // primType: INT
#line 163 "a.yy"
                            {}
#line 1110 "parser.cc"
    break;

  case 19: // primType: BOOL
#line 164 "a.yy"
                                     {}
#line 1116 "parser.cc"
    break;

  case 20: // primType: VOID
#line 165 "a.yy"
                                     {}
#line 1122 "parser.cc"
    break;

  case 21: // classTypeDecl: id COLON CUSTOM LCURLY classBody RCURLY SEMICOL
#line 169 "a.yy"
                                {}
#line 1128 "parser.cc"
    break;

  case 22: // classBody: classBody varDecl SEMICOL
#line 171 "a.yy"
                                                {}
#line 1134 "parser.cc"
    break;

  case 23: // classBody: classBody fnDecl
#line 172 "a.yy"
                                        {}
#line 1140 "parser.cc"
    break;

  case 24: // classBody: %empty
#line 173 "a.yy"
                                        {}
#line 1146 "parser.cc"
    break;

  case 25: // maybeformals: formalsList
#line 176 "a.yy"
                             {}
#line 1152 "parser.cc"
    break;

  case 26: // maybeformals: %empty
#line 177 "a.yy"
                                 {}
#line 1158 "parser.cc"
    break;

  case 27: // formalsList: formalDecl
#line 179 "a.yy"
                             {}
#line 1164 "parser.cc"
    break;

  case 28: // formalsList: formalsList COMMA formalDecl
#line 180 "a.yy"
                                                {}
#line 1170 "parser.cc"
    break;

  case 29: // formalDecl: id COLON type
#line 182 "a.yy"
                                {}
#line 1176 "parser.cc"
    break;

  case 30: // stmtList: stmtList stmt SEMICOL
#line 184 "a.yy"
                                        {}
#line 1182 "parser.cc"
    break;

  case 31: // stmtList: stmtList blockStmt
#line 185 "a.yy"
                                        {}
#line 1188 "parser.cc"
    break;

  case 32: // stmtList: %empty
#line 186 "a.yy"
                                        {}
#line 1194 "parser.cc"
    break;

  case 33: // blockStmt: WHILE LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 188 "a.yy"
                                                                {}
#line 1200 "parser.cc"
    break;

  case 34: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY
#line 189 "a.yy"
                                                                {}
#line 1206 "parser.cc"
    break;

  case 35: // blockStmt: IF LPAREN exp RPAREN LCURLY stmtList RCURLY ELSE LCURLY stmtList RCURLY
#line 190 "a.yy"
                                                                                                {}
#line 1212 "parser.cc"
    break;

  case 36: // stmt: varDecl
#line 192 "a.yy"
                          {}
#line 1218 "parser.cc"
    break;

  case 37: // stmt: loc ASSIGN exp
#line 193 "a.yy"
                                 {}
#line 1224 "parser.cc"
    break;

  case 38: // stmt: callExp
#line 194 "a.yy"
                          {}
#line 1230 "parser.cc"
    break;

  case 39: // stmt: loc POSTDEC
#line 195 "a.yy"
                              {}
#line 1236 "parser.cc"
    break;

  case 40: // stmt: loc POSTINC
#line 196 "a.yy"
                              {}
#line 1242 "parser.cc"
    break;

  case 41: // stmt: loc MEANS exp OTHERWISE exp
#line 197 "a.yy"
                                                              {}
#line 1248 "parser.cc"
    break;

  case 42: // stmt: TOCONSOLE exp
#line 198 "a.yy"
                                {}
#line 1254 "parser.cc"
    break;

  case 43: // stmt: FROMCONSOLE loc
#line 199 "a.yy"
                                  {}
#line 1260 "parser.cc"
    break;

  case 44: // stmt: RETURN exp
#line 200 "a.yy"
                             {}
#line 1266 "parser.cc"
    break;

  case 45: // stmt: RETURN
#line 201 "a.yy"
                         {}
#line 1272 "parser.cc"
    break;

  case 46: // exp: exp DASH exp
#line 203 "a.yy"
                                {}
#line 1278 "parser.cc"
    break;

  case 47: // exp: exp CROSS exp
#line 204 "a.yy"
                                {}
#line 1284 "parser.cc"
    break;

  case 48: // exp: exp STAR exp
#line 205 "a.yy"
                                {}
#line 1290 "parser.cc"
    break;

  case 49: // exp: exp SLASH exp
#line 206 "a.yy"
                                {}
#line 1296 "parser.cc"
    break;

  case 50: // exp: exp AND exp
#line 207 "a.yy"
                                {}
#line 1302 "parser.cc"
    break;

  case 51: // exp: exp OR exp
#line 208 "a.yy"
                                {}
#line 1308 "parser.cc"
    break;

  case 65: // term: loc
#line 226 "a.yy"
                      {}
#line 1314 "parser.cc"
    break;

  case 66: // term: INTLITERAL
#line 227 "a.yy"
                             {}
#line 1320 "parser.cc"
    break;

  case 67: // term: STRINGLITERAL
#line 228 "a.yy"
                               {}
#line 1326 "parser.cc"
    break;

  case 68: // term: TRUE
#line 229 "a.yy"
                       {}
#line 1332 "parser.cc"
    break;

  case 69: // term: FALSE
#line 230 "a.yy"
                        {}
#line 1338 "parser.cc"
    break;

  case 70: // term: LPAREN exp RPAREN
#line 231 "a.yy"
                                    {}
#line 1344 "parser.cc"
    break;

  case 71: // term: callExp
#line 232 "a.yy"
                          {}
#line 1350 "parser.cc"
    break;

  case 72: // loc: id
#line 234 "a.yy"
                        {}
#line 1356 "parser.cc"
    break;

  case 73: // loc: loc ARROW id
#line 235 "a.yy"
                                {}
#line 1362 "parser.cc"
    break;

  case 74: // id: ID
#line 238 "a.yy"
                  {}
#line 1368 "parser.cc"
    break;


#line 1372 "parser.cc"

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


  const signed char Parser::yypact_ninf_ = -102;

  const signed char Parser::yytable_ninf_ = -12;

  const short
  Parser::yypact_[] =
  {
    -102,     7,    -6,  -102,  -102,  -102,  -102,   -29,  -102,     9,
    -102,    61,  -102,     4,  -102,    17,    -6,    57,  -102,    53,
    -102,  -102,  -102,  -102,  -102,    21,    52,  -102,    58,  -102,
    -102,   261,   -15,    59,    -6,    95,   303,  -102,  -102,   261,
     261,  -102,  -102,   211,  -102,    27,     0,  -102,    29,  -102,
      32,    69,    95,  -102,  -102,  -102,   125,  -102,  -102,   261,
     261,   261,   261,   261,   261,   261,   261,   261,   261,   261,
     261,    -6,   246,  -102,  -102,    66,    62,  -102,    68,  -102,
      68,   229,   229,   229,   229,   229,    68,  -102,    -8,    -8,
    -102,  -102,   211,    -7,  -102,   261,  -102,   258,   211,    -6,
      63,   261,  -102,   261,    64,  -102,  -102,    54,  -102,   100,
      92,   105,   261,   211,   211,   261,  -102,   261,   261,  -102,
    -102,    95,   143,   161,   211,   179,    89,    91,   261,  -102,
    -102,   211,   277,   291,   107,  -102,    93,  -102,   296,  -102
  };

  const signed char
  Parser::yydefact_[] =
  {
       4,     0,     2,     1,    74,     3,     7,     0,     6,     0,
       5,     0,    19,     0,    18,     0,    26,     0,    20,     9,
      12,    15,    17,    24,    13,     0,    25,    27,     0,    14,
      16,     0,     0,     0,     0,     0,     0,    69,    66,     0,
       0,    67,    68,    10,    71,    60,    65,    72,     0,    23,
       0,     0,     0,    28,    29,    59,     0,    60,    58,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,    21,    22,     0,     0,    70,    50,    46,
      52,    54,    55,    56,    57,    53,    51,    47,    49,    48,
      73,    61,    63,     0,    32,     0,    62,     0,    64,     0,
       0,    45,     8,     0,     0,    36,    31,     0,    38,     0,
      72,    43,     0,    44,    42,     0,    30,     0,     0,    39,
      40,     0,     0,     0,    37,     0,     0,     0,     0,    32,
      32,    41,     0,     0,    34,    33,     0,    32,     0,    35
  };

  const signed char
  Parser::yypgoto_[] =
  {
    -102,  -102,  -102,  -102,    88,     2,   -27,   106,   108,  -102,
    -102,  -102,  -102,    90,  -101,  -102,  -102,   -21,   -80,  -102,
     -25,   -77,    -2
  };

  const signed char
  Parser::yydefgoto_[] =
  {
       0,     1,     2,     5,     6,   105,    19,    20,    21,     8,
      32,    25,    26,    27,    97,   106,   107,    43,    44,    93,
      57,    46,    47
  };

  const short
  Parser::yytable_[] =
  {
       9,    95,    60,     4,     7,    71,    45,     3,    54,    22,
      10,    55,     4,    22,    28,    30,    11,   108,    56,    58,
     109,    48,   111,    12,    68,    76,    72,    23,   132,   133,
      51,    96,    28,    22,    50,     4,   138,    14,    78,    79,
      80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
      22,    92,   108,   108,    17,   109,   109,    31,   108,    33,
      34,   109,    18,    12,    52,    35,   -11,    12,    73,    90,
      13,    74,    12,    22,    98,     4,    75,    14,    60,     4,
     113,    14,   114,    15,     4,    94,    14,    16,    15,   112,
     115,   122,    16,   116,   123,   110,   124,   125,    17,   121,
      68,    12,    18,    17,   117,    71,    18,   131,    69,    70,
      71,    18,   129,     4,   130,    14,   137,    15,   136,    22,
      49,    24,     0,     0,    53,    29,    72,   118,    59,     0,
     110,   110,    17,   119,   120,    60,   110,     0,    61,     0,
      18,    62,    63,     0,     0,     0,    59,     0,     0,    64,
      65,     0,     0,    60,    66,    67,    61,    68,     0,    62,
      63,     0,     0,    77,    59,    69,    70,    64,    65,     0,
       0,    60,    66,    67,    61,    68,     0,    62,    63,     0,
       0,   126,    59,    69,    70,    64,    65,     0,     0,    60,
      66,    67,    61,    68,     0,    62,    63,     0,     0,   127,
       0,    69,    70,    64,    65,     0,     0,     0,    66,    67,
     128,    68,     0,     0,    59,     0,     0,     0,     0,    69,
      70,    60,     0,     0,    61,     0,     0,    62,    63,     0,
       0,     0,    59,     0,     0,    64,    65,     0,     0,    60,
      66,    67,    61,    68,     0,   -12,   -12,     0,     0,     0,
       0,    69,    70,   -12,   -12,     0,    36,     0,   -12,    67,
      37,    68,     0,     0,     4,     0,     0,    38,     0,    69,
      70,    36,    39,    99,    40,    37,     4,   100,     0,     4,
       0,     0,    38,     0,    91,     0,     0,    39,    41,    40,
      42,     0,    99,   101,   102,     4,   100,     0,     0,     0,
       0,   103,     0,    41,   104,    42,    99,     0,     0,     4,
     100,    99,   101,   134,     4,   100,     0,    37,     0,     0,
     103,     4,     0,   104,    38,     0,   101,   135,     0,    39,
       0,   101,   139,     0,   103,     0,     0,   104,     0,   103,
       0,     0,   104,     0,     0,    41,     0,    42
  };

  const short
  Parser::yycheck_[] =
  {
       2,     8,    10,    18,     2,     5,    31,     0,    35,    11,
      39,    36,    18,    15,    16,    17,     7,    97,    39,    40,
      97,    36,    99,     6,    32,    52,    26,    23,   129,   130,
      32,    38,    34,    35,    32,    18,   137,    20,    59,    60,
      61,    62,    63,    64,    65,    66,    67,    68,    69,    70,
      52,    72,   132,   133,    37,   132,   133,     4,   138,    38,
       8,   138,    45,     6,     5,     7,    39,     6,    39,    71,
       9,    39,     6,    75,    95,    18,     7,    20,    10,    18,
     101,    20,   103,    22,    18,    23,    20,    26,    22,    26,
      26,   112,    26,    39,   115,    97,   117,   118,    37,     7,
      32,     6,    45,    37,     4,     5,    45,   128,    40,    41,
       5,    45,    23,    18,    23,    20,    23,    22,    11,   121,
      32,    15,    -1,    -1,    34,    17,    26,    27,     3,    -1,
     132,   133,    37,    33,    34,    10,   138,    -1,    13,    -1,
      45,    16,    17,    -1,    -1,    -1,     3,    -1,    -1,    24,
      25,    -1,    -1,    10,    29,    30,    13,    32,    -1,    16,
      17,    -1,    -1,    38,     3,    40,    41,    24,    25,    -1,
      -1,    10,    29,    30,    13,    32,    -1,    16,    17,    -1,
      -1,    38,     3,    40,    41,    24,    25,    -1,    -1,    10,
      29,    30,    13,    32,    -1,    16,    17,    -1,    -1,    38,
      -1,    40,    41,    24,    25,    -1,    -1,    -1,    29,    30,
      31,    32,    -1,    -1,     3,    -1,    -1,    -1,    -1,    40,
      41,    10,    -1,    -1,    13,    -1,    -1,    16,    17,    -1,
      -1,    -1,     3,    -1,    -1,    24,    25,    -1,    -1,    10,
      29,    30,    13,    32,    -1,    16,    17,    -1,    -1,    -1,
      -1,    40,    41,    24,    25,    -1,    10,    -1,    29,    30,
      14,    32,    -1,    -1,    18,    -1,    -1,    21,    -1,    40,
      41,    10,    26,    15,    28,    14,    18,    19,    -1,    18,
      -1,    -1,    21,    -1,    38,    -1,    -1,    26,    42,    28,
      44,    -1,    15,    35,    36,    18,    19,    -1,    -1,    -1,
      -1,    43,    -1,    42,    46,    44,    15,    -1,    -1,    18,
      19,    15,    35,    36,    18,    19,    -1,    14,    -1,    -1,
      43,    18,    -1,    46,    21,    -1,    35,    36,    -1,    26,
      -1,    35,    36,    -1,    43,    -1,    -1,    46,    -1,    43,
      -1,    -1,    46,    -1,    -1,    42,    -1,    44
  };

  const signed char
  Parser::yystos_[] =
  {
       0,    48,    49,     0,    18,    50,    51,    52,    56,    69,
      39,     7,     6,     9,    20,    22,    26,    37,    45,    53,
      54,    55,    69,    23,    54,    58,    59,    60,    69,    55,
      69,     4,    57,    38,     8,     7,    10,    14,    21,    26,
      28,    42,    44,    64,    65,    67,    68,    69,    36,    51,
      52,    69,     5,    60,    53,    67,    64,    67,    64,     3,
      10,    13,    16,    17,    24,    25,    29,    30,    32,    40,
      41,     5,    26,    39,    39,     7,    53,    38,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      69,    38,    64,    66,    23,     8,    38,    61,    64,    15,
      19,    35,    36,    43,    46,    52,    62,    63,    65,    68,
      69,    68,    26,    64,    64,    26,    39,     4,    27,    33,
      34,     7,    64,    64,    64,    64,    38,    38,    31,    23,
      23,    64,    61,    61,    36,    36,    11,    23,    61,    36
  };

  const signed char
  Parser::yyr1_[] =
  {
       0,    47,    48,    49,    49,    50,    50,    50,    51,    52,
      52,    52,    53,    53,    54,    54,    54,    54,    55,    55,
      55,    56,    57,    57,    57,    58,    58,    59,    59,    60,
      61,    61,    61,    62,    62,    62,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    64,    64,    64,    64,
      64,    64,    64,    64,    64,    64,    64,    64,    64,    64,
      64,    65,    65,    66,    66,    67,    67,    67,    67,    67,
      67,    67,    68,    68,    69
  };

  const signed char
  Parser::yyr2_[] =
  {
       0,     2,     1,     2,     0,     2,     1,     1,    10,     3,
       5,     5,     1,     2,     2,     1,     2,     1,     1,     1,
       1,     7,     3,     2,     0,     1,     0,     1,     3,     3,
       3,     2,     0,     7,     7,    11,     1,     3,     1,     2,
       2,     5,     2,     2,     2,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     2,     2,
       1,     3,     4,     1,     3,     1,     1,     1,     1,     1,
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
  "INTLITERAL", "IMMUTABLE", "LCURLY", "LESS", "LESSEQ", "LPAREN", "MEANS",
  "NOT", "NOTEQUALS", "OR", "OTHERWISE", "CROSS", "POSTDEC", "POSTINC",
  "RETURN", "RCURLY", "REF", "RPAREN", "SEMICOL", "SLASH", "STAR",
  "STRINGLITERAL", "TOCONSOLE", "TRUE", "VOID", "WHILE", "$accept",
  "program", "globals", "decl", "fnDecl", "varDecl", "type", "datatype",
  "primType", "classTypeDecl", "classBody", "maybeformals", "formalsList",
  "formalDecl", "stmtList", "blockStmt", "stmt", "exp", "callExp",
  "actualsList", "term", "loc", "id", YY_NULLPTR
  };
#endif


#if YYDEBUG
  const unsigned char
  Parser::yyrline_[] =
  {
       0,   122,   122,   130,   135,   138,   139,   140,   144,   146,
     150,   151,   155,   156,   158,   159,   160,   161,   163,   164,
     165,   168,   171,   172,   173,   176,   177,   179,   180,   182,
     184,   185,   186,   188,   189,   190,   192,   193,   194,   195,
     196,   197,   198,   199,   200,   201,   203,   204,   205,   206,
     207,   208,   209,   210,   211,   212,   213,   214,   216,   217,
     218,   220,   221,   223,   224,   226,   227,   228,   229,   230,
     231,   232,   234,   235,   237
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
      45,    46
    };
    // Last valid token kind.
    const int code_max = 301;

    if (t <= 0)
      return symbol_kind::S_YYEOF;
    else if (t <= code_max)
      return static_cast <symbol_kind_type> (translate_table[t]);
    else
      return symbol_kind::S_YYUNDEF;
  }

#line 5 "a.yy"
} // a_lang
#line 2020 "parser.cc"

#line 243 "a.yy"


void a_lang::Parser::error(const std::string& msg){
	//For the project, we will only be checking std::cerr for 
	// correctness. You might choose to uncomment the following
	// Line to help you debug, since it gives slightly more 
	// descriptive error messages 
	 std::cout << msg <<  " ----> Line: " << __LINE__ << std::endl;
	/* std::cerr << "syntax error\nParse failed." << std::endl; */
}
