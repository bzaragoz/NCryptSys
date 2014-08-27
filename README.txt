-----
ABOUT
-----
This program does NOT do decryption; it only encrypts.
There are five steps to the encryption process:
	1) Preprocessing
	2) Substitution (via Vignere cipher)
	3) Padding
	4) Row-Shifting
	5) Even-bit parity
	** Column-Shifting would be the 6th step to implement

An "output.txt" file will be generated that breaks down the encryption
and returns the resulting value at each step of the process.


------------ 
INSTRUCTIONS
------------
Compile the C++ file to create an executable (.exe) that runs with two arguments:
(1) input text file; (2) input key file.


--------
EXAMPLES
--------
./hw3 test_files/input_file_1 test_files/key_file_1

./hw3 test_files/input_file_2 test_files/key_file_2

./hw3 test_files/input_file_3 test_files/key_file_3

