
# Client-Server Application

## Description
This project is a client-server application implemented in C. The server application listens for incoming connections on a specified port and handles client requests. The client application connects to the server, sends requests, and receives responses.

## Technologies Used
- C
- POSIX threads (for handling concurrency)
- Sockets (for network communication)


### Prerequisites
- GCC (GNU Compiler Collection)
- Make utility


### How to Compile
To compile the server and client applications, use the following commands:
```bash
gcc -o server server.c
gcc -o client client.c
