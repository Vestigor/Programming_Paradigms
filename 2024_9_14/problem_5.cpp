/***********************************************************
* File:     problem_3.cpp
* Author:   Xiaolong Ma(ÂíÐ¡Áú)
* E-mail:   2353814@tongji.edu.cn
* Compiler: Visual Studio 2022
* Function: maximize stock profit
* Date:     2024.9.17
* Update:   2024.9.20
***********************************************************/

#include <iostream>
#include <vector>
#include <limits>

/***********************************************************
* Function Name:   ClearBuffer
* Function:        clear the buffer to prevent impact on subsequent input
* Input Parameter:
* Returned Value:
***********************************************************/
void ClearBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

/***********************************************************
* Function Name:   MaximizeStockProfit
* Function:        calculate maximum profit
* Input Parameter: prices: record daily stock prices
*                  daynum:total days
* Returned Value:  maximumprofit: maximum profit
***********************************************************/
int MaximizeStockProfit(std::vector<int> prices,int num_day)
{
    int maximum_profit = 0, min_price = prices[0];
    for (int i = 1; i < num_day; ++i) {
        if (prices[i] < min_price)
            min_price = prices[i];
        else
            maximum_profit = maximum_profit > prices[i] - min_price ? maximum_profit : prices[i] - min_price;//Calculate the current price, compare it with the lowest price, and take the lowest value
    }
    return maximum_profit;
}

/***********************************************************
* Function Name:   main
* Function:        input&output
* Input Parameter: 
* Returned Value:  0
***********************************************************/
int main() 
{
    int num_day;
    std::cout << "Please input the total number of days(1~105): ";
    while (true) {
        std::cin >> num_day;
        if (std::cin.fail() || num_day < 1 || num_day>105) {
            std::cout << "Input error, please re-input: ";
            ClearBuffer();
            continue;
        }
        ClearBuffer();
        break;
    }
    std::vector<int> prices(num_day);
    for(int i=0;i< num_day;i++)
        while (true) {
            std::cout << "Please input the stock price for day " << (i + 1) << "(0~104): ";
            std::cin >> prices[i];
            if (std::cin.fail() || prices[i] < 0 || prices[i]>104) {
                std::cout << "Input error, please re-input\n";
                ClearBuffer();
                continue;
            }
            ClearBuffer();
            break;
        }
    std::cout << "\nThe maximum profit is "<< MaximizeStockProfit(prices, num_day)<<".\n";

    return 0;
}