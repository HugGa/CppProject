#pragma once
#include <map>
#include <array>
#include <fstream>
#include <string>
namespace Hugh
{
struct InflationTable
{
    std::map<int, std::array<double, 13>> Mapping;

  public:
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
    double CalculateInflation(int startYear, int endYear, double amount)
    {
        double inflate = (Mapping[startYear][12] - Mapping[endYear][12]) / Mapping[startYear][12];
        return amount * inflate;
    }
};
}; // namespace Hugh