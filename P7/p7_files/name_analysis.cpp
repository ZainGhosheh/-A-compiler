#include "ast.hpp"
#include "symbol_table.hpp"
#include "errName.hpp"
#include "types.hpp"

namespace a_lang{

bool ProgramNode::nameAnalysis(SymbolTable * symTab){
	//Enter the global scope
	symTab->enterScope();

	bool res = true;
	for (auto decl : *myGlobals){
		res = decl->nameAnalysis(symTab) && res;
	}
	//Leave the global scope
	symTab->leaveScope();
	return res;
}

bool AssignStmtNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myDst->nameAnalysis(symTab) && result;
	result = mySrc->nameAnalysis(symTab) && result;
	return result;
}

bool PostDecStmtNode::nameAnalysis(SymbolTable * symTab){
	return this->myLoc->nameAnalysis(symTab);
}

bool PostIncStmtNode::nameAnalysis(SymbolTable * symTab){
	return this->myLoc->nameAnalysis(symTab);
}

bool FromConsoleStmtNode::nameAnalysis(SymbolTable * symTab){
	return myDst->nameAnalysis(symTab);
}

bool ToConsoleStmtNode::nameAnalysis(SymbolTable * symTab){
	return mySrc->nameAnalysis(symTab);
}

bool IfStmtNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myCond->nameAnalysis(symTab) && result;
	symTab->enterScope();
	for (auto stmt : *myBody){
		result = stmt->nameAnalysis(symTab) && result;
	}
	symTab->leaveScope();
	return result;
}

bool IfElseStmtNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myCond->nameAnalysis(symTab) && result;
	symTab->enterScope();
	for (auto stmt : *myBodyTrue){
		result = stmt->nameAnalysis(symTab) && result;
	}
	symTab->leaveScope();
	symTab->enterScope();
	for (auto stmt : *myBodyFalse){
		result = stmt->nameAnalysis(symTab) && result;
	}
	symTab->leaveScope();
	return result;
}

bool WhileStmtNode::nameAnalysis(SymbolTable * symTab){
	bool result = true;
	result = myCond->nameAnalysis(symTab) && result;
	symTab->enterScope();
	for (auto stmt : *myBody){
		result = stmt->nameAnalysis(symTab) && result;
	}
	symTab->leaveScope();
	return result;
}

bool VarDeclNode::nameAnalysis(SymbolTable * symTab){
	bool validType = myType->nameAnalysis(symTab);
	std::string varName = ID()->getName();
	const DataType * dataType = getTypeNode()->getType();
	bool validInit = true;
	if (myInit != nullptr){
		validInit = myInit->nameAnalysis(symTab);
	}

	if (dataType == nullptr){
		throw new InternalError("typeNode null");
		validType = false;
	} else if (validType){
		validType = dataType->validVarType();
	}

	if (!validType && !dataType->asError()){
		NameErr::badVarType(ID()->pos());
	}

	bool validName = !symTab->clash(varName);
	if (!validName){ NameErr::multiDecl(ID()->pos()); }

	if (!validType || !validName || !validInit){
		return false;
	} else {
		symTab->insert(new VarSymbol(varName, dataType));
		SemSymbol * sym = symTab->find(varName);
		this->myID->attachSymbol(sym);
		return true;
	}
}

bool ImmutableTypeNode::nameAnalysis(SymbolTable * symTab){
	return mySub->nameAnalysis(symTab);
}

bool FnDeclNode::nameAnalysis(SymbolTable * symTab){
	std::string fnName = this->ID()->getName();

	bool validRet = myRetType->nameAnalysis(symTab);

	// hold onto the scope of the function.
	ScopeTable * atFnScope = symTab->getCurrentScope();
	//Enter a new scope for "within" this function.
	ScopeTable * inFnScope = symTab->enterScope();

	/*Note that we check for a clash of the function
	  name in it's declared scope (e.g. a global
	  scope for a global function)
	*/
	bool validName = true;
	if (atFnScope->clash(fnName)){
		NameErr::multiDecl(ID()->pos());
		validName = false;
	}

	bool validFormals = true;
	auto formalTypeNodes = list<TypeNode *>();
	for (auto formal : *(this->myFormals)){
		validFormals = formal->nameAnalysis(symTab) && validFormals;
		TypeNode * formalTypeNode = formal->getTypeNode();
		formalTypeNodes.push_back(formalTypeNode);
	}
	auto formalTypes = TypeList::produce(&formalTypeNodes);

	const DataType * retType = this->getRetTypeNode()->getType();
	FnType * dataType = FnType::produce(formalTypes, retType);
	//Make sure the fnSymbol is in the symbol table before
	// analyzing the body, to allow for recursive calls
	if (validName){
		atFnScope->addFn(fnName, dataType);
		SemSymbol * sym = atFnScope->lookup(fnName);
		this->myID->attachSymbol(sym);
	}

	bool validBody = true;
	for (auto stmt : *myBody){
		validBody = stmt->nameAnalysis(symTab) && validBody;
	}

	symTab->leaveScope();
	return (validRet && validFormals && validName && validBody);
}

bool BinaryExpNode::nameAnalysis(SymbolTable * symTab){
	bool resultLHS = myExp1->nameAnalysis(symTab);
	bool resultRHS = myExp2->nameAnalysis(symTab);
	return resultLHS && resultRHS;
}

bool CallExpNode::nameAnalysis(SymbolTable* symTab){
	bool result = true;
	result = myCallee->nameAnalysis(symTab) && result;
	for (auto arg : *myArgs){
		result = arg->nameAnalysis(symTab) && result;
	}
	return result;
}

bool NegNode::nameAnalysis(SymbolTable* symTab){
	return myExp->nameAnalysis(symTab);
}


bool NotNode::nameAnalysis(SymbolTable* symTab){
	return myExp->nameAnalysis(symTab);
}

bool ReturnStmtNode::nameAnalysis(SymbolTable * symTab){
	if (myExp == nullptr){ // May happen in void functions
		return true;
	}
	return myExp->nameAnalysis(symTab);
}

bool MaybeStmtNode::nameAnalysis(SymbolTable* symTab){
	bool res = true;
	res = myDst->nameAnalysis(symTab) && res;
	res = mySrc1->nameAnalysis(symTab) && res;
	res = mySrc2->nameAnalysis(symTab) && res;
	return res;
}

bool CallStmtNode::nameAnalysis(SymbolTable* symTab){
	return myCallExp->nameAnalysis(symTab);
}

bool TypeNode::nameAnalysis(SymbolTable * symTab){
	return true;
}

bool IntLitNode::nameAnalysis(SymbolTable * symTab){
	return true;
}

bool StrLitNode::nameAnalysis(SymbolTable * symTab){
	return true;
}

bool TrueNode::nameAnalysis(SymbolTable * symTab){
	return true;
}

bool FalseNode::nameAnalysis(SymbolTable * symTab){
	return true;
}

bool IDNode::nameAnalysis(SymbolTable* symTab){
	std::string myName = this->getName();
	SemSymbol * sym = symTab->find(myName);
	if (sym == nullptr){
		return NameErr::undeclID(pos());
	}
	this->attachSymbol(sym);
	return true;
}

void LocNode::attachSymbol(SemSymbol * symbolIn){
	this->mySymbol = symbolIn;
}

}
