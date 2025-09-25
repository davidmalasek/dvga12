# Exercise 3

This project is a simple vehicle registry management system written in C. It allows users to add, remove, sort, search, and display vehicles stored in a CSV file. The program validates user input, ensures the registry file exists, and provides colored feedback messages for success and error states.

**Usage**
Compile the project using the provided Makefile, then run the executable.
Follow the menu prompts to manage the vehicle registry.

# TODO

- [x] Free everything read_string() returns
- [x] Validate inputs and return error messages when needed
- [x] Don't let the user input diacritics
- [x] Limit amout of chars for each field
- [x] If registry.csv does not exist, program must create it
- [x] Define buffer (~ input limit) in header file
- [x] Correct the table view
- [x] Unite all error messages
- [x] Remove spaces before and after string
- [x] Let file related functions be in file.c, rest in utils.c
- [x] Seg fault when data in registry is not valid
- [x] Use only vehicle struct even for owner
