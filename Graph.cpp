//#ifndef __GRAPH__
#define __GRAPH__
#include <iostream>
#include <list>
#include <map>
#include <algorithm>
#include <ostream>
#include <assert.h>
#include <cassert>
#include <set>
#include <string>
#include <queue>

using namespace std;

template <class VT, class LT>
class Graph
{
private:
	map<VT, list<pair<VT, LT>>> edges;//VT e key, list<pair<VT,LT>> e value. Vseki vuzel poluchava spisuk ot dvoiki
public:
	void toDotty(ostream&) const;
	void addVertex(const VT& newVertex)
	{
		edges[newVertex];
	}
	void addEdge(const VT &outV, const VT &inV, const LT &lbl)//izhodqsht i vhodqst vruh
	{
		addVertex(outV);
		addVertex(inV);

		edges[outV].push_back(pair<VT, LT>(inV, lbl));//edges[outV] vrushta list-a suotvetstvasht na vurha outV
		//i nai-otzad mu dobavq tazi dvoika
	}
	list<pair<VT, LT>> edgesFrom(const VT& out) const
	{
		return edges.at(out);//shte vurne value-to koeto otgovarq na vuzela out. Tpva value e spisuk ot dvoika ot susedite mu
		//i labelite 
	}

	LT getLabel(const VT&out, const VT&in)const
	{
		assert(edges.count(out) != 0);
		assert(edges.count(in) != 0);

		for (const pair<int, char>& edge : edgesFrom(out))//minava po rebrata izlizshti ot vuzela out, a tova predstavlqva spisuk
			//ot dvoiki ot susedite mu i labelite 
		{
			if (in == edge.first)
			{
				return edge.second;
			}
		}

		assert(false);

		//LT dummy;
		//return dummy;
	}

};

template <class VT, class LT>
void Graph<VT, LT>::toDotty(ostream &out) const
{
	
	out << "digraph G\n{\n";

	for (const pair<VT, list<pair<VT, LT>>>& mapEl : edges)
	{
		out << "\t" << mapEl.first << ";\n";

		for (const pair<VT, LT> &edge : mapEl.second)
		{
			out << "\t"
				<< mapEl.first
				<< " -> "
				<< edge.first
				<< "[label=\""
				<< edge.second
				<< "\"];\n";
		}
	}

	out << "}\n";
}

string stringOfLabels(int start, int end, const Graph<int, char>& g, set<int>& visited)
{
	if (start == end)
		return "";
	visited.insert(start);
	for (const pair<int, char>& edge : g.edgesFrom(start))
	{
		if (visited.count(edge.first) == 0)// count Counts elements with a specific value 
		{
			string nextString = stringOfLabels(edge.first, end, g, visited);
			if (!nextString.empty())
			{
				return edge.second + nextString;
			}
			if (edge.first == end)
			{
				string result;
				result += edge.second;
				return result;
			}
		}
	}
}
string stringOfLabelsPub(int start, int end, const Graph<int, char> g)
{
	set<int> visited;
	return stringOfLabels(start, end, g, visited);
}
bool hasPath(int start, const char *str, const Graph<int, char> g)
{
	if (*str == 0)
		return true;
	for (const pair<int, char>& edge : g.edgesFrom(start))
	{
		if (edge.second == *str && hasPath(edge.first, str + 1, g))//ili edge.second == str[0]
		{
			return true;
		}
	}
	return false;
}
bool hasPathBFS(int start, int end, const Graph<int, char> g)
{

	set<int> visited;
	queue<int> q;

	q.push(start);
	visited.insert(start);


	while (!q.empty() && q.front() != end)
	{
		int v = q.front();
		q.pop();

		for (const pair<int, char>& edge : g.edgesFrom(v))
		{
			const int &neigh = edge.first;

			if (visited.count(neigh) == 0)
			{
				q.push(neigh);
				visited.insert(neigh);
			}

		}

	}

	return !q.empty();
}

void testGraph()
{
	Graph<int, char> g;
	g.addEdge(0, 1, 'a');
	g.addEdge(2, 0, 'c');

	g.addEdge(1, 4, 'b');
	g.addEdge(1, 2, 'b');
	g.addEdge(1, 3, 'b');
	g.addEdge(4, 3, 'x');
	g.addEdge(3, 4, 'z');

	assert(g.getLabel(0, 1) == 'a');
	assert(g.getLabel(3, 4) == 'z');
	assert(g.getLabel(4, 3) == 'x');
	assert(g.getLabel(1, 3) == 'b');

	g.toDotty(cout);
	cout << endl;
	string res = stringOfLabelsPub(2, 3, g);
	cerr << "str = " << res << endl;
	string res1 = stringOfLabelsPub(2, 4, g);
	cerr << "str = " << res1 << endl;

	assert(hasPath(0, "abc", g));
	assert(!hasPath(1, "abc", g));
	assert(hasPath(1, "bca", g));
	assert(hasPath(0, "abcabcabcabc", g));

	assert(hasPathBFS(2, 4, g));
	assert(!hasPathBFS(3, 1, g));
	assert(hasPathBFS(1, 1, g));
	assert(!hasPathBFS(4, 2, g));

}

int main()
{
	testGraph();

	return 0;
}
