#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "class.h"

using namespace std;

int use_register;   // number of used register

vector <vector <vector <string>>> symbol_table_scopes;

bool lexical_analyzer(ifstream& read_file, vector<vector<string>>& token);
bool LL_parser(vector<vector<string>> token, Node*& root);
void build_symbol_table(ofstream& symbol_file, Node*& root);
bool code_generator(ofstream& code_file, Node* topnode);

int main(int argc, char** argv)
{
    if(argc != 2){
        cout << "Input File Error!" << endl;
        return 0;
    }

    string input_file_name(argv[1]);
    
    // open files for result
    ifstream target_file;
    ofstream instruction_file;
    ofstream symbol_file;

    target_file.open(input_file_name);
    instruction_file.open(input_file_name + ".code");
    symbol_file.open(input_file_name + ".symbol");

    vector<vector<string>> tokens; // data of tokens
    Node* root; // root address of syntax tree
    bool is_error = false;
    
    //compiler starts : returns true if error occurs
    is_error = lexical_analyzer(target_file, tokens);
    if(!is_error) is_error = LL_parser(tokens, root);
	if(!is_error) build_symbol_table(symbol_file, root);
    if(!is_error) code_generator(instruction_file, root);

    //close files
    target_file.close();
    instruction_file.close();
    symbol_file.close();
}
