#ifndef __A_LANG_SCANNER_HPP__
#define __A_LANG_SCANNER_HPP__ 1

#if ! defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif

#include "frontend.hh"
#include "errors.hpp"

using TokenKind = a_lang::Parser::token;

namespace a_lang {

class Scanner : public yyFlexLexer{
public:
   
   Scanner(std::istream *in) : yyFlexLexer(in)
   {
	lineNum = 1;
	colNum = 1;
   };
   virtual ~Scanner() {
   };

   //get rid of override virtual function warning
   using FlexLexer::yylex;

   // YY_DECL defined in the flex a_lang.l
   virtual int yylex( a_lang::Parser::semantic_type * const lval);

   int makeBareToken(int tagIn){
	size_t len = static_cast<size_t>(yyleng);
	Position * pos = new Position(
	  this->lineNum, this->colNum,
	  this->lineNum, this->colNum+len);
        this->yylval->emplace<a_lang::Token *>(new Token(pos, tagIn));
        colNum += len;
        return tagIn;
   }

   void errIllegal(Position * pos, std::string match){
	a_lang::Report::fatal(pos, 
	"Illegal character " + match);
   }

   void errStrEsc(Position * pos){
	a_lang::Report::fatal(pos, 
	"String literal with bad escape sequence detected");
   }

   void errStrUnterm(Position * pos){
	a_lang::Report::fatal(pos,
	"Unterminated string literal detected");
   }

   void errStrEscAndUnterm(Position * pos){
	a_lang::Report::fatal(pos, 
	"Unterminated string literal with bad escape sequence detected");
   }

   void errIntOverflow(Position * pos){
	a_lang::Report::fatal(pos, "Integer literal overflow");
   }

   static std::string tokenKindString(int tokenKind);

   void outputTokens(std::ostream& outstream);

private:
   a_lang::Parser::semantic_type *yylval = nullptr;
   size_t lineNum;
   size_t colNum;
};

} /* end namespace */

#endif /* END __A_LANG_SCANNER_HPP__ */
