#include "DataSourceSerieContinue.hpp"

// Constructors
DataSourceSerieContinue::DataSourceSerieContinue():
    m_itemOccurrenceList(), m_sortedList(), m_rangeOccurrenceList() {
}

// Getters
const HeplList<Data1D>& DataSourceSerieContinue::getItemOccurrenceList() {
    return m_itemOccurrenceList;
}

const HeplSortedList<double>& DataSourceSerieContinue::getSortedList() {
    return m_sortedList;
}

const HeplList<HeplList<double>>& DataSourceSerieContinue::getRangeOccurrenceList() {
    return m_rangeOccurrenceList;
}

double DataSourceSerieContinue::getStart() const {
    return m_start;
}

double DataSourceSerieContinue::getInterval() const {
    return m_interval;
}

// Setters
void DataSourceSerieContinue::setItemOccurrenceList(const HeplList<Data1D>& itemOccurrenceList) {
    m_itemOccurrenceList = itemOccurrenceList;
}

void DataSourceSerieContinue::setSortedList(const HeplSortedList<double>& sortedList) {
    m_sortedList = sortedList;
}

void DataSourceSerieContinue::setRangeOccurrenceList(const HeplList<HeplList<double>>& rangeOccurrenceList) {
    m_rangeOccurrenceList = rangeOccurrenceList;
}

void DataSourceSerieContinue::setStart(const double& start) {
    m_start = start;
}

void DataSourceSerieContinue::setInterval(const double& interval) {
    m_interval = interval;
}
