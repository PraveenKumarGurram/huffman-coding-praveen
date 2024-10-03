#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// A Tree node structure for Huffman tree
struct Node {
    char ch;             // Character
    int freq;            // Frequency of the character
    Node *left, *right;  // Left and Right children
    
    Node(char ch, int freq) {
        left = right = nullptr;
        this->ch = ch;
        this->freq = freq;
    }
};

// Comparator for priority queue (min-heap)
struct Compare {
    bool operator()(Node* l, Node* r) {
        return l->freq > r->freq;  // Min-Heap based on frequency
    }
};

// Function to print the Huffman Codes in preorder traversal
void printCodes(Node* root, string code) {
    if (!root) return;
    
    // If a leaf node (character) is encountered, print its code
    if (root->ch != '#') {
        cout << root->ch << " : " << code << "\n";
    }
    
    // Recur left with '0'
    printCodes(root->left, code + "0");
    
    // Recur right with '1'
    printCodes(root->right, code + "1");
}

// Function to build the Huffman Tree and print codes
void huffmanCoding(string S, vector<int> f) {
    // Create a min-heap (priority queue)
    priority_queue<Node*, vector<Node*>, Compare> pq;
    
    // Create leaf nodes and insert them into the min-heap
    for (int i = 0; i < S.size(); ++i) {
        pq.push(new Node(S[i], f[i]));
    }
    
    // Iterate until the heap contains only one node (the root of the tree)
    while (pq.size() > 1) {
        // Extract two nodes with minimum frequency
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();
        
        // Create a new internal node with frequency equal to the sum of the two nodes
        Node* internal = new Node('#', left->freq + right->freq);
        internal->left = left;
        internal->right = right;
        
        // Insert the new node into the priority queue
        pq.push(internal);
    }
    
    // The remaining node is the root of the Huffman tree
    Node* root = pq.top();
    
    // Print Huffman Codes in preorder traversal
    printCodes(root, "");
}

// Main function
int main() {
    string S = "abcdef";
    vector<int> f = {5, 9, 12, 13, 16, 45};
    
    // Build Huffman tree and print codes
    huffmanCoding(S, f);
    
    return 0;
}
