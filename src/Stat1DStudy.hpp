#ifndef STAT1DSTUDY_HPP_INCLUDED
#define STAT1DSTUDY_HPP_INCLUDED

#include "./lib/utils/src/HeplBaseException.hpp"
#include "Sample.hpp"
#include "DataSourceSerieDiscrete.hpp"
#include "DataSourceSerieContinue.hpp"
// We want ceil() and floor() to compute the median properly.
#include <cmath>
// For atof()
#include <cstdlib>
// For setw() used in streams
#include <iomanip>

class Stat1DStudy {

    private:
        // Model members
        const HeplString FILE_DELIMITER = ":";
        Sample *m_sample;
        double m_range;
        double m_mean;
        double m_median;
        double *m_mode;
        double m_sd;
        double m_variationCoefficient;
        double m_dataControlMin;
        double m_dataControlMax;
        // Used to change the report appearance and display it as ranges
        // instead of a grouped occurrence list.
        bool m_startIntervalSet = false;

        // Utilities methods
        void parseToSample(const HeplString& filename, int column);
        void computeStats();
        void displayRecords() const;
        HeplList<HeplBaseException> isFileMalformed(const HeplString& filename) const;
        HeplList<Data1D> getItemOccurrenceList(const HeplSortedList<double>& sortedList);
        HeplList<HeplList<double>> getRangeOccurrenceList(const HeplList<Data1D>& itemOccurrenceList);

    public:
        // Constructors
        Stat1DStudy(HeplString filename, int column);

        // Others
        void displayReport() const;

        Sample* getSample() const;

        // Statistical methods
        unsigned int getTotalHeadcount() const;
        double getRange() const;
        double getMean() const;
        double getMedian() const;
        double *getMode() const;
        double getStandardDeviation() const;
        double getVariationCoefficient() const;
        double getMinValueFromSample() const;
        double getMaxValueFromSample() const;

        // Destructor
        ~Stat1DStudy();
};

// Graphical stuff
#include <QApplication>
#include "./lib/graph/Graph1DDiscrete/graphstat1ddiscrete.h"
extern QApplication *qtApp;

#endif // STAT1DSTUDY_HPP_INCLUDED
