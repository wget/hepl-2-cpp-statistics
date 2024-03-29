#ifndef DATASOURCESERIE2D
#define DATASOURCESERIE2D

#include "./lib/utils/src/HeplList.hpp"
#include "DataSource.hpp"
#include "Data2D.hpp"

class DataSourceSerie2D: public DataSource {

    private:
        HeplList<Data2D> m_list;
        HeplString m_subject2;
        char m_type2;

    public:
        // Constructors
        DataSourceSerie2D();

        // Getters
        const HeplList<Data2D>& getList();
        HeplString getSubject2() const;
        char getType2() const;

        // Setters
        void setList(const HeplList<Data2D>& list);
        void setSubject2(const HeplString& subject);
        void setType2(const char& type);
};


#endif // DATASOURCESERIE2D
