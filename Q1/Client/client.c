#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#define PORT 8082

int main(int argc, char const *argv[])
{
	int sock = 0;
	struct sockaddr_in serv_addr;
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("\nSocket creation error\n");
		return -1;
	}
	// to make sure the struct is empty. Essentially sets sin_zero as 0
	// which is meant to be, and rest is defined below
	memset(&serv_addr, '0', sizeof(serv_addr));

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(PORT);
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	// connect to the server address
	if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) 
	{
		perror("\nConnection Failed \n");
		return -1;
	}

	char filename[1024],reply[1024],str[100];
	printf("\nEnter the file name to download from server: ");
	scanf("%s",filename);
	// send the filename to the server
	send(sock,filename,1024,0);
	// receive the message whether file exists or not
	recv(sock,str,sizeof(str),0);

	if (strcmp(str,"File doesn't exist")==0)
	{printf("\nFile doesn't exist\n");}
	else
	{
		int length=0;
		FILE *fptr = fopen(filename,"w+");
		memset(reply,0,sizeof(reply));
		// receive the data and write to the file
		while(length=recv(sock,reply,1024,0)>0)
		{
			fwrite(reply,1,strlen(reply),fptr);
			memset(reply,0,sizeof(reply));
			// if (length<=1024)
			// 	{break;}
		}
		fclose(fptr);
		printf("\nFile download completed\n");
	}
	close(sock);
	return 0;
}
