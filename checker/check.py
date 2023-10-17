#! usr/bin/python3
import os
import subprocess

checker = 'bin/checker'


def run_solution(solution_path, input_file, output_file):
    with open(input_file, "r") as infile:
        with open(output_file, "w") as outfile:
            subprocess.run([solution_path], stdin=infile,
                           stdout=outfile, text=True)


def compare_outputs(output_file, expected_output_file):
    command = [checker, output_file, expected_output_file]
    result = -1
    try:
        result = subprocess.run(command, stdout=subprocess.PIPE,
                                stderr=subprocess.PIPE, text=True, check=True)
        return result.returncode == 0
    except:
        return False


test_folder = "tests/"
solve_folder = "bin/"
output_folder = "output/"

if not os.path.exists(output_folder):
    os.mkdir(output_folder)

test_files = [f for f in os.listdir(
    test_folder) if os.path.isfile(os.path.join(test_folder, f))]

solution_files = [f for f in os.listdir(
    solve_folder) if os.path.isfile(os.path.join(solve_folder, f))]

for test_file in test_files:
    if 'out' in test_file:
        continue
    test_input = os.path.join(test_folder, test_file)
    print(f"Testing {test_input}...")

    for solution_file in solution_files:
        if 'checker' in solution_file:
            continue
        solution_path = os.path.join(solve_folder, solution_file)
        output_file = os.path.join(
            output_folder, f"{solution_file}_{test_file}")
        with open(output_file, "a"):
            run_solution(solution_path, test_input, output_file)

        if compare_outputs(test_input, output_file):
            print(f"Solution {solution_file} PASSED")
        else:
            print(f"Solution {solution_file} FAILED, Output is not a coverage")

        # os.remove(output_file)
