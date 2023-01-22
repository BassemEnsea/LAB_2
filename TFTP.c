
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define PORT "1069"
const int BUF_SIZE = 1024;

int main(int argc,char* argv[]){
	
	//argv[1]=get/put tftp  argv[2]=host argv[3]=fichier
	char* host=argv[2];
	char* file=argv[3];
	int fileLen=strlen(file);
	
	//getinfo of the domain (host)
	int status;
	struct addrinfo hints;
	struct addrinfo *res;  // will point to the results
	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	int s=getaddrinfo(host,PORT, &hints, &res);
	if ( (s!=0)){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return EXIT_FAILURE;
	}
	
	//socket definition
	//struct sockaddr_in sockInterface;
	//socklen_t* addrlen;
	int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	
	//bind(sockfd,&sockInterface,addrlen);
	if (sockfd == -1) {
		perror("socket error");
		exit(1);
	}	

	
	//Creation of the packet (buffer)
	char buffer[BUF_SIZE];
	
	uint16_t Opcode=1;
	Opcode=htons(Opcode);
	char* Mode="octet";
	int modeLen=strlen(Mode);
	
	//Filling the packet
	*((short*)buffer)=Opcode;
	strcpy(&buffer[2],file);
	buffer[2+fileLen]=0;
	
	
	strcpy(&buffer[fileLen+3],Mode);
	buffer[fileLen+3+modeLen]=0;
	int buffer_len=4+modeLen+strlen(file);
	
	//Send packet(file) to host
	
	sendto(sockfd, buffer, buffer_len, 0,res->ai_addr,res->ai_addrlen ); // verify with if
	printf("request done\n");
	
	//Receive packet from the host
	char buffer_receive[BUF_SIZE];
	int len;
	  //Verify with if 
	struct sockaddr server_addr;
	int* server_addrlen;
	  
		
	if ((len=recvfrom(sockfd,&buffer_receive,BUF_SIZE,0,&server_addr,server_addrlen)) == -1){
		printf("Error reading data\n");
	}
	printf("%d\n",len);
	printf("%c",buffer_receive[100]);

	if (strcmp(argv[1],"gettftp")==0){
		//gettftp(host, file);
	}
	else if (strcmp(argv[1],"puttftp")==0){
		//puttftp(host, file);
	}
	else{
		printf("Invalid command\n");
	}
	
	return 0;
}

