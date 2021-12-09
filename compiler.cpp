#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"

using namespace std;

char operators[] = {'+', '*', '<', ';', '=', '(', ')', '{', '}'};
Grammar grammer_list[30];
Nonterminal nonterminal_list[N_NONTERMINAL];
Terminal terminal_list[N_TERMINAL];
Grammar* parsing_table[N_NONTERMINAL][N_TERMINAL];

bool lexical_analyzer(ifstream& read_file, vector<vector<string>>& token);
bool parsing_table_generator(void);
bool LL_parser(vector<vector<string>> token);
//bool code_generator(vector<vector<string>> token);

int main(int argc, char** argv)
{
    if(argc != 2){
        cout << "Input File Error!" << endl;
        return 0;
    }

    string input_file_name(argv[1]);
    
    ifstream target_file;
    ofstream instruction_file;
    ofstream symbol_file;

    target_file.open(input_file_name);
    instruction_file.open(input_file_name + ".code");
    symbol_file.open(input_file_name + ".symbol");

    vector<vector<string>> tokens;
    bool is_error = false;

    is_error = lexical_analyzer(target_file, tokens);
    if(is_error) cout << "lexical success" << endl;
    cout << tokens.size() << endl;
    for(int i = 0; i < tokens.size(); i++){
        cout << i+1 << " line size: " << tokens[i].size() << endl;
        for(int j = 0; j < tokens[i].size(); j++)
        {
            cout << tokens[i][j] << ' ';
        }
        cout << "\n";
    }
    is_error = parsing_table_generator();
    is_error = LL_parser(tokens);
    //is_error = code_generator(tokens);
 


    target_file.close();
    instruction_file.close();
    symbol_file.close();
}
