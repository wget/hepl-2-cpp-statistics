#ifndef DATASOURCESERIECONTINUE_HPP_INCLUDED
#define DATASOURCESERIECONTINUE_HPP_INCLUDED

#include "./lib/utils/src/HeplSortedList.hpp"
#include "DataSource.hpp"
#include "Data1D.hpp"

class DataSourceSerieContinue: public DataSource {

    private:
        HeplList<Data1D> m_itemOccurrenceList;
        HeplSortedList<double> m_sortedList;
        HeplList<HeplList<double>> m_rangeOccurrenceList;
        double m_start;
        double m_interval;

    public:
        // Constructors
        DataSourceSerieContinue();

        // Getters
        const HeplList<Data1D>& getItemOccurrenceList();
        const HeplSortedList<double>& getSortedList();
        const HeplList<HeplList<double>>& getRangeOccurrenceList();
        double getStart() const;
        double getInterval() const;

        // Setters
        void setItemOccurrenceList(const HeplList<Data1D>& itemOccurrenceList);
        void setSortedList(const HeplSortedList<double>& sortedList);
        void setRangeOccurrenceList(const HeplList<HeplList<double>>& rangeOccurrenceList);
        void setStart(const double& start);
        void setInterval(const double& interval);
};

#endif // DATASOURCESERIECONTINUE_HPP_INCLUDED
