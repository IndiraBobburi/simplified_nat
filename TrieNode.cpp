//
//  TrieNode.cpp
//  simplified_nat
//
//  Created by Indira Bobburi.
//

#include "TrieNode.hpp"
#include <regex>
#include <string>
#include <iostream>

using namespace std;

/* TrieNode implementation */
TrieNode::TrieNode(int value) {
    this->value = value;
}

void TrieNode::setResult(const std::string& r) {
    result = r;
}

std::string TrieNode::getResult() const {
    return result;
}

/* Trie implementation */
Trie::Trie() {
    root = new TrieNode();
}

void Trie::insert(const std::string &entry) {
    smatch match;
    regex_match(entry, match, regex("(.*):(.*),(.*)"));
    string ip, port, result;
    if(match.size() == 4) {
        ip = match[1];
        port = match[2];
        result = match[3];
        insert(ip, port, result);
    }
}

void Trie::insert(const std::string &ip, const std::string &port, const std::string& result) {
    if(ip == "*") {
        //inserting *:port in -1 node of root
        TrieNode* emptyip = getChildNode(root, -1);
        TrieNode* portNode = getChildNode(emptyip, stoi(port)); 
        portNode->setResult(result);
    } else {
        smatch match;
        regex_match(ip, match, regex("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})"));
        //cout << match[1] << " " << match[2] << " " <<  match[3] << " " <<  match[4] << endl;  
        if(match.size() == 5) {
            //TODO: Make this generic
            TrieNode* level1 = getChildNode(root, stoi(match[1]));
            TrieNode* level2 = getChildNode(level1, stoi(match[2]));
            TrieNode* level3 = getChildNode(level2, stoi(match[3]));
            TrieNode* level4 = getChildNode(level3, stoi(match[4]));
            
            if(port == "*") {
                TrieNode* starNode = getChildNode(level4, -1); 
                starNode->setResult(result);
            } else {
                TrieNode* portNode = getChildNode(level4, stoi(port)); 
                portNode->setResult(result);
            }
            
        }
    }
}

TrieNode* Trie::getChildNode(TrieNode* parent, int value) {
    map<int, TrieNode*>::iterator it = parent->children.find(value);
    if(it == parent->children.end()) {
        TrieNode* child = new TrieNode(value);
        parent->children[value] = child;
        return child;
    }     
    else {
        return it->second;
    }    
}

TrieNode* Trie::findChildNode(TrieNode* parent, int value) {
    map<int, TrieNode*>::iterator it = parent->children.find(value);
    if(it == parent->children.end()) {
        return nullptr;
    }     
    else {
        return it->second;
    }    
}

bool Trie::search(const std::string &entry, std::string &result) {
    smatch match;
    regex_match(entry, match, regex("(.*):(.*)"));
    string ip, port;
    if(match.size() == 3) {
        ip = match[1];
        port = match[2];
    }
    return search(ip, port, result);
}

bool Trie::search(const std::string &ip, const std::string &port, std::string &result) {
    if(ip == "*" || port == "*") {
        result = "";
        return false;
    }
        
     
    smatch match;
    regex_match(ip, match, regex("(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})\\.(\\d{1,3})"));
    if(match.size() == 5) {
        //cout << match[1] << match[2] << match[3] << match[4] << endl;
        TrieNode* child = root;
        for(int i=1; i<=4 && child != nullptr; i++) {
            child = findChildNode(child, stoi(match[i]));
        }
        if(child != nullptr) { //ip found
            TrieNode* portNode = findChildNode(child, stoi(port));
            if(portNode != nullptr && !portNode->getResult().empty()) { //ip:port exists
                    result = portNode->getResult();
                    return true;
            } else {
                TrieNode* starNode = findChildNode(child, -1);
                if(starNode != nullptr) { // ip:* exists
                    result = starNode->getResult();
                    return true;
                }
            }
        } else { //ip not found 
            TrieNode* starNode = findChildNode(root, -1);
            if(starNode != nullptr) {
                TrieNode* portNode = findChildNode(starNode, stoi(port)); // *:port exists
                if(portNode != nullptr && !portNode->getResult().empty()) {
                    result = portNode->getResult();
                    return true;
                }
            }
        }
    }
    result = "";
    return false;
}

bool Trie::haveChildren(TrieNode const* parent) {
    return (parent != nullptr) && (parent->children.size() != 0);
}

