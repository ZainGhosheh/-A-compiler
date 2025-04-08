#include "ast.hpp"
#include "errors.hpp"

namespace a_lang{

static void doIndent(std::ostream& out, int indent){
	for (int k = 0 ; k < indent; k++){ out << "    "; }
}

void ProgramNode::unparse(std::ostream& out, int indent){
	for (DeclNode * decl : *myGlobals){
		decl->unparse(out, indent);
	}
}

void VarDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent); 
	myID->unparse(out, 0);
	out << " : ";
	myType->unparse(out, 0);
	if (myInit != nullptr){
		out << " = ";
		myInit->unparse(out, 0);
	}
	out << ";\n";
}

void FormalDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent); 
	ID()->unparse(out, 0);
	out << " : ";
	getTypeNode()->unparse(out, 0);
}

void FnDeclNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent); 
	myID->unparse(out, 0);
	out << " : ";
	out << "(";
	bool firstFormal = true;
	for(auto formal : *myFormals){
		if (firstFormal) { firstFormal = false; }
		else { out << ", "; }
		formal->unparse(out, 0);
	}
	out << ") -> ";
	myRetType->unparse(out, 0); 
	out << " {\n";
	for(auto stmt : *myBody){
		stmt->unparse(out, indent+1);
	}
	doIndent(out, indent);
	out << "}\n";
}

void AssignStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myDst->unparse(out, 0);
	out << " = ";
	mySrc->unparse(out, 0);
	out << ";\n";
}

void FromConsoleStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "fromconsole ";
	myDst->unparse(out,0);
	out << ";\n";
}

void ToConsoleStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "toconsole ";
	mySrc->unparse(out,0);
	out << ";\n";
}

void PostIncStmtNode::unparse(std::ostream& out, int indent){
	if (indent != -1){ doIndent(out, indent); }
	
	this->myLoc->unparse(out,0);
	out << "++";

	if (indent != -1){ out << ";\n"; }
}

void PostDecStmtNode::unparse(std::ostream& out, int indent){
	if (indent != -1){ doIndent(out, indent); }
	this->myLoc->unparse(out,0);
	out << "--";
	if (indent != -1){ out << ";\n"; }
}

void IfStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "if (";
	myCond->unparse(out, 0);
	out << "){\n";
	for (auto stmt : *myBody){
		stmt->unparse(out, indent + 1);
	}
	doIndent(out, indent);
	out << "}\n";
}

void IfElseStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "if (";
	myCond->unparse(out, 0);
	out << "){\n";
	for (auto stmt : *myBodyTrue){
		stmt->unparse(out, indent + 1);
	}
	doIndent(out, indent);
	out << "} else {\n";
	for (auto stmt : *myBodyFalse){
		stmt->unparse(out, indent + 1);
	}
	doIndent(out, indent);
	out << "}\n";
}

void WhileStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "while (";
	myCond->unparse(out, 0);
	out << "){\n";
	for (auto stmt : *myBody){
		stmt->unparse(out, indent + 1);
	}
	doIndent(out, indent);
	out << "}\n";
}

void ReturnStmtNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "return";
	if (myExp != nullptr){
		out << " ";
		myExp->unparse(out, 0);
	}
	out << ";\n";
}

void MaybeStmtNode::unparse(std::ostream& out, int indent){
	if (indent != -1){ doIndent(out, indent); }
	out << "maybe ";
	myDst->unparse(out, 0);
	out << " means ";
	mySrc1->unparse(out, 0);
	out << " otherwise ";
	mySrc2->unparse(out, 0);
	if (indent != -1){ out << ";\n"; }
}

void CallStmtNode::unparse(std::ostream& out, int indent){
	if (indent != -1){ doIndent(out, indent); }
	myCallExp->unparse(out, 0);
	if (indent != -1){ out << ";\n"; }
}

void ExpNode::unparseNested(std::ostream& out){
	out << "(";
	unparse(out, 0);
	out << ")";
}

void CallExpNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myCallee->unparse(out, 0);
	out << "(";
	
	bool firstArg = true;
	for(auto arg : *myArgs){
		if (firstArg) { firstArg = false; }
		else { out << ", "; }
		arg->unparse(out, 0);
	}
	out << ")";
}
void CallExpNode::unparseNested(std::ostream& out){
	unparse(out, 0);
}

void MinusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " - ";
	myExp2->unparseNested(out);
}

void PlusNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " + ";
	myExp2->unparseNested(out);
}

void TimesNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " * ";
	myExp2->unparseNested(out);
}

void DivideNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " / ";
	myExp2->unparseNested(out);
}

void AndNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " and ";
	myExp2->unparseNested(out);
}

void OrNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " or ";
	myExp2->unparseNested(out);
}

void EqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " == ";
	myExp2->unparseNested(out);
}

void NotEqualsNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " != ";
	myExp2->unparseNested(out);
}

void GreaterNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " > ";
	myExp2->unparseNested(out);
}

void GreaterEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " >= ";
	myExp2->unparseNested(out);
}

void LessNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " < ";
	myExp2->unparseNested(out);
}

void LessEqNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	myExp1->unparseNested(out); 
	out << " <= ";
	myExp2->unparseNested(out);
}

void NotNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "!";
	myExp->unparseNested(out); 
}

void NegNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "-";
	myExp->unparseNested(out); 
}

void ImmutableTypeNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "immutable ";
	mySub->unparse(out, 0);
}

void VoidTypeNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "void";
}

void IntTypeNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "int";
}

void BoolTypeNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "bool";
}

void IDNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << name;

	if (const SemSymbol * sym = getSymbol()){
		out << "{"
		  << sym->getDataType()->getString()
		  << "}";
	}
}

void IDNode::unparseNested(std::ostream& out){
	this->unparse(out, 0);
}

void FalseNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "false";
}

void EhNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "eh?";
}

void IntLitNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << myNum;
}

void StrLitNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << myStr;
}

void TrueNode::unparse(std::ostream& out, int indent){
	doIndent(out, indent);
	out << "true";
}

} //End namespace a_lang
