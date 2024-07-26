#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include <syslog.h>

// Requirements
// 1. Accepts two arguments: the first is the full path to a file
//    and the second is a test string which will be written within
//    within the file
// 2. Exits and print statements if any of the arguments
//    are not specified
// 3. Creates a new file with name and path specified, with contents
//    from the second argument

int main(int argc, char* argv[])
{
    // Check that we recieved exactly 2 arguments
    if(argc != 3)
    {
        syslog(LOG_ERR, "Invalid number of arguments passed to writer");
        printf("Usage: writer [path-to-file] [contents-to-write]\n");
        exit(EXIT_FAILURE);
    }

    // set up syslog to log to /var/log/syslog
    openlog(NULL, 0, LOG_USER);


    // Open the file. Create if it doesn't exist. If it does already exist,
    // truncate it to 0 bytes
    int fd = creat(argv[1], 0644);
    if(fd == -1)
    {
        int err = errno;
        syslog(LOG_ERR, "Open file %s failed with error: %d\n", argv[1], err);
        exit(EXIT_FAILURE);
    }

    // Append a newline to the string and Write it to the file
    char* str = (char*) calloc(strlen(argv[2])+2, sizeof(char));
    syslog(LOG_DEBUG, "Writing %s to %s", argv[2], argv[1]);
    snprintf(str, strlen(argv[2]) + 2, "%s\n", argv[2]);
    if(-1 == write(fd, str, strlen(str)))
    {
        perror("Error writing contents to file");
        syslog(LOG_ERR, "Error writing to file");
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;

}