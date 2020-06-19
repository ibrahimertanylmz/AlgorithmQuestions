#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

///------------------------------------------------------
/// Design a dynamic programming algorithm that given a set of coins that includes 1
/// returns the minimum number of coins necessary to represent the amount
///
int MinCoinExchangeDP(vector<int>& coins, int amount) {

	int m = coins.size() / coins[0];	
	int* table = new int[amount];

	// Base case (verilen deðer 0'sa) 
	table[0] = 0;

	// tüm deðerler initialize edilir 
	for (int i = 1; i <= amount; i++)
		table[i] = INT_MAX;

	//amount'a kadar tüm deðerler için gereke minimum coin hesaplanýr
	for (int i = 1; i <= amount; i++)
	{
		// i'den küçük tüm coinler için
		for (int j = 0; j < m; j++)
			if (coins[j] <= i)
			{
				int sub_res = table[i - coins[j]];
				if (sub_res != INT_MAX && sub_res + 1 < table[i])
					table[i] = sub_res + 1;
			}
	}
	return table[amount];
} //end-MinCoinExchangeDP
