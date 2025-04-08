#include "ast.hpp"
#include "3ac.hpp"


namespace a_lang{

IRProgram * ProgramNode::to3AC(TypeAnalysis * ta){
	IRProgram * prog = new IRProgram(ta);
	for (auto global : *myGlobals){
		global->to3AC(prog);
	}
	return prog;
}

void FnDeclNode::to3AC(IRProgram * prog){
	Procedure * proc = prog->makeProc(myID->getName());
	size_t i = 0;
	for (auto formal : *myFormals){
		formal->to3AC(proc);
		proc->addQuad(new GetArgQuad(i+1, proc->getFormal(i)));
		i++;
	}
	for (auto stmt : *myBody){
		stmt->to3AC(proc);
	}

	SemSymbol * sym = myID->getSymbol();
	assert(sym != nullptr);
	prog->gatherGlobal(sym);
}


void FnDeclNode::to3AC(Procedure * proc){
	throw new InternalError("FnDecl at a local scope");
}

void FormalDeclNode::to3AC(IRProgram * prog){
	throw new InternalError("Formal at a global scope");
}

void FormalDeclNode::to3AC(Procedure * proc){
    SemSymbol * sym = ID()->getSymbol();
    assert(sym != nullptr);
    proc->gatherFormal(sym);
}

Opd * IntLitNode::flatten(Procedure * proc){
	const DataType * type = proc->getProg()->nodeType(this);
	return new LitOpd(std::to_string(myNum), 8);
}

Opd * StrLitNode::flatten(Procedure * proc){
	Opd * res = proc->getProg()->makeString(myStr);
	return res;
}

Opd * TrueNode::flatten(Procedure * proc){
	const DataType * type = proc->getProg()->nodeType(this);
	return new LitOpd("1", 8);
}

Opd * FalseNode::flatten(Procedure * proc){
	const DataType * type = proc->getProg()->nodeType(this);
	return new LitOpd("0", 8);
}

Opd * EhNode::flatten(Procedure * proc){

	Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));
	FnType * fnType = FnType::produce(nullptr, BasicType::BOOL());
	SemSymbol * sym = new FnSymbol("randBool", fnType);
	proc->addQuad(new CallQuad(sym));

	proc->addQuad(new GetRetQuad(dst));
	return dst;
}


Opd * CallExpNode::flatten(Procedure * proc){
    bool assign = false;
	auto * callee = myCallee->flatten(proc);
	size_t i = 1;
	for (auto arg : *myArgs){
		Opd * src = arg->flatten(proc);
		proc->addQuad(new SetArgQuad(i++, src));
	}
	proc->addQuad(new CallQuad(myCallee->getSymbol()));
	if (getRetType() != nullptr && getRetType()->isVoid()){
		return callee;
	}
	auto * tmp = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));
	if (assign) {
		proc->addQuad(new GetRetQuad(tmp));
		return tmp;
	}
	return callee;
}


Opd * NegNode::flatten(Procedure * proc){
	Opd * src = myExp->flatten(proc);
	Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));
	proc->addQuad(new UnaryOpQuad(dst, UnaryOp::NEG64, src));
	return dst;
}

Opd * NotNode::flatten(Procedure * proc){
	Opd * src = myExp->flatten(proc);
	Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));
	proc->addQuad(new UnaryOpQuad(dst, UnaryOp::NOT64, src));
	return dst;
}

Opd * PlusNode::flatten(Procedure * proc) {
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::ADD64, lhs, rhs));  
    return dst;
}

Opd * MinusNode::flatten(Procedure * proc){
	Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::SUB64, lhs, rhs));  
    return dst;
}

Opd * TimesNode::flatten(Procedure * proc){
	Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::MULT64, lhs, rhs));  
    return dst;
}

Opd * DivideNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::DIV64, lhs, rhs));  
    return dst;
}

Opd * AndNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::AND64, lhs, rhs));  
    return dst;
}

Opd * OrNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::OR64, lhs, rhs));  
    return dst;
}

Opd * EqualsNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::EQ64, lhs, rhs));  
    return dst;
}

Opd * NotEqualsNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::NEQ64, lhs, rhs));  
    return dst;
}

Opd * LessNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::LT64, lhs, rhs));  
    return dst;
}

Opd * GreaterNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::GT64, lhs, rhs));  
    return dst;
}

Opd * LessEqNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::LTE64, lhs, rhs));  
    return dst;
}

Opd * GreaterEqNode::flatten(Procedure * proc){
    Opd * lhs = myExp1->flatten(proc);  
    Opd * rhs = myExp2->flatten(proc);  
    Opd * dst = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));  
    proc->addQuad(new BinOpQuad(dst, BinOp::GTE64, lhs, rhs));  
    return dst;
}

void AssignStmtNode::to3AC(Procedure * proc){
	Opd * src = mySrc->flatten(proc);
	Opd * dst = myDst->flatten(proc);
	proc->addQuad(new AssignQuad(dst, src));
}

void MaybeStmtNode::to3AC(Procedure * proc){
	Opd * dst = myDst->flatten(proc);
	Opd * src1 = mySrc1->flatten(proc);
	Opd * src2 = mySrc2->flatten(proc);

	Opd * tmp = proc->makeTmp(Opd::width(proc->getProg()->nodeType(this)));

	FnType * fnType = FnType::produce(nullptr, BasicType::BOOL());
	SemSymbol * sym = new FnSymbol("randBool", fnType);
	proc->addQuad(new CallQuad(sym));

	proc->addQuad(new GetRetQuad(tmp));

	Label * tgt = proc->getProg()->makeLabel();
	auto * ifzQuad = new IfzQuad(tmp, tgt);
	proc->addQuad(ifzQuad);

	Quad * quad = new AssignQuad(dst, src1);
	proc->addQuad(quad);

	Label * tgt2 = proc->getProg()->makeLabel();
	auto * gotoQuad = new GotoQuad(tgt2);
	proc->addQuad(gotoQuad);

	auto * nopQuad = new NopQuad();
	nopQuad->addLabel(tgt);
	proc->addQuad(nopQuad);

	quad = new AssignQuad(dst, src2);
	proc->addQuad(quad);

	nopQuad = new NopQuad();
	nopQuad->addLabel(tgt2);
	proc->addQuad(nopQuad);
}




void PostIncStmtNode::to3AC(Procedure * proc){
	Opd * opd = myLoc->flatten(proc);
	proc->addQuad(new BinOpQuad(opd, BinOp::ADD64, opd, new LitOpd("1", 8)));
}

void PostDecStmtNode::to3AC(Procedure * proc){
	Opd * opd = myLoc->flatten(proc);
	proc->addQuad(new BinOpQuad(opd, BinOp::SUB64, opd, new LitOpd("1", 8)));
}

void ToConsoleStmtNode::to3AC(Procedure * proc){
	Opd * src = mySrc->flatten(proc);
    proc->addQuad(new WriteQuad(src, proc->getProg()->nodeType(mySrc)));
}

void FromConsoleStmtNode::to3AC(Procedure * proc){
	Opd * dst = myDst->flatten(proc);
    proc->addQuad(new ReadQuad(dst, proc->getProg()->nodeType(myDst)));
}

void IfStmtNode::to3AC(Procedure * proc){
	Opd * cond = myCond->flatten(proc);
	Label * label1 = proc->getProg()->makeLabel();
	auto * ifzQuad = new IfzQuad(cond, label1);
	proc->addQuad(ifzQuad);
	for (auto stmt : *myBody){
		stmt->to3AC(proc);
	}

	auto * nopQuad = new NopQuad();
	nopQuad->addLabel(label1);
	proc->addQuad(nopQuad);
}

void IfElseStmtNode::to3AC(Procedure * proc){
	Opd * cond = myCond->flatten(proc);
	Label * label1 = proc->getProg()->makeLabel();
	Label * label2 = proc->getProg()->makeLabel();
	proc->addQuad(new IfzQuad(cond, label1));
	for (auto stmt : *myBodyTrue){
		stmt->to3AC(proc);
	}


	proc->addQuad(new GotoQuad(label2));


	auto * nopQuad = new NopQuad();
	nopQuad->addLabel(label1);
	proc->addQuad(nopQuad);


	for (auto stmt : *myBodyFalse){
		stmt->to3AC(proc);
	}

	auto * nopQuad2 = new NopQuad();
	nopQuad2->addLabel(label2);
	proc->addQuad(nopQuad2);
}


void WhileStmtNode::to3AC(Procedure * proc){
	Opd * cond = myCond->flatten(proc);
	Label * label1 = proc->getProg()->makeLabel(); 
	Label * label2 = proc->getProg()->makeLabel(); 

	auto * nopQuad = new NopQuad(); 
	nopQuad->addLabel(label1);
	proc->addQuad(nopQuad);

	proc->addQuad(new IfzQuad(cond, label2)); 
	for (auto stmt : *myBody){
		stmt->to3AC(proc);
	}
	proc->addQuad(new GotoQuad(label1));
	nopQuad = new NopQuad(); 
	nopQuad->addLabel(label2);
	proc->addQuad(nopQuad);
}
void CallStmtNode::to3AC(Procedure * proc){
	myCallExp->flatten(proc);
}

void ReturnStmtNode::to3AC(Procedure * proc){
	if (myExp == nullptr){
		proc->addQuad(new GotoQuad(proc->getLeaveLabel()));
		return;
	}
	Opd * exp = myExp->flatten(proc);
	proc->addQuad(new SetRetQuad(exp));
	proc->addQuad(new GotoQuad(proc->getLeaveLabel()));
}


void VarDeclNode::to3AC(Procedure * proc){
	SemSymbol * sym = ID()->getSymbol();
	assert(sym != nullptr);
	proc->gatherLocal(sym);
    if (myInit != nullptr) {
        Opd * initOpd = myInit->flatten(proc);
        Opd * targetOpd = proc->getSymOpd(sym);
        proc->addQuad(new AssignQuad(targetOpd, initOpd));
    }
}

void VarDeclNode::to3AC(IRProgram * prog){
	SemSymbol * sym = ID()->getSymbol();
	assert(sym != nullptr);
	prog->gatherGlobal(sym);
	if (myInit != nullptr) {

        Opd * initValue = myInit->flatten(prog->initProc());
        assert(initValue && "Failed to flatten initializer expression");

        Opd * globalOpd = prog->getGlobal(sym);
        assert(globalOpd && "Global operand must not be null");
        prog->initProc()->addQuad(new AssignQuad(globalOpd, initValue));
    }
}

Opd * IDNode::flatten(Procedure * proc){
    SemSymbol * sym = getSymbol();
    assert(sym != nullptr); 
    return proc->getSymOpd(sym);
}

}
