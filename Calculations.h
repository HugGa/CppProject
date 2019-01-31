#pragma once
#include <cmath>
#include <numeric>
#include "Returns.h"
namespace Hugh
{
inline double average(Stock stock)
{
    return std::accumulate(stock.begin(), stock.end(), 0) / stock.size();
}
inline double average(Stock stock, size_t size)
{
    auto advanced = stock.begin();
    std::advance(advanced, size);
    return std::accumulate(stock.begin(), advanced, 0) / size;
}
inline double Variance(Stock stock)
{
    double avg = average(stock);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    return std::accumulate(stock.begin(), stock.end(), 0, func) / stock.size();
}
inline double Variance(Stock stock, size_t datasize)
{
    double avg = average(stock, datasize);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    auto advanced = stock.begin();
    std::advance(advanced, datasize);
    return std::accumulate(stock.begin(), stock.end(), 0, func) / stock.size();
}
inline double Stddev(Stock stock)
{
    return sqrt(Variance(stock));
}
inline double Stddev(Stock stock, size_t datasize)
{
    return sqrt(Variance(stock, datasize));
}
inline double Covariance(Stock stock1, Stock stock2, size_t datasize)
{
    double avg1 = average(stock1, datasize), avg2 = average(stock2, datasize);
    double sum = 0;
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