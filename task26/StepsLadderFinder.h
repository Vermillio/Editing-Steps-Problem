#pragma once
#include <vector>
#include <string>

using namespace std;

class StepsLadderFinder
{
	bool check(const string &s1, const string &s2);
	int findLongestStart(vector<vector<int>> &g, int start);
	void findLongestPath(vector<vector<int>> &g, vector<int> &ans);
	void bfs(vector<vector<int>> &g, int start, vector<bool> &used, vector<int> &ans);
public:
	void test();
	void run(vector<string> w, vector<string> &ans);
	StepsLadderFinder();
	~StepsLadderFinder();
};

bool operator< (const string &x, const string &y);

//void operator= (string x, const string &y);

