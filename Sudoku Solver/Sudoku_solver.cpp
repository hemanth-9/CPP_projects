#include <iostream>
#include <vector>

using namespace std;

typedef vector<vector<pair<int, vector<int>>>> vvpvi;
typedef vector<pair<int, vector<int>>> vpvi;
typedef vector<int> vi;
typedef pair<int, vector<int>> pivi;

int count = 0;

vvpvi arr;
int size = 9;
vi predef = {1, 2, 3, 4, 5, 6, 7, 8, 9};

void creb(vvpvi &arr, int i, int j)
{
    pivi copy = arr[i][j];
    int box_i = i / 3 * 3, box_j = j / 3 * 3;

    for (int b_i = box_i; b_i < box_i + 3; b_i++)
    {
        for (int b_j = box_j; b_j < box_j + 3; b_j++)
        {

            if (arr[b_i][b_j].first != 0)
            {
                continue;
            }
            else if (b_i != i || b_j != j)
            {
                vi::iterator i1 = arr[b_i][b_j].second.begin(), i2 = arr[b_i][b_j].second.end();
                while (i1 != i2)
                {
                    vi::iterator it = copy.second.begin(), it2 = copy.second.end();
                    while (it != it2)
                    {
                        if (*i1 == *it)
                        {
                            vi::iterator it1 = it;

                            copy.second.erase(it1);
                            it2 = copy.second.end();
                        }
                        else
                        {
                            it++;
                        }
                    }
                    i1++;
                }
            }
        }
    }
    if (copy.second.size() == 1)
    {
        arr[i][j].first = copy.second[0];
        arr[i][j].second = copy.second;
        count--;
    }
}

void crex(vvpvi &arr, int i, int j)
{
    pivi copy = arr[i][j];
    for (int l = 0; l < size; l++)
    {
        vi::iterator it = arr[i][j].second.begin(), it2 = arr[i][j].second.end();
        if (l == i)
        {
            int id = 0;
            for (pivi temp : arr[i])
            {
                if (temp.first != 0)
                {
                    continue;
                }
                else if (id != j)
                {

                    vi::iterator i1 = temp.second.begin(), i2 = temp.second.end();
                    while (i1 != i2)
                    {
                        vi::iterator it = copy.second.begin(), it2 = copy.second.end();
                        while (it != it2)
                        {
                            if (*i1 == *it)
                            {
                                vi::iterator it1 = it;
                                copy.second.erase(it);

                                it2 = copy.second.end();
                            }
                            else
                            {
                                it++;
                            }
                        }
                        i1++;
                    }
                }
                id++;
            }
        }
    }
    if (copy.second.size() == 1)
    {
        arr[i][j].first = copy.second[0];
        arr[i][j].second = copy.second;
        count--;
    }
}

void crey(vvpvi &arr, int i, int j)
{
    pivi copy = arr[i][j];
    for (int l = 0; l < size; l++)
    {
        vi::iterator it = arr[i][j].second.begin(), it2 = arr[i][j].second.end();
        if (l == i)
        {
            continue;
        }
        else
        {
            if (arr[l][j].first == 0)
            {

                vi::iterator i1 = arr[l][j].second.begin(), i2 = arr[l][j].second.end();
                while (i1 != i2)
                {
                    vi::iterator it = copy.second.begin(), it2 = copy.second.end();
                    while (it != it2)
                    {
                        if (*i1 == *it)
                        {
                            vi::iterator it1 = it;

                            copy.second.erase(it);
                            it2 = copy.second.end();
                        }
                        else
                        {
                            it++;
                        }
                    }
                    i1++;
                }
            }
        }
    }
    if (copy.second.size() == 1)
    {
        arr[i][j].first = copy.second[0];
        arr[i][j].second = copy.second;
        count--;
    }
}

void create(vvpvi &arr, int i, int j)
{

    for (int l = 0; l < size; l++)
    {
        vi::iterator it = arr[i][j].second.begin(), it2 = arr[i][j].second.end();
        if (l == i)
        {

            for (pivi temp : arr[i])
            {
                if (temp.first != 0)
                {
                    vi::iterator it = arr[i][j].second.begin(), it2 = arr[i][j].second.end();
                    while (it != it2)
                    {
                        if (temp.first == *it)
                        {
                            vi::iterator it1 = it;

                            arr[i][j].second.erase(it);
                            it2--;
                        }
                        else
                        {
                            it++;
                        }
                    }
                }
            }
        }
        else
        {
            if (arr[l][j].first != 0)
            {
                while (it != it2)
                {
                    if (arr[l][j].first == *it)
                    {
                        vi::iterator it1 = it;

                        arr[i][j].second.erase(it1);
                        it2--;
                    }
                    else
                    {
                        it++;
                    }
                }
            }
        }
    }
    int box_i = i / 3 * 3, box_j = j / 3 * 3;
    vi::iterator it = arr[i][j].second.begin(), it2 = arr[i][j].second.end();

    for (int b_i = box_i; b_i < box_i + 3; b_i++)
    {
        for (int b_j = box_j; b_j < box_j + 3; b_j++)
        {
            if (arr[b_i][b_j].first != 0)
            {
                vi::iterator it = arr[i][j].second.begin(), it2 = arr[i][j].second.end();
                while (it != it2)
                {
                    if (arr[b_i][b_j].first == *it)
                    {
                        vi::iterator it1 = it;

                        arr[i][j].second.erase(it);
                        it2--;
                    }
                    else
                    {
                        it++;
                    }
                }
            }
        }
    }
}
void intialize(vvpvi &arr)
{
    // vi temp;

    for (int i = 0; i < size; i++)
    {
        vpvi temp;
        for (int j = 0; j < size; j++)
        {
            pivi temp1;
            int a;
            cin >> a;
            temp1.first = a;
            if (a == 0)
            {
                temp1.second = predef;
                count++;
            }
            temp.push_back(temp1);
        }
        arr.push_back(temp);
    }
}
void print_all(vvpvi &arr)
{
    for (vpvi a : arr)
    {
        for (pivi b : a)
        {
            cout << b.first << " ";
        }
        cout << endl;
    }
}
void print_s(vvpvi &arr)
{
    for (vpvi a : arr)
    {
        for (pivi b : a)
        {
            cout << b.second.size() << " ";
        }
        cout << endl;
    }
}

void solve(vvpvi &arr)
{
    int i = 9, l = 81;
    int m = 3;
    while (i--)
    {
        if (count == 0)
        {
            return;
        }
        int l = 81;
        while (l--)
        {
            for (int j = 0; j < 9; j++)
            {

                for (int k = 0; k < 9; k++)
                {
                    if (count == 0)
                    {
                        return;
                    }
                    if (arr[j][k].first == 0)
                    {
                        create(arr, j, k);

                        if (arr[j][k].second.size() == 1)
                        {
                            arr[j][k].first = arr[j][k].second[0];
                            count--;
                        }
                    }
                }
            }
        }
        if (m % 3 == 0)
        {
            for (int j = 0; j < 9; j++)
            {
                for (int k = 0; k < 9; k++)
                {

                    if (arr[j][k].first == 0)
                    {
                        creb(arr, j, k);
                    }
                }
            }
        }
        else if (m % 3 == 1)
        {
            for (int j = 0; j < 9; j++)
            {
                for (int k = 0; k < 9; k++)
                {

                    if (arr[j][k].first == 0)
                    {
                        crex(arr, j, k);
                    }
                }
            }
        }
        else
        {
            for (int j = 0; j < 9; j++)
            {
                for (int k = 0; k < 9; k++)
                {

                    if (arr[j][k].first == 0)
                    {
                        crey(arr, j, k);
                    }
                }
            }
        }
        m++;
    }
}
int main()
{
    intialize(arr);
    solve(arr);
    if (count == 0)
    {
        cout<<"SOLVED!"<<endl;
        print_all(arr);
        
        
        cout << endl;
        // print_s(arr);
    }
    else
    {
        cout<<"NOT SOLVED"<<endl;
        // print_s(arr);
        
        cout << endl;
        // print_all(arr);
        // cout << endl;
        
    }

    

    return 0;
}