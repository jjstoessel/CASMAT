/*
 *  CATSMAT_main.cpp
 *  imusant
 *
 *  Created by Jason Stoessel on 8 March 2015.
 *  Copyright © 2015 Jason Stoessel. All rights reserved.
 *  
 *
 */
#include <iostream>

#include <boost/filesystem.hpp>

#include "CATSMAT_processing.h"
#include "CATSMAT_menu.h"


#define __DEBUG__ 0

using namespace boost;
using namespace std;
using namespace CATSMAT;

int main (int argc, char * const argv[])
{
    CATSMAT_menu the_menu;
    the_menu.outputWelcomeMessage(cout);
    
	filesystem::path full_path(filesystem::initial_path());
	CATSMAT_processing processor;
	
    the_menu.addFilesToAnalyse(&processor);
    if (!processor.getScores().empty())
     the_menu.runToolsMenu(&processor);
    
    cout << "Goodbye." << endl;

	return 0;

}


