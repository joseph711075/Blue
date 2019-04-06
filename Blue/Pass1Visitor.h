#ifndef PASS1VISITOR_H_
#define PASS1VISITOR_H_

#include <iostream>

#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"
#include "wci/intermediate/TypeSpec.h"

#include "BlueBaseVisitor.h"
#include "antlr4-runtime.h"
#include "BlueVisitor.h"

using namespace wci;
using namespace wci::intermediate;

class Pass1Visitor : public BlueBaseVisitor
{
private:
    SymTabStack *symtab_stack;
    SymTabEntry *program_id;
    vector<SymTabEntry *> variable_id_list;
    vector<string> variable_func_list;
    TypeSpec *type;
    string type_indicator;
    ofstream j_file;
    string program_name;
    string name;
    int lableNumber;
    int errorCount;

public:
    Pass1Visitor();
    virtual ~Pass1Visitor();

    ostream& get_assembly_file();

    antlrcpp::Any visitProgram(BlueParser::ProgramContext *ctx) override;
    antlrcpp::Any visitHeader(BlueParser::HeaderContext *ctx) override;

    antlrcpp::Any visitDeclarationList(BlueParser::DeclarationListContext *ctx) override;
    antlrcpp::Any visitDeclarations(BlueParser::DeclarationsContext *ctx) override;
    antlrcpp::Any visitVar_list(BlueParser::Var_listContext *ctx) override;
    antlrcpp::Any visitVar_id(BlueParser::Var_idContext *ctx) override;
    antlrcpp::Any visitType_id(BlueParser::Type_idContext *ctx) override;

    antlrcpp::Any visitFunc(BlueParser::FuncContext *ctx) override;
    antlrcpp::Any visitParam(BlueParser::ParamContext *ctx) override;
    antlrcpp::Any visitAssignment_stmt(BlueParser::Assignment_stmtContext *ctx) override;
    antlrcpp::Any visitFunc_ret(BlueParser::Func_retContext *ctx) override;
    antlrcpp::Any visitPrintf(BlueParser::PrintfContext *ctx) override;



    antlrcpp::Any visitWhen_stmt(BlueParser::When_stmtContext *ctx) override;
    antlrcpp::Any visitLoop_stmt(BlueParser::Loop_stmtContext *ctx) override;
    antlrcpp::Any visitAddSubExpr(BlueParser::AddSubExprContext *ctx) override;
    antlrcpp::Any visitMulDivExpr(BlueParser::MulDivExprContext *ctx) override;
    antlrcpp::Any visitRelExpr(BlueParser::RelExprContext *ctx) override;
    antlrcpp::Any visitIdentifier(BlueParser::IdentifierContext *ctx) override;
    antlrcpp::Any visitUnsignedNumberExpr(BlueParser::UnsignedNumberExprContext *ctx) override;
    antlrcpp::Any visitSignedNumberExpr(BlueParser::SignedNumberExprContext *ctx) override;
    antlrcpp::Any visitSignedNumber(BlueParser::SignedNumberContext *ctx) override;
    antlrcpp::Any visitIntegerConst(BlueParser::IntegerConstContext *ctx) override;
    antlrcpp::Any visitFloatConst(BlueParser::FloatConstContext *ctx) override;
    antlrcpp::Any visitParens(BlueParser::ParensContext *ctx) override;
    int getLableNumber() {return lableNumber;}
    int getErrorCount() {return errorCount;}
//
//    antlrcpp::Any visitRelExpr(BlueParser::RelExprContext *ctx) override;
//    antlrcpp::Any visitBoolean(BlueParser::BooleanContext *ctx) override;


};

#endif /* PASS1VISITOR_H_ */
