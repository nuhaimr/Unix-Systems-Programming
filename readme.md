# PipeSimulator - README

## Overview

PipeSimulator is a C-based program that simulates the functionality of a Unix pipe command. It allows users to execute and process commands through an input file, outputting results based on the operations performed. The program uses custom data structures (like linked lists) to manage commands and interactions between components, providing an efficient and functional simulation of a piped execution environment.

---

## Features

1. **Unix Pipe Simulation**: Processes multiple commands connected through pipes, simulating Unix-style operations.
2. **Linked List Management**: Implements a linked list to manage commands and their inputs/outputs.
3. **Modular Codebase**:
   - `LinkedList.c` and `LinkedList.h`: Implements the linked list functionality.
   - `PipeSimulator.c` and `PipeSimulator.h`: Contains the main logic for command simulation.
   - `TestHarness.c`: A test utility to validate functionality.
4. **Makefile for Compilation**: Simplifies the process of compiling the program.

---

## File Structure

- **Core Files**:
  - `PipeSimulator.c`: Main implementation of the pipe simulator.
  - `PipeSimulator.h`: Header file for the pipe simulator.
  - `LinkedList.c`: Implementation of linked list operations.
  - `LinkedList.h`: Header file for the linked list implementation.
- **Testing**:
  - `TestHarness.c`: Contains tests for validating functionality.
- **Build System**:
  - `makefile`: Build script for compiling the program.
- **Sample Input/Output**:
  - `sampletext1.txt`: Sample input file for testing.
  - `sampletext2.txt`: Additional input file for testing.
  - `text.txt`: Example input for demonstration purposes.
- **Documentation**:
  - `readme.md`: This README file for documentation.

---

## Compilation and Execution

### Prerequisites

- GCC (GNU Compiler Collection) or equivalent C compiler installed on your system.

### Compilation

To compile the program, use the provided `makefile`. Run the following command in the terminal:

```bash
make
```

This will generate the executable file for the program.

### Execution

Run the program using the command:

```bash
./pipesim <input_file>
```

- Replace `<input_file>` with the name of your input text file containing the commands to be processed.
- The output will be written to separate files depending on the number of commands in the input.

### Example

To run the simulation with `sampletext1.txt`:

```bash
./pipesim sampletext1.txt
```

---

## Input and Output

### Input

The input file should contain Unix-style commands, each separated by a newline or pipe (`|`).

**Example Input (sampletext1.txt):**

```bash
cat file1.txt | grep "example" | sort
```

### Output

The program generates output files for each piped command and combines results appropriately. The number of output files corresponds to the number of commands processed.

---

## Cleaning Up

To clean the compiled files and reset the directory:

```bash
make clean
```

---

## Testing

Use the `TestHarness.c` file to run automated tests:

1. Compile the test harness:
   ```bash
   gcc -o test TestHarness.c LinkedList.c PipeSimulator.c
   ```
2. Execute the tests:
   ```bash
   ./test
   ```

---

## Notes

- **Command-Line Interface**: Ensure that commands in the input file are formatted correctly to avoid runtime errors.
- **Modular Design**: The modular structure makes it easy to extend or modify components.
- **Error Handling**: Basic error handling is included for invalid inputs and command failures.

---

## Support

For issues or inquiries, contact the project maintainer or refer to the source code for further details.

---

*Happy Simulating!*
