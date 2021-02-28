#include "Data1D.hpp"

// Getters
float Data1D::getValue() const {
    return m_value;
}

unsigned int Data1D::getHeadcount() const {
    return m_headcount;
}

// Setters
void Data1D::setValue(float value) {
    m_value = value;
}

void Data1D::setHeadcount(unsigned int eff) {
    m_headcount = eff;
}

std::ostream& operator<<(std::ostream& lhs, const Data1D& rhs) {
    lhs << rhs.m_value;
    return lhs;
}
