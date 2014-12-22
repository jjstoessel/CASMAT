// (C) Copyright 2002
// Craig Henderson
//
// cdm.henderson@virgin.net
// http://homepage.virgin.net/cdm.henderson
//
// Diff.cpp

#include <stdio.h>
#include "compare.h"
#include "data_source_text_file.h"




// small test function to calculate the difference
// between two character strings
static void test_character_diff(const char * const str1, const char * const str2)
{
    // instantiate data source objects for each text string
    cmp::data_source<const char> compare_data1(str1, strlen(str1));
    cmp::data_source<const char> compare_data2(str2, strlen(str2));

    // we need to instantiate a template compare object
    // create a typedef first so that we can use a short-handed
    // version later
    typedef cmp::compare< cmp::data_source<const char> > compare_t;
    compare_t compare(&compare_data1, &compare_data2);

    size_t                lcs;
    std::string           result_str1, result_str2;
    compare_t::result_set seq;

    // process the data sources
    if ((lcs = compare.process(&seq)) != -1)
    {
        printf("Comparing: \"%s\" & \"%s\"\n"
               "Lowest Common Subsequence length is %d\n", str1, str2, lcs);

        compare_t::result_set::iterator it   = seq.begin();
        compare_t::result_set::iterator ite  = seq.end();
        for (; it != ite; ++it)
        {
            compare_t::result_set::value_type res = *it;
            if (res->type() == cmp::REMOVE)
            {
                result_str1 += res->data();
                result_str2 += '_';
            }
            else if (res->type() == cmp::INSERT)
            {
                result_str1 += '_';
                result_str2 += res->data();
            }
            else
            {
                result_str1 += res->data();
                result_str2 += res->data();
            }
        }
        seq.erase(seq.begin(), seq.end());
    }

    printf("%s\n%s\n\n", result_str1.c_str(), result_str2.c_str());
}



int main(int argc, char **argv)
{
    if (argc != 3)
    {
        fprintf(stderr, "Usage: %s file1 file2\n", argv[0]);
        return 1;
    }

    // this is the test documented by David Eppstein at
    // http://www1.ics.uci.edu/~eppstein/161/960229.html
    test_character_diff("nematode knowledge", "empty bottle");

    // other tests
    test_character_diff("little jack horner", "sat in a corner");
    test_character_diff("jack and jill went up the hill", "to fetch a pale of water");
    test_character_diff("to fetch a pale of water", "jack and jill went up the hill");

    // open the two files
    FILE *fp1, *fp2;
    fp1 = fopen(argv[1], "r");
    if (fp1 == NULL)
    {
        fprintf(stderr, "Unable to open %s\n", argv[1]);
        return 1;
    }

    fp2 = fopen(argv[2], "r");
    if (fp2 == NULL)
    {
        fprintf(stderr, "Unable to open %s\n", argv[2]);
        fclose(fp1);
        return 1;
    }

    try
    {
        // instantiate two text file data sources;one for each file
        cmp::data_source_text_file compare_data1(fp1);
        cmp::data_source_text_file compare_data2(fp2);

        // we need to instantiate a template compare object
        // create a typedef first so that we can use a short-handed
        // version later
        typedef cmp::compare<cmp::data_source_text_file> compare_t;
        compare_t compare(&compare_data1, &compare_data2);

        int lcs;
        compare_t::result_set seq;

        // process the data sources
        if ((lcs = compare.process(&seq)) != -1)
        {
            if (lcs == 0)
            {
                printf("The two files contain no identical lines.\n");
            }
            else
            {
                // loop through the result set and output the differing lines
                compare_t::result_set::iterator it  = seq.begin();
                compare_t::result_set::iterator ite = seq.end();
                for (; it != ite; ++it)
                {
                    compare_t::result_set::value_type res = *it;

                    // we ignore identical records
                    if (res->type() != cmp::KEEP)
                    {
                        if (res->type() == cmp::REMOVE)
                            printf("DEL: ");
                        else if (res->type() == cmp::INSERT)
                            printf("INS: ");
                        printf("%-3d %s", res->rec_num(), res->data().c_str());
                    }   // ! identical records
                }       // end of for-loop
            }           // lcs
        }               // compare::process
        else
            fprintf(stderr, "Comparison failed.\n");
    }
    catch(cmp::out_of_memory&)
    {
        fprintf(stderr, "Out of memory.\n");
    }

    // close the files
    fclose(fp1);
    fclose(fp2);

    return 0;
}
