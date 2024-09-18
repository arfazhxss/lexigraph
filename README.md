# Lexigraphy Context Mapper

**Lexigraph** is a Python and C-based tool designed to generate keyword-in-context concordances from text files, providing users with powerful text indexing and contextual analysis. This tool facilitates the exploration of large text datasets by indexing words and offering a detailed view of their contextual usage.

## Key Features (Completed Tasks):
- [x] **Dynamic Memory Management**: Implemented efficient memory handling in C, with Valgrind confirming no memory leaks.
- [x] **Flexible Input/Output**: Added support for processing text from standard input or files, with results outputted to the console or files.
- [x] **Exclusion Lists**: Customizable exclusion lists (e.g., common conjunctions) are implemented for words to be ignored during indexing.
- [x] **Regular Expressions**: Integrated Python’s regex capabilities for precise pattern matching and keyword identification.
- [x] **Text Exploration**: Enhanced readability by capitalizing indexed words in their original context for easy navigation.
- [x] **Platform Compatibility**: Fully compatible with Linux environments, ensuring stable performance across different systems.

## How to Use:
Clone the repository:
```bash
git clone https://github.com/username/lexigraph.git
```

### Running the Program:
For Python:
```bash
python3 lexigraph.py --in input.txt --out output.txt
```

For C:
```bash
gcc -o lexigraph lexigraph.c
./lexigraph < input.txt > output.txt
```

Contributions are welcome!
