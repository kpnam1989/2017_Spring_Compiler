/*
 * Parser.h
 *
 *  Created on: Feb 15, 2017
 *      Author: nam_na
 */

#ifndef SRC_PARSER_PARSER_H_
#define SRC_PARSER_PARSER_H_

#include "../Scanner/Scanner.hpp"
#include "../SemanticAnalyzer/SymbolTable.hpp"
#include "../SemanticAnalyzer/SymbolTerminalPair.hpp"
#include "../common/Symbol.hpp"
#include "ParseTree.h"
#include "CodeGenerator.hpp"
#include <cstring>


class Parser {
private:
	Scanner scanner;

	int numErrors = 0;

	CodeGenerator CodeFactory;
	CodeGenerator DebugCode;
	std::string globalFileName, reportCurr;

	std::stack<int> parseStack;
	std::stack<Level*> scopeStack;

	std::stack<ParseNode*> parseNodeStack;
	std::map<int, std::string> terminalMapped;

	std::map<SymbolTerminalPair, std::vector<int>> parseTable;
	void ArrayStore(std::vector<std::pair<std::string, Record> > &thisStack);
	void ArrayLoading(std::vector<std::pair<std::string, Record> > &thisStack);
	SymbolTable scope0;

	void InsertParseTable(int a, const std::vector<int> &wordList,
				const std::vector<int> &productionRule);

	bool isFloat(std::pair<std::string, Record> rhs_, std::pair<std::string, Record> lhs_);
	bool anyArray(std::pair<std::string, Record> rhs_, std::pair<std::string, Record> lhs_);
	void EvaluateFunction(std::vector<std::pair<std::string, Record> > &thisStack);

	void initializeTerminalMapped();

	void RemoveNullChildren(ParseNode* toDelete);
	void PromoteOnlyChild(ParseNode* toPromote);

	void CreateParseTable_MainPart();
	void CreateParseTable_TYPE_DECL();
	void CreateParseTable_VAR_DECL();
	void CreateParseTable_FUNC_DECL();
	void CreateParseTable_STAT_SEQ();
	void CreateParseTable_EXPR_LIST();
	void CreateParseTable_EXPR();

	bool isTerminal(int thisSymbol);
	void AddDebugMessage(std::string DebugMessage);

public:
	std::ofstream outFile;
	ParseNode rootNode;

	std::string NULLValue = "NULLL";

	bool printDebug;
	Parser(std::string fileName);
	int tmpCounter = 0, ControlFlowCounter = 0;
	void CreateParseTable();
	void error(TokenPair *w, int currentExpression);

	void error(std::string thisString);

	void parse();
	void parse_Node();
	void printHelp();

	void ApplyOperator(std::string thisOperator,
			std::vector<std::pair<std::string, Record>> &thisStack);
};

#endif /* SRC_PARSER_PARSER_H_ */
