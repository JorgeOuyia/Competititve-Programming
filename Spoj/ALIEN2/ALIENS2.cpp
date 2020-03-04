#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <queue>
#include <stack>
 
using namespace std;
 
int stations, maxPeople, aux, flag, resPeople, resStations;
 
int a[10002];
int b[10002];
 
int main()
{
	while (cin >> stations >> maxPeople)
	{
		flag = 1;
		resStations = stations;
		for (int i = 0; i < stations; i++)
			cin >> a[i];
		for (int i = 0; i < stations; i++)
			cin >> b[i];
		for (int i = 0; i < stations; i++)
		{
			aux = a[i];
			// Vemos si sale mejor quedarnos en el tren A o irnos al B
			a[i] = min(a[i - 1] + a[i], b[i - 1] + b[i] + a[i]);
			b[i] = min(b[i - 1] + b[i], a[i - 1] + aux + b[i]);
			
			if (min(a[i], b[i]) > maxPeople)
			{
				resStations = i;
				flag = 0; 
				break;
			}
		}
		if (!flag)
		{
			resPeople = min(a[resStations - 1], b[resStations - 1]);
		}
		else
		{
			resPeople = min(a[stations - 1], b[stations - 1]);
		}
		cout << resStations << " " << resPeople << endl;
	}
	return 0;
} 