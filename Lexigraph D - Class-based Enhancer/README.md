# **Lexigraph Class-based Enhancer**

A Python-based enhancement to the Lexigraph tool, utilizing user-defined classes and regular expressions to generate keyword-in-context concordances. This version provides a flexible and scalable approach to processing large text files.

#### **Features**

- Fully object-oriented design using Python classes.
- Regular expressions for advanced pattern matching and keyword identification.
- Handles both file input and stdin, offering flexibility for large datasets.

#### **Usage**

```bash
# Run the program with file input
python3 driver-new.py --in input.txt --out output.txt

# Alternatively, use stdin and compare with expected output
cat input.txt | python3 driver-original.py | diff output.txt expected_output.txt
```

#### **Requirements**

- Python 3.x
- No external libraries required, regular expressions are built-in.

#### **Contributing**

We welcome all contributions, including bug fixes, new features, and documentation improvements. Open an issue or submit a pull request.
