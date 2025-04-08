#ifndef A_LANG_AST_HPP
#define A_LANG_AST_HPP

#include <ostream>
#include <list>
#include "tokens.hpp"
#include <cassert>
#include <iostream>

#define DEBUG 0

#if DEBUG
#define DEBUG_PRINT(...) fprintf(stdout, __VA_ARGS__);
#else
#define DEBUG_PRINT(...) do { } while (0)
#endif

/* You'll probably want to add a bunch of ASTNode subclasses */

namespace a_lang{

/* You may find it useful to forward declare AST subclasses
   here so that you can use a class before it's full definition
*/
class DeclNode;
class TypeNode;
class StmtNode;
class IDNode;
class VarDeclNode;
class ExpNode;
class LocNode;
class FormalDeclNode;
class CallExpNode;

/** 
* \class ASTNode
* Base class for all other AST Node types
**/
class ASTNode{
public:
	ASTNode(const Position * p) : myPos(p){ }
	virtual void unparse(std::ostream& out, int indent) = 0;
	const Position * pos() { return myPos; }
	std::string posStr() { return pos()->span(); }
protected:
	const Position * myPos = nullptr;
};

/** 
* \class ProgramNode
* Class that contains the entire abstract syntax tree for a program.
* Note the list of declarations encompasses all global declarations
* which includes (obviously) all global variables and struct declarations
* and (perhaps less obviously), all function declarations
**/
class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn) ;
	void unparse(std::ostream& out, int indent) override;
private:
	std::list<DeclNode * > * myGlobals;
};

class StmtNode : public ASTNode{
public:
	StmtNode(const Position * p) : ASTNode(p){ }
	void unparse(std::ostream& out, int indent) override = 0;
};

/*
 * Subclasses of StmtNode
 */
class AssignStmtNode : public StmtNode{
public:
	AssignStmtNode(const Position * p, LocNode * locIn, ExpNode * exprIn)
	: StmtNode(p), myLoc(locIn), myExpr(exprIn){ }
	void unparse(std::ostream& out, int indent);
private:
	LocNode * myLoc;
	ExpNode * myExpr;
};

class CallStmtNode : public StmtNode{
public:
	CallStmtNode(const Position * p, CallExpNode * callIn)
	: StmtNode(p), myCall(callIn){ }

	void unparse(std::ostream& out, int indent);

private:
	CallExpNode * myCall;
};

class ExitStmtNode : public StmtNode{
public:
	ExitStmtNode(const Position * p) : StmtNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class FromConsoleStmtNode : public StmtNode{
public:
	FromConsoleStmtNode(const Position * p, LocNode * l) : StmtNode(p), myLoc(l) { }
	void unparse(std::ostream& out, int indent);
private:
	LocNode * myLoc;
};

class IfElseStmtNode : public StmtNode{
public:
	IfElseStmtNode(const Position * p, ExpNode * e, std::list<StmtNode *> * ifIn, std::list<StmtNode *> * elseIn)
		: StmtNode(p), myCond(e), myThen(ifIn), myElse(elseIn)
	{
	}
	void unparse(std::ostream& out, int indent);
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myThen;
	std::list<StmtNode *> * myElse;
};

class IfStmtNode : public StmtNode{
public:
	IfStmtNode(const Position * p, ExpNode * e, std::list<StmtNode *> * s) : StmtNode(p), myCond(e), myBody(s) { }
	void unparse(std::ostream& out, int indent);
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBody;
};

class MaybeStmtNode : public StmtNode{
public:
	MaybeStmtNode(const Position * p, ExpNode * e, ExpNode * e2, ExpNode * e3) : StmtNode(p), myExpr(e), myExpr2(e2), myExpr3(e3){ }
	void unparse(std::ostream& out, int indent);
private:
	ExpNode * myExpr;
	ExpNode * myExpr2;
	ExpNode * myExpr3;
};

class PostDecStmtNode : public StmtNode{
public:
	PostDecStmtNode(const Position * p, LocNode * l) : StmtNode(p), myLoc(l) { }
	void unparse(std::ostream& out, int indent);
private:
	LocNode * myLoc;
};

class PostIncStmtNode : public StmtNode{
public:
	PostIncStmtNode(const Position * p, LocNode * l) : StmtNode(p), myLoc(l) { }
	void unparse(std::ostream& out, int indent);
private:
	LocNode * myLoc;
};

class ReturnStmtNode : public StmtNode{
public:
	ReturnStmtNode(const Position * p, ExpNode * e) : StmtNode(p), myExpr(e) { }
	ReturnStmtNode(const Position * p) : StmtNode(p) { }

	void unparse(std::ostream& out, int indent);
private:
	ExpNode * myExpr;
};

class ToConsoleStmtNode : public StmtNode{
public:
	ToConsoleStmtNode(const Position * p, ExpNode * e) : StmtNode(p), myExpr(e) { }
	void unparse(std::ostream& out, int indent);
private:
	ExpNode * myExpr;
};

class WhileStmtNode : public StmtNode{
public:
	WhileStmtNode(const Position * p, ExpNode * e, std::list<StmtNode *> * s) : StmtNode(p), myCond(e), myBody(s) { }

	void unparse(std::ostream& out, int indent);

private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBody;
};

/** \class DeclNode
* Superclass for declarations (i.e. nodes that can be used to 
* declare a struct, function, variable, etc).  This base class will 
**/
class DeclNode : public StmtNode{
public:
	DeclNode(const Position * p) : StmtNode(p) { }

	void unparse(std::ostream& out, int indent) override = 0;
};

/*
 * Subclasses of DeclNode
 */
class ClassDefnNode : public DeclNode{
public:
	ClassDefnNode(const Position * p, IDNode * idIn, std::list<DeclNode *> * fieldsIn)
	: DeclNode(p), myID(idIn), myFields(fieldsIn) {}

	void unparse(std::ostream& out, int indent);

private:
	IDNode * myID;
	std::list<DeclNode *> * myFields;
};

class FnDeclNode : public DeclNode{
public:
	FnDeclNode(const Position * p, IDNode * idIn, TypeNode * returnTypeIn, std::list<FormalDeclNode *> * paramsIn, std::list<StmtNode *> * bodyIn)
	: DeclNode(p), myID(idIn), myReturnType(returnTypeIn), myParams(paramsIn), myBody(bodyIn){ }
	void unparse(std::ostream& out, int indent);
private:
	IDNode * myID;
	TypeNode * myReturnType;
	std::list<FormalDeclNode *> * myParams;
	std::list<StmtNode *> * myBody;
};

/**  \class ExpNode
* Superclass for expression nodes (i.e. nodes that can be used as
* part of an expression).  Nodes that are part of an expression
* should inherit from this abstract superclass.
**/
class ExpNode : public ASTNode{
public:
	void setParenthesis(bool p) { parenthesis = p; }

protected:
	ExpNode(const Position * p) : ASTNode(p){ }

	bool parenthesis = false;
};

class BinaryExpNode : public ExpNode{
public:
	BinaryExpNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: ExpNode(p), myLeft(leftIn), myRight(rightIn){ }
	virtual void unparse(std::ostream& out, int indent) = 0;
protected:
	ExpNode * myLeft;
	ExpNode * myRight;
};

/*
 * Subclasses of BinaryExpNode
 */
class AndNode : public BinaryExpNode{
public:
	AndNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class DivideNode : public BinaryExpNode{
public:
	DivideNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class EqualsNode : public BinaryExpNode{
public:
	EqualsNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class GreaterEqNode : public BinaryExpNode{
public:
	GreaterEqNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class GreaterNode : public BinaryExpNode{
public:
	GreaterNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class LessEqNode : public BinaryExpNode{
public:
	LessEqNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class LessNode : public BinaryExpNode{
public:
	LessNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class MinusNode : public BinaryExpNode{
public:
	MinusNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class NotEqualsNode : public BinaryExpNode{
public:
	NotEqualsNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class OrNode : public BinaryExpNode{
public:
	OrNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class PlusNode : public BinaryExpNode{
public:
	PlusNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

class TimesNode : public BinaryExpNode{
public:
	TimesNode(const Position * p, ExpNode * leftIn, ExpNode * rightIn)
	: BinaryExpNode(p, leftIn, rightIn){ }
	void unparse(std::ostream& out, int indent);
};

/*
 * Subclasses of ExpNode
 */
class CallExpNode : public ExpNode{
public:
	CallExpNode(const Position * p, LocNode * locIn, std::list<ExpNode *> * argsIn)
	: ExpNode(p), myLoc(locIn), myArgs(argsIn){ }

	void unparse(std::ostream& out, int indent);

private:
	LocNode * myLoc;
	std::list<ExpNode *> * myArgs;
};

class EhNode : public ExpNode{
public:
	EhNode(const Position * p) : ExpNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class FalseNode : public ExpNode{
public:
	FalseNode(const Position * p) : ExpNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class IntLitNode : public ExpNode{
public:
	IntLitNode(const Position * p, int numIn)
	: ExpNode(p), myNum(numIn){ }
	void unparse(std::ostream& out, int indent);
private:
	int myNum;
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(const Position * p, std::string strIn)
	: ExpNode(p), myStr(strIn){ }
	void unparse(std::ostream& out, int indent);
private:
	std::string myStr;
};

class TrueNode : public ExpNode{
public:
	TrueNode(const Position * p) : ExpNode(p){ }
	void unparse(std::ostream& out, int indent);
};

class UnaryExpNode : public ExpNode{
public:
	UnaryExpNode(const Position * p, ExpNode * childIn)
	: ExpNode(p), myChild(childIn){ }
	virtual void unparse(std::ostream& out, int indent) = 0;
protected:
	ExpNode * myChild;
};

/*
 * Subclasses of UnaryExpNode
 */
class NegNode : public UnaryExpNode{
public:
	NegNode(const Position * p, ExpNode * childIn)
	: UnaryExpNode(p, childIn){ }
	void unparse(std::ostream& out, int indent);
};

class NotNode : public UnaryExpNode{
public:
	NotNode(const Position * p, ExpNode * childIn)
	: UnaryExpNode(p, childIn){ }
	void unparse(std::ostream& out, int indent);
};

/**  \class TypeNode
* Superclass of nodes that indicate a data type. For example, in 
* the declaration "int a", the int part is the type node (a is an IDNode
* and the whole thing is a DeclNode).
**/
class TypeNode : public ASTNode{
protected:
	TypeNode(const Position * p) : ASTNode(p){
	}
public:
	virtual void unparse(std::ostream& out, int indent) = 0;
};

/*
 * Subclasses of TypeNode
 */
class BoolTypeNode : public TypeNode{
public:
	BoolTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

class ClassTypeNode : public TypeNode{
public:
	ClassTypeNode(const Position * p, IDNode * idIn) : TypeNode(p), myID(idIn){ }
	void unparse(std::ostream& out, int indent) override;

private:
	IDNode * myID;
};

class ImmutableTypeNode : public TypeNode{
public:
	ImmutableTypeNode(const Position * p, TypeNode * typeIn) : TypeNode(p), myType(typeIn){ }
	void unparse(std::ostream& out, int indent) override;

private:
	TypeNode * myType;
};

class RefTypeNode : public TypeNode{
public:
	RefTypeNode(const Position * p, TypeNode * typeIn) : TypeNode(p), myType(typeIn) {}
	RefTypeNode(const Position * p, LocNode * locIn) : TypeNode(p), myLoc(locIn) {}
	void unparse(std::ostream& out, int indent) override;

private:
	TypeNode * myType;
	LocNode * myLoc;
};

class VoidTypeNode : public TypeNode{
public:
	VoidTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent) override;
};

/** A memory location. LocNodes subclass ExpNode
 * because they can be used as part of an expression. 
**/
class LocNode : public ExpNode{
public:
	LocNode(const Position * p)
	: ExpNode(p) {}
	void unparse(std::ostream& out, int indent) = 0;
};

/*
 * Subclasses of LocNode
 */
/** An identifier. Note that IDNodes subclass
 * LocNode because they are a type of memory location. 
**/
class IDNode : public LocNode{
public:
	IDNode(const Position * p, std::string nameIn) 
	: LocNode(p), name(nameIn){ }
	void unparse(std::ostream& out, int indent);
private:
	/** The name of the identifier **/
	std::string name;
};

class MemberFieldExpNode : public LocNode{
public:
	MemberFieldExpNode(const Position * p, LocNode * parentIn, IDNode * fieldIn)
	: LocNode(p), myParent(parentIn), myField(fieldIn){ }
	void unparse(std::ostream& out, int indent);
private:
	LocNode * myParent;
	IDNode * myField;
};

/** A variable declaration.
**/
class VarDeclNode : public DeclNode{
public:
	VarDeclNode(const Position * p, IDNode * inID, TypeNode * inType) 
	: DeclNode(p), myID(inID), myType(inType)
	{
	}

	VarDeclNode(const Position * p, IDNode * inID, TypeNode * inType, ExpNode * inExp) 
	: DeclNode(p), myID(inID), myType(inType), myExp(inExp)
	{
	}

	void unparse(std::ostream& out, int indent);

protected:
	IDNode * myID;
	TypeNode * myType;
	ExpNode * myExp;
};

/*
 * Subclasses of VarDeclNode
 */
class FormalDeclNode : public VarDeclNode{
public:
	FormalDeclNode(const Position * p, IDNode * inID, TypeNode * inType)
	: VarDeclNode(p, inID, inType){ }

	void unparse(std::ostream& out, int indent);
};

/*
 * Subclasses of TypeNode
 */
class IntTypeNode : public TypeNode{
public:
	IntTypeNode(const Position * p) : TypeNode(p){ }
	void unparse(std::ostream& out, int indent);
};
} //End namespace a_lang

#endif
