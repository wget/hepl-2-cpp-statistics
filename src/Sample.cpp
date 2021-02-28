#include "Sample.hpp"

Sample::Sample() {
    m_source = nullptr;
}

Sample::Sample(DataSource *source) {
    m_source = source;
}

DataSource* Sample::getDataSource() {
    return m_source;
}

void Sample::setDataSource(DataSource *source) {
    m_source = source;
}

Sample::~Sample() {
    if (m_source != nullptr) {
        delete m_source;
    }
}
