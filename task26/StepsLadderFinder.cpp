//We call the editing step a transformation of the word x into the word y, that the words x and y belong to the dictionary 
//and the word x can be transformed into the word y by adding, deleting or changing one letter. 
//Conversions "dig" to "dog" and "dog" to "do" are editing steps. 
//A ladder of editing steps is a sequence of words w1, w2, ..., wn sorted in the lexicographic order 
//such that the transformation wi into wi + 1 is the step of the transformation for any i from 1 to n - 1. 
//
//For a given dictionary find the largest ladder of editing steps.
//
//Input consists of a dictionary : a set of words in the lower register in lexicographical order one word per line.
//Each word does not exceed 16 letters, and in the dictionary no more than 25 000 words.

#include "StepsLadderFinder.h"
#include <algorithm>
#include <iostream>
#include <queue>
using namespace std;

void StepsLadderFinder::test()
{
	int sz = 6;
	vector<vector<string>> TEST = {
		{"MM", "M", "Ma", "Mr", "aa", "a", "ab", "aab", "aaba", "baaba", "baab", "cccccccccccc"},
		{"U", "nnnnnnnn", "nnnnvnnn", "nnnnvvnn", "nnnvvvnn", "nnvvvvnn", "nvvvvvnn", "vvvvvvnn", "vvvvvvvn", "vvvvvvvv", "", "a", "", "b", "B", "c", "", "d" },
		{"", "a", "", "b", "B", "c", "", "d"},
		{"dag" "deg", "dig", "dog", "dug", "duc", "duck", "luck", "lock", "clock"},
		{"L", "ana", "anan", "anana", "banana", "L", "ana", "an", "un", "unn", "unnn"},
		{"q", "w", "e", "r", "t", "", "y", "yy", "yyy", "yxy", "yxyx", "yxyxy", "xyxyxy", "red"}

	};

	vector<int> ANS = {
		6, 9, 2, 3, 5, 4 };

	int count = 0;
	vector<string> CUR;
	for (int i = 0; i < sz; ++i)
	{
		run(TEST[i], CUR);
		bool valid = true;
		if (ANS[i] == CUR.size())
		{
			for (int j = 0; j < CUR.size() - 1; ++j)
				if (!check(CUR[j], CUR[j + 1]))
				{
					valid = false;
					break;
				}
		}
		else
			valid = false;
		if (!valid)
		{
			if (count == 0)
				cout << "Tests crashed : ";
			cout << i+1 << " ";
			++count;
		}
	}
	if (count == 0)
		cout << "All tests passed.";
}

void StepsLadderFinder::run(vector<string> w, vector<string> &ans)
{
	sort(w.begin(), w.end());
	vector<vector<int>> g;
	g.resize(w.size());
	for (int i = 0; i < w.size() - 1; ++i)
		for (int j = i+1; j < w.size(); ++j) {
			if (check(w[i], w[j]))
				g[i].push_back(j);
		}
	vector<int> ladder;
	findLongestPath(g, ladder);
	ans.resize(ladder.size());
	for (int i = 0; i < ladder.size(); ++i)
		ans[i] = w[ladder[i]];
}

StepsLadderFinder::StepsLadderFinder()
{
}


StepsLadderFinder::~StepsLadderFinder()
{
}

int StepsLadderFinder::findLongestStart(vector<vector<int>>&g, int start)
{
	queue<int> q;
	q.push(start);
	vector<bool> used(g.size());
	vector<int> d(g.size());
	used[start] = true;
	d[start] = 0;
	q.push(start);
	int v;
	while (!q.empty()) {
		v = q.front();
		for (size_t i = 0; i < g[v].size(); ++i) 
		{
			int to = g[v][i];
			if (!used[to]) 
			{
				used[to] = true;
				q.push(to);
				d[to] = d[v] + 1;
			}
		}
		q.pop();
	}
	return d[v];
}

void StepsLadderFinder::findLongestPath(vector<vector<int>>& g, vector<int>& ans)
{
	int l = findLongestStart(g, 0);
	ans.clear();
	vector<bool> used(g.size());
	for (int i = 0; i < used.size(); ++i)
		if (!used[i])
		{
			vector<int> cur;
			bfs(g, i, used, cur);
			if (cur.size() > ans.size())
				ans = cur;
		}
}

void StepsLadderFinder::bfs(vector<vector<int>>& g, int start, vector<bool>& used, vector<int>& ans)
{
	queue<int> q;
	q.push(start);
	vector<int> d(g.size());
	used[start] = true;
	int v;
	while (!q.empty()) {
		v = q.front();
		for (size_t i = 0; i < g[v].size(); ++i)
		{
			int to = g[v][i];
			if (!used[to])
			{
				used[to] = true;
				q.push(to);
				d[to] = v;
			}
		}
		q.pop();
	}
	ans.push_back(v);
	while (v != start)
	{
		v = d[v];
		ans.push_back(v);
	}
}

bool StepsLadderFinder::check(const string &s1, const string &s2)
{
	string s3;
	if (s1.length() > s2.length() + 1) return false;
	if (s2.length() > s1.length() + 1) return false;
	if (s1.length() == s2.length())
	{
		for (size_t i = 0; i < s1.length(); i++)
		{
			s3 = s1;
			s3[i] = s2[i];
			if (s2 == s3) return true;
		}
		return false;
	}
	if (s1.length() > s2.length())
	{

		for (size_t i = 0; i < s1.length(); ++i)
		{
			s3 = s1;
			s3.erase(s3.begin() + i, s3.begin() + i + 1);
			if (s2 == s3) return true;
		}
		return false;
	}
	if (s1.length() < s2.length())
	{

		for (size_t i = 0; i < s2.length(); i++)
		{
			s3 = s2;
			s3.erase(s3.begin() + i, s3.begin() + i + 1);
			if (s1 == s3) return true;
		}
		return false;
	}

}

bool operator<(const string & x, const string & y)
{
	int i = 0;
	while (x[i] == y[i])
		++i;
	return x[i] < y[i];
}
