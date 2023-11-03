
/*cat cn_ftp_client.c*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <dirent.h>
#define SIZE 1024

void receive_file1(int sockfd, const char *filename) {
    int n;
    char data[SIZE];

    FILE *fp = fopen(filename, "wb"); // Open file in binary write mode
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
void send_file2(int sockfd, const char *filename) {
    int n;
    char data[SIZE];
    FILE *fp = fopen(filename, "rb");

    if (fp == NULL) {
        printf("[-]Error in opening file.");
        exit(1);
    }
    while (1) {
        n = fread(data, 1, SIZE, fp);
        if (n <= 0) {
            break;
        }
        send(sockfd, data, n, 0);
    }

    fclose(fp);
}
int main()
{
 int sal;
 printf("\n enter your choise for uplode( 2 ) or downlode( 1 ) file : ");
 scanf("%d",&sal);
 if (sal == 1)
 {
   char *ip = "127.0.0.1";
    int port = 8080;
    int e;
    int sockfd;
    struct sockaddr_in server_addr;
    char username[50];
    char password[50];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        printf("[-]Error in socket");
        exit(1);
    }
     printf("[+]Client socket created successfully.\n");

server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);

e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (e == -1)
{
 printf("[-]Error in connection");
 exit(1);
 }
 printf("[+]Connected to Server.\n");
printf("[+]Enter the userID: ");
scanf("%s", username);
send(sockfd, username, sizeof(username), 0);
printf("[+]Enter the userpass: ");
scanf("%s", password);
send(sockfd, password, sizeof(password), 0);
char file_list[SIZE];
recv(sockfd, file_list, SIZE, 0);
printf("[+]Available files:\n%s\n", file_list);
char selected_file[50];
printf("Enter the filename you want to copy: ");
scanf("%s", selected_file);
send(sockfd, selected_file, sizeof(selected_file), 0);
int rows = 8,columns = 9,delay = 25000;
for (int i = 0; i < rows; i++) {
 for (int j = 0; j < columns; j++) {
if(i==0){if(j==8 || j==7 || j==6){continue;
}
else if (i==0 && j==4){
	printf("^ ");fflush(stdout);usleep(delay);j++;}}
        else if(i==1){if( j==7 || j==6){continue;
	}
	else if (i==1 && j==4){printf("^ ");fflush(stdout);usleep(delay);j++;
}}
else if(i==2 ){if(j==6)
{
	continue;
}
else if (i==2 && j==4)
{
printf("^ ");fflush(stdout);usleep(delay);j++;
}}
else if(i==3 ){if (i==3 && j==4){printf("^ ");
fflush(stdout);usleep(delay);j++;
}}
printf("# ");fflush(stdout);usleep(delay);
}
printf("\n");
 }
printf("\n");

int totalBytes = 400,uploadedBytes = 0,progressBarWidth = 50;
int uploadSpeed = totalBytes / 8;
while (uploadedBytes < totalBytes) {
	uploadedBytes += uploadSpeed;
	if (uploadedBytes > totalBytes) 
	{
	uploadedBytes = totalBytes;
	}
	int percentage = (uploadedBytes * 100) / totalBytes;
	int progress = (uploadedBytes * progressBarWidth) / totalBytes;
	printf("Progress: [%3d%%] [", percentage);
	for (int i = 0; i < progressBarWidth; i++) 
	{
	if (i < progress) 
	{
	printf("=");
	}
	else {printf(" ");}}
	printf("]\r");fflush(stdout);usleep(1000000);}
	printf("\n");
	printf("[+]Receiving file...\n");
	receive_file1(sockfd, selected_file);
	printf("[+]FILE DATA DOWNLODED! SUCCESSFULLY.\n");
	close(sockfd);
        }
	else if(sal == 2)
        {
	char *ip = "127.0.0.1";
	int port = 8080;
	int e;
	int sockfd;
	struct sockaddr_in server_addr;
	char username[50];
	char password[50];

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0) {
	printf("[-]Error in socket");
	exit(1);
}
printf("[+]Client socket created successfully.\n");

server_addr.sin_family = AF_INET;
server_addr.sin_port = port;
server_addr.sin_addr.s_addr = inet_addr(ip);

e = connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));
if (e == -1) {
printf("[-]Error in connection");
exit(1);
}
printf("[+]Connected to Server.\n");

printf("[+]Enter the userID: ");
scanf("%s", username);
send(sockfd, username, sizeof(username), 0);

printf("[+]Enter the userpass: ");
scanf("%s", password);
send(sockfd, password, sizeof(password), 0);

// List files in the files_client directory
DIR *dir;
struct dirent *ent;
char clientFiles[SIZE] = "";

dir = opendir("./files_client"); // Change the path to your client directory
if (dir != NULL) {
while ((ent = readdir(dir)) != NULL) {
if (ent->d_type == DT_REG) {
	strcat(clientFiles, ent->d_name);
	strcat(clientFiles, "\n");
}}
closedir(dir);
}

printf("[+]Available files on the client:\n%s\n", clientFiles);

char selected_file[50];
printf("Enter the filename you want to upload: ");
scanf("%s", selected_file);
send(sockfd, selected_file, sizeof(selected_file), 0);
char uploadPath[256];
snprintf(uploadPath, sizeof(uploadPath), "./files_client/%s", selected_file);

// Check if the selected file exists on the client
FILE *upload_fp = fopen(uploadPath, "rb");
if (upload_fp == NULL) {
printf("[-]Selected file does not exist on the client. Exiting.\n");
close(sockfd);
return 1;
}
fclose(upload_fp);
int rows = 8,columns = 9,delay = 25000;
for (int i = 0; i < rows; i++) {
for (int j = 0; j < columns; j++) {
	if(i==0){if(j==8 || j==7 || j==6){
	  continue;
	}else if (i==0 && j==4){
	   printf("^ ");fflush(stdout);
	   usleep(delay);j++;
	}}
	else if(i==1){if( j==7 || j==6){
		continue;
	}else if (i==1 && j==4){
		printf("^ ");fflush(stdout);usleep(delay);j++;
	}}
	else if(i==2 ){
	if(j==6){
		continue;
	}else if (i==2 && j==4){
		printf("^ ");fflush(stdout);
		usleep(delay);j++;
	}}
	else if(i==3 ){
		if (i==3 && j==4){
		printf("^ ");fflush(stdout);
		usleep(delay);
		j++;
	}}
	printf("# ");fflush(stdout);usleep(delay);
	}
	printf("\n");
}
printf("\n");

int totalBytes = 400,uploadedBytes = 0,progressBarWidth = 50;
int uploadSpeed = totalBytes / 8;
while (uploadedBytes < totalBytes) {
uploadedBytes += uploadSpeed;
if (uploadedBytes > totalBytes) {uploadedBytes = totalBytes;}
int percentage = (uploadedBytes * 100) / totalBytes;
int progress = (uploadedBytes * progressBarWidth) / totalBytes;
printf("Progress: [%3d%%] [", percentage);
for (int i = 0; i < progressBarWidth; i++) 
	{
	if (i < progress)
	 {
	printf("=");
	}
	else {printf(" ");
	}}
	printf("]\r");fflush(stdout);
	usleep(1000000);
	}

	printf("\n");
	send_file2(sockfd, uploadPath);
	printf("[+]File uploaded successfully.\n");
	close(sockfd);
        }
        else
    	{
       	 printf("\n invalid choice");
   	 }
    return 0;
}
