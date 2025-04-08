#ifndef A_LANG_TYPE_ANALYSIS
#define A_LANG_TYPE_ANALYSIS

#include "ast.hpp"
#include "symbol_table.hpp"
#include "types.hpp"


namespace a_lang {

class NameAnalysis;

// An instance of this class will be passed over the entire
// AST. Rather than attaching types to each node, the
// TypeAnalysis class contains a map from each ASTNode to it's
// DataType. Thus, instead of attaching a type field to most nodes,
// one can instead map the node to it's type, or lookup the node
// in the map.
class TypeAnalysis {

private:
	//The private constructor here means that the type analysis
	// can only be created via the static build function
	TypeAnalysis(){
		hasError = false;
	}

public:
	static TypeAnalysis * build(NameAnalysis * astRoot);
	//static TypeAnalysis * build();

	//The type analysis has an instance variable to say whether
	// the analysis failed or not. Setting this variable is much
	// less of a pain than passing a boolean all the way up to the
	// root during the TypeAnalysis pass.
	bool passed(){
		return !hasError;
	}

	void setCurrentFnType(const FnType * type){
		currentFnType = type;
	}

	const FnType * getCurrentFnType(){
		return currentFnType;
	}

	//Set the type of a node. Note that the function name is
	// overloaded: this 2-argument nodeType puts a value into the
	// map with a given type.
	void nodeType(const ASTNode * node, const DataType * type){
		nodeToType[node] = type;
	}

	//Gets the type of a node already placed in the map. Note
	// that this function name is overloaded: the 1-argument nodeType
	// gets the type of the given node out of the map.
	const DataType * nodeType(const ASTNode * node){
		const DataType * res = nodeToType[node];
		if (res == nullptr){
			const char * msg = "No type for node ";
			throw new InternalError(msg);
		}
		return nodeToType[node];
	}

	//The following functions all report and error and
	// tell the object that the analysis has failed.
	void errOutputFn(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Attempt to output a function");
	}
	void errOutputClass(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Attempt to output a class");
	}
	void errOutputVoid(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Attempt to output void");
	}

	void errReadFn(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Attempt to assign user input to function");
	}
	void errReadClass(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Attempt to assign user input to class");
	}
	void errCallee(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Attempt to call a "
			"non-function");
	}
	void errArgCount(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Function call with wrong"
			" number of args");
	}
	void errArgMatch(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Type of actual does not match"
			" type of formal");
	}
	void errRetEmpty(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Missing return value");
	}
	void extraRetValue(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Return with a value in void"
			" function");
	}
	void errRetWrong(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Bad return value");
	}
	void errMathOpd(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Arithmetic operator applied"
			" to invalid operand");
	}
	void errRelOpd(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Relational operator applied to"
			" non-numeric operand");
	}
	void errLogicOpd(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Logical operator applied to"
			" non-bool operand");
	}
	void errCond(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Non-bool expression used as"
			" a condition");
	}
	void errEqOpd(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Invalid equality operand");
	}
	void errEqOpr(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Invalid equality operation");
	}
	void errAssignOpd(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Invalid assignment operand");
	}
	void errAssignOpr(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Invalid assignment operation");
	}
	void errAssignNonLVal(const Position * pos){
		hasError = true;
		Report::fatal(pos,
			"Non-lval assignment");
	}
private:
	HashMap<const ASTNode *, const DataType *> nodeToType;
	const FnType * currentFnType;
	bool hasError;
public:
	ProgramNode * ast;
};

}
#endif
