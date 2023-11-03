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

1. Compile and run the server program on the machine
