#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd;
    char buffer[255];
    struct flock fvar;

    /* Check for filename argument */
    if (argc < 2) {
        printf("Usage: %s filename\n", argv[0]);
        return -1;
    }

    /* Open file */
    fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    /* Initialize lock structure */
    fvar.l_type   = F_WRLCK;      // Write lock
    fvar.l_whence = SEEK_END;     // Relative to EOF
    fvar.l_start  = -100;         // Start 100 bytes before EOF
    fvar.l_len    = 100;          // Lock 100 bytes

    printf("Press ENTER to set lock...\n");
    getchar();

    printf("Trying to get lock...\n");

    /* Try to set lock (non-blocking) */
    if (fcntl(fd, F_SETLK, &fvar) == -1) {

        /* If lock failed, find who owns it */
        fcntl(fd, F_GETLK, &fvar);
        printf("File already locked by process (PID): %d\n", fvar.l_pid);
        close(fd);
        return -1;
    }

    printf("File locked successfully.\n");

    /* Move file pointer and read data */
    if (lseek(fd, -50, SEEK_END) == -1) {
        perror("lseek");
        exit(1);
    }

    if (read(fd, buffer, 100) == -1) {
        perror("read");
        exit(1);
    }

    buffer[100] = '\0';
    printf("Data read from file:\n%s\n", buffer);

    printf("Press ENTER to release lock...\n");
    getchar();

    /* Unlock file */
    fvar.l_type   = F_UNLCK;
    fvar.l_whence = SEEK_SET;
    fvar.l_start  = 0;
    fvar.l_len    = 0;

    if (fcntl(fd, F_SETLK, &fvar) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("File unlocked.\n");

    close(fd);
    return 0;
}
