#ifndef A_LANG_SYMBOL_TABLE_HPP
#define A_LANG_SYMBOL_TABLE_HPP
#include <string>
#include <unordered_map>
#include <list>
#include "ast.hpp"

//Use an alias template so that we can use
// "HashMap" and it means "std::unordered_map"
template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

using namespace std;

namespace a_lang {

//A semantic symbol, which represents a single
// variable, function, etc. Semantic symbols 
// exist for the lifetime of a scope in the 
// symbol table. 
class SemSymbol {
	//TODO add the fields that 
	// each semantic symbol should track
	// (i.e. the kind of the symbol (either a variable or function)
	// and functions to get/set those fields
public:
	SemSymbol(std::string name, DeclNode * kind, std::string type) {
		this->name = name;
		this->kind = kind;
		this->type = type;
	}

	std::string name;
	DeclNode * kind;
	std::string type;
};

//A single scope. The symbol table is broken down into a 
// chain of scope tables, and each scope table holds 
// semantic symbols for a single scope. For example,
// the globals scope will be represented by a ScopeTable,
// and the contents of each function can be represented by
// a ScopeTable.
class ScopeTable {
	public:
		ScopeTable();
		//TODO: add functions for looking up symbols
		// and/or returning information to indicate
		// that the symbol does not exist within the
		// current scope.
		bool doesSymbolExist(std::string name);
		SemSymbol * getSymbol(std::string name);
		void addSymbol(std::string name, SemSymbol * symbol);
		void printSymbols();

	private:
		HashMap<std::string, SemSymbol *> * symbols;
};

class SymbolTable{
	public:
		SymbolTable();
		// TODO: add functions to create a new ScopeTable
		// when a new scope is entered, drop a ScopeTable
		// when a scope is exited, etc.
		ScopeTable * enterScope();
		ScopeTable * exitScope();
		ScopeTable * currentScope();

		SemSymbol * findFirstSymbol(std::string name);
		// SemSymbol * findClassSymbol(std::string type);

	private:
		std::list<ScopeTable *> * scopeTableChain;
};
}

#endif
