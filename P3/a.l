%{
#include <string>
#include <limits.h>

/* Get our custom yyFlexScanner subclass */
#include "scanner.hpp"
#undef YY_DECL
#define YY_DECL int a_lang::Scanner::yylex(a_lang::Parser::semantic_type * const lval)

using TokenKind = a_lang::Parser::token;

/* define yyterminate as returning an EOF token (instead of NULL) */
#define yyterminate() return ( TokenKind::END )

/* exclude unistd.h for Visual Studio compatibility. */
#define YY_NO_UNISTD_H

using TokenKind = a_lang::Parser::token;
#define EXIT_ON_ERR 0

%}

/*%option debug*/
%option nodefault
%option yyclass="a_lang::Scanner"
%option noyywrap
%option c++

DIGIT [0-9]
WHITESPACE [\040\t]
LETTER [a-zA-Z]
ESCAPEE [nt'"\\]

 /* */ 
BADESC [\\][^nt"\\\n]
STRELT (\\[nt"\\])|([^\\\n"])

%%
%{
	this->yylval = lval;
%}
bool 	    { return makeBareToken(TokenKind::BOOL); }
custom	    { return makeBareToken(TokenKind::CUSTOM); }
else	    { return makeBareToken(TokenKind::ELSE); }
false	    { return makeBareToken(TokenKind::FALSE); }
fromconsole { return makeBareToken(TokenKind::FROMCONSOLE); }
if  	    { return makeBareToken(TokenKind::IF); }
int 	    { return makeBareToken(TokenKind::INT); }
immutable   { return makeBareToken(TokenKind::IMMUTABLE); }
return	    { return makeBareToken(TokenKind::RETURN); }
toconsole   { return makeBareToken(TokenKind::TOCONSOLE); }
true	    { return makeBareToken(TokenKind::TRUE); }
void	    { return makeBareToken(TokenKind::VOID); }
means       { return makeBareToken(TokenKind::MEANS); }
maybe       { return makeBareToken(TokenKind::MAYBE); }
otherwise   { return makeBareToken(TokenKind::OTHERWISE); }
while	    { return makeBareToken(TokenKind::WHILE); }
"and"       { return makeBareToken(TokenKind::AND); }
"or"	    { return makeBareToken(TokenKind::OR); }
"eh?"	    { return makeBareToken(TokenKind::EH); }
"->"        { return makeBareToken(TokenKind::ARROW); }
"="         { return makeBareToken(TokenKind::ASSIGN); }
":"         { return makeBareToken(TokenKind::COLON); }
","         { return makeBareToken(TokenKind::COMMA); }
"+"         { return makeBareToken(TokenKind::CROSS); }
"-"         { return makeBareToken(TokenKind::DASH); }
"=="        { return makeBareToken(TokenKind::EQUALS); }
">"         { return makeBareToken(TokenKind::GREATER); }
">="        { return makeBareToken(TokenKind::GREATEREQ); }
"{"	    { return makeBareToken(TokenKind::LCURLY); }
"<"	    { return makeBareToken(TokenKind::LESS); }
"<="	    { return makeBareToken(TokenKind::LESSEQ); }
"("	    { return makeBareToken(TokenKind::LPAREN); }
"!"	    { return makeBareToken(TokenKind::NOT); }
"!="	    { return makeBareToken(TokenKind::NOTEQUALS); }
"--"	    { return makeBareToken(TokenKind::POSTDEC); }
"++"	    { return makeBareToken(TokenKind::POSTINC); }
"}"	    { return makeBareToken(TokenKind::RCURLY); }
")"	    { return makeBareToken(TokenKind::RPAREN); }
";"	    { return makeBareToken(TokenKind::SEMICOL); }
"/"	    { return makeBareToken(TokenKind::SLASH); }
"*"	    { return makeBareToken(TokenKind::STAR); }
"&"	    { return makeBareToken(TokenKind::REF); }
({LETTER}|_)({LETTER}|{DIGIT}|_)* { 
			  Position * pos = new Position(lineNum, colNum,
				lineNum, colNum + yyleng);
		            yylval->emplace<a_lang::Token *>( 
		            new IDToken(pos, yytext));
		            colNum += yyleng;
		            return TokenKind::ID;
}

{DIGIT}+	    {
								double asDouble = std::stod(yytext);
			          int intVal = atoi(yytext);
			          bool overflow = false;
			          if (asDouble > INT_MAX){ overflow = true; }

								std::string str = yytext;
				  			std::string suffix = "";
				  			for(int i = 0 ; i < str.length(); i++){
									if (str[i] != '0'){
										suffix = str.substr(i, std::string::npos);
										break;
									}
				  			}
			          if (suffix.length() > 10){ overflow = true; }

			          if (overflow){
										Position pos(lineNum,colNum,lineNum,colNum+yyleng);
				            errIntOverflow(&pos);
					    intVal = 0;
			          }
				  			Position * pos = new Position(lineNum, colNum,
									lineNum, colNum + yyleng);
			          yylval->emplace<a_lang::Token *>( 
			              new IntLitToken(pos, intVal));
			          colNum += yyleng;
			          return TokenKind::INTLITERAL; 
}


\"{STRELT}*\" {
			Position * pos;
			pos = new Position(lineNum, colNum, lineNum, colNum + yyleng);
   		          yylval->emplace<a_lang::Token *>( 
                    new StrToken(pos, yytext));
		            this->colNum += yyleng;
		            return TokenKind::STRINGLITERAL;
}

\"{STRELT}* {
			Position pos(lineNum, colNum, lineNum, colNum + yyleng);
		            errStrUnterm(&pos);
		            colNum += yyleng; /*Upcoming \n resets lineNum */
			    #if EXIT_ON_ERR
			    exit(1);
			    #endif
}

["]({STRELT}*{BADESC}{STRELT}*)+(\\["])? {
                // Bad, unterm string lit
		Position pos(lineNum,colNum,lineNum,colNum+yyleng);
		errStrEscAndUnterm(&pos);
                colNum += yyleng;

    #if EXIT_ON_ERR
	  exit(1);
	  #endif
}

["]({STRELT}*{BADESC}?{STRELT}*)+\\ {
	// Bad, unterm string lit
	Position pos(lineNum,colNum,lineNum,colNum+yyleng);
	errStrEscAndUnterm(&pos);
	colNum += yyleng;

	#if EXIT_ON_ERR
	exit(1);
	#endif
}

["]({STRELT}*{BADESC}{STRELT}*)+["] {
                // Bad string lit
		Position pos(lineNum,colNum,lineNum,colNum+yyleng);
		errStrEsc(&pos);
                colNum += yyleng;
}

\n|(\r\n)     { lineNum++; colNum = 1; }


[ \t]+	      { colNum += yyleng; }

[#][^\n]* 	{ /* Comment. No token, but update the 
                   char num in the very specific case of 
                   getting the correct EOF position */ 
		   colNum += yyleng;
}

.	          { 
		
		    Position pos(lineNum,colNum,lineNum,colNum+yyleng);
		    errIllegal(&pos, yytext);
		    #if EXIT_ON_ERR
		    exit(1);
		    #endif
	            this->colNum += yyleng;
}
%%
