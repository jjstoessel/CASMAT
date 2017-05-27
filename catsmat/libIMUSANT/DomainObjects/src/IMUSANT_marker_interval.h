//
//  IMUSANT_marker_interval.h
//  imusant
//
//  Created by Jason Stoessel on 5/05/2016.
//
//  This is a child class of IMUSANT_interval and is used to create a
//  unique polymorphic instances of an interval, specifically for providing
//  unique end markers for suffix tree strings.

#ifndef __imusant__IMUSANT_marker_interval__
#define __imusant__IMUSANT_marker_interval__

#include "IMUSANT_interval.h"

using namespace std;

namespace IMUSANT
{

    class IMUSANT_marker_interval : public IMUSANT_interval
    {
    public:
        IMUSANT_marker_interval(int iv) : IMUSANT_interval() {}
        
        static IMUSANT_marker_interval MakeUniqueInterval();        //! make a unique interval to append for suffix tree
        
        //setters
        void    setWorkTitle(const string& workTitle) { fWorkTitle = workTitle; }
        void    setMovementTitle(const string& moveTitle) { fMovementTitle = moveTitle; }
        void    setPartID(const long partID) { fPartID = partID; }
        void    setMarkerID(const int markerID) { fMarkerID = markerID; }
        
        //getters
        const string& getWorkTitle() const { return fWorkTitle; }
        const string& getMovementTitle() const { return fMovementTitle; }
        const long    getPartID() const { return fPartID; }
        int           getMarkerID() const { return fMarkerID; }
        
        //operators
        const IMUSANT_marker_interval& operator=( const IMUSANT_marker_interval& rhs );
        
    private:
        
        string  fWorkTitle;
        string  fMovementTitle;
        long    fPartID;
        int     fMarkerID;
    };

}
#include <stdio.h>

#endif /* defined(__imusant__IMUSANT_marker_interval__) */
