#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

///------------------------------------------------------
/// Design a greedy algorithm that given a set of coins that includes 1
/// returns the minimum number of coins necessary to represent the amount
/// Pre-requisites: coins are NOT given in sorted order
/// Requirement: If you have "n" coins, your algorithm must run in O(nlogn)
///
int MinCoinExchange(vector<int>& coins, int amount) {

	sort(coins.begin(), coins.end());
    int size = coins.size();
    int coinsNumber = 0;
    for (int i = size - 1; i >= 0; i--)
	{
        while (amount >= coins[i]) 
		{
            amount -= coins[i];
            coinsNumber++;
        }
    }
    return coinsNumber;
}