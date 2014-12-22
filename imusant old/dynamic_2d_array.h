/*
 *  dynamic_2d_array.h
 *  imusant
 *
 *  Created by Jason Stoessel on 29/08/06.
 *  Copyright 2006 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __DYNAMIC_2D_ARRAY__
#define __DYNAMIC_2D_ARRAY__

#include <vector>

using namespace std;

template < class T>
class dynamic_2d_array
{
public:
    dynamic_2d_array(int row, int col) : m_data(row, vector<T>(col,T)) {}
    ~dynamic_2d_array(){}
    T* operator[](int i) {return (m_data + (m_col*i));}
    T const*const operator[](int i) const {return (m_data + (m_col*i));}
private:
    vector<vector<T> > m_data; 
};

template <class T>
inline dynamic_2d_array<T>::T* dynamic_2d_array<T>::operator[](int i) 
{
	return m_data[i] + (m_col*i));
}
inline dynamic_2d_array<T>::T const*const dynamic_2d_array<T>::operator[](int i) const 
{
	return (m_data + (m_col*i));
}

#endif //__DYNAMIC_2D_ARRAY__