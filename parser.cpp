#include "class.h"
#include "extern.h"

using namespace std;

bool parsing_table_generator(void)
{
    //1. Grammar assign
    //2. Making table
}
int find_terminal_id(string terminal)
{
    
}

int find_nonterminal_id(string nonterminal)
{

}

bool LL_parser(vector<vector<string>> token)
{   
    int line = 0;
    vector <string> parse_stack;
    parse_stack.push_back("prog"); 
    while(1)
    {
        if(token.size() == line + 1 && token[line].size() == 0) break;
        else if(token[line].size() == 0) line++;

        if(parse_stack.size() == 0)
        {
            cout << "Syntax Error: excessive input token" << endl;
            return false;
        }
        
        if(token[line][0] == parse_stack[0])
        {
            token.erase(token.begin());
            parse_stack.erase(parse_stack.begin());
            continue;
        }
        
        int terminal_id = find_terminal_id(token[line][0]);
        int nonterminal_id = find_nonterminal_id(parse_stack[0]);
        if(terminal_id == -1 || nonterminal_id == -1) 
        {
            cout << "Syntax Error: line " << line+1 << endl;
            return false;
        }

        Grammar* current_grammar = parsing_table[nonterminal_id][terminal_id];
        token.erase(token.begin());
        parse_stack.erase(parse_stack.begin());
        for(int i = 0; i < current_grammar->rhs.size(); i++)
        {
            parse_stack.insert(parse_stack.begin()+i, current_grammar->rhs[i]);
        }

    }

    if(parse_stack.size() == 0) return true;
    else 
    {
        cout << "Syntax Error: missing input token" << endl;
        return false;
    }          
}
