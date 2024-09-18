# **Lexigraph Formatter - Python Version**

This Python tool enhances the Lexigraph suite by generating formatted keyword-in-context concordances. It improves readability by aligning keywords and their surrounding context.

#### **Features**
- Reads input text and generates concordances with aligned keywords.
- Handles both upper and lower case keywords, treating them equivalently for indexing.
- Words surrounding the keyword are displayed for context, with customizable column alignment.
  
#### **Usage**
```bash
# Run the script
cat input.txt | python3 concord2.py > output.txt

# Compare output with expected results
diff expected_output.txt output.txt
```

#### **Requirements**
- Python 3.x
- No external libraries required.

#### **Contributing**
Please open issues for any bugs or feature requests, and feel free to submit pull requests.
