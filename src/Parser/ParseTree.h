/*
 * ParseTree.h
 *
 *  Created on: Feb 22, 2017
 *      Author: nam_na
 *	Include Methods to implement the Parse Tree
 */

#ifndef SRC_PARSER_PARSETREE_H_
#define SRC_PARSER_PARSETREE_H_

#include "../common/Symbol.hpp"

class ParseNode {
public:
	std::vector<ParseNode*> children;
	int ExpressionType_;
	ParseNode* parent_;
	std::string ExpressionName;

	ParseNode(int ExpressionType, ParseNode* parent) :
			ExpressionType_(ExpressionType), parent_(parent) {
		ExpressionName = Symbol::ConvertNumberEnum(ExpressionType_);
	}

	ParseNode(int ExpressionType) :
			ExpressionType_(ExpressionType) {
		parent_ = this;
		ExpressionName = Symbol::ConvertNumberEnum(ExpressionType_);
	}

	void toString() {
		if (isLeaf()) {
			std::cout << " " << ExpressionType_ << " ";
		} else {
			std::cout << " Children of " << ExpressionName << std::endl;
			for (int i = 0; i < children.size(); ++i) {
				std::cout << children[i]->ExpressionName << "  ";
			}

			std::cout << std::endl << " End Children of " << ExpressionName
					<< std::endl;
		}

	}

	void DeleteChildren(ParseNode* toDelete) {
		if (children.size() == 0) {
			throw("There is no children");
		} else {
			for (int i = 0; i < children.size(); ++i) {
				if (children[i] == toDelete) {
					children.erase(children.begin() + i);
				}
			}

		}
	}

	bool isLeaf() {
		return (children.size() == 0);
	}

	bool isAction() {
		return (this->ExpressionType_ >= 180);
	}

private:

};

#endif /* SRC_PARSER_PARSETREE_H_ */
