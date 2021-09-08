#include "DataSourceSerie2D.hpp"

// Constructors
DataSourceSerie2D::DataSourceSerie2D():
    m_list() {
}

// Getters
const HeplList<Data2D>& DataSourceSerie2D::getList() {
    return m_list;
}

HeplString DataSourceSerie2D::getSubject2() const {
    return m_subject2;
}

char DataSourceSerie2D::getType2() const {
    return m_type2;
}

// Setters
void DataSourceSerie2D::setList(const HeplList<Data2D>& list) {
    m_list = list;
}

void DataSourceSerie2D::setSubject2(const HeplString& subject) {
    m_subject2 = subject;
}

void DataSourceSerie2D::setType2(const char& type) {
    m_type2 = type;
}
