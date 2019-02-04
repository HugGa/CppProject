#include <iostream>
#include <fstream>
#include "Stock.h"
#include "Inflation.h"
#include "Calculations.h"
#include "Eigen/Dense"
#include <iomanip>
using namespace Hugh;
int main()
{
    try
    {
        std::cout << "CAGR is wrong because the values are too small for calculating with double-precision floating point" << std::endl;
        Stock stock("SStock.csv");
        std::cout << "Kind\t\tCAGR\tAverage\t\tVariance\tSTDDEV" << std::endl;
        std::cout << "Small stocks:\t" << std::setprecision(9) << Hugh::CalcCAGR(1929, 2015, stock);
        std::cout << "\t" << Hugh::average(stock);
        std::cout << "\t" << Hugh::Variance(stock);
        std::cout << "\t" << Hugh::Stddev(stock) << std::endl;
        Stock stock1("LStock.csv");
        std::cout << "Large stocks:\t" << std::setprecision(9) << Hugh::CalcCAGR(1929, 2015, stock1);
        std::cout << "\t" << Hugh::average(stock1);
        std::cout << "\t" << Hugh::Variance(stock1);
        std::cout << "\t" << Hugh::Stddev(stock1) << std::endl;
        InflationTable table("InflationS.csv");
        std::cout << "Inflation:\t" << std::setprecision(9) << Hugh::CalcCAGR(1929, 2015, table);
        std::cout << "\t" << Hugh::average(table);
        std::cout << "\t" << Hugh::Variance(table);
        std::cout << "\t" << Hugh::Stddev(table) << std::endl;

        std::cout << "Correlation between small and large stock for 50 years: " << Hugh::Correlation(stock, stock1, 50) << std::endl;
        std::cout << "Correlation between small stock and inflation for 50 years: " << Hugh::Correlation(stock, table, 50) << std::endl;
        std::cout << "Correlation between large stock and inflation for 50 years: " << Hugh::Correlation(stock1, table, 50) << std::endl;

        std::cout << "No matter what I do, I cannot figure out how to do the model portfolio section, as it's such as complex topic I don't even know where to start"
                     "I know I've dissapointed you in this, as well as the fact that I can't seem to find any more data than I did in an easy to use format, but that's how my life goes";
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
}