// (C) Copyright 2002
// Craig Henderson
//
// cdm.henderson@virgin.net
// http://homepage.virgin.net/cdm.henderson
//
// data_source_text_file.h

// data source class for supplying a text file to the compare routine.
// limitations:
//   the entire file will be read into memory. Note that the compare
//   routine requires n*m*sizeof(short) bytes of storage where n and m
//   are the number of data records; in this case lines in the data file
//

#ifndef __DATA_SOURCE_TEXT_FILE_H
#define __DATA_SOURCE_TEXT_FILE_H

// scope the class inside a namespace
// this is always good practice to avoid clashes
// with classes from external sources
namespace cmp {

class data_source_text_file
{
  public:
    // public typedef to define the data type
    typedef std::string data_type;

  private:
    FILE                     *m_file;
    std::vector<std::string>  m_data;

  protected:
    // if these methods are not defined, then the compiler
    // will generate them if we try to use them.
    // we declare them but do not implement them as they are unused,
    // but if they are called in error, then we will get a linker
    // error. if we did not do this, the compiler will generate a basic
    // memcpy version, but that will be incorrect as the m_data vector
    // will not get copied correctly
    data_source_text_file();
    data_source_text_file(const data_source_text_file &);
    operator=(const data_source_text_file &);

  public:
    // define the ctor with an explicit FILE* parameter to
    // prevent bad conversions
    explicit data_source_text_file(FILE *file);

    // the dtor doesn't need to be virtual as this class is not used as a base
    ~data_source_text_file();

    // all data source classes must define the following interface
    void             clear_data(void);
    bool             get_at(size_t index, const data_type **data) const;
    const data_type *get_base_data(void)                    const { return NULL;          }
    size_t           get_size(void)                         const { return m_data.size(); }
    void             retrieve_data(void);
};


// ctor
inline data_source_text_file::data_source_text_file(FILE *file)
  : m_file(file)
{
}

// dtor
inline data_source_text_file::~data_source_text_file()
{
}

// get the data at a specified offset
inline bool data_source_text_file::get_at(size_t index, const data_type **data) const
{
    // the caller will request one beyond the end, so return NULL
    if (index >= m_data.size())
        *data = NULL;
    else
        *data = &m_data.at(index);

    return true;
}

// clear the data buffer
inline void data_source_text_file::clear_data(void)
{
    m_data.erase(m_data.begin(), m_data.end());
}


// read the data into the data buffer
inline void data_source_text_file::retrieve_data(void)
{
    char buffer[4096];

    ASSERT(m_data.size() == 0);
    while (!feof(m_file))
    {
        fgets(buffer, sizeof(buffer)/sizeof(buffer[0]), m_file);
        m_data.push_back(buffer);
    }

    return;
}

};  // namespace cmp


#endif  // __DATA_SOURCE_TEXT_FILE_H
