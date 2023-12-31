SERVER PROGRAM

/*cat final_cn_ftp_server.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>
#define SIZE 1024

void send_file1(int sockfd, const char *filename) {
    int n;
    FILE *fp;
    char buffer[SIZE];

    fp = fopen(filename, "rb"); // Open file in binary mode
    if (fp == NULL) {
        printf("[-]Error in reading file.");
        return;
    }
    while (1) {
        n = fread(buffer, 1, SIZE, fp);
        if (n <= 0) {
            break;
        }

        send(sockfd, buffer, n, 0);
        bzero(buffer, SIZE);
    }

    fclose(fp);
}
void receive_file2(int sockfd, const char *filename) {
    int n;
    char data[SIZE];
    FILE *fp = fopen(filename, "wb");
    if (fp == NULL) {
        printf("[-]Error in creating file.");
        exit(1);
    }
    while (1) {
        n = recv(sockfd, data, SIZE, 0);
        if (n <= 0) {
            break;
        }
        fwrite(data, 1, n, fp);
    }

    fclose(fp);
}
int main(){       
	int kal;
        printf("\n enter your choise for send ( 1 ) or recive ( 2 ) file : ");
        scanf("%d",&kal);
        if (kal == 1){
	 char *ip = "127.0.0.1";

	 int port = 8080;
	 int e;
	 int sockfd, new_sock;	
	 struct sockaddr_in server_addr, new_addr;
	 socklen_t addr_size;
	 char buffer[SIZE];
	 char storedUsername[] = "user";   // Hardcoded username
	 char storedPassword[] = "password"; // Hardcoded password
	 char directory[] = "./files/"; // Path to the directory with your files
	 char availableFiles[SIZE] = ""; // Initialize an empty string
	 DIR *dir;
	 struct dirent *ent;
	 dir = opendir("./files");
	 if (dir != NULL) {
 	 while ((ent = readdir(dir)) != NULL) {
	 if (ent->d_type == DT_REG) {
  		strcat(availableFiles, ent->d_name);
                strcat(availableFiles, "\n");
           }
    }
 closedir(dir);
} else {
     printf("[-]Error opening directory");
     // Handle the error if needed
 }
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd < 0) {
 printf("[-]Error in socket");
 exit(1);
 }

printf("[+]Server socket created successfully.\n");
server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
 server_addr.sin_addr.s_addr = inet_addr(ip);
e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (e < 0) {
 printf("[-]Error in bind");
  exit(1);
 }                       
 printf("[+]Binding successful.\n");
if (listen(sockfd, 10) == 0) {
printf("[+]Listening....\n");
} else {
 printf("[-]Error in listening");
  exit(1);
 }
ddr_size = sizeof(new_addr);
 new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
 // Authentication
 char username[50];
 char password[50];
 recv(new_sock, username, sizeof(username), 0);
recv(new_sock, password, sizeof(password), 0);
if (strcmp(username, storedUsername) == 0 && strcmp(password, storedPassword) == 0) 
{
   printf("[+]Authentication successful.\n");
// Send the list of available files to the client
send(new_sock, availableFiles, strlen(availableFiles), 0);
char selected_file[50];
recv(new_sock, selected_file, sizeof(selected_file), 0);

 // Write the selected file to the client
char full_file_path[256];
snprintf(full_file_path, sizeof(full_file_path), "%s%s", directory, selected_file);
send_file1(new_sock, full_file_path);
int totalBytes = 400,uploadedBytes = 0,progressBarWidth = 50;
int uploadSpeed = totalBytes / 8;
while (uploadedBytes < totalBytes) {
   uploadedBytes += uploadSpeed;
     if (uploadedBytes > totalBytes) {uploadedBytes = totalBytes;}
       int percentage = (uploadedBytes * 100) / totalBytes;
       int progress = (uploadedBytes * progressBarWidth) / totalBytes;
        printf("Progress: [%3d%%] [", percentage);
        for (int i = 0; i < progressBarWidth; i++) {if (i < progress) {printf("=");}
         else {printf(" ");}}
           printf("]\r");fflush(stdout);usleep(1000000);}
           printf("\n");
           printf("[+]Data written in the file successfully.\n");
           } else {
            printf("[-]Authentication failed. Closing the connection.\n");
          }
           close(new_sock);
           close(sockfd);
}
else if(kal == 2)       
{
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;
 int sockfd;
 struct sockaddr_in server_addr;

 sockfd = socket(AF_INET, SOCK_STREAM, 0);
 if (sockfd < 0) {
     printf("[-]Error in socket");
     exit(1);
 }
  printf("[+]Server socket created successfully.\n");
 server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);
 e = bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
 if (e < 0) {
   printf("[-]Error in bind");
   exit(1);
}
 printf("[+]Binding successful.\n");
if (listen(sockfd, 10) == 0) {
 printf("[+]Listening....\n");
}
else
{
   printf("[-]Error in listening");
   exit(1);
}
socklen_t addr_size;
struct sockaddr_in new_addr;
 addr_size = sizeof(new_addr);
int new_sock = accept(sockfd, (struct sockaddr *)&new_addr, &addr_size);
// Authentication (modify as needed)
char username[50];
char password[50];

recv(new_sock, username, sizeof(username), 0);
recv(new_sock, password, sizeof(password), 0);
if (strcmp(username, "user") == 0 && strcmp(password, "password") == 0)
{
  printf("[+]Authentication successful.\n");
char selected_file[50];
 recv(new_sock, selected_file, sizeof(selected_file), 0);
// Save the received file to the 'files' directory
 char savePath[256];
 snprintf(savePath, sizeof(savePath), "./files/%s", selected_file);
receive_file2(new_sock, savePath);
 int totalBytes = 400,uploadedBytes = 0,progressBarWidth = 50;
int uploadSpeed = totalBytes / 8;
while (uploadedBytes < totalBytes) {
    uploadedBytes += uploadSpeed;
     if (uploadedBytes > totalBytes) {uploadedBytes = totalBytes;}
     int percentage = (uploadedBytes * 100) / totalBytes;
     int progress = (uploadedBytes * progressBarWidth) / totalBytes;
     printf("Progress: [%3d%%] [", percentage);
     for (int i = 0; i < progressBarWidth; i++) {if (i < progress) {printf("=");}
       else {printf(" ");}}
           printf("]\r");fflush(stdout);usleep(1000000);}
           printf("\n");
	   printf("[+]File received and saved successfully.\n");
 }
 else
  {
    printf("[-]Authentication failed. Closing the connection.\n");
}
 close(new_sock);

close(sockfd);
}
else
{
  printf("\n invalid choice");
}
 return 0;
}
