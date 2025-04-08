#include <stdlib.h>
#include "ast.hpp"

namespace a_lang{

/*
doIndent is declared static, which means that it can 
only be called in this file (its symbol is not exported).
*/
static void doIndent(std::ostream& out, int indent){
	for (int k = 0 ; k < indent; k++){ out << "\t"; }
}

static void printParenthesis(std::ostream& out, bool parenthesis, std::function<void()> print) {
	if (parenthesis) {
		out << "(";
	}
	print();
	if (parenthesis) {
		out << ")";
	}
}

/*
In this code, the intention is that functions are grouped 
into files by purpose, rather than by class.
If you're used to having all of the functions of a class 
defined in the same file, this style may be a bit disorienting,
though it is legal. Thus, we can have
ProgramNode::unparse, which is the unparse method of ProgramNodes
defined in the same file as DeclNode::unparse, the unparse method
of DeclNodes.
*/


void ProgramNode::unparse(std::ostream& out, int indent){
	/* Oh, hey it's a for-each loop in C++!
	   The loop iterates over each element in a collection
	   without that gross i++ nonsense. 
	 */
	for (auto global : *myGlobals){
		/* The auto keyword tells the compiler
		   to (try to) figure out what the
		   type of a variable should be from 
		   context. here, since we're iterating
		   over a list of DeclNode *s, it's 
		   pretty clear that global is of 
		   type DeclNode *.
		*/
		global->unparse(out, indent);
		out << "\n";
	}
}

void VarDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myID->unparse(out, 0);
	out << ": ";
	this->myType->unparse(out, 0);
	if (this->myExp) {
		out << " = ";
		this->myExp->unparse(out, 0);
	}
	out << ";";
}

void FormalDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	this->myID->unparse(out, 0);
	out << ": ";
	this->myType->unparse(out, 0);
}

void IDNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << this->name;
}

/*
 Types
 */
void IntTypeNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "int";
}

void a_lang::BoolTypeNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "bool";
}

void a_lang::VoidTypeNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "void";
}

/*
 Binary Expressions
 */
void a_lang::DivideNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " / ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::EqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " == ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::LessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " < ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::LessEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " <= ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::GreaterNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " > ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::GreaterEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " >= ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::NotEqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " != ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::OrNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " or ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::AndNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " and ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::PlusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " + ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::MinusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " - ";
		this->myRight->unparse(out, 0);
	});
}

void a_lang::TimesNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		this->myLeft->unparse(out, 0);
		out << " * ";
		this->myRight->unparse(out, 0);
	});
}

/*
 Unary Expressions
 */
void a_lang::NegNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		out << "-";
		this->myChild->unparse(out, 0);
	});
}

void a_lang::NotNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	printParenthesis(out, this->parenthesis, [&]() {
		out << "!";
		this->myChild->unparse(out, 0);
	});
}

void a_lang::FnDeclNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	this->myID->unparse(out, 0);
	out << " : ";
	out << "(";
	if (myParams) {
		for (auto formal : *myParams){
			formal->unparse(out, 0);
			if (formal != myParams->back()) {
				out << ", ";
			}
		}
	}
	out << ")";
	out << " -> ";
	this->myReturnType->unparse(out, 0);
	out << " {\n";
	if (myBody) {
		for (auto stmt : *myBody){
			stmt->unparse(out, indent + 1);
			out << "\n";
		}
	}
	doIndent(out, indent);
	out << "}";
}

void a_lang::ClassDefnNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	this->myID->unparse(out, 0);
	out << ": custom";
	out << " {\n";
	if (myFields)
	{
		for (auto member : *myFields)
		{
			member->unparse(out, indent + 1);
			out << "\n";
		}
	}
	doIndent(out, indent);
	out << "};";
}

void a_lang::RefTypeNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "&";
	if (this->myLoc) {
		this->myLoc->unparse(out, 0);
	}
	else if (this->myType) {
		this->myType->unparse(out, 0);
	}
}

void a_lang::PostIncStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	this->myLoc->unparse(out, 0);
	out << "++;";
}

void a_lang::PostDecStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	this->myLoc->unparse(out, 0);
	out << "--;";
}

void a_lang::FromConsoleStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "fromconsole ";
	this->myLoc->unparse(out, 0);
	out << ";";
}

void a_lang::AssignStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	this->myLoc->unparse(out, 0);
	out << " = ";
	this->myExpr->unparse(out, 0);
	out << ";";
}

void a_lang::ImmutableTypeNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "immutable ";
	this->myType->unparse(out, 0);
}

void a_lang::ClassTypeNode::unparse(std::ostream& out, int indent)
{
	DEBUG_PRINT("ClassTypeNode unparse\n");
	doIndent(out, indent);
	this->myID->unparse(out, indent);
}

void a_lang::MemberFieldExpNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	this->myParent->unparse(out, 0);
	out << "->";
	this->myField->unparse(out, 0);
}

void CallExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
    this->myLoc->unparse(out, 0);
    out << "(";
    if (this->myArgs) {
        for (auto arg: *myArgs){
            arg->unparse(out, 0);
            if (arg != myArgs->back()){
                out << ", ";
            }
        }
    }
	out << ")";
}

void CallStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
    this->myCall->unparse(out, 0);
	out << ";";
}

void a_lang::IfElseStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "if (";
	if (this->myCond) {
		this->myCond->unparse(out, 0);
	}
	out << ")";
	out << " {\n";
	if (myThen) {
		for (auto stmt : *myThen){
			stmt->unparse(out, indent + 1);
			out << "\n";
		}
	}
	doIndent(out, indent);
	out << "} else {\n";
	if (myElse) {
		for (auto stmt : *myElse){
			stmt->unparse(out, indent + 1);
			out << "\n";
		}
	}
	doIndent(out, indent);
	out << "}";
}

void a_lang::IfStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "if (";
	if (this->myCond) {
		this->myCond->unparse(out, 0);
	}
	out << ")";
	out << " {\n";
	if (myBody) {
		for (auto stmt : *myBody){
			stmt->unparse(out, indent + 1);
			out << "\n";
		}
	}
	doIndent(out, indent);
	out << "}";
}

void a_lang::MaybeStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "maybe ";
	if (this->myExpr) {
		this->myExpr->unparse(out, 0);
	}
	out << " means ";
	if (this->myExpr2) {
		this->myExpr2->unparse(out, 0);
	}
	out << " otherwise ";
	if (this->myExpr3) {
		this->myExpr3->unparse(out, 0);
	}
	out << ";";
}

void a_lang::ReturnStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "return";
	if (myExpr) {
		out << " ";
		myExpr->unparse(out, 0);
	}
	out << ";";
}

void a_lang::ToConsoleStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "toconsole";
	if (this->myExpr) {
		out << " ";
		this->myExpr->unparse(out, 0);
	}
	out << ";";
}

void a_lang::WhileStmtNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "while (";
	if (this->myCond) {
		this->myCond->unparse(out, 0);
	}
	out << ")";
	out << " {\n";
	if (myBody) {
		for (auto stmt : *myBody){
			stmt->unparse(out, indent + 1);
			out << "\n";
		}
	}
	doIndent(out, indent);
	out << "}";
}

void a_lang::IntLitNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << this->myNum;
}

void a_lang::StrLitNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << this->myStr;
}

void a_lang::EhNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "eh?";
}

void a_lang::TrueNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "true";
}

void a_lang::FalseNode::unparse(std::ostream& out, int indent)
{
	doIndent(out, indent);
	out << "false";
}
} // End namespace a_lang
