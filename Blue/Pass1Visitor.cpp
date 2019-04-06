#include <iostream>
#include <string>
#include <vector>

#include "Pass1Visitor.h"
#include "antlr4-runtime.h"
#include "wci/intermediate/SymTabStack.h"
#include "wci/intermediate/SymTabEntry.h"
#include "wci/intermediate/TypeSpec.h"
#include "wci/intermediate/SymTabFactory.h"
#include "wci/intermediate/symtabimpl/Predefined.h"
#include "wci/util/CrossReferencer.h"

using namespace std;
using namespace wci;
using namespace wci::intermediate;
using namespace wci::intermediate::symtabimpl;
using namespace wci::util;

Pass1Visitor::Pass1Visitor()
    : program_id(nullptr), j_file(nullptr)
{
    // Create and initialize the symbol table stack.
    symtab_stack = SymTabFactory::create_symtab_stack();
    Predefined::initialize(symtab_stack);
    type = NULL;
    lableNumber = 0;
    errorCount = 0;

    //cout << "=== Pass1Visitor(): symtab stack initialized." << endl;
}

Pass1Visitor::~Pass1Visitor() {}

ostream& Pass1Visitor::get_assembly_file() { return j_file; }

////////////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitProgram(BlueParser::ProgramContext *ctx)
{
    auto value = visitChildren(ctx);

//    cout << "=== visitProgram: Printing xref table." << endl;

    // Print the cross-reference table.
    if(errorCount == 0)
    {
		CrossReferencer cross_referencer;
		cross_referencer.print(symtab_stack);
    }

    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitHeader(BlueParser::HeaderContext *ctx)
{
    program_name = ctx->IDENTIFIER()->toString();

    program_id = symtab_stack->enter_local(program_name);
    program_id->set_definition((Definition)DF_PROGRAM);
    program_id->set_attribute((SymTabKey) ROUTINE_SYMTAB,
                              symtab_stack->push());
    symtab_stack->set_program_id(program_id);

    // Create the assembly output file.
    j_file.open(program_name + ".j");
    if (j_file.fail())
    {
            cout << "***** Cannot open assembly file." << endl;
            exit(-99);
    }

    // Emit the program header.
    j_file << ".class public " << program_name << endl;
    j_file << ".super java/lang/Object" << endl;

    // Emit the RunTimer and PascalTextIn fields.
    j_file << endl;
    j_file << ".field private static _runTimer LRunTimer;" << endl;
    j_file << ".field private static _standardIn LPascalTextIn;" << endl;
    j_file << endl << endl;
    return visitChildren(ctx);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitFunc(BlueParser::FuncContext *ctx)
{
    string func_name = ctx->func_name()->IDENTIFIER()->toString();
    string type_name;
    if(ctx->type_id() != NULL)
    	type_name = ctx->type_id()->IDENTIFIER()->toString();
    else
    	type_name = "void";

    string type_indicator;

    if (type_name == "Integer")
    {
        type = Predefined::integer_type;
        type_indicator = "I";
    }
    else if (type_name == "Float")
    {
        type = Predefined::real_type;
        type_indicator = "F";
    }
    else if (type_name == "Boolean")
    {
        type = Predefined::boolean_type;
        type_indicator = "Z";
    }
    else if (type_name == "void")
    {
    	type_indicator = "V";
    }
    else
    {
    	type = nullptr;
		type_indicator = "?";
    }


    SymTabEntry *func_id;// = SymTabFactory::create_symtab_stack();
    func_id = symtab_stack->enter_local(func_name);
    func_id->set_definition((Definition)DF_FUNCTION);
    func_id->set_attribute((SymTabKey) ROUTINE_SYMTAB,
                              symtab_stack->push());
    if(type_indicator != "V")
    	func_id->set_typespec(type);

    variable_func_list.resize(0);



    j_file << ".method private static " + func_name + "(";

    //symtab_stack->set_program_id(func_id);

    //cout << "Enter function " << symtab_stack->get_current_nesting_level() << endl;

    auto value = visit(ctx->func_name());

    if(ctx->param_list() != NULL)
     value = visit(ctx->param_list());

    j_file << ")" << type_indicator << endl << endl;

    //cout << "Enter function " << symtab_stack->get_current_nesting_level() << endl;

    value = visit(ctx->func_block());

//    cout << "Enter function " << symtab_stack->get_current_nesting_level() << endl;

    if(ctx->func_ret() != NULL)
    {
    	value = visit(ctx->func_ret());
    	j_file << "\t" << (char)tolower(type_indicator[0]) << "return" << endl;
    }
    else
    	j_file << "\treturn" << endl;

    j_file << "\n\n.limit stack 10" << endl;
    j_file << ".limit locals 10" << endl;
    j_file << ".end method" << endl;
    symtab_stack->pop();

    //cout << "========> FUNCTION\n";

    return value;
}

antlrcpp::Any Pass1Visitor::visitPrintf(BlueParser::PrintfContext *ctx)
{

	if(symtab_stack->get_current_nesting_level() == 1)
		return visitChildren(ctx);

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

	return value;
}

antlrcpp::Any Pass1Visitor::visitFunc_ret(BlueParser::Func_retContext *ctx)
{

    string variable_name = ctx->variable()->IDENTIFIER()->toString();

	string type_indicator =
				  (type == Predefined::integer_type) ? "I"
				: (type == Predefined::real_type)    ? "F"
				:                                      "?";

    if(symtab_stack->get_current_nesting_level() == 2)
    {
    	for(int i = 0; i < variable_func_list.size(); i++)
    	{
    		if(variable_func_list[i] == variable_name)
    		{

    			j_file << "\t" << (char)tolower(type_indicator[0]) << "load_" << i << endl;
    		}
    	}
    }

    return visitChildren(ctx);
}

antlrcpp::Any Pass1Visitor::visitParam(BlueParser::ParamContext *ctx)
{
    string type_name = ctx->declarations()->type_id()->IDENTIFIER()->toString();

    TypeSpec *type;


    if (type_name == "Integer")
    {
        type = Predefined::integer_type;
        type_indicator = "I";
    }
    else if (type_name == "Float")
    {
        type = Predefined::real_type;
        type_indicator = "F";
    }
    else if (type_name == "Boolean")
    {
        type = Predefined::boolean_type;
        type_indicator = "Z";
    }
    else
    {
    	type = nullptr;
		type_indicator = "?";
    }

    j_file << type_indicator;

    return visitChildren(ctx);
}



/////////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitDeclarationList(BlueParser::DeclarationListContext *ctx)
{
    auto value = visitChildren(ctx);

    if(symtab_stack->get_current_nesting_level() == 2)
    	return value;

    // Emit the class constructor.
    j_file << endl << endl;
    j_file << ".method public <init>()V" << endl;
    j_file << endl;
    j_file << "\taload_0" << endl;
    j_file << "\tinvokenonvirtual    java/lang/Object/<init>()V" << endl;
    j_file << "\treturn" << endl;
    j_file << endl;
    j_file << ".limit locals 1" << endl;
    j_file << ".limit stack 1" << endl;
    j_file << ".end method" << endl << endl << endl;

    return value;
}

antlrcpp::Any Pass1Visitor::visitAssignment_stmt(BlueParser::Assignment_stmtContext *ctx)
{
	//cout << "==================Assignment " << ctx->getText() << endl;

    auto value = visit(ctx->expr());




    string variable_name = ctx->variable()->IDENTIFIER()->toString();

    SymTabEntry *variable = symtab_stack->lookup(variable_name);

	string type_indicator =
				  (ctx->expr()->type == Predefined::integer_type) ? "Integer"
				: (ctx->expr()->type == Predefined::real_type)    ? "Float"
				:                                                   "?";

	type = ctx->expr()->type;
	if(variable->get_typespec() != type)
	{
		cout << "Error: " << variable_name << " variable doesn't match type " << type_indicator << endl;
		errorCount++;
	}

    if(symtab_stack->get_current_nesting_level() == 2)
    {
    	for(int i = 0; i < variable_func_list.size(); i++)
    	{
    		if(variable_func_list[i] == variable_name)
    		{
    			j_file << "\t" << (char)tolower(type_indicator[0]) << "store_" << i << endl;
    		}
    	}
    }

    return value;
}


/////////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitDeclarations(BlueParser::DeclarationsContext *ctx)
{
    //cout << "=== visitDeclarations: " << ctx->getText() << endl;


	//j_file << "\n; " << ctx->getText() << "\n" << endl;

    auto value = visitChildren(ctx);

    // Emit the class constructor.

    return value;
}


////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitVar_list(BlueParser::Var_listContext *ctx)
{
//    cout << "=== visitVarList: " + ctx->getText() << endl;

//	if(symtab_stack->get_current_nesting_level() == 1)
	variable_id_list.resize(0);
//	else if(symtab_stack->get_current_nesting_level() == 2)
//		variable_func_list.resize(0);


    auto value = visitChildren(ctx);


    for (SymTabEntry *id : variable_id_list) {
        id->set_typespec(type);

        // Emit a field declaration.
        if(symtab_stack->get_current_nesting_level() == 1)
        	j_file << ".field private static " << id->get_name() << " " << type_indicator << endl;
    }

    //cout << "Varlist\n";

    return value;
}


///////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitVar_id(BlueParser::Var_idContext *ctx)
{
    //cout << "=== visitVarId: " + ctx->getText() << endl;

    string variable_name = ctx->IDENTIFIER()->toString();
    SymTabEntry *variable_id = symtab_stack->enter_local(variable_name);
    variable_id->set_definition((Definition) DF_VARIABLE);
    variable_id_list.push_back(variable_id);
    if(symtab_stack->get_current_nesting_level() == 2)
    	variable_func_list.push_back(variable_name);

    return visitChildren(ctx);
}

//////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitType_id(BlueParser::Type_idContext *ctx)
{
//    cout << "=== visitTypeId: " + ctx->getText() << endl;


    string type_name = ctx->IDENTIFIER()->toString();

    if (type_name == "Integer")
    {
        type = Predefined::integer_type;
        type_indicator = "I";
    }
    else if (type_name == "Float")
    {
        type = Predefined::real_type;
        type_indicator = "F";
    }
    else if (type_name == "Boolean")
    {
        type = Predefined::boolean_type;
        type_indicator = "Z";
    }
    else
    {
    	type = nullptr;
		type_indicator = "?";
    }

    return visitChildren(ctx);
}

/////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitAddSubExpr(BlueParser::AddSubExprContext *ctx)
{
    //cout << "=== visitAddSubExpr: " + ctx->getText() << endl;

    auto value = visitChildren(ctx);

    TypeSpec *type1 = ctx->expr(0)->type;
    TypeSpec *type2 = ctx->expr(1)->type;

    bool integer_mode =    (type1 == Predefined::integer_type)
                        && (type2 == Predefined::integer_type);
    bool real_mode    =    (type1 == Predefined::real_type)
                        && (type2 == Predefined::real_type);

    TypeSpec *type = integer_mode ? Predefined::integer_type
                   : real_mode    ? Predefined::real_type
                   :                nullptr;
    ctx->type = type;

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

	if(opcode == "????")
	{
		cout << "Error: " << " variables don't match type" << endl;
		errorCount++;
	}

	// Emit an add or subtract instruction.
	if(symtab_stack->get_current_nesting_level() == 2)
		j_file << "\t" << opcode << endl;



    return value;
}

antlrcpp::Any Pass1Visitor::visitWhen_stmt(BlueParser::When_stmtContext *ctx)
{

    auto value = visitChildren(ctx);
    if(symtab_stack->get_current_nesting_level() == 1) return value;
    j_file << endl << "L00" << lableNumber << ":" << endl << endl;


    return value;
}

antlrcpp::Any Pass1Visitor::visitLoop_stmt(BlueParser::Loop_stmtContext *ctx)
{
	int temp;
	if(symtab_stack->get_current_nesting_level() == 2)
	{
		temp = (++lableNumber)++;
		j_file << endl << "L00" << temp << ":" << endl << endl;
		j_file << endl << "; " + ctx->getText() << endl << endl;
	}
	auto value = visitChildren(ctx);

	if(symtab_stack->get_current_nesting_level() == 2)
	{
		j_file << endl << "\tgoto\tL00" << temp << endl << endl;
		j_file << endl << "L00" << lableNumber << ":" << endl << endl;
	}

    return value;
}


/////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitMulDivExpr(BlueParser::MulDivExprContext *ctx)
{
//    cout << "=== visitMulDivExpr: " + ctx->getText() << endl;

    auto value = visitChildren(ctx);

    TypeSpec *type1 = ctx->expr(0)->type;
    TypeSpec *type2 = ctx->expr(1)->type;

    bool integer_mode =    (type1 == Predefined::integer_type)
                        && (type2 == Predefined::integer_type);
    bool real_mode    =    (type1 == Predefined::real_type)
                        && (type2 == Predefined::real_type);

    TypeSpec *type = integer_mode ? Predefined::integer_type
                   : real_mode    ? Predefined::real_type
                   :                nullptr;
    ctx->type = type;

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

	if(opcode == "????")
	{
		cout << "Error: " << " variables don't match type" << endl;
		errorCount++;
	}

	// Emit a multiply or divide instruction.
	if(symtab_stack->get_current_nesting_level() == 2)
		j_file << "\t" << opcode << endl;


    return value;
}

antlrcpp::Any Pass1Visitor::visitRelExpr(BlueParser::RelExprContext *ctx)
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

	if(opcode == "????")
	{
		cout << "Error: " << " variables don't match type" << endl;
		errorCount++;
	}

    // Emit an add or subtract instruction.
    if(symtab_stack->get_current_nesting_level() == 1) return value;

    j_file << "\t" << opcode << "\tL00" << lableNumber++ <<endl;
    j_file << "\ticonst_0" << endl;
    j_file << "\tgoto\tL00" << lableNumber << endl;
    j_file << "L00" << lableNumber-1 << ":" << endl;
    j_file << "\ticonst_1" << endl;
    j_file << "L00" << lableNumber << ":" << endl;
    j_file << "\tifeq\tL00" << ++lableNumber << endl;

    return value;
}


//////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitIdentifier(BlueParser::IdentifierContext *ctx)
{
    //cout << "=== visitVariableExpr: " + ctx->getText() << endl;

    string variable_name = ctx->variable()->IDENTIFIER()->toString();
    name = variable_name;
    SymTabEntry *variable_id = symtab_stack->lookup(variable_name);

    SymTabEntry *check = symtab_stack->lookup_local(variable_name);




    ctx->type = variable_id->get_typespec();
    TypeSpec *type = ctx->type;


    string type_indicator = (type == Predefined::integer_type) ? "I"
                          : (type == Predefined::real_type)    ? "F"
                          :                                      "?";

    if(symtab_stack->get_current_nesting_level() == 1) return 0;

    if(symtab_stack->get_current_nesting_level() == 2 && check != nullptr)
    {
    	for(int i = 0; i < variable_func_list.size(); i++)
    	{
    		if(variable_func_list[i] == variable_name)
    		{
    			j_file << "\t" << (char)tolower(type_indicator[0]) << "load_" << i << endl;
    		}
    	}
    }
    else
    {
		j_file << "\tgetstatic\t  " << program_name
			   << "/" << variable_name << " " << type_indicator << endl;
    }

    //cout << variable_name << endl;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitSignedNumberExpr(BlueParser::SignedNumberExprContext *ctx)
{
//    cout << "=== visitSignedNumberExpr: " + ctx->getText() << endl;

    auto value = visitChildren(ctx);
    ctx->type = ctx->signedNumber()->type;
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitSignedNumber(BlueParser::SignedNumberContext *ctx)
{
//    cout << "=== visitSignedNumber: " + ctx->getText() << endl;

    auto value = visit(ctx->number());
    ctx->type = ctx->number()->type;
	TypeSpec *type = ctx->number()->type;

	if (ctx->sign()->children[0] == ctx->sign()->SUB_operation() && symtab_stack->get_current_nesting_level() == 2)
	{
		string opcode = (type == Predefined::integer_type) ? "ineg"
					  : (type == Predefined::real_type)    ? "fneg"
					  :                                      "?neg";

		// Emit a negate instruction.
		j_file << "\t" << opcode << endl;
	}

    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitUnsignedNumberExpr(BlueParser::UnsignedNumberExprContext *ctx)
{
//    cout << "=== visitUnsignedNumberExpr: " + ctx->getText() << endl;

    auto value = visit(ctx->number());
    ctx->type = ctx->number()->type;
    return value;
}

////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitIntegerConst(BlueParser::IntegerConstContext *ctx)
{
//    cout << "=== visitIntegerConst: " + ctx->getText() << endl;

    ctx->type = Predefined::integer_type;
    if(symtab_stack->get_current_nesting_level() == 2)
    	j_file << "\tldc\t" << ctx->getText() << endl;

    return visitChildren(ctx);
}

//////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitFloatConst(BlueParser::FloatConstContext *ctx)
{
//    cout << "=== visitFloatConst: " + ctx->getText() << endl;

    ctx->type = Predefined::real_type;
    if(symtab_stack->get_current_nesting_level() == 2)
    	j_file << "\tldc\t" << ctx->getText() << endl;

    return visitChildren(ctx);
}

////////////////////////////////////////////////////////////////////////////////////////////
antlrcpp::Any Pass1Visitor::visitParens(BlueParser::ParensContext *ctx)
{
 //   cout << "=== visitParenExpr: " + ctx->getText() << endl;

    auto value = visitChildren(ctx);
    ctx->type = ctx->expr()->type;
    return value;
}


