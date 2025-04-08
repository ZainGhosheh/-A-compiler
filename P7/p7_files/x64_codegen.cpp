#include <ostream>
#include "3ac.hpp"

namespace a_lang{

void IRProgram::allocGlobals(){
	//Choose a label for each global
	TODO(Implement me)
}

void IRProgram::datagenX64(std::ostream& out){
	TODO(Write out data section)
	//Put this directive after you write out strings
	// so that everything is aligned to a quadword value
	// again
	out << ".align 8\n";

}

void IRProgram::toX64(std::ostream& out){
	allocGlobals();
	datagenX64(out);
	// Iterate over each procedure and codegen it
	TODO(Implement me)
}

void Procedure::allocLocals(){
	//Allocate space for locals
	// Iterate over each procedure and codegen it
	TODO(Implement me)
}

void Procedure::toX64(std::ostream& out){
	//Allocate all locals
	allocLocals();

	enter->codegenLabels(out);
	enter->codegenX64(out);
	out << "#Fn body " << myName << "\n";
	for (auto quad : *bodyQuads){
		quad->codegenLabels(out);
		out << "#" << quad->toString() << "\n";
		quad->codegenX64(out);
	}
	out << "#Fn epilogue " << myName << "\n";
	leave->codegenLabels(out);
	leave->codegenX64(out);
}

void Quad::codegenLabels(std::ostream& out){
	if (labels.empty()){ return; }

	size_t numLabels = labels.size();
	size_t labelIdx = 0;
	for ( Label * label : labels){
		out << label->getName() << ": ";
		if (labelIdx != numLabels - 1){ out << "\n"; }
		labelIdx++;
	}
}

void BinOpQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void UnaryOpQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void AssignQuad::codegenX64(std::ostream& out){
	src->genLoadVal(out, A);
	dst->genStoreVal(out, A);
}

void ReadQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void WriteQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void GotoQuad::codegenX64(std::ostream& out){
	out << "jmp " << tgt->getName() << "\n";
}

void IfzQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void NopQuad::codegenX64(std::ostream& out){
	out << "nop" << "\n";
}

void CallQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void EnterQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void LeaveQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void SetArgQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void GetArgQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void SetRetQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void GetRetQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void LocQuad::codegenX64(std::ostream& out){
	TODO(Implement me)
}

void SymOpd::genLoadVal(std::ostream& out, Register reg){
	TODO(Implement me)
}

void SymOpd::genStoreVal(std::ostream& out, Register reg){
	TODO(Implement me)
}

void SymOpd::genLoadAddr(std::ostream& out, Register reg) {
	TODO(Implement me if necessary)
}

void AuxOpd::genLoadVal(std::ostream& out, Register reg){
	TODO(Implement me)
}

void AuxOpd::genStoreVal(std::ostream& out, Register reg){
	TODO(Implement me)
}
void AuxOpd::genLoadAddr(std::ostream& out, Register reg){
	TODO(Implement me)
}


void AddrOpd::genStoreVal(std::ostream& out, Register reg){
	TODO(Implement me)
}

void AddrOpd::genLoadVal(std::ostream& out, Register reg){
	TODO(Implement me)
}

void AddrOpd::genStoreAddr(std::ostream& out, Register reg){
	TODO(Implement me)
}

void AddrOpd::genLoadAddr(std::ostream & out, Register reg){
	TODO(Implement me)
}

void LitOpd::genLoadVal(std::ostream & out, Register reg){
	out << getMovOp() << " $" << val << ", " << getReg(reg) << "\n";
}

}
