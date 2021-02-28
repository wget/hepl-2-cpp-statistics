#include "Stat2DStudy.hpp"

// Constructors
Stat2DStudy::Stat2DStudy(HeplString filename, int column) {
    this->m_sample = nullptr;
}

// Getters
Sample* Stat2DStudy::getSample() const {
    return m_sample;
}

double Stat2DStudy::getMean1() const {
    return m_mean1;
}

double Stat2DStudy::getMean2() const {
    return m_mean2;
}

double Stat2DStudy::getCoeff1() const {
    return m_coeff1;

}

double Stat2DStudy::getCoeff2() const {
    return m_coeff2;
}

double Stat2DStudy::getCoeffCorrelation() const {
    return m_coeffCorrelation;
}

// Setters
void Stat2DStudy::setCoeff1() {
}

void Stat2DStudy::setCoeff2() {
}

void Stat2DStudy::setCoeffCorrelation(double coeff) {
    m_coeffCorrelation = coeff;
}
