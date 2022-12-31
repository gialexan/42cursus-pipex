# Pipex
This project consists of reproducing the behavior of the [shell pipe](https://www.geeksforgeeks.org/piping-in-unix-or-linux/).

### What is pipex?
Pipex is an individual project at [42](https://www.42sp.org.br/) that requires us to create a program that simulates the behavior of the [shell pipe](https://www.geeksforgeeks.org/piping-in-unix-or-linux/). To build the program it is necessary to create child processes using [fork()](https://www.geeksforgeeks.org/fork-system-call/) communicating with the parent process through [pipe()](https://www.geeksforgeeks.org/pipe-system-call/), manipulate the environment variable testing if the command exists or has execution permission, print errors to [STDERR] when necessary, returning the correct [status code](https://www.geeksforgeeks.org/exit-codes-in-c-c-with-examples/).

#### Badge
<img src="pipexm.png" width="150" height="150"/>

#### Objectives
- Unix logic

#### Skills
- Unix
- Imperative programming

#### My grade
<img src="score.png" width="150" height="150"/>

## Getting started
**Follow the steps below**
```bash
# Clone the project and access the folder
git clone https://github.com/gialexan/pipex-42 && cd pipex-42/
# Create a file to use in program input
echo "wwwwwwwxxxxxxxyyyyyyyyyzzzzzzz" > infile
# Run make so you can build the library
make
# Run the program like the example:
./pipex infile "ls -l" "wc -l" outfile
# Check the output file
cat outfile
# Run Make with bonus if number of input arguments is greater than five
make bonus
# Run the program like the example:
./pipex_bonus infile "tr x X" "tr y Y" "tr z Z" "tr w W" outfile
# Check the output file
cat outfile
# Clean output objects with
make fclean
# Well done!
```