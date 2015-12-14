//
//  CATSMAT_Menu.h
//  imusant
//
//  Created by Derrick Hill on 6/12/2015.
//
//

#ifndef __imusant__CATSMAT_Menu__
#define __imusant__CATSMAT_Menu__

#include <stdio.h>
#include <vector>
#include <string>

#include "CATSMAT_processing.hpp"

using namespace std;

namespace CATSMAT
{
    
    class CATSMAT_menu
    {
    
    public:
        
        CATSMAT_menu() {};
        
        void runMenu();
        
        void outputWelcomeMessage(ostream &out);
        void getFilesToAnalyse(CATSMAT_processing *processor);
        void runToolsMenu(CATSMAT_processing *processor);
        
    private:
        vector<string> getConfiguredFiles(string full_path);
        void getOneFileToAnalyse(CATSMAT_processing *processor);
        void getDirectoryToAnalyse(CATSMAT_processing *processor);
        void getAllConfiguredFiles(CATSMAT_processing *processor);
        
        void outputToolsMenu(ostream &out);
        
        char readMenuSelection();
    };
    
    
    
} //namespace CATSMAT




#endif /* defined(__imusant__CATSMAT_Menu__) */
