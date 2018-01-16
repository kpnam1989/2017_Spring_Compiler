/**
 * Terminal
 *
 * @author:  Gatech Buzz
 */
#ifndef Symbol_hpp
#define Symbol_hpp

#include<cstdio>
#include<iostream>
#include<fstream>
#include<ctype.h>

#include<algorithm>
#include<string>
#include<set>
#include<stack>
#include<map>

enum Entry {Variables, Constants, Types, Functions, Temporaries
};
  
class Symbol
{
private:
  int value;
  static std::map<int, std::string> NumberEnum;

public:

	static std::string ConvertNumberEnum(int thisExpression);

    enum Terminal{
    // Keyword tokens
	ARRAY=0, BREAK, DO, ELSE, END, FOR, FUNCTION, IF,
	IN, LET, OF, THEN, TO, TYPE,
	VAR, WHILE, ENDIF, BEGIN, ENDDO, RETURN,INT, FLOAT,


	// Regular tokens
	COMMA,COLON, SEMI, LPAREN, RPAREN, LBRACK, RBRACK, LBRACE, RBRACE, PERIOD,
	PLUS, MINUS, MULT, DIV, EQ, NEQ, LESSER, GREATER, LESSEREQ, GREATEREQ, AND,
	OR, ASSIGN,
    //
    	// Type tokens
	ID, INTLIT, FLOATLIT,

	// NULL token
	NULLL,

	// End of file token
	EOFF
    };

     enum Nonterminal{
	TIGER_PROGRAM=100,
	DECLARATION_SEGMENT,
	STAT_SEQ,STAT, STAT_TAIL,
	CONST, EXPR, EXPR_LIST, EXPR_LIST_TAIL,
	TYPE_DECLARATION_LIST, VAR_DECLARATION_LIST, FUNCT_DECLARATION_LIST,
	TYPE_DECLARATION,
	VAR_DECLARATION,
	FUNCT_DECLARATION,
	TYPE_EXPR, TYPE_ID,
	ID_LIST, ID_LIST_TAIL,
	OPTIONAL_INIT,
	PARAM_LIST, PARAM, PARAM_LIST_TAIL,
	RET_TYPE,
	ENDIF_CLAUSE,

	// Expression
	ORTERM, ORTAIL,
	ANDTERM, ANDTAIL,
	LEQTERM, LEQTAIL,
	GEQTERM, GEQTAIL,
	LESSTERM, LESSTAIL,
	MORETERM, MORETAIL,
	NEQTERM, NEQTAIL,
	EQTERM, EQTAIL,
	PLUSTERM, PLUSTAIL, PLUS_MINUS,
	FACTOR, FACTOR_TAIL, MUL_DIV,
	ID_TAIL
     };

    enum Action{

	// Dealing with main
	MakeMainLabel=180, MakeReturn,
    //

	// Scope
	// after let and right before end
	InitializeScope, FinalizeScope,

	// For recording ID
	AddVarID,
	CheckVarDeclared,

	// For recording Type
	AddTypeID, AddTypeID_TypeDecl, AddConst,
	CreateArrayType,
	AddSemanticStack,

	LoadArray, StoreArray,
	PushSymbolTable_VAR,
	PushSymbolTable_TYPE,

	AddOperator,
	ApplyOperator,
	AssignAction,

	CheckExistingType,

	// For recording Function
	GetFuncName,
	AddParmID, AddParmType, AddParameterToScope,
	CheckReturnType,
	HasReturn,
	EvaluateFunction,
	PushSymbolTable_FUNC,

	AddFinalRet,

	// IF-flow code generation
	IfCondition, EndIfLabel, ElseCondition,
	GoToEnd,

	// While-flow
	WhileStart, WhileBranch,
	WhileLoop,

	// For-flow
	AddLoopIndex, AddLoopLimit,
	EndLoop,

	BreakAction,

	ClearSemanticStack

    };

    enum IRKeyWord{
    	IR_assign = 300,
    	IR_add,
    	IR_sub,
    	IR_mult,
    	IR_div,
    	IR_and,
    	IR_or,
    	IR_goto,
    	IR_breq,
    	IR_brneq,
    	IR_brlt,
    	IR_brgt,
    	IR_brgeq,
    	IR_brleq,
    	IR_return,
    	IR_call,
    	IR_callr,
    	IR_array_store,
    	IR_array_load
    };

  void operator=(int value){
	this->value = value;
  }

  int getValue() const {
    return value;
  }

  bool isAction() const {
	  return(this->value >= 180);
  }

};

std::map<int, std::string> Symbol::NumberEnum = {
		{0,"ARRAY"},
		{1," BREAK"},
		{2," DO"},
		{3," ELSE"},
		{4," END"},
		{5," FOR"},
		{6," FUNCTION"},
		{7," IF"},
		{8,"IN"},
		{9," LET"},
		{10," OF"},
		{11," THEN"},
		{12," TO"},
		{13," TYPE"},
		{14,"VAR"},
		{15," WHILE"},
		{16," ENDIF"},
		{17," BEGIN"},
		{18," ENDDO"},
		{19," RETURN"},
		{20,"INT"},
		{21," FLOAT"},
		{22,"COMMA"},
		{23,"COLON"},
		{24," SEMI"},
		{25," LPAREN"},
		{26," RPAREN"},
		{27," LBRACK"},
		{28," RBRACK"},
		{29," LBRACE"},
		{30," RBRACE"},
		{31," PERIOD"},
		{32,"PLUS"},
		{33," MINUS"},
		{34," MULT"},
		{35," DIV"},
		{36," EQ"},
		{37," NEQ"},
		{38," LESSER"},
		{39," GREATER"},
		{40," LESSEREQ"},
		{41," GREATEREQ"},
		{42," AND"},
		{43,"OR"},
		{44," ASSIGN"},
		{45,"ID"},
		{46," INTLIT"},
		{47," FLOATLIT"},
		{48,"NULLL"},
		{49,"EOFF"},
		{100,"TIGER_PROGRAM"},
		{101,"DECLARATION_SEGMENT"},
		{102,"STAT_SEQ"},
		{103,"STAT"},
		{104," STAT_TAIL"},
		{105,"CONST"},
		{106," EXPR"},
		{107," EXPR_LIST"},
		{108," EXPR_LIST_TAIL"},
		{109,"TYPE_DECLARATION_LIST"},
		{110," VAR_DECLARATION_LIST"},
		{111," FUNCT_DECLARATION_LIST"},
		{112,"TYPE_DECLARATION"},
		{113,"VAR_DECLARATION"},
		{114,"FUNCT_DECLARATION"},
		{115,"TYPE_EXPR"},
		{116," TYPE_ID"},
		{117,"ID_LIST"},
		{118," ID_LIST_TAIL"},
		{119,"OPTIONAL_INIT"},
		{120,"PARAM_LIST"},
		{121," PARAM"},
		{122," PARAM_LIST_TAIL"},
		{123,"RET_TYPE"},
		{124,"ENDIF_CLAUSE"},
		{125,"ORTERM"},
		{126," ORTAIL"},
		{127,"ANDTERM"},
		{128," ANDTAIL"},
		{129,"LEQTERM"},
		{130," LEQTAIL"},
		{131,"GEQTERM"},
		{132," GEQTAIL"},
		{133,"LESSTERM"},
		{134," LESSTAIL"},
		{135,"MORETERM"},
		{136," MORETAIL"},
		{137,"NEQTERM"},
		{138," NEQTAIL"},
		{139,"EQTERM"},
		{140," EQTAIL"},
		{141,"PLUSTERM"},
		{142," PLUSTAIL"},
		{143," PLUS_MINUS"},
		{144,"FACTOR"},
		{145," FACTOR_TAIL"},
		{146," MUL_DIV"},
		{147,"ID_TAIL"}
};

std::string Symbol::ConvertNumberEnum(int thisExpression){
	return(Symbol::NumberEnum.find(thisExpression)->second);
}



#endif
