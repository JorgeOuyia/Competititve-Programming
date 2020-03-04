#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <vector>
 
#define INF 0x3F3F3F3F
 
using namespace std;
 
int f, c, tamUnos, dist, minDist;
string line;
 
int tablero[184][184];
pair<int, int> unos[184 * 184];
 
int main()
{
	int t;
	cin >> t;
	while (t--)
	{
		cin >> f >> c;
		tamUnos = 0;
		for (int i = 0; i < f; i++)
		{
			cin >> line;
			for (int j = 0; j < c; j++)
			{
				tablero[i][j] = line[j] - '0';
				if (tablero[i][j] == 1)
					unos[tamUnos] = { i, j }, tamUnos++;
			}
		}
		for (int i = 0; i < f; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (tablero[i][j] == 0)
				{
					minDist = INF;
					for (int k = 0; k < tamUnos; k++)
					{
						minDist = min(minDist, abs(i - unos[k].first) + abs(j - unos[k].second));
					}
					tablero[i][j] = minDist;
				}
				else
				{
					tablero[i][j] = 0;
				}
			}
		}
		for (int i = 0; i < f; i++)
		{
			for (int j = 0; j < c; j++)
			{
				if (j == 0)
					cout << tablero[i][j];
				else
					cout << " " << tablero[i][j];
			}
			cout << endl;
		}
	}
	return 0;
}