/*******************************************************************************
** Original implementation by Menno van Zaanen
** mvzaanen@science.uva.nl    2001-2002
** mvzaanen@uvt.nl            2002-
**
** Converted for processing generalised suffix trees by JS. 25/7/2006
** 
********************************************************************************
** Filename: suffixtree_impl.h
********************************************************************************
** This file is part of the suffix tree package.
********************************************************************************
** This file contains the implementation of the classes used in the
** suffix tree package. The class suffixtree_impl contains the
** functionality of a suffix tree, while the class node is only used
** by the suffixtree_impl class. Both classes are defined in the
** ns_suffixtree namespace.
*******************************************************************************/

#ifndef __suffixtree_impl__
#define __suffixtree_impl__

#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include <utility>

using namespace std;

namespace ns_suffixtree {

class StringNotFound {}; // Exception

template <class V> class abstract_suffixtree_iterator;

template <class V>
class suffixtree_impl {
	friend class abstract_suffixtree_iterator<V>;
public:
	typedef V value_type;
	typedef typename V::size_type size_type;
	typedef typename V::value_type element_type;
	typedef typename V::const_iterator index;
	typedef pair<int,size_type> number;
	
//protected:
    //class node; // forward reference
    //typedef pair<node*, index> position;

    class node {
		// node is a support class for the suffixtree_impl class. Each
		// instance of node describes a part of the actual suffix tree. 
		// Actually, node describes the (sub)string that is between two
		// nodes. The node's suffixlink is attached to the node before
		// the begin of the (sub)string.
public:
        typedef pair<node*, index> position;
	    // node creates an empty node
		node ();
		// node creates a node with substring (b, e). u denotes the node
		// one level up, o is the owner of the node (the suffixtree_impl
		// instance that it belongs to) and num is the offset in the
		// string where the suffix starts.
		node(index b, index e, node* u, suffixtree_impl* o, size_type num, int ID);
		// ~node destructor.
		~node();
		
		// begin returns the index denoting the begin of the (sub)string
		// in the node.
		inline const index begin() const;
		// end returns the index denoting the end of the (sub)string
		// in the node. (end actually returns the one past the end
		// pointer.)
		inline const index end() const;
		// give_number returns the number stored in the node.
		inline const number give_number() const;
		
		const size_type path_label_length() const;
		// print_node writes the contents of the node on os in a
		// pleasing format. depth indicates how deep the node is
		// expected to be in the tree. This is used to print offsets
		// denoting tree depth.
		inline void print_node(ostream& os, size_type depth) const;
		
		// SEA implements the Single Extension Algorithm (SEA) (see
		// Gusfield). (b, e) is the string to be inserted. level denotes
		// the start index of the suffix, longest is a pointer to the
		// node containing the current longest suffix. cur points to the
		// end of the current string, and cont is true to start with (to
		// indicate that new extensions should be handled) and set to
		// false if handling new extensions in the current phase is not
		// needed. seek indicates if sv and gamma need to be found.
		position SEA(index b, index e, size_type level, node*& longest,
					 index cur, bool& cont, bool seek, int ID);
		
		// find_child finds the child node whose string begins with e.
		// A pointer to that node is returned. It returns 0 if the child
		// doesn't exist.
		vector<element_type> next_children() const;
		
		// find_child finds the child node whose string begins with e.
		// A pointer to that node is returned. It returns 0 if the child
		// doesn't exist.
		const node* find_child(const element_type& e) const;
		
		const node* parent() const { return up; }
	
		// assign_child sets val as a child of this node indexed with
		// value e. It is expected that e is the first value of the
		// string contained in val.
		void assign_child(const element_type e, node* val);
		
		void find_shared_nodes(vector< pair< vector<number>, int > > &results, const vector<int> IDs, int length) const;
		
		// find_leaf_positions finds all leaves reachable from this. It
		// returns all numbers that are found in these leaves. The
		// vector is unordered.
		vector<number> find_leaf_positions() const;
		
		// children_size returns the number of direct children at this
		// node.
		const size_type children_size() const;
		
protected:
private:
			// find_sv finds the sv node starting from cur. Once the v node
			// is found, the suffix_link is followed and b is adjusted. It
			// finds the new gamma (b, e) with b adjusted if needed. A
			// pointer to the sv node is returned.
			node* find_sv(index cur, index& b, index e);
		
		// seek_gamma follows (b, e) from the end of the current node.
		// New branches are selected, b will be adjusted. seek_begin
		// will find the index where gamma ends in the tree. The
		// function returns a position containing a pointer to a node
		// and an index indicating where gamma ends.
		position seek_gamma(index& b, index e);
		// extend_gamma adds the new letter at the end of the gamma. It
		// uses one of the three types of extensions as described in
		// (Gusfield). (b, e) is the new part of the branch, cur is the
		// current position in the branch of the current node. level
		// indicates the starting position in the string of this
		// particular suffix. longest denotes the one past the end
		// iterator of the longest suffix handled sofar. cont is set to
		// false if it is clear that in the current phase, no new
		// suffices need to be added. (observation 1 and trick 2)
		position extend_gamma(index b, index e, index cur,
							  size_type level, node*& longest, bool& cont, int ID);
		
		struct same_owner : binary_function<number,number,bool> 
		{
			bool operator() (const number& a, const number& b) const 
			{
				return a.first == b.first;
			}
		};
		// children relates the children of the node by their first
		// element of the string.
		map<element_type, node *> children;
		// begin_i points to the begin of the substring of the current
		// node.
		index begin_i;
		// end_i points to the one past the end of the substring of the
		// current node.
		index end_i;
		
		// up points to the node one level up. If it is the root node,
		// it points to 0.
		node* up;
		// suffix_link points to another node in the tree. It's
		// semantics is that of a suffix_link (see (Gusfield)).
		node* suffix_link;
		// owner points to a suffixtree_impl class that has this node as
		// a part of the actual tree.
		suffixtree_impl* owner;
		// number is the offset in the ID string indicating where the
		// suffix has started.
		number suffixNumber;
		//vector<int> IDmark;
		
	};
	
public:
	// suffixtree_impl creates a suffixtree based on s.
	suffixtree_impl(value_type s, int ID);
	// find_position returns a position if w is present in the
	// suffixtree and otherwise it raises a StringNotFound exception. w
	// need not be a suffix.
	number find_position(value_type w) const;
	// find_all_positions finds all positions of substring w occurring
	// in the suffix tree. The vector need not be ordered.
	vector<number> find_all_positions(value_type w) const;
	// JS: find_common_substring returns return substrings shared by two or
	// more sentences in generalised suffix tree. 
	vector< pair<vector<number>, int> > find_common_subsequences(const vector<int> IDs, int length=3) const;
	// self_test returns true if all affixes of w can be found in the
	// suffixtree and it returns false if it doesn't. It dumps some
	// debug information on cerr.
	bool self_test(value_type w) const;
	// print writes the suffixtree on os.
	void print(ostream& os) const;
	
	const node& root_node() const { return root; }
	
	map<int,value_type> get_sentences() const { return sentences; }
	
	void add_sentence(V s, int ID);
protected:
	//first_sentence actually builds the suffixtree based on first sentence.
	void first_sentence(int ID);
	// SPA implements the Single Pass Algorithm (SPA). i is what
	// Gusfield calls i+1.
	void SPA(index i, int ID);
	void SPA_2(index i,  int ID );
	// sentence contains the sentence contained in the suffixtree
	map<int, value_type> sentences;
	// root is the root node of the suffix tree
	node root;
	// longest is a pointer to the node containing the longest suffix
	node* longest;
	// e indexes into sentence denoting the longest extension handled
	// so far. It shifts one character further each phase.
	map <int,index> e;
private:
	size_type j_i;
	bool rule3stopped;
	typename node::position current;
	map<int,element_type> terminators;
	
};


/*******************************************************************************
** Menno van Zaanen
** mvzaanen@science.uva.nl    2001-2002
** mvzaanen@uvt.nl            2002-
********************************************************************************
** Filename: suffixtree_impl.cpp
********************************************************************************
** This file is part of the suffix tree package.
********************************************************************************
** This file contains the implementation of the suffixtree_impl and node
** classes. These classes are defined in suffixtree_impl.h.
*******************************************************************************/

template <class V>
suffixtree_impl<V>::node::node()
   :begin_i(0),end_i(0),up(0),suffix_link(0),owner(0)
{
// Constructor initialising an empty node.
	suffixNumber = make_pair<int,size_type>(0,0);
}

template <class V>
suffixtree_impl<V>::node::node(index b, index e, node* u,
      suffixtree_impl* o, size_type num, int ID)
   :begin_i(b),end_i(e),up(u),suffix_link(0),owner(o)
{
// Constructor initialising a node with begin_i, end_i, up, owner and
// number. suffix_link and children are still empty.
	//suffixNumber = make_pair<int,size_type>(ID,num); //C++98 compatible
    suffixNumber = make_pair(std::forward<int>(ID), std::forward<size_type>(num));
	//IDmark.push_back(ID);
}

template <class V>
suffixtree_impl<V>::node::~node() {
// Destructor automatically calls delete for each of the children
// recursively.
   for (typename map<typename suffixtree_impl<V>::element_type, node *>::iterator
         i=children.begin(); i!=children.end(); i++) {
      delete i->second;
   }
}

template <class V>
const typename suffixtree_impl<V>::index
suffixtree_impl<V>::node::begin() const {
// Return the begin index, stored in begin_i.
   return begin_i;
}

template <class V>
const typename suffixtree_impl<V>::number
suffixtree_impl<V>::node::give_number() const {
// Return the number, stored in number.
   return suffixNumber;
}

template <class V>
const typename suffixtree_impl<V>::size_type
suffixtree_impl<V>::node::path_label_length() const
{
	const node* current = this;
	size_type length = 0;
	
	while (current!=NULL)
	{
		length += current->end() - current->begin();
		current=current->up;
	}
	
	return length;
}

template <class V>
const typename suffixtree_impl<V>::index
suffixtree_impl<V>::node::end() const {
// Return the end index. This is stored in end_i, unless it is a leaf.
// Then the e value of the owner should be returned, since that
// denotes the longest handled extension so far.
   if (children.size()==0) // no children
      return owner->e[suffixNumber.first];
   else 
      return end_i;
}

template <class V>
void
suffixtree_impl<V>::node::print_node(ostream& os, size_type
									 depth) const {
	// Print the content of the node on os. depth indicates how far the
	// current node should be indented.
	if (begin()!=end()) { // print the entry only if it defines a substring
		if (children.size()==0) 
		{
			os << "+"; // start the line with a + if it is a leaf
		} 
		else 
		{
			os << "-"; // start the line with a - if it has branches
		}
		if (depth>0) { // print |'s indicating branch depth
			size_type d=depth;
			while (d>0) 
			{
				os << "|";
				d--;
			}
		}
		//os << V(begin(), end()); // print the substring
		//JS: Replacement routine for vectors
		typename V::const_iterator iter=this->begin();
		for (  ; iter!=this->end(); iter++)
		{
			os << (*iter) << ",";
		}
		//end replacement
		if (children.size()==0) { // if it is a leaf, print it's start index
			os << suffixNumber.first << "," << suffixNumber.second;
		}
		//-
		/* os << " Owners: ";
				for (vector<int>::const_iterator j=IDmark.begin(); j!=IDmark.end(); j++)
				{
					os << (*j);
					if ((j+1)!=IDmark.end())
						os << ", ";
				} */
		//-
		os << endl;
	}
	for (typename map<typename suffixtree_impl<V>::element_type, node *>::const_iterator i=children.begin();
         i!=children.end(); i++) { // print all children
		i->second->print_node(os, depth+1); // depth+1 it is one level deeper
	}
}

template <class V>
typename suffixtree_impl<V>::node::position
suffixtree_impl<V>::node::SEA(index b, index e, size_type level, node*&
      longest, index cur, bool& cont, bool seek, int ID) {
// SEA implements the Single Extension Algorithm (SEA) (see
// Gusfield). (b, e) is the string to be inserted.  level denotes
// the start index of the suffix, longest is a pointer to the
// node containing the current longest suffix. cur points to the
// end of the current string, and cont is true to start with (to
// indicate that new extensions should be handled) and set to
// false if handling new extensions in the current phase is not
// needed. seek indicates if sv and gamma need to be found (true, yes,
// false, no).
   node *sv;
   if (seek) {
      sv=find_sv(cur, b, e); // find the sv node starting from cur
      position pos=sv->seek_gamma(b, e-1); // move to the end of gamma from sv
      sv=pos.first;
      cur=pos.second;
   }
   else {
      sv=this;
   }
   // add new character from the end of gamma
   return sv->extend_gamma(b, e, cur, level, longest, cont, ID);
}

template <class V>
vector<typename suffixtree_impl<V>::element_type>
suffixtree_impl<V>::node::next_children() const {
// Collect all possible keys of this node and return them in a vector.
   typename map<typename suffixtree_impl<V>::element_type,
      node *>::const_iterator i=children.begin();
   vector<element_type> v;
   while (i!=children.end()) {
      v.push_back(i->first);
      i++;
   }
   return v;
}


template <class V>
const typename suffixtree_impl<V>::node*
suffixtree_impl<V>::node::find_child(const typename suffixtree_impl<V>::element_type &e) const {
// Find the child that was indexed with e. It returns 0 if the child
// doesn't exist.
   typename map<typename suffixtree_impl<V>::element_type, node *>::const_iterator f_node=children.find(e);
   if (f_node==children.end()) {
      return 0;
   }
   else {
      return f_node->second;
   }
}

// JS: a recursive function that inspects IDmark in nodes for presence of list of supplied IDs
// The return data is constrained by the length parameter
/* template <class V>
void
suffixtree_impl<V>::node::find_shared_nodes(vector< pair<vector<number>, int> > &results, const vector<int> IDs, int length) const
{
	bool found = true;
	for (vector<int>::const_iterator i=IDs.begin(); i!=IDs.end(); i++)
	{
		if (find(IDmark.begin(),IDmark.end(), *i)==IDmark.end())
		{
			found = false;
			break;
		}
	}
	if (!found) return;
	
	size_type path_length = path_label_length();
	
	if (path_length>=length)
	{
		pair <vector<typename suffixtree_impl<V>::number>,int> res;
		res.first=find_leaf_positions();
		res.second=path_length;
		results.push_back(res);
	}
	
	typename map<typename suffixtree_impl<V>::element_type, node *>::const_iterator child=children.begin();
	
	for (; child!=children.end(); child++)
	{
		child->second->find_shared_nodes(results,IDs,length);
	}
}
 */
//JS: recursive function to find shared nodes
template <class V>
void
suffixtree_impl<V>::node::find_shared_nodes(vector< pair<vector<number>, int> > &results, const vector<int> IDs, int length) const
{
	bool found = true;
	
	vector<number> leaves = find_leaf_positions();
	
	for (vector<int>::const_iterator i=IDs.begin(); i!=IDs.end(); i++)
	{
		number test = number(*i,0);
		if (find_if(leaves.begin(),leaves.end(), std::bind2nd(same_owner(),test))==leaves.end())
        {
			found = false;
			break;
		}
	}
	if (!found) return;
	
	size_type path_length = path_label_length();
	
	if (path_length>=length)
	{
		pair <vector<typename suffixtree_impl<V>::number>,size_type> res;
		res.first=leaves;
		res.second=path_length;
		results.push_back(res);
	}
	
	typename map<typename suffixtree_impl<V>::element_type, node *>::const_iterator child=children.begin();
	
	for (; child!=children.end(); child++)
	{
		child->second->find_shared_nodes(results,IDs,length);
	}
}

template <class V>
void
suffixtree_impl<V>::node::assign_child(const element_type e, node* val) {
// Set val as a child indexed with value e.
   children[e]=val;
}

template <class V>
vector<typename suffixtree_impl<V>::number>
suffixtree_impl<V>::node::find_leaf_positions() const {
   vector<typename suffixtree_impl<V>::number> result;
   if (children.size()==0) {
      result.push_back(suffixNumber);
   }
   for (typename map<typename suffixtree_impl<V>::element_type, node*>::const_iterator c=children.begin();
         c!=children.end(); c++) {
      vector<typename suffixtree_impl<V>::number> res=c->second->find_leaf_positions();
      result.insert(result.end(), res.begin(), res.end());
   }
   return result;
}

template <class V>
const typename suffixtree_impl<V>::size_type
suffixtree_impl<V>::node::children_size() const {
   return children.size();
}

template <class V>
typename suffixtree_impl<V>::node*
suffixtree_impl<V>::node::find_sv(index cur, index& b, index e) {
// find the sv node. This means going back from e towards b matching
// from cur (cur is the current position, so the string ending with
// cur should match a suffix of (b, e)). Once a suffix link is found,
// it is followed. gamma keeps track of the number of positions that
// have been recognised while going back to find the suffixlink.
// Note that if no suffixlink is found, b is not changed.
   node *sv=this; // seeker node going up and through suffixlink
   size_type gamma=cur-sv->begin(); // current string must be searched
   while (!((sv->up==0)||(sv->suffix_link!=0))) { // find suffix link or root
      sv=sv->up; // going up
      gamma+=sv->end()-sv->begin(); // append gamma
   }
   if (sv->suffix_link!=0) { // found suffix link
      gamma-=sv->end()-sv->begin(); // suffix link is at end of branch
      sv=sv->suffix_link; // follow suffixlink
      b=e-gamma; // new begin
   }
   return sv;
}

template <class V>
typename suffixtree_impl<V>::node::position
suffixtree_impl<V>::node::seek_gamma(index& b, index e) {
// seek_gamma follows (b, e) from the end of the current node going
// up.  New branches are selected, b will be adjusted.  seek_begin
// will find the index where gamma ends in the tree. The function
// returns a pointer to the node that contains seek_begin and
// seek_begin itself. It uses the skip count trick.
   typename suffixtree_impl::node *seek_node=this;
   index seek_begin=seek_node->end();
   size_type g=e-b; // skip count trick
   size_type g_prime=seek_node->end()-seek_begin;
   while (g_prime<g) {
      g-=g_prime; // skip gamma it must match
      b+=g_prime; // skip b it must match
      seek_node=seek_node->children[*b]; // choose correct branch
      seek_begin=seek_node->begin(); // get new seek_begin
      g_prime=seek_node->end()-seek_node->begin(); // compute new g_prime
   }
   seek_begin+=g; // find end of string(b, e); don't change b
   return make_pair(seek_node, seek_begin);
}

template <class V>
typename suffixtree_impl<V>::node::position
suffixtree_impl<V>::node::extend_gamma(index b, index e, index cur,
      typename suffixtree_impl<V>::size_type level, typename suffixtree_impl<V>::node*& longest, bool& cont, int ID) {
	// extend_gamma adds the new letter at the end of the gamma. It
	// uses one of the three types of extensions as described in
	// (Gusfield 1997: 96). (b, e) is the new part of the branch, cur is the
	// current position in the branch of the current node. level
	// indicates the starting position in the string of this
	// particular suffix. longest denotes the one past the end
	// iterator of the longest suffix handled sofar. cont is set to
	// false if it is clear that in the current phase, no new
	// suffices need to be added.  (observation 1 and trick 2)
	node *seek_node=this; // seek_node points to node that gets added to
	element_type new_el=*(e-1); // get last element (e is one past the end)
	static node* sw; // remember sw, it will be used as a suffix link
	if (cur==end()) {
		if (children.size()==0) { // rule 1
			begin_i=b;
			end_i=e;
			cur=end_i;
		}
		else {
			typename map<typename suffixtree_impl<V>::element_type, node*>::iterator place=children.find(new_el);
			if (place==children.end()) { // rule 2
				seek_node=new node(e-1, e, this, owner, level, ID); // new child
				children[new_el]=seek_node; // add a new child
				cur=e;
			}
			else { // rule 3
		
				seek_node=place->second;
				cur=seek_node->begin()+1; // first one always matches
				cont=false; // rule 3, so don't continue
				//JS: This maps ID marks to node during construction for the purposes of finding common substrings
				/* if (find(this->IDmark.begin(), this->IDmark.end(), ID)==this->IDmark.end())
				{
					//Then must be another string
					this->IDmark.push_back(ID);
				}
				//- */
			}
		}
	} 
	else { // cur!=end()
		if (*cur!=new_el) { // rule 2 break string
							// note that the divisions of nodes is very delicate. The
							// procedure needs to set all pointers correctly, because
							// suffixlinks and return values don't work otherwise.
			node *break_node=new node(begin(), cur, up, owner,
									  suffixNumber.second,suffixNumber.first); // new begin part
			break_node->up->children[*begin()]=break_node;
			break_node->children[*cur]=this;
			break_node->children[new_el]=new node(e-1, e, break_node,
												  owner, level,ID); // new inserted part
			//JS: This remaps ID marks to node for the purposes of finding common substrings
			/* if (find(break_node->IDmark.begin(), break_node->IDmark.end(), ID)==break_node->IDmark.end())
						break_node->IDmark.push_back(ID); */
			//-
			up=break_node; // adjust up to new (break) node
			begin_i=cur; // this becomes end part
			seek_node=break_node->children[new_el];
			cur=seek_node->end();
			if (sw!=0) { // handle sw if present before we store new one
				sw->suffix_link=break_node; // break node is new begin part
				sw=0;
			}
			if(up!=0) { // skip root
				sw=break_node;
			}
			return make_pair(seek_node, cur);
		}
		else { // rule 3
			cur++; // first one always matches
			cont=false; // rule 3, so don't continue
			//JS: This maps ID marks to node during construction for the purposes of finding common substrings
			/* if (find(this->IDmark.begin(), this->IDmark.end(), ID)==this->IDmark.end())
			{
				//Then must be another string
				this->IDmark.push_back(ID);
			}
			//- */
		}
	}
	if (sw!=0) { // store sw's suffix link
		sw->suffix_link=this;
		sw=0;
	}
	return make_pair(seek_node, cur);
}

template <class V>
suffixtree_impl<V>::suffixtree_impl(V s, int ID)
    //: root(index(0), index(0), 0, this, 0, 0) - 12-12-14 JS worked in earlier implementation - now calls to private iterator
    :root(sentences[ID].begin(), sentences[ID].end(), 0, this, 0, 0) //root has no ID
{
// suffix tree constructor. s is the sentence.
   longest=&root; // setup longest (which is the entire sentence at the moment
   // Build the suffix tree based on s.
   sentences[ID]=s; // remember sentence
   first_sentence(ID); // actually build the suffix tree for first string
}

template <class V>
typename suffixtree_impl<V>::number
suffixtree_impl<V>::find_position(V w) const {
// Check if sentence is a substring in the suffix tree. Throw a
// StringNotFound if it is not.
   typename suffixtree_impl::index i=w.begin(); // search index in w
   const node *current=&root; // start at the root
   if (i==w.end()) { // empty strings are not found
      throw StringNotFound();
   }
   if (current->begin()==current->end()) { // empty substring
      current=current->find_child(*i); // find next branch
      if (current==0) { // couldn't find next branch
         throw StringNotFound();
      }
   }
   typename suffixtree_impl::index seeker=current->begin(); // begin of substring
   while (*i==*seeker) {
      i++;
      if (i==w.end()) {
         break;
      }
      seeker++;
      if (seeker==current->end()) { // branch
         current=current->find_child(*i); // next branch
         if (current==0) { // couldn't find right branch
            throw StringNotFound(); // and string is not finished yet
         }
         seeker=current->begin(); // adjust seeker pointer
      }
   }
   if (i==w.end()) { // found position
      return current->give_number();
   }
   throw StringNotFound(); // should never be reached
}

template <class V>
vector<typename suffixtree_impl<V>::number>
suffixtree_impl<V>::find_all_positions(typename suffixtree_impl<V>::value_type w) const {
   typename suffixtree_impl::index i=w.begin(); // search index in w
   vector<number> results;
   const node *current=&root; // start at the root
   if (i==w.end()) { // empty strings are not found
      return results;
   }
   if (current->begin()==current->end()) { // empty substring
      current=current->find_child(*i); // find next branch
      if (current==0) { // couldn't find next branch
         return results;
      }
   }
   typename suffixtree_impl::index seeker=current->begin(); // begin of substring
   while (*i==*seeker) {
      i++;
      if (i==w.end()) {
         break;
      }
      seeker++;
      if (seeker==current->end()) { // branch
         current=current->find_child(*i); // next branch
         if (current==0) { // couldn't find right branch
            return results; // and string is not finished yet
         }
         seeker=current->begin(); // adjust seeker pointer
      }
   }
   if (i==w.end()) { // found position
      vector<number> subres=current->find_leaf_positions();
      results.insert(results.end(), subres.begin(), subres.end());
   }
   return results; // should never be reached
}

template <class V>
vector< pair<vector<typename suffixtree_impl<V>::number>, int> >
suffixtree_impl<V>::find_common_subsequences(const vector<int> IDs, int length) const
{
	vector< pair <vector<number>, int> > results;
	//check that IDs have been entered into tree.
	if (sentences.size() < IDs.size()) return results;
	for (vector<int>::const_iterator iter=IDs.begin(); iter!=IDs.end(); iter++)
	{
		typename map<int, value_type>::const_iterator sentence=sentences.find(*iter);
		if (sentence==sentences.end())
			return results;
	}
	
	const node *current=&root; // start at the root
	
	current->find_shared_nodes(results, IDs, length);
	
	return results;
	
}

template <class V>
bool
suffixtree_impl<V>::self_test(V sentence) const {
// Return true if all affixes of sentence can be found in the
// suffixtree and return false otherwise.
   number found;
   bool res=true;
   size_type length=sentence.size();
   for (size_type i=0; i<=length; i++) { // begin of substring
      for (size_type j=1; j<=length-i; j++) 
	  { // end of substring
			//JS: replacement for vector manipution
			vector<element_type> subsentence(j);
			copy(sentence.begin()+i, sentence.begin()+i+j, subsentence.begin());
        
		  try {
			
			found = find_position(subsentence);
			//end replacement
            //found=find_position(sentence.substr(i, j)); // check
         }
         catch (StringNotFound) {
			cerr << "Test Results: Fail in string (" << i;
			cerr << "," << j << ")=";
			//JS changed for vector based implementation
			for (typename V::const_iterator iter=subsentence.begin(); iter!=subsentence.end(); iter++)
			{
				cerr << (*iter);
			} 
			cerr << endl;
			//cerr << "," << j << ")=" << sentence.substr(i, j) << endl;
			res=false;
         }
      }
   }
   if (res) {
      cerr << "Test Results: Success." << endl;
   }
   else {
      cerr << "Test Results: Failed." << endl;
   }
   return res;
}

template <class V>
void
suffixtree_impl<V>::print(ostream& os) const {
// print the suffixtree on os. Start with the root node.
   os << "root" << endl;
   root.print_node(os, 0); // level is 0, it is the root node
}

template <class V>
void
suffixtree_impl<V>::add_sentence(V s, int ID)
{
	sentences[ID]=s;
	if (sentences[ID].empty() || sentences[ID].begin()==sentences[ID].end())
		return;
	terminators[ID]=*(sentences[ID].end()-1);
	// Start at root, match S_2 until mismatch occurs
	typename suffixtree_impl::index i=sentences[ID].begin()+1; // search index in sentence
	//const node* current_node=&root; // start at the root
	j_i = -1;
	current=make_pair(const_cast<node*>(&root), root.end());
	rule3stopped = false;
	typename suffixtree_impl::index m=sentences[ID].end();
	for (; i<=m; i++) // i is `end' pointer
	{ 
		SPA_2(i,ID); 
	}
}

 
template <class V>
void
suffixtree_impl<V>::first_sentence(int ID) 
{
	if (sentences[ID].empty() || sentences[ID].begin()==sentences[ID].end()) // no sentence
	  return; // nothing to do
	// build I_0
	//--
	//record termination elements
	terminators[ID]=*(sentences[ID].end()-1);
	
	typename suffixtree_impl::index i=sentences[ID].begin();
	node *first=new node(i, i+1, &root, this, 0, ID);
	root.assign_child(*i, first);
	e[ID]=i+1;
	//--
	//node *first=new node(sentences[ID].begin(), sentences[ID].begin()+1, &root, this, 0, ID); // extension starts at index 0
	//root.assign_child(*sentences[ID].begin(), first); // first char is a child of root
	//e=sentences[ID].begin()+1; // next char to do
	longest=first; // we have a longest substring
	//--
	current = make_pair(longest, longest->end());
	j_i = 0;
	rule3stopped = false;
	typename suffixtree_impl::index m=sentences[ID].end();
	for (i+=2; i<=m; i++) // i is `end' pointer
	{ 
		SPA_2(i,ID); 
		//SPA(i,ID);
	}
	//--
	/* typename suffixtree_impl::index m=sentences[ID].end();
		for (typename suffixtree_impl::index i=sentences[ID].begin()+2; i<=m; i++) // i is `end' pointer
		{ 
		  SPA(i,ID); // do SPA based on Gusfields description of the algorithm
		} */
}

template <class V>
void
suffixtree_impl<V>::SPA(suffixtree_impl::index i, int ID) {
// Do the SPA algorithm (described in Gusfield). We care currently
// handling phase i (i+1 in Gusfields algorithm).
   static size_type j_i=0;
   e=i; //special case longest string, increase e
   size_type j_index=j_i+1;
   static typename node::position current=make_pair(longest, longest->end());
   bool cont=true;
   static bool rule3stopped=false;
   if (rule3stopped) {// we already know where to extend
      current=current.first->SEA(i-1, i, j_index, longest,
            current.second, cont, false, ID);
      j_index++;
      rule3stopped=false;
      if (!cont) {
         rule3stopped=true;
         return;
      }
   }
   
   for (typename suffixtree_impl::index j=sentences[ID].begin()+j_index; j<i; j++) {
      current=current.first->SEA(j, i, j_index, longest,
            current.second, cont, true, ID);
      if (!cont) { // no need to continue (step 3 has been done)
         rule3stopped=true; // remember that rule 3 stopped us
         break;
      }
      j_index++;
   }
   j_i=j_index-1; // remember j_i
}

template <class V>
void
suffixtree_impl<V>::SPA_2(suffixtree_impl::index i, int ID ) 
{
// Do the SPA algorithm (described in Gusfield). We care currently
// handling phase i (i+1 in Gusfields algorithm).
   e[ID]=i; //special case longest string, increase e
   size_type j_index=j_i+1;
   bool cont=true;
   if (rule3stopped) {// we already know where to extend
      current=current.first->SEA(i-1, i, j_index, longest,
            current.second, cont, false, ID);
      j_index++;
      rule3stopped=false;
      if (!cont) {
         rule3stopped=true;
         return;
      }
   }
   
   for (typename suffixtree_impl::index j=sentences[ID].begin()+j_index; j<i; j++) {
      current=current.first->SEA(j, i, j_index, longest,
            current.second, cont, true, ID);
      if (!cont) { // no need to continue (step 3 has been done)
         rule3stopped=true; // remember that rule 3 stopped us
         break;
      }
      j_index++;
   }
   j_i=j_index-1; // remember j_i
}

}
#endif // __suffixtree_impl__
// end of file: suffixtree_impl.h
