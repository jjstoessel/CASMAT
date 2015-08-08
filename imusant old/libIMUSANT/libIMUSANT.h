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

#pragma GCC visibility pop
#endif
