# 🔧 pipex - Understanding Unix Pipes in C

Hey there! 👋 Welcome to my pipex project, where I recreated one of Unix's most powerful features - command piping! Let me walk you through this fascinating journey into the world of process handling and Unix pipes.

## 🎯 What's This Project About?

Ever used the `|` symbol in your terminal to pipe commands together? Like `cat file.txt | grep "hello"`? Well, I built a program that does exactly that, but from scratch! The goal was to:

- Recreate the behavior of the shell pipe operator (`|`)
- Handle input/output redirection (`<` and `>`)
- Execute shell commands with their arguments
- Manage multiple processes and their communication
- Handle various edge cases and errors gracefully

My program works like this:
```bash
./pipex file1 cmd1 cmd2 file2
# Which is equivalent to:
< file1 cmd1 | cmd2 > file2
```

## 🛠️ How I Built It

I broke down this project into several key components:

1. **Process Management**:
   - Used `fork()` to create child processes
   - Implemented both parent and child process handlers
   - Managed process synchronization using `wait()`

2. **Pipe Communication**:
   - Created pipes using the `pipe()` system call
   - Set up communication channels between processes
   - Handled file descriptors carefully to avoid leaks

3. **Command Execution**:
   - Parsed command arguments properly
   - Found executable paths in the system
   - Used `execve()` to run the commands
   - Handled command execution errors

4. **File Operations**:
   - Managed file opening and permissions
   - Handled input/output redirection
   - Dealt with file access errors

## 🤔 The Tricky Parts

This project had some interesting challenges:

1. **Process Synchronization**:
   - Making sure processes run in the right order
   - Handling pipe communication without deadlocks
   - Managing process exit statuses

2. **Memory Management**:
   - Avoiding memory leaks with multiple processes
   - Properly freeing allocated resources
   - Handling file descriptor cleanup

3. **Error Handling**:
   - Dealing with command not found errors
   - Managing file access permissions
   - Handling pipe creation failures
   - Graceful error reporting

## 🎓 What I Learned

This project was a goldmine of learning opportunities:

1. **Deep Unix Knowledge**:
   - Understanding process creation and management
   - Learning about file descriptors and redirection
   - Grasping how pipes work at a low level

2. **System Programming**:
   - Working with system calls
   - Managing multiple processes
   - Handling inter-process communication

3. **Better Error Handling**:
   - Implementing robust error checking
   - Creating informative error messages
   - Graceful program termination

### 📝 Speaking of Error Handling...

My implementation includes robust error handling for:
- Invalid number of arguments
- File access errors
- Command not found
- Pipe creation failures
- Fork failures
- Execution errors

## 💡 How to Use It

```bash
# Compile the program
make

# Basic usage
./pipex infile "ls -l" "wc -l" outfile

# This will:
# 1. Read from infile
# 2. Run ls -l on its contents
# 3. Pipe the result to wc -l
# 4. Save the final output to outfile
```

## 🔍 Final Thoughts

This project really opened my eyes to how Unix systems work under the hood. It's amazing to see how fundamental concepts like pipes and processes come together to create powerful command-line functionality.

The skills I learned here - especially about process management and system calls - have been invaluable for understanding how modern operating systems work. Plus, it's pretty cool to build something that mimics such a fundamental Unix feature! 🚀

---
*Built with ❤️ and lots of coffee at 42 School*
