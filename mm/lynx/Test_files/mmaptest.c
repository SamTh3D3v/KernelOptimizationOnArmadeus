#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/io.h>
#include <sys/mman.h>

int main(int argc, char const *argv[])
{
    unsigned char *f;
    int size;
    int i;
    struct stat s;
    const char * file_name = argv[1];
    int fd = open (argv[1], O_RDONLY);

    /* Get the size of the file. */
    int status = fstat (fd, & s);
    size = s.st_size;

    f = (char *) mmap (0, size, PROT_READ, MAP_PRIVATE, fd, 0);
    
    madvise(f,size,MADV_SEQUENTIAL);
    
    for ( i = 0; i < size; i++) {
        char c;

        c = f[i];
        //putchar(c);
    }
    printf("\n done reading the file \n");
    return 0;
}
