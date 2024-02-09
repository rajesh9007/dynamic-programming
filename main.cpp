#include <iostream>
#include <string>
#include <map>

struct Node {
    std::map<char, Node*> children;
    int suffixIndex;
    bool isLeaf;

    Node() {
        isLeaf = false;
    }
};

Node* buildSuffixTree(const std::string& str) {
    Node* root = new Node();

    for (int i = 0; i < str.size(); i++) {
        Node* cur = root;
        for (int j = i; j < str.size(); j++) {
            char c = str[j];
            if (cur->children.count(c) == 0)
                cur->children[c] = new Node();
            cur = cur->children[c];
        }
        cur->isLeaf = true;
        cur->suffixIndex = i;
    }
    return root;
}

int traverseAndGetLongestPath(Node* root, const std::string& str) {
    Node* cur = root;
    int len = 0;
    for (char c : str) {
        if (cur->children.count(c) == 0)
            break;
        len++;
        cur = cur->children[c];
    }
    return len;
}

int main() {
    std::string str1, str2;

    std::cout << "Enter first string: ";
    std::cin >> str1;

    std::cout << "Enter second string: ";
    std::cin >> str2;

    Node* suffixTree = buildSuffixTree(str1);

    int maxLen = 0;
    int endIndex = 0;

    for (int i = 0; i < str2.size(); i++) {
        int len = traverseAndGetLongestPath(suffixTree, str2.substr(i));
        if (len > maxLen) {
            maxLen = len;
            endIndex = i;
        }
    }

    std::string result = str2.substr(endIndex, maxLen);
    std::cout << "Longest common substring: " << result << "\n";
    std::cout << "Length: " << maxLen << "\n";

    return 0;
}
