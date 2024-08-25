// TRIE_H
#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>  

using namespace std;

struct TrieNode {
    unique_ptr<TrieNode> children[4];
    bool isEndofSequence;

    TrieNode() : isEndofSequence(false) {
        for (int i = 0; i < 4; i++) {
            children[i] = nullptr;
        }
    }
};

class Trie {
private:
    unique_ptr<TrieNode> root;

public:
    Trie() : root(make_unique<TrieNode>()) {}

    void insert(const string& sequence) {
        TrieNode* node = root.get();

        for (char c : sequence) {
            int index = charToIndex(c);
            if (index == -1) return; // Skip unsupported characters
            if (!node->children[index]) {
                node->children[index] = make_unique<TrieNode>();
            }
            node = node->children[index].get();
            node->isEndofSequence = true; // Mark every node in the path as a potential end
        }
    }

    bool search(const string& sequence) {
        for (size_t i = 0; i < sequence.length(); i++) {
            if (searchFromPosition(root.get(), sequence, i)) {
                return true;
            }
        }
        return false;
    }

    bool searchFromPosition(TrieNode* node, const string& sequence, size_t index) {
        if (!node) return false;

        for (size_t j = index; j < sequence.length(); j++) {
            int charIndex = charToIndex(sequence[j]);
            if (charIndex == -1) return false;

            if (!node->children[charIndex]) {
                return false;
            }
            node = node->children[charIndex].get();
        }
        return node->isEndofSequence;
    }

    bool searchWithAllowedMismatches(const string& sequence, int allowedMismatches) {
        for (size_t i = 0; i < sequence.length(); i++) {
            if (searchWithMismatch(root.get(), sequence.substr(i), 0, 0, allowedMismatches)) {
                return true;
            }
        }
        return false;
    }

private:
    bool searchWithMismatch(TrieNode* node, const string& sequence, int index, int mismatchCount, int allowedMismatches) {
        if (!node) return false;

        if (index == sequence.length()) {
            return node->isEndofSequence && mismatchCount <= allowedMismatches;
        }

        int charIndex = charToIndex(sequence[index]);

        // Exact match
        if (node->children[charIndex] && searchWithMismatch(node->children[charIndex].get(), sequence, index + 1, mismatchCount, allowedMismatches)) {
            return true;
        }

        // Try mismatches
        if (mismatchCount < allowedMismatches) {
            for (int i = 0; i < 4; i++) {
                if (node->children[i]) {
                    if (searchWithMismatch(node->children[i].get(), sequence, index + 1, mismatchCount + 1, allowedMismatches)) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    int charToIndex(char c) {
        switch (c) {
            case 'A': return 0;
            case 'C': return 1;
            case 'G': return 2;
            case 'T': return 3;
            default:
                cerr << "Error: Unsupported character '" << c << "' in sequence." << endl;
                return -1;
        }
    }
};

#endif // TRIE_H
