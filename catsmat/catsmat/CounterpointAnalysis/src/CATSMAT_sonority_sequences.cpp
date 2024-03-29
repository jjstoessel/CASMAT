//
//  CATSMAT_sonority_sequences.cpp
//  imusant
//
//  Created by Jason Stoessel on 29/06/2015.
//
//

#include "CATSMAT_sonority_sequences.h"
#include "CATSMAT_t_utilities.h"
#include <map>

namespace CATSMAT
{

    sonority& sonority::operator=(const sonority& r)
    {
        this->setQuality(r.getQuality());
        this->setLocation(r.getMeasure(), r.getIndex());
        return *this;
    }

    signed int
    sonority::compare(const sonority& i) const
    {
        return (signed int)this->mQuality-(signed int)i.getQuality();
    }

    void
    sonority::print(ostream& os) const
    {
        os << "(" << mMeasure << ", " << mIndex << ", " << mDuration << ", " << mQuality << ")" << endl;
    }

    ostream& operator<< (ostream& os, const sonority& elt )
    {
        elt.print(os);
        
        return os;
    }

    ostream& operator<<(ostream& os, const CATSMAT_sonority_sequences& sequences)
    {
        sequences.Print(os);
        
        return os;
    }
    
    void CATSMAT_sonority_sequences::Visit(CATSMAT_cp_matrix& matrix)
    {
        if (!matrix.getCPmatrix().empty())
        {
            for (list<S_CATSMAT_chord>::const_iterator chord = matrix.getCPmatrix().begin(); chord!=matrix.getCPmatrix().end(); chord++)
            {
                //make a sorted copy of the chord by reversing key and value in templated utility
                S_CATSMAT_chord the_chord = *chord;
                multimap<S_IMUSANT_note, int> flipped_chord = flip_map(*the_chord);
                //insert in order (lowest to highest) in a new multimap, using custom compare function
                multimap<S_IMUSANT_note, int, IMUSANT_note::less_than> sorted_chord;
                for ( auto i : flipped_chord)
                {
                    sorted_chord.insert(i);
                }
                
                //storage for calculated sonority
                sonority* s = new sonority();
                //get lowest note and calculate all intervals with respect to it
                auto bass = sorted_chord.begin();
                //ensure bass is a note
                while (bass->first->getType()==IMUSANT_NoteType::rest) bass++;
                s->setDuration(bass->first->duration()->AsAbsoluteNumeric());
                
                auto note = bass;
                for (note++;
                     note != sorted_chord.end();
                     note++)
                {
                    //chord (or sonority) quality is ORing interval quality so that
                    //all perfect | perfect = 1; imperfect | imperfect = 2; perfect | imperfect = 3;  imperfect | dissonance = 4; perfect | disonance = 5; imperfect | dissonance = 6, and Perf|Imp|Dis = 7
                    //this functionality needs to be moved soon to chord
                    //an interval is between two notes!
                    if (note->first->getType()!=IMUSANT_NoteType::rest)
                    {
                        IMUSANT_interval interval(note->first->pitch(), bass->first->pitch());
                        s->setQuality(s->getQuality() | interval.getQuality());
                        s->setLocation(bass->first->getMeasureNum(),  bass->first->getNoteIndex());
                    }
                   
                }
            
                //only add sonority if it has a quality
                //NB. chord_quality.quality < 4 are consonant
                //if (s->getQuality()!=0 && s->getQuality() < 4) {
                if (s->getQuality()!=0) {
                    vectors_.push_back(*s);
                }
            }
        }

    }

    void CATSMAT_sonority_sequences::Print(ostream& os) const
    {
        os << "sonority types (measure, index, duration, sonority type): " << endl;
        
        for (auto iter1 = vectors_.begin(); iter1 != vectors_.end(); iter1++)
        {
           os << *iter1; //uses tuple print member function
        }

        cout << endl << "all perfect | perfect = 1; imperfect | imperfect = 2; perfect | imperfect = 3;  imperfect | dissonance = 4; perfect | disonance = 5; imperfect | dissonance = 6, and Perf|Imp|Dis = 7" << endl;

    }

    void CATSMAT_sonority_sequences::find_repeated(int min)
    {
        if (vectors_.size()>0)
        {
            int_tree* tree = new int_tree(vectors_,1); //change last parameter to id for whole work tree.
            vector<pair<int_tree::size_type, int_tree::size_type> >* results = new vector<pair<int_tree::size_type, int_tree::size_type> >();
            
            find_repeated_substrings(*results, tree->root_node(), min);
            
            map<int, int_tree::value_type > m = tree->get_sentences();
            int_tree::value_type int_v = m[1];
            
            for (auto j=results->begin(); j!=results->end(); j++)
            {
                cout << "Sequence: (";
                
                cout << int_v[j->first].getMeasure();
                cout << ", " << int_v[j->first].getIndex() << ") ";
                
                for (auto k = j->first; k<j->second+j->first; k++)
                {
                    cout << int_v[k].getQuality();
                }
                cout << endl;
            }
            
            delete results;
            delete tree;
        }

    }

    //private recursive function - needs to be templated into a base class
    void CATSMAT_sonority_sequences::find_repeated_substrings(vector< pair<int_tree::size_type, int_tree::size_type> >& results, const int_tree::node& n, int min_length)
    {
        int_tree::size_type prefix_length = n.path_label_length() - (n.end() - n.begin());
        
        if (n.children_size()==0)
        {
            if (prefix_length>=min_length)
            {
                pair<int_tree::size_type, int_tree::size_type> res;
                res.first=n.give_number().second; //give index of vector where branch starts
                res.second=prefix_length;
                results.push_back(res);
            }
        }
        
        vector<int_tree::element_type> v = n.next_children();
        
        if (!v.empty())
        {
            for (vector<int_tree::element_type>::const_iterator it=v.begin();it!=v.end();it++)
            {
                const int_tree::node* m = n.find_child(*it);
                find_repeated_substrings(results, *m, min_length);
            }
        }
    }
}
