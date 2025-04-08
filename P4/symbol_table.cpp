#include "symbol_table.hpp"
namespace a_lang {

ScopeTable::ScopeTable(){
	symbols = new HashMap<std::string, SemSymbol *>();
}

SymbolTable::SymbolTable(){
	//TODO: implement the list of hashtables approach
	// to building a symbol table:
	// Upon entry to a scope a new scope table will be 
	// entered into the front of the chain and upon exit the 
	// latest scope table will be removed from the front of 
	// the chain.
	scopeTableChain = new std::list<ScopeTable *>();
	scopeTableChain->push_front(new ScopeTable()); // add the global scope
}

bool ScopeTable::doesSymbolExist(std::string name) {
	if (symbols->find(name) == symbols->end()){
		return false;
	}
	return true;
}

SemSymbol * ScopeTable::getSymbol(std::string name) {
	if (!doesSymbolExist(name)){
		return nullptr;
	}
	return symbols->at(name);
}

void ScopeTable::addSymbol(std::string name, SemSymbol * symbol) {
	symbols->insert(std::make_pair(name, symbol));
}

ScopeTable * SymbolTable::enterScope(){
	ScopeTable * newScope = new ScopeTable();
	scopeTableChain->push_front(newScope);
	return newScope;
}

ScopeTable * SymbolTable::exitScope(){
	ScopeTable * oldScope = scopeTableChain->front();
	scopeTableChain->pop_front();
	return oldScope;
}

ScopeTable * SymbolTable::currentScope(){
	return scopeTableChain->front();
}

SemSymbol * SymbolTable::findFirstSymbol(std::string name){
	for (auto scope : *scopeTableChain){
		if (scope->doesSymbolExist(name))
		{
			return scope->getSymbol(name);
		}
	}
	return nullptr;
}
}
