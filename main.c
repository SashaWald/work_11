#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int generate_random(){
    int rand;
    int o = open("/dev/random", O_RDONLY);
    if (o == -1){
        printf("Error with open: %s\n",strerror(errno));
    }
    int r=read(o,&rand,sizeof(rand));
    if (r == -1){
        printf("Error with open: %s\n",strerror(errno));
    }
    close(o);
    return(rand);
}

int main(){
    int r_array[10];
    for (int i = 0; i < 10; i++){
        r_array[i]=generate_random();
        printf("r_array[%d]: %d\n",i,r_array[i]);
    }
    //create file to write
    int file_write=open("output.txt", O_WRONLY | O_CREAT, 0666);
    if(file_write == -1){
        printf("Error with open: %s\n",strerror(errno));
    }
    //write numbers to file
    int file_read=write(file_write,r_array,sizeof(r_array));
    if(file_read == -1){
        printf("Error with open: %s\n",strerror(errno)); 
    }
    
    int r_array_copy[10];
    int file_copy=open("output.txt",O_RDONLY);
    if (file_copy == -1){
        printf("Error with open: %s\n",strerror(errno)); 
    }
    int file_copy_read=read(file_copy,r_array_copy,sizeof(r_array_copy));
    printf("Verifying that written values are consistent\n");
    for (int i = 0; i < 10; i++){
        printf("r_array_copy[%d]: %d\n",i,r_array_copy[i]);
    }
    close(file_write);
    close(file_copy);
    return(0);
}