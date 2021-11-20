#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define OPERATORS_N 9

extern char operators[];
using namespace std;

bool lexical_analyzer(ifstream& read_file, vector<vector<string>> tokens)
{
    while(!read_file.eof())
    {
        string input_line;
        size_t rp_begin = 0;
        vector<string> token_line;

        getline(read_file, input_line);

        for(size_t i = 0; i < input_line.size(); i++)
        {
            if(input_line[i] == ' ')
            {
                if(i - rp_begin == 0)
                {
                    rp_begin++;
                    continue;
                }
                string t = input_line.substr(rp_begin, i - rp_begin);
                rp_begin = i+1;
                token_line.push_back(t);
                continue;
            }

            for(size_t j = 0; j < OPERATORS_N; j++)
            {
                if( input_line[i] == operators[j] )
                {
                    string t = input_line.substr(rp_begin, i - rp_begin + 1);
                    rp_begin = i+1;
                    token_line.push_back(t);
                    continue;
                }
            }
        }

        tokens.push_back(token_line);
    }
    return true;
}
