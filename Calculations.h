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
inline double Covariance(Stock stock)
{
    double sum = 0;
    for (int i = 0; i < stock.size(); i++)
    {
    }
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