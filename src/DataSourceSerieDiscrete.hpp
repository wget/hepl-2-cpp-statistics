#ifndef DATASOURCESERIEDISCRETE_HPP_INCLUDED
#define DATASOURCESERIEDISCRETE_HPP_INCLUDED

#include "./lib/utils/src/HeplSortedList.hpp"
#include "DataSource.hpp"
#include "Data1D.hpp"

class DataSourceSerieDiscrete: public DataSource {

    private:
        HeplList<Data1D> m_itemOccurrenceList;
        HeplSortedList<double> m_sortedList;

    public:
        // Constructors
        DataSourceSerieDiscrete();

        // Getters
        const HeplList<Data1D>& getItemOccurrenceList();
        const HeplSortedList<double>& getSortedList();

        // Setters
        void setItemOccurrenceList(const HeplList<Data1D>& itemOccurrenceList);
        void setSortedList(const HeplSortedList<double>& sortedList);
};

#endif // DATASOURCESERIEDISCRETE_HPP_INCLUDED
