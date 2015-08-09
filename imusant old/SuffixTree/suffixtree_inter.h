/*******************************************************************************
** Menno van Zaanen
** mvzaanen@science.uva.nl    2001-2002
** mvzaanen@uvt.nl            2002-
********************************************************************************
** Filename: suffixtree_inter.h
********************************************************************************
** This file is part of the suffix tree package.
********************************************************************************
** This file contains the definitions of the user interface of the
** suffixtree class of the suffix tree package. The class suffixtree_inter
** describes all user entry points to the suffix tree. An
** implementation of a suffix tree should derive from this class.
** This class is defined within the ns_suffixtree namespace.
*******************************************************************************/

#ifndef __suffixtree_inter__
#define __suffixtree_inter__

#include <iostream>
#include <vector>

using std::ostream;
using std::vector;

namespace ns_suffixtree {

class StringNotFound; // Exception

template <class V>
class suffixtree_inter {
   // This class defines the interface of a suffixtree. It is an
   // abstract base class, and is only used to seperate the user
   // interface from the implementation. This file should give the
   // user enough information to use the suffixtree class.
public:
   typedef V value_type;
   typedef typename value_type::size_type size_type;
   typedef std::pair<int, size_type>	number;

   // ~suffixtree_inter virtual destructor.
   virtual ~suffixtree_inter() {}
   // find_position returns a position if w is present in the
   // suffixtree and otherwise it raises a StringNotFound exception. w
   // need not be a suffix.
   virtual number find_position(value_type w) const=0;
   // find_all_positions finds all positions of substring w occurring
   // in the suffix tree.
   virtual vector<number> find_all_positions(value_type w) const=0;
   
   // self_test returns true if all affixes of word can be found in
   // the suffixtree and it returns false if it doesn't. It may dump
   // some debug information on cerr.
   virtual bool self_test(value_type word) const=0;
   // print writes the suffixtree on os.
   virtual void print(ostream& os) const=0;
protected:
private:
};

}
#endif // __suffixtree_inter__
// end of file: suffixtree_inter.h
