#include "DataSource.hpp"

// In C++11, the "= default" is asking the compiler to create a default
// destructor.
// Doing this, would have been equivalent for this use case:
// DataSource::~DataSource() {}
DataSource::~DataSource() = default;

// Getters
HeplString DataSource::getName() const {
    return m_name;
}

HeplString DataSource::getSubject() const {
    return m_subject;
}

unsigned int DataSource::getTotalHeadcount() const {
    return m_totalHeadcount;
}

char DataSource::getType() const {
    return m_type;
}

// Setters
void DataSource::setName(HeplString name) {
    m_name = name;
}

void DataSource::setSubject(HeplString subject) {
    m_subject = subject;
}

void DataSource::setTotalHeadcount(unsigned int totalHeadcount) {
    m_totalHeadcount = totalHeadcount;
}

void DataSource::setType(char type) {
    m_type = type;
}
