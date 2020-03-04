#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
#include <set>

using namespace std;

int t, friendships, cont;
string f1, f2;
map<string, int> traducciones;
map<int, string> reverseTraducciones;
set<string> personas;
int people[200005];
int sz[200005];

int find(int x)
{
	if (people[x] == x)
		return x;
	return people[x] = find(people[x]);
}

void connect(int x, int y)
{
	x = find(x);
	y = find(y);
	if (x != y)
	{
		if (sz[x] > sz[y])
		{
			sz[x] += sz[y];
			people[y] = x;
			cout << sz[x] << endl;
			return;
		}
		else
		{
			sz[y] += sz[x];
			people[x] = y;
			cout << sz[y] << endl;
			return;
		}
	}
	cout << sz[x] << endl;
}

int main()
{
	cin >> t;
	while (t--)
	{
		cont = 1;
		traducciones.clear();
		reverseTraducciones.clear();
		personas.clear();
		cin >> friendships;
		for (int i = 1; i <= friendships * 2; i++)
			people[i] = i, sz[i] = 1;
		while (friendships--)
		{
			cin >> f1 >> f2;
			if (traducciones[f1] == 0)
			{
				traducciones[f1] = cont;
				reverseTraducciones[cont] = f1;
				cont++;
			}
			if (traducciones[f2] == 0)
			{
				traducciones[f2] = cont;
				reverseTraducciones[cont] = f2;
				cont++;
			}
			connect(traducciones[f1], traducciones[f2]);
		}
	}
	return 0;
}