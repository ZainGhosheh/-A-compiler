#ifndef A_LANG_DATA_TYPES
#define A_LANG_DATA_TYPES

#include <list>
#include <sstream>
#include "errors.hpp"

#include <unordered_map>

#ifndef A_LANG_HASH_MAP_ALIAS
// Use an alias template so that we can use
// "HashMap" and it means "std::unordered_map"
template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

#endif


namespace a_lang{

class DataType;

class TypeNode;

class BasicType;
class FnType;
class ErrorType;
class ClassType;
class ScopeTable;
class SemSymbol;

enum BaseType{
	INT, VOID, STRING, BOOL, CLASS
};

//This class is the superclass for all a_lang types. You
// can get information about which type is implemented
// concretely using the as<X> functions, or query information
// using the is<X> functions.
class DataType{
public:
	virtual std::string getString() const = 0;
	virtual const BasicType * asBasic() const { return nullptr; }
	virtual const FnType * asFn() const { return nullptr; }
	virtual const ClassType * asClass() const { return nullptr; }
	virtual const ErrorType * asError() const { return nullptr; }
	virtual bool isVoid() const { return false; }
	virtual bool isInt() const { return false; }
	virtual bool isBool() const { return false; }
	virtual bool isString() const { return false; }
	virtual bool isClass() const { return false; }
	virtual bool isPerfect() const { return false; }
	virtual bool isRef() const { return false; }
	virtual bool validVarType() const = 0 ;
	virtual size_t getSize() const = 0;
protected:
};

//This DataType subclass is the superclass for all a_lang types.
// Note that there is exactly one instance of this
class ErrorType : public DataType{
public:
	static ErrorType * produce(){
		//Note: this static member will only ever be initialized
		// ONCE, no matter how many times the function is called.
		// That means there will only ever be 1 instance of errorType
		// in the entire codebase.
		static ErrorType * error = new ErrorType();
		return error;
	}
	virtual const ErrorType * asError() const override { return this; }
	virtual std::string getString() const override {
		return "ERROR";
	}
	virtual bool validVarType() const override { return false; }
	virtual size_t getSize() const override { return 0; }
private:
	ErrorType(){
		/* private constructor, can only
		be called from produce */
	}
	size_t line;
	size_t col;
};

class RefType : public DataType {
public:
	static RefType * produce(const DataType * in){
		if (in == nullptr){
			throw new InternalError("immutable type with no subtype");
		}

		static std::list<RefType *> flyweights;
		for(RefType * fly : flyweights){
			if (fly->subType == in){
				return fly;
			}
		}
		RefType * newType = new RefType(in);
		flyweights.push_back(newType);
		return newType;
	}

	virtual const BasicType * asBasic() const override { return subType->asBasic(); }
	virtual const FnType * asFn() const override { return subType->asFn(); }
	virtual const ClassType * asClass() const override { return subType->asClass(); }
	virtual const ErrorType * asError() const override { return subType->asError(); }
	virtual bool isVoid() const override { return subType->isVoid(); }
	virtual bool isInt() const override { return subType->isInt(); }
	virtual bool isBool() const override { return subType->isBool(); }
	virtual bool isString() const override { return subType->isString(); }
	virtual bool isClass() const override { return subType->isClass(); }
	virtual bool isPerfect() const override { return subType->isPerfect(); }
	virtual bool isRef() const override { return true; }

	virtual std::string getString() const override {
		return "& " + subType->getString();
	}

	virtual bool validVarType() const override {
		return subType->validVarType();
	}

	virtual size_t getSize() const override {
		return subType->getSize();
	}
private:
	RefType(const DataType * sub)
	: subType(sub){ }

	const DataType * subType;
};

class PerfectType : public DataType {
public:
	static PerfectType * produce(const DataType * in){
		if (in == nullptr){
			throw new InternalError("immutable type with no subtype");
		}

		static std::list<PerfectType *> flyweights;
		for(PerfectType * fly : flyweights){
			if (fly->subType == in){
				return fly;
			}
		}
		PerfectType * newType = new PerfectType(in);
		flyweights.push_back(newType);
		return newType;
	}

	virtual const BasicType * asBasic() const override { return subType->asBasic(); }
	virtual const FnType * asFn() const override { return subType->asFn(); }
	virtual const ClassType * asClass() const override { return subType->asClass(); }
	virtual const ErrorType * asError() const override { return subType->asError(); }
	virtual bool isVoid() const override { return subType->isVoid(); }
	virtual bool isInt() const override { return subType->isInt(); }
	virtual bool isBool() const override { return subType->isBool(); }
	virtual bool isString() const override { return subType->isString(); }
	virtual bool isClass() const override { return subType->isClass(); }
	virtual bool isPerfect() const override { return true; }
	virtual bool isRef() const override { return subType->isRef(); }

	virtual std::string getString() const override {
		return "immutable " + subType->getString();
	}

	virtual bool validVarType() const override {
		return subType->validVarType();
	}

	virtual size_t getSize() const override {
		return subType->getSize();
	}
private:
	PerfectType(const DataType * sub)
	: subType(sub){ }

	const DataType * subType;
};

//DataType subclass for all scalar types
class BasicType : public DataType{
public:
	static BasicType * VOID(){
		return produce(BaseType::VOID);
	}
	static BasicType * BOOL(){
		return produce(BaseType::BOOL);
	}
	static BasicType * INT(){
		return produce(BaseType::INT);
	}
	static BasicType * STRING(){
		return produce(BaseType::STRING);
	}

	//Create a scalar type. If that type already exists,
	// return the known instance of that type. Making sure
	// there is only 1 instance of a class for a given set
	// of fields is known as the "flyweight" design pattern
	// and ensures that the memory needs of a program are kept
	// down: rather than having a distinct type for every base
	// INT (for example), only one is constructed and kept in
	// the flyweights list. That type is then re-used anywhere
	// it's needed.

	//Note the use of the static function declaration, which
	// means that no instance of BasicType is needed to call
	// the function.
	static BasicType * produce(BaseType base){
		//Note the use of the static local variable, which
		//means that the flyweights variable persists between
		// multiple calls to this function (it is essentially
		// a global variable that can only be accessed
		// in this function).
		static std::list<BasicType *> flyweights;
		for(BasicType * fly : flyweights){
			if (fly->getBaseType() == base){
				return fly;
			}
		}
		BasicType * newType = new BasicType(base);
		flyweights.push_back(newType);
		return newType;
	}
	const BasicType * asBasic() const override {
		return this;
	}
	BasicType * asBasic(){
		return this;
	}
	bool isInt() const override {
		return myBaseType == BaseType::INT;
	}
	bool isBool() const override {
		return myBaseType == BaseType::BOOL;
	}
	virtual bool isVoid() const override {
		return myBaseType == BaseType::VOID;
	}
	virtual bool isString() const override {
		return myBaseType == BaseType::STRING;
	}
	virtual bool isClass() const override {
		return myBaseType == BaseType::CLASS;
	}
	virtual bool validVarType() const override {
		return !isVoid();
	}
	virtual BaseType getBaseType() const { return myBaseType; }
	virtual std::string getString() const override;
	virtual size_t getSize() const override {
		switch (myBaseType) {
		case BaseType::BOOL: return 8;
		case BaseType::STRING: return 8;
		case BaseType::INT: return 8;
		case BaseType::VOID: return 8;
		case BaseType::CLASS: throw new ToDoError("class size");
		}
		throw new InternalError("getSize of unknown type");
		/*
		if (isBool()){ return 8; }
		else if (isString()){ return 8; }
		else if (isVoid()){ return 8; }
		else if (isInt()){ return 8; }
		else if (isShort()){ return 1; }
		else { return 0; }
		*/
	}
private:
	BasicType(BaseType base)
	: myBaseType(base){ }
	BaseType myBaseType;
};

class TypeList : public DataType{
public:
	static TypeList * produce(const std::list<TypeNode *> * typeNodes);
	size_t count() const{ return types->size(); }
	size_t getSize() const {
		size_t res = 0;
		for (auto t : *types){
			res += t->getSize();
		}
		return res;
	}
	std::string getString() const{
		std::string res;
		bool first = true;
		for (auto t : *types){
			if (first){ first = false; }
			else { res += ", "; }
			res += t->getString();
		}
		return res;
	}
	bool validVarType() const { return false; }
	const std::list<const DataType *> * getTypes() const { return types; }

private:
	TypeList(const std::list<const DataType *> * typesIn): types(typesIn){
	}
	const std::list<const DataType *> * types;
};

class ClassType : public DataType{
public:
	static HashMap<const ClassType *, ScopeTable *> myMap;

	static SemSymbol * getField(const ClassType * type, 
	  std::string name);
	
	ClassType(std::string name, ScopeTable * fields)
	: myName(name), myFields(fields){ 
		myMap[this] = fields;
	}

	virtual const ClassType * asClass() const override { return this; }
	virtual bool isClass() const override { return true; }

	SemSymbol * fieldLookup(std::string name);

	std::string getString() const override;

	virtual size_t getSize() const override{
		//calculate the size of the class
		throw new ToDoError("iterate over non-fn fields");
	}	
	virtual bool validVarType() const override { return true; }
private:
	std::string myName;
	ScopeTable * myFields;
};

//DataType subclass to represent the type of a function. It will
// have a list of argument types and a return type.
class FnType : public DataType{
public:
	static FnType * produce(const TypeList * inTypes, const DataType * outType){
		static std::list<FnType *> knownFnTypes;
		for (auto knownFnType : knownFnTypes){
			if (knownFnType->sameSigAs(inTypes, outType)){
				return knownFnType;
			}
		}
		FnType * t = new FnType(inTypes, outType);
		knownFnTypes.push_back(t);
		return t;
	}

	bool sameSigAs(const TypeList * inTypes, const DataType * outType){
		if (myFormalTypes != inTypes){ return false; }
		if (myRetType != outType){ return false; }
		return true;
	}

	std::string getString() const override{
		std::string result = "";
		bool first = true;
		result += "(";
		result += myFormalTypes->getString();
		result += ")";
		result += "->";
		result += myRetType->getString();
		return result;
	}
	virtual const FnType * asFn() const override { return this; }

	const DataType * getReturnType() const {
		return myRetType;
	}
	const TypeList * getFormalTypes() const {
		return myFormalTypes;
	}
	virtual bool validVarType() const override { return true; }
	virtual size_t getSize() const override { return 0; }

private:
	FnType(const TypeList * formalTypesIn, const DataType * retTypeIn)
	: DataType(),
	  myFormalTypes(formalTypesIn),
	  myRetType(retTypeIn)
	{
	}
	const TypeList * myFormalTypes;
	const DataType * myRetType;
};

}

#endif
