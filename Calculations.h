#pragma once
#include <cmath>
#include "Returns.h"
namespace Hugh
{
inline double average(Stock stock)
{
    double sum = 0;
    for (auto i = stock.begin(); i < stock.end(); i++)
    {
        sum += *i;
    }
    return sum / stock.size();
}
inline double average(Stock stock, size_t size)
{
    double sum = 0;
    for (size_t i = 0; i < size; i++)
    {
        sum += stock[i];
    }
    return sum / size;
}
inline double Variance(Stock stock)
{
    double avg = average(stock);
    double sum = 0;
    for (auto i = stock.begin(); i < stock.end(); i++)
    {
        sum += pow(*i - avg, 2);
    }
    return sum / stock.size();
}
inline double Stddev(Stock stock)
{
    return sqrt(Variance(stock));
}
inline double Covariance(Stock stock1, Stock stock2, size_t datasize)
{
    double sum = 0;
    double avg1 = average(stock1, datasize), avg2 = average(stock2, datasize);
    for (size_t i = 0; i < datasize; i++)
    {
        sum += (stock1[i] - avg1) * (stock2[i] - avg2);
    }
    return sum / (datasize - 1);
}
inline double Correlation(Stock stock1, Stock stock2, size_t dataSize)
{
    return Covariance(stock1, stock2, dataSize) / (Stddev(stock1) * Stddev(stock2));
}
// calculates compound annual return based on years, starting, and ending
inline double CalcCAGR(int years, double start, double ending)
{
    return pow(ending / start, 1 / years) - 1;
}
inline double CalcCAGR(int startYear, int endYear, Stock stock)
{
    int startIndex = stock.getStartYear() - startYear;
    int endIndex = startIndex + endYear - startYear;
    return CalcCAGR(endYear - startYear, stock.getReturnPercent(startIndex), stock.getReturnPercent(endIndex));
}
} // namespace Hugh