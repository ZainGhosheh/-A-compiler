#include <fstream>
#include "scanner.hpp"

using namespace a_lang;

using TokenKind = a_lang::Parser::token;
using Lexeme = a_lang::Parser::semantic_type;

void Scanner::outputTokens(std::ostream& outstream){
	Lexeme lastMatch;
	//Token * t = lex.as<Token *>();
	int tokenKind;
	while(true){
		tokenKind = this->yylex(&lastMatch);
		if (tokenKind == TokenKind::END){
			outstream << "EOF" 
			  << " [" << this->lineNum 
			  << "," << this->colNum << "]"
			  << std::endl;
			return;
		} else {
			//outstream << lex.as<Token *>()->toString()
			outstream << lastMatch.as<Token *>()->toString()
			  << std::endl;
		}
	}
}
