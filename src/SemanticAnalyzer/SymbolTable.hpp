#include "Level.hpp"
#include "Record.hpp"
#include <fstream>

// This file implement the scoping and symbol table
// During Semantic Analysis, the compiler will keep track of the variables' scope and value using a Symbol Table
// Many functions in this file have been removed to avoid plagiarism

class SymbolTable {
private:
  Level topLevel;
  Level currLevel;

  std::string NULLvalue = "NULLL";


  std::map<std::string, Record> InnerMap;
  SymbolTable* ParentPtr;
  std::vector<SymbolTable*> childrenScope;

public:
  int scopeLevel;

  SymbolTable(int scopeLevel_): scopeLevel(scopeLevel_) {
	  ParentPtr = this;
    }

  void SetParent(SymbolTable* ParentPtr_){
	  ParentPtr = ParentPtr_;
  }

  SymbolTable* GetParent() const {
	  return ParentPtr;
  }

  int GetMapSize(){
	  return InnerMap.size();
  }

// Set up based type and function
  void Setup(){
	  Record tmpRecord;
	  tmpRecord.tableType = "Types";
	  tmpRecord.type = "int";
	  tmpRecord.NamedType = "int";

	  AddPair(std::make_pair("int", tmpRecord));

	  tmpRecord.type = "float";
	  tmpRecord.NamedType = "float";
	  AddPair(std::make_pair("float", tmpRecord));


	  AddNULL();

	  tmpRecord.parameters.push_back("i");
	  tmpRecord.tableType = "Functions";
	  tmpRecord.parameterTypes.push_back("int");
	  tmpRecord.parameterDimensions.push_back("0");
	  tmpRecord.type = "";
	  tmpRecord.NamedType = "";
	  AddPair(std::make_pair("printi", tmpRecord));



  }

  std::pair<std::string, Record> AddVar(std::string varName, std::vector<std::string> DimensionType,
		  std::string VariableType = "Variables", std::string value = "0.0"){

	  if ((DimensionType.size() != 2) &(DimensionType.size() != 1)){
		  std::cout << "Variable: "<< varName << ": Wrong number of dimensions: " << DimensionType.size() << std::endl;
	  }

	  Record tmp = Record(scopeLevel);
	  tmp.tableType = VariableType;

	  if (DimensionType.size() == 2){
		  tmp.type = DimensionType[1];
		  tmp.dimension = DimensionType[0];

	  }

	  if (DimensionType.size() == 1){
		  tmp.type = DimensionType[0];
	  }

	  std::pair<std::string, Record> tmpPair = std::make_pair(varName, tmp);
	  InnerMap.insert(tmpPair);
	  return tmpPair;
  }

  std::pair<std::string, Record> Lookup(std::string thisName){
	  std::map<std::string, Record>::iterator tmp = InnerMap.find(thisName);
	  if(tmp != InnerMap.end()){
		  return *tmp;
	  } else {
		  if(scopeLevel != 0) {
			  // if not the main scope
			  return ParentPtr->Lookup(thisName);
		  } else {
			  return ParentPtr->Lookup(NULLvalue);
		  }
	  }

  }

  void toString(){
	  for(std::map<std::string, Record>::iterator it = InnerMap.begin();
			  it != InnerMap.end();
			  ++it){
		  std::cout << "-----------------------------------------------" << std::endl;
		  std::cout << "Name: " << it->first << std::endl;
		  it->second.toString();
	  }

	  for(std::vector<SymbolTable*>::iterator it = childrenScope.begin();
			  it != childrenScope.end();
			  ++it){
		  (*it)->toString();
	  }
  }

  void WriteToFile(std::ostream &fileStream){

	  for(std::map<std::string, Record>::iterator it = InnerMap.begin();
	  			  it != InnerMap.end();
	  			  ++it){
		  fileStream << "-----------------------------------------------" << std::endl;
		  fileStream << "Name: " << it->first << std::endl;
	  		  it->second.WriteToFile(fileStream);
	  	  }

	  	  for(std::vector<SymbolTable*>::iterator it = childrenScope.begin();
	  			  it != childrenScope.end();
	  			  ++it){
	  		  (*it)->WriteToFile(fileStream);
	  	  }
  }

};
