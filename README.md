
# C Client-Server Application

## Description
This project is a simple client-server application written in C that utilizes Windows named pipes for inter-process communication. The server application creates a named pipe and listens for client connections. The client sends data to the server, which is then read and displayed.

## Technologies Used
- C
- Windows API (Named Pipes)

## Installation

### Prerequisites
- A Windows operating system
- GCC compiler (MinGW) or Microsoft Visual Studio

### Setup Instructions
1. Clone the repository:
    ```bash
    git clone <repository-url>
    cd <repository-directory>
    ```

2. Build the project:
    ```bash
    gcc -o server server.c
    gcc -o client client.c
    ```

## Usage

### How to Compile
To compile the server and client applications, use the following commands:
```bash
gcc -o server server.c
gcc -o client client.c
