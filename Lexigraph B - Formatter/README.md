# **Lexigraph Formatter - Python Version**

**Lexig-formatter.py** is a Python tool for generating formatted keyword-in-context (KWIC) concordances, used primarily for text analysis. It is part of the Lexigraph suite and enhances readability by aligning keywords and their surrounding context, adhering to column-specific formatting rules.

## **Table of Contents**

- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Command-Line Options](#command-line-options)
- [Test Suite](#test-suite)
- [Implementation Details](#implementation-details)
- [Contributing](#contributing)
- [License](#license)

## **Features**

- **Keyword-in-Context (KWIC) Formatter:** Formats keywords and their surrounding context, adhering to specific alignment rules.
- **Case-Insensitive Indexing:** Indexes keywords regardless of case (upper or lower).
- **Column Constraints:** 
  - Keywords are centered at column 30.
  - Left context starts from column 10.
  - Right context ends at column 60.
- **Customizable Exclusion Words:** Allows specific words to be excluded from indexing.
- **Simple and Efficient:** No external libraries required (except for testing), and efficient performance for large datasets.
- **Test Suite:** Comprehensive tests (15 cases) to ensure the correctness of the formatter output.

## **Installation**

### Requirements

- **Python**: Version 3.x is required to run this script.
- **Operating System**: Developed and tested on Linux. It should run on any platform with a Python 3.x interpreter.

### Clone the Repository

```bash
git clone https://github.com/your-repo/lexig-formatter.git
cd lexig-formatter
```

### No Dependencies

This script does not rely on any external libraries, except for optional testing (`colorama` for colored output, used only for test scripts).

### Install `colorama` for Test Script

```bash
pip install colorama
```

## **Usage**

The script reads text input from `stdin` and outputs formatted concordances to `stdout`.

### Example Usage

```bash
cat input.txt | python3 lexig-formatter.py > output.txt
```

### Compare Output with Expected Results

To validate the output, use `diff` to compare it with an expected output file:

```bash
diff expected_output.txt output.txt
```

### Input/Output Specifications

- **Input**: Plain text files. Each line contains words that may include keywords to be indexed.
- **Output**: Formatted concordances adhering to:
  - Keywords start at column 30.
  - Left and right context constrained between columns 10 and 60.
  - Case-insensitive keyword matching, while maintaining original case in the surrounding context.

### Example Input

`input.txt`:

```text
life of robert browning the man who knew too much legend of montrose
visit to iceland orthodoxy the mountains on the track ward of king canute
```

### Example Output

```text
       the man who KNEW too much legend of montrose
     visit to ICELAND orthodoxy the mountains on the
             WARD of king canute
```

### **Test Execution**

To run all the test cases:

```bash
python3 test_suite.py
```

## **Command-Line Options**

This script does not accept command-line arguments for filenames. Input is piped from `stdin`, and output is directed to `stdout`. Here’s how to handle the most common operations:

- **Run the formatter**:
  ```bash
  cat tests/in07.txt | python3 lexig-formatter.py
  ```

- **Compare outputs**:
  ```bash
  cat tests/in07.txt | python3 lexig-formatter.py | diff tests/out07.txt -
  ```

## **Test Suite**

The included test suite ensures the correctness of the script. The script (`test_suite.py`) automates the comparison of actual vs. expected output for 15 test cases.

### **Running Tests**

To run the tests, execute the `test_suite.py` script. It will run the tests located in the `tests/` directory.

```bash
python3 test_suite.py
```

Test inputs are named `inXX.txt` (e.g., `in01.txt`), and the expected outputs are named `outXX.txt` (e.g., `out01.txt`).

### **Test Structure**

Each test performs the following steps:
1. Reads input data from a file (e.g., `in01.txt`).
2. Runs the formatter and captures its output.
3. Compares the captured output with the expected output (e.g., `out01.txt`).
4. Displays a pass/fail message for each test.

### **Testing Example**

To run an individual test, such as `in01.txt`, manually:

```bash
cat tests/in01.txt | python3 lexig-formatter.py | diff tests/out01.txt -
```

### **Automated Test Script Breakdown**

- **compile_program()**: Simulates compilation for non-Python projects (skipped in Python).
- **run_tests()**: Loops through all 15 test cases and compares the formatter's output with expected results.
- **cleanup()**: No files to clean in Python, but included for extensibility in case temporary files are added in the future.

## **Implementation Details**

### **Core Script (`lexig-formatter.py`)**

- **Main Function**: Reads from `stdin`, processes lines, formats keywords based on defined rules, and outputs concordances to `stdout`.
- **Keyword Matching**: The script ignores case when indexing keywords but preserves the original casing in the output.
- **Text Alignment**:
  - **Left of keyword**: Appears between columns 10–30.
  - **Right of keyword**: Appears between columns 30–60.

### **Test Suite (`test_suite.py`)**

- **Language**: Python.
- **Libraries**: Uses `subprocess` to run `lexig-formatter.py` and compare outputs. Optionally uses `colorama` for colored terminal output.
- **Test Strategy**: 15 tests covering simple to complex cases, including handling of exclusion words, capitalization, and keyword alignment.

## **Contributing**

We welcome contributions! Follow these steps:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -am 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a Pull Request.

For bugs or feature requests, please open an issue in the repository.

## **License**

This project is licensed under the MIT License. 