//!!!!!!!!!! http://comproguide.blogspot.bg/search?q=linked+list+c%2B%2B RESHENI ZADACHI za linked list
#include <iostream>
#include <string.h>
#include <string>
#include <assert.h>
#include <map>


using namespace std;

bool func(int*a, int*b, int n1, int n2)
{
	map<int, bool> f;
	for (size_t i = 0; i < n1; i++)
	{
		f[a[i]] = true;
	}
	for (size_t i = 0; i < n2; i++)
	{
		if (f.find(b[i]) != f.end())
		{
			return false;
		}
		return true;
	}

}
int max(int a, int b)
{
	if (a > b) return a;
	else
		return b;
}
int maxDistance(int*arr, int n)
{
	map<int, int> mp;
	int max_dist = 0;
	for (int i = 0; i<n; i++)
	{
		// If this is first occurrence of element, insert its
		// index in map
		if (mp.find(arr[i]) == mp.end())
			mp[arr[i]] = i;

		// Else update max distance
		else
			max_dist = max(max_dist, i - mp[arr[i]]);
	}

	return max_dist;
}
// C++ program to check if a string can be converted to
// a string that has repeated substrings of length k.
#include<bits/stdc++.h>
using namespace std;

// Returns true if str can be coverted to a string
// with k repeated substrings after replacing k
// characters.
bool checkString(string str, long k)
{
	// Length of string must be a multiple of k
	int n = str.length();
	if (n%k != 0)
		return false;

	// Map to store strings of length k and their counts
	unordered_map<string, int> mp;
	for (int i = 0; i<n; i += k)
		mp[str.substr(i, k)]++;

	// If string is already a repition of k substrings,
	// return true.
	if (mp.size() == 1)
		return true;

	// If number of distinct substrings is not 2, then
	// not possible to replace a string.
	if (mp.size() != 2)
		return false;

	// One of the two distinct must appear exactly once.
	// Either the first entry appears once, or it appears
	// n/k-1 times to make other substring appear once.
	if ((mp.begin()->second == (n / k - 1)) ||
		mp.begin()->second == 1)
		return true;

	return false;
}

int main()
{
	int a[4] = { 1,2,5,7 };
	int b[5] = { 10,9,0,4,6 };
	cout << func(a, b, 4, 5) << endl;
	map<int, char> mapp;

	int arr[] = { 3, 2, 1, 2, 1, 4, 5, 8, 6, 7, 4, 2 };
	int n = 12;
	cout << maxDistance(arr, n) << endl;


	mapp[1] = 'a';
	mapp[2] = 'b';
	mapp[3] = 'c';
	cout << mapp[2] << endl;
	mapp.insert(pair<int, char>(4, 'd'));
	map<int, char>::iterator it;
	for (it = mapp.begin(); it != mapp.end(); ++it)
	{
		cout << it->first << " " << it->second << endl;
	}
	it = mapp.find(3);
	cout << "value found: " << it->second << endl;
	mapp.erase(it);
	for (it = mapp.begin(); it != mapp.end(); ++it)
	{
		cout << it->first << " " << it->second << endl;
	}

	return 0;
}
