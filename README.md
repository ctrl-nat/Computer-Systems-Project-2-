# Computer-Systems-Project-2-

This repository contains Assignment 2 for COMP30023 Computer Systems Semester 1 2019. The aim of the project was to crack passwords, ourselves with SHA256 hashing algorithm, the Diffie-Hellman key exchange protocol as well as what makes a good/ bad passwords and analysing them.

# Files
crack.c - main driver program

sha256.c/sha256.h - program for computing the SHA256 hashes, adapted from Brad Conte (URL provided in inline comments)

compute.c/compute.h - program to compare each line of password guesses with the corresponding hash file

bruteforce_generator.c - program I used to implement brute-force generation of a dictionary, which produced output I redirected into a .txt file, generated_passwords.txt. I then ran the .txt file through my crack.c program to discover passwords. 

The generated_passwords.txt file cannot be uploaded to git as the file size is too big, however can be generated simply by compiling
```gcc bruteforce_generator.c -o bruteforce_generator```
and then directing the output to another .txt file when you run it
```bruteforce_generator > generated_passwords.txt'.```

dh.c - program for the Diffie-Hellman key exchange to obtain pwd6sha256 file from the server

good_guesses.txt - text file containing good guesses for crack with 1 arg

dictionary .txt files I used for a dictionary attack to crack my passwords

common_passwords.txt (https://gitlab.eng.unimelb.edu.au/junhaog/comp30023-labcode-current/blob/master/proj-2/common_passwords.txt)

10kmilpw.txt (https://github.com/danielmiessler/SecLists/blob/master/Passwords/xato-net-10-million-passwords-1000000.txt)

however files exceeded 1MB and could not be included
