/* Filename:   compute.c
   Author:     Natalie Kong (904997)
   Adapted from Brad Conte:
   https://github.com/B-Con/crypto-algorithms/blob/master/sha256_test.c
   https://github.com/B-Con/crypto-algorithms/blob/master/sha256.c

   Details:    Implementation of the testing program against two hashes.
              If a match is found, returns password that matched the hash
              and the index number of that hash as given in pwd4sha256/
              pwd6sha256 files.
*/


#include "compute.h"

void compute(FILE* password_fp, FILE* fp){
  unsigned char hash_arr[MAX_HASH_SIZE];

  char line[MAXLINE+1];
  BYTE buf[PW_SIZE];
  SHA256_CTX ctx;
  int read = 0;
  char *token;


  /* reads each line of password file */
  while (fgets(line, MAXLINE+1, password_fp)!=NULL){

    /* keeps track of which hash is being compared (from pwd file) */
    int hash_number = 0;

    /* tokenise string containing newline */
    /* so we don't pass newline characters into the hash function */
    token = strtok(line, ",\n\r");

    /* compute hash of each line */
    sha256_init(&ctx);
    sha256_update(&ctx, (BYTE*) token, strlen(token));
    sha256_final(&ctx, buf);

    /* reads each group of 32 bytes from hash file */
    while((read = fread(hash_arr, PW_SIZE, 1, fp)) > 0) {
      hash_number++;
      
      /* compare with hashes from pwd file */
      if (memcmp(hash_arr, buf, PW_SIZE) == 0) {
        printf("%s %d\n", token, hash_number);
        }
      }

      /* move file pointer back to beginning */
      rewind(fp);
  }
}

