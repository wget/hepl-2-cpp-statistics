#ifndef STAT2DSTUDY_HPP_INCLUDED
#define STAT2DSTUDY_HPP_INCLUDED

#include "./lib/utils/src/HeplString.hpp"
#include "Sample.hpp"

class Stat2DStudy {

    private:
        // Model members
        const HeplString FILE_DELIMITER = ":";
        Sample *m_sample;
        double m_mean1;
        double m_mean2;
        double m_coeff1;
        double m_coeff2;
        double m_coeffCorrelation;

    public:
        // Constructors
        Stat2DStudy(HeplString filename, int column);

        // Others
        void displayReport() const;
        Sample* getSample() const;

        double getMean1() const;
        double getMean2() const;
        double getCoeff1() const;
        double getCoeff2() const;
        double getCoeffCorrelation() const;

        void setCoeff1();
        void setCoeff2();
        void setCoeffCorrelation(double coeff);
};

#endif // STAT2DSTUDY_HPP_INCLUDED
