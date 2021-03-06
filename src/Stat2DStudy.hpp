#ifndef STAT2DSTUDY_HPP_INCLUDED
#define STAT2DSTUDY_HPP_INCLUDED

#include "./lib/utils/src/HeplString.hpp"
#include "Sample.hpp"

class Stat2DStudy {

    private:
        // Model members
        const HeplString FILE_DELIMITER = ":";
        Sample *m_sample;
        double m_meanA;
        double m_meanB;
        double m_coeffA;
        double m_coeffB;
        double m_coeffCorrelation;

    public:
        // Constructors
        Stat2DStudy(HeplString filename, int column);

        // Others
        void displayReport() const;
        Sample* getSample() const;

        double getMeanA() const;
        double getMeanB() const;
        double getCoeffA() const;
        double getCoeffB() const;
        double getCoeffCorrelation() const;

        void setCoeffA();
        void setCoeffB();
        void setCoeffCorrelation(double coeff);
};

#endif // STAT2DSTUDY_HPP_INCLUDED
