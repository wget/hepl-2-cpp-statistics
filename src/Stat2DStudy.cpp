#include "Stat2DStudy.hpp"

// Constructors
Stat2DStudy::Stat2DStudy(HeplString filename, int column) {
    this->m_sample = nullptr;
}

// Getters
Sample* Stat2DStudy::getSample() const {
    return m_sample;
}

double Stat2DStudy::getMeanA() const {
    return m_meanA;
}

double Stat2DStudy::getMeanB() const {
    return m_meanB;
}

double Stat2DStudy::getCoeffA() const {
    return m_coeffA;

}

double Stat2DStudy::getCoeffB() const {
    return m_coeffB;
}

double Stat2DStudy::getCoeffCorrelation() const {
    return m_coeffCorrelation;
}

// Setters
void Stat2DStudy::setCoeffA() {
}

void Stat2DStudy::setCoeffB() {
}

void Stat2DStudy::setCoeffCorrelation(double coeff) {
    m_coeffCorrelation = coeff;
}
