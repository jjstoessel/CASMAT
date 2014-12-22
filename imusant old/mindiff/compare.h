// (C) Copyright 2002
// Craig Henderson
//
// cdm.henderson@virgin.net
// http://homepage.virgin.net/cdm.henderson
//
// compare.h

// the result_type set for the comparison will be returned in
// a vector, so we include the STL vector header here
//
// disable the the VC++ Level 1 compiler warning "identifier
// was truncated to 'number' characters in the debug information"
// 

#ifndef ASSERT
#   define ASSERT(expr)     1? (void)0 : (void)0
#endif

#ifndef TRACE
#   define TRACE         1? (void)0 : (void)0
#endif

// typeid() required string
#include <string>

#pragma warning(disable: 4786)
#include <vector>

// guarded header file to prevent multiple include compilation errors
#ifndef __COMPARE_H_
#define __COMPARE_H_


// scope the class inside a namespace
// this is always good practice to avoid clashes
// with classes from external sources
namespace cmp {


// exception class thrown if memory allocation fails
class out_of_memory : public std::exception
{
  protected:
    const out_of_memory& operator=(const out_of_memory&);

  public:
    // default ctor
    out_of_memory()                     { TRACE("Out of memory\n"); }
    out_of_memory(const out_of_memory&) { }
    ~out_of_memory()                    { }
};


// template function to determine if a pointer to a type points to
// a null value. we also return true if the pointer itself is null
template<typename T>
inline bool is_null(T *t)
{
    return t == 0  ||  *t == T();
}


// special case for a string pointer uses the length() method
// to determine a zero length string
inline bool is_null(const std::string *t)
{
    return (t == NULL)  ||  (t->length() == 0);
}


// template class to determine if the contents of two pointer are equivalent
template<typename T>
inline bool is_equal_to(const T * const t1, const T * const t2)
{
    ASSERT(t1 != 0  &&  t2 != 0);
    return (*t1 == *t2);
}


// special case for a string pointer uses the compare() method
// to compare the two strings
inline bool is_equal_to(const std::string * const t1, const std::string * const t2)
{
    return (t1->compare(*t2) == 0);
}




// basic data provider template class for integral types.
// this class can be used to provide the compare class with
// data from an array of integral types to be compared
//
//     const char str[] = "a string to compare";
//     cmp::data_source<const char> compare_data1(str, strlen(str));
//
template<typename T>
class data_source
{
  public:
    // public typedef to define the data type
    typedef T data_type;

  private:
    const T *m_data;         // pointer to the data block
    const T *m_source;       // pointer to the source data block
    size_t   m_size;         // length of the data block

  private:
    // if these methods are not defined, then the compiler
    // will generate them if we try to use them.
    // we declare them but do not implement them as they are unused,
    // but if they are called in error, then we will get a linker
    // error. if we did not do this, the compiler will generate a basic
    // memcpy version, but that will be incorrect as the m_data vector
    // will not get copied correctly
    data_source();
    data_source(const data_source &);
    operator=(const data_source &);

  public:
    // define a single ctor taking a pointer to the data and the size of the data
    data_source(const T * const data, size_t size);

    // the dtor doesn't need to be virtual as this class is not used as a base
    ~data_source();

    // all data source classes must define the following interface
    void            clear_data(void)                                   {                                      }
    bool            get_at(size_t index, const data_type **data) const { *data = &m_data[index]; return true; }
    const T * const get_base_data(void) const                          { return m_data;                       }
    size_t          get_size(void)      const                          { return (m_data == 0)? 0 : m_size;    }
    void            retrieve_data(void);
};

// ctor
template<typename T>
inline data_source<T>::data_source<T>(const T * const data, size_t size)
  : m_data(0),
    m_source(data),
    m_size(size)
{
}

// dtor
template<typename T>
inline data_source<T>::~data_source<T>()
{
}

// fill the data buffer
template<typename T>
inline void data_source<T>::retrieve_data(void)
{
    m_data   = m_source;
    m_source = 0;
}



// public typedefs for the record types
typedef enum
{
    UNDEFINED=0,
    KEEP,       // record is in both
    REMOVE,     // record is in the first, but not the second
    INSERT      // record is in the second, but not the first
} record_type;


// the class is used to describe each result
template<typename T>
class result_type
{
  private:
    size_t              m_rec_num;  // record number
    record_type         m_type;     // record type (see enum above)
    const T::data_type &m_data;     // record data

  protected:
    // if these methods are not defined, then the compiler
    // will generate them if we try to use them.
    // we declare them but do not implement them as they are unused,
    // but if they are called in error, then we will get a linker
    // error. if we did not do this, the compiler will generate a basic
    // memcpy version, but that will be incorrect as the m_data vector
    // will not get copied correctly
    result_type();
    result_type(const result_type&);
    operator=(const result_type&);

  public:
    // ctor just stores the data
    result_type(size_t rec_num, record_type type, const T::data_type &data)
      : m_rec_num(rec_num),
        m_type(type),
        m_data(data)
    {
    }

    // empty dtor
    ~result_type() { }

    // public accessors
    size_t              rec_num(void) const  { return m_rec_num; }
    record_type         type(void)    const  { return m_type; }
    const T::data_type &data(void)    const  { return m_data; }
};




// this is it! the main class that does all the work
template<typename T>
class compare
{
  public:
    // define a typedef for the results
    typedef std::vector<result_type<T> *> result_set;

  private:
    short  *m_array;    // lcs working array
    T      *m_source;   // first data source
    T      *m_dest;     // second data source

  private:
    // if these methods are not defined, then the compiler
    // will generate them if we try to use them.
    // we declare them but do not implement them as they are unused,
    // but if they are called in error, then we will get a linker
    // error. if we did not do this, the compiler will generate a basic
    // memcpy version, but that will be incorrect as the m_data vector
    // will not get copied correctly
    compare();
    compare(const compare &);
    operator=(const compare &);

  protected:
    short get_result(int col, int row)                 const  { return m_array[(row*m_source->get_size())+col]; }
    bool  get_result_set(compare<T>::result_set *pseq) const;
    void  set_result(int col, int row, short v)               { m_array[(row*m_source->get_size())+col] = v;    }

  public:
    compare(T *source, T *dest);
    ~compare();

    int  process(compare<T>::result_set *pseq);
};

// ctor will just store the data pointers
template<typename T>
compare<T>::compare<T>(T *source, T *dest)
  : m_array(NULL),
    m_source(source),
    m_dest(dest)
{
}

// dtor to free allocated memory
template<typename T>
compare<T>::~compare<T>()
{
    if (m_array != NULL)
    {
        delete m_array;
        m_array = NULL;
    }
}


// this is the main function
// we calculate the lcs array and return the lcs length
// Note: throws cmp::out_of_memory
template<typename T>
int compare<T>::process(compare<T>::result_set *pseq)
{
    m_dest->clear_data();
    m_dest->retrieve_data();
    m_source->clear_data();
    m_source->retrieve_data();

    // if we're at the end of both data streams,
    // then return -1 to indicate the end
    if (m_source->get_size() == 0
    &&  m_dest->get_size() == 0)
    {
        return -1;
    }

    // if the two data sources are equal size, then try
    // a quick memcmp first. this avoids unnecessary
    // processing using the slower lcs algorithm
    const void * const base_data1 = m_source->get_base_data();
    const void * const base_data2 = m_dest->get_base_data();
    if (base_data1 != NULL
    &&  base_data2 != NULL
    &&  m_source->get_size() == m_dest->get_size()
    &&  memcmp(base_data1, base_data2, m_source->get_size()) == 0)
    {
        TRACE("Identical sections\n");
        return m_source->get_size();
    }

    // allocate an array for the results. if the allocation
    // fails, return -1 to indicate failure
    if (m_array != NULL)
    {
        delete m_array;
        m_array = NULL;
    }

    // calculate the size of the lcs working array
    size_t size = (1+m_source->get_size())*(1+m_dest->get_size());
    if (size > 1)
    {
        TRACE("Allocating %lu (0x%08x) bytes\n", size, size);
        m_array = new short[size];
        if (m_array == NULL)
            throw out_of_memory();

        TRACE("compare< %s > processing type \'%s\'\n", typeid(T).name(), typeid(typename T::data_type).name());

        // initialise the array to -1
        memset(m_array, 0xffffffff, size);

        // work through the array, right to left, bottom to top
        int col,row;
        for (col=m_source->get_size(); col>=0; --col)
        {
            for (row=m_dest->get_size(); row>=0; --row)
            {
                const T::data_type *data1, *data2;

                // get the data at the current col,row for each data source
                if (m_source->get_at(col, &data1)  &&  m_dest->get_at(row, &data2))
                {
                    if (cmp::is_null(data1)  ||  cmp::is_null(data2))
                    {
                        // if either data is null, set the array entry to zero
                        this->set_result(col, row, 0);
                    }
                    else if (cmp::is_equal_to(data1, data2))
                    {
                        // if the data for each source is equal, then add one
                        // to the value at the previous diagonal location - to
                        // the right and below - and store it in the current location
                        this->set_result(col, row, short(1) + this->get_result(col+1, row+1));
                    }
                    else
                    {
                        // if the data is not null and not equal, then copy
                        // the maximum value from the two cells to the right
                        // and below, into the current location
                        this->set_result(col, row, std::_cpp_max(this->get_result(col+1, row),
                                                                 this->get_result(col, row+1)));
                    }

                }
                else
                    return -1;      // something went wrong
            }   // each row
        }       // each column
    }

    // return the length of the LCS
    return this->get_result_set(pseq)? this->get_result(0, 0) : -1;
}


// construct result set and return to the caller
template<typename T>
bool compare<T>::get_result_set(compare<T>::result_set *pseq) const
{
    size_t col = 0;
    size_t row = 0;
    const typename  T::data_type *data1, *data2;
    while (col < m_source->get_size()  ||  row < m_dest->get_size())
    {
        if (m_source->get_at(col, &data1)  &&  m_dest->get_at(row, &data2))
        {
            if (cmp::is_equal_to(data1, data2))
            {
                // if the data is equal, then mark the record to be kept
                pseq->push_back(new result_type<T>(++col, cmp::KEEP, *data1));
                ++row;
            }
            else if (this->get_result(col+1, row) >= this->get_result(col, row+1)  &&  !cmp::is_null(data1))
            {
                // if the value to the right is greater than or equal to the
                // value below, and the data is not null, then mark the first
                // data to be deleted
                pseq->push_back(new result_type<T>(++col, cmp::REMOVE, *data1));
            }
            else
            {
                // if the value below is greater than the value to the right,
                // then mark the first data to be deleted
                // the data should not null
                ASSERT(!cmp::is_null(data2));
                pseq->push_back(new result_type<T>(++row, cmp::INSERT, *data2));
            }
        }
        else
            return false;       // something went wrong
    }

    return true;
}


}   // namespace cmp

#endif  // __COMPARE_H_
