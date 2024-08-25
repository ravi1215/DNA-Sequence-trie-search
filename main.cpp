//DNA Sequence Search using Trie

#include "trie.h"
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <memory>

using namespace std;

vector<string> readFastaFile(const string& filename) {
    ifstream file(filename);
    vector<string> sequences;
    string line;
    string currentSequence;

    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << endl;
        return sequences;
    }

    while (getline(file, line)) {
        if (line[0] == '>') {
            if (!currentSequence.empty()) {
                sequences.push_back(currentSequence);
                currentSequence.clear();
            }
        } else {
            currentSequence += line;
        }
    }
    if (!currentSequence.empty()) {
        sequences.push_back(currentSequence);
    }

    file.close();
    return sequences;
}

int main() {
    Trie trie;

    vector<string> sequences = readFastaFile("/Users/ravipandey/Project R/data/sequence.fasta"); 

    for (const string& seq : sequences) {
        cout << "Inserting: " << seq << endl;
        trie.insert(seq); 
    }

    string userSequence;
    int allowedMismatches;

    while (true) {
        cout << "Enter a DNA sequence to search (or type 'exit' to quit): ";
        cin >> userSequence;

        if (userSequence == "exit") {
            break;
        }

        cout << "Enter the number of allowed mismatches: ";
        cin >> allowedMismatches;

        if (allowedMismatches > 2) {
            cout << "Error: Number of mismatches cannot be greater than 2." << endl;
            continue;
        }

        if (allowedMismatches == 0) {
            cout << (trie.search(userSequence) ? "Found" : "Not Found") << endl;
        } else {
            cout << (trie.searchWithAllowedMismatches(userSequence, allowedMismatches) ? 
                    "Found with mismatches" : "Not Found with mismatches") << endl;
        }
    }
    return 0;
}
