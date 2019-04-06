#include <iostream>
#include <string>

#include "Pass2Visitor.h"
#include "antlr4-runtime.h"
#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"
#include "wci/intermediate/TypeSpec.h"
#include "wci/intermediate/symtabimpl/Predefined.h"

using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;

Pass2Visitor::Pass2Visitor(ostream& j_file, int lable)
    : program_name(""), j_file(j_file)
{
	lableNumber = lable;
}

Pass2Visitor::~Pass2Visitor() {}

antlrcpp::Any Pass2Visitor::visitProgram(BlueParser::ProgramContext *ctx)
{
    auto value = visitChildren(ctx);

    //j_file.close();
    return value;
}

antlrcpp::Any Pass2Visitor::visitHeader(BlueParser::HeaderContext *ctx)
{
    program_name = ctx->IDENTIFIER()->toString();
    return visitChildren(ctx);
}

antlrcpp::Any Pass2Visitor::visitFunc_list(BlueParser::Func_listContext *ctx)
{
    return 0;
}


antlrcpp::Any Pass2Visitor::visitMain(BlueParser::MainContext *ctx)
{
    // Emit the main program header.
    j_file << endl;
    j_file << ".method public static main([Ljava/lang/String;)V" << endl;
    j_file << endl;
    j_file << "\tnew RunTimer" << endl;
    j_file << "\tdup" << endl;
    j_file << "\tinvokenonvirtual RunTimer/<init>()V" << endl;
    j_file << "\tputstatic        " << program_name
           << "/_runTimer LRunTimer;" << endl;
    j_file << "\tnew PascalTextIn" << endl;
    j_file << "\tdup" << endl;
    j_file << "\tinvokenonvirtual PascalTextIn/<init>()V" << endl;
    j_file << "\tputstatic        " + program_name
           << "/_standardIn LPascalTextIn;" << endl;

    auto value = visitChildren(ctx);


    // Emit the main program epilogue.
    j_file << endl;
    j_file << "\tgetstatic     " << program_name
               << "/_runTimer LRunTimer;" << endl;
    j_file << "\tinvokevirtual RunTimer.printElapsedTime()V" << endl;
    j_file << endl;
    j_file << "\treturn" << endl;
    j_file << endl;
    j_file << ".limit locals 16" << endl;
    j_file << ".limit stack 16" << endl;
    j_file << ".end method" << endl;



    return value;
}

antlrcpp::Any Pass2Visitor::visitLoopStmt(BlueParser::LoopStmtContext *ctx)
{
    j_file << endl << "; " + ctx->getText() << endl << endl;

    return visitChildren(ctx);
}

//antlrcpp::Any Pass2Visitor::visitCompoundStmt(BlueParser::CompoundStmtContext *ctx)
//{
//    j_file << endl << "; " + ctx->getText() << endl << endl;
//
//    return visitChildren(ctx);
//}
antlrcpp::Any Pass2Visitor::visitAssignmentStmt(BlueParser::AssignmentStmtContext *ctx)
{
    j_file << endl << "; " + ctx->getText() << endl << endl;

    return visitChildren(ctx);
}
antlrcpp::Any Pass2Visitor::visitWhenStmt(BlueParser::WhenStmtContext *ctx)
{
    j_file << endl << "; " + ctx->getText() << endl << endl;

    return visitChildren(ctx);
}

antlrcpp::Any Pass2Visitor::visitPrintf(BlueParser::PrintfContext *ctx)
{


	string type_indicator;
	j_file << endl << endl;
	j_file << ";" << ctx->getText() << endl;
	j_file << "\tgetstatic    java/lang/System/out Ljava/io/PrintStream;" << endl;
	j_file << "\tldc          " << ctx->expr(0)->getText() << endl;
	j_file << "\ticonst_" << ctx->expr().size() - 1 << endl;
	j_file << "\tanewarray    java/lang/Object" << endl;

	auto value = 0;

	for(int i = 0; i < ctx->expr().size() - 1; i++)
	{
		j_file << "\tdup" << endl;
		j_file << "\ticonst_" << i << endl;
		//cout << "in dude\n";
		value = visit(ctx->expr(i+1));
		//cout << "out dude\n";
		type_indicator =
					  (ctx->expr(i+1)->type == Predefined::integer_type) ? "I"
					: (ctx->expr(i+1)->type == Predefined::real_type)    ? "F"
					:                                                      "?";




		j_file << "\tinvokestatic  java/lang/";
		if(type_indicator == "I") j_file << "Integer.valueOf(I)Ljava/lang/Integer;" << endl;
		else 					  j_file << "Float.valueOf(F)Ljava/lang/Float;" << endl;

		j_file << "\taastore" << endl;
	}



	j_file << "\tinvokevirtual java/io/PrintStream.printf(Ljava/lang/String;[Ljava/lang/Object;)Ljava/io/PrintStream;" << endl;
	j_file << "\tpop" << endl;
	j_file << endl << endl;

	return 0;
}

antlrcpp::Any Pass2Visitor::visitAssignment_stmt(BlueParser::Assignment_stmtContext *ctx)
{
    auto value = visit(ctx->expr());

    string type_indicator =
                  (ctx->expr()->type == Predefined::integer_type) ? "I"
                : (ctx->expr()->type == Predefined::real_type)    ? "F"
                :                                                   "?";

    // Emit a field put instruction.
    j_file << "\tputstatic\t" << program_name
           << "/" << ctx->variable()->IDENTIFIER()->toString()
           << " " << type_indicator << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitFuncCall_stmt(BlueParser::FuncCall_stmtContext *ctx)
{
	string functionName = ctx->expr(0)->getText();
	string variable;
	string parameters = "";
	TypeSpec *type1;
	auto value = 0;


	for(int i = 1; ctx->expr(i) != NULL; i++)
	{
		value = visit(ctx->expr(i));
		type1 = ctx->expr(i)->type;
		if (type1 == Predefined::integer_type) {
			parameters += "I";
		}
		else if(type1 == Predefined::real_type) {
			parameters += "F";
		}

	}


	j_file << "\tinvokestatic\t" + program_name + "/" + functionName + "(" + parameters + ")";

	type1 = ctx->expr(0)->type;
	parameters.clear();

	if (type1 == Predefined::integer_type) {
		j_file << "I" << endl;
		parameters = "I";
	}
	else if(type1 == Predefined::real_type) {
		j_file << "F" << endl;
		parameters = "F";
	}
	else
		j_file << "V" << endl;



	if(ctx->variable() != NULL)
	{
		variable = ctx->variable()->IDENTIFIER()->toString();
		j_file << "\tputstatic\t" << program_name << "/" << variable << " " << parameters;
	}

	j_file << endl << endl;


    return value;
}


antlrcpp::Any Pass2Visitor::visitWhen_stmt(BlueParser::When_stmtContext *ctx)
{
    j_file << endl << "; " + ctx->getText() << endl << endl;
    auto value = visitChildren(ctx);
    j_file << endl << "L00" << lableNumber << ":" << endl << endl;


    return value;
}

antlrcpp::Any Pass2Visitor::visitLoop_stmt(BlueParser::Loop_stmtContext *ctx)
{
	int temp = (++lableNumber)++;
	j_file << endl << "L00" << temp << ":" << endl << endl;
    j_file << endl << "; " + ctx->getText() << endl << endl;
    auto value = visitChildren(ctx);
    j_file << endl << "\tgoto\tL00" << temp << endl << endl;
    j_file << endl << "L00" << lableNumber << ":" << endl << endl;


    return value;
}

antlrcpp::Any Pass2Visitor::visitRelExpr(BlueParser::RelExprContext *ctx)
{
    auto value = visitChildren(ctx);

    TypeSpec *type1 = ctx->expr(0)->type;
    TypeSpec *type2 = ctx->expr(1)->type;

    bool integer_mode =    (type1 == Predefined::integer_type)
                        && (type2 == Predefined::integer_type);
    bool real_mode    =    (type1 == Predefined::real_type)
                        && (type2 == Predefined::real_type);


    string op = ctx->rel_operation()->getText();
    string opcode;

    if (op == "==")
    {
        opcode = integer_mode ? "if_icmpeq"
              // : real_mode    ? "fadd"
               :                "????";
    }
    else if(op == "!=")
    {
        opcode = integer_mode ? "if_icmpne"
               //: real_mode    ? "fsub"
               :                "????";
    }
    else if(op == "<")
    {
        opcode = integer_mode ? "if_icmplt"
              // : real_mode    ? "fsub"
               :                "????";
    }
    else if(op == "<=")
    {
        opcode = integer_mode ? "if_icmple"
              // : real_mode    ? "fsub"
               :                "????";
    }
    else if(op == ">")
    {
        opcode = integer_mode ? "if_icmpgt"
              // : real_mode    ? "fsub"
               :                "????";
    }
    else if(op == ">=")
    {
        opcode = integer_mode ? "if_icmpge"
              // : real_mode    ? "fsub"
               :                "????";
    }

    // Emit an add or subtract instruction.
    j_file << "\t" << opcode << "\tL00" << lableNumber++ <<endl;
    j_file << "\ticonst_0" << endl;
    j_file << "\t goto\tL00" << lableNumber << endl;
    j_file << "L00" << lableNumber-1 << ":" << endl;
    j_file << "\ticonst_1" << endl;
    j_file << "L00" << lableNumber << ":" << endl;
    j_file << "\tifeq\tL00" << ++lableNumber << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitAddSubExpr(BlueParser::AddSubExprContext *ctx)
{
    auto value = visitChildren(ctx);

    TypeSpec *type1 = ctx->expr(0)->type;
    TypeSpec *type2 = ctx->expr(1)->type;

    bool integer_mode =    (type1 == Predefined::integer_type)
                        && (type2 == Predefined::integer_type);
    bool real_mode    =    (type1 == Predefined::real_type)
                        && (type2 == Predefined::real_type);

    string op = ctx->add_sub_operation()->getText();
    string opcode;

    if (op == "+")
    {
        opcode = integer_mode ? "iadd"
               : real_mode    ? "fadd"
               :                "????";
    }
    else
    {
        opcode = integer_mode ? "isub"
               : real_mode    ? "fsub"
               :                "????";
    }

    // Emit an add or subtract instruction.
    j_file << "\t" << opcode << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitMulDivExpr(BlueParser::MulDivExprContext *ctx)
{
    auto value = visitChildren(ctx);

    TypeSpec *type1 = ctx->expr(0)->type;
    TypeSpec *type2 = ctx->expr(1)->type;

    bool integer_mode =    (type1 == Predefined::integer_type)
                        && (type2 == Predefined::integer_type);
    bool real_mode    =    (type1 == Predefined::real_type)
                        && (type2 == Predefined::real_type);

    string op = ctx->mul_div_operation()->getText();
    string opcode;

    if (op == "*")
    {
        opcode = integer_mode ? "imul"
               : real_mode    ? "fmul"
               :                "????";
    }
    else
    {
        opcode = integer_mode ? "idpv"
               : real_mode    ? "fdiv"
               :                "????";
    }

    // Emit a multiply or divide instruction.
    j_file << "\t" << opcode << endl;

    return value;
}

antlrcpp::Any Pass2Visitor::visitIdentifier(BlueParser::IdentifierContext *ctx)
{
    string variable_name = ctx->variable()->IDENTIFIER()->toString();
    TypeSpec *type = ctx->type;

    string type_indicator = (type == Predefined::integer_type) ? "I"
                          : (type == Predefined::real_type)    ? "F"
                          :                                      "?";

    // Emit a field get instruction.
    j_file << "\tgetstatic\t" << program_name
           << "/" << variable_name << " " << type_indicator << endl;

    return 0;
}

antlrcpp::Any Pass2Visitor::visitSignedNumber(BlueParser::SignedNumberContext *ctx)
{
    auto value = visitChildren(ctx);
    TypeSpec *type = ctx->number()->type;

    if (ctx->sign()->children[0] == ctx->sign()->SUB_operation())
    {
        string opcode = (type == Predefined::integer_type) ? "ineg"
                      : (type == Predefined::real_type)    ? "fneg"
                      :                                      "?neg";

        // Emit a negate instruction.
        j_file << "\t" << opcode << endl;
    }

    return value;
}

antlrcpp::Any Pass2Visitor::visitIntegerConst(BlueParser::IntegerConstContext *ctx)
{
    // Emit a load constant instruction.
    j_file << "\tldc\t" << ctx->getText() << endl;

    return 0;
}

antlrcpp::Any Pass2Visitor::visitFloatConst(BlueParser::FloatConstContext *ctx)
{
    // Emit a load constant instruction.
    j_file << "\tldc\t" << ctx->getText() << endl;

    return 0;
}

