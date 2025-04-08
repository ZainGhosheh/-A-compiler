%{
#include <string>
#include <limits.h>

/* Get our custom yyFlexScanner subclass */
#include "scanner.hpp"
#include "tokens.hpp"
#undef  YY_DECL
#define YY_DECL int a_lang::Scanner::yylex( a_lang::Parser::semantic_type * const lval )

/* define yyterminate as this instead of NULL */
#define yyterminate() return( TokenKind::END )

/* Exclude unistd.h for Visual Studio compatability. */
#define YY_NO_UNISTD_H

/* typedef to make the reference to token kinds shorter */
using TokenKind = a_lang::Parser::token;

%}

%option debug
%option nodefault
%option yyclass="a_lang::Scanner"
%option noyywrap
%option c++

DIGIT [0-9]

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
%}

"+"		{
		// Keep track of the "kind" of token we matched. In this case,
		// it's a CROSS (aka the plus symbol). The full list of token
		// kinds is declared around line 197 of grammar.hh. The testing
		// function Scanner::outputTokens also indicates what each token
		// represents (declared in scanner.cpp line 9)

		int tokenKind = TokenKind::CROSS;

		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));

		//Instatiate a token. There are 5 classes of tokens defined based on 
		// - a literal string (StringLitToken)
		// - a literal integer (IntLitToken)
		// - a literal short (ShortLitToken)
		// - an identifier (IDToken)
		// - a base Token (any other type)
		// The token object is a handy place to keep information about the
		// token (i.e. token metadata) such as the line and column on which
		// the token character started (which can be used later in debug 
		// messages, etc). 
		Token * token = new Token(pos, tokenKind);

		//Supply the scanner with the lastest token.
		// (When Flex processes a .l file in C++ mode, it creates 
		// a class called Scanner, which is a subclass of yyFlexScanner)
		// By emplacing the token value, the scanner's client program
		// can retrieve it and use it for parsing or printing.
		this->yylval->emplace<a_lang::Token *>(token);

		//Since we consumed 1 character, increase the column number by 1
		colNum += strlen(yytext);

		//Let the scanner's client program know that a PLUS token
		// has been matched
		return tokenKind;
		}

"-" {
		//Essentially the same thing as CROSS, but without the verbose
		// comments so it doesn't look so scary.
		int tokenKind = TokenKind::DASH;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"," {
		int tokenKind = TokenKind::COMMA;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

":" {
		int tokenKind = TokenKind::COLON;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"=" {
		int tokenKind = TokenKind::ASSIGN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}



"==" {
		int tokenKind = TokenKind::EQUALS;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

">" {

		int tokenKind = TokenKind::GREATER;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}


">=" {
		int tokenKind = TokenKind::GREATEREQ;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"{" {

		int tokenKind = TokenKind::LCURLY;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}


"<" {

		int tokenKind = TokenKind::LESS;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"<=" {

		int tokenKind = TokenKind::LESSEQ;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}



"(" {

		int tokenKind = TokenKind::LPAREN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"!" {

		int tokenKind = TokenKind::NOT;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}



"&" {

		int tokenKind = TokenKind::AND;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"!=" {

		int tokenKind = TokenKind::NOTEQUALS;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}



"--" {

		int tokenKind = TokenKind::POSTDEC;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"++" {

		int tokenKind = TokenKind::POSTINC;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

		
		
"}" {
		int tokenKind = TokenKind::RCURLY;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

")" {

		int tokenKind = TokenKind::RPAREN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

";" {
		int tokenKind = TokenKind::SEMICOL;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}


"/" {
		int tokenKind = TokenKind::SLASH;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}


"*" {
		int tokenKind = TokenKind::STAR;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}


"->" {
		int tokenKind = TokenKind::ARROW;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"and" {
		int tokenKind = TokenKind::AND;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"bool" {
		int tokenKind = TokenKind::BOOL;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"custom" {
		int tokenKind = TokenKind::CUSTOM;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}


"else" {
		int tokenKind = TokenKind::ELSE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"eh?" {
		int tokenKind = TokenKind::EH;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"false" {
		int tokenKind = TokenKind::FALSE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

		
"fromconsole" {
		int tokenKind = TokenKind::FROMCONSOLE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"if" {
		int tokenKind = TokenKind::IF;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"immutable" {
		int tokenKind = TokenKind::IMMUTABLE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

		
"int" {
		int tokenKind = TokenKind::INT;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"or" {
		int tokenKind = TokenKind::OR;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"otherwise" {
		int tokenKind = TokenKind::OTHERWISE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}
		
"means" {
		int tokenKind = TokenKind::MEANS;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"toconsole" {
		int tokenKind = TokenKind::TOCONSOLE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"return" {
		int tokenKind = TokenKind::RETURN;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}
		
"true" {
		int tokenKind = TokenKind::TRUE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"void" {
		int tokenKind = TokenKind::VOID;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

"while" {
		int tokenKind = TokenKind::WHILE;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		this->yylval->emplace<a_lang::Token *>(new Token(pos, tokenKind));
		colNum += strlen(yytext);
		return tokenKind;
		}

[_A-Za-z][_A-Za-z0-9]* {
		std::string value = yytext;

		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+strlen(yytext));
		Token * tok = new IDToken(pos, value);
		yylval->emplace<a_lang::Token *>(tok);
		colNum ++;
		return TokenKind::ID;
		}



\"([^\\\n\"]|\\[nt\"\\])*\" {
		std::string value = yytext;

		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+strlen(yytext));
		Token *tok = new StrToken(pos, value);
		yylval->emplace<a_lang::Token *>(tok);
		colNum += strlen(yytext);
		return TokenKind::STRINGLITERAL;
		}

\"([^\\\"\n]|\\[nt\"\\])* {
	Position * pos = new Position(
		lineNum, colNum, lineNum, colNum+strlen(yytext));
		Report::fatal(pos, "Unterminated string literal");
		colNum += strlen(yytext);
}

\"([^\\\"\n]|\\[nt\"\\])*\\[^nt\"\\][^\\\"\n]*\" {
	Position * pos = new Position(
		lineNum, colNum, lineNum, colNum+strlen(yytext));
		Report::fatal(pos, "String literal with bad escape detected");
		colNum += strlen(yytext);
}

\"([^\\\"\n]|\\[nt\"\\])*\\[^nt\"\\][^\\\"\n]* {
	Position * pos = new Position(
		lineNum, colNum, lineNum, colNum+strlen(yytext));
		Report::fatal(pos, "Undetermined string literal with bad escape detected");
		colNum += strlen(yytext);
}



	



{DIGIT}+	{
		auto int intVal = atoi(yytext);
		int strLen = strlen(yytext);


		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum+strlen(yytext));
		colNum += strlen(yytext);

		bool fatal = false;

		if (strLen > 10 || intVal > INT_MAX) {
			fatal = true;
			Report::fatal(pos, "Integer overflow");
		}
	
		if (!fatal) {
			Token * tok = new IntLitToken(pos, intVal);
			yylval->emplace<a_lang::Token *>(tok);
			return TokenKind::INTLITERAL;
		}	
		}




#.* {
	colNum += strlen(yytext);
}


[ \t]+ {
		colNum += strlen(yytext);
		}


\n		{
		//Update the line number, reset the columnNumber
		lineNum++;
		colNum = 1;
		}




.   {
		
		std::string msg = "Illegal character ";
		msg += yytext;
		Position * pos = new Position(
			lineNum, colNum, lineNum, colNum + strlen(yytext));
		Report::fatal(pos,msg);
		colNum += strlen(yytext);
    }
%%
