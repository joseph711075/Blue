#ifndef PASS2VISITOR_H_
#define PASS2VISITOR_H_

#include <iostream>
#include <string>

#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"
#include "wci/intermediate/TypeSpec.h"

#include "BlueBaseVisitor.h"
#include "antlr4-runtime.h"
#include "BlueVisitor.h"

using namespace wci;
using namespace wci::intermediate;

class Pass2Visitor : public BlueBaseVisitor
{
private:
	string program_name;
	ostream& j_file;
	int lableNumber;

public:
	Pass2Visitor(ostream& j_file, int label);
    virtual ~Pass2Visitor();

	antlrcpp::Any visitProgram(BlueParser::ProgramContext *ctx) override;
	antlrcpp::Any visitMain(BlueParser::MainContext *ctx) override;
	antlrcpp::Any visitHeader(BlueParser::HeaderContext *ctx) override;
	antlrcpp::Any visitFunc_list(BlueParser::Func_listContext *ctx) override;


	//antlrcpp::Any visitCompoundStmt(BlueParser::CompoundStmtContext *ctx) override ;
	antlrcpp::Any visitAssignmentStmt(BlueParser::AssignmentStmtContext *ctx) override ;
	antlrcpp::Any visitLoopStmt(BlueParser::LoopStmtContext *ctx) override ;
	antlrcpp::Any visitWhenStmt(BlueParser::WhenStmtContext *ctx) override ;

	antlrcpp::Any visitPrintf(BlueParser::PrintfContext *ctx) override;
	//antlrcpp::Any visitCompound_stmt(BlueParser::Compound_stmtContext *ctx) override ;
	antlrcpp::Any visitAssignment_stmt(BlueParser::Assignment_stmtContext *ctx) override ;
	antlrcpp::Any visitLoop_stmt(BlueParser::Loop_stmtContext *ctx) override ;
	antlrcpp::Any visitWhen_stmt(BlueParser::When_stmtContext *ctx) override ;

	antlrcpp::Any visitFuncCall_stmt(BlueParser::FuncCall_stmtContext *ctx) override;
	//antlrcpp::Any visitVariable(BlueParser::VariableContext *ctx) override ;

	//antlrcpp::Any visitParens(BlueParser::ParensContext *ctx) override ;
	//antlrcpp::Any visitBoolean(BlueParser::BooleanContext *ctx) override ;


	antlrcpp::Any visitAddSubExpr(BlueParser::AddSubExprContext *ctx) override ;
	antlrcpp::Any visitMulDivExpr(BlueParser::MulDivExprContext *ctx) override ;
	antlrcpp::Any visitIdentifier(BlueParser::IdentifierContext *ctx) override ;



	//antlrcpp::Any visitUnsignedNumberExpr(BlueParser::UnsignedNumberExprContext *ctx) override ;
	antlrcpp::Any visitRelExpr(BlueParser::RelExprContext *ctx) override ;

	//antlrcpp::Any visitSignedNumberExpr(BlueParser::SignedNumberExprContext *ctx) override ;


	antlrcpp::Any visitSignedNumber(BlueParser::SignedNumberContext *ctx) override ;
	antlrcpp::Any visitIntegerConst(BlueParser::IntegerConstContext *ctx) override ;
	antlrcpp::Any visitFloatConst(BlueParser::FloatConstContext *ctx) override ;
	//antlrcpp::Any visitSign(BlueParser::SignContext *ctx) override ;
	//antlrcpp::Any visitMul_div_operation(BlueParser::Mul_div_operationContext *ctx) override ;
	//antlrcpp::Any visitAdd_sub_operation(BlueParser::Add_sub_operationContext *ctx) override ;
	//antlrcpp::Any visitRel_operation(BlueParser::Rel_operationContext *ctx) override ;
};

#endif /* PASS2VISITOR_H_ */
