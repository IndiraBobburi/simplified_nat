//
//  main.cpp
//  simplified_nat
//
//  Created by Indira Bobburi.
//

#include <iostream>
#include <fstream>
#include <regex>
#include "TrieNode.hpp"

using namespace std;

const string INPUT_NAT_FILE = "input/NAT.txt";
const string INPUT_FLOW_FILE = "input/FLOW.txt";
const string OUTPUT_FILE = "output/OUTPUT.txt";

int main(int argc, const char * argv[]) {
    
    // Open the input NAT file.
    ifstream input;
    input.open(INPUT_NAT_FILE);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_NAT_FILE << endl;
        return -1;
    }
    
    Trie* tree = new Trie();
    string line;
    while(getline(input, line)) {
       // cout << line << endl;
        tree->insert(line);
    }
    input.close();
    
    // Open input Flow file
    input.open(INPUT_FLOW_FILE);
    if (input.fail())
    {
        cout << "Failed to open " << INPUT_FLOW_FILE << endl;
        return -1;
    }
    
    std::string result;
    
    //output file handler
    ofstream output;  
    output.open(OUTPUT_FILE);  
    
    while(getline(input, line)) {
        //cout << line << endl;
        result = "";
        bool success = tree->search(line, result);
        if(success && !result.empty()) {
            output << line << " -> " << result << endl;
        } else {
            output << "No match for " << line << endl;
        }
    }
    input.close();
    
    
    return 0;
}

