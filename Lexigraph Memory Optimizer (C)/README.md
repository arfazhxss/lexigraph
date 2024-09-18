# **Lexigraph Memory Optimizer**

An advanced C implementation of the Lexigraph tool that focuses on dynamic memory management. This project uses linked lists and dynamic arrays to store keywords and text data while leveraging Valgrind for memory optimization.

#### **Features**
- Uses dynamic memory allocation to handle large and variable-sized text inputs.
- Implements linked lists and dynamic arrays to store indexed keywords and exception words.
- Optimized with Valgrind for effective memory management, ensuring no memory leaks.
  
#### **Usage**
```bash
# Compile the program
make

# Run the program with input redirection and diff comparison
cat input.txt | ./lexigraph_memory | diff output.txt expected_output.txt

# Use Valgrind to check memory
valgrind ./lexigraph_memory < input.txt
```

#### **Requirements**
- C11 Standard
- Valgrind for memory management and debugging.
  
#### **Contributing**
Contributions and improvements are welcome. Please report any issues, and submit pull requests.
