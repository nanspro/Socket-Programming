#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define PORT 8082

int main(int argc, char const *argv[])
{
	int server_fd, new_socket;
	// sockaddr_in - references elements of the socket address. "in" for internet
	struct sockaddr_in address,client; 
	int addrlen = sizeof(address);

    // Creating socket file descriptor
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) 
    {
        perror("socket failed");
        return -1;
    }
    
    address.sin_family = AF_INET;  // Address family
    address.sin_addr.s_addr = INADDR_ANY; // Accept connections from any IP address - listens from all interfaces.
    address.sin_port = htons(PORT); // Server port to open. Htons converts to Big Endian - Left to Right. RTL is Little Endian

    // Forcefully attaching socket to the port 8080
    if (bind(server_fd, (struct sockaddr *)&address,sizeof(address))<0)
    {
        perror("bind failed");
        return -1;
    }
   
    // The process is two step: first you listen(), then you accept()    
    if (listen(server_fd, 5) < 0)
    {
        perror("listen error");
        return -1;
    }

    // returns a brand new socket file descriptor to use for this single accepted connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client,(socklen_t*)&addrlen))<0)
    {
        perror("acceptance error");
        return -1;
    }
	
	int len = 1;
	char str[100] = {0};
	while(len)	
	{
		char filename[1024] = {0};
		char data[1024] = {0};
		// receive the filename
		len = recv(new_socket,filename,1024,0);
		printf("%s\n",filename);
		if (len==-1)
		{
			perror("error receiving filename");
			continue;
		}
		char file[1000]="./Data/";
		strcat(file,filename);
		printf("%s\n",file);
		// access is used for searching the file in the current directory
		//if (access(file,F_OK)==-1)
		//{
		//	printf("\nFile doesn't exist\n");
		//	strcpy(str,"File doesn't exist");
		//}
		// send the message of file existence
		send(new_socket,str,sizeof(str),0);
		if (strcmp(str,"File doesn't exist")==0)
		{break;}
		FILE *fptr = fopen(file,"r");
		if (fptr==NULL)
		{
			printf("\nFile open error\n");
			continue;
		}
		// file has been opened and data is being sent in chunks of 1024 bytes
		while(fgets(data,1024,fptr))
		{
			send(new_socket,data,strlen(data),0);
		}
		fclose(fptr);
		break;
	}
	if (strcmp(str,"File doesn't exist")!=0)
	{printf("\nFile successfully sent\n");}
	close(new_socket);
	close(server_fd);
	return 0;
}
