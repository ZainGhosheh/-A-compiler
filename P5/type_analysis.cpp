#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"
#include "types.hpp"
#include "name_analysis.hpp"
#include "type_analysis.hpp"

namespace a_lang{

static void arithmeticTypeCheck(TypeAnalysis * ta, ExpNode * exp1, ASTNode * thisNode, const Position * pos) {
	// First we need to do type analysis on the operands
	exp1->typeAnalysis(ta);

	// Get the types of the operands
	const DataType * expType = ta->nodeType(exp1);

	// Check if the operands are not valid for the operator
	if (expType->asError()) {
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	// Check if the operands are not numeric
	if (!expType->isInt()) {

		ta->errMathOpd(pos); // TODO pos @ The offending expression operand root node
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	// Set the type of the binary expression to the type of the operands
	ta->nodeType(thisNode, BasicType::produce(INT));
}

static void logicalTypeCheck(TypeAnalysis * ta, ExpNode * exp, ASTNode * thisNode, const Position * pos) {
	// First we need to do type analysis on the operands
	exp->typeAnalysis(ta);

	// Get the types of the operands
	const DataType * expType = ta->nodeType(exp);

	// Check if the operands are not valid for the operator
	if (expType->asError()) {
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	// Check if the operands are not numeric
	if (!expType->isBool()) {
		ta->errLogicOpd(pos); // TODO pos @ The offending expression operand root node
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	// Set the type of the binary expression to the type of the operands
	ta->nodeType(thisNode, BasicType::produce(BOOL));
}

static void equalityTypeCheck(TypeAnalysis * ta, ExpNode * exp1, ExpNode * exp2, ASTNode * thisNode, const Position * pos) {
	// First we need to do type analysis on the operands
	exp1->typeAnalysis(ta);
	exp2->typeAnalysis(ta);

	// Get the types of the operands
	const DataType * leftType = ta->nodeType(exp1);
	const DataType * rightType = ta->nodeType(exp2);


	// Applying an (in)equality operator to two valid but incompatible operands,
	// such as an int to a bool.
	// String bool int


	// Check if the operands are not valid for the operator
	if (leftType->asError() || rightType->asError()) {
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	/*
		Equality operations are legal if and only if:

		* Both operands are of the same primitive type
		* Neither operands are of the same class type
			AND
		* Neither operand is a function type
	*/
	if (leftType->asFn() || rightType->asFn()) {
		ta->errEqOpd(thisNode->pos());
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}
	// else if (leftType->isClass() && rightType->isClass()) {
	// 	// if (leftType == rightType) { // TODO : this may not be right
	// 	// 	ta->nodeType(thisNode, BasicType::produce(BOOL));
	// 	// 	return;
	// 	// }

	// 	ta->errEqOpd(thisNode->pos());
	// 	ta->nodeType(thisNode, ErrorType::produce());
	// 	return;
	// }
	else if (leftType->isClass() || rightType->isClass()) {
		ta->errEqOpd(thisNode->pos());
		Report::fatal(thisNode->pos(), "Equality operator applied to custom names");
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}
	else if (leftType->isVoid() || rightType->isVoid()) {
		ta->errEqOpd(thisNode->pos());
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	if (leftType != rightType) {
		ta->errEqOpr(thisNode->pos());
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	// Set the type of the binary expression to the type of the operands
	ta->nodeType(thisNode, BasicType::produce(BOOL));
}

static void relationalTypeCheck(TypeAnalysis * ta, ExpNode * exp, ASTNode * thisNode, const Position * pos) {
	// First we need to do type analysis on the operands
	exp->typeAnalysis(ta);

	// Get the types of the operands
	const DataType * expType = ta->nodeType(exp);

	// Check if the operands are not valid for the operator
	if (expType->asError()) {
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	// Check if the operands are not numeric
	if (!expType->isInt()) {
		ta->errRelOpd(pos);
		ta->nodeType(thisNode, ErrorType::produce());
		return;
	}

	// Set the type of the binary expression to the type of the operands
	ta->nodeType(thisNode, BasicType::produce(BOOL));
}

TypeAnalysis * TypeAnalysis::build(NameAnalysis * nameAnalysis){
	//To emphasize that type analysis depends on name analysis
	// being complete, a name analysis must be supplied for 
	// type analysis to be performed.
	TypeAnalysis * typeAnalysis = new TypeAnalysis();
	auto ast = nameAnalysis->ast;	
	typeAnalysis->ast = ast;

	ast->typeAnalysis(typeAnalysis);
	if (typeAnalysis->hasError){
		return nullptr;
	}

	return typeAnalysis;
}

void ProgramNode::typeAnalysis(TypeAnalysis * ta){

	//pass the TypeAnalysis down throughout
	// the entire tree, getting the types for
	// each element in turn and adding them
	// to the ta object's hashMap
	for (auto global : *myGlobals){
		global->typeAnalysis(ta);
	}

	//The type of the program node will never
	// be needed. We can just set it to VOID
	//(Alternatively, we could make our type 
	// be error if the DeclListNode is an error)
	ta->nodeType(this, BasicType::produce(VOID));
}

void FnDeclNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
    // Get the return type of the function
    const DataType * returnType = myRetType->getType();

	for (auto stmt : *myBody){
		stmt->typeAnalysis(ta, returnType);
	}
}

void StmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	TODO("Implement me in the subclass");
}

void AssignStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){ // TODO
	//Do typeAnalysis on the subexpressions
	myDst->typeAnalysis(ta);
	mySrc->typeAnalysis(ta);

	const DataType * tgtType = ta->nodeType(myDst);
	const DataType * srcType = ta->nodeType(mySrc);

	// As error returns null if subType is NOT an error type
	// otherwise, it returns the subType itself. It 
	// sort of serves as a way to cast the subtype
	if (tgtType->asError() || srcType->asError()) {
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	// Check if the LHS of the assignment is an lvalue
	if (tgtType->isPerfect()) {
		ta->errAssignNonLVal(this->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	// Applying an invalid operand to an assignment (either as the target or
	// source). e.g., "f = g;", where f and/or g are function names.
	if (tgtType->asFn() || srcType->asFn()){
		ta->errAssignOpd(this->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	// It is ILLEGAL for the operand of an assignment to be a class name
	// or instance of a class.
	if (tgtType->isClass()){ // TODO
		Report::fatal(this->pos(), "custom name assignment");
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	// Check if the types of the LHS and RHS of the assignment are not the same
	// Applying an assignment to two valid but incompatible types.
	// e.g., "f = g;", where f is a bool and g is an int.
	if (tgtType != srcType) {
		ta->errAssignOpr(this->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	//While incomplete, this gives you one case for 
	// assignment: if the types are exactly the same
	// it is usually ok to do the assignment. One
	// exception is that if both types are function
	// names, it should fail type analysis
	if (tgtType->asFn() && srcType->asFn()){
		ta->errAssignOpd(this->pos());
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	if (tgtType == srcType){
		ta->nodeType(this, tgtType);
		return;
	}
	
	//Some functions are already defined for you to
	// report type errors. Note that these functions
	// also tell the typeAnalysis object that the
	// analysis has failed, meaning that main.cpp
	// will print "Type check failed" at the end
	ta->errAssignOpr(this->pos());


	// Here, we set the type of the assignment
	// to void to indicate no error was found.
	// This step is optional, since you'll never
	// use the type of a statement
	ta->nodeType(this, BasicType::produce(VOID));

}

void MaybeStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){ // TODO
	myDst->typeAnalysis(ta);
	mySrc1->typeAnalysis(ta);
	mySrc2->typeAnalysis(ta);
}

void FromConsoleStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt) {
	myDst->typeAnalysis(ta);
	const DataType * srcType = ta->nodeType(myDst);
	if (srcType->isClass())
	{
		ta->errReadClass(this->pos()); // TODO: pos @ argument to fromconsole
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	else if (srcType->asFn())
	{
		ta->errReadFn(this->pos()); // TODO: pos @ function name IDNode
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(VOID));
}

void ToConsoleStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt) {
	mySrc->typeAnalysis(ta);
	const DataType * srcType = ta->nodeType(mySrc);
	if (srcType->isClass())
	{
		ta->errOutputClass(this->pos()); // TODO: pos @ expression node being written
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	else if (srcType->asFn())
	{
		ta->errOutputFn(this->pos()); // TODO: pos @ function name IDNode
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	else if (srcType->isVoid())
	{
		ta->errOutputVoid(this->pos()); // TODO: pos @ call expression node
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(VOID));
}

void PostDecStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	arithmeticTypeCheck(ta, myLoc, this, this->pos());
}

void PostIncStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	arithmeticTypeCheck(ta, myLoc, this, this->pos());
}

void IfStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	myCond->typeAnalysis(ta);
	const DataType * condType = ta->nodeType(myCond);
	if (!condType->isBool())
	{
		ta->errCond(this->pos());
		ta->nodeType(this, ErrorType::produce());
	}
	for (auto stmt : *myBody)
	{
		stmt->typeAnalysis(ta, dt);
	}
}

void IfElseStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	myCond->typeAnalysis(ta);
	const DataType * condType = ta->nodeType(myCond);
	if (!condType->isBool())
	{
		ta->errCond(this->pos());
		ta->nodeType(this, ErrorType::produce());
	}
	for (auto stmt : *myBodyTrue)
	{
		stmt->typeAnalysis(ta, dt);
	}
	for (auto stmt : *myBodyFalse)
	{
		stmt->typeAnalysis(ta, dt);
	}
}

void WhileStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	myCond->typeAnalysis(ta);
	const DataType * condType = ta->nodeType(myCond);
	if (!condType->isBool())
	{
		ta->errCond(this->pos());
		ta->nodeType(this, ErrorType::produce());
	}
	for (auto stmt : *myBody)
	{
		stmt->typeAnalysis(ta, dt);
	}
}

void ReturnStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * fnRetType){
    const DataType * actualReturnType = nullptr;
	if (myExp)
	{
		myExp->typeAnalysis(ta);
    	actualReturnType = ta->nodeType(myExp);
	}

    // Check if the expression's type is an error
    if (actualReturnType && actualReturnType->asError()) {
        ta->nodeType(this, ErrorType::produce());
        return;
    }

	// Check for missing return value
	if (actualReturnType == nullptr && !fnRetType->isVoid()) {
		ta->errRetEmpty(this->pos()); // todo err @ Return subexpression
		ta->nodeType(this, ErrorType::produce());
		return;
	}

    // Check if the actual return type matches the expected return type
    if (actualReturnType != fnRetType) {
        // Report a type error if the return types do not match
		fnRetType->isVoid() ? ta->extraRetValue(this->pos()) : ta->errRetWrong(this->pos()); // todo err @ Return subexpression
        ta->nodeType(this, ErrorType::produce());
		return;
    } else {
        // Set the node type to the actual return type if there is no error
        ta->nodeType(this, actualReturnType);
    }
}

void CallStmtNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	myCallExp->typeAnalysis(ta);
	const auto * retType = ta->nodeType(myCallExp);
	if (retType->asError()) {
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	ta->nodeType(this, BasicType::produce(VOID));
}

void ExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void DeclNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	TODO("Override me in the subclass");
}

void ClassDefnNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){
	myID->typeAnalysis(ta);
	for (auto member : *myMembers)
	{
		member->typeAnalysis(ta);
	}
	// ta->nodeType(this, myID->getSymbol()->getDataType());
}

void VarDeclNode::typeAnalysis(TypeAnalysis * ta, const DataType * dt){ // TODO
	myID->typeAnalysis(ta);
	myType->typeAnalysis(ta);
	if (myInit)
	{
		myInit->typeAnalysis(ta);
		const DataType * initType = ta->nodeType(myInit);
		const DataType * declType = ta->nodeType(myType);

		// Check if the initialization expression is an error
		if (initType->asError()) {
			// ta->err(this->pos()); // TODO: what error?
			ta->nodeType(this, ErrorType::produce());
			return;
		}

		// Check if the initialization expression is not the same type as the declaration
		if (initType != declType) {
			ta->errAssignOpr(this->pos());
			ta->nodeType(this, ErrorType::produce());
			return;
		}
	}

	// VarDecls always pass type analysis, since they 
	// are never used in an expression. You may choose
	// to type them void (like this), as discussed in class
	ta->nodeType(this, BasicType::produce(VOID));
}

void IDNode::typeAnalysis(TypeAnalysis * ta){
	// IDs never fail type analysis and always
	// yield the type of their symbol (which
	// depends on their definition)
	ta->nodeType(this, this->getSymbol()->getDataType());
}

void MemberFieldExpNode::typeAnalysis(TypeAnalysis * ta){ // TODO
	// Get the type of the object
	myBase->typeAnalysis(ta);
	myField->typeAnalysis(ta);
	const DataType * baseType = ta->nodeType(myBase);

	// Check if the object is not a class
	if (!baseType->isClass()) {
		// ta->(this->pos()); // TODO: what error?
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	// Get the class type
	const ClassType * classType = baseType->asClass();
	// Get the field's type
	const SemSymbol * field = classType->getField(classType, myField->getName());

	// Check if the field is not a member of the class
	if (field == nullptr) {
		// ta->err(this->pos()); // TODO: what error?
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	// Set the type of the member field expression to the type of the field
	ta->nodeType(this, field->getDataType());
}

void CallExpNode::typeAnalysis(TypeAnalysis * ta){
	// First we need to do type analysis on the callee
	myCallee->typeAnalysis(ta);

	// Get the callee's type
	const DataType * calleeType = ta->nodeType(myCallee);

	if (calleeType->asError()) {
		ta->nodeType(this, ErrorType::produce());
		return;
	}

	// Check if the callee is not a function
	if (calleeType->asFn() == nullptr) {
		ta->errCallee(this->pos()); // TODO pos @ Variable IDNode 
		ta->nodeType(this, ErrorType::produce());
		return;
	}
	else {
		// Get the function's return type
		if (calleeType->asFn()->getReturnType() == nullptr) {
			// should never happen
			ta->errRetEmpty(this->pos());
			ta->nodeType(this, calleeType->asFn()->getReturnType());
			return;
		}

		// Check if the number of arguments matches the number of formals
		if (myArgs->size() != calleeType->asFn()->getFormalTypes()->count()) {
			ta->errArgCount(this->pos()); // TODO pos @ IDNode for the function name.
		}

		// Check if the types of the arguments match the types of the formals
		// If there are several arguments with the wrong type, give an error for each
		auto formalTypesList = calleeType->asFn()->getFormalTypes()->getTypes();
		auto argIt = myArgs->begin();
		auto formalIt = formalTypesList->begin();
		for (; argIt != myArgs->end(); ++argIt, ++formalIt) {
			(*argIt)->typeAnalysis(ta);
			const DataType * argType = ta->nodeType(*argIt);
			const DataType * formalType = *formalIt;
			if (argType != formalType) {
				ta->errArgMatch((*argIt)->pos()); // TODO pos @ Actual argument subexpression node
			}
		}

		ta->nodeType(this, calleeType->asFn()->getReturnType());
	}
}

void BinaryExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void PlusNode::typeAnalysis(TypeAnalysis * ta){
	arithmeticTypeCheck(ta, myExp1, this, myExp1->pos());
	arithmeticTypeCheck(ta, myExp2, this, myExp2->pos());
}

void MinusNode::typeAnalysis(TypeAnalysis * ta){
	arithmeticTypeCheck(ta, myExp1, this, myExp1->pos());
	arithmeticTypeCheck(ta, myExp2, this, myExp2->pos());
}

void TimesNode::typeAnalysis(TypeAnalysis * ta){
	arithmeticTypeCheck(ta, myExp1, this, myExp1->pos());
	arithmeticTypeCheck(ta, myExp2, this, myExp2->pos());
}

void DivideNode::typeAnalysis(TypeAnalysis * ta){
	arithmeticTypeCheck(ta, myExp1, this, myExp1->pos());
	arithmeticTypeCheck(ta, myExp2, this, myExp2->pos());
}

void AndNode::typeAnalysis(TypeAnalysis * ta){
	logicalTypeCheck(ta, myExp1, this, myExp1->pos());
	logicalTypeCheck(ta, myExp2, this, myExp2->pos());
}

void OrNode::typeAnalysis(TypeAnalysis * ta){
	logicalTypeCheck(ta, myExp1, this, myExp1->pos());
	logicalTypeCheck(ta, myExp2, this, myExp2->pos());
}

void EqualsNode::typeAnalysis(TypeAnalysis * ta){
	equalityTypeCheck(ta, myExp1, myExp2, this, this->pos());
}

void NotEqualsNode::typeAnalysis(TypeAnalysis * ta){
	equalityTypeCheck(ta, myExp1, myExp2, this, this->pos());
}

void LessNode::typeAnalysis(TypeAnalysis * ta){
	relationalTypeCheck(ta, myExp1, this, myExp1->pos());
	relationalTypeCheck(ta, myExp2, this, myExp2->pos());
}

void LessEqNode::typeAnalysis(TypeAnalysis * ta){
	relationalTypeCheck(ta, myExp1, this, myExp1->pos());
	relationalTypeCheck(ta, myExp2, this, myExp2->pos());
}

void GreaterNode::typeAnalysis(TypeAnalysis * ta){
	relationalTypeCheck(ta, myExp1, this, myExp1->pos());
	relationalTypeCheck(ta, myExp2, this, myExp2->pos());
}

void GreaterEqNode::typeAnalysis(TypeAnalysis * ta){
	relationalTypeCheck(ta, myExp1, this, myExp1->pos());
	relationalTypeCheck(ta, myExp2, this, myExp2->pos());
}

void UnaryExpNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void NegNode::typeAnalysis(TypeAnalysis * ta){
	arithmeticTypeCheck(ta, myExp, this, this->pos());
}

void NotNode::typeAnalysis(TypeAnalysis * ta){
	logicalTypeCheck(ta, myExp, this, this->pos());
}

void IntLitNode::typeAnalysis(TypeAnalysis * ta){
	// IntLits never fail their type analysis and always
	// yield the type INT
	ta->nodeType(this, BasicType::produce(INT));
}

void StrLitNode::typeAnalysis(TypeAnalysis * ta){
	// StrLits never fail their type analysis and always
	// yield the type STRING
	ta->nodeType(this, BasicType::produce(STRING));
}

void TrueNode::typeAnalysis(TypeAnalysis * ta){
	// TrueNodes never fail their type analysis and always
	// yield the type BOOL
	ta->nodeType(this, BasicType::produce(BOOL));
}

void FalseNode::typeAnalysis(TypeAnalysis * ta){
	// FalseNodes never fail their type analysis and always
	// yield the type BOOL
	ta->nodeType(this, BasicType::produce(BOOL));
}

void EhNode::typeAnalysis(TypeAnalysis * ta){
	// EhNodes never fail their type analysis and always
	// yield the type BOOL
	ta->nodeType(this, BasicType::produce(BOOL));
}

void TypeNode::typeAnalysis(TypeAnalysis * ta){
	TODO("Override me in the subclass");
}

void ClassTypeNode::typeAnalysis(TypeAnalysis * ta){
	// ClassTypeNodes never fail their type analysis and always
	// yield the type CLASS
	ta->nodeType(this, BasicType::produce(CLASS));
}

void VoidTypeNode::typeAnalysis(TypeAnalysis * ta){
	// VoidTypeNodes never fail their type analysis and always
	// yield the type VOID
	ta->nodeType(this, BasicType::produce(VOID));
}

void ImmutableTypeNode::typeAnalysis(TypeAnalysis * ta){
	// ImmutableTypeNodes never fail their type analysis and always
	// yield the type IMMUTABLE
	ta->nodeType(this, mySub->getType());
}

void RefTypeNode::typeAnalysis(TypeAnalysis * ta){
	// RefTypeNodes never fail their type analysis and always
	// yield the type REF
	ta->nodeType(this, mySub->getType());
}

void IntTypeNode::typeAnalysis(TypeAnalysis * ta){
	// IntTypeNodes never fail their type analysis and always
	// yield the type INT
	ta->nodeType(this, BasicType::produce(INT));
}

void BoolTypeNode::typeAnalysis(TypeAnalysis * ta){
	// BoolTypeNodes never fail their type analysis and always
	// yield the type BOOL
	ta->nodeType(this, BasicType::produce(BOOL));
}
}
