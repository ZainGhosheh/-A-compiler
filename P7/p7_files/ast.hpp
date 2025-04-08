#ifndef A_LANG_AST_HPP
#define A_LANG_AST_HPP

#include <ostream>
#include <sstream>
#include <string.h>
#include <list>
#include "tokens.hpp"
#include "types.hpp"
#include "3ac.hpp"
#include "errors.hpp"

namespace a_lang {

class TypeAnalysis;

class Opd;

class SymbolTable;
class SemSymbol;

class DeclNode;
class VarDeclNode;
class StmtNode;
class FormalDeclNode;
class TypeNode;
class ExpNode;
class IDNode;

class ASTNode{
public:
	ASTNode(const Position * pos) : myPos(pos){ }
	virtual void unparse(std::ostream&, int) = 0;
	const Position * pos() { return myPos; };
	std::string posStr(){ return pos()->span(); }
	virtual bool nameAnalysis(SymbolTable *) = 0;
	//Note that there is no ASTNode::typeAnalysis. To allow
	// for different type signatures, type analysis is
	// implemented as needed in various subclasses
protected:
	const Position * myPos = nullptr;
};

class ProgramNode : public ASTNode{
public:
	ProgramNode(std::list<DeclNode *> * globalsIn);
	void unparse(std::ostream&, int) override;
	virtual bool nameAnalysis(SymbolTable *) override;
	virtual void typeAnalysis(TypeAnalysis *);
	IRProgram * to3AC(TypeAnalysis * ta);
	virtual ~ProgramNode(){ }
private:
	std::list<DeclNode *> * myGlobals;
};

class ExpNode : public ASTNode{
protected:
	ExpNode(const Position * p) : ASTNode(p){ }
public:
	virtual void unparseNested(std::ostream& out);
	//virtual void unparse(std::ostream& out, int indent) override = 0;
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
	virtual void typeAnalysis(TypeAnalysis *) = 0;
	virtual Opd * flatten(Procedure * proc) = 0;
};

class LocNode : public ExpNode{
public:
	LocNode(const Position * p)
	: ExpNode(p), mySymbol(nullptr){}
	void attachSymbol(SemSymbol * symbolIn);
	SemSymbol * getSymbol() { return mySymbol; }
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
	virtual void typeAnalysis(TypeAnalysis *) override = 0;
	virtual Opd * flatten(Procedure * proc) override = 0;
private:
	SemSymbol * mySymbol;
};

class IDNode : public LocNode{
public:
	IDNode(const Position * p, std::string nameIn)
	: LocNode(p), name(nameIn){}
	std::string getName(){ return name; }
	void unparse(std::ostream& out, int indent) override;
	void unparseNested(std::ostream& out) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * proc) override;
private:
	std::string name;
};

class TypeNode : public ASTNode{
public:
	TypeNode(const Position * p) : ASTNode(p){ }
	void unparse(std::ostream&, int) override = 0;
	virtual const DataType * getType() const = 0;
	virtual bool nameAnalysis(SymbolTable *) override;
	virtual void typeAnalysis(TypeAnalysis *);
};

class StmtNode : public ASTNode{
public:
	StmtNode(const Position * p) : ASTNode(p){ }
	virtual void unparse(std::ostream& out, int indent) override = 0;
	virtual void typeAnalysis(TypeAnalysis *) = 0;
	virtual void to3AC(Procedure * proc) = 0;
};

class DeclNode : public StmtNode{
public:
	DeclNode(const Position * p) : StmtNode(p){ }
	void unparse(std::ostream& out, int indent) override =0;
	virtual std::string getName() = 0;
	virtual void typeAnalysis(TypeAnalysis *) override = 0;
	virtual void to3AC(IRProgram * prog) = 0;
	virtual void to3AC(Procedure * proc) override = 0;
};

class VarDeclNode : public DeclNode{
public:
	VarDeclNode(const Position * p, IDNode * inID,
	TypeNode * inType, ExpNode * inInit)
	: DeclNode(p), myID(inID), myType(inType), myInit(inInit){
		if (myType == nullptr){
			throw new InternalError("null typenode");
		}
	}
	void unparse(std::ostream& out, int indent) override;
	IDNode * ID(){ return myID; }
	virtual std::string getName() override { 
		return myID->getName(); 
	}
	virtual TypeNode * getTypeNode(){ return myType; }
	bool nameAnalysis(SymbolTable * symTab) override;
	void typeAnalysis(TypeAnalysis * typing) override;
	virtual void to3AC(Procedure * proc) override;
	virtual void to3AC(IRProgram * prog) override;
private:
	IDNode * myID;
	TypeNode * myType;
	ExpNode * myInit;
};

class FormalDeclNode : public VarDeclNode{
public:
	FormalDeclNode(const Position * p, IDNode * id, TypeNode * type)
	: VarDeclNode(p, id, type, nullptr){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void to3AC(Procedure * proc) override;
	virtual void to3AC(IRProgram * prog) override;
};

class FnDeclNode : public DeclNode{
public:
	FnDeclNode(const Position * p,
	  IDNode * inID,
	  std::list<FormalDeclNode *> * inFormals,
	  TypeNode * inRetType,
	  std::list<StmtNode *> * inBody)
	: DeclNode(p), myID(inID),
	  myFormals(inFormals), myRetType(inRetType),
	  myBody(inBody){
	}
	IDNode * ID() const { return myID; }
	virtual std::string getName() override { 
		return myID->getName(); 
	}
	std::list<FormalDeclNode *> * getFormals() const{
		return myFormals;
	}
	virtual TypeNode * getRetTypeNode() {
		return myRetType;
	}
	void unparse(std::ostream& out, int indent) override;
	virtual bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	void to3AC(IRProgram * prog) override;
	void to3AC(Procedure * prog) override;
private:
	IDNode * myID;
	std::list<FormalDeclNode *> * myFormals;
	TypeNode * myRetType;
	std::list<StmtNode *> * myBody;
};

class AssignStmtNode : public StmtNode{
public:
	AssignStmtNode(const Position * p, LocNode * inDst, ExpNode * inSrc)
	: StmtNode(p), myDst(inDst), mySrc(inSrc){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	LocNode * myDst;
	ExpNode * mySrc;
};

class MaybeStmtNode : public StmtNode{
public:
	MaybeStmtNode(const Position * p, LocNode * inDst, ExpNode * inSrc1, ExpNode * inSrc2)
	: StmtNode(p), myDst(inDst), mySrc1(inSrc1), mySrc2(inSrc2){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	LocNode * myDst;
	ExpNode * mySrc1;
	ExpNode * mySrc2;
};

class FromConsoleStmtNode : public StmtNode{
public:
	FromConsoleStmtNode(const Position * p, LocNode * inDst)
	: StmtNode(p), myDst(inDst){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	LocNode * myDst;
};

class ToConsoleStmtNode : public StmtNode{
public:
	ToConsoleStmtNode(const Position * p, ExpNode * inSrc)
	: StmtNode(p), mySrc(inSrc){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	ExpNode * mySrc;
};

class PostDecStmtNode : public StmtNode{
public:
	PostDecStmtNode(const Position * p, LocNode * inLoc)
	: StmtNode(p), myLoc(inLoc){ }
	void unparse(std::ostream& out, int indent) override;
	virtual bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	LocNode * myLoc;
};

class PostIncStmtNode : public StmtNode{
public:
	PostIncStmtNode(const Position * p, LocNode * inLoc)
	: StmtNode(p), myLoc(inLoc){ }
	void unparse(std::ostream& out, int indent) override;
	virtual bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	LocNode * myLoc;
};

class IfStmtNode : public StmtNode{
public:
	IfStmtNode(const Position * p, ExpNode * condIn,
	  std::list<StmtNode *> * bodyIn)
	: StmtNode(p), myCond(condIn), myBody(bodyIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBody;
};

class IfElseStmtNode : public StmtNode{
public:
	IfElseStmtNode(const Position * p, ExpNode * condIn,
	  std::list<StmtNode *> * bodyTrueIn,
	  std::list<StmtNode *> * bodyFalseIn)
	: StmtNode(p), myCond(condIn),
	  myBodyTrue(bodyTrueIn), myBodyFalse(bodyFalseIn) { }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBodyTrue;
	std::list<StmtNode *> * myBodyFalse;
};

class WhileStmtNode : public StmtNode{
public:
	WhileStmtNode(const Position * p, ExpNode * condIn,
	  std::list<StmtNode *> * bodyIn)
	: StmtNode(p), myCond(condIn), myBody(bodyIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * prog) override;
private:
	ExpNode * myCond;
	std::list<StmtNode *> * myBody;
};

class ReturnStmtNode : public StmtNode{
public:
	ReturnStmtNode(const Position * p, ExpNode * exp)
	: StmtNode(p), myExp(exp){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * proc) override;
private:
	ExpNode * myExp;
};

class CallExpNode : public ExpNode{
public:
	CallExpNode(const Position * p, LocNode * inCallee,
	  std::list<ExpNode *> * inArgs)
	: ExpNode(p), myCallee(inCallee), myArgs(inArgs){ }
	void unparse(std::ostream& out, int indent) override;
	void unparseNested(std::ostream& out) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	void typeAnalysis(TypeAnalysis *) override;
	DataType * getRetType();

	virtual Opd * flatten(Procedure * proc) override;
private:
	LocNode * myCallee;
	std::list<ExpNode *> * myArgs;
};

class BinaryExpNode : public ExpNode{
public:
	BinaryExpNode(const Position * p, ExpNode * lhs, ExpNode * rhs)
	: ExpNode(p), myExp1(lhs), myExp2(rhs) { }
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override = 0;
	virtual Opd * flatten(Procedure * prog) override = 0;
protected:
	ExpNode * myExp1;
	ExpNode * myExp2;
	void binaryLogicTyping(TypeAnalysis * typing);
	void binaryEqTyping(TypeAnalysis * typing);
	void binaryRelTyping(TypeAnalysis * typing);
	void binaryMathTyping(TypeAnalysis * typing);
};

class PlusNode : public BinaryExpNode{
public:
	PlusNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class MinusNode : public BinaryExpNode{
public:
	MinusNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class TimesNode : public BinaryExpNode{
public:
	TimesNode(const Position * p, ExpNode * e1In, ExpNode * e2In)
	: BinaryExpNode(p, e1In, e2In){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class DivideNode : public BinaryExpNode{
public:
	DivideNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class AndNode : public BinaryExpNode{
public:
	AndNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class OrNode : public BinaryExpNode{
public:
	OrNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class EqualsNode : public BinaryExpNode{
public:
	EqualsNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class NotEqualsNode : public BinaryExpNode{
public:
	NotEqualsNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class LessNode : public BinaryExpNode{
public:
	LessNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * proc) override;
};

class LessEqNode : public BinaryExpNode{
public:
	LessEqNode(const Position * pos, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(pos, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class GreaterNode : public BinaryExpNode{
public:
	GreaterNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * proc) override;
};

class GreaterEqNode : public BinaryExpNode{
public:
	GreaterEqNode(const Position * p, ExpNode * e1, ExpNode * e2)
	: BinaryExpNode(p, e1, e2){ }
	void unparse(std::ostream& out, int indent) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class UnaryExpNode : public ExpNode {
public:
	UnaryExpNode(const Position * p, ExpNode * expIn)
	: ExpNode(p){
		this->myExp = expIn;
	}
	virtual void unparse(std::ostream& out, int indent) override = 0;
	virtual bool nameAnalysis(SymbolTable * symTab) override = 0;
	virtual void typeAnalysis(TypeAnalysis *) override = 0;
	virtual Opd * flatten(Procedure * prog) override = 0;
protected:
	ExpNode * myExp;
};

class NegNode : public UnaryExpNode{
public:
	NegNode(const Position * p, ExpNode * exp)
	: UnaryExpNode(p, exp){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class NotNode : public UnaryExpNode{
public:
	NotNode(const Position * p, ExpNode * exp)
	: UnaryExpNode(p, exp){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class VoidTypeNode : public TypeNode{
public:
	VoidTypeNode(const Position * p) : TypeNode(p){}
	void unparse(std::ostream& out, int indent) override;
	virtual const DataType * getType() const override {
		return BasicType::VOID();
	}
};

class ImmutableTypeNode : public TypeNode{
public:
	ImmutableTypeNode(const Position * p, TypeNode * inSub)
	: TypeNode(p), mySub(inSub){}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual const DataType * getType() const override {
		return ImmutableType::produce(mySub->getType());
	};
private:
	TypeNode * mySub;
};

class IntTypeNode : public TypeNode{
public:
	IntTypeNode(const Position * p): TypeNode(p){}
	void unparse(std::ostream& out, int indent) override;
	virtual const DataType * getType() const override;
};

class BoolTypeNode : public TypeNode{
public:
	BoolTypeNode(const Position * p): TypeNode(p) { }
	void unparse(std::ostream& out, int indent) override;
	virtual const DataType * getType() const override;
};

class IntLitNode : public ExpNode{
public:
	IntLitNode(const Position * p, const int numIn)
	: ExpNode(p), myNum(numIn){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
private:
	const int myNum;
};

class StrLitNode : public ExpNode{
public:
	StrLitNode(const Position * p, const std::string strIn)
	: ExpNode(p), myStr(strIn){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable *) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * proc) override;
private:
	 const std::string myStr;
};

class TrueNode : public ExpNode{
public:
	TrueNode(const Position * p): ExpNode(p){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class FalseNode : public ExpNode{
public:
	FalseNode(const Position * p): ExpNode(p){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class EhNode : public ExpNode{
public:
	EhNode(const Position * p): ExpNode(p){ }
	virtual void unparseNested(std::ostream& out) override{
		unparse(out, 0);
	}
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override {
		return true;
	};
	virtual void typeAnalysis(TypeAnalysis * ta) override;
	virtual Opd * flatten(Procedure * prog) override;
};

class CallStmtNode : public StmtNode{
public:
	CallStmtNode(const Position * p, CallExpNode * expIn)
	: StmtNode(p), myCallExp(expIn){ }
	void unparse(std::ostream& out, int indent) override;
	bool nameAnalysis(SymbolTable * symTab) override;
	virtual void typeAnalysis(TypeAnalysis *) override;
	virtual void to3AC(Procedure * proc) override;
private:
	CallExpNode * myCallExp;
};

} //End namespace a_lang

#endif

