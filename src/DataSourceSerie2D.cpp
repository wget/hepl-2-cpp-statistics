#include "DataSourceSerie2D.hpp"

// Getters
HeplString DataSourceSerie2D::getSubject2() const {
    return m_subject2;
}

char DataSourceSerie2D::getType2() const {
    return m_type2;
}

// Setters
void DataSourceSerie2D::setSubject2(HeplString subject) {
    m_subject2 = subject;
}

void DataSourceSerie2D::setType2(char type) {
    m_type2 = type;
}
