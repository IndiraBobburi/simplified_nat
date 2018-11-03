//
//  TrieNode.hpp
//  simplifiedNAT
//
//  Created by Indira Bobburi.
//

#ifndef TrieNode_hpp
#define TrieNode_hpp

#include <stdio.h>
#include <map>
#include <string>

/*
 * Each number in the ip and port are saved as a TrieNode.
 */
class TrieNode {
    public:
        TrieNode(){}
        TrieNode(int value);
        void setResult(const std::string& r);
        std::string getResult() const;
        
        int value;
        std::string result;
        std::map<int, TrieNode*> children;
};

/*
 * Trie class starting with root has nodes from input
 * This covers 3 cases ip:port, ip:*, *:port
 */
class Trie {
    public:
        Trie();
        
        /*insert entry in the format valid in NAT file*/
        void insert(const std::string &entry);
        
        /*search entry in the format valid in FLOW file and output to result*/
        bool search(const std::string &entry, std::string &result);
       
    private:
        /*
         * Checks if parent has child with value, if so returns the child node 
         * else creates new Node as child with value to the parent
         */
        TrieNode* getChildNode(TrieNode* parent, int value);
        
        /*
         * Checks if parent has child with value, if so returns the child node 
         * else returns nullptr
         */
        TrieNode* findChildNode(TrieNode* parent, int value);
        
        /*
         * Insert nodes to the root for valid ip, port and result values.
         */
        void insert(const std::string &ip, const std::string &port, const std::string& result);
        
        /*
         * Searches root for valid ip, port and returns if the input exists in the node
         * and result will populated.
         */
        bool search(const std::string &ip, const std::string &port, std::string &result);
        
        /*
         * Returns if child exist for a particular node.
         */
        bool haveChildren(TrieNode const*);
        
        /* Root for the Trie */
        TrieNode* root;
};

#endif /* TrieNode_hpp */

