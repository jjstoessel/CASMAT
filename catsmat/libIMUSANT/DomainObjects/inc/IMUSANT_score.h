/*
 *  IMUSANT_score.h
 *  imusant - the Intertextual MUSic ANalysis Tool
 *	Project Supervisor: Dr Rex Eakins
 *
 *  Created by Jason Stoessel on 23/05/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

/*!
\brief A IMUSANT_score representation.

	Contains internal representation of musical data.
	
*/

#ifndef __IMUSANT_score__
#define __IMUSANT_score__

#include "IMUSANT_partlist.h"
#include "IMUSANT_common.h"

using namespace std;

namespace IMUSANT
{

class IMUSANT_score;
typedef IMUSANT_SMARTP<IMUSANT_score> 	S_IMUSANT_score;

class IMUSANT_score : public smartable, public IMUSANT_visitable
{
	public:
		friend IMUSANT_SMARTP<IMUSANT_score> new_IMUSANT_score(const string& movtTitle);
		
		friend	ostream& operator<<(ostream& os, S_IMUSANT_score& score);
        
		void	accept(IMUSANT_visitor& visitor);

		//Accessors/setters
		void			setWorkTitle (const string& work) { fWorkTitle = work; }
		void			setWorkNum( const string& workNum ) { fWorkNum = workNum; }
		void			setMovementTitle(const string& movtTitle) { fMovementTitle = movtTitle; }
        void			setMovementNum(const string& movtNum) { fMovementNum = movtNum; }
		void			addCreator(const STRPAIR& creator ) { fCreator.push_back(creator); }
		// single text string for copyright information
		void			addRights(const STRPAIR& rights) { fRights.push_back(rights); }
		void			setComments(const string& comments) { fScoreComments = comments; }
		//may be any type of source, eg. MS
		void			setSource(const string& source) { fSource = source; }
		void			setEditor(const string& editor) { fEditor = editor; }
		void			setDate(const string& date) { fDate = date; }
	
		const string&	getWorkTitle() const			{ return fWorkTitle; }
        const string&	getWorkNum() const              { return fWorkNum; }
        const string& 	getMovementTitle() const		{ return fMovementTitle; }
		const string& 	getMovementNum() const          { return fMovementNum; }
		const STRPAIRVECTOR& getCreator() const         { return fCreator; }
		const STRPAIRVECTOR& getRights() const          { return fRights; }
		const string&	getComments() const             { return fScoreComments; }
		const string&	getSource() const               { return fSource; }
		const string&	getEditor() const				{ return fEditor; }
		const string&	getDate() const                 { return fDate; }
		
        bool getPartById(string partId, S_IMUSANT_part& output_part);
        S_IMUSANT_partlist& partlist() { return fPartList; }
		
		void			addPart(const S_IMUSANT_part& part) { fPartList->add(part); }
		
		void			print(ostream& os);
    
        bool operator== (const IMUSANT_score& score) const;
		
	protected:
		
				IMUSANT_score(const string& movtTitle);
		virtual	~IMUSANT_score() {}
		
	private:
		S_IMUSANT_partlist	fPartList;
		
		string				fWorkTitle;		//title of work to which movement belongs; perhaps change these to tagged pairs?
		string				fWorkNum;
		string				fMovementTitle;
		string				fMovementNum;
		STRPAIRVECTOR		fCreator;
		STRPAIRVECTOR		fRights;
		string				fScoreComments;
		string				fSource;
		string				fEditor;
		string				fDate;			//publication date; composition date?
};

	typedef IMUSANT_SMARTP<IMUSANT_score> S_IMUSANT_score;
	IMUSANT_SMARTP<IMUSANT_score> new_IMUSANT_score(const string& movtTitle="");

} //namespace IMUSANT
#endif
