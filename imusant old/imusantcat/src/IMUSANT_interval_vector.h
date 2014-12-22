/*
 *  IMUSANT_interval_vector.h
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 *	A _sequence_ of intervals
 */
 
#ifndef __IMUSANT_INTERVAL_VECTOR__
#define __IMUSANT_INTERVAL_VECTOR__

#include "smartpointer.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_record.h"

#include <vector>

namespace IMUSANT
{

class IMUSANT_interval_vector : public smartable
{
	public:
	
		friend SMARTP<IMUSANT_interval_vector> new_IMUSANT_interval_vector();
		
		void	setMinimum(long min) { fMinimumIntervals=min; fIntervals.reserve(min); }
		void	setMaximum(long max) { fMaximumIntervals=max; }
		//add element if space, returns false if full - handled by collection
		bool	add(const IMUSANT_interval& interval);
		void	clear() { fIntervals.clear(); }
		long	intervalCount() { return fIntervals.size(); }
		void	pop_front() { fIntervals.erase(fIntervals.begin()); }
		const vector<IMUSANT_interval>& getIntervals() const { return fIntervals; }
		const vector<S_IMUSANT_record>&	getRecords() const { return fRecords; }
		
		void print(ostream& os);
		
		friend ostream& operator<< (ostream& os, const SMARTP<IMUSANT_interval_vector>& elt );
		
	protected:
	
				IMUSANT_interval_vector();
		virtual ~IMUSANT_interval_vector() {}
		
	private:
	//a vector of intervals
	vector<IMUSANT_interval>	fIntervals;
	//records of location of interval
	vector<S_IMUSANT_record>	fRecords;
	
	long	fMinimumIntervals;
	long	fMaximumIntervals;
	
};
typedef SMARTP<IMUSANT_interval_vector> S_IMUSANT_interval_vector;
    
S_IMUSANT_interval_vector new_IMUSANT_interval_vector();

} //namespace IMUSANT
#endif