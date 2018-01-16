/**
 * Parser
 *
 * @author: Gatech Buzz
 * Gatech Buzz provides a very rough outline of the parser
 * I add more functions in order to make the Parser functional include:
 * Semantic Analysis
 * Intermediate Represetation
 * Outputting translated codes
 */
#include "Parser.h"
#include "ParseTree.h"
#include "../common/Symbol.hpp"

void Parser::InsertParseTable(int a, const std::vector<int> &wordList,
		const std::vector<int> &productionRule) {
	for (std::vector<int>::const_iterator it = std::begin(wordList);
			it != std::end(wordList); it++) {
		SymbolTerminalPair stp(a, *it);
		std::vector<int> tmpVector = productionRule;
		parseTable.insert(std::make_pair(stp, tmpVector));
	}
}

void Parser::initializeTerminalMapped() {
	terminalMapped.insert(std::make_pair(Symbol::Terminal::COMMA, ","));
	terminalMapped.insert(std::make_pair(Symbol::Terminal::EOFF, ""));
	terminalMapped.insert(std::make_pair(Symbol::Terminal::SEMI, ";"));
	terminalMapped.insert(std::make_pair(Symbol::Terminal::LPAREN, "("));
	terminalMapped.insert(std::make_pair(Symbol::Terminal::RPAREN, ")"));
	terminalMapped.insert(std::make_pair(Symbol::Terminal::LBRACK, "["));
	// ....
}

// Constructor - also initiate the scanner
Parser::Parser(std::string fileName) :
		scanner(fileName), rootNode(Symbol::Nonterminal::TIGER_PROGRAM), scope0(
				0) {

	scope0.Setup();

	parseStack.push(Symbol::Terminal::EOFF);
	parseStack.push(Symbol::Nonterminal::TIGER_PROGRAM);

	parseNodeStack.push(new ParseNode(Symbol::Terminal::EOFF));
	parseNodeStack.push(&rootNode);

	initializeTerminalMapped();

	globalFileName = fileName;

	CreateParseTable();
}

bool Parser::isFloat(std::pair<std::string, Record> rhs_,
		std::pair<std::string, Record> lhs_) {
	return ((lhs_.second.type == "float") || (rhs_.second.type == "float"));
}

bool Parser::anyArray(std::pair<std::string, Record> rhs_,
		std::pair<std::string, Record> lhs_) {
	return ((lhs_.second.dimension != "0") || (rhs_.second.dimension != "0"));
}

void Parser::ArrayStore(
		std::vector<std::pair<std::string, Record> > &thisStack) {
	if (thisStack.size() != 3) {
		error(
				"Expect the stack to be of size 3: array, index and expression. Current size: ");
		return;
	}

	std::pair<std::string, Record> tmpRecord = thisStack.back();
	thisStack.pop_back();

	std::pair<std::string, Record> theIndex = thisStack.back();
	thisStack.pop_back();

	std::pair<std::string, Record> theArray = thisStack.back();
	thisStack.pop_back();

	if (theIndex.second.type != "int") {
		error("Expect the index expression to be of type int.");
		return;
	} else if (tmpRecord.second.NamedType != theArray.second.type) {
		error(
				"Array of type " + theArray.second.type
						+ " while value is of type "
						+ tmpRecord.second.NamedType);
		return;
	}

	CodeFactory.AddTab();
	CodeFactory.Add_Separator("arrayStore");
	CodeFactory.Add_Separator(theArray.first);
	CodeFactory.Add_Separator(theIndex.first);
	CodeFactory.Add(tmpRecord.first);
	CodeFactory.AddLine();

}

void Parser::EvaluateFunction(
		std::vector<std::pair<std::string, Record> > &thisStack) {
	int functionIndex = thisStack.size() - 1;
	Record thisFunction;

	while (functionIndex >= 0) {
		if (thisStack[functionIndex].second.tableType == "Functions")
			break;
		functionIndex = functionIndex - 1;
	}

	if (functionIndex < 0) {
		std::cout << "    " << "Not found any function in the semantic list."
				<< std::endl;
		return;
	}

	thisFunction = thisStack[functionIndex].second;
	AddDebugMessage(
			"Start evaluating function: " + thisStack[functionIndex].first
					+ ".");

	for (int j = 1; j < (thisStack.size() - functionIndex); ++j) {
		if (thisStack[functionIndex + j].second.NamedType
				!= thisFunction.parameterTypes[j - 1]) {
			error(
					"Evaluate error: Expect parameter " + std::to_string(j)
							+ " to be " + thisFunction.parameterTypes[j - 1]
							+ " , instead receive "
							+ thisStack[functionIndex + j].second.NamedType
							+ ".");
			return;
		}
		if (thisStack[functionIndex + j].second.dimension
				!= thisFunction.parameterDimensions[j - 1]) {
			error(
					"Evaluate error: Expect parameter " + std::to_string(j)
							+ " to have dimension "
							+ thisFunction.parameterDimensions[j - 1]
							+ " , instead receive "
							+ thisStack[functionIndex + j].second.dimension
							+ ".");
			return;
		}

	}

	if (thisStack.size() - functionIndex - 1 < thisFunction.parameters.size()) {
		error(
				"Function " + thisStack[functionIndex].first + " expect "
						+ std::to_string(thisFunction.parameters.size())
						+ " parameters but found only "
						+ std::to_string(thisStack.size() - functionIndex - 1));
		return;
	}

	std::string tmpName;
	thisFunction.NamedType = thisFunction.returnType;
	thisFunction.type = thisFunction.returnType;

	thisFunction.functionIndex = functionIndex;
	if (thisFunction.returnType == "") {
		thisFunction.value = "0";
	} else {
		// TODO: just a place holder here
		thisFunction.value = "1";
		tmpCounter += 1;
		tmpName = "$t" + std::to_string(tmpCounter);
	}

	// IR code generator
	CodeFactory.AddTab();
	if (thisFunction.returnType == "") {
		CodeFactory.Add_Separator("call");
	} else {
		CodeFactory.Add_Separator("callr");
		CodeFactory.Add_Separator(tmpName);
	}

	CodeFactory.Add_Separator(thisStack[functionIndex].first);
	for (int j = 1; j < (thisStack.size() - functionIndex); ++j) {
		CodeFactory.Add_Separator(thisStack[functionIndex + j].first);
	}

	CodeFactory.AddLine();

	while (thisStack.size() != functionIndex) {
		thisStack.pop_back();
	}
	if (thisFunction.returnType == "")
		thisStack.push_back(std::make_pair(tmpName, thisFunction));

}

int main(int argc, char** argv) {
//		// The user has given us a bad number of args
	if (argc > 3 || argc < 1) {
		printHelp();
		return 0;
	}

	// Initialize the Parser with the given filename
	Parser parser(argv[1]);

	// Print debug info. if flagged
	if (argc > 2 && strcmp(argv[2], "-d") == 0)
		parser.printDebug = true;

	if (argc > 2 && strcmp(argv[2], "-d") != 0)
		std::cout << "\nPlease use \"-d\" as flag for debugging.\n";

	parser.parse_Node();
//	parser.outFile.close();

	return 0;
}

