#include "Data2D.hpp"
 
// Constructors
Data2D::Data2D() = default;

Data2D::Data2D(double value1, double value2) {
    m_value1 = value1;
    m_value2 = value2;
}

// Getters
double Data2D::getValue1() const {
    return m_value1;
}

double Data2D::getValue2() const {
    return m_value2;
}

// Setters
void Data2D::setValue1(double value) {
    m_value1 = value;
}

void Data2D::setValue2(double value) {
    m_value2 = value;
}

bool Data2D::operator<(const Data2D& rhs) const {
    if (m_value1 < rhs.m_value1 && m_value2 < rhs.m_value2) {
        return true;
    }
    return false;
}

std::ostream& operator<<(std::ostream& lhs, const Data2D& rhs) {
    lhs << "[ " << rhs.m_value1 << ", " << rhs.m_value2 << " ]";
    return lhs;
}
