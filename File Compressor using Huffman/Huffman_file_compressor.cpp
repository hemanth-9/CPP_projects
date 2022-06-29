#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
#include <limits.h>
#include <list>
#include <ctype.h>
#include <cmath>
#include <math.h>
#include <fstream>
#include <unordered_map>

using namespace std;


bool com2(pair<char, int> &a, pair<char, int> &b)
{
    return a.second < b.second;
}

class Node
{
public:
    char ch;
    int fr;
    Node *left;
    Node *right;

    Node(char c, int freq)
    {
        ch = c;
        fr = freq;
        left = NULL;
        right = NULL;
    }
    Node(int freq, Node *l, Node *r)
    {
        fr = freq;
        left = l;
        right = r;
    }
};

Node *huffmantree2(vector<Node *> &arr, int top_pre_index)
{
    vector<Node *>::iterator itr, it;
    itr = arr.begin() + top_pre_index;
    Node *h = new Node(((*itr)->fr + (*(itr + 1))->fr), *(itr), *(itr + 1));

    itr += 2;

    vector<Node *> top;
    top.push_back(h);

    int top_index = 0;
    int top_tot = 1;

    while (itr != arr.end())
    {
        if (top_index != top_tot && (*itr)->fr < top[top_index]->fr)
        {
            Node *lef = (*itr);
            if (top_index != top_tot && (itr + 1) != arr.end() && (*(itr + 1))->fr < top[top_index]->fr)
            {
                Node *righ = *(itr + 1);
                top.push_back(new Node(lef->fr + righ->fr, lef, righ));
                top_tot++;
                itr += 2;
            }
            else if (top_index != top_tot)
            {
                top.push_back(new Node(lef->fr + top[top_index]->fr, lef, top[top_index]));
                top_tot++;
                top_index++;
                itr++;
            }
        }
        else if (top_index != top_tot)
        {
            if ((top_index + 1) != top_tot && (*itr)->fr >= top[top_index + 1]->fr)
            {
                top.push_back(new Node(top[top_index + 1]->fr + top[top_index]->fr, top[top_index], top[top_index + 1]));
                top_tot += 2;
                top_index += 2;
            }
            else
            {
                Node *righ = (*itr);
                top.push_back(new Node(righ->fr + top[top_index]->fr, top[top_index], righ));
                top_tot++;
                top_index++;
                itr++;
            }
        }
    }

    if (itr == arr.end() && top_index != (top_tot - 1))
    {
        return huffmantree2(top, top_index);
    }
    else
    {
        return top[top_index];
    }
}

Node *huffmantree(vector<pair<char, int>> &arr)
{
    vector<pair<char, int>>::iterator itr, it;
    itr = arr.begin();
    Node *h = new Node((itr->second + (itr + 1)->second), new Node(itr->first, itr->second), new Node((itr + 1)->first, (itr + 1)->second));

    itr += 2;

    vector<Node *> top;
    top.push_back(h);

    int top_index = 0;
    int top_tot = 1;

    while (itr != arr.end())
    {
        if (top_index != top_tot && itr->second < top[top_index]->fr)
        {
            Node *lef = new Node(itr->first, itr->second);
            if (top_index != top_tot && (itr + 1) != arr.end() && (itr + 1)->second < top[top_index]->fr)
            {
                Node *righ = new Node((itr + 1)->first, (itr + 1)->second);
                top.push_back(new Node(lef->fr + righ->fr, lef, righ));

                top_tot++;
                itr += 2;
            }
            else if (top_index != top_tot)
            {
                top.push_back(new Node(lef->fr + top[top_index]->fr, lef, top[top_index]));
                top_tot++;
                top_index++;
                itr++;
            }
        }
        else if (top_index != top_tot)
        {
            if ((top_index + 1) != top_tot && itr->second >= top[top_index + 1]->fr)
            {
                top.push_back(new Node(top[top_index + 1]->fr + top[top_index]->fr, top[top_index], top[top_index + 1]));
                top_tot += 2;
                top_index += 2;
            }
            else
            {
                Node *righ = new Node(itr->first, itr->second);
                top.push_back(new Node(righ->fr + top[top_index]->fr, top[top_index], righ));
                top_tot++;
                top_index++;
                itr++;
            }
        }
    }

    if (itr == arr.end() && top_index != (top_tot - 1))
    {
        return huffmantree2(top, top_index);
    }
    else
    {
        return top[top_index];
    }
}

void cre_huffcode_table(Node *head, string str, unordered_map<char, string> &huffcode_tab)
{
    if (head->left == NULL && head->right == NULL)
    {
        huffcode_tab[head->ch] = str;
    }
    else
    {
        cre_huffcode_table(head->right, str + "1", huffcode_tab);
        cre_huffcode_table(head->left, str + "0", huffcode_tab);
    }
}

void print_fre(vector<pair<char, int>> &freq2)
{
    for (pair<char, int> a : freq2)
    {
        if (a.first == ' ')
        {
            cout << "Space"
                 << " " << a.second << endl;
        }
        else if (a.first == '\n')
        {
            cout << "Newline"
                 << " " << a.second << endl;
        }
        else
            cout << a.first << " " << a.second << endl;
    }
}

void print_huffcode_table(unordered_map<char, string> &huffcode_tab)
{
    for (pair<char, string> a : huffcode_tab)
    {
        if (a.first == ' ')
        {
            cout << "Space"
                 << " " << a.second << endl;
        }
        else if (a.first == '\n')
        {
            cout << "Newline"
                 << " " << a.second << endl;
        }
        else
            cout << a.first << " " << a.second << endl;
    }
}

void cre_file_huffcode(unordered_map<char, string> huff, string filename)
{
    ofstream huffcode_file;
    huffcode_file.open(filename + "_table_code.txt");

    for (pair<char, string> a : huff)
    {
        huffcode_file << a.second << " " << (int)a.first << endl;
    }
    huffcode_file.close();
}

void encoding_file(unordered_map<char, string> huff, string filename)
{
    ofstream huffcode_file;
    ifstream input_file;
    input_file.open(filename + ".txt");
    huffcode_file.open(filename + "_encoded.bin", ios::binary);
    string str, s = "";
    char bin = 0, bin_rev = 0;
    int count = 0;
    int flag=0;

    while (getline(input_file, str))
    {
        if(flag==1)
        {
            for (char x : huff['\n'])
            {
                if (x == '1')
                {
                    bin = (bin << 1);
                    bin += 1;
                    count++;
                }
                else
                {
                    bin = (bin << 1);
                    count++;
                }
                if (count == 8)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        bin_rev = bin_rev << 1;
                        bin_rev += abs(bin % 2);
                        bin = bin >> 1;
                    }
                    huffcode_file << ((char)bin_rev);
                    bin_rev = 0;
                    bin = 0;
                    count = 0;
                }
            }
        }
        flag=1;
        for (char a : str)
        {
            for (char x : huff[a])
            {
                if (x == '1')
                {
                    bin = (bin << 1);
                    bin += 1;
                    count++;
                }
                else
                {
                    bin = (bin << 1);
                    count++;
                }
                if (count == 8)
                {
                    for (int i = 0; i < 8; i++)
                    {
                        bin_rev = bin_rev << 1;
                        bin_rev += abs(bin % 2);
                        bin = bin >> 1;
                    }
                    huffcode_file << ((char)bin_rev);
                    bin_rev = 0;
                    bin = 0;
                    count = 0;
                }
            }
        }

        
    }
    if (count != 0)
    {
        for (int i = 0; i < count; i++)
        {
            bin_rev = bin_rev << 1;
            bin_rev += abs(bin % 2);
            bin = bin >> 1;
        }
        huffcode_file << ((char)bin_rev);

        bin_rev = 0;
        bin = 1;
    }
    input_file.close();
    huffcode_file.close();
}

int main()
{

    ifstream myfile;
    string filename = "abc";
    myfile.open(filename + ".txt");

    string str;

    unordered_map<char, int> freq;

    int flag=0;

    while (getline(myfile, str))
    {
        if(flag==1) freq['\n']++;
        flag=1;
        for (char a : str)
        {
            freq[a]++;
        }
    }
    myfile.close();
    vector<pair<char, int>> freq2;
    for (pair<char, int> a : freq)
    {
        freq2.push_back(a);
    }
    sort(freq2.begin(), freq2.end(), com2);

    // print_fre(freq2);

    Node *head = huffmantree(freq2);

    unordered_map<char, string> huffcode_table;

    cre_huffcode_table(head, "", huffcode_table);

    // print_huffcode_table(huffcode_table);

    cre_file_huffcode(huffcode_table, filename);

    encoding_file(huffcode_table, filename);

    return 0;
}