#ifndef SAMPLE_HPP_INCLUDED
#define SAMPLE_HPP_INCLUDED

#include "DataSource.hpp"

class Sample {

    private:
        DataSource *m_source;

    public:
        Sample();
        Sample(DataSource *source);
        ~Sample();
        DataSource* getDataSource();
        void setDataSource(DataSource *source);
};

#endif // SAMPLE_HPP_INCLUDED
