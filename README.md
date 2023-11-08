# Client-Server File Transfer Program

This repository contains client and server programs for transferring files over a network using TCP/IP. The server program allows for file uploads and downloads, and the client program can be used to interact with the server for file transfer.

## Table of Contents

- [Introduction](#introduction)
- [Server Program](#server-program)
- [Client Program](#client-program)
- [Usage](#usage)
- [Authentication](#authentication)
- [License](#license)

## Introduction

This repository consists of two programs:
- **Server Program**: A server that listens for client connections and handles file uploads and downloads.
- **Client Program**: A client that can connect to the server to upload or download files.

## Server Program

The server program is written in C and provides the following features:
- Authentication based on a hardcoded username and password.
- List available files on the server.
- Allow clients to download files from the server.
- Receive files from clients and store them in a specific directory.

## Client Program

The client program is also written in C and provides the following features:
- Authentication to connect to the server.
- List available files on the client.
- Upload files to the server.
- Download files from the server.

## Usage

To use these programs, follow the instructions below:

### Server Program

1. Compile and run the server program on the machine where you want to host files.

2. Clients can connect to the server by providing a valid username and password.

3. Once authenticated, clients can list available files, select files for download, and upload files to the server.

### Client Program

1. Compile and run the client program on a machine where you want to upload or download files.

2. Connect to the server using the server's IP address and port.

3. Provide the username and password for authentication.

4. Choose whether to upload or download files based on your needs.

### Authentication

Both the server and client programs use hardcoded username and password for authentication. You can modify these values in the source code as needed.

**Server Authentication**:
- Default username: "user"
- Default password: "password"

**Client Authentication**:
- Username and password must match the server's authentication values.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

Feel free to use, modify, and adapt these programs for your own file transfer needs.

