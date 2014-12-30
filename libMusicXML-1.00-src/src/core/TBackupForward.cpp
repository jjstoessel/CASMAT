/*

  MusicXML Library
  Copyright (C) 2003  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  grame@grame.fr

*/

#include "TBackupForward.h"

using namespace MusicXML;

namespace MusicXML 
{
//______________________________________________________________________________
// the new functions
//______________________________________________________________________________
SBackup newBackup() { TBackup * o = new TBackup(); assert(o!=0); return o; }
SForward newForward() { TForward * o = new TForward(); assert(o!=0); return o; }

//______________________________________________________________________________
void TBackup::setDuration (long dur)		{ fDur = dur;  }
//______________________________________________________________________________
void TBackup::accept(TScoreVisitor& visitor)
{
	SBackup sptr(this);
	visitor.visite(sptr);
}

//______________________________________________________________________________
TForward& TForward::setDuration (long dur)		{ fDur = dur; return *this; }
TForward& TForward::setVoice 	(long voice)	{ fVoice = voice; return *this; }
TForward& TForward::setStaff 	(long staff)	{ fStaff = staff; return *this; }
//______________________________________________________________________________
void TForward::accept(TScoreVisitor& visitor)
{
	SForward sptr(this);
	visitor.visite(sptr);
}

} // namespace MusicXML

