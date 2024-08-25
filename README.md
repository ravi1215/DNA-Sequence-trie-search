# DNA Sequence Trie Search

## Overview

This project is a DNA sequence search tool implemented in C++ using a Trie data structure. It allows you to insert DNA sequences from a FASTA file taken from latest NCBI Homo sapeins dataset dated Feb 22, 2022 into a Trie and search for sequences with optional mismatches.

## Features

- **Insert DNA Sequences**: Insert sequences from a FASTA file into the Trie.
- **Exact Search**: Search for exact matches of a DNA sequence.
- **Approximate Search**: Search for matches with a specified number of allowed mismatches with upto 2 mismatches.
- **Command-Line Interface**: Interact with the program via a command-line interface.

## Files

- `main.cpp`: Contains the main implementation of the Trie, the FASTA file reader, and the command-line interface.
- `trie.h`: Header file for the `Trie` class and `TrieNode` structure.

## How to Build and Run

1. **Clone the Repository**: Download the project files to your local machine.

2. **Compile the Program**:
   ```bash
g++ -std=c++14 main.cpp -o main_program
