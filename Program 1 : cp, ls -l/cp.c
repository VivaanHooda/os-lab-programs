#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define BUFF_SIZE 8192

int main (int argc[], char*  argv[]){

    ssize_t ret_in, ret_out;
    char buffer[BUFF_SIZE];
    int input_fd, output_fd;

    if (argc != 3){
        printf("Usage: cp file1 file2");
        return 1;
    }

    input_fd = open(argv[1], O_RDONLY);
    if (input_fd == -1){
        perror("open");
        return 2;
    }
    output_fd = open(argv[2], O_WRONLY | O_CREAT , 0644);
    if (output_fd == -1){
        perror("open");
        return 3;
    }
    while ((ret_in = read(input_fd, &buffer, BUFF_SIZE)) > 0){
        ret_out = write(output_fd, &buffer, (ssize_t) ret_in);

        if(ret_out != ret_in){
            perror(write);
            return 4;
        }
    }
    close (input_fd);
    close (output_fd);

    return (EXIT_SUCCESS);
}