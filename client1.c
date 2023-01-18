#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>

int main(){
	int sockfd, portno,n;
	struct sockaddr_in serv_addr;
	
	char buffer[1024];
	
	portno=9002;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	if(sockfd<0){
		printf("error in opening socket");
		exit(1);
	}

	//struct of serv addr
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port=htons(portno);
	serv_addr.sin_addr.s_addr = INADDR_ANY;

	//conect with socket
	if(connect(sockfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr))<0){
		printf("connection failed");}
	else{
		bzero(buffer,1024);
		//WRITE SOME DATA
		fgets(buffer,1024,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if(n<0){
			printf("error in writing");
			exit(1);
		}
		//now read back from server
		bzero(buffer,1024);
		n = read(sockfd,buffer,1024);
		if(n<0){
			printf("error in reading");
			exit(1);
		}

		//print server respone
		printf("\nServer --> %s", buffer);

		bzero(buffer,1024);
		fgets(buffer,1024,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		bzero(buffer,1024);

		//read
		n = read(sockfd,buffer,1024);
		if(n<0){
			printf("error in reading");
			exit(1);}
		printf("\nServer --> %s",buffer);
		bzero(buffer,1024);

		fgets(buffer,1024,stdin);
		n = write(sockfd,buffer,strlen(buffer));
		if(n<0){

			exit(1);}
		bzero(buffer,1024);
		if(!strncmp("bye", buffer,3)){
			exit(1);}
	}
	close(sockfd);
	return 0;
}
