//
//  IMUSANT_processing_Tests.cpp
//  imusant
//
//  Created by Derrick Hill on 9/08/2015.
//
//


#include <stdio.h>

#include "gtest/gtest.h"

#include "libIMUSANT.h"
#include <boost/filesystem.hpp>

using namespace IMUSANT;
using namespace boost;

// The fixture for testing class IMUSANT_pitch.
class IMUSANT_processing_Tests : public ::testing::Test {
    
protected:
    
    IMUSANT_processing_Tests()
    {
        // You can do set-up work for each test here.
    }
    
    virtual ~IMUSANT_processing_Tests()
    {
        // You can do clean-up work that doesn't throw exceptions here.
    }
    
};


TEST_F(IMUSANT_processing_Tests, SmokeTest)
{
    string relative_path = "../testdata/MusicXMLv1";

    filesystem::path testdata(filesystem::initial_path());
    testdata.append(relative_path);
    
    IMUSANT_processing *the_processor = new IMUSANT_processing();
    
    the_processor->process_directory_files(testdata);
    
    filesystem::path kyrie_xml = testdata.append("/Kyrie.xml");
    
    the_processor->add_file(kyrie_xml);
    the_processor->find_repeated_interval_substrings();
    
    ASSERT_TRUE(false) << "--------> Test not implemented yet";
    
}

