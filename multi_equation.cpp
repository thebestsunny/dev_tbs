/**
 *
 *  @copyright       Copyright (c) 2021 By
 *             HANAKU STUDIO(Frank Service Centre)
 *                    All Rights Reserved
 * 
 *  @file  mulit_equation.cpp
 * 
 *  @brief  正整数系多元一次方程求解工具
 *  @details  
 *
 *  @author  XIANG ZHEYU
 *  @date  2021/01/25
 */

/*******************************************************************************
 **  HEADER FILE
 ******************************************************************************/

#include <cassert>
#include <cstring>
#include <string.h>
#include <sstream>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;


bool TryFactor(int sum, int factor, int& sol)
{
    while(true)
    {
        //从1开始试解，如果恰好满足系数乘以解等于合值，则返回true与解值，否则返回false
        if(factor * sol == sum)
        {
            return true;
        }
        else if(factor * sol > sum)
        {
            sol--;
            return false;
        }

        sol++;
    }
}

void PrintSolution(vector<int>& factors, vector<int>&solution)
{
    if(factors.size() != solution.size())
    {
        for (int i = solution.size(); i < factors.size(); i++)
        {
            solution.push_back(0);
        }
    }

    for (int i = 0; i < factors.size() - 1; i++)
    {
        cout << "x" << i+1 << " = " << solution[i] << ", ";
    }
    cout << "x" << factors.size() << " = " << solution[factors.size()-1] << endl;
}

void Cal(vector<int>& factors, int sum, int index = 0, vector<int> solution = vector<int> ())
{
    if(sum == 0 || factors.size() == 0)
    {
        return;
    }
    else if(index == 0)
    {
        cout << "Equation:" << endl;
        for (int i = 0; i < factors.size()-1; i++)
        {
            cout << factors[i] << "*x" << i+1 << " + ";
        }
        cout << factors[factors.size()-1] << "*x" << factors.size() << " = " << sum << endl;
        cout << "Solutions:" << endl;
    }

    bool solved = false;
    int i = 0;
    if(TryFactor(sum, factors[index], i))
    {
        //如果尝试至第index位系数时，恰好得到一组解，则返回0，并输出解值
        vector<int> solCopy = solution;
        solCopy.push_back(i);
        solved = true;
        PrintSolution(factors, solCopy);       
    }

    if(index == factors.size() - 1)
    {
        return;
    }

    //开始迭代尝试下一位系数
    for(int j = i; j>=0; j--)
    {
        vector<int> solCopy = solution;
        solCopy.push_back(j);
        Cal(factors, sum - factors[index] * j, index + 1, solCopy);
    }

}


int main(int arhc, char **arhv)
{
    vector<int> factors = {27,24,10,21,25}; 
    Cal(factors, 261);

    return 0;
}

