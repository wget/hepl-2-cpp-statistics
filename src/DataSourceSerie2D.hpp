#ifndef DATASOURCESERIE2D_HPP_INCLUDED
#define DATASOURCESERIE2D_HPP_INCLUDED

#include "./lib/utils/src/HeplBaseException.hpp"
#include "./lib/utils/src/HeplString.hpp"
#include "Data2D.hpp"

class DataSourceSerie2D {


    private:

        HeplString m_subject2;
        char m_type2;


    public:
        // Getters
        HeplString getSubject2() const;
        char getType2() const;

        // Setters
        void setSubject2(HeplString subject);
        void setType2(char type);
};

#endif  // DATASOURCESERIE2D_HPP_INCLUDED
