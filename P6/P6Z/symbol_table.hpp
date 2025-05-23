#ifndef A_LANG_SYMBOL_TABLE_HPP
#define A_LANG_SYMBOL_TABLE_HPP
#include <string>
#include <unordered_map>
#include <list>
#include "types.hpp"

//Use an alias template so that we can use
// "HashMap" and it means "std::unordered_map"
template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

using ArgsType = std::list<const a_lang::DataType *>;

using namespace std;

namespace a_lang{

enum SymbolKind {
	VAR, FN
};

//A semantic symbol, which represents a single
// variable, function, etc. Semantic symbols
// exist for the lifetime of a scope in the
// symbol table.
class SemSymbol {
public:
	SemSymbol(std::string nameIn, const DataType * typeIn)
	: myName(nameIn), myType(typeIn){ 
		if (myType == nullptr){
			throw new InternalError("symbol with no type");
		}
	}
	virtual std::string toString() const;
	std::string getName() const { return myName; }
	virtual SymbolKind getKind() const = 0;

	virtual const DataType * getDataType() const{
		return myType;
	}
	static std::string kindToString(SymbolKind symKind) {
		switch(symKind){
			case VAR: return "var";
			case FN: return "fn";
		}
		return "UNKNOWN KIND";
	}
protected:
	std::string myName;
	const DataType * myType;
};

class VarSymbol : public SemSymbol {
public:
	VarSymbol(std::string name, const DataType * type)
	: SemSymbol(name, type) { }
	virtual SymbolKind getKind() const override { return VAR; }
};

class FnSymbol : public SemSymbol{
public:
	FnSymbol(std::string name, const FnType * fnType)
	: SemSymbol(name, fnType){ }
	virtual SymbolKind getKind() const { return FN; }
	SymbolKind getKind(){ return FN; }
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
		SemSymbol * lookup(std::string name);
		bool insert(SemSymbol * symbol);
		bool clash(std::string name);
		std::string toString() const;
		void addVar(std::string name, const DataType * type){
			insert(new VarSymbol(name, type));
		}
		FnSymbol * addFn(std::string name, FnType * type){
			FnSymbol * sym = new FnSymbol(name, type);
			insert(sym);
			return sym;
		}
	private:
		HashMap<std::string, SemSymbol *> * symbols;
};

class SymbolTable{
	public:
		SymbolTable();
		ScopeTable * enterScope();
		void leaveScope();
		ScopeTable * getCurrentScope();
		bool insert(SemSymbol * symbol);
		SemSymbol * find(std::string varName);
		bool clash(std::string name);
		void addVar(std::string name, const DataType * type){
			getCurrentScope()->addVar(name, type);
		}
		SemSymbol * addFn(std::string name, FnType * type){
			return getCurrentScope()->addFn(name, type);
		}
		void print();
	private:
		std::list<ScopeTable *> * scopeTableChain;
};


}

#endif
