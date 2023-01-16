
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>

const int BUF_SIZE = 1024;

int main(int argc,char* argv[]){
	
	
	
	//argv[1]=get/put tftp  argv[2]=host argv[3]=fichier
	char* host=argv[2];
	char* file=argv[3];
	
	//getinfo of the domain (host)
	int status;
	struct addrinfo hints;
	struct addrinfo *res;  // will point to the results

	memset(&hints, 0, sizeof hints); // make sure the struct is empty
	int s=getaddrinfo(host,"tftp", &hints, &res);
	if ( (s!=0)){
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
		return EXIT_FAILURE;
	}
	
	//socket definition
	char host_name[100], service[100];
	status = getnameinfo(res->ai_addr, res->ai_addrlen, host_name, sizeof(host_name), service, sizeof(service), NI_NUMERICHOST);
	int sockfd = socket(AF_INET,SOCK_DGRAM,IPPROTO_UDP);
	if (sockfd == -1) {
		perror("socket error");
		exit(1);
	}
	
	char Opcode[2]="01";
	char* zero="0";
	char* Mode="octet";
	int modeLen=strlen(Mode);

	
	
	
	char buffer[BUF_SIZE];
	strcat(buffer,"(((");
	strcat(buffer,file);
	strcat(buffer,zero);
	strcat(buffer,Mode);
	strcat(buffer,zero);
	int buffer_len=4+modeLen+strlen(file);
	printf("  buffer: %s\n ",buffer);
	
	sendto(sockfd, buffer, buffer_len, 0,res->ai_addr,res->ai_addrlen );
	
		

	printf("IP address: %s\n", host_name);
	
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

