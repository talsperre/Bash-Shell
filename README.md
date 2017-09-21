# C Shell
Implementation of a C based bash shell using system calls

## Getting Started
To run the shell, write:
```
make
```
Followed by:
```
./shell
```
## Features
- Comma separated commands can be given as input. For e.g. echo hello ; ls -al will produce hello then the contents of the current directory.
- Bonus
  - If background process exits then it displays the appropriate message to the user
  - Command nightswatch (_Now my watch begins_) implemented - dirty version is completed.
- Modularized code
  - Uses makefile for compilation process
  - All header files and declarations in header.h
- Proper error handling whenever required
- Uniform coding style (Variable names, brackets styling)
- Supports signal handling (eg. Ctrl-C returns Caught signal 2)
  - ```Ctrl-C``` returns ```Caught signal 2, exiting```
- Properly documented
- Unit tests for certain functions

## Authors
- **S. Shashank (20161103)**
- **Kanay Gupta (20161098)**

## License
This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details
