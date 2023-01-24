#include "functions.h"


#define ERROR_MSG "Usage : %s host:port file \n Please try again... \n"

#define port "1069"
//because we need 2 bytes for the uploading code+ 2 bytes for the block id
//and 512 bytes for the data. 
//Buffersize=516

int main (int Numb_Arg,char * Arg_Vector[]){
	struct addrinfo hints;
	struct addrinfo *result;
	char *serverName;
	char RRQ[516];

	struct sockaddr sock_addr;
	
	
	//point 1 checks if the arguments passed to the command line of the program. 
	if (Numb_Arg != 3) {
		printf("not enough arguments");
		printf(ERROR_MSG, Arg_Vector[0]);
		exit(EXIT_FAILURE);
	}
	
	//Data reception
	serverName = strtok(Arg_Vector[1], ":");
	
	
	printf("Try on server : %s on port %s\n", serverName, port);
	
	//call getaddrinfo to get the server address
	memset(&hints,0,sizeof(struct addrinfo));
	printf("\nRaised");
	hints.ai_family=AF_INET;//IPv4 addresses
	hints.ai_socktype=SOCK_DGRAM;//UDP socket Types
	hints.ai_protocol=IPPROTO_UDP;//make sure is UDP protocols
	printf("\nValues Ready");
	
	
	//connection to the socket
	int Sock,Sock2,Call,size,SendSize,RecvSize;
	
	Call=getaddrinfo(Arg_Vector[1],port,&hints,&result);
	if (Call != 0){//checking if the call went wrong
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(Call));
        exit(EXIT_FAILURE);
    }
	
	printf("\ngetaddrinfo= %d",Call);
	printf("\ngetaddrinfo test\n");
	Sock=socket(result->ai_family,result->ai_socktype,result->ai_protocol);
	if(Sock==-1){
		perror("Erro in connection in Socket");
		exit(EXIT_FAILURE);
	}
	printf("socket= %d",Sock);
	printf("\nsocket test\n");
	
	//building a RRQ packet with the filename.
	
	
	RRQ[0]=0;
	RRQ[1]=1;
	printf("Opening the buffer\n");

	strcpy(&RRQ[2],Arg_Vector[2]);
	strcpy(&RRQ[2 + strlen(Arg_Vector[2]) +1],"Byte");
	printf("\nargument copied\n");
	size= (int)(2+strlen(Arg_Vector[2])+1+4+1);
	printf("Setting the size\n");
	printf("Current Buffer");
	printf(RRQ);
	
	// Sending the RRQ 
	SendSize = sendto(Sock,RRQ,size,0,result->ai_addr,result->ai_addrlen);
	if(SendSize<0){
		perror("Error in connection in Sendto");
		exit(EXIT_FAILURE);
	}
	
	//receiving the DATA 
	socklen_t addrsize;
	RecvSize = recvfrom(Sock,RRQ, 516, 0, &sock_addr, &addrsize);
	printf("recvfrom= %d\n",RecvSize);
	if(RecvSize == -1){
		perror("error while recvfrom: \n");
	}
	printf("buffer= %d %d %d %c %c %c %c\n", RRQ[1],RRQ[2],RRQ[3],RRQ[4],RRQ[5],RRQ[6],RRQ[7]);
	
	//from here
//	char *buf = calloc(BUFFER_SIZE, sizeof(char));
	if (RecvSize == -1){
		printf("Server not found \n"); 
		exit (EXIT_FAILURE); 
	}
	
	

	RRQ[0]=0;
	RRQ[1]=4;
	RRQ[4]=0;
	Sock2=sendto(Sock,RRQ,4,0,result->ai_addr,result->ai_addrlen);
	printf("ACK= %d",Sock2);
	printf("\n");
}
