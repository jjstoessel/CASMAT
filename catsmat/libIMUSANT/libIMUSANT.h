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
#include "IMUSANT_generic_interval.h"
#include "IMUSANT_note.h"
#include "IMUSANT_chord.h"
#include "IMUSANT_comment.h"
#include "IMUSANT_barline.h"
#include "IMUSANT_measure.h"
#include "IMUSANT_part.h"
#include "IMUSANT_partlist.h"
#include "IMUSANT_score.h"
#include "IMUSANT_processing.h"
#include "IMUSANT_mxmlv3_exceptions.h"
//#include "IMUSANT_repeated_interval_substring.h"
#include "IMUSANT_t_repeated_substring.h"
#include "IMUSANT_segmented_part_LBDM.h"
#include "IMUSANT_segmented_part_fixed_period.h"

#include "IMUSANT_LBDM_segmenter.h"

#pragma GCC visibility pop
#endif
