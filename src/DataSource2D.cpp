#include "DataSource2D.hpp"

// Constructors
DataSource2D::DataSource2D():
    m_list() {
}

// Getters
const HeplList<Data2D>& DataSource2D::getList() {
    return m_list;
}

HeplString DataSource2D::getSubject2() const {
    return m_subject2;
}

char DataSource2D::getType2() const {
    return m_type2;
}

// Setters
void DataSource2D::setList(const HeplList<Data2D>& list) {
    m_list = list;
}

void DataSource2D::setSubject2(const HeplString& subject) {
    m_subject2 = subject;
}

void DataSource2D::setType2(const char& type) {
    m_type2 = type;
}
