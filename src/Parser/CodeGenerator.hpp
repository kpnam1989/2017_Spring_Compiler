/*
 * CodeGenerator.hpp
 *
 *  Created on: Mar 3, 2017
 *      Author: nam_na
 */

#ifndef SRC_PARSER_CODEGENERATOR_HPP_
#define SRC_PARSER_CODEGENERATOR_HPP_

#include "../SemanticAnalyzer/Record.hpp"
#include <iostream>
#include <sstream>
#include <fstream>

class CodeGenerator {
private:
	std::ostringstream mainStream;
	std::ostringstream* currentStreamPtr;

public:
	std::stack<std::string> IfCounter, WhileCounter, ForCounter;
	std::stack<std::string> CurrentFlow; // used for the break function
	std::stack<std::string> LoopIndex, LoopLimit;

	CodeGenerator(){
		currentStreamPtr = &mainStream;
	};

	void AddLine(){
		(*currentStreamPtr) << std::endl;
	}

	void AddMessage(int currentLine, std::string DebugMessage){
		(*currentStreamPtr) << "Current Line " << currentLine << " : " << DebugMessage << std::endl;
	}

	void AddTab(){
		(*currentStreamPtr) << "\t";
	}

	void GenerateCode(){
		(*currentStreamPtr) << "Starting "<< std::endl;
	};

	void Add(std::string thisCode){
		(*currentStreamPtr) << thisCode;
	}

	void Add_Separator(std::string thisCode){
		(*currentStreamPtr) << thisCode << ", ";
	}

	void PrintAll(std::ostream &fileStream){
		fileStream << mainStream.str();
	}

};




#endif /* SRC_PARSER_CODEGENERATOR_HPP_ */
