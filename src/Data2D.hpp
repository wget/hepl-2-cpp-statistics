#ifndef DATA2D_HPP_INCLUDED
#define DATA2D_HPP_INCLUDED

#include <ostream>

class Data2D {

    private:
        double m_value1;
        double m_value2;

    public:

        // Constructors
        Data2D();
        Data2D(double value1, double value2);

        // Getters
        double getValue1() const;
        double getValue2() const;

        // Setters
        void setValue1(double value);
        void setValue2(double value);

        // Others
        bool operator<(const Data2D& rhs) const;

        // Needed because in Cell.ipp we have a function displaying the value
        // of the Cell content.
        // src/Cell.ipp:34:15
        // std::cout << m_value << std::endl
        friend std::ostream& operator<<(std::ostream& lhs, const Data2D& rhs);
};

#endif // DATA2D_HPP_INCLUDED
