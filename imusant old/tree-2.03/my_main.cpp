/*
 *  my_main.cpp
 *  tree
 *
 *  Created by Jason Stoessel on 24/06/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#include <algorithm>
#include <string>
#include <iostream>
#include "tree.hh"

using namespace std;

int main(int, char **)
{
	tree<long> tr;
	tree<long>::iterator iter = tr.set_head(0);

	
	for (long i=1; i < 13; i++)
	{
		tr.append_child(iter, i);
		iter++;
	}
	
	tree<long>::iterator iter2=tr.begin();
	tree<long>::iterator end=tr.end();
	while(iter2!=end) 
	{
         cout << (*iter);
         ++iter2;
	}
	
	
}
