#include <iostream>
#include <vector>
#include <string>
using namespace std;

// diag1 [ 0 1 2 3 ]
//       [ 1 2 3 4 ]
//       [ 2 3 4 5 ]
//       [ 3 4 5 6 ]
//  x+1,y-1  and x-1, y+1 (for 2,2 x=2,y=2  => 3,1 1,3)

// diag2 [ 3 4 5 6 ]
//       [ 2 3 4 5 ]
//       [ 1 2 3 4 ]
//       [ 0 1 2 3 ]
//  x+1,y+1 or x-1, y-1    (2,2 => 3,3 1,1 0,0)

bool diag2(vector<vector<int>> vec, int i, int j, int n)
{
    int x = i, y = j;
    while (i <= n - 1 && j <= n - 1)
    {
        if (vec[i][j] == 1)
        {
            return true;
        }
        i++;
        j++;
    }
    while (x >= 0 && y >= 0)
    {
        if (vec[x][y] == 1)
        {
            return true;
        }
        x--;
        y--;
    }
    return false;
}

bool diag1(vector<vector<int>> vec, int i, int j, int n)
{
    int x = i, y = j;
    while (i <= n - 1 && j >= 0)
    {
        if (vec[i][j] == 1)
        {
            return true;
        }
        i++;
        j--;
    }
    while (x >= 0 && y <= n - 1)
    {
        if (vec[x][y] == 1)
        {
            return true;
        }
        x--;
        y++;
    }
    return false;
}

bool col(vector<vector<int>> vec, int i, int j, int n)
{
    int x = i, y = j;
    while (i <= n - 1)
    {
        if (vec[i][j] == 1)
        {
            return true;
        }
        i++;
    }
    while (x >= 0)
    {
        if (vec[x][y] == 1)
        {
            return true;
        }
        x--;
    }
    return false;
}

void print_mat(vector<vector<int>> vec)
{
    for (int i = 0; i < vec.size(); i++)
    {
        for (int j = 0; j < vec.size(); j++)
        {
            // here loop
            cout << vec[i][j] << " ";
        }
        cout << endl;
    }
}

void search(int y, int n, int &count, vector<vector<int>> &vec)
{
    int x = 0;
    if (y == n) // y is row, x is col
    {
        count++;
        cout << "print matirx at " << y << x << endl;
        print_mat(vec);
        cout << "\n\n";
        return;
    }
    for (x = 0; x < n; x++)
    {
        if (col(vec, y, x, n) || diag1(vec, y, x, n) || diag2(vec, y, x, n))
        {
            continue;
            // cout << "Presnet" << x << endl;
        }
        vec[y][x] = 1;

        // cout << "print matirx at " << y << x << endl;
        // print_mat(vec);
        // cout << "\n\n";
        search(y + 1, n, count, vec);

        vec[y][x] = 0;
    }
}

int main()
{
    // your code begins here
    vector<vector<int>> vec(5, vector<int>(5, 0)); // 8X8 matrices with 0 value
    int count = 0;
    int y = 0;
    search(y, vec.size(), count, vec);
    cout << count;

    return 0;
}