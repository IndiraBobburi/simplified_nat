# Simplified Nat implementation

## Instructions to run
```
git clone https://github.com/IndiraBobburi/simplified_nat
cd simplified_nat
g++ -Wall main.cpp TrieNode.cpp -o main
./main
```

## Assumptions
1. Format will be valid in NAT and FLOW file
2. If for an entry in FLOW file which has matched from NAT file (such as ip:port, ip:*, *:port), result for that matches has the priority order: ip:port > ip:* > *:port
3. Entire NAT file will be fit into the memory in the Trie datastructure.

## More ideas on optimal solution
If there is a way to convert IP address to a int and get back IP address from the int, storing the int value, port and result in maps (to consider all three cases) would have been efficient and easy to understand code.
