#include "tokens.hpp" // Get the class declarations
#include "frontend.hh" // Get the TokenKind definitions

namespace a_lang{

using TokenKind = a_lang::Parser::token;
using Lexeme = a_lang::Parser::semantic_type;

static std::string tokenKindString(int tokKind){
	switch(tokKind){
		case TokenKind::AND: return "AND";
		case TokenKind::ARROW: return "ARROW";
		case TokenKind::ASSIGN: return "ASSIGN";
		case TokenKind::BOOL: return "BOOL";
		case TokenKind::COLON: return "COLON";
		case TokenKind::COMMA: return "COMMA";
		case TokenKind::CROSS: return "CROSS";
		case TokenKind::CUSTOM: return "CUSTOM";
		case TokenKind::DASH: return "DASH";
		case TokenKind::EH: return "EH";
		case TokenKind::ELSE: return "ELSE";
		case TokenKind::END: return "EOF";
		case TokenKind::EQUALS: return "EQUALS";
		case TokenKind::FALSE: return "FALSE";
		case TokenKind::FROMCONSOLE: return "FROMCONSOLE";
		case TokenKind::GREATER: return "GREATER";
		case TokenKind::GREATEREQ: return "GREATEREQ";
		case TokenKind::ID: return "ID";
		case TokenKind::IF: return "IF";
		case TokenKind::INT: return "INT";
		case TokenKind::INTLITERAL: return "INTLITERAL";
		case TokenKind::IMMUTABLE: return "IMMUTABLE";
		case TokenKind::LCURLY: return "LCURLY";
		case TokenKind::LESS: return "LESS";
		case TokenKind::LESSEQ: return "LESSEQ";
		case TokenKind::LPAREN: return "LPAREN";
		case TokenKind::MEANS: return "MEANS";
		case TokenKind::NOT: return "NOT";
		case TokenKind::NOTEQUALS: return "NOTEQUALS";
		case TokenKind::OR: return "OR";
		case TokenKind::OTHERWISE: return "OTHERWISE";
		case TokenKind::POSTDEC: return "POSTDEC";
		case TokenKind::POSTINC: return "POSTINC";
		case TokenKind::RETURN: return "RETURN";
		case TokenKind::REF: return "REF";
		case TokenKind::RCURLY: return "RCURLY";
		case TokenKind::RPAREN: return "RPAREN";
		case TokenKind::SEMICOL: return "SEMICOL";
		case TokenKind::SLASH: return "SLASH";
		case TokenKind::STRINGLITERAL: return "STRINGLITERAL";
		case TokenKind::STAR: return "STAR";
		case TokenKind::TOCONSOLE: return "TOCONSOLE";
		case TokenKind::TRUE: return "TRUE";
		case TokenKind::VOID: return "VOID";
		case TokenKind::WHILE: return "WHILE";
		default:
			return "OTHER"; //This should never happen
	}
}

Token::Token(Position * posIn, int kindIn)
  : myPos(posIn), myKind(kindIn){
}

std::string Token::toString(){
	return tokenKindString(kind())
	+ " " + myPos->begin();
}

int Token::kind() const { 
	return this->myKind; 
}

const Position * Token::pos() const {
	return myPos;
}

IDToken::IDToken(Position * posIn, std::string vIn)
  : Token(posIn, TokenKind::ID), myValue(vIn){ 
}

std::string IDToken::toString(){
	return tokenKindString(kind()) + ":"
	+ myValue + " " + myPos->begin();
}

const std::string IDToken::value() const { 
	return this->myValue; 
}

StrToken::StrToken(Position * posIn, std::string sIn)
  : Token(posIn, TokenKind::STRINGLITERAL), myStr(sIn){
}

std::string StrToken::toString(){
	return tokenKindString(kind()) + ":"
	+ this->myStr + " " + myPos->begin();
}

const std::string StrToken::str() const {
	return this->myStr;
}

IntLitToken::IntLitToken(Position * pos, int numIn)
  : Token(pos, TokenKind::INTLITERAL), myNum(numIn){}

std::string IntLitToken::toString(){
	return tokenKindString(kind()) + ":"
	+ std::to_string(this->myNum) + " "
	+ myPos->begin();
}

int IntLitToken::num() const {
	return this->myNum;
}

} //End namespace a_lang
