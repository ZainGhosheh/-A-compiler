#include "ast.hpp"
#include "symbol_table.hpp"
#include "errors.hpp"

namespace a_lang{
// TODO CHECK TYPES IF VALID
// inside reftype
// inside classtype

static bool checkType(TypeNode * type, Position const * pos, SymbolTable * symTab){
	bool nameAnalysisOk = true;
	if (dynamic_cast<VoidTypeNode*>(type) != nullptr) // check invalid type
	{
		Report::fatal(pos, "Invalid type in declaration");
		nameAnalysisOk = false;
	}
	else if (dynamic_cast<ImmutableTypeNode *>(type) != nullptr)
	{
		ImmutableTypeNode * immutable = dynamic_cast<ImmutableTypeNode *>(type);
		nameAnalysisOk = checkType(immutable->getSub(), pos, symTab);
	}
	else if (dynamic_cast<RefTypeNode *>(type) != nullptr)
	{
		RefTypeNode * reftype = dynamic_cast<RefTypeNode *>(type);
		nameAnalysisOk = checkType(reftype->getSub(), pos, symTab);
	}
	return nameAnalysisOk;
}

bool ASTNode::nameAnalysis(SymbolTable * symTab){
	throw new ToDoError("This function should have"
		"been overriden in the subclass!");
}

bool ProgramNode::nameAnalysis(SymbolTable * symTab){
	bool res = true;
	for (auto global : *myGlobals){
		res = global->nameAnalysis(symTab) && res;
	}
	return res;
}

bool VarDeclNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	// Add the variable to the symbol table
	// if it doesn't already exist
	auto * curScope = symTab->currentScope();
	if (curScope->doesSymbolExist(ID()->getName())){
//   		if (myType && !myType->nameAnalysis(symTab))
//		{
//		}
//  		else
//  		{
		Report::fatal(ID()->pos(), "Multiply declared identifier");
		nameAnalysisOk = false;
//  		}
	} else {
		std::stringstream type;
		getTypeNode()->unparse(type, 0);
		curScope->addSymbol(ID()->getName(), new SemSymbol(ID()->getName(), this, type.str()));
		ID()->attachSymbol(curScope->getSymbol(ID()->getName()));
	}

	if (myType){
		nameAnalysisOk = myType->nameAnalysis(symTab) && nameAnalysisOk;
		nameAnalysisOk = nameAnalysisOk && checkType(getTypeNode(), ID()->pos(), symTab);
	}
	if (myInit){
		nameAnalysisOk = myInit->nameAnalysis(symTab) && nameAnalysisOk;
	}

// 	Report::fatal(ID()->pos(), "here");

	return nameAnalysisOk;
}

bool FnDeclNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	auto * curScope = symTab->currentScope(); // get the current scope
	if (curScope->doesSymbolExist(ID()->getName())){ // check if the function already exists in this scope
		Report::fatal(ID()->pos(), "Multiply declared identifier");
		nameAnalysisOk = false;

		// even if we hit an error, still analyze the formals and body
		curScope = symTab->enterScope();
		for (auto formal : *myFormals){
			nameAnalysisOk = formal->nameAnalysis(symTab) && nameAnalysisOk;
		}
		for (auto stmt : *myBody){
			nameAnalysisOk = stmt->nameAnalysis(symTab) && nameAnalysisOk;
		}
		symTab->exitScope();
	} else {
		curScope = symTab->enterScope();

		std::stringstream type;
		type << "(";
		for (auto formal : *myFormals){
			formal->getTypeNode()->unparse(type, 0);
			if (formal != myFormals->back()){
				type << ", ";
			}
		}
		type << ")";
		type << "->";
		myRetType->unparse(type, 0);
		curScope->addSymbol(ID()->getName(), new SemSymbol(ID()->getName(), this, type.str()));
		ID()->attachSymbol(curScope->getSymbol(ID()->getName()));

		for (auto formal : *myFormals){
			nameAnalysisOk = formal->nameAnalysis(symTab) && nameAnalysisOk;
		}
		for (auto stmt : *myBody){
			nameAnalysisOk = stmt->nameAnalysis(symTab) && nameAnalysisOk;
		}

		symTab->exitScope();

		curScope = symTab->currentScope();
		curScope->addSymbol(ID()->getName(), new SemSymbol(ID()->getName(), this, type.str()));
	}

	return nameAnalysisOk;
}

bool FormalDeclNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	// Add the variable to the symbol table
	// if it doesn't already exist
	auto * curScope = symTab->currentScope();
	if (curScope->doesSymbolExist(ID()->getName())){
		Report::fatal(ID()->pos(), "Multiply declared identifier");
		nameAnalysisOk = false;
	}
	else {
		std::stringstream type;
		getTypeNode()->unparse(type, 0);
		nameAnalysisOk = nameAnalysisOk && getTypeNode()->nameAnalysis(symTab);
		nameAnalysisOk = nameAnalysisOk && checkType(getTypeNode(), ID()->pos(), symTab);
		curScope->addSymbol(ID()->getName(), new SemSymbol(ID()->getName(), this, type.str()));
		ID()->attachSymbol(curScope->getSymbol(ID()->getName()));
	}

	return nameAnalysisOk;
}

bool StmtNode::nameAnalysis(SymbolTable * symTab){
	throw new ToDoError("This function should have"
		"been overriden in the subclass!");
}

bool ExpNode::nameAnalysis(SymbolTable * symTab){
	throw new ToDoError("This function should have"
		"been overriden in the subclass!");
}

bool DeclNode::nameAnalysis(SymbolTable * symTab){
	throw new ToDoError("This function should have"
		"been overriden in the subclass!");
}

bool ClassDefnNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	auto * curScope = symTab->currentScope(); // global scope
	if (curScope->doesSymbolExist(ID()->getName())){
		Report::fatal(pos(), "Multiply declared identifier");
		nameAnalysisOk = false;

		curScope = symTab->enterScope();
		for (auto member : *myMembers){
			nameAnalysisOk = member->nameAnalysis(symTab) && nameAnalysisOk;
		}
		symTab->exitScope();
	} else {
		curScope = symTab->enterScope();
		curScope->addSymbol(ID()->getName(), new SemSymbol(ID()->getName(), this, ID()->getName()));
		ID()->attachSymbol(curScope->getSymbol(ID()->getName()));

		for (auto member : *myMembers){
			nameAnalysisOk = member->nameAnalysis(symTab) && nameAnalysisOk;
		}

		symTab->exitScope();
	}

	if (nameAnalysisOk)
	{
		// add to global scope
		curScope = symTab->currentScope();
		curScope->addSymbol(ID()->getName(), new SemSymbol(ID()->getName(), this, ID()->getName()));
	}

	return nameAnalysisOk;
}

bool AssignStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = myDst->nameAnalysis(symTab) && nameAnalysisOk;
	nameAnalysisOk = mySrc->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool MaybeStmtNode::nameAnalysis(SymbolTable * symTab){
 	throw new ToDoError("implement me");
	return true;
}

bool FromConsoleStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = myDst->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool ToConsoleStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = mySrc->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool PostDecStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = myLoc->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool PostIncStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = myLoc->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool IfStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	// check if cond is in scope
	nameAnalysisOk = nameAnalysisOk && myCond->nameAnalysis(symTab);
	// enter new scope
	auto * curScope = symTab->enterScope();
	for (auto stmt : *myBody){
		nameAnalysisOk = stmt->nameAnalysis(symTab) && nameAnalysisOk;
	}

	// exit scope
	symTab->exitScope();

	return nameAnalysisOk;
}

bool IfElseStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	// check if cond is in scope
	nameAnalysisOk = nameAnalysisOk && myCond->nameAnalysis(symTab);

	// enter new scope for true body
	auto * curScope = symTab->enterScope();
	for (auto stmt : *myBodyTrue){
		nameAnalysisOk = stmt->nameAnalysis(symTab) && nameAnalysisOk;
	}

	// exit scope
	symTab->exitScope();

	// enter new scope for false body
	curScope = symTab->enterScope();
	for (auto stmt : *myBodyFalse){
		nameAnalysisOk = stmt->nameAnalysis(symTab) && nameAnalysisOk;
	}

	// exit scope
	symTab->exitScope();

	return nameAnalysisOk;
}

bool WhileStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	// check if cond is in scope
	nameAnalysisOk = myCond->nameAnalysis(symTab);


	// enter new scope
	auto * curScope = symTab->enterScope();
	for (auto stmt : *myBody){
		nameAnalysisOk = stmt->nameAnalysis(symTab) && nameAnalysisOk;
	}

	// exit scope
	symTab->exitScope();

	return nameAnalysisOk;
}

bool ReturnStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	if (myExp){
		nameAnalysisOk = myExp->nameAnalysis(symTab) && nameAnalysisOk;
	}

	return nameAnalysisOk;
}

bool CallStmtNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	auto * callExp = myCallExp;

	std::stringstream up;
	callExp->unparse(up, 0);
	auto f = up.str().find_first_of("(");
	if (f != std::string::npos){
		auto fnName = up.str().substr(0, f);
		if (symTab->findFirstSymbol(fnName)){
			auto * fn = symTab->findFirstSymbol(fnName);
			nameAnalysisOk = callExp->getCallee()->nameAnalysis(symTab) && nameAnalysisOk;

			for (auto arg : *callExp->getArgs()){
				nameAnalysisOk = arg->nameAnalysis(symTab) && nameAnalysisOk;
			}
		}
		else
		{
			Report::fatal(callExp->pos(), "Undeclared identifier");
			nameAnalysisOk = false;
		}
	}

	return nameAnalysisOk;
}

bool VoidTypeNode::nameAnalysis(SymbolTable * symTab){
	// Name analysis may never even recurse down to VoidTypeNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool ClassTypeNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	if (symTab->findFirstSymbol(myID->getName())){
		auto * classSym = symTab->findFirstSymbol(myID->getName());
		myID->attachSymbol(classSym);
	}
	else
	{
		Report::fatal(myID->pos(), "Invalid type in declaration");
		nameAnalysisOk = false;
	}

	nameAnalysisOk = nameAnalysisOk && myID->nameAnalysis(symTab);

	return nameAnalysisOk;
}

// TODO REFS

bool ImmutableTypeNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = mySub->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool RefTypeNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = mySub->nameAnalysis(symTab) && nameAnalysisOk;
 	nameAnalysisOk = checkType(mySub, mySub->pos(), symTab);
	if (dynamic_cast<ClassTypeNode *>(mySub) != nullptr)
	{
		ClassTypeNode * classType = dynamic_cast<ClassTypeNode *>(mySub);
	   	auto baseName = classType->getID()->getName();
  		// check if ID exists first
  		auto * baseSym = symTab->currentScope()->getSymbol(baseName);
  		if (baseSym)
	  	{
//	    	Report::fatal(mySub->pos(), "Multiply declared identifier");
	  	}
	   	// check if class exists
	   	baseSym = symTab->findFirstSymbol(baseName);
	   	auto * classSym = symTab->findFirstSymbol(baseSym->type);
	   	if (!(classSym && classSym->type == classSym->name))
		{
			Report::fatal(mySub->pos(), "Invalid type in declaration");
	   	}
 	}

	return nameAnalysisOk;
}

bool BoolTypeNode::nameAnalysis(SymbolTable * symTab){
	// Name analysis may never even recurse down to BoolTypeNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool IntTypeNode::nameAnalysis(SymbolTable* symTab){
	// Name analysis may never even recurse down to IntTypeNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool LocNode::nameAnalysis(SymbolTable * symTab)
{
	throw new ToDoError("This function should have"
		"been overriden in the subclass!");
}

bool IDNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;

	if (symTab->findFirstSymbol(getName())){
		auto * argSym = symTab->findFirstSymbol(getName());
		attachSymbol(argSym);
	}
	else
	{
		Report::fatal(pos(), "Undeclared identifier");
		nameAnalysisOk = false;
	}

	return nameAnalysisOk;
}

bool MemberFieldExpNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = myBase->nameAnalysis(symTab) && nameAnalysisOk;
	bool baseFound = false;

	// find my base's type in the symbol table
	if (nameAnalysisOk){
		auto fieldName = myField->getName();
		// get the symbol for the base
		auto baseName = myBase->getName();
		if (symTab->findFirstSymbol(baseName)){
			auto * baseSym = symTab->findFirstSymbol(baseName);
			auto * classSym = symTab->findFirstSymbol(baseSym->type);
			if (classSym && classSym->type == classSym->name)
			{
				if (dynamic_cast<ClassDefnNode *>(classSym->kind))
				{
					auto * classDefn = dynamic_cast<ClassDefnNode *>(classSym->kind);
					for (auto member : *classDefn->getMembers())
					{
						if (dynamic_cast<VarDeclNode *>(member))
						{
							auto * varDecl = dynamic_cast<VarDeclNode *>(member);
							if (varDecl->ID()->getName() == fieldName)
							{
								myField->attachSymbol(varDecl->ID()->getSymbol());
								baseFound = true;
							}
						}
      					else if (dynamic_cast<FnDeclNode *>(member))
        				{
					    	auto * fnDecl = dynamic_cast<FnDeclNode *>(member);
					  		if (fnDecl->ID()->getName() == fieldName)
					  		{
					 			myField->attachSymbol(fnDecl->ID()->getSymbol());
					 			baseFound = true;
					  		}
					    }
					}

					if (!baseFound)
					{
						Report::fatal(myField->pos(), "Undeclared identifier");
					}
				}
			}
			else
			{
				Report::fatal(myBase->pos(), "Undeclared identifier");
			}
		}
	}
	else
	{
		Report::fatal(pos(), "Undeclared identifier");
	}

	nameAnalysisOk = nameAnalysisOk && baseFound;
	return nameAnalysisOk;
}

bool CallExpNode::nameAnalysis(SymbolTable * symTab)
{
	bool nameAnalysisOk = true;

	if (myCallee)
	{
		nameAnalysisOk = myCallee->nameAnalysis(symTab) && nameAnalysisOk;
	}

	for (auto arg : *myArgs)
	{
		nameAnalysisOk = arg->nameAnalysis(symTab) && nameAnalysisOk;
	}

	return nameAnalysisOk;
}

bool BinaryExpNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = myExp1->nameAnalysis(symTab) && nameAnalysisOk;
	nameAnalysisOk = myExp2->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool UnaryExpNode::nameAnalysis(SymbolTable * symTab){
	bool nameAnalysisOk = true;
	nameAnalysisOk = myExp->nameAnalysis(symTab) && nameAnalysisOk;
	return nameAnalysisOk;
}

bool IntLitNode::nameAnalysis(SymbolTable * symTab){
	// Name analysis may never even recurse down to IntLitNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool StrLitNode::nameAnalysis(SymbolTable * symTab){
	// Name analysis may never even recurse down to StrLitNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool TrueNode::nameAnalysis(SymbolTable * symTab){
	// Name analysis may never even recurse down to TrueNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool FalseNode::nameAnalysis(SymbolTable * symTab){
	// Name analysis may never even recurse down to FalseNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}

bool EhNode::nameAnalysis(SymbolTable * symTab){
	// Name analysis may never even recurse down to EhNode,
	// but if it does, just return true to indicate that
	// name analysis has not failed, and add nothing to the symbol table
	return true;
}
}
