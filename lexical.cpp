#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"
#include "extern.h"

#define OPERATORS_N 9

using namespace std;

char operators[] = {'+', '*', '<', ';', '=', '(', ')', '{', '}'};
bool lexical_analyzer(ifstream& read_file, vector<vector<string>>& tokens)
{
    int line_number = 0;
    while(1)
    {
        line_number++;
        string input_line;
        size_t rp_begin = 0; // read pointer which pointing the start position of token in the line
        vector<string> token_line;

        // get line until file ends
        getline(read_file, input_line);
        if(read_file.eof()) break;
        int state = 0; // state for FSA

        // read each character in the line
        for(size_t i = 0; i < input_line.size(); i++)
        {
            // if character is space or tab : generate new token
            if(input_line[i] == ' ' || input_line[i] == '\t')
            {
                // if there is only space or tab : do not generate token
                if(i - rp_begin == 0)
                {
                    rp_begin++;
                    continue;
                }
                
                // generate token by get substring of line
                string t = input_line.substr(rp_begin, i - rp_begin);
                rp_begin = i+1;
                token_line.push_back(t);
                state = 0;
                continue;
            }

            int flag = 0; // flag == 1 if charcter is operator

            for(size_t j = 0; j < OPERATORS_N; j++)
            {
                // if character is operator
                if( input_line[i] == operators[j] )
                {
                    // if other variable entered before operator
                    if(i != rp_begin){
                        // generate token for variable first
                        string t1 = input_line.substr(rp_begin, i - rp_begin);
                        token_line.push_back(t1);
                    }
                    
                    //generate token for operator
                    string t2 = input_line.substr(i, 1);
                    token_line.push_back(t2);
                    
                    rp_begin = i+1;
                    state = 0;
                    flag = 1;
                    break;
                }
            }
            if(flag == 1) continue;


            // ERROR HANDLING
            //=============================================================================================================================
            // if character is not operators or space or tab
            // if charcter is number
            if(input_line[i] - '0' >= 0 && input_line[i] - '0' <= 9)
            {
                // check state
                if(state == 0) state = 1;
                else if(state == 2)
                {
                    //if state == 2 : error (can't use alphabet and number both in one variable name)
                    cout << "Lexical Error (Line " << line_number << "): Can't use numbers and alphabets both in variable name\n";
                    return true;
                }
            }

            // if charcter is alphabet
            else if((input_line[i] - 'a' >= 0 && input_line[i] - 'a' <= 25) || (input_line[i] - 'A' >= 0 && input_line[i] - 'A' <= 25)) 
            {
                // check state
                if(state == 0) state = 2;
                else if(state == 1)
                {
                    //if state == 1 : error (can't use alphabet and number both in one variable name)
                    cout << "Lexical Error (Line " << line_number << "): Can't use numbers and alphabets both in variable name\n";
                    return true;
                }
            }

            // if character isn't alphabet or number
            else
            {
                cout << "Lexical Error (Line " << line_number << "): invalid variable name\n";
                return true;
            }
            //=============================================================================================================================
            
            // if the character is last one in line, generate token
            if(i == input_line.size()-1)
            {
                string t = input_line.substr(rp_begin, i+1 - rp_begin);
                rp_begin = i+1;
                token_line.push_back(t);
                state = 0;

            }

        }

        // add all tokens that in the line
        tokens.push_back(token_line);
    }
    return false;
}
