/*
 *  maximals.h
 *  Tests
 *
 *  Created by Jason Stoessel on 9/08/06.
 *  Copyright 2006 Jason Stoessel. All rights reserved.
 *
 */

#ifndef __repeats__
#define __repeats__

#include <vector>
#include <map>
#include <list>

#include "suffixtree.h"
#include "iterator.h"

using namespace ns_suffixtree;
using namespace std;

template <class V>
class repeats
{
	public:
		
		typedef typename suffixtree_impl<V>::value_type value_type;
		typedef typename suffixtree_impl<V>::size_type size_type;
		typedef typename suffixtree_impl<V>::element_type element_type;
		typedef typename suffixtree_impl<V>::index index;
		typedef typename suffixtree_impl<V>::number	number;
		
		class supermax_node
		{
			public:
				supermax_node() : num_witness(0), num_leaves(0), percent(0) {}
				~supermax_node() {}
			
				int num_witness, num_leaves, percent;
				supermax_node *next;
				index begin_i, end_i;
		};
	
		class lvnode
		{
			public: 
				lvnode();
				lvnode(element_type v, int amount): value(v), count(amount) {}
			//private:
				lvnode* next;
				element_type value;
				int count;
		};
		
				repeats(const suffixtree_impl<V>* sufftree) : tree(sufftree) { }
				~repeats();
		void	add_value(typename suffixtree_impl<V>::number ID, element_type value, int amount);
		int		get_value(typename suffixtree_impl<V>::number ID, element_type value);
		const list<supermax_node*>&  supermax_find(int min_percent, int min_length);
		
	private: 	
		list<supermax_node*>& compute_supermax(const typename suffixtree_impl<V>::node*, int min_percent, 
												int min_length, list<supermax_node*>& max_list);
		list<supermax_node*> max_list;
		map<number, lvnode *>	stack;
		const suffixtree_impl<V>*	tree;
};

template <class V>
repeats<V>::~repeats()
{
	typename map<typename suffixtree_impl<V>::number, lvnode *>::iterator i = stack.begin();
	for ( ; i != stack.end(); i++ )
	{
		delete i->second;
	}
	
	typename list<supermax_node*>::const_iterator j = max_list.begin();
	for ( ; j !=max_list.end(); j++)
	{
		delete *j;
	}
}

template <class V>
const list<typename repeats<V>::supermax_node*>&  
repeats<V>::supermax_find(int min_percent, int min_length)
{
	const typename suffixtree_impl<V>::node* n = &tree->root_node();
	
	max_list = compute_supermax(n, min_percent, min_length, max_list);
	
	return max_list;
}

template <class V>
void
repeats<V>::add_value(typename suffixtree_impl<V>::number ID, element_type value, int amount)
{
	lvnode* node;
	
	for (node=stack[ID]; node!=0; node=node->next)
	{
		if (node->value == value)
		{
			node->count += amount;
			return;
		}
	}
	
	node = new lvnode(value,amount);
	if (node==0) return;
	
	node->next = stack[ID];
	stack[ID] = node;
	return;
}

template <class V>
int	
repeats<V>::get_value(typename suffixtree_impl<V>::number ID, element_type value)
{
	lvnode* node;
	
	for (node=stack[ID]; node!=0; node=node->next)
	{
		if (node->value == value)
			return node->count;
	}

	return 0;
}

template <class V>
list<typename repeats<V>::supermax_node*>& 
repeats<V>::compute_supermax(const typename suffixtree_impl<V>::node* n, int min_percent, 
							int min_length, list<repeats<V>::supermax_node*>& max_list)
{
	lvnode* lvn;
	const vector< element_type > children = n->next_children(); //ensure vector is maintained
	typename vector< element_type >::const_iterator c = children.begin();
	const typename suffixtree_impl<V>::node* child = n->find_child(*c);
	
	for (  ; (child!=0 && c!=children.end()); c++, child = n->find_child(*c))
	{
		max_list = compute_supermax(child, min_percent, min_length, max_list);
		lvn = stack[child->give_number()];
		while (lvn!=NULL)
		{
			add_value(n->give_number(), lvn->value, lvn->count);
			lvn = lvn->next;
		}
	}
	
	if (n==&tree->root_node()) return max_list;
	
	//find all leaves for current node and add left predecessor
	
	vector<typename suffixtree_impl<V>::number> leaves = n->find_leaf_positions();
	typename vector<typename suffixtree_impl<V>::number>::const_iterator leaf_i = leaves.begin();
	
	for ( ; leaf_i!=leaves.end(); leaf_i++)
	{
		element_type elt = *(n->begin()-1);
		add_value(n->give_number(), (n->give_number().second == 0 ? element_type(-1) : elt), 1);
	}
	
	/* Determine if current node is supermaximal or near super maximal
	 * 
	 *	1:	Find total number of leaves in subtree and number of different left
	 *		predecessors of those leaves (i.e. diversity of left predecessors).
	 *		Any Node wih a diversity > 1 is left diverse.
	 */
	int num_leaves = 0;
	int diversity = 0;
	
	for (lvn=stack[n->give_number()]; lvn!=0; lvn=lvn->next)
	{
		num_leaves += lvn->count;
		diversity++;
	}
	
	if (diversity==1) return max_list;
	
	/*
	 *	2:	Find number of leaves at the current node or its children
	 *		whose left predecessor is unique (i.e. no other lead in the same 
	 *		subtree has the same left predecessor).  This type of leaf witnesses
	 *		the supermaximality of the current node's label.
	 */
	int witnesses = 0;
	c = children.begin();
	child = n->find_child(*c);
	for ( ; (child!=NULL && c!=children.end()); c++, child = n->find_child(*c))
	{
		if (child->children_size()==0 && child->find_leaf_positions().size() > 0)
		{
			leaves = child->find_leaf_positions();
			leaf_i = leaves.begin();
			
			for ( ; leaf_i!=leaves.end(); leaf_i++)
			{
				element_type elt = *(child->begin()-1);
				if (get_value(n->give_number(),(n->give_number().second == 0 ? element_type(-1) : elt))==1)
					witnesses++;
			}

		}
	}
	
	leaves = n->find_leaf_positions();
	leaf_i = leaves.begin();
	
	for ( ; leaf_i!=leaves.end(); leaf_i++)
	{
		element_type elt = *(n->begin()-1);
		if (get_value(n->give_number(),(n->give_number().second == 0 ? element_type(-1) : elt))==1)
			witnesses++;
		
	}
	
	if (witnesses == 0)
		return max_list;
		
	//Check whether the node is sufficiently near a super maximal	
	int percent = (int) (((float)witnesses) / ((float) num_leaves) * 100.0);
	supermax_node* newnode;
	if (min_percent == 0 || (min_percent < 100 && percent >= min_percent) || (min_percent == 100 && witnesses == num_leaves)) 
	{
		newnode = new supermax_node();
		assert(newnode!=0);
		newnode->begin_i = n->begin();
		newnode->end_i = n->end();
		newnode->num_leaves = num_leaves;
		newnode->num_witness = witnesses;
		newnode->percent = percent;
		newnode->next = *(max_list.begin());
		max_list.push_front(newnode);
	}

	return max_list;

}

#endif
