#ifndef CLASS_H
#define CLASS_H

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#define N_TERMINAL 18
#define N_NONTERMINAL 16
#define N_GRAMMAR 25

using namespace std;

// Node for syntax tree
class Node{
    public:
    string data;            // terminal, nonterminal data
    int childn;             // number of child
    Node* parent;           // parent node address
    vector<Node*> child;    // child node address
    int line_num;           // line nunber in target code

    int reg;                // register number
    int label;              // label number
    int scope;              // scope number
};

// Regular Grammar
class Grammar{
    public:
    vector<string> rhs;     // right hand side object
    int grammar_id;         
};

class Nonterminal{
    public:
    string nonterminal;
    int nonterminal_id;
};

class Terminal{
    public:
    string terminal;
    int terminal_id;
};

#endif
