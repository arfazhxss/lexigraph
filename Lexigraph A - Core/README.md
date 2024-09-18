# **Lexigraph - Core Functionalities**

A C-based command-line tool for generating keyword-in-context concordances from text files. This tool indexes keywords while excluding predefined words, forming the core functionality of the Lexigraph suite.

#### **Features**
- Processes text files to create a concordance (keyword-in-context) index.
- Excludes certain predefined words (e.g., "the", "and") from being indexed.
- Provides context around keywords by displaying surrounding text.
- Command-line interface for easy use with Unix-based environments.
  
#### **Usage**
```bash
# Compile the program
gcc -o lexigraph_core concord1.c

# Run the program with input and output redirection
cat input.txt | ./lexigraph_core > output.txt
```

#### **Requirements**
- C11 Standard (Compile with `-std=c11`)
- No dynamic memory allocation is used in this project.

#### **Contributing**
Feel free to submit issues and pull requests for bug fixes or new features.

