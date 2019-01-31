#include <iostream>
#include <fstream>
#include "Stock.h"
#include "Inflation.h"
#include "Eigen/Dense"
using namespace Hugh;
int main()
{
    InflationTable table("series.csv");
    std::fstream ofile;
    ofile.open("series3.csv",std::ios::out);
    ofile << table;
    std::cout << "Is open: " << ofile.is_open() << std::endl;
}