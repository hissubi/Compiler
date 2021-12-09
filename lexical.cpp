#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"
#include "extern.h"

#define OPERATORS_N 9

using namespace std;

bool lexical_analyzer(ifstream& read_file, vector<vector<string>>& tokens)
{
    while(1)
    {
        string input_line;
        size_t rp_begin = 0;
        vector<string> token_line;

        getline(read_file, input_line);
        if(read_file.eof()) break;
        
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
                    if(i != rp_begin){
                        string t1 = input_line.substr(rp_begin, i - rp_begin);
                        token_line.push_back(t1);
                    }

                    string t2 = input_line.substr(i, 1);
                    token_line.push_back(t2);
                    
                    rp_begin = i+1;
                    continue;
                }
            }
        }
        tokens.push_back(token_line);
    }
    return true;
}
