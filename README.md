# Lexigraph

**Lexigraph** is a Python and C-based tool designed to generate keyword-in-context concordances from text files, providing users with powerful text indexing and contextual analysis. This tool facilitates the exploration of large text datasets by indexing words and offering a detailed view of their contextual usage.

## Key Features:
- **Dynamic Memory Management**: Uses C for efficient memory handling with Valgrind to detect memory leaks.
- **Flexible Input/Output**: Supports text processing from standard input or files, with results outputted to the console or files.
- **Exclusion Lists**: Allows customizable lists of words (like common conjunctions) to be ignored during indexing.
- **Regular Expressions**: Leverages Python's regex capabilities for precise pattern matching.
- **Text Exploration**: Provides insights by capitalizing indexed words in their original context for easy navigation.
- **Platform Compatibility**: Designed to work on Linux, ensuring stable performance across different environments.

## How to Use:
Clone the repository:
```bash
git clone https://github.com/username/lexigraph.git
```

### Running the Program:
For Python:
```bash
python3 concord4.py --in input.txt --out output.txt
```

For C:
```bash
gcc -o concord3 concord3.c
./concord3 < input.txt > output.txt
```

Contributions are welcome!
