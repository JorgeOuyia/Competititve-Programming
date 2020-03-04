#include <iostream>

using namespace std;

int people[10003];
int money[10003];

int t, friends, relations, a, b;

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
        money[x] += money[y];
        money[y] = 0;
        people[y] = x;
    }
}

int main() 
{
    
    cin >> t;
    while (t--) {
        cin >> friends >> relations;
        for (int i = 0; i < friends; i++) 
        {
            people[i] = i;
            cin >> money[i];
        }
        for (int i = 0; i < relations; i++)
        {
            cin >> a >> b;
            connect(a, b);
        }
        int k;
        for (k = 0; k < friends; k++) 
        {
            if (money[k] != 0) 
            {
                cout << "IMPOSSIBLE" << endl;
                break;
            }
        }
        if (k >= friends) 
        {
            cout << "POSSIBLE" << endl;
        }
    }
    return 0;
}