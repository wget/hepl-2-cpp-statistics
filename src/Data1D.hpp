#ifndef DATA1D_HPP_INCLUDED
#define DATA1D_HPP_INCLUDED

#include <ostream>

class Data1D {

    private:
        float m_value;
        unsigned int m_headcount;

    public:
        // Getters
        float getValue() const;
        unsigned int getHeadcount() const;

        // Setters
        void setValue(float value);
        void setHeadcount(unsigned int eff);

        // Others
        // Needed because in Cell.ipp we have a function displaying the value
        // of the Cell content.
        // src/Cell.ipp:34:15
        // std::cout << m_value << std::endl
        friend std::ostream& operator<<(std::ostream& lhs, const Data1D& rhs);
};

#endif // DATA1D_HPP_INCLUDED
