#include <stdio.h>
#include <stdint.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <stdlib.h>

// DDR reserved memory (DMM)
#define DMM_START 0x1000000
#define DMM_SIZE  0x2000000

int main(int argc, char** argv){

    int samples;

    if(argc < 2){
        printf("Uso: ./DRRclear BYTES\n");
        return 1;
    }

    samples = atoi(argv[1]);

    int fd;
    char* name = "/dev/mem";

    if((fd = open(name, O_RDWR | O_SYNC)) < 0){
        perror("open");
        return 1;
    }

    void* dmm = mmap(NULL, DMM_SIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, DMM_START);


    __sync_synchronize();

    uint8_t* ptr = (uint8_t*) dmm;
    for(int i = 0; i < samples; i++)
        ptr[i] = 0;
    printf("%d bytes limpiados\n", samples);


}
