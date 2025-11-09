# BSDSF23A018 - OS Assignment 03

## 🧠 Project Overview
This project is a simple shell program developed as part of the Operating Systems Assignment 03.  
It allows execution of external commands and supports essential built-in commands like `cd`, `help`, `exit`, and `jobs`.

---

## 📂 Project Structure
ROLL_NO-OS-A03/
├── src/
│ ├── main.c
│ ├── shell.c
│ └── execute.c
├── include/
│ └── shell.h
├── Makefile
└── README.md

---

## 🚀 Feature 1: The Base Shell (v1.0-base)
### Tasks Completed:
- Created GitHub repository: `BSDSF23A018-OS-A03`
- Added starter code from instructor’s repository.
- Built the project using `make` and verified shell execution with commands like:
  ```bash
  ls -l
  pwd
  whoami
feat: Initial project setup with base shell code

Created annotated tag v1.0-base
Published Release 1 - The Base Shell with the compiled binary bin/myshell.
⚙️ Feature 2: Built-in Commands (v2.0)
Concepts:

Process Model (Parent vs Child)

Built-in Commands

System Calls (chdir)

Git Branching, Tagging & Releases

Tasks Completed:

Created and switched to new branch feature-built-ins.

Implemented built-in commands:

cd <directory> → Change working directory.

help → Displays list of built-in commands.

exit → Exits the shell gracefully.

jobs → Placeholder for job control.

Modified main shell loop to check for built-in commands before forking.

Tested and verified all commands.

Committed code with message:

feat: Added built-in commands (cd, help, exit, jobs)


Merged branch into main.

Created annotated tag v2.0 and published Release 2 - Built-in Commands.

🧩 Built-in Commands Summary
Command	Description
cd <dir>	Change directory
help	Display help message
exit	Exit the shell
jobs	Placeholder for job control
🧑‍💻 Author

Name: Muhammad Noman Shamim
Roll No: BSDSF23A018
