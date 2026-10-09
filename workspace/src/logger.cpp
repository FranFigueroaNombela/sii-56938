#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

int main(int argc, char **argv) {
    int fd;
    char buffer[1024];
    const char* nombreFIFO = "/tmp/tenis_fifo";
    // borrar FIFO por si existiera previamente
    unlink(nombreFIFO);

    /* crear el FIFO */
    if (mkfifo(nombreFIFO, 0666)<0) {
        perror("No puede crearse el FIFO");
        return(1);
    }
    /* Abrir el FIFO */
    if ((fd = open(nombreFIFO, O_RDONLY)) < 0) {
        perror("No puede abrirse el FIFO");
        return(1);
    }
    /* Leer de la FIFO */
    ssize_t bytesLeidos;

   while ((bytesLeidos = read(fd, buffer, sizeof(buffer) - 1)) > 0)
   {
     buffer[bytesLeidos] = '\0';
     printf("%s", buffer);
     fflush(stdout);
   }
    close(fd);
    unlink(nombreFIFO);
    return(0);
}
