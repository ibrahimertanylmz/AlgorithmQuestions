#include <stdio.h>
#include <iostream>
#include <vector>

using namespace std;

///------------------------------------------------------
/// The following algorithm is used in spelling checkersand correctors.
/// You are given two strings, X = $x_1x_2...x_m$ and Y = $y_1y_2...y_n$.
/// Define the edit distance between X and Y to be the minimum number of 
/// single character insertions, deletions, and replacements 
/// applied to X to make it equal to Y.
/// For example, if X = backache and Y = sackrace, then the edit distance is 3. 
/// The sequence of changes is :
/// •	Replace x_1 with  y_1('s')
/// •	Insert  y_5('r') after x_4
/// •	Delete x_7('h')
/// Give a dynamic programming algorithm that determines 
/// the minimum edit distance between X and Y.
///
int findMin(int x, int y, int z)
{
    if (x < y)
	{
        if (x < z)
            return x;
        else
            return z;
    }
    else 
	{
        if (y < z)
            return y;
        else
            return z;
    }
}
int EditDistance(string &X, string &Y) {
    int m = X.length();
    int n = Y.length();

    int** dp = new int* [m];
    for (int i = 0; i < m+1; ++i) //dinamik çok boyutlu array
        dp[i] = new int[n];

    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {

			if (i == 0)
			{
				dp[i][j] = j; // min operations = j 
			}
			else if (j == 0)
			{
				dp[i][j] = i;
			}
			else if (X[i - 1] == Y[j - 1]) 
			{
				dp[i][j] = dp[i - 1][j - 1];
			}
			else
			{
				dp[i][j] = 1 + findMin(dp[i][j - 1],dp[i - 1][j],dp[i - 1][j - 1]);
			}
        }
    }
    return dp[m][n];
} 
