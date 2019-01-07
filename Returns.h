#pragma once
#include <vector>
#include "Stock.h"
namespace Hugh
{
struct Invested
{
    int investStart;
    int investEnd;
    Stock value;
    double percentage;
    double investedStart;
};
class Portfolio
{
    std::vector<Invested> portfolioValues;

  public:
    double weightedAverageReturn()
    {
        double sum = 0;
        for (auto i = portfolioValues.begin(); i < portfolioValues.end(); i++)
        {
            sum += i->percentage * i->value->calcReturns(i->investStart, i->investEnd, i->investedStart);
        }
        return sum;
    }
};
} // namespace Hugh