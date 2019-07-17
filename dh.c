/* A client program for Diffie-Hellman key exchange.

   To compile: gcc dh.c -o dh
   and run: ./dh <server> <b value - the first two digits of this 
program hashed by SHA-256
   then converted to decimal>

	 Author: Natalie Kong
	 Student ID: 904997
	 Adapted from client.c code (Lab 5) */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>

#define PORT_NUMBER 7800
#define BUF_SIZE 256
#define ARR_SIZE 10
#define G_VALUE 15
#define P_VALUE 97

/* Function to convert int to char string */
char* convert_to_int(int b)
{
    char *a;
    int counter = 1, temp = b;

    /* get number of digits */
    while (temp > 0)
    {
        temp /= 10;
        counter++;
    }

   /* allocate the memory */
    a = (char *)malloc(counter+1);

    /* convert to string */
    sprintf(a, "%d", b);


    return a;
}


/* Function to compute (g ^ b) mod p */
int compute_exp_modulo(int g, int b, int p) {
	long long x = 1, y = g;
	while (b > 0) {
		if (b % 2 == 1)
			x = (x * y) % p;
		y = (y * y) % p;
		b /= 2;
	}
	return (int)(x % p);
}


int main(int argc, char ** argv)
{
    int sockfd, n;
    int portno = PORT_NUMBER;
    struct sockaddr_in serv_addr;
    struct hostent * server;

    char buffer[BUF_SIZE];
    int g = G_VALUE;
    int p = P_VALUE;

    if (argc < 2)
    {
        fprintf(stderr, "usage %s hostname b\n", argv[0]);
        exit(0);
    }


    /* Translate host name into peer's IP address ;
     * This is name translation service by the operating system
     */
    server = gethostbyname("172.26.37.44");

    if (server == NULL)
    {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }

    /* Building data structures for socket */

    bzero((char *)&serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy(server->h_addr_list[0], (char *)&serv_addr.sin_addr.s_addr,
server->h_length);

    serv_addr.sin_port = htons(portno);

    /* converts b passed in from command line to int for computation */
    int b = atoi(argv[1]);
    int gb_modp = compute_exp_modulo(g, b, p);

    /* Create TCP socket -- active open
    * Preliminary steps: Setup: creation of active open socket
    */

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
    {
        perror("ERROR opening socket");
        exit(0);
    }

    if (connect(sockfd, (struct sockaddr *)&serv_addr,
sizeof(serv_addr)) < 0)
    {
        perror("ERROR connecting");
        exit(0);
    }

    /* Do processing
    */

    /* Send username, newline and gb_mod p value and newline */

		while(1){
		bzero(buffer, BUF_SIZE);
		char val[ARR_SIZE];

		/* add username to buffer */
		strcpy(buffer, "nkong1\n");

		/* convert g^b mod p to text and add to buffer */
		strcpy(val, convert_to_int(gb_modp));
		strcat(buffer, val);

		/* add newline to buffer */
		strcat(buffer, "\n");

		/* sends whole buffer */
		n = write(sockfd, buffer, strlen(buffer));

    if (n < 0){
      perror("ERROR writing to socket");
      exit(0);
    }

		bzero(buffer, BUF_SIZE);

		n = read(sockfd, buffer, BUF_SIZE);

    if (n < 0){
      perror("ERROR reading from socket");
      exit(0);
    }

		printf("ga_modp: %s\n", buffer);
		printf("gb_modp: %d\n", gb_modp);

		int ga_modp = atoi(buffer);

		/* compute shared secret g^ab mod p */
		int secret = compute_exp_modulo(ga_modp, b, p);
		char temp[ARR_SIZE];

		printf("Shared secret key is %d\n", secret);

		/* add shared secret and newline character to buffer */
		bzero(buffer, BUF_SIZE);
		strcpy(temp, convert_to_int(secret));
		strcat(buffer, temp);
		strcat(buffer, "\n");

		/* send whole buffer */
		n = write(sockfd, buffer, strlen(buffer));

    if (n < 0){
      perror("ERROR writing to socket");
      exit(0);
    }

}

    close(sockfd);
    return 0;
}

