# 🔧 pipex - Understanding Unix Pipes in C

Hey there! 👋 Welcome to my pipex project, where I recreated one of Unix's most powerful features - command piping!

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

Developing pipex revealed several fundamental challenges in Unix process management and inter-process communication.

### Process Synchronization
The cornerstone challenge was ensuring reliable process coordination. Each command in the pipe chain needed to execute in the correct sequence, with data flowing smoothly between processes. I implemented careful synchronization mechanisms to prevent deadlocks while maintaining proper process execution order. My solution monitors process exit statuses to ensure reliable operation and proper error propagation through the pipe chain.

### Resource Management
Managing resources across multiple processes demanded meticulous attention to detail. Each process required careful tracking of its memory allocations and file descriptors. I developed a comprehensive cleanup system that prevents memory leaks by properly deallocating resources, even in error conditions. Special attention was paid to file descriptor management, ensuring proper closure in both parent and child processes.

### Error Handling and Recovery
Robust error management proved crucial for system reliability. My implementation handles various failure scenarios gracefully, from missing commands to permission issues. The error handling system provides clear, actionable feedback while ensuring proper cleanup of system resources. This comprehensive approach maintains system stability even when encountering unexpected conditions.

## 🎓 What I learned 

This project provided deep insights into Unix system internals and process management.

### Unix System Architecture
Implementing pipex deepened my understanding of Unix's process model. I gained practical experience with process creation, management, and inter-process communication through pipes. This hands-on work revealed the elegant simplicity of Unix's file descriptor system and how it enables powerful data flow between processes.

### System Programming Fundamentals
The project required mastery of essential system calls and process management techniques. Working directly with fork(), pipe(), and execve() provided practical experience in low-level system programming. I learned to manage complex process hierarchies while maintaining data integrity throughout the execution chain.

### Robust Error Management
Developing comprehensive error handling proved essential for reliable operation. I implemented systematic error checking at each critical point, from command validation to resource allocation. The resulting system gracefully handles edge cases while providing meaningful feedback, ensuring a stable and user-friendly experience.

### 📝 Speaking of Error Management...

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
