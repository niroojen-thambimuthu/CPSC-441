/*
 
 udp_server.c
 
 This program will run indefinitely and wait for a text file request
 from the client. If it doesn't exist, send message. Else, send 
 exist message and file size to client. Read txt file, split up into
 octoleg sizes and send individually to the client. It will then wait
 for next text file request.
 
 Author: Niroojen Thambimuthu (10153928) using ta codes
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#define PORT 8001
int main(int argc, char *argv[]) {
	// port to start the server on
	int SERVER_PORT = PORT;

	// socket address used for the server
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	// htons: host to network short: transforms a value in host byte
	// ordering format to a short value in network byte ordering format
	server_address.sin_port = htons(SERVER_PORT);

	// htons: host to network long: same as htons but to long
	server_address.sin_addr.s_addr = htonl(INADDR_ANY);

	// create a UDP socket, creation returns -1 on failure
	int sock;
	if ((sock = socket(PF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("could not create socket\n");
		return 1;
	}
	printf("server socket created\n");
	// bind it to listen to the incoming connections on the created server
	// address, will return -1 on error
	if ((bind(sock, (struct sockaddr *)&server_address,
	          sizeof(server_address))) < 0) {
		printf("could not bind socket\n");
		return 1;
	}
	printf("binding was successful\n");
	// socket address used to store client address
	struct sockaddr_in client_address;
	int client_address_len = sizeof(client_address);
        char client_name[100];
    printf("\n\nWaiting");
	// run indefinitely
	while (true) {
        printf("\n********************\n");
		char buffer[500];

		// received client text file input
		int len = recvfrom(sock, buffer, sizeof(buffer), 0,
		                   (struct sockaddr *)&client_address,
		                   &client_address_len);
		
		// inet_ntoa prints user friendly representation of the
		// ip address
		buffer[len] = '\0';
		printf("received: '%s' from client %s on port %d\n", buffer,
		       inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
        
        //printf("\n\n%s\n\n", buffer);
        FILE *file;
        file = fopen(buffer, "r");
        
        // If the received input is valid
        if(file){
            printf("This file exist\n");
            // send back txt file for acknowledgement purposes
            int sent_len = sendto(sock, buffer, len, 0, (struct sockaddr *)&client_address,
                                  client_address_len);
            //printf("server sent back message:%d\n",sent_len);
            
            /*// read content into buffer from an incoming client
            int octoRe = recvfrom(sock, buffer, sizeof(buffer), 0,
                               (struct sockaddr *)&client_address,
                               &client_address_len);
            
            // inet_ntoa prints user friendly representation of the
            // ip address
            buffer[octoRe] = '\0';
            printf("received: '%s' from client %s on port %d\n", buffer,
                   inet_ntoa(client_address.sin_addr),ntohs(client_address.sin_port));
            */
            int sizeFile=0;
            
            // Seek the last byte of the file
            fseek(file, 0, SEEK_END);
            // Offset from the first to the last byte, or in other words, filesize
            sizeFile = ftell(file);
            // go back to the start of the file
            rewind(file);
            //printf("File size:\n %d \n",sizeFile);
            //char* Check = "OKOKOKOKOKOKOK";
            //char* Check = (char)sizeFile;
            char* Check;
            Check = malloc(16);
            snprintf(Check, 16, "%d", sizeFile);
            // send sizefile to client
            int sent_len2 = sendto(sock, Check, strlen(Check), 0, (struct sockaddr *)&client_address,
                                  client_address_len);
            //printf("server sent back message:%d\n",sent_len2);
            printf("Send back file size of: %d\n", sizeFile);
            
            // coding which starts reading the file
            int read_size;
            rewind(file);
            char buff[sizeFile];
            read_size = fread(buff, 1, sizeof(buff), file);
            if (sizeFile != read_size)
            {
                // Something went wrong, throw away the memory and set
                // the buffer to NULL
                free(buff);
            }
            else
            {
                //printf("\nFile content: \n%s\n",buff);
                int octo = 0;
                int pOcto = 0;
                int mOcto = 0;
                
                int block = sizeFile;
                //int block = 27478;
                
                char sendToClient[sizeFile+1];
                int counter = 0;
                
                
                // This part will sort the total amount of octo blocks
                // and will split to octoleg sizes and send to client
                printf("\n\nInitial block length %d\n\n", block);
                while (block > 0){
                    if (block/8888 != 0){
                        // Full octoblocks legs
                        octo = block/8888;
                        printf("Sets of 8888 octablocks: %d\n", octo);
                        int legTemp = 1111;
                        sendToClient[legTemp] = '\0';
                        
                        // if there are multiple full octoblock sets
                        int help = octo*8;
                        printf("\n\n\nTest: %d\n\n\n\n", help);

                        // for loops which sends incremented leg bytes to client
                        for (int j = 0; j < help; j++) {
                            // partial octolegs
                            printf("\nPartial Octa #: %d\n", j+1);
                            //data = (dataBuffer + (octaLeg * j));
                            strncpy(sendToClient, buff + (legTemp * j), legTemp);
                            
                            printf("Send this data to client is: \n%s\n\n", sendToClient);
                            
                            
                            //send the individual octoleg
                            int sent_len_trial = sendto(sock, sendToClient, strlen(sendToClient), 0, (struct sockaddr *)&client_address,client_address_len);
                            
                            // test purposes
                            block -= legTemp;
                            counter += legTemp;
                            printf("Counter size: %d\n\n", counter);
                        }
                        printf("\nlast block size is is: \n%d", block);
                    }
                    else if(block/8 != 0){
                        // Partial octoblocks legs
                        pOcto = block/8;
                        //block = block%8;
                        printf("\nPartial Octa bytes is: %d\n", block);
                        printf("Each Octaleg will contain: %d bytes\n", pOcto);
                        
                        sendToClient[pOcto] = '\0';
                        
                        // for loops which sends incremented leg bytes to client
                        for (int j = 0; j < 8; j++) {
                            
                            // partial octolegs
                            printf("\nPartial Octa #: %d\n", j+1);
                            //data = (dataBuffer + (octaLeg * j));
                            strncpy(sendToClient, buff + (pOcto * j), pOcto);
                            
                            printf("Send this data to client is: \n%s\n\n", sendToClient);
                            
                            
                            // send the individual octoleg
                            int sent_len_trial = sendto(sock, sendToClient, strlen(sendToClient), 0, (struct sockaddr *)&client_address,client_address_len);
                            
                            // test purposes
                            block -= pOcto;
                            counter += pOcto;
                            printf("Counter size: %d\n\n", counter);
                        }
                        printf("\nlast block size is is: \n%d", block);

                    }
                    else if(block%8 !=0){
                        // Micro octoblocks leg
                        mOcto = block;
                        printf("\nMicro octa bytes is: %d\n", mOcto);
                        sendToClient[mOcto] = '\0';
                        int small = 8 - mOcto;
                        //block = block - mOcto;
                        //Loop which sends the micro blocks
                        // for loops which sends incremented leg bytes to client
                        for (int j = 0; j < 8; j++) {
                            if(j < mOcto){
                                // micro octolegs
                                printf("\nMicro Octa #: %d\n", j+1);
                                //data = (dataBuffer + (octaLeg * j));
                                strncpy(sendToClient, buff + (mOcto * j), mOcto);
                                
                                printf("Send this data to client is: \n%s\n\n", sendToClient);
                                
                                
                                // send the individual octoleg
                                int sent_len_trial = sendto(sock, sendToClient, strlen(sendToClient), 0, (struct sockaddr *)&client_address,client_address_len);
                                
                                // test purposes
                                block -= mOcto;
                                counter += mOcto;
                                printf("Counter size: %d\n\n", counter);
                            }
                            else{
                                // micro octolegs
                                printf("\nMicro Octa #: %d\n", j+1);
                                
                                //send blank data to client
                                strncpy(sendToClient, " ", 1);
                                
                                printf("Send this data to client is: \n%s\n\n", sendToClient);
                                
                                // send the individual octoleg
                                int sent_len_trial = sendto(sock, sendToClient, strlen(sendToClient), 0, (struct sockaddr *)&client_address,client_address_len);
                               
                                // test purposes
                                block -= mOcto;
                                counter += mOcto;
                                printf("Counter size: %d\n\n", counter);
                            }
                        }
                        printf("\nlast block size is is: \n%d", block);
                    }
                    else{
                        //Error precaution
                        printf("Error");
                    }
                }
                printf("Octo bytes %d = 8888*%d\n", octo*8888, octo);
                printf("\tOcto bytes leg set = %d\n\n", octo);
                //printf("Octo bytes per leg %d\n\n", 1111);
                printf("Partial octo bytes %d = 8*%d\n", pOcto*8, pOcto);
                printf("\tPartial octo bytes per leg = %d\n\n", pOcto);
                printf("Micro octo bytes = %d\n\n", mOcto);
                printf("Final block length = %d \n", block);
            }

        }
        // If the file doesn't exist in the server directory, send not a text file message
        else
        {
            printf("No such file exist\n");
            char Error[500] = "Not a text file";
            // send back message to client
            int sent_len = sendto(sock, Error, strlen(Error), 0, (struct sockaddr *)&client_address,
                                  client_address_len);
            //printf("server sent back message:%d\n",sent_len);
        }
        printf("\n********************\n\n\n\n\n\n\n");
        printf("\n\nWaiting");


	}
	close(sock);
	return 0;
}
