# **Lexigraph - Core Functionalities**

## **Overview**

Lexigraph is a command-line tool written in C that generates a keyword-in-context concordance from text files. It indexes specified keywords while excluding predefined words, providing a detailed context around each keyword occurrence. This tool is designed for Unix-based environments and focuses on processing single text files for indexing.

## **Features**

- **Keyword Indexing:** Generates a concordance index showing keywords in their original context.
- **Exclusion List:** Ignores predefined words such as articles, conjunctions, and prepositions.
- **Context Display:** Provides surrounding text for each keyword occurrence.
- **Command-Line Interface:** Easy integration with Unix-based command-line environments.

## **Usage**

1. **Compile the Program**

   ```bash
   gcc -o lexig-core-exc lexig-core.c
   ```

2. **Run the Program**

   ```bash
   cat tests/in01.txt | ./lexig-core-exc > temp.txt
   ```

3. **Compare Output**

   To compare the program's output with the expected output:

   ```bash
   cat tests/in01.txt | ./lexig-core-exc | diff tests/out01.txt -
   ```

## **Requirements**

- **C Standard:** C11 (Compile with `-std=c11`)
- **Dynamic Memory:** The program does not use dynamic memory allocation.

## **Testing**

A Python script is provided to automate the testing process. It compiles the program, runs tests, and cleans up the compiled executable. The test results are color-coded for clarity.

### **Run the Python Test Script**

1. Ensure all test files are in the `tests` directory.
2. Execute the test script:

   ```bash
   python3 test-lex-A.py
   ```

   **Sample Output:**

   ```
   Compiling the program...
   Compilation successful.
   Checking in01.txt (input path: tests/in01.txt) and out01.txt (output path: tests/out01.txt)...
   in01.txt PASSED
   Checking in02.txt (input path: tests/in02.txt) and out02.txt (output path: tests/out02.txt)...
   in02.txt PASSED
   Checking in03.txt (input path: tests/in03.txt) and out03.txt (output path: tests/out03.txt)...
   in03.txt PASSED
   ...
   Checking in10.txt (input path: tests/in10.txt) and out10.txt (output path: tests/out10.txt)...
   in10.txt PASSED
   Cleaned up the compiled executable.
   ```

## **Contributing**

Contributions to improve the tool are welcome. Please submit issues or pull requests for bug fixes or new features.
