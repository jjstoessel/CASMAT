//
//  CATSMAT_sonority_sequences.cpp
//  imusant
//
//  Created by Jason Stoessel on 29/06/2015.
//
//

#include "CATSMAT_sonority_sequences.hpp"

using namespace CATSMAT;

sonority& sonority::operator=(const sonority& r)
{
    this->quality = r.quality;
    this->measure = r.measure;
    this->index =r.index;
    return *this;
}

signed int  sonority::compare(const sonority& i) const
{
    return (signed int)this->quality-(signed int)i.quality;;
}


void CATSMAT_sonority_sequences::Visit(const CATSMAT_cp_matrix& matrix)
{
    if (!matrix.getCPmatrix().empty())
    {
        for (auto chord = matrix.getCPmatrix().begin(); chord!=matrix.getCPmatrix().end(); chord++)
        {
            (*chord)->sort(); //nb destructive; copy constructor needed in chord.
            
            sonority* chord_quality = new sonority();
            
            //find lowest not in chord which can contain rests.
            
            auto bass = (*chord)->getNotes().begin();
            
            while ( bass != (*chord)->getNotes().end() && (*bass)->getType()==IMUSANT_NoteType::rest)
            {
                bass++;
            }
            
            if (bass!=(*chord)->getNotes().end())
            {
        
                //start in the middle and move up
                for (auto note = bass+1;
                     note != (*chord)->getNotes().end();
                     note++)
                {
                    //chord (or sonority) quality is ORing interval quality so that
                    //all perfect | perfect = 1; perfect | imperfect = 3; perfect | disonance = 5; imperfect | dissonance = 6, and Perf|Imp|Dis = 7
                    //this functionality needs to be moved soon to chord
                    //an interval is between two notes!
                    if ((*note)->getType()!=IMUSANT_NoteType::rest && (*bass)->getType()!=IMUSANT_NoteType::rest )
                    {
                        IMUSANT_interval interval((*note)->pitch(), (*bass)->pitch());
                        
                        //interval.setLocation(1, (*bass)->getMeasureNum(), (*bass)->getNoteIndex(), (*note)->getMeasureNum(), (*note)->getNoteIndex());
                        
                        chord_quality->quality |= interval.getQuality();
                        chord_quality->measure = (*bass)->getMeasureNum();
                        chord_quality->index = (*bass)->getNoteIndex();
                    }
                   
                }
                
                //only add sonority if it has a quality
                //NB. chord_quality.quality < 4 are consonant
                if (chord_quality->quality!=0 && chord_quality->quality < 4) {
                    fQualityVector.push_back(*chord_quality);
                }
            }
        }
    }

}

void CATSMAT_sonority_sequences::print(ostream& os) const
{

}

void CATSMAT_sonority_sequences::find_repeated(int min)
{
    if (fQualityVector.size()>0)
    {
        
        int_tree* tree = new int_tree(fQualityVector,1); //change last parameter to id for whole work tree.
        vector<pair<int_tree::size_type, int_tree::size_type> >* results = new vector<pair<int_tree::size_type, int_tree::size_type> >();
        
        find_repeated_substrings(*results, tree->root_node(), min);
        
        map<int, int_tree::value_type > m = tree->get_sentences(); //const vector<IMUSANT_interval>& int_v = (*i)->getIntervals();
        int_tree::value_type int_v = m[1];
        
        for (auto j=results->begin(); j!=results->end(); j++)
        {
            cout << "Sequence: (";
            
            cout << int_v[j->first].measure;
            cout << ", " << int_v[j->first].index << ") ";
            
            for (auto k = j->first; k<j->second+j->first; k++)
            {
                cout << int_v[k].quality;
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
