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
    int line_number = 0;
    while(1)
    {
        line_number++;
        string input_line;
        size_t rp_begin = 0;
        vector<string> token_line;

        getline(read_file, input_line);
        if(read_file.eof()) break;
        
        int state = 0;
        for(size_t i = 0; i < input_line.size(); i++)
        {
            if(input_line[i] == ' ' || input_line[i] == '\t')
            {
                if(i - rp_begin == 0)
                {
                    rp_begin++;
                    continue;
                }
                string t = input_line.substr(rp_begin, i - rp_begin);
                rp_begin = i+1;
                token_line.push_back(t);
                state = 0;
                continue;
            }

            int flag = 0;
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
                    state = 0;
                    flag = 1;
                    break;
                }
            }
            if(flag == 1) continue;

            if(input_line[i] - '0' >= 0 && input_line[i] - '0' <= 9)
            {
                if(state == 0) state = 1;
                else if(state == 2)
                {
                    cout << "Lexical Error (Line " << line_number << "): invalid variable name\n";
                    return false;
                }
            }
            else if((input_line[i] - 'a' >= 0 && input_line[i] - 'a' <= 25) || (input_line[i] - 'A' >= 0 && input_line[i] - 'A' <= 25)) 
            {
                if(state == 0) state = 2;
                else if(state == 1)
                {
                    cout << "Lexical Error (Line " << line_number << "): invalid variable name\n";
                    return false;
                }
            }
            else
            {
                cout << "Lexical Error (Line " << line_number << "): invalid variable name\n";
                return false;
            }
        }
        tokens.push_back(token_line);
    }
    return true;
}
