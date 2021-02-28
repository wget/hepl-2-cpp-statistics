#include "DataSourceSerieDiscrete.hpp"

// Constructors
DataSourceSerieDiscrete::DataSourceSerieDiscrete():
    m_itemOccurrenceList(), m_sortedList() {
}

// Getters
const HeplList<Data1D>& DataSourceSerieDiscrete::getItemOccurrenceList() {
    return m_itemOccurrenceList;
}

const HeplSortedList<double>& DataSourceSerieDiscrete::getSortedList() {
    return m_sortedList;
}

// Setters
void DataSourceSerieDiscrete::setItemOccurrenceList(const HeplList<Data1D>& itemOccurrenceList) {
    m_itemOccurrenceList = itemOccurrenceList;
}

void DataSourceSerieDiscrete::setSortedList(const HeplSortedList<double>& sortedList) {
    m_sortedList = sortedList;
}
