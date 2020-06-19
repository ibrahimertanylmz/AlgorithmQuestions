#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

enum DIR { DOWN = 1, RIGHT = 2 };
struct Index { int i, j; Index(int _i, int _j) { i = _i; j = _j; } };

///------------------------------------------------------
/// You are given a NxN matrix with each slot containing a number 
/// indicating the cost of going through that slot
/// Initially you are at(0, 0)
/// You are only allowed to go Down or Right
/// You want to go to(N - 1, N - 1)
/// Find the path that has the minimum total cost
///
int MinimumCostPath(vector<vector<int>>& M, vector<Index>& Path) {

	vector<vector<int>> solution;
	vector<vector<DIR>> direction;

	int N = M.size();

	for (size_t i = 0; i < N; i++) {
		direction.push_back(vector<DIR>());
		direction[i].resize(N);

		solution.push_back(vector<int>());
		for (size_t j = 0; j < N; j++)
		{
			solution[i].push_back(-1);
		}
	}

	for (int i = N - 1; i >= 0; i--) {
		for (int j = N - 1; j >= 0; j--) {
			if (i == N - 1 && j == N - 1) {
				solution[i][j] = 0;
				continue;
			}

			int downCost = INT_MAX;
			if (i + 1 < N) downCost = solution[i + 1][j];

			int rightCost = INT_MAX;
			if (j + 1 < N) rightCost = solution[i][j + 1];

			int minCost = downCost;
			direction[i][j] = DOWN;
			if (rightCost < downCost)
			{
				minCost = rightCost;
				direction[i][j] = RIGHT;
			}

			solution[i][j] = M[i][j] + minCost;
		}
	}

	int cost = solution[0][0];

	int i = 0, j = 0;
	while (!(i == N - 1 && j == N - 1)) 
	{
		Path.push_back(Index(i, j));

		if (direction[i][j] == DOWN) i++; // aþaðý
		else j++; // saða
	}

	Path.push_back(Index(N - 1, N - 1));

	return cost;
} //end-MinimumCostPath