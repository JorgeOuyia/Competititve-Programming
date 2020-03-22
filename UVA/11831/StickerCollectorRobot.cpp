#include <iostream>
#include <string>
#include <cstring>
#include <unordered_map>
#include <vector>

using namespace std;

int rows, columns, instructions, cont;
unordered_map<char, char> right90Degrees;
unordered_map<char, char> left90Degrees;
unordered_map<char, pair<int, int>> movement;
string line;
char dir;
char matrix[105][105];
pair<int, int> pos;

int main()
{
    right90Degrees['N'] = 'L';
    right90Degrees['L'] = 'S';
    right90Degrees['S'] = 'O';
    right90Degrees['O'] = 'N';
    left90Degrees['N'] = 'O';
    left90Degrees['O'] = 'S';
    left90Degrees['S'] = 'L';
    left90Degrees['L'] = 'N';
    movement['N'] = { -1, 0 };
    movement['L'] = { 0, 1 };
    movement['S'] = { 1, 0 };
    movement['O'] = { 0, -1 };
    while (cin >> rows >> columns >> instructions && (rows != 0 || columns != 0 || instructions != 0))
    {
        cont = 0;
        for (int i = 0; i < rows; i++)
        {
            cin >> line;
            for (int j = 0; j < columns; j++)
            {
                matrix[i][j] = line[j];
                if (matrix[i][j] != '*' && matrix[i][j] != '#' && matrix[i][j] != '.')
                    dir = matrix[i][j], pos = { i, j };
            }
        }
        cin >> line;
        for (int i = 0; i < line.length(); i++)
        {
            if (line[i] == 'D')
            {
                dir = right90Degrees[dir];
            }
            else if (line[i] == 'E')
            {
                dir = left90Degrees[dir];
            }
            else if (line[i] == 'F')
            {
                int row = pos.first;
                int column = pos.second;

                row += movement[dir].first;
                column += movement[dir].second;

                if (row >= 0 && column >= 0 && row < rows && column < columns && matrix[row][column] != '#')
                {
                    if (matrix[row][column] == '*')
                        matrix[row][column] = '.', cont++;
                    pos = { row, column };
                }
            }
        }
        cout << cont << endl;
    }
    return 0;
}