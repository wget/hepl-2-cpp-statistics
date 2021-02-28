#ifndef DATASOURCE_HPP_INCLUDED
#define DATASOURCE_HPP_INCLUDED

#include "./lib/utils/src/HeplBaseException.hpp"
#include "./lib/utils/src/HeplString.hpp"

class DataSource {
    protected:
        HeplString m_name;
        HeplString m_subject;
        unsigned int m_totalHeadcount;
        char m_type;

    public:
        virtual ~DataSource();

        // Getters
        HeplString getName() const;
        HeplString getSubject() const;
        unsigned int getTotalHeadcount() const;
        char getType() const;

        // Setters
        void setName(HeplString name);
        void setSubject(HeplString subject);
        void setTotalHeadcount(unsigned int totalHeadcount);
        void setType(char type);
};

class DataSourceItemNotFoundException: HeplBaseException {
    using HeplBaseException::HeplBaseException;
};

#endif // DATASOURCE_HPP_INCLUDED
