/*
 * ParseTree.cpp
 *
 *  Created on: Feb 22, 2017
 *      Author: nam_na
 */
#include "ParseTree.h"
#include "../common/Symbol.hpp"

ParseNode::ParseNode(int ExpressionType, ParseNode* parent) :
		ExpressionType_(ExpressionType), parent_(parent) {
	ExpressionName = Symbol::ConvertNumberEnum(ExpressionType_);
}

ParseNode::ParseNode(int ExpressionType) :
		ExpressionType_(ExpressionType) {
	parent_ = this;
	ExpressionName = Symbol::ConvertNumberEnum(ExpressionType_);
}

bool ParseNode::isAction(){
	return(this->ExpressionType_ >= 180);
}

void ParseNode::DeleteChildren(ParseNode* toDelete){
	if(children.size() == 0 ){
		throw("There is no children");
	} else {
		for(int i = 0; i< children.size(); ++i){
			if(children[i] == toDelete){
				children.erase(children.begin()+i);
			}
		}

	}
};

bool ParseNode::isLeaf(){
	// actually, also whether the Node can be nullified
	return (children.size()==0);
}

void ParseNode::toString(){
	if (isLeaf()){
		std::cout << " " << ExpressionType_ << " ";
	} else {
		std::cout << " Children of " << ExpressionName << std::endl;
		for (int i = 0; i < children.size(); ++i){
			std::cout << children[i]->ExpressionName << "  ";
		}

		std::cout << std::endl << " End Children of " << ExpressionName <<std::endl;
	}

}


