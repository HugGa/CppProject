#pragma once
#include <map>
#include <vector>
#include <limits>
#include <stdexcept>
#include <cassert>
#include <fstream>
#include <string>
#include <iostream>
namespace Hugh
{
class Stock
{
    std::map<int, double> yearPercents;
    std::vector<double> Percents;
    int startYear;
    int endYear;

  public:
    Stock(std::string table)
    {
        std::ifstream file(table);
        if (!file.is_open())
        {
            throw std::exception("Stuff");
        }
        while (!file.eof())
        {
            int year;
            file >> year;
            file.get();
            double val;
            file >> val;
            file.get();
            yearPercents[year] = val;
        }
        Percents.resize(yearPercents.size());
        Percents[0] = 0;
        auto begin = yearPercents.begin();
        auto begin2 = yearPercents.begin();
        std::advance(begin2, 1);
        auto end = yearPercents.end();
        for (int i = 1; i < yearPercents.size() && begin2 != end; i++, begin++, begin2++)
        {
            Percents[i] = ((begin2->second - begin->second) / begin->second) * 100;
        }
    }
    inline int getStartYear()
    {
        return startYear;
    }
    inline int getEndYear()
    {
        return endYear;
    }
    using percent_iterator = std::vector<double>::iterator;
    using cr_percent_iterator = std::vector<double>::reverse_iterator;
    inline percent_iterator begin()
    {
        return Percents.begin();
    }
    inline auto crbegin() -> decltype(Percents.crbegin())
    {
        return Percents.crbegin();
    }
    inline auto crend() -> decltype(Percents.crbegin())
    {
        return Percents.crend();
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
        return invested * (Percents[end] - Percents[start]) / (end - start);
    }
    inline double operator[](int year)
    {
        return Percents[year];
    }
    inline double at(int year)
    {
        return yearPercents[year];
    }
};
} // namespace Hugh