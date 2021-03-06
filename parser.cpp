#include "class.h"
#include "extern.h"

using namespace std;

Grammar grammar_list[N_GRAMMAR];
Nonterminal nonterminal_list[N_NONTERMINAL];
Terminal terminal_list[N_TERMINAL];
Grammar* parsing_table[N_NONTERMINAL][N_TERMINAL];

void parsing_table_generator(void)
{
    //1. nonterminal list
    //
    nonterminal_list[0].nonterminal = "prog0";
    nonterminal_list[0].nonterminal_id = 0;

    nonterminal_list[1].nonterminal = "decl0";
    nonterminal_list[1].nonterminal_id = 1;
    
    nonterminal_list[2].nonterminal = "decls0";
    nonterminal_list[2].nonterminal_id = 2;
    
    nonterminal_list[3].nonterminal = "decls_0";
    nonterminal_list[3].nonterminal_id = 3;
    
    nonterminal_list[4].nonterminal = "vtype0";
    nonterminal_list[4].nonterminal_id = 4;

    nonterminal_list[5].nonterminal = "block0";
    nonterminal_list[5].nonterminal_id = 5;

    nonterminal_list[6].nonterminal = "slist0";
    nonterminal_list[6].nonterminal_id = 6;

    nonterminal_list[7].nonterminal = "slist_0";
    nonterminal_list[7].nonterminal_id = 7;

    nonterminal_list[8].nonterminal = "stat0";
    nonterminal_list[8].nonterminal_id = 8;
    
    nonterminal_list[9].nonterminal = "cond0";
    nonterminal_list[9].nonterminal_id = 9;
 
    nonterminal_list[10].nonterminal = "expr0";
    nonterminal_list[10].nonterminal_id = 10;
  
    nonterminal_list[11].nonterminal = "E_0";
    nonterminal_list[11].nonterminal_id = 11;   
    
    nonterminal_list[12].nonterminal = "T0";
    nonterminal_list[12].nonterminal_id = 12;   
    
    nonterminal_list[13].nonterminal = "T_0";
    nonterminal_list[13].nonterminal_id = 13;  
 
    nonterminal_list[14].nonterminal = "F0";
    nonterminal_list[14].nonterminal_id = 14;

    nonterminal_list[15].nonterminal = "fact0";
    nonterminal_list[15].nonterminal_id = 15;

    //2. terminal list

    terminal_list[0].terminal = "$";
    terminal_list[0].terminal_id = 0;

    terminal_list[1].terminal = "(";
    terminal_list[1].terminal_id = 1;

    terminal_list[2].terminal = ")";
    terminal_list[2].terminal_id = 2;

    terminal_list[3].terminal = ";";
    terminal_list[3].terminal_id = 3;

    terminal_list[4].terminal = "int";
    terminal_list[4].terminal_id = 4;

    terminal_list[5].terminal = "char";
    terminal_list[5].terminal_id = 5;

    terminal_list[6].terminal = "{";
    terminal_list[6].terminal_id = 6;

    terminal_list[7].terminal = "}";
    terminal_list[7].terminal_id = 7;

    terminal_list[8].terminal = "IF";
    terminal_list[8].terminal_id = 8;

    terminal_list[9].terminal = "THEN";
    terminal_list[9].terminal_id = 9;

    terminal_list[10].terminal = "ELSE";
    terminal_list[10].terminal_id = 10;

    terminal_list[11].terminal = "=";
    terminal_list[11].terminal_id = 11;

    terminal_list[12].terminal = "EXIT";
    terminal_list[12].terminal_id = 12;

    terminal_list[13].terminal = "<";
    terminal_list[13].terminal_id = 13;

    terminal_list[14].terminal = "+";
    terminal_list[14].terminal_id = 14;

    terminal_list[15].terminal = "*";
    terminal_list[15].terminal_id = 15;
   
    terminal_list[16].terminal = "num";
    terminal_list[16].terminal_id = 16;
    
    terminal_list[17].terminal = "word";
    terminal_list[17].terminal_id = 17;

    //3. grammar assign

    for(int i = 0; i < N_GRAMMAR; i++)
    {
        grammar_list[i].grammar_id = i;
    }

    grammar_list[0].rhs.push_back("word");
    grammar_list[0].rhs.push_back("(");
    grammar_list[0].rhs.push_back(")");
    grammar_list[0].rhs.push_back("block0");

    grammar_list[1].rhs.push_back("vtype0");
    grammar_list[1].rhs.push_back("word");
    grammar_list[1].rhs.push_back(";");
    
    grammar_list[2].rhs.push_back("decls_0");
    
    grammar_list[3].rhs.push_back("decl0");
    grammar_list[3].rhs.push_back("decls_0");

    grammar_list[4].rhs.clear();

    grammar_list[5].rhs.push_back("int");
    
    grammar_list[6].rhs.push_back("char");

    grammar_list[7].rhs.push_back("{");
    grammar_list[7].rhs.push_back("decls0");
    grammar_list[7].rhs.push_back("slist0");
    grammar_list[7].rhs.push_back("}");

    grammar_list[8].rhs.clear();

    grammar_list[9].rhs.push_back("slist_0");

    grammar_list[10].rhs.push_back("stat0");
    grammar_list[10].rhs.push_back("slist_0");

    grammar_list[11].rhs.clear();

    grammar_list[12].rhs.push_back("IF");
    grammar_list[12].rhs.push_back("cond0");
    grammar_list[12].rhs.push_back("THEN");
    grammar_list[12].rhs.push_back("block0");
    grammar_list[12].rhs.push_back("ELSE");
    grammar_list[12].rhs.push_back("block0");

    grammar_list[13].rhs.push_back("word");
    grammar_list[13].rhs.push_back("=");
    grammar_list[13].rhs.push_back("expr0");
    grammar_list[13].rhs.push_back(";");

    grammar_list[14].rhs.push_back("EXIT");
    grammar_list[14].rhs.push_back("expr0");
    grammar_list[14].rhs.push_back(";");

    grammar_list[15].rhs.push_back("expr0");
    grammar_list[15].rhs.push_back("<");
    grammar_list[15].rhs.push_back("expr0");

    grammar_list[16].rhs.push_back("T0");
    grammar_list[16].rhs.push_back("E_0");

    grammar_list[17].rhs.push_back("+");
    grammar_list[17].rhs.push_back("T0");
    grammar_list[17].rhs.push_back("E_0");

    grammar_list[18].rhs.clear();

    grammar_list[19].rhs.push_back("F0");
    grammar_list[19].rhs.push_back("T_0");
    
    grammar_list[20].rhs.push_back("*");
    grammar_list[20].rhs.push_back("F0");
    grammar_list[20].rhs.push_back("T_0");
    
    grammar_list[21].rhs.clear();

    grammar_list[22].rhs.push_back("fact0");

    grammar_list[23].rhs.push_back("num");

    grammar_list[24].rhs.push_back("word");


    //4.making table
    for(int i = 0; i < N_GRAMMAR; i++)
    {
        for(int j = 0; j < N_GRAMMAR; j++)
        {
            parsing_table[i][j] = NULL;
        }
    }
    parsing_table[5][0] = grammar_list + 8;
    parsing_table[11][3] = grammar_list + 18;
    parsing_table[13][3] = grammar_list + 21;
    parsing_table[1][4] = grammar_list + 1;
    parsing_table[2][4] = grammar_list + 2;
    parsing_table[3][4] = grammar_list + 3;
    parsing_table[4][4] = grammar_list + 5;
    parsing_table[1][5] = grammar_list + 1;
    parsing_table[2][5] = grammar_list + 2;
    parsing_table[3][5] = grammar_list + 3;
    parsing_table[4][5] = grammar_list + 6;
    parsing_table[5][6] = grammar_list + 7;
    parsing_table[2][7] = grammar_list + 2;
    parsing_table[3][7] = grammar_list + 4;
    parsing_table[5][7] = grammar_list + 8;
    parsing_table[6][7] = grammar_list + 9;
    parsing_table[7][7] = grammar_list + 11;
    parsing_table[2][8] = grammar_list + 3;
    parsing_table[3][8] = grammar_list + 4;
    parsing_table[5][8] = grammar_list + 8;
    parsing_table[6][8] = grammar_list + 9;
    parsing_table[7][8] = grammar_list + 10;
    parsing_table[8][8] = grammar_list + 12;
    parsing_table[11][9] = grammar_list + 18;
    parsing_table[13][9] = grammar_list + 21;
    parsing_table[5][10] = grammar_list + 8;
    parsing_table[2][12] = grammar_list + 3;
    parsing_table[3][12] = grammar_list + 4;
    parsing_table[5][12] = grammar_list + 8;
    parsing_table[6][12] = grammar_list + 9;
    parsing_table[7][12] = grammar_list + 10;
    parsing_table[8][12] = grammar_list + 14;
    parsing_table[11][13] = grammar_list + 18;
    parsing_table[13][13] = grammar_list + 21;
    parsing_table[11][14] = grammar_list + 17;
    parsing_table[13][14] = grammar_list + 21;
    parsing_table[13][15] = grammar_list + 20;
    parsing_table[9][16] = grammar_list + 15;
    parsing_table[10][16] = grammar_list + 16;
    parsing_table[12][16] = grammar_list + 19;
    parsing_table[14][16] = grammar_list + 22;
    parsing_table[15][16] = grammar_list + 23;
    parsing_table[0][17] = grammar_list + 0;
    parsing_table[2][17] = grammar_list + 2;
    parsing_table[3][17] = grammar_list + 4;
    parsing_table[5][17] = grammar_list + 8;
    parsing_table[6][17] = grammar_list + 9;
    parsing_table[7][17] = grammar_list + 10;
    parsing_table[8][17] = grammar_list + 13;
    parsing_table[9][17] = grammar_list + 15;
    parsing_table[10][17] = grammar_list + 16;
    parsing_table[12][17] = grammar_list + 19;
    parsing_table[14][17] = grammar_list + 22;
    parsing_table[15][17] = grammar_list + 24;

}

// convert terminal to terminal_id
int find_terminal_id(string terminal)
{
   for(int i = 0; i < N_TERMINAL-2; i++)
   {
       if(terminal_list[i].terminal == terminal) return terminal_list[i].terminal_id;
   }
   //terminal is num
   if(terminal[0] - '0' >= 0 && terminal[0] - '0' <= 9 ) return 16; 
   
   //terminal is word
   else if((terminal[0] - 'a' >=0 && terminal[0] - 'a' < 26) || (terminal[0] - 'A' >=0 && terminal[0] - 'A' < 26)) return 17; 
   
   // return -1 if there isn't appropriate terminal
   else return -1; 
}

// convert nonterminal to nonterminal_id
int find_nonterminal_id(string nonterminal)
{
   for(int i = 0; i < N_NONTERMINAL; i++)
   {
       if(nonterminal_list[i].nonterminal == nonterminal) return nonterminal_list[i].nonterminal_id;
   }
   // return -1 if there isn't appropriate terminal
   return -1; 
}

bool LL_parser(vector<vector<string>> token, Node*& root)
{   
    // generate parsing table
    parsing_table_generator();
    
    int line = 0;
    int flag = 0;
    vector <string> parse_stack; // stack for parser processing
    vector <Node*> node_stack;  // Node stack for gernerating tree
    
    parse_stack.push_back("prog0"); 
    root = new Node;
    root->data = "prog0";
    root->childn = 0;
    root->parent = NULL;
    node_stack.push_back(root);

    while(1)
    {
        // if parser stack is empty : end parser
        if(parse_stack.size() == 0) break;

        // if read all of tokens : read '$' for token
        else if(token.size() == line + 1 && token[line].size() == 0)
        {
            flag = 1;
            token[line].push_back("$");
        }

        // if read all of tokens in a line : read next line
        else if(token[line].size() == 0) 
        {
            while(token[line].size() == 0)
            {
                line++;
            }       
        }

        string top_parse_stack = parse_stack[0];    // top of parser stack
        string top_token = token[line][0];          // next token
        Node* top_node = node_stack[0];             // top of node stack
        // pop node stack
        node_stack.erase(node_stack.begin());

        // find terminal id
        int terminal_id = find_terminal_id(token[line][0]);
        if(terminal_id == 16) top_token = "num";
        else if(terminal_id == 17) top_token = "word";

        // if top of parser stack and token is same
        if(top_parse_stack == top_token)
        {
            // if it is number or word : make new node with token
            if(top_token == "num" || top_token == "word")
            {
                Node* newnode = new Node;
                newnode->data = token[line][0];
                newnode->childn = 0;
                newnode->parent = top_node;
                newnode->line_num = line + 1;
                top_node->childn = 1;
                top_node->child.push_back(newnode);
            }

            // pop parser stack and token
            token[line].erase(token[line].begin());
            parse_stack.erase(parse_stack.begin());
            
            continue;
        }
        
        // find nonterminal id
        int nonterminal_id = find_nonterminal_id(parse_stack[0]);
        
        // if top of parser stack or token is invalid
        if(terminal_id == -1 || nonterminal_id == -1) 
        {
            // error
            cout << "Syntax Error (Line " << line+1 << "): There is no proper grammar" << endl;
            return true;
        }

        // determine which grammar should be used with parsing table
        Grammar* current_grammar = parsing_table[nonterminal_id][terminal_id];

        // if parsing table is NULL
        if(current_grammar == NULL)
        {
            // error : no appropriate grammar
            cout << "Syntax Error (Line " << line+1 << "): There is no proper grammar" << endl;
            return true;
        }
        
        // pop parser stack
        parse_stack.erase(parse_stack.begin());
        
        // generate nodes by grammar
        for(int i = 0; i < current_grammar->rhs.size(); i++)
        {
            Node* newnode = new Node;
            newnode->data = current_grammar->rhs[i];
            newnode->childn = 0;
            newnode->parent = top_node;
            newnode->line_num = line+1;
            top_node->childn++;
            top_node->child.push_back(newnode);

            //push into node stack and parser stack
            node_stack.insert(node_stack.begin()+i, newnode);
            parse_stack.insert(parse_stack.begin()+i, current_grammar->rhs[i]);
        }
    
        // pop '$' from token
        if(flag)
        {
            token[line].pop_back();
        }
    }
    
    // skip last enter('\n') if it exist
    while(token.size() != line+1 && token[line].size() == 0)
    {
        line++;
    }

    // if read all of tokens : parser finished properly
    if(token.size() == line + 1 && token[line].size() == 0) return false;

    // if not, error occurs
    else 
    {
        cout << "Syntax Error: Excessive target code" << endl;
        cout << "        Note: Check parentheses" << endl;
        return true;
    }          
}
