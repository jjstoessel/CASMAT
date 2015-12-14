/*
 *  CATSMAT_processing.cpp
 *  catsmat
 *
 *  Created by Jason Stoessel on 12/03/15.
 *  Copyright 2015 the programmers. All rights reserved.
 *
 *  A file processing class for CATSMAT.
 */
#include <iostream>
#include <deque>
#include <boost/filesystem.hpp>

#include "CATSMAT_processing.hpp"
#include "TMusicXMLFile.h"
#include "IMUSANT_XMLFile.h"
#include "TXML2IMUSANTVisitor.h"
#include "IMUSANT_XMLVisitor.h"
#include "IMUSANT_XMLReader.h"
#include "TScore.h"
#include "CATSMAT_dyad_sequences.hpp"
#include "CATSMAT_dyadtuple_sequences.hpp"
#include "CATSMAT_sonority_sequences.hpp"

#define MAX(X,Y) ( (X>Y)? (X) : (Y) )

using namespace std;
using namespace boost;

namespace CATSMAT
{
    
    void
    CATSMAT_processing::
    process_directory_files(const filesystem::path& full_path)
    {
        if (filesystem::is_directory( full_path ) )
        {
            filesystem::directory_iterator end;
            for (	filesystem::directory_iterator iter(full_path);
                 iter != end;
                 ++iter )
            {
                add_file(*iter);
            }
        }
    }
    
    //   REVISIT
    //   ADD TESTS FOR THE FOLLOWING
    ////                //Here only for testing; could be placed in test unit or specific tool
    ////                CATSMAT_dyad_sequences dyads;
    ////                CATSMAT_dyadtuple_sequences tuples;
    ////                CATSMAT_sonority_sequences   sonorities;
    ////
    ////                collections[i].getCPMatrix()->Accept(dyads);
    ////                //collections[i].getCPMatrix()->Accept(tuples);
    ////                collections[i].getCPMatrix()->Accept(sonorities);
    ////                //cout << collections[i].getCPMatrix();
    ////
    ////                cout << dyads;
    ////
    ////                dyads.find_repeated(4);
    ////                sonorities.find_repeated(4);
    //
    //                
    //                //cout << tuples;
    //                
    //                //tuples.find_repeated_tuplet_sequences(3);
    //                
    
    
} //namespace CATSMAT