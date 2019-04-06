/* Copyright (c) 2012-2017 The ANTLR Project. All rights reserved.
 * Use of this file is governed by the BSD 3-clause license that
 * can be found in the LICENSE.txt file in the project root.
 */
//
//  Created by Mike Lischke on 13.03.16.
//
#include <iostream>
#include <fstream>

#include "antlr4-runtime.h"
#include "BlueLexer.h"
#include "BlueParser.h"
#include "Pass1Visitor.h"
#include "Pass2Visitor.h"

using namespace antlrcpp;
using namespace antlr4;
using namespace std;

int main(int, const char **)
{
	//cout << "L48484L";
    ifstream ins;

    ins.open("sample.bl");

    ANTLRInputStream input(ins);
    BlueLexer lexer(&input);
    CommonTokenStream tokens(&lexer);




    BlueParser parser(&tokens);
    tree::ParseTree *tree = parser.program();

	Pass1Visitor *pass1 = new Pass1Visitor();
	pass1->visit(tree);
	ostream& j_file = pass1->get_assembly_file();

	if(pass1->getErrorCount() != 0)
	{
		cout << pass1->getErrorCount() << " Errors\nFile Terminated\n";
	}

	Pass2Visitor *pass2 = new Pass2Visitor(j_file, pass1->getLableNumber());
	pass2->visit(tree);


    //cout << endl << "Parse tree (Lisp format):" << endl;
    //std::cout << tree->toStringTree(&parser) << endl;


	//delete tree;

    return 0;
}
