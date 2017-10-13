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
#include <fstream>
#include <deque>
#include <boost/filesystem.hpp>

#include "CATSMAT_processing.h"

#include "CATSMAT_dyad_sequences.h"
// #include "CATSMAT_dyadtuple_sequences.hpp"
#include "CATSMAT_sonority_sequences.h"
#include "CATSMAT_score_profile.h"
#include "CATSMAT_TrigramSequences.h"
#include "CATSMAT_TrigramSuffixTreeBuilder.h"
#include "CATSMAT_canonic_techniques_tools.h"
#include "CATSMAT_scoredata.h"
#include "VectorMapAnalysisTypes.h"

using namespace std;
using namespace boost;
using namespace boost::filesystem;


namespace CATSMAT
{

    void
    CATSMAT_processing::
    processRelativeDirectoryFiles(const string& directory)
    {
        filesystem::path full_path(filesystem::initial_path());

        full_path = filesystem::system_complete( filesystem::path(directory) );

        if (!filesystem::exists( full_path ))
        {
            cerr << full_path << " not found." << endl << endl; //needs to throw
        }
        else if (filesystem::is_directory( full_path ) )
        {
            processDirectoryFiles(full_path);
            cout << "Data files loaded into memory." << endl << endl;
        }
    }

    S_IMUSANT_score
    CATSMAT_processing::
    addRelativeFile(const string& filename)
    {
        filesystem::path full_path(filesystem::initial_path());
        IMUSANT::S_IMUSANT_score score;

        if (!filename.empty())
        {
            cout << "Adding a single file: " << filename.c_str() << endl;
            full_path = filesystem::system_complete( filesystem::path(filename) );

            if (!filesystem::exists( full_path ))
            {
                cerr << full_path << " not found." << endl << endl; //needs to throw
            }
            else if (!filesystem::is_directory( full_path ) )
            {
                score = addFile(full_path);
                cout << "Added " << full_path << endl << endl;
            }
        }

        return score;
    }

    void
    CATSMAT_processing::
    addFilesFromFixedConfigFile()
    {
        boost::filesystem::path config_file = getHomeDirectory();

        config_file /= FIXED_CONFIG_FILE_NAME;

        addFilesFromConfigFile(config_file);
    }

    void
    CATSMAT_processing::
    addFilesFromConfigFile(boost::filesystem::path config_file)
    {
        vector<string> files = getContentsOfConfigurationFile(config_file);
        vector<string>::iterator it;

        for(it = files.begin(); it < files.end(); it++)
        {
            cout << " Adding: " << *it << "...";
            try
            {
                addFile(*it);
            }
            catch (std::exception& e)
            {
                cout << e.what() << endl;
            }
            catch (...)
            {
                cout << "ERROR processing file." << endl;
            }
            cout << "...done" << endl;
        }
    }

    //  ******* UTILITY FUNCTIONS *******

    boost::filesystem::path
    CATSMAT_processing::
    getHomeDirectory()
    {
        char * home_dir = NULL;
        home_dir = getenv(HOME_DIR_ENV_VAR_NAME);
        if (home_dir == NULL)
        {
            cerr << "No $HOME directory set.  Cannot read configuration.";
        }

        string home_dir_str(home_dir);
        boost::filesystem::path home_dir_path(home_dir_str);
        return home_dir_path;

    }

    vector<string>
    CATSMAT_processing::
    getContentsOfConfigurationFile(boost::filesystem::path full_path)
    {
        vector<string> ret_val;
        string next_line;
        std::ifstream input_stream;

        //  0427 569 018

        input_stream.open(full_path.string());
        if (! input_stream.good())
        {
            cerr << "Error opening configuration file: " << full_path << endl;
            input_stream.close();
            return ret_val;
        }

        while (getline(input_stream, next_line))
        {
            if (! next_line.empty())
            {
                ret_val.push_back(next_line);
            }
        }

        input_stream.close();
        return ret_val;
    }


    map<int, boost::filesystem::path>
    CATSMAT_processing::
    getConfigurationFiles()
    {
        map<int, boost::filesystem::path> ret_val;

        boost::filesystem::path config_dir(getHomeDirectory());
        config_dir /= CONFIG_FILE_DIR;

        directory_iterator end_iter;
        int file_index = 1;
        for(directory_iterator dir_iter(config_dir) ; dir_iter != end_iter ; ++dir_iter)
        {
            if (is_regular_file(dir_iter->status()) )
            {
                // cout << "ADDING [" << file_index << ", " << dir_iter->path().string() << "]" << endl;
                ret_val.insert(std::pair<int,boost::filesystem::path>(file_index++,*dir_iter) );
            }
        }
        return ret_val;
    }

    //==

    void
    CATSMAT_processing::
    FindRepeatedDyadSequences(int min, bool ignoreDissonances, bool ignoreRepeatedDyads, bool across)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor  score_to_matrix_translator;
            CATSMAT_dyad_sequences      dyads;
            
            //set internal parameters called within search functions
            dyads.set_ignore_dissonances(ignoreDissonances);
            dyads.set_ignore_repeated(ignoreRepeatedDyads);
            
            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                score_to_matrix_translator.getCPMatrix()->Accept(dyads);
                
                cout << "Repeated dyad sequences for each voice pair in " << (*score).getMovementTitle() << endl;
                if (across)
                    dyads.FindRepeatedAcross(min);
                else
                    dyads.FindRepeatedIn(min);
            }
            
        }
    }
    
    void
    CATSMAT_processing::
    FindRepeatedSonoritySequences(int min)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_sonority_sequences      sonorities;
            
            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                score_to_matrix_translator.getCPMatrix()->Accept(sonorities);
                
                cout << "Repeated dyad sequences in " << (*score).getMovementTitle() << endl;
                sonorities.find_repeated(min);
            }
            
        }

    }
    
    void
    CATSMAT_processing::FindRepeatedTrigramSequences(int min, bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_TrigramSequences        trigram_sequences;
            trigram_sequences.set_ignore_dissonances(ignoreDissonances);
            trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
            
            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                if (!score_to_matrix_translator.getCPMatrix()->SelfTest())
                    catsmat_runtime_error("Problem in CP Matrix for " + score->getWorkTitle());
                score_to_matrix_translator.getCPMatrix()->Accept(trigram_sequences);
                CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
                trigram_sequences.Accept(trigram_tree);
                cout << "Repeated trigram sequences in " << (*score).getMovementTitle() << endl;
                cout << trigram_tree.FindAndPrintRepeatedSubstrings().c_str();
            }
            
        }
    }
    
    //This method identifies canonic parts only, places them in a CP matrix and then looks for repeated sequences of trigrams
    void
    CATSMAT_processing::
    FindRepeatedTrigramSequencesCanonic(int min, bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        for (auto score : this->getScores())
        {
            S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
            tools->Initialise(score);
            for (auto canon : tools->GetCanonTypes())
            {
                CATSMAT_TrigramSequences        trigram_sequences;
                S_CATSMAT_cp_matrix matrix = new_CATSMAT_object<CATSMAT_cp_matrix>();
                
                trigram_sequences.set_ignore_dissonances(ignoreDissonances);
                trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
                
                for (auto part : canon.parts_)
                    matrix->add(part);
                matrix->Accept(trigram_sequences);
                CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
                trigram_sequences.Accept(trigram_tree);
                cout << "Repeated trigram sequences in " << (*score).getMovementTitle() << endl;
                cout << trigram_tree.FindAndPrintRepeatedSubstrings().c_str();
            }
        }
    }

    //This method compares pairs of trigram sequences across a score, ie. trigrams over three voices
    void
    CATSMAT_processing::
    FindRepeatedTrigramSequencesThreeVoices(int min, bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_TrigramSequences        trigram_sequences;
            trigram_sequences.set_ignore_dissonances(ignoreDissonances);
            trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);

            if (score!=NULL)
            {
                (*score).accept(score_to_matrix_translator);
                if (!score_to_matrix_translator.getCPMatrix()->SelfTest())
                    catsmat_runtime_error("Problem in CP Matrix for " + score->getWorkTitle());
                score_to_matrix_translator.getCPMatrix()->Accept(trigram_sequences);

                for (auto trigram_sequence : trigram_sequences.get_tokens())
                {

                }

                //CATSMAT_TrigramSuffixTreeBuilder trigram_tree;
                //trigram_sequences.Accept(trigram_tree);
                //cout << "Repeated trigram sequences in " << (*score).getMovementTitle() << endl;
                //cout << trigram_tree.FindAndPrintRepeatedSubstrings().c_str();
            }
        }

    }

    //This method counts trigrams in a score
    void
    CATSMAT_processing::
    FindTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_TrigramSequences        trigram_sequences;
            CATSMAT_TrigramInformation      trigram_info;
            trigram_sequences.set_ignore_dissonances(ignoreDissonances);
            trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
            
            score->accept(score_to_matrix_translator);
            score_to_matrix_translator.getCPMatrix()->Accept(trigram_sequences);
            trigram_sequences.Accept(trigram_info);
            
            cout << "Trigram counts in " << (*score).getMovementTitle() << endl;
            cout << trigram_info;
        }
    }
    
    /*!
     \fn CATSMAT_processing::FindSummativeTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads)
     
     \brief returns a table that collects all results from multiple scores
     
     */
    void
    CATSMAT_processing::
    FindSummativeTrigramCounts(bool ignoreDissonances, bool ignoreRepeatedDyads)
    {
        CATSMAT_score_profile<CATSMAT_TrigramSequences::Token> trigrams_profile("trigrams");
        
        for (auto score : this->getScores())
        {
            CATSMAT_collection_visitor      score_to_matrix_translator;
            CATSMAT_TrigramSequences        trigram_sequences;
            CATSMAT_TrigramInformation      trigram_info;
            
            trigram_sequences.set_ignore_dissonances(ignoreDissonances);
            trigram_sequences.set_ignore_repeated(ignoreRepeatedDyads);
            score->accept(score_to_matrix_translator);
            score_to_matrix_translator.getCPMatrix()->Accept(trigram_sequences);
            trigram_sequences.Accept(trigram_info);
            CATSMAT_TrigramInformation::PROFILE score_tokens_by_count = trigram_info.token_count();
            string part_name = score->getWorkTitle();
            if (part_name.empty())
            {
                part_name = score->getMovementTitle();
                if (part_name.empty()) throw catsmat_runtime_error("The work or movement lacks a name");
            }
            trigrams_profile.Accumulate(part_name, score_tokens_by_count);
        }
        
        cout << "Printing trigram table for inputed scores" << endl;
        
        cout << trigrams_profile;
        
    }
    
    /*!
     \fn CATSMAT_processing::FindMelodicDirectionCounts()
     
     \brief returns a table that collects all results from multiple scores
     
     */
    void
    CATSMAT_processing::
    FindMelodicDirectionCounts()
    {
        CATSMAT_score_profile<IMUSANT_contour_symbol> profiles("contours");
        
        for (auto score : this->getScores())
        {
            S_CATSMAT_scoredata                 scoredata = new_CATSMAT_object<CATSMAT_scoredata>();
            ContourVectorMapAnalysis    cv_map;
            
            scoredata->findBasicDataFromScore(score);
            CATSMAT_score_profile<IMUSANT_contour_symbol> score_profile = scoredata->score_contour_symbol_profile();
            string part_name = score->getWorkTitle();
            if (part_name.empty())
            {
                part_name = score->getMovementTitle();
                if (part_name.empty()) throw catsmat_runtime_error("The work or movement lacks a name");
            }
            profiles.Accumulate(part_name, score_profile.profile());
        }
        
        cout << "Printing trigram table for inputed scores" << endl;
        
        cout << profiles;
        
    }
    
    void
    CATSMAT_processing::
    FindMelodicDirectionDupleCounts()
    {
        //IMUSANT_ContourVectorMapAnalysis   cv;
        //cv.Visit(*this);
        //cout << cv.EntabulateAndPrintMelodicDirectionPairs();
        
        CATSMAT_score_profile<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol> > profiles("contour duples");
        
        for (auto score : this->getScores())
        {
            S_CATSMAT_scoredata                 scoredata = new_CATSMAT_object<CATSMAT_scoredata>();
            ContourDupleVectorMapAnalysis    cv_map;
            
            scoredata->findBasicDataFromScore(score);
            CATSMAT_score_profile<std::pair<IMUSANT_contour_symbol, IMUSANT_contour_symbol> > score_profile = scoredata->score_contour_symbol_duple_profile();
            string part_name = score->getWorkTitle();
            if (part_name.empty())
            {
                part_name = score->getMovementTitle();
                if (part_name.empty()) throw catsmat_runtime_error("The work or movement lacks a name");
            }
            profiles.Accumulate(part_name, score_profile.profile());
        }
        
        cout << "Printing trigram table for inputed scores" << endl;
        
        cout << profiles;

        
    }
    
    void
    CATSMAT_processing::
    ListCanonicTechniques()
    {
        for (auto score : this->getScores())
        {
            S_CATSMAT_CanonicTechniquesTools tools = new_CATSMAT_object<CATSMAT_CanonicTechniquesTools>();
            
            tools->Initialise(score);
        
            for ( auto type : tools->GetCanonTypes())
            {
                cout << type;
            }
            
        }
    }

} //namespace CATSMAT
