#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <fstream>

using namespace std;

string New_line = "-1";

void decode(string filename, unordered_map<string, char> &huff_table)
{
    ifstream encode_f(filename + "_encoded.bin");
    ofstream decode_f(filename+"_decoded.txt");

    string str;
    char bin = 0;
    string b = "";

    int count = 0;

    while (getline(encode_f, str))
    {
        for (char c : str)
        {
            for (int i = 0; i < 8; i++)
            {
                if (abs(c % 2) == 1)
                {
                    b =  b +"1";
                    c=c >> 1;
                }
                else
                {
                    b = b + "0";
                    c=c >> 1;
                }
                if(huff_table[b]!=(char)(0))
                {
                    decode_f<<huff_table[b];
                    b="";
                }
            }
        }
    }
    encode_f.close();
    decode_f.close();
}
int main()
{

    string filename = "abc";

    unordered_map<string, char> huff_table;

    ifstream huff_code_tab(filename + "_table_code.txt");

    string str;
    int str1;

    while (huff_code_tab >> str)
    {
        huff_code_tab >> str1;

        huff_table[str] = (char)str1;

        if (str1 == 0)
        {
            New_line = str1;
        }
    }

    decode(filename,huff_table);

    return 0;
}