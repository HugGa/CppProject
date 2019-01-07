#pragma once
#include <map>
#include <vector>
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
    // THIS FUNCTION DOES IT BASED ON ACTUAL YEARS INPUT
    inline double calcReturns(int start, int end, double invested)
    {
    }
};
} // namespace Hugh