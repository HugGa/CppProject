#pragma once
#include <cmath>
#include <numeric>
#include <iostream>
#include "Inflation.h"
#include "Stock.h"
#include <cassert>
namespace Hugh
{
inline double average(InflationTable table)
{
    return std::accumulate(table.begin(), table.end(), 0.0) / table.size();
}
inline double average(Stock stock)
{
    return std::accumulate(stock.begin(), stock.end(), 0.0) / stock.size();
}
inline double average(InflationTable stock, size_t size)
{
    auto advanced = stock.begin();
    std::advance(advanced, size);
    return std::accumulate(stock.begin(), advanced, 0.0) / size;
}
inline double caverage(InflationTable stock, size_t size)
{
    auto advanced = stock.crbegin();
    std::advance(advanced, size);
    return std::accumulate(stock.crbegin(), advanced, 0.0) / size;
}
inline double caverage(Stock stock, size_t size)
{
    auto advanced = stock.crbegin();
    std::advance(advanced, size);
    return std::accumulate(stock.crbegin(), advanced, 0.0) / size;
}
inline double average(Stock stock, size_t size)
{
    auto advanced = stock.begin();
    std::advance(advanced, size);
    return std::accumulate(stock.begin(), advanced, 0.0) / size;
}
inline double Variance(Stock stock)
{
    double avg = average(stock);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    return std::accumulate(stock.begin(), stock.end(), 0.0, func) / stock.size();
}

inline double Variance(InflationTable stock)
{
    double avg = average(stock);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    return std::accumulate(stock.begin(), stock.end(), 0.0, func) / stock.size();
}

inline double Variance(InflationTable stock, size_t datasize)
{
    double avg = average(stock, datasize);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    auto advanced = stock.begin();
    std::advance(advanced, datasize);
    return std::accumulate(stock.begin(), stock.end(), 0.0, func) / stock.size();
}
inline double Variance(Stock stock, size_t datasize)
{
    double avg = average(stock, datasize);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    auto advanced = stock.begin();
    std::advance(advanced, datasize);
    return std::accumulate(stock.begin(), stock.end(), 0.0, func) / stock.size();
}
inline double cVariance(InflationTable stock, size_t datasize)
{
    double avg = caverage(stock, datasize);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    auto advanced = stock.crbegin();
    std::advance(advanced, datasize);
    return std::accumulate(stock.crbegin(), stock.crend(), 0.0, func) / stock.size();
}
inline double cVariance(Stock stock, size_t datasize)
{
    double avg = caverage(stock, datasize);
    auto func = [avg](double val, double it) {
        return val + pow(it - avg, 2);
    };
    auto advanced = stock.crbegin();
    std::advance(advanced, datasize);
    return std::accumulate(stock.crbegin(), stock.crend(), 0.0, func) / stock.size();
}
inline double Stddev(Stock stock)
{
    return sqrt(Variance(stock));
}
inline double Stddev(InflationTable stock)
{
    return sqrt(Variance(stock));
}
inline double Stddev(Stock stock, size_t datasize)
{
    return sqrt(Variance(stock, datasize));
}
inline double Stddev(InflationTable stock, size_t datasize)
{
    return sqrt(Variance(stock, datasize));
}
template <typename T, typename T2>
inline double Covariance(T stock1, T2 stock2, size_t datasize)
{
    double avg1 = caverage(stock1, datasize), avg2 = caverage(stock2, datasize);
    double sum = 0;
    for (size_t i = 0; i < datasize; i++)
    {
        sum += (stock1[i] - avg1) * (stock2[i] - avg2);
    }
    return sum / (datasize - 1);
}
inline double Correlation(Stock stock1, Stock stock2, size_t dataSize)
{
    std::cout << "WTF1";
    return Covariance(stock1, stock2, dataSize) / (Stddev(stock1) * Stddev(stock2));
}
template <typename T, typename T2>
inline double Correlation(T tab, T2 tab2, size_t datasize)
{
    std::cout << "WTF";
    return Covariance(tab, tab2, datasize) / (Stddev(tab, datasize) * Stddev(tab2, datasize));
}
// calculates compound annual return based on years, starting, and ending
inline double CalcCAGR(int years, double start, double ending)
{
    return pow(ending / start, 1 / years) - 1;
}
template <typename T>
inline double CalcCAGR(int startYear, int endYear, T stock)
{
    return CalcCAGR(endYear - startYear, stock.at(startYear), stock.at(endYear));
}
} // namespace Hugh