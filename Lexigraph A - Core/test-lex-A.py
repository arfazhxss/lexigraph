import subprocess
import os
from colorama import init, Fore, Style

# Initialize colorama
init()

def compile_program():
    print(Fore.CYAN + "Compiling the program..." + Style.RESET_ALL)
    result = subprocess.run(['gcc', '-o', 'lexig-core-exc', 'lexig-core.c'], capture_output=True, text=True)
    if result.returncode == 0:
        print(Fore.GREEN + "Compilation successful." + Style.RESET_ALL)
    else:
        print(Fore.RED + "Compilation failed." + Style.RESET_ALL)
        print(result.stderr)
        exit(1)

def run_test(input_file, expected_output_file, input_path, expected_output_path):
    # Run the program with input redirection
    try:
        with open(input_path) as f:
            input_data = f.read()
    except FileNotFoundError:
        print(Fore.YELLOW + f"Input file {input_path} not found." + Style.RESET_ALL)
        return
    
    result = subprocess.run(['./lexig-core-exc'], input=input_data, text=True, capture_output=True)
    
    # Read expected output
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

def cleanup():
    """Remove the compiled executable."""
    if os.path.exists('lexig-core-exc'):
        os.remove('lexig-core-exc')
        print(Fore.CYAN + "Cleaned up the compiled executable." + Style.RESET_ALL)
    else:
        print(Fore.YELLOW + "No compiled executable to clean up." + Style.RESET_ALL)

def main():
    # Compile the program first
    compile_program()

    # Define the number of test cases
    num_tests = 10

    # Iterate through test cases
    for i in range(1, num_tests + 1):
        input_file = f'in{i:02}.txt'  # Generates in01.txt, in02.txt, etc.
        expected_output_file = f'out{i:02}.txt'  # Generates out01.txt, out02.txt, etc.
        
        # Construct the paths for input and expected output files in the tests directory
        input_path = os.path.join('tests', input_file)
        expected_output_path = os.path.join('tests', expected_output_file)
        
        # Print paths being checked
        print(Fore.CYAN + f"Checking {input_file} (input path: {input_path}) and {expected_output_file} (output path: {expected_output_path})..." + Style.RESET_ALL)

        # Check if the files exist
        if os.path.exists(input_path) and os.path.exists(expected_output_path):
            run_test(input_file, expected_output_file, input_path, expected_output_path)
        else:
            print(Fore.YELLOW + f"Test files for test case {i} are missing." + Style.RESET_ALL)
            if not os.path.exists(input_path):
                print(Fore.YELLOW + f"File {input_path} does not exist." + Style.RESET_ALL)
            if not os.path.exists(expected_output_path):
                print(Fore.YELLOW + f"File {expected_output_path} does not exist." + Style.RESET_ALL)

    # Cleanup
    cleanup()

if __name__ == "__main__":
    main()
