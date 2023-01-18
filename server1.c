#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<netdb.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
int main(){
	int sockfd, newsockfd, portno,n;
	struct sockaddr_in serv_addr, client_addr;
	char buffer[1024];
	socklen_t len;

	portno = 9002;
	sockfd = socket(AF_INET, SOCK_STREAM,0);
	//chekc socket creating
	if(sockfd<0){
		printf("error in socket creating");
		exit(1);
	
	}
	
	//build struct for socket
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(portno);
	//bind the socket to struct
	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
		printf("error in binding socket");
	listen(sockfd,5);
	len = sizeof(client_addr);
	
	newsockfd = accept(sockfd,(struct sockaddr * )&client_addr, &len);
	//chek if client sok connnected prop
	if(newsockfd <0){
		printf("error in accepting request");
		exit(1);
}
else{
		//read
		bzero(buffer,1024);
		n = read(newsockfd,buffer,1024);
		if(n<0){
			printf("error in reading");
			exit(1);
		}
		printf("\nClient --> %s",buffer);
		bzero(buffer,1024);
		//write
		write(newsockfd,"CHOOSE ANY OF THE OPTIONS BELOW\n1.OPEN A WEBPAGE\n2.OPEN AN APPLICATION\n",1024);
		//read
		n = read(newsockfd,buffer,1024);
		if(n<0){
			exit(1);}
		printf("\nClient --> %s",buffer);
		int opt = atoi(buffer);
		if(opt == 1){
			bzero(buffer,1024);
			printf("option 1");
			write(newsockfd,"ENTER WEBPAGE NAME\n",1024);
			n = read(newsockfd,buffer,1024);
			printf("\nClient --> %s",buffer);
			char url[] =" cmd.exe /C start http://";
			strcat(url,buffer);
			system(url);
			bzero(buffer,1024);}

		
		if(opt == 2){
			bzero(buffer,1024);
			write(newsockfd,"ENTER APPLICATION NAME \n",1024);
			n = read(newsockfd,buffer,1024);
			printf("\nClient --> %s",buffer);
			char dom[] = "cmd.exe /C ";
			strcat(dom,buffer);
			system(dom);
			bzero(buffer,1024);
		}


			
		if(!strncmp("bye",buffer,3)){
			exit(1);
		}
}

	close(newsockfd);
	close(sockfd);
	return 0;
	


}
