/*
 *  IMUSANT_record.h
 *  imusant
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __IMUSANT_RECORD__
#define __IMUSANT_RECORD__

#include <string>
#include "smartpointer.h"

using namespace std;

namespace IMUSANT
{

class IMUSANT_record : public smartable
{
	public:
	
		friend SMARTP<IMUSANT_record> new_IMUSANT_record();
		
		enum { undefined=-1 };
		
		void	setMeasureNumber(const long meas) { fStartMeasureNum = meas; }
		void	setNoteIndex(const long index) { fStartNoteIndex = index; }
		void	setMovementTitle ( const string title ) { fMovementTitle = title; }
		void	setFileName ( const string filename ) { fFileName = filename; }
		
		long	getMeasureNumber() const { return fStartMeasureNum; }
		long	getNoteIndex() const { return fStartNoteIndex; }
		const string getMovementTitle() const { return fMovementTitle; }
		const string getFileName() const { return fFileName; }
		
	protected:
				IMUSANT_record() : fMovementTitle(""), fStartMeasureNum(undefined), fStartNoteIndex(undefined) {}
		virtual ~IMUSANT_record() {}
		
	private:
	
		string	fMovementTitle;
		string	fFileName;
		long	fStartMeasureNum;
		long	fStartNoteIndex;
				
};
typedef SMARTP<IMUSANT_record> S_IMUSANT_record;

S_IMUSANT_record new_IMUSANT_record();
    
} //namespace IMUSANT
#endif
