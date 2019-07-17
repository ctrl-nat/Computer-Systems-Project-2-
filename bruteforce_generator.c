/* Brute force password generator
   Author: Natalie Kong (904997)
   Adapted and modified from
   
https://stackoverflow.com/questions/10159649/generate-all-letter-combinations

   To compile:
   gcc bruteforce_generator.c -o bruteforce_generator
   and run by directing output to a text file:
   bruteforce_generator > generated_passwords.txt

   */

#include <stdio.h>
#include <string.h>

/* set length of each generated password */
#define LEN 4

/* recursively iterates through each index of string */
/* assigns a character from 0 - z to that index */
void iterate(char *str, int idx, int len) {
  char c;
  if (idx < (len - 1)) {
    for (c = '0'; c <= 'z'; ++c) {
      str[idx] = c;
      iterate(str, idx + 1, len);
    }
  }
  else {
    for (c = 'A'; c <= 'z'; ++c) {
      str[idx] = c;
      printf("%s\n", str);
    }
  }
}


int main(int argc, char **argv) {
  char str[LEN + 1];
  memset(str, 0, LEN + 1);
  iterate(str, 0, LEN);
}

