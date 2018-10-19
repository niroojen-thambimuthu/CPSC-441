/*
 * Proxy.c
 *  This program is a Basic HTTP proxy which receives the HTTP Requests from the web browser
 *  and forward it to the desired web server. After receiving the response from the web server
 *  it forward it to the web browser of the client.
 *  The proxy listens on port 8001
 *  Created on: Jan 23, 2018
 */

/* Standard libraries */
#include <stdio.h>
#include <stdlib.h>

/* Libraries for socket programming */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

/* Library for parsing strings */
#include <string.h>
#include <strings.h>

/* h_addr?! */
#include <netdb.h>

/* Clean exit! */
#include <signal.h>

int lstn_sock;

/* The function will run after catching Ctrl+c in terminal */
void catcher(int sig) {
    close(lstn_sock);
    printf("catcher with signal  %d\n", sig);
    exit(0);
    
}

int main() {
    printf("\n\n\tSloxy: A Slow web Proxy\n\n");
    
    /* For catching Crtl+c in terminal */
    signal(SIGINT, catcher);
    int lstn_port = 8001;
    
    /* Initializing the Address */
    struct sockaddr_in addr_proxy;
    addr_proxy.sin_family = AF_INET;
    addr_proxy.sin_addr.s_addr = htonl(INADDR_ANY);
    addr_proxy.sin_port = htons(lstn_port);
    printf("Address Initialization: done.\n");
    
    /* Creating the listening socket for proxy */
    lstn_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (lstn_sock < 0) {
        printf("Error in socket() call.\n");
        exit(-1);
    } else {
        printf("Listening Socket creation: done.\n");
    }
    
    /* Binding the socket to address and port */
    int bind_status;
    bind_status = bind(lstn_sock, (struct sockaddr *) &addr_proxy,
                       sizeof(struct sockaddr_in));
    if (bind_status < 0) {
        printf("Error in bind() call.\n");
        exit(-1);
    } else {
        printf("Binding: done.\n");
    }
    
    /* Listening on binded port number */
    int lstn_status;
    lstn_status = listen(lstn_sock, 10);
    if (lstn_status < 0) {
        printf("Error in listen() call.\n");
        exit(-1);
    }
    /* Infinite while loop for listening accepting connection requests */
    while (1) {
        /* Accepting connection requests */
        int data_sock;
        data_sock = accept(lstn_sock, NULL, NULL);
        if (data_sock < 0) {
            printf("Error in accept() call");
            exit(-1);
        } else {
            printf("Accepting connection request: done.\n");
        }
        
        /* Receiving HTTP message from the client */
        char c_message_in[1024];
        char s_message_out[1024];
        int c_recv_status;
        c_recv_status = recv(data_sock, c_message_in, sizeof(c_message_in), 0);
        if (c_recv_status < 0) {
            printf("Error in recv() call for client recv message\n");
            exit(-1);
        } else {
            printf("\n\n############################################\n");
            printf("## HTTP message received from the client. ##\n");
            printf("############################################\n");
        }
        printf("\n\n\t\tGET REQUEST\n");
        printf("\nReceived GET Request: \n%s", c_message_in);
        /* Preserving the HTTP request for sending it to the web server later */
        strcpy(s_message_out, c_message_in);
        
        /* Parsing the HTTP message to extract the HOST name of the desired web server */
        char host[1024];
        char URL[1024];
        char PATH[1024];
        int i;

        // find and parse the GET request, isolating the URL for later use
        char *pathname = strtok(c_message_in, "\r\n");
        printf("Found HTTP request: %s\n", pathname);
        if (sscanf(pathname, "GET http://%s", URL) == 1)
            printf("URL = %s\n", URL);
        
        // seperate the hostname from the pathname
        for (i = 0; i < strlen(URL); i++) {
            if (URL[i] == '/') {
                strncpy(host, URL, i); //copy out the hostname
                host[i] = '\0';
                break;
            }
        }
        
        bzero(PATH, 500); //to clear junk at the beginning of this buffer. don't know why its there
        for (; i < strlen(URL); i++) {
            strcat(PATH, &URL[i]); //copy out the path
            break;
        }
        printf("******************************\n");
        printf("First Half(host): %s\n", host); //firstHalf is the hostname
        printf("Second Half(path): %s\n", PATH); //secondHalf is the path
        printf("******************************\n");
        
        /* Creating the TCP socket for connecting to the desired web server */
        // Address initialization
        struct sockaddr_in addr_server;
        struct hostent *server;
        
        // Getting web server's Address by its host name
        server = gethostbyname(host);
        if (server == NULL)
            printf("Error in gethostbyname() call.\n");
        else
            printf("Web server = %s\n", server->h_name);
            printf("\n\n");
        
        // Initialize socket structure
        bzero((char *) &addr_server, sizeof(addr_server));
        addr_server.sin_family = AF_INET;
        bcopy((char *) server->h_addr, (char *) &addr_server.sin_addr.s_addr, server->h_length);
        addr_server.sin_port = htons(80);

        
        /*
         *			HEAD REQUEST
         *
         *  This section will find whether a file is an html,
         *  while also finding the length.
         * 
         */
        printf("\n\n\t\tHEAD REQUEST\n\n");
        
        // Creating the socket for head request
        int head_web_sock = socket(AF_INET, SOCK_STREAM, 0);
        if (head_web_sock < 0) {
            printf(
                   "Error in socket() call for creating --proxy-WebServer-- socket.\n");
        } else {
            printf("###############################################\n");
            printf("## --proxy-WebServer-- socket creation: done ##\n");
            printf("###############################################\n");
        }
        
        // Connecting to the web server's socket
        int connect_status;
        connect_status = connect(head_web_sock, (struct sockaddr *) &addr_server,sizeof(addr_server));
        if (connect_status < 0) {
            printf(
                   "Error in connect() call for connecting to the web server's socket.\n");
            exit(-1);
        } else {
            printf("Web server's socket connection establishment: done\n ");
        }
        
        // Create head request
        char http_head_request[100000];
        snprintf(http_head_request, sizeof(http_head_request), "HEAD http://%s HTTP/1.1\r\nHost: %s\r\n\r\n",URL,host);
        printf("%s", http_head_request);
        
        //Sending head request to server
        int head_send_status;
        char head_response[100000];
        bzero(head_response, sizeof(head_response));
        head_send_status = send(head_web_sock, http_head_request, sizeof(http_head_request),0);
        printf("head_send_status is: %d\n", head_send_status);
        if (head_send_status < 0) {
            printf(
                   " Error in send() call for sending HTTP request to the web server.\n ");
            exit(-1);
        } else {
            printf("##############################################\n");
            printf("## Sending HTTP request to the server: done ##\n");
            printf("##############################################\n");
        }
        
        // Receiving head request from the web server
        int head_recv_status;
        char tempResult [100000];
        head_recv_status = recv(head_web_sock, head_response, sizeof(head_response), 0);
        printf("\head_recv_status is: %d\n\n",head_recv_status);
        if (head_recv_status < 0) {
            printf(
                    " Error in recv() call for receiving web server's HTTP response.\n ");
            exit(-1);
        } else {
            printf("################################################\n");
            printf("## Receiving web server's HTTP response: done ##\n");
            printf("################################################\n");
        }
        strcpy(tempResult, head_response);
        printf("Received head response from the web server: \n%s\n",head_response);
        
        
        
        /*
         *			Html files
         *
         *  This section will determine if the requested content
         * 	should be restricted to be painfully slow.
         *
         */
        int loopTemp;
        char *content = "NULL";
        char html_content;
        char *concatenation = "NULL";
        char range_request[100000];
        char length[1024];
        content = strstr(head_response, "Content-Type: ");
        sscanf(content, "Content-Type: %s", &html_content);
        if(strcmp(&html_content, "text/html;") == 0){
            printf("\n\n\tTHIS IS AN HTML FILE, MAKE IT SLOW \n\n");
            char *contentLength = "\0";
            int loop = 0;
            contentLength = strstr(head_response, "Content-Length: ");
            sscanf(contentLength, "Content-Length: %s", length);
            printf("%s\n",length);
            loopTemp = atoi(length);
            // looping for html file length
            while (loop <= loopTemp){
                //Create the socket
                int html_web_sock = socket(AF_INET, SOCK_STREAM, 0);
                if (html_web_sock < 0) {
                    printf(
                           "Error in socket() call for creating --proxy-WebServer-- socket.\n");
                } else {
                    printf("###############################################\n");
                    printf("## --proxy-WebServer-- socket creation: done ##\n");
                    printf("###############################################\n");
                }
                
                // Connecting to the web server's socket
                int html_connect_status;
                html_connect_status = connect(html_web_sock, (struct sockaddr *) &addr_server,
                                         sizeof(addr_server));
                if (html_connect_status < 0) {
                    printf(
                           "Error in connect() call for connecting to the web server's socket.\n");
                    exit(-1);
                } else {
                    printf("Web server's socket connection establishment: done\n ");
                }
                
                //Create The range request
                snprintf(range_request, sizeof(range_request), "GET http://%s HTTP/1.1\r\nHost: %s\r\nRange: bytes=%d-%d\r\n\r\n",URL,host,loop,(loop+100));
                printf("\nThis range request is: %s\n",range_request);
                loop = loop +101;
                
                //Sending the range request of the client to the server
                int range_send_status;
                char range_request_temp[100000];
                bzero(range_request_temp, sizeof(range_request_temp));
                range_send_status = send(html_web_sock, range_request, sizeof(range_request), 0);
                printf("range_recv_status is: %d\n",range_send_status);
                if (range_send_status < 0) {
                    printf(
                           " Error in send() call for sending HTTP request to the web server.\n ");
                    exit(-1);
                } else {
                    printf("##############################################\n");
                    printf("## Sending HTTP request to the server: done ##\n");
                    printf("##############################################\n");
                }
                
                //Receiving the range request response from the web server
                int range_recv_status;
                range_recv_status = recv(html_web_sock, range_request_temp, sizeof(range_request_temp), 0);
                printf("\n\range_recv_status is %d\n\n", range_recv_status);
                if (range_recv_status < 0) {
                    printf(
                           " Error in recv() call for receiving web server's HTTP response.\n ");
                    exit(-1);
                } else {
                    printf("################################################\n");
                    printf("## Receiving web server's HTTP response: done ##\n");
                    printf("################################################\n");
                }
                printf("\n\nRange request response from server is: \n%s\n\n", range_request_temp);
                
                // put together the all seperate ranges into one, not working
                concatenation = strstr(range_request_temp, "\r\n\r\n");
                strcat(tempResult, concatenation);
                close(html_web_sock);
            }
            printf("\nThe HTML file is: \n%s\n",tempResult);
            // almost identical to the second half of the proxy.c file
            // Creating the socket
            int web_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (web_sock < 0) {
                printf(
                       "Error in socket() call for creating --proxy-WebServer-- socket.\n");
            } else {
                printf("###############################################\n");
                printf("## --proxy-WebServer-- socket creation: done ##\n");
                printf("###############################################\n");
            }
            
            // Connecting to the web server's socket
            int connect_status;
            connect_status = connect(web_sock, (struct sockaddr *) &addr_server,
                                       sizeof(addr_server));
            if (connect_status < 0) {
                printf(
                       "Error in connect() call for connecting to the web server's socket.\n");
                exit(-1);
            } else {
                printf("Web server's socket connection establishment: done\n ");
            }
            
            /* Sending the HTTP request of the client to the web server */
            int web_send_status;
            web_send_status = send(web_sock, s_message_out, sizeof(c_message_in),0);
            if (web_send_status < 0) {
                printf(
                       " Error in send() call for sending HTTP request to the web server.\n ");
                exit(-1);
            } else {
                printf("##############################################\n");
                printf("## Sending HTTP request to the server: done ##\n");
                printf("##############################################\n");
            }
            
            /* Receiving the HTTP response from the web server */
            char w_message_in[100000];
            bzero(w_message_in, sizeof(w_message_in));
            
            int web_recv_status;
            web_recv_status = recv(web_sock, w_message_in, sizeof(w_message_in), 0);
            if (web_recv_status < 0) {
                printf(
                       " Error in recv() call for receiving web server's HTTP response.\n ");
                exit(-1);
            } else {
                printf("################################################\n");
                printf("## Receiving web server's HTTP response: done ##\n");
                printf("################################################\n");
            }
            
            printf("\n\nReceived HTTP response from the web server:\n%s",w_message_in);
            printf("\n\n\n");
            
            /* Closing the socket connection with the web server */
            close(web_sock);
            close(head_web_sock);
            
            
            /* Sending the HTTP response to the client */
            int c_send_status;
            c_send_status = send(data_sock, w_message_in, sizeof(w_message_in), 0);
            if (c_send_status < 0) {
                printf(
                       "Error in send() call for sending HTTP response to the client.\n");
                exit(-1);
            } else {
                printf("###############################################\n");
                printf("## Sending HTTP response to the client: done ##\n");
                printf("###############################################\n");
            }
            
            /* Closing the socket connection with the client */
            close(data_sock);
            printf("\n\n\tdata socket is closed.\n\n\n\n");
        }
        /*
         *			NON HTML files
         *
         *  This section will determine if the requested content
         * 	should be treated normally, or anything else that isn't
         *  a html file.
         * 
         */
        else{
            printf("\n\n\tTHIS IS NOT AN HTML FILE, TREATED NORMALLY \n\n");
            // almost identical to the second half of the proxy.c file
            // Creating the socket
            int web_sock = socket(AF_INET, SOCK_STREAM, 0);
            if (web_sock < 0) {
                printf(
                       "Error in socket() call for creating --proxy-WebServer-- socket.\n");
            } else {
                printf("###############################################\n");
                printf("## --proxy-WebServer-- socket creation: done ##\n");
                printf("###############################################\n");
            }
            
            // Connecting to the web server's socket
            int connect_status;
            connect_status = connect(web_sock, (struct sockaddr *) &addr_server,
                                       sizeof(addr_server));
            if (connect_status < 0) {
                printf(
                       "Error in connect() call for connecting to the web server's socket.\n");
                exit(-1);
            } else {
                printf("Web server's socket connection establishment: done\n ");
            }
            
            /* Sending the HTTP request of the client to the web server */
            int web_send_status;
            web_send_status = send(web_sock, s_message_out, sizeof(c_message_in),0);
            if (web_send_status < 0) {
                printf(
                       " Error in send() call for sending HTTP request to the web server.\n ");
                exit(-1);
            } else {
                printf("##############################################\n");
                printf("## Sending HTTP request to the server: done ##\n");
                printf("##############################################\n");
            }
            
            /* Receiving the HTTP response from the web server */
            char w_message_in[100000];
            bzero(w_message_in, sizeof(w_message_in));
            
            int web_recv_status;
            web_recv_status = recv(web_sock, w_message_in, sizeof(w_message_in), 0);
            if (web_recv_status < 0) {
                printf(
                       " Error in recv() call for receiving web server's HTTP response.\n ");
                exit(-1);
            } else {
                printf("################################################\n");
                printf("## Receiving web server's HTTP response: done ##\n");
                printf("################################################\n");
            }
            
            printf("\n\nReceived HTTP response from the web server:\n%s",w_message_in);
            printf("\n\n\n");
            
            /* Closing the socket connection with the web server */
            close(web_sock);
            close(head_web_sock);///////////////////////////////////////////////////////////
            
            /* Sending the HTTP response to the client */
            int c_send_status;
            c_send_status = send(data_sock, w_message_in, sizeof(w_message_in), 0);
            if (c_send_status < 0) {
                printf(
                       "Error in send() call for sending HTTP response to the client.\n");
                exit(-1);
            } else {
                printf("###############################################\n");
                printf("## Sending HTTP response to the client: done ##\n");
                printf("###############################################\n");
            }
            
            /* Closing the socket connection with the client */
            close(data_sock);
            printf("\n\n\tdata socket is closed.\n\n\n\n");
        }
    }
    close(lstn_sock);
    printf("lstn_sock is closed.\n");
    return 0;
}
