#pragma once
#include <map>
#include <array>
#include <fstream>
#include <string>
#include <vector>
namespace Hugh
{
struct InflationTable
{
    std::map<int, std::array<double, 13>> Mapping;
    std::vector<double> Percents;
    std::vector<double> YearMappings;

  public:
    using iterator = std::vector<double>::iterator;
    using riterator = std::vector<double>::reverse_iterator;
    InflationTable(std::string table)
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
            std::array<double, 13> months;
            file.get();
            for (int i = 0; i < months.size(); i++)
            {
                double val;
                file >> val;
                file.get();
                months[i] = val;
            }
            Mapping[year] = months;
        }
        YearMappings.resize(Mapping.size());
        auto it = Mapping.begin();
        for (int i = 0; i < Mapping.size() && it != Mapping.end(); i++, it++)
        {
            YearMappings[i] = it->second[12];
        }
        Percents.resize(Mapping.size());
        Percents[0] = 0;
        auto begin = Mapping.begin();
        auto begin2 = Mapping.begin();
        std::advance(begin2, 1);
        auto end = Mapping.end();
        for (int i = 1; i < Mapping.size() && begin2 != end; i++, begin++, begin2++)
        {
            Percents[i] = ((begin2->second[12] - begin->second[12]) / begin->second[12]) * 100;
        }
    }
    iterator begin()
    {
        return YearMappings.begin();
    }
    iterator end()
    {
        return YearMappings.end();
    }
    auto crbegin() -> decltype(YearMappings.crbegin())
    {
        return YearMappings.crbegin();
    }
    auto crend() -> decltype(YearMappings.crbegin())
    {
        return YearMappings.crend();
    }
    size_t size()
    {
        return Mapping.size();
    }
    inline double at(int year)
    {
        return Mapping[year][12];
    }
    double operator[](int year)
    {
        return YearMappings[year];
    }
    friend std::ostream &operator<<(std::ostream &stream, const InflationTable &table)
    {
        for (auto v : table.Mapping)
        {
            stream << v.first;
            for (auto va : v.second)
            {
                stream << "," << va;
            }
            stream << std::endl;
        }
        return stream;
    }
    double getYearReturnPercent(int year)
    {
        return YearMappings[year];
    }
    double CalculateInflation(int startYear, int endYear, double amount)
    {
        double inflate = (Mapping[startYear][12] - Mapping[endYear][12]) / Mapping[startYear][12];
        return amount * inflate;
    }
};
}; // namespace Hugh