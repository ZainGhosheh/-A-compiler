// A Bison parser, made by GNU Bison 3.8.2.

// Skeleton interface for Bison LALR(1) parsers in C++

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


/**
 ** \file frontend.hh
 ** Define the a_lang::parser class.
 */

// C++ LALR(1) parser skeleton written by Akim Demaille.

// DO NOT RELY ON FEATURES THAT ARE NOT DOCUMENTED in the manual,
// especially those whose name start with YY_ or yy_.  They are
// private implementation details that can be changed or removed.

#ifndef YY_YY_FRONTEND_HH_INCLUDED
# define YY_YY_FRONTEND_HH_INCLUDED
// "%code requires" blocks.
#line 12 "a.yy"

	#include <list>
	#include "tokens.hpp"
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

#line 69 "frontend.hh"


# include <cstdlib> // std::abort
# include <iostream>
# include <stdexcept>
# include <string>
# include <vector>

#if defined __cplusplus
# define YY_CPLUSPLUS __cplusplus
#else
# define YY_CPLUSPLUS 199711L
#endif

// Support move semantics when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_MOVE           std::move
# define YY_MOVE_OR_COPY   move
# define YY_MOVE_REF(Type) Type&&
# define YY_RVREF(Type)    Type&&
# define YY_COPY(Type)     Type
#else
# define YY_MOVE
# define YY_MOVE_OR_COPY   copy
# define YY_MOVE_REF(Type) Type&
# define YY_RVREF(Type)    const Type&
# define YY_COPY(Type)     const Type&
#endif

// Support noexcept when possible.
#if 201103L <= YY_CPLUSPLUS
# define YY_NOEXCEPT noexcept
# define YY_NOTHROW
#else
# define YY_NOEXCEPT
# define YY_NOTHROW throw ()
#endif

// Support constexpr when possible.
#if 201703 <= YY_CPLUSPLUS
# define YY_CONSTEXPR constexpr
#else
# define YY_CONSTEXPR
#endif



#ifndef YY_ATTRIBUTE_PURE
# if defined __GNUC__ && 2 < __GNUC__ + (96 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_PURE __attribute__ ((__pure__))
# else
#  define YY_ATTRIBUTE_PURE
# endif
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# if defined __GNUC__ && 2 < __GNUC__ + (7 <= __GNUC_MINOR__)
#  define YY_ATTRIBUTE_UNUSED __attribute__ ((__unused__))
# else
#  define YY_ATTRIBUTE_UNUSED
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YY_USE(E) ((void) (E))
#else
# define YY_USE(E) /* empty */
#endif

/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
#if defined __GNUC__ && ! defined __ICC && 406 <= __GNUC__ * 100 + __GNUC_MINOR__
# if __GNUC__ * 100 + __GNUC_MINOR__ < 407
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")
# else
#  define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN                           \
    _Pragma ("GCC diagnostic push")                                     \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")              \
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# endif
# define YY_IGNORE_MAYBE_UNINITIALIZED_END      \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif

#if defined __cplusplus && defined __GNUC__ && ! defined __ICC && 6 <= __GNUC__
# define YY_IGNORE_USELESS_CAST_BEGIN                          \
    _Pragma ("GCC diagnostic push")                            \
    _Pragma ("GCC diagnostic ignored \"-Wuseless-cast\"")
# define YY_IGNORE_USELESS_CAST_END            \
    _Pragma ("GCC diagnostic pop")
#endif
#ifndef YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_BEGIN
# define YY_IGNORE_USELESS_CAST_END
#endif

# ifndef YY_CAST
#  ifdef __cplusplus
#   define YY_CAST(Type, Val) static_cast<Type> (Val)
#   define YY_REINTERPRET_CAST(Type, Val) reinterpret_cast<Type> (Val)
#  else
#   define YY_CAST(Type, Val) ((Type) (Val))
#   define YY_REINTERPRET_CAST(Type, Val) ((Type) (Val))
#  endif
# endif
# ifndef YY_NULLPTR
#  if defined __cplusplus
#   if 201103L <= __cplusplus
#    define YY_NULLPTR nullptr
#   else
#    define YY_NULLPTR 0
#   endif
#  else
#   define YY_NULLPTR ((void*)0)
#  endif
# endif

/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

#line 5 "a.yy"
namespace a_lang {
#line 205 "frontend.hh"




  /// A Bison parser.
  class Parser
  {
  public:
#ifdef YYSTYPE
# ifdef __GNUC__
#  pragma GCC message "bison: do not #define YYSTYPE in C++, use %define api.value.type"
# endif
    typedef YYSTYPE value_type;
#else
  /// A buffer to store and retrieve objects.
  ///
  /// Sort of a variant, but does not keep track of the nature
  /// of the stored data, since that knowledge is available
  /// via the current parser state.
  class value_type
  {
  public:
    /// Type of *this.
    typedef value_type self_type;

    /// Empty construction.
    value_type () YY_NOEXCEPT
      : yyraw_ ()
    {}

    /// Construct and fill.
    template <typename T>
    value_type (YY_RVREF (T) t)
    {
      new (yyas_<T> ()) T (YY_MOVE (t));
    }

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    value_type (const self_type&) = delete;
    /// Non copyable.
    self_type& operator= (const self_type&) = delete;
#endif

    /// Destruction, allowed only if empty.
    ~value_type () YY_NOEXCEPT
    {}

# if 201103L <= YY_CPLUSPLUS
    /// Instantiate a \a T in here from \a t.
    template <typename T, typename... U>
    T&
    emplace (U&&... u)
    {
      return *new (yyas_<T> ()) T (std::forward <U>(u)...);
    }
# else
    /// Instantiate an empty \a T in here.
    template <typename T>
    T&
    emplace ()
    {
      return *new (yyas_<T> ()) T ();
    }

    /// Instantiate a \a T in here from \a t.
    template <typename T>
    T&
    emplace (const T& t)
    {
      return *new (yyas_<T> ()) T (t);
    }
# endif

    /// Instantiate an empty \a T in here.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build ()
    {
      return emplace<T> ();
    }

    /// Instantiate a \a T in here from \a t.
    /// Obsolete, use emplace.
    template <typename T>
    T&
    build (const T& t)
    {
      return emplace<T> (t);
    }

    /// Accessor to a built \a T.
    template <typename T>
    T&
    as () YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Const accessor to a built \a T (for %printer).
    template <typename T>
    const T&
    as () const YY_NOEXCEPT
    {
      return *yyas_<T> ();
    }

    /// Swap the content with \a that, of same type.
    ///
    /// Both variants must be built beforehand, because swapping the actual
    /// data requires reading it (with as()), and this is not possible on
    /// unconstructed variants: it would require some dynamic testing, which
    /// should not be the variant's responsibility.
    /// Swapping between built and (possibly) non-built is done with
    /// self_type::move ().
    template <typename T>
    void
    swap (self_type& that) YY_NOEXCEPT
    {
      std::swap (as<T> (), that.as<T> ());
    }

    /// Move the content of \a that to this.
    ///
    /// Destroys \a that.
    template <typename T>
    void
    move (self_type& that)
    {
# if 201103L <= YY_CPLUSPLUS
      emplace<T> (std::move (that.as<T> ()));
# else
      emplace<T> ();
      swap<T> (that);
# endif
      that.destroy<T> ();
    }

# if 201103L <= YY_CPLUSPLUS
    /// Move the content of \a that to this.
    template <typename T>
    void
    move (self_type&& that)
    {
      emplace<T> (std::move (that.as<T> ()));
      that.destroy<T> ();
    }
#endif

    /// Copy the content of \a that to this.
    template <typename T>
    void
    copy (const self_type& that)
    {
      emplace<T> (that.as<T> ());
    }

    /// Destroy the stored \a T.
    template <typename T>
    void
    destroy ()
    {
      as<T> ().~T ();
    }

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    value_type (const self_type&);
    /// Non copyable.
    self_type& operator= (const self_type&);
#endif

    /// Accessor to raw memory as \a T.
    template <typename T>
    T*
    yyas_ () YY_NOEXCEPT
    {
      void *yyp = yyraw_;
      return static_cast<T*> (yyp);
     }

    /// Const accessor to raw memory as \a T.
    template <typename T>
    const T*
    yyas_ () const YY_NOEXCEPT
    {
      const void *yyp = yyraw_;
      return static_cast<const T*> (yyp);
     }

    /// An auxiliary type to compute the largest semantic type.
    union union_type
    {
      // ID
      char dummy1[sizeof (a_lang::IDToken *)];

      // INTLITERAL
      char dummy2[sizeof (a_lang::IntLitToken *)];

      // STRINGLITERAL
      char dummy3[sizeof (a_lang::StrToken *)];

      // AND
      // ASSIGN
      // ARROW
      // BOOL
      // COLON
      // COMMA
      // CUSTOM
      // DASH
      // ELSE
      // EH
      // EQUALS
      // FALSE
      // FROMCONSOLE
      // GREATER
      // GREATEREQ
      // IF
      // INT
      // IMMUTABLE
      // LCURLY
      // LESS
      // LESSEQ
      // LPAREN
      // MEANS
      // NOT
      // NOTEQUALS
      // OR
      // OTHERWISE
      // CROSS
      // POSTDEC
      // POSTINC
      // RETURN
      // RCURLY
      // REF
      // RPAREN
      // SEMICOL
      // SLASH
      // STAR
      // TOCONSOLE
      // TRUE
      // VOID
      // WHILE
      char dummy4[sizeof (a_lang::Token *)];
    };

    /// The size of the largest semantic type.
    enum { size = sizeof (union_type) };

    /// A buffer to store semantic values.
    union
    {
      /// Strongest alignment constraints.
      long double yyalign_me_;
      /// A buffer large enough to store any of the semantic values.
      char yyraw_[size];
    };
  };

#endif
    /// Backward compatibility (Bison 3.8).
    typedef value_type semantic_type;


    /// Syntax errors thrown from user actions.
    struct syntax_error : std::runtime_error
    {
      syntax_error (const std::string& m)
        : std::runtime_error (m)
      {}

      syntax_error (const syntax_error& s)
        : std::runtime_error (s.what ())
      {}

      ~syntax_error () YY_NOEXCEPT YY_NOTHROW;
    };

    /// Token kinds.
    struct token
    {
      enum token_kind_type
      {
        YYEMPTY = -2,
    END = 0,                       // "end file"
    YYerror = 256,                 // error
    YYUNDEF = 257,                 // "invalid token"
    AND = 258,                     // AND
    ASSIGN = 259,                  // ASSIGN
    ARROW = 260,                   // ARROW
    BOOL = 261,                    // BOOL
    COLON = 262,                   // COLON
    COMMA = 263,                   // COMMA
    CUSTOM = 264,                  // CUSTOM
    DASH = 265,                    // DASH
    ELSE = 266,                    // ELSE
    EH = 267,                      // EH
    EQUALS = 268,                  // EQUALS
    FALSE = 269,                   // FALSE
    FROMCONSOLE = 270,             // FROMCONSOLE
    GREATER = 271,                 // GREATER
    GREATEREQ = 272,               // GREATEREQ
    ID = 273,                      // ID
    IF = 274,                      // IF
    INT = 275,                     // INT
    INTLITERAL = 276,              // INTLITERAL
    IMMUTABLE = 277,               // IMMUTABLE
    LCURLY = 278,                  // LCURLY
    LESS = 279,                    // LESS
    LESSEQ = 280,                  // LESSEQ
    LPAREN = 281,                  // LPAREN
    MEANS = 282,                   // MEANS
    NOT = 283,                     // NOT
    NOTEQUALS = 284,               // NOTEQUALS
    OR = 285,                      // OR
    OTHERWISE = 286,               // OTHERWISE
    CROSS = 287,                   // CROSS
    POSTDEC = 288,                 // POSTDEC
    POSTINC = 289,                 // POSTINC
    RETURN = 290,                  // RETURN
    RCURLY = 291,                  // RCURLY
    REF = 292,                     // REF
    RPAREN = 293,                  // RPAREN
    SEMICOL = 294,                 // SEMICOL
    SLASH = 295,                   // SLASH
    STAR = 296,                    // STAR
    STRINGLITERAL = 297,           // STRINGLITERAL
    TOCONSOLE = 298,               // TOCONSOLE
    TRUE = 299,                    // TRUE
    VOID = 300,                    // VOID
    WHILE = 301                    // WHILE
      };
      /// Backward compatibility alias (Bison 3.6).
      typedef token_kind_type yytokentype;
    };

    /// Token kind, as returned by yylex.
    typedef token::token_kind_type token_kind_type;

    /// Backward compatibility alias (Bison 3.6).
    typedef token_kind_type token_type;

    /// Symbol kinds.
    struct symbol_kind
    {
      enum symbol_kind_type
      {
        YYNTOKENS = 47, ///< Number of tokens.
        S_YYEMPTY = -2,
        S_YYEOF = 0,                             // "end file"
        S_YYerror = 1,                           // error
        S_YYUNDEF = 2,                           // "invalid token"
        S_AND = 3,                               // AND
        S_ASSIGN = 4,                            // ASSIGN
        S_ARROW = 5,                             // ARROW
        S_BOOL = 6,                              // BOOL
        S_COLON = 7,                             // COLON
        S_COMMA = 8,                             // COMMA
        S_CUSTOM = 9,                            // CUSTOM
        S_DASH = 10,                             // DASH
        S_ELSE = 11,                             // ELSE
        S_EH = 12,                               // EH
        S_EQUALS = 13,                           // EQUALS
        S_FALSE = 14,                            // FALSE
        S_FROMCONSOLE = 15,                      // FROMCONSOLE
        S_GREATER = 16,                          // GREATER
        S_GREATEREQ = 17,                        // GREATEREQ
        S_ID = 18,                               // ID
        S_IF = 19,                               // IF
        S_INT = 20,                              // INT
        S_INTLITERAL = 21,                       // INTLITERAL
        S_IMMUTABLE = 22,                        // IMMUTABLE
        S_LCURLY = 23,                           // LCURLY
        S_LESS = 24,                             // LESS
        S_LESSEQ = 25,                           // LESSEQ
        S_LPAREN = 26,                           // LPAREN
        S_MEANS = 27,                            // MEANS
        S_NOT = 28,                              // NOT
        S_NOTEQUALS = 29,                        // NOTEQUALS
        S_OR = 30,                               // OR
        S_OTHERWISE = 31,                        // OTHERWISE
        S_CROSS = 32,                            // CROSS
        S_POSTDEC = 33,                          // POSTDEC
        S_POSTINC = 34,                          // POSTINC
        S_RETURN = 35,                           // RETURN
        S_RCURLY = 36,                           // RCURLY
        S_REF = 37,                              // REF
        S_RPAREN = 38,                           // RPAREN
        S_SEMICOL = 39,                          // SEMICOL
        S_SLASH = 40,                            // SLASH
        S_STAR = 41,                             // STAR
        S_STRINGLITERAL = 42,                    // STRINGLITERAL
        S_TOCONSOLE = 43,                        // TOCONSOLE
        S_TRUE = 44,                             // TRUE
        S_VOID = 45,                             // VOID
        S_WHILE = 46,                            // WHILE
        S_YYACCEPT = 47,                         // $accept
        S_program = 48,                          // program
        S_globals = 49,                          // globals
        S_decl = 50,                             // decl
        S_varDecl = 51,                          // varDecl
        S_type = 52,                             // type
        S_datatype = 53,                         // datatype
        S_primType = 54,                         // primType
        S_classTypeDecl = 55,                    // classTypeDecl
        S_classBody = 56,                        // classBody
        S_fnDecl = 57,                           // fnDecl
        S_maybeFormals = 58,                     // maybeFormals
        S_formalList = 59,                       // formalList
        S_formalDecl = 60,                       // formalDecl
        S_stmtList = 61,                         // stmtList
        S_blockStmt = 62,                        // blockStmt
        S_stmt = 63,                             // stmt
        S_exp = 64,                              // exp
        S_callExp = 65,                          // callExp
        S_actualList = 66,                       // actualList
        S_term = 67,                             // term
        S_loc = 68,                              // loc
        S_name = 69                              // name
      };
    };

    /// (Internal) symbol kind.
    typedef symbol_kind::symbol_kind_type symbol_kind_type;

    /// The number of tokens.
    static const symbol_kind_type YYNTOKENS = symbol_kind::YYNTOKENS;

    /// A complete symbol.
    ///
    /// Expects its Base type to provide access to the symbol kind
    /// via kind ().
    ///
    /// Provide access to semantic value.
    template <typename Base>
    struct basic_symbol : Base
    {
      /// Alias to Base.
      typedef Base super_type;

      /// Default constructor.
      basic_symbol () YY_NOEXCEPT
        : value ()
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      basic_symbol (basic_symbol&& that)
        : Base (std::move (that))
        , value ()
      {
        switch (this->kind ())
    {
      case symbol_kind::S_ID: // ID
        value.move< a_lang::IDToken * > (std::move (that.value));
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.move< a_lang::IntLitToken * > (std::move (that.value));
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.move< a_lang::StrToken * > (std::move (that.value));
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
        value.move< a_lang::Token * > (std::move (that.value));
        break;

      default:
        break;
    }

      }
#endif

      /// Copy constructor.
      basic_symbol (const basic_symbol& that);

      /// Constructors for typed symbols.
#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#else
      basic_symbol (typename Base::kind_type t)
        : Base (t)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, a_lang::IDToken *&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const a_lang::IDToken *& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, a_lang::IntLitToken *&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const a_lang::IntLitToken *& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, a_lang::StrToken *&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const a_lang::StrToken *& v)
        : Base (t)
        , value (v)
      {}
#endif

#if 201103L <= YY_CPLUSPLUS
      basic_symbol (typename Base::kind_type t, a_lang::Token *&& v)
        : Base (t)
        , value (std::move (v))
      {}
#else
      basic_symbol (typename Base::kind_type t, const a_lang::Token *& v)
        : Base (t)
        , value (v)
      {}
#endif

      /// Destroy the symbol.
      ~basic_symbol ()
      {
        clear ();
      }



      /// Destroy contents, and record that is empty.
      void clear () YY_NOEXCEPT
      {
        // User destructor.
        symbol_kind_type yykind = this->kind ();
        basic_symbol<Base>& yysym = *this;
        (void) yysym;
        switch (yykind)
        {
       default:
          break;
        }

        // Value type destructor.
switch (yykind)
    {
      case symbol_kind::S_ID: // ID
        value.template destroy< a_lang::IDToken * > ();
        break;

      case symbol_kind::S_INTLITERAL: // INTLITERAL
        value.template destroy< a_lang::IntLitToken * > ();
        break;

      case symbol_kind::S_STRINGLITERAL: // STRINGLITERAL
        value.template destroy< a_lang::StrToken * > ();
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
        value.template destroy< a_lang::Token * > ();
        break;

      default:
        break;
    }

        Base::clear ();
      }

      /// The user-facing name of this symbol.
      std::string name () const YY_NOEXCEPT
      {
        return Parser::symbol_name (this->kind ());
      }

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// Whether empty.
      bool empty () const YY_NOEXCEPT;

      /// Destructive move, \a s is emptied into this.
      void move (basic_symbol& s);

      /// The semantic value.
      value_type value;

    private:
#if YY_CPLUSPLUS < 201103L
      /// Assignment operator.
      basic_symbol& operator= (const basic_symbol& that);
#endif
    };

    /// Type access provider for token (enum) based symbols.
    struct by_kind
    {
      /// The symbol kind as needed by the constructor.
      typedef token_kind_type kind_type;

      /// Default constructor.
      by_kind () YY_NOEXCEPT;

#if 201103L <= YY_CPLUSPLUS
      /// Move constructor.
      by_kind (by_kind&& that) YY_NOEXCEPT;
#endif

      /// Copy constructor.
      by_kind (const by_kind& that) YY_NOEXCEPT;

      /// Constructor from (external) token numbers.
      by_kind (kind_type t) YY_NOEXCEPT;



      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_kind& that);

      /// The (internal) type number (corresponding to \a type).
      /// \a empty when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// Backward compatibility (Bison 3.6).
      symbol_kind_type type_get () const YY_NOEXCEPT;

      /// The symbol kind.
      /// \a S_YYEMPTY when empty.
      symbol_kind_type kind_;
    };

    /// Backward compatibility for a private implementation detail (Bison 3.6).
    typedef by_kind by_type;

    /// "External" symbols: returned by the scanner.
    struct symbol_type : basic_symbol<by_kind>
    {
      /// Superclass.
      typedef basic_symbol<by_kind> super_type;

      /// Empty symbol.
      symbol_type () YY_NOEXCEPT {}

      /// Constructor for valueless symbols, and symbols from each type.
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#else
      symbol_type (int tok)
        : super_type (token_kind_type (tok))
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, a_lang::IDToken * v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const a_lang::IDToken *& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, a_lang::IntLitToken * v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const a_lang::IntLitToken *& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, a_lang::StrToken * v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const a_lang::StrToken *& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
#if 201103L <= YY_CPLUSPLUS
      symbol_type (int tok, a_lang::Token * v)
        : super_type (token_kind_type (tok), std::move (v))
#else
      symbol_type (int tok, const a_lang::Token *& v)
        : super_type (token_kind_type (tok), v)
#endif
      {}
    };

    /// Build a parser object.
    Parser (a_lang::Scanner &scanner_yyarg);
    virtual ~Parser ();

#if 201103L <= YY_CPLUSPLUS
    /// Non copyable.
    Parser (const Parser&) = delete;
    /// Non copyable.
    Parser& operator= (const Parser&) = delete;
#endif

    /// Parse.  An alias for parse ().
    /// \returns  0 iff parsing succeeded.
    int operator() ();

    /// Parse.
    /// \returns  0 iff parsing succeeded.
    virtual int parse ();

#if YYDEBUG
    /// The current debugging stream.
    std::ostream& debug_stream () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging stream.
    void set_debug_stream (std::ostream &);

    /// Type for debugging levels.
    typedef int debug_level_type;
    /// The current debugging level.
    debug_level_type debug_level () const YY_ATTRIBUTE_PURE;
    /// Set the current debugging level.
    void set_debug_level (debug_level_type l);
#endif

    /// Report a syntax error.
    /// \param msg    a description of the syntax error.
    virtual void error (const std::string& msg);

    /// Report a syntax error.
    void error (const syntax_error& err);

    /// The user-facing name of the symbol whose (internal) number is
    /// YYSYMBOL.  No bounds checking.
    static std::string symbol_name (symbol_kind_type yysymbol);

    // Implementation of make_symbol for each token kind.
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_END ()
      {
        return symbol_type (token::END);
      }
#else
      static
      symbol_type
      make_END ()
      {
        return symbol_type (token::END);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#else
      static
      symbol_type
      make_YYerror ()
      {
        return symbol_type (token::YYerror);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#else
      static
      symbol_type
      make_YYUNDEF ()
      {
        return symbol_type (token::YYUNDEF);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_AND (a_lang::Token * v)
      {
        return symbol_type (token::AND, std::move (v));
      }
#else
      static
      symbol_type
      make_AND (const a_lang::Token *& v)
      {
        return symbol_type (token::AND, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ASSIGN (a_lang::Token * v)
      {
        return symbol_type (token::ASSIGN, std::move (v));
      }
#else
      static
      symbol_type
      make_ASSIGN (const a_lang::Token *& v)
      {
        return symbol_type (token::ASSIGN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ARROW (a_lang::Token * v)
      {
        return symbol_type (token::ARROW, std::move (v));
      }
#else
      static
      symbol_type
      make_ARROW (const a_lang::Token *& v)
      {
        return symbol_type (token::ARROW, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_BOOL (a_lang::Token * v)
      {
        return symbol_type (token::BOOL, std::move (v));
      }
#else
      static
      symbol_type
      make_BOOL (const a_lang::Token *& v)
      {
        return symbol_type (token::BOOL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COLON (a_lang::Token * v)
      {
        return symbol_type (token::COLON, std::move (v));
      }
#else
      static
      symbol_type
      make_COLON (const a_lang::Token *& v)
      {
        return symbol_type (token::COLON, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_COMMA (a_lang::Token * v)
      {
        return symbol_type (token::COMMA, std::move (v));
      }
#else
      static
      symbol_type
      make_COMMA (const a_lang::Token *& v)
      {
        return symbol_type (token::COMMA, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CUSTOM (a_lang::Token * v)
      {
        return symbol_type (token::CUSTOM, std::move (v));
      }
#else
      static
      symbol_type
      make_CUSTOM (const a_lang::Token *& v)
      {
        return symbol_type (token::CUSTOM, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_DASH (a_lang::Token * v)
      {
        return symbol_type (token::DASH, std::move (v));
      }
#else
      static
      symbol_type
      make_DASH (const a_lang::Token *& v)
      {
        return symbol_type (token::DASH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ELSE (a_lang::Token * v)
      {
        return symbol_type (token::ELSE, std::move (v));
      }
#else
      static
      symbol_type
      make_ELSE (const a_lang::Token *& v)
      {
        return symbol_type (token::ELSE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EH (a_lang::Token * v)
      {
        return symbol_type (token::EH, std::move (v));
      }
#else
      static
      symbol_type
      make_EH (const a_lang::Token *& v)
      {
        return symbol_type (token::EH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_EQUALS (a_lang::Token * v)
      {
        return symbol_type (token::EQUALS, std::move (v));
      }
#else
      static
      symbol_type
      make_EQUALS (const a_lang::Token *& v)
      {
        return symbol_type (token::EQUALS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FALSE (a_lang::Token * v)
      {
        return symbol_type (token::FALSE, std::move (v));
      }
#else
      static
      symbol_type
      make_FALSE (const a_lang::Token *& v)
      {
        return symbol_type (token::FALSE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_FROMCONSOLE (a_lang::Token * v)
      {
        return symbol_type (token::FROMCONSOLE, std::move (v));
      }
#else
      static
      symbol_type
      make_FROMCONSOLE (const a_lang::Token *& v)
      {
        return symbol_type (token::FROMCONSOLE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATER (a_lang::Token * v)
      {
        return symbol_type (token::GREATER, std::move (v));
      }
#else
      static
      symbol_type
      make_GREATER (const a_lang::Token *& v)
      {
        return symbol_type (token::GREATER, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_GREATEREQ (a_lang::Token * v)
      {
        return symbol_type (token::GREATEREQ, std::move (v));
      }
#else
      static
      symbol_type
      make_GREATEREQ (const a_lang::Token *& v)
      {
        return symbol_type (token::GREATEREQ, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_ID (a_lang::IDToken * v)
      {
        return symbol_type (token::ID, std::move (v));
      }
#else
      static
      symbol_type
      make_ID (const a_lang::IDToken *& v)
      {
        return symbol_type (token::ID, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IF (a_lang::Token * v)
      {
        return symbol_type (token::IF, std::move (v));
      }
#else
      static
      symbol_type
      make_IF (const a_lang::Token *& v)
      {
        return symbol_type (token::IF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INT (a_lang::Token * v)
      {
        return symbol_type (token::INT, std::move (v));
      }
#else
      static
      symbol_type
      make_INT (const a_lang::Token *& v)
      {
        return symbol_type (token::INT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_INTLITERAL (a_lang::IntLitToken * v)
      {
        return symbol_type (token::INTLITERAL, std::move (v));
      }
#else
      static
      symbol_type
      make_INTLITERAL (const a_lang::IntLitToken *& v)
      {
        return symbol_type (token::INTLITERAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_IMMUTABLE (a_lang::Token * v)
      {
        return symbol_type (token::IMMUTABLE, std::move (v));
      }
#else
      static
      symbol_type
      make_IMMUTABLE (const a_lang::Token *& v)
      {
        return symbol_type (token::IMMUTABLE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LCURLY (a_lang::Token * v)
      {
        return symbol_type (token::LCURLY, std::move (v));
      }
#else
      static
      symbol_type
      make_LCURLY (const a_lang::Token *& v)
      {
        return symbol_type (token::LCURLY, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESS (a_lang::Token * v)
      {
        return symbol_type (token::LESS, std::move (v));
      }
#else
      static
      symbol_type
      make_LESS (const a_lang::Token *& v)
      {
        return symbol_type (token::LESS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LESSEQ (a_lang::Token * v)
      {
        return symbol_type (token::LESSEQ, std::move (v));
      }
#else
      static
      symbol_type
      make_LESSEQ (const a_lang::Token *& v)
      {
        return symbol_type (token::LESSEQ, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_LPAREN (a_lang::Token * v)
      {
        return symbol_type (token::LPAREN, std::move (v));
      }
#else
      static
      symbol_type
      make_LPAREN (const a_lang::Token *& v)
      {
        return symbol_type (token::LPAREN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_MEANS (a_lang::Token * v)
      {
        return symbol_type (token::MEANS, std::move (v));
      }
#else
      static
      symbol_type
      make_MEANS (const a_lang::Token *& v)
      {
        return symbol_type (token::MEANS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOT (a_lang::Token * v)
      {
        return symbol_type (token::NOT, std::move (v));
      }
#else
      static
      symbol_type
      make_NOT (const a_lang::Token *& v)
      {
        return symbol_type (token::NOT, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_NOTEQUALS (a_lang::Token * v)
      {
        return symbol_type (token::NOTEQUALS, std::move (v));
      }
#else
      static
      symbol_type
      make_NOTEQUALS (const a_lang::Token *& v)
      {
        return symbol_type (token::NOTEQUALS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OR (a_lang::Token * v)
      {
        return symbol_type (token::OR, std::move (v));
      }
#else
      static
      symbol_type
      make_OR (const a_lang::Token *& v)
      {
        return symbol_type (token::OR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_OTHERWISE (a_lang::Token * v)
      {
        return symbol_type (token::OTHERWISE, std::move (v));
      }
#else
      static
      symbol_type
      make_OTHERWISE (const a_lang::Token *& v)
      {
        return symbol_type (token::OTHERWISE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_CROSS (a_lang::Token * v)
      {
        return symbol_type (token::CROSS, std::move (v));
      }
#else
      static
      symbol_type
      make_CROSS (const a_lang::Token *& v)
      {
        return symbol_type (token::CROSS, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POSTDEC (a_lang::Token * v)
      {
        return symbol_type (token::POSTDEC, std::move (v));
      }
#else
      static
      symbol_type
      make_POSTDEC (const a_lang::Token *& v)
      {
        return symbol_type (token::POSTDEC, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_POSTINC (a_lang::Token * v)
      {
        return symbol_type (token::POSTINC, std::move (v));
      }
#else
      static
      symbol_type
      make_POSTINC (const a_lang::Token *& v)
      {
        return symbol_type (token::POSTINC, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RETURN (a_lang::Token * v)
      {
        return symbol_type (token::RETURN, std::move (v));
      }
#else
      static
      symbol_type
      make_RETURN (const a_lang::Token *& v)
      {
        return symbol_type (token::RETURN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RCURLY (a_lang::Token * v)
      {
        return symbol_type (token::RCURLY, std::move (v));
      }
#else
      static
      symbol_type
      make_RCURLY (const a_lang::Token *& v)
      {
        return symbol_type (token::RCURLY, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_REF (a_lang::Token * v)
      {
        return symbol_type (token::REF, std::move (v));
      }
#else
      static
      symbol_type
      make_REF (const a_lang::Token *& v)
      {
        return symbol_type (token::REF, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_RPAREN (a_lang::Token * v)
      {
        return symbol_type (token::RPAREN, std::move (v));
      }
#else
      static
      symbol_type
      make_RPAREN (const a_lang::Token *& v)
      {
        return symbol_type (token::RPAREN, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SEMICOL (a_lang::Token * v)
      {
        return symbol_type (token::SEMICOL, std::move (v));
      }
#else
      static
      symbol_type
      make_SEMICOL (const a_lang::Token *& v)
      {
        return symbol_type (token::SEMICOL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_SLASH (a_lang::Token * v)
      {
        return symbol_type (token::SLASH, std::move (v));
      }
#else
      static
      symbol_type
      make_SLASH (const a_lang::Token *& v)
      {
        return symbol_type (token::SLASH, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STAR (a_lang::Token * v)
      {
        return symbol_type (token::STAR, std::move (v));
      }
#else
      static
      symbol_type
      make_STAR (const a_lang::Token *& v)
      {
        return symbol_type (token::STAR, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_STRINGLITERAL (a_lang::StrToken * v)
      {
        return symbol_type (token::STRINGLITERAL, std::move (v));
      }
#else
      static
      symbol_type
      make_STRINGLITERAL (const a_lang::StrToken *& v)
      {
        return symbol_type (token::STRINGLITERAL, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TOCONSOLE (a_lang::Token * v)
      {
        return symbol_type (token::TOCONSOLE, std::move (v));
      }
#else
      static
      symbol_type
      make_TOCONSOLE (const a_lang::Token *& v)
      {
        return symbol_type (token::TOCONSOLE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_TRUE (a_lang::Token * v)
      {
        return symbol_type (token::TRUE, std::move (v));
      }
#else
      static
      symbol_type
      make_TRUE (const a_lang::Token *& v)
      {
        return symbol_type (token::TRUE, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_VOID (a_lang::Token * v)
      {
        return symbol_type (token::VOID, std::move (v));
      }
#else
      static
      symbol_type
      make_VOID (const a_lang::Token *& v)
      {
        return symbol_type (token::VOID, v);
      }
#endif
#if 201103L <= YY_CPLUSPLUS
      static
      symbol_type
      make_WHILE (a_lang::Token * v)
      {
        return symbol_type (token::WHILE, std::move (v));
      }
#else
      static
      symbol_type
      make_WHILE (const a_lang::Token *& v)
      {
        return symbol_type (token::WHILE, v);
      }
#endif


    class context
    {
    public:
      context (const Parser& yyparser, const symbol_type& yyla);
      const symbol_type& lookahead () const YY_NOEXCEPT { return yyla_; }
      symbol_kind_type token () const YY_NOEXCEPT { return yyla_.kind (); }
      /// Put in YYARG at most YYARGN of the expected tokens, and return the
      /// number of tokens stored in YYARG.  If YYARG is null, return the
      /// number of expected tokens (guaranteed to be less than YYNTOKENS).
      int expected_tokens (symbol_kind_type yyarg[], int yyargn) const;

    private:
      const Parser& yyparser_;
      const symbol_type& yyla_;
    };

  private:
#if YY_CPLUSPLUS < 201103L
    /// Non copyable.
    Parser (const Parser&);
    /// Non copyable.
    Parser& operator= (const Parser&);
#endif


    /// Stored state numbers (used for stacks).
    typedef unsigned char state_type;

    /// The arguments of the error message.
    int yy_syntax_error_arguments_ (const context& yyctx,
                                    symbol_kind_type yyarg[], int yyargn) const;

    /// Generate an error message.
    /// \param yyctx     the context in which the error occurred.
    virtual std::string yysyntax_error_ (const context& yyctx) const;
    /// Compute post-reduction state.
    /// \param yystate   the current state
    /// \param yysym     the nonterminal to push on the stack
    static state_type yy_lr_goto_state_ (state_type yystate, int yysym);

    /// Whether the given \c yypact_ value indicates a defaulted state.
    /// \param yyvalue   the value to check
    static bool yy_pact_value_is_default_ (int yyvalue) YY_NOEXCEPT;

    /// Whether the given \c yytable_ value indicates a syntax error.
    /// \param yyvalue   the value to check
    static bool yy_table_value_is_error_ (int yyvalue) YY_NOEXCEPT;

    static const signed char yypact_ninf_;
    static const signed char yytable_ninf_;

    /// Convert a scanner token kind \a t to a symbol kind.
    /// In theory \a t should be a token_kind_type, but character literals
    /// are valid, yet not members of the token_kind_type enum.
    static symbol_kind_type yytranslate_ (int t) YY_NOEXCEPT;

    /// Convert the symbol name \a n to a form suitable for a diagnostic.
    static std::string yytnamerr_ (const char *yystr);

    /// For a symbol, its name in clear.
    static const char* const yytname_[];


    // Tables.
    // YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
    // STATE-NUM.
    static const short yypact_[];

    // YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
    // Performed when YYTABLE does not specify something else to do.  Zero
    // means the default is an error.
    static const signed char yydefact_[];

    // YYPGOTO[NTERM-NUM].
    static const signed char yypgoto_[];

    // YYDEFGOTO[NTERM-NUM].
    static const signed char yydefgoto_[];

    // YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
    // positive, shift that token.  If negative, reduce the rule whose
    // number is the opposite.  If YYTABLE_NINF, syntax error.
    static const short yytable_[];

    static const short yycheck_[];

    // YYSTOS[STATE-NUM] -- The symbol kind of the accessing symbol of
    // state STATE-NUM.
    static const signed char yystos_[];

    // YYR1[RULE-NUM] -- Symbol kind of the left-hand side of rule RULE-NUM.
    static const signed char yyr1_[];

    // YYR2[RULE-NUM] -- Number of symbols on the right-hand side of rule RULE-NUM.
    static const signed char yyr2_[];


#if YYDEBUG
    // YYRLINE[YYN] -- Source line where rule number YYN was defined.
    static const short yyrline_[];
    /// Report on the debug stream that the rule \a r is going to be reduced.
    virtual void yy_reduce_print_ (int r) const;
    /// Print the state stack on the debug stream.
    virtual void yy_stack_print_ () const;

    /// Debugging level.
    int yydebug_;
    /// Debug stream.
    std::ostream* yycdebug_;

    /// \brief Display a symbol kind, value and location.
    /// \param yyo    The output stream.
    /// \param yysym  The symbol.
    template <typename Base>
    void yy_print_ (std::ostream& yyo, const basic_symbol<Base>& yysym) const;
#endif

    /// \brief Reclaim the memory associated to a symbol.
    /// \param yymsg     Why this token is reclaimed.
    ///                  If null, print nothing.
    /// \param yysym     The symbol.
    template <typename Base>
    void yy_destroy_ (const char* yymsg, basic_symbol<Base>& yysym) const;

  private:
    /// Type access provider for state based symbols.
    struct by_state
    {
      /// Default constructor.
      by_state () YY_NOEXCEPT;

      /// The symbol kind as needed by the constructor.
      typedef state_type kind_type;

      /// Constructor.
      by_state (kind_type s) YY_NOEXCEPT;

      /// Copy constructor.
      by_state (const by_state& that) YY_NOEXCEPT;

      /// Record that this symbol is empty.
      void clear () YY_NOEXCEPT;

      /// Steal the symbol kind from \a that.
      void move (by_state& that);

      /// The symbol kind (corresponding to \a state).
      /// \a symbol_kind::S_YYEMPTY when empty.
      symbol_kind_type kind () const YY_NOEXCEPT;

      /// The state number used to denote an empty symbol.
      /// We use the initial state, as it does not have a value.
      enum { empty_state = 0 };

      /// The state.
      /// \a empty when empty.
      state_type state;
    };

    /// "Internal" symbol: element of the stack.
    struct stack_symbol_type : basic_symbol<by_state>
    {
      /// Superclass.
      typedef basic_symbol<by_state> super_type;
      /// Construct an empty symbol.
      stack_symbol_type ();
      /// Move or copy construction.
      stack_symbol_type (YY_RVREF (stack_symbol_type) that);
      /// Steal the contents from \a sym to build this.
      stack_symbol_type (state_type s, YY_MOVE_REF (symbol_type) sym);
#if YY_CPLUSPLUS < 201103L
      /// Assignment, needed by push_back by some old implementations.
      /// Moves the contents of that.
      stack_symbol_type& operator= (stack_symbol_type& that);

      /// Assignment, needed by push_back by other implementations.
      /// Needed by some other old implementations.
      stack_symbol_type& operator= (const stack_symbol_type& that);
#endif
    };

    /// A stack with random access from its top.
    template <typename T, typename S = std::vector<T> >
    class stack
    {
    public:
      // Hide our reversed order.
      typedef typename S::iterator iterator;
      typedef typename S::const_iterator const_iterator;
      typedef typename S::size_type size_type;
      typedef typename std::ptrdiff_t index_type;

      stack (size_type n = 200) YY_NOEXCEPT
        : seq_ (n)
      {}

#if 201103L <= YY_CPLUSPLUS
      /// Non copyable.
      stack (const stack&) = delete;
      /// Non copyable.
      stack& operator= (const stack&) = delete;
#endif

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      const T&
      operator[] (index_type i) const
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Random access.
      ///
      /// Index 0 returns the topmost element.
      T&
      operator[] (index_type i)
      {
        return seq_[size_type (size () - 1 - i)];
      }

      /// Steal the contents of \a t.
      ///
      /// Close to move-semantics.
      void
      push (YY_MOVE_REF (T) t)
      {
        seq_.push_back (T ());
        operator[] (0).move (t);
      }

      /// Pop elements from the stack.
      void
      pop (std::ptrdiff_t n = 1) YY_NOEXCEPT
      {
        for (; 0 < n; --n)
          seq_.pop_back ();
      }

      /// Pop all elements from the stack.
      void
      clear () YY_NOEXCEPT
      {
        seq_.clear ();
      }

      /// Number of elements on the stack.
      index_type
      size () const YY_NOEXCEPT
      {
        return index_type (seq_.size ());
      }

      /// Iterator on top of the stack (going downwards).
      const_iterator
      begin () const YY_NOEXCEPT
      {
        return seq_.begin ();
      }

      /// Bottom of the stack.
      const_iterator
      end () const YY_NOEXCEPT
      {
        return seq_.end ();
      }

      /// Present a slice of the top of a stack.
      class slice
      {
      public:
        slice (const stack& stack, index_type range) YY_NOEXCEPT
          : stack_ (stack)
          , range_ (range)
        {}

        const T&
        operator[] (index_type i) const
        {
          return stack_[range_ - i];
        }

      private:
        const stack& stack_;
        index_type range_;
      };

    private:
#if YY_CPLUSPLUS < 201103L
      /// Non copyable.
      stack (const stack&);
      /// Non copyable.
      stack& operator= (const stack&);
#endif
      /// The wrapped container.
      S seq_;
    };


    /// Stack type.
    typedef stack<stack_symbol_type> stack_type;

    /// The stack.
    stack_type yystack_;

    /// Push a new state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param sym  the symbol
    /// \warning the contents of \a s.value is stolen.
    void yypush_ (const char* m, YY_MOVE_REF (stack_symbol_type) sym);

    /// Push a new look ahead token on the state on the stack.
    /// \param m    a debug message to display
    ///             if null, no trace is output.
    /// \param s    the state
    /// \param sym  the symbol (for its value and location).
    /// \warning the contents of \a sym.value is stolen.
    void yypush_ (const char* m, state_type s, YY_MOVE_REF (symbol_type) sym);

    /// Pop \a n symbols from the stack.
    void yypop_ (int n = 1) YY_NOEXCEPT;

    /// Constants.
    enum
    {
      yylast_ = 338,     ///< Last index in yytable_.
      yynnts_ = 23,  ///< Number of nonterminal symbols.
      yyfinal_ = 3 ///< Termination state number.
    };


    // User arguments.
    a_lang::Scanner &scanner;

  };


#line 5 "a.yy"
} // a_lang
#line 2085 "frontend.hh"




#endif // !YY_YY_FRONTEND_HH_INCLUDED
