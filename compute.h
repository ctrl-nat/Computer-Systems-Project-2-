/* Filename:   compute.h
   Author:     Natalie Kong (904997)
   Details:    Defines the API for the corresponding testing against 
hashes. */

#include <stdio.h>
#include <memory.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include "sha256.h"

#define MAXLINE 10000
#define PW_SIZE 32
#define MAX_HASH_SIZE 640
#define GUESS_PW_LEN 6
#define MAXLEN_GUESS 128

/*********************** FUNCTION DECLARATIONS **********************/
void compute(FILE* password_fp, FILE* fp);

