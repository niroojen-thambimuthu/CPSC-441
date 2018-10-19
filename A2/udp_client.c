
/*
 
 udp_client.c 
 
 This program will have a command line input text
 argument and it will request the server(udp_server.c)
 if it exists or not. It will receive acknowledgement
 and receive file size if text file. Using file size, 
 it will determine the amount of total octolegs, and
 will have a receiving loop for the amount of octolegs.
 Using the concatenated data, it will print into a text 
 file within the client directory.
 
 Author: Niroojen Thambimuthu (10153928) using ta codes
 */

#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#define PORT 8001
int main(int argc, char *argv[]) {
	const char* server_name = "localhost";//loopback
	const int server_port = PORT;

	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	// creates binary representation of server name
	// and stores it as sin_addr
	//inet_pton: convert IPv4 and IPv6 addresses from text to binary form

	inet_pton(AF_INET, server_name, &server_address.sin_addr);
	
	
	server_address.sin_port = htons(server_port);

	// open socket
	int sock;
	if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		printf("could not create socket\n");
		return 1;
	}
	printf("client socket created\n\n\n\n");
    
	// input data meant for text file
    const char* data_to_send = argv[1];
    char filename[30];
    strcpy(filename, argv[1]);
    printf("The entered filename is: %s\n", filename);
    
    // send data request to server
    int len =
    sendto(sock, data_to_send, strlen(data_to_send), 0,
           (struct sockaddr*)&server_address, sizeof(server_address));
    printf("Text File request has been sent to server\n");
    // received data request from server
    char buffer[100];
    int recv_bytes=recvfrom(sock, buffer, sizeof(buffer), 0, NULL, NULL);
    buffer[recv_bytes] = '\0';
    //printf("received bytes = %d\n",recv_bytes);
    printf("Message received from server: %s\n", buffer);
    
    char *tempIF;
    tempIF = strstr(buffer, ".txt");
    
    // If input is a text file
    if (tempIF != NULL){
        printf("\n\tThis is a text file\n");
        /*const char* Request = "Hi Server!!!";
        
        // send data
        int len =
        sendto(sock, Request, strlen(Request), 0,
               (struct sockaddr*)&server_address, sizeof(server_address));
        printf("message has been sent to server\n");
        */
        // Receive filesize from server
        char fileSize[250];
        int recv_bytes_RE=recvfrom(sock, fileSize, sizeof(fileSize), 0, NULL, NULL);
        //printf("received bytes = %d\n",recv_bytes_RE);
        buffer[recv_bytes_RE] = '\0';
        printf("\nFile size is: %s\n", fileSize);
        
        int octo = 0;
        int pOcto = 0;
        int mOcto = 0;
        
        // put file size into block
        int block = atoi(fileSize);
        //int block = 27478;
        
        int start = 0;
        
        // This part will sort the total amount of octo blocks
        printf("\n\nInitial block length %d\n\n", block);
        while (block > 0){
            // Full octoblocks legs
            if (block/8888 != 0){
                octo = block/8888;
                block = block - (octo*8888);
                //Loop which sends the octo blocks
            }
            // Partial octoblocks legs
            else if(block/8 != 0){
                pOcto = block/8;
                block = block%8;
                //Loop whih sends the partial blocks
            }
            // Micro octoblocks leg
            else if(block%8 !=0){
                mOcto = block;
                block = block - mOcto;
                //Loop which sends the micro blocks
            }
            else{
                printf("Error");
            }
        }
        printf("Octo bytes %d = 8888*%d\n", octo*8888, octo);
        printf("\tOcto bytes leg set %d\n\n", octo);
        //printf("Octo bytes per leg %d\n\n", 1111);
        printf("Partial octo bytes %d = 8*%d\n", pOcto*8, pOcto);
        printf("\tPartial octo bytes per leg %d\n\n", pOcto);
        printf("Micro octo bytes %d\n\n", mOcto);
        printf("Final block length%d\n", block);
        
        int totalLegs = 0;
        // This part will determine the total amount of octo blocks
        if(octo > 0){
            totalLegs = totalLegs + 8*octo;
        }
        if(pOcto > 0){
            totalLegs = totalLegs + 8;
        }
        if(mOcto > 0){
            totalLegs = totalLegs + 8;
        }
        
        printf("Total legs %d\n", totalLegs);

        /*for (int i = 4; i > 0; i--){
            // receive echoed data back
            char responseTrial[100];
            int recv_bytes_trial = recvfrom(sock, responseTrial, sizeof(responseTrial), 0, NULL, NULL);
            printf("Size of response,in bytes, from the server = %d bytes\n",recv_bytes_trial);
            responseTrial[recv_bytes_trial] = '\0';
            printf("Response from server: '%s'\n", responseTrial);
        }
         */
        
        //char totalEnd[atoi(fileSize)];
        char totalEnd[300000] = {'\0'};


        printf("Received file:");
        // For loop which will receive and concatenate the received individual legs into totalend
        for (int i = totalLegs; i > 0; i--){
        // receive echoed data back
        char responseBufferT[5000];
        int recv_bytesT = recvfrom(sock, responseBufferT, sizeof(responseBufferT), 0, NULL, NULL);
        printf("\n\n\n\nSize of response,in bytes, from the server = %d bytes\n",recv_bytesT);
        //responseBufferT[recv_bytesT] = '\0';
        printf("Response from server: \n%s\n", responseBufferT);
        //printf("%s", responseBufferT);
        strcat(totalEnd, responseBufferT);
       // sprintf(totalEnd, "%s", responseBufferT);
        //memcpy(totalEnd, responseBufferT, strlen(responseBufferT));
            //sprintf(totalEnd,"%s",responseBufferT);
            //sprintf(totalTemp, totalEnd);
            
        }
        printf("\nReceived file: \n%s\n", totalEnd);
        //Coding which will print the concatenated data into a text file within the client directory
        
        FILE *f_output;
        f_output = fopen(argv[1], "wb");
        //if(f_output == NULL)
          //  return;
        
        fwrite(totalEnd, sizeof(totalEnd[0]), sizeof(totalEnd)/sizeof(totalEnd[0]), f_output);
        fclose(f_output);
         
        
    }
    // If input is not a text file
    else{
        printf("\n\tThis is not a text file\n\n\n\n");
    }
    
	// close the socket
	close(sock);
	return 0;
}

