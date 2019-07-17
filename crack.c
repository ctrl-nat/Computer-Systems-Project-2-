/*
  COMP30023 Project 2
  Password cracker driver program
  Filename: crack.c
  Author: Natalie Kong (904997)
  */


#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "sha256.h"
#include "compute.h"
#define PW_SIZE 32
#define FILENAME "pwd6sha256"

int main(int argc, char *argv[]) {

    FILE *fp, *password_fp;

    char* filename = FILENAME;


    /* run crack with no arguments */
    if (argc == 1){
      password_fp = fopen("generated_passwords.txt", "r");
      fp = fopen((char*)filename, "rb");

      assert(password_fp);
      assert(fp);

      compute(password_fp, fp);

      fclose(fp);
      fclose(password_fp);
    }



  /* run crack with one argument */
  if (argc == 2){
    int wordcount = 0;
   
    /* good guesses are generated by comparing 6-character passwords of other  */
    /* students and observing a pattern in the passwords i.e. many passwords   */
    /* are a play on the capitalisation of the first alphabet (usually) or in  */
    /* other cases other parts of the word itself. Not more than one letter is */
    /* capitalised. Other observations include replacing letters that          */
    /* "resembled a number by the number itself. E.g. passw0rd                 */

    fp = fopen("good_guesses.txt", "r");

    /* specifies number of guesses to be printed */
    int count = atoi(argv[1])+1;

    char buffer[MAXLEN_GUESS];

    while((fgets(buffer, MAXLEN_GUESS, fp) != NULL && wordcount < count)) {

      /* prints only 6 character passwords */
      if(strlen(buffer) == GUESS_PW_LEN + 1){
        printf("%s", buffer);
        wordcount++;
      }
    }
    fclose(fp);
}



  /* run crack with two arguments */
  if (argc == 3){

    password_fp = fopen(argv[1], "r");
    fp = fopen(argv[2], "rb");

    assert(password_fp);
    assert(fp);

    compute(password_fp, fp);

    fclose(fp);
    fclose(password_fp);
  }

  return 0;
}
