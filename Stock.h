#pragma once
#include <map>
#include <vector>
#include <limits>
#include <stdexcept>
#include <cassert>
namespace Hugh
{
class Stock
{
    std::map<int, double> yearPercents;
    std::vector<double> Percents;
    int startYear;
    int endYear;

  public:
    inline int getStartYear()
    {
        return startYear;
    }
    inline int getEndYear()
    {
        return endYear;
    }
    using percent_iterator = std::vector<double>::iterator;
    inline percent_iterator begin()
    {
        return Percents.begin();
    }
    inline percent_iterator end()
    {
        return Percents.end();
    }
    inline size_t size()
    {
        return Percents.size();
    }
    // THIS FUNCTION IS BASED ON THE ACTUAL YEAR YOU HAVE, NOT ANYTHING ELSE
    inline double getYearReturnPercent(int year)
    {
        return yearPercents[year];
    }
    // THIS TAKES INDEX, NOT YEAR
    inline double getReturnPercent(int index)
    {
        return Percents[index];
    }
    inline double logReturns(size_t start, size_t end, double invested)
    {
        assert(end > Percents.size() && "End is past beginning");
        return log(calcReturns(start, end, invested) / invested);
    }
    // THIS FUNCTION DOES IT BASED ON YEARS OFFSET INPUT
    // MAX DOUBLE = ERROR
    inline double calcReturns(size_t start, size_t end, double invested)
    {
        assert(end > Percents.size() && "End is past beginning");
        for (size_t i = start; i < end; i++)
        {
            double multi = Percents[i];
            if (!signbit(multi))
            {
                multi++;
            }
            else
            {
                multi = std::abs(1 / multi);
            }
            invested *= multi;
        }
        return invested;
    }
    inline double operator[](int year)
    {
        return Percents[year];
    }
};
} // namespace Hugh