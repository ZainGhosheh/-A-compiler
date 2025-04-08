#include <assert.h>

#include "name_analysis.hpp"
#include "type_analysis.hpp"

namespace a_lang {

static const DataType * checkAssign(ExpNode * myDst, ExpNode * mySrc, TypeAnalysis * typing);

static bool typeCondOpd(TypeAnalysis * ta, ExpNode * node){
	node->typeAnalysis(ta);
	const DataType * type = ta->nodeType(node);

	if (type->asError()){
		return false;
	} else if (!type->isBool()){
		ta->errCond(node->pos());
		return false;
	}
	return true;
}


TypeAnalysis * TypeAnalysis::build(NameAnalysis * nameAnalysis){
	TypeAnalysis * typeAnalysis = new TypeAnalysis();
	auto ast = nameAnalysis->ast;
	typeAnalysis->ast = ast;

	ast->typeAnalysis(typeAnalysis);
	if (typeAnalysis->hasError){
		return nullptr;
	}

	return typeAnalysis;

}

void ProgramNode::typeAnalysis(TypeAnalysis * typing){
	for (auto decl : *myGlobals){
		decl->typeAnalysis(typing);
	}
	typing->nodeType(this, BasicType::VOID());
}

void IDNode::typeAnalysis(TypeAnalysis * typing){
	assert(getSymbol() != nullptr);
	const DataType * type = getSymbol()->getDataType();
	typing->nodeType(this, type);
}

void VarDeclNode::typeAnalysis(TypeAnalysis * typing){
	if (myInit){
		const DataType * res = checkAssign(myID, myInit, typing);
		if (!res){
			//Propagating error
			typing->nodeType(this, ErrorType::produce());
		} else if (res->asError()){
			//Novel error
			typing->errAssignOpr(this->pos());
			typing->nodeType(this, ErrorType::produce());
		} else {
			typing->nodeType(this, res);
		}
	} else {
		myType->typeAnalysis(typing);
		const DataType * declaredType = typing->nodeType(myType);
		//We assume that the type that comes back is valid,
		// otherwise we wouldn't have passed nameAnalysis
		typing->nodeType(this, declaredType);
	}
}

void FnDeclNode::typeAnalysis(TypeAnalysis * typing){
	myRetType->typeAnalysis(typing);
	const DataType * retDataType = typing->nodeType(myRetType);

	//auto formalTypes = new std::list<const DataType *>();
	auto formalNodes = new std::list<TypeNode *>();
	for (auto formal : *myFormals){
		formal->typeAnalysis(typing);
		TypeNode * typeNode = formal->getTypeNode();
		formalNodes->push_back(typeNode);
	}
	const TypeList * list = TypeList::produce(formalNodes);

	typing->nodeType(this, FnType::produce(list, retDataType));

	typing->setCurrentFnType(typing->nodeType(this)->asFn());
	for (auto stmt : *myBody){
		stmt->typeAnalysis(typing);
	}
	typing->setCurrentFnType(nullptr);
}

static bool validAssignOpd(const DataType * type){
	if (type->isBool() || type->isInt() ){
		return true;
	}
	if (type->asError()){
		return true;
	}
	return false;
}

static bool type_isError(const DataType * type){
	return type != nullptr && type->asError();
}


void AssignStmtNode::typeAnalysis(TypeAnalysis * typing){
	const DataType * res = checkAssign(myDst, mySrc, typing);
	if (!res){
		//Propagating error
		typing->nodeType(this, ErrorType::produce());
	} else if (res->asError()){
		//Novel error
		typing->errAssignOpr(this->pos());
		typing->nodeType(this, ErrorType::produce());
	} else {
		typing->nodeType(this, res);
	}
}

void MaybeStmtNode::typeAnalysis(TypeAnalysis * typing){
	const DataType * res1 = checkAssign(myDst, mySrc1, typing);
	const DataType * res2 = checkAssign(myDst, mySrc2, typing);
	bool res1ok = true;
	bool res2ok = true;
	if (!res1){
		//Propagating error
		typing->nodeType(this, ErrorType::produce());
		res1ok = false;
	} else if (res1->asError()){
		//Novel error
		typing->errAssignOpr(this->pos());
		typing->nodeType(this, ErrorType::produce());
		res1ok = false;
	}

	if (!res2){
		//Propagating error
		typing->nodeType(this, ErrorType::produce());
		res2ok = false;
	} else if (res2->asError()){
		//Novel error
		typing->errAssignOpr(this->pos());
		typing->nodeType(this, ErrorType::produce());
		res2ok = false;
	}

	if (res1ok && res2ok){
		typing->nodeType(this, BasicType::VOID());
	}
}

void CallExpNode::typeAnalysis(TypeAnalysis * typing){
	std::list<const DataType *> * aList = new std::list<const DataType *>();
	for (auto actual : *myArgs){
		actual->typeAnalysis(typing);
		aList->push_back(typing->nodeType(actual));
	}

	SemSymbol * calleeSym = myCallee->getSymbol();
	assert(calleeSym != nullptr);
	const DataType * calleeType = calleeSym->getDataType();
	const FnType * fnType = calleeType->asFn();
	if (fnType == nullptr){
		typing->errCallee(myCallee->pos());
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	const TypeList * formals = fnType->getFormalTypes();
	const std::list<const DataType *>* fList = formals->getTypes();
	if (aList->size() != fList->size()){
		typing->errArgCount(pos());
		//Note: we still consider the call to return the
		// return type
	} else {
		auto actualTypesItr = aList->begin();
		auto formalTypesItr = fList->begin();
		auto actualsItr = myArgs->begin();
		while(actualTypesItr != aList->end()){
			const DataType * actualType = *actualTypesItr;
			const DataType * formalType = *formalTypesItr;
			ExpNode * actual = *actualsItr;
			auto actualsItrOld = actualsItr;
			actualTypesItr++;
			formalTypesItr++;
			actualsItr++;

			//Matching to error is ignored
			if (actualType->asError()){ continue; }
			if (formalType->asError()){ continue; }

			//Ok match
			if (formalType == actualType){ continue; }

			//Bad match
			typing->errArgMatch(actual->pos());
			typing->nodeType(this, ErrorType::produce());
		}
	}

	typing->nodeType(this, fnType->getReturnType());
	return;
}

void NegNode::typeAnalysis(TypeAnalysis * typing){

	myExp->typeAnalysis(typing);
	const DataType * subType = typing->nodeType(myExp);

	//Propagate error, don't re-report
	if (subType->asError()){
		typing->nodeType(this, subType);
		return;
	} else if (subType->isInt()){
		typing->nodeType(this, BasicType::INT());
	} else {
		typing->errMathOpd(myExp->pos());
		typing->nodeType(this, ErrorType::produce());
	}
}

void NotNode::typeAnalysis(TypeAnalysis * typing){
	myExp->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myExp);

	if (childType->asError() != nullptr){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (childType->isBool()){
		typing->nodeType(this, childType);
		return;
	} else {
		typing->errLogicOpd(myExp->pos());
		typing->nodeType(this, ErrorType::produce());
		return;
	}
}

void TypeNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, this->getType());
}


static bool typeMathOpd(TypeAnalysis * typing, ExpNode * opd){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);
	if (type->isInt()){ return true; }
	if (type->asError()){
		//Don't re-report an error, but don't check for
		// incompatibility
		return false;
	}

	typing->errMathOpd(opd->pos());
	return false;
}

/*
static const DataType * getEltType(const ArrayType * arrType){
	if (arrType == nullptr){
		return ErrorType::produce();
	}
	return arrType->baseType();
}
*/

void BinaryExpNode::binaryMathTyping(
	TypeAnalysis * typing
){
	bool lhsValid = typeMathOpd(typing, myExp1);
	bool rhsValid = typeMathOpd(typing, myExp2);
	if (!lhsValid || !rhsValid){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	typing->nodeType(this, BasicType::INT());
	return;
}

static const DataType * typeLogicOpd(
	TypeAnalysis * typing, ExpNode * opd
){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);

	//Return type if it's valid
	if (type->isBool()){ return type; }

	//Don't re-report an error, but return null to
	// indicate incompatibility
	if (type->asError()){ return nullptr; }

	//If type isn't an error, but is incompatible,
	// report and indicate incompatibility
	typing->errLogicOpd(opd->pos());
	return NULL;
}

void BinaryExpNode::binaryLogicTyping(TypeAnalysis * typing){
	const DataType * lhsType = typeLogicOpd(typing, myExp1);
	const DataType * rhsType = typeLogicOpd(typing, myExp2);
	if (!lhsType || !rhsType){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	//Given valid operand types, check operator
	if (lhsType->isBool() && rhsType->isBool()){
		typing->nodeType(this, BasicType::BOOL());
		return;
	}

	//We never expect to get here, so we'll consider it
	// an error with the compiler itself
	throw new InternalError("Incomplete typing");
	typing->nodeType(this, ErrorType::produce());
	return;
}

void PlusNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void MinusNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void TimesNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void DivideNode::typeAnalysis(TypeAnalysis * typing){
	binaryMathTyping(typing);
}

void AndNode::typeAnalysis(TypeAnalysis * typing){
	binaryLogicTyping(typing);
}

void OrNode::typeAnalysis(TypeAnalysis * typing){
	binaryLogicTyping(typing);
}

static const DataType * typeEqOpd(
	TypeAnalysis * typing, ExpNode * opd
){
	assert(opd != nullptr || "opd is null!");

	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);

	if (type->isInt()){ return type; }
	if (type->isBool()){ return type; }

	//Errors are invalid, but don't cause re-reports
	if (type->asError()){ return ErrorType::produce(); }

	typing->errEqOpd(opd->pos());
	return ErrorType::produce();
}

void BinaryExpNode::binaryEqTyping(TypeAnalysis * typing){
	const DataType * lhsType = typeEqOpd(typing, myExp1);
	const DataType * rhsType = typeEqOpd(typing, myExp2);

	if (lhsType->asError() || rhsType->asError()){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (lhsType == rhsType){
		typing->nodeType(this, BasicType::BOOL());
		return;
	}

	typing->errEqOpr(pos());
	typing->nodeType(this, ErrorType::produce());
	return;
}

void EqualsNode::typeAnalysis(TypeAnalysis * typing){
	binaryEqTyping(typing);
	assert(typing->nodeType(this) != nullptr);
}

void NotEqualsNode::typeAnalysis(TypeAnalysis * typing){
	binaryEqTyping(typing);
}

static const DataType * typeRelOpd(
	TypeAnalysis * typing, ExpNode * opd
){
	opd->typeAnalysis(typing);
	const DataType * type = typing->nodeType(opd);

	if (type->isInt()){ return type; }

	//Errors are invalid, but don't cause re-reports
	if (type->asError()){ return nullptr; }

	typing->errRelOpd(opd->pos());
	typing->nodeType(opd, ErrorType::produce());
	return nullptr;
}

void BinaryExpNode::binaryRelTyping(TypeAnalysis * typing){
	const DataType * lhsType = typeRelOpd(typing, myExp1);
	const DataType * rhsType = typeRelOpd(typing, myExp2);

	if (!lhsType || !rhsType){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (lhsType->isInt() && rhsType->isInt()){
		typing->nodeType(this, BasicType::BOOL());
		return;
	}

	//There is no bad relational operator, so we never
	// expect to get here
	return;
}

void GreaterNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void GreaterEqNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void LessNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void LessEqNode::typeAnalysis(TypeAnalysis * typing){
	binaryRelTyping(typing);
}

void PostDecStmtNode::typeAnalysis(TypeAnalysis * typing){
	this->myLoc->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(this->myLoc);

	if (childType->asError()){ return; }
	if (childType->isInt()){ return; }

	//Any other unary math is an error
	typing->errMathOpd(myLoc->pos());
}

void PostIncStmtNode::typeAnalysis(TypeAnalysis * typing){
	this->myLoc->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(this->myLoc);

	if (childType->asError()){ return; }
	if (childType->isInt()){ return; }

	//Any other unary math is an error
	typing->errMathOpd(this->myLoc->pos());
}

void FromConsoleStmtNode::typeAnalysis(TypeAnalysis * typing){
	myDst->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myDst);

	typing->nodeType(this, BasicType::VOID());

	if (childType->isBool()){
		return;
	} else if (childType->isInt()){
		return;
	} else if (childType->asFn()){
		typing->errReadFn(myDst->pos());
		typing->nodeType(this, ErrorType::produce());
		return;
	} else if (childType->asError()){
		typing->nodeType(this, ErrorType::produce());
		return;
	}
	typing->nodeType(this, BasicType::VOID());
}

void ToConsoleStmtNode::typeAnalysis(TypeAnalysis * typing){
	mySrc->typeAnalysis(typing);
	const DataType * srcType = typing->nodeType(mySrc);

	typing->nodeType(this, BasicType::VOID());

	//Mark error, but don't re-report
	if (srcType->asError()){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	//Check for invalid type
	if (srcType->isVoid()){
		typing->errOutputVoid(mySrc->pos());
		typing->nodeType(this, ErrorType::produce());
		return;
	} else if (srcType->asFn()){
		typing->errOutputFn(mySrc->pos());
		typing->nodeType(this, ErrorType::produce());
		return;
	} else if (srcType->asBasic()){
		//Can write to any var type
		return;
	}

}

void IfStmtNode::typeAnalysis(TypeAnalysis * typing){
	//Start off the typing as void, but may update to error
	typing->nodeType(this, BasicType::VOID());

	myCond->typeAnalysis(typing);
	const DataType * condType = typing->nodeType(myCond);
	bool goodCond = true;
	if (condType == nullptr){
		typing->nodeType(this, ErrorType::produce());
		goodCond = false;
	} else if (condType->asError()){
		typing->nodeType(this, ErrorType::produce());
		goodCond = false;
	} else if (!condType->isBool()){
		goodCond = false;
		typing->errCond(myCond->pos());
		typing->nodeType(this,
			ErrorType::produce());
	}

	for (auto stmt : *myBody){
		stmt->typeAnalysis(typing);
	}

	if (goodCond){
		typing->nodeType(this, BasicType::produce(VOID));
	} else {
		typing->nodeType(this, ErrorType::produce());
	}
}

void IfElseStmtNode::typeAnalysis(TypeAnalysis * typing){
	myCond->typeAnalysis(typing);
	const DataType * condType = typing->nodeType(myCond);

	bool goodCond = true;
	if (condType->asError()){
		goodCond = false;
		typing->nodeType(this, ErrorType::produce());
	} else if (!condType->isBool()){
		typing->errCond(myCond->pos());
		goodCond = false;
	}
	for (auto stmt : *myBodyTrue){
		stmt->typeAnalysis(typing);
	}
	for (auto stmt : *myBodyFalse){
		stmt->typeAnalysis(typing);
	}

	if (goodCond){
		typing->nodeType(this, BasicType::produce(VOID));
	} else {
		typing->nodeType(this, ErrorType::produce());
	}
}

void WhileStmtNode::typeAnalysis(TypeAnalysis * typing){
	myCond->typeAnalysis(typing);
	const DataType * condType = typing->nodeType(myCond);

	typing->nodeType(this, BasicType::VOID());
	if (condType->asError()){
		typing->nodeType(this, ErrorType::produce());
	} else if (!condType->isBool()){
		typing->errCond(myCond->pos());
	}

	for (auto stmt : *myBody){
		stmt->typeAnalysis(typing);
	}

}

void CallStmtNode::typeAnalysis(TypeAnalysis * typing){
	myCallExp->typeAnalysis(typing);
	typing->nodeType(this, BasicType::VOID());
}

void ReturnStmtNode::typeAnalysis(TypeAnalysis * typing){
	const FnType * fnType = typing->getCurrentFnType();
	const DataType * fnRet = fnType->getReturnType();

	//Check: shouldn't return anything
	if (fnRet == BasicType::VOID()){
		if (myExp != nullptr) {
			myExp->typeAnalysis(typing);
			typing->extraRetValue(myExp->pos());
			typing->nodeType(this, ErrorType::produce());
		} else {
			typing->nodeType(this, BasicType::VOID());
		}
		return;
	}

	//Check: returns nothing, but should
	if (myExp == nullptr){
		typing->errRetEmpty(pos());
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	myExp->typeAnalysis(typing);
	const DataType * childType = typing->nodeType(myExp);

	if (childType->asError()){
		typing->nodeType(this, ErrorType::produce());
		return;
	}

	if (childType != fnRet){
		typing->errRetWrong(myExp->pos());
		typing->nodeType(this, ErrorType::produce());
		return;
	}
	typing->nodeType(this, ErrorType::produce());
	return;
}

void StrLitNode::typeAnalysis(TypeAnalysis * typing){
	BasicType * basic = BasicType::STRING();
	//ArrayType * asArr = ArrayType::produce(basic, 0);
	typing->nodeType(this, basic);
}

void FalseNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, BasicType::BOOL());
}

void TrueNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, BasicType::BOOL());
}

void EhNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, BasicType::BOOL());
}

void IntLitNode::typeAnalysis(TypeAnalysis * typing){
	typing->nodeType(this, BasicType::INT());
}


static const DataType * checkAssign(ExpNode * myDst, ExpNode * mySrc, TypeAnalysis * typing){
	myDst->typeAnalysis(typing);
	mySrc->typeAnalysis(typing);
	const DataType * dstType = typing->nodeType(myDst);
	const DataType * srcType = typing->nodeType(mySrc);

	bool validOperands = true;
	bool knownError = type_isError(dstType) || type_isError(srcType);
	if (!validAssignOpd(dstType)){
		typing->errAssignOpd(myDst->pos());
		validOperands = false;
	}
	if (!validAssignOpd(srcType)){
		typing->errAssignOpd(mySrc->pos());
		validOperands = false;
	}
	if (!validOperands || knownError){
		//Error type, but due to propagation
		return nullptr; 
	}

	if (dstType == srcType){
		bool isError = false;
		if (dstType->asFn()){
			typing->errAssignOpd(myDst->pos());
			typing->errAssignOpd(mySrc->pos());
		}
		else {
			return BasicType::VOID();
		}
	}

	return ErrorType::produce();
}

}
