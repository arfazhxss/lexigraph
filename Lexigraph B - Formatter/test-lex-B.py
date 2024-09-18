import subprocess
import os
from colorama import init, Fore, Style

# Initialize colorama for colored terminal output
init()

def compile_program():
    """Compiles the Python script or core executable needed for testing."""
    print(Fore.CYAN + "Compiling the Python formatter script..." + Style.RESET_ALL)
    # Since you're using Python, there's no need to actually compile
    # If you had a C file, you could uncomment the code below:
    # result = subprocess.run(['gcc', '-o', 'lexig-formatter', 'lexig-formatter.c'], capture_output=True, text=True)
    # if result.returncode == 0:
    #     print(Fore.GREEN + "Compilation successful." + Style.RESET_ALL)
    # else:
    #     print(Fore.RED + "Compilation failed." + Style.RESET_ALL)
    #     print(result.stderr)
    #     exit(1)
    print(Fore.GREEN + "Compilation step skipped (Python script)." + Style.RESET_ALL)

def run_test(input_file, expected_output_file, input_path, expected_output_path):
    """Runs the test and compares actual output against expected output."""
    try:
        with open(input_path) as f:
            input_data = f.read()
    except FileNotFoundError:
        print(Fore.YELLOW + f"Input file {input_path} not found." + Style.RESET_ALL)
        return
    
    # Run the Python script and capture output
    result = subprocess.run(['python3', 'lexig-formatter.py'], input=input_data, text=True, capture_output=True)

    try:
        with open(expected_output_path) as f:
            expected_output = f.read()
    except FileNotFoundError:
        print(Fore.YELLOW + f"Expected output file {expected_output_path} not found." + Style.RESET_ALL)
        return
    
    # Compare the actual output with the expected output
    if result.stdout == expected_output:
        print(Fore.GREEN + f"{input_file} PASSED" + Style.RESET_ALL)
    else:
        print(Fore.RED + f"{input_file} FAILED" + Style.RESET_ALL)
        print(Fore.MAGENTA + "Expected Output:" + Style.RESET_ALL)
        print(Fore.MAGENTA + expected_output + Style.RESET_ALL)
        print(Fore.MAGENTA + "Actual Output:" + Style.RESET_ALL)
        print(Fore.MAGENTA + result.stdout + Style.RESET_ALL)

def run_tests():
    """Runs all tests from in01.txt to in15.txt and compares against expected outputs."""
    # First batch of tests: in01.txt to in09.txt
    for i in range(1, 10):
        run_individual_test(i)
    
    # Second batch of tests: in10.txt to in15.txt
    for i in range(10, 16):
        run_individual_test(i)

def run_individual_test(test_num):
    """Runs a single test given a test number."""
    input_file = f'in{test_num:02}.txt'  # in01.txt, in02.txt, etc.
    expected_output_file = f'out{test_num:02}.txt'  # out01.txt, out02.txt, etc.
    
    input_path = os.path.join('tests', input_file)
    expected_output_path = os.path.join('tests', expected_output_file)
    
    print(Fore.CYAN + f"Running test {input_file}..." + Style.RESET_ALL)

    if os.path.exists(input_path) and os.path.exists(expected_output_path):
        run_test(input_file, expected_output_file, input_path, expected_output_path)
    else:
        print(Fore.YELLOW + f"Test files missing for test case {test_num}." + Style.RESET_ALL)
        if not os.path.exists(input_path):
            print(Fore.YELLOW + f"Missing: {input_path}" + Style.RESET_ALL)
        if not os.path.exists(expected_output_path):
            print(Fore.YELLOW + f"Missing: {expected_output_path}" + Style.RESET_ALL)

def cleanup():
    """Cleans up any files created by the script."""
    # No compiled files for Python, but this is where you'd remove any temp files
    print(Fore.CYAN + "Cleanup complete. No files to remove." + Style.RESET_ALL)

def main():
    compile_program()
    run_tests()
    cleanup()

if __name__ == "__main__":
    main()

