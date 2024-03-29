/*
 *  libIMUSANT.h
 *  libIMUSANT
 *
 *  Created by Derrick Hill on 6/06/2015.
 *
 *
 */

#ifndef libIMUSANT_
#define libIMUSANT_

/* The classes below are exported */
#pragma GCC visibility push(default)

class libIMUSANT
{
	public:
		void HelloWorld(const char *);
};

#include "exports.h"
#include "smartpointer.h"

//Domain types
#include "IMUSANT_types.h"
#include "IMUSANT_pitch.h"
#include "IMUSANT_duration.h"
#include "IMUSANT_key.h"
#include "IMUSANT_element.h"
#include "IMUSANT_note.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_comment.h"
#include "IMUSANT_barline.h"
#include "IMUSANT_measure.h"
#include "IMUSANT_part.h"
#include "IMUSANT_partlist.h"
#include "IMUSANT_score.h"
#include "IMUSANT_interval.h"
#include "IMUSANT_generalised_interval.h"
#include "IMUSANT_marker_interval.h"
#include "IMUSANT_contour_symbol.h"
#include "IMUSANT_interval_vector.h"

//function types
#include "IMUSANT_processing.h"
#include "IMUSANT_mxmlv3_exceptions.h"

//visitor types
#include "IMUSANT_visitor.h"
#include "IMUSANT_collection_visitor.h"

//convertor types
//#include "IMUSANT_imusant_to_musicxml_visitor.h"

#pragma GCC visibility pop
#endif
