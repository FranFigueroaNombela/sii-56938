#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "DatosMemCompartida.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc,char* argv[])
{
	int i;
	DatosMemCompartida* dat;
	void *direccion;
	int fd;
	
	fd=open("/tmp/tenis_mem", O_RDWR);
	if (fd == -1)
	{
		perror("Error al abrir el archivo"); 
		return 1;
	}
	direccion=mmap(nullptr,sizeof(DatosMemCompartida),PROT_READ | PROT_WRITE,MAP_SHARED,fd,0);
	if (direccion == MAP_FAILED)
	{
		perror("Error en la proyeccion mmap"); 
		close(fd);
		return 1;
	}
	close(fd);
	dat=(DatosMemCompartida*)direccion;

	//while(1)
	while(dat->finPartida==0)
	{
		usleep(25000);
		// X3 Completar la lógica
		// dat->jugador, por ejemplo, accede al identificador del jugador
		
		// Posicion vertical de la pelota
    		float yPelota = dat->esfera.centro.y;

   		// Centro vertical de la raqueta
    		float yRaqueta = (dat->raqueta1.y1 + dat->raqueta1.y2) / 2.0f;

    		// Decidir el movimiento
		    if (yPelota > yRaqueta + 0.2f)
		    {
			dat->accion = 1;   // Subir
		    }
		    else if (yPelota < yRaqueta - 0.2f)
		    {
			dat->accion = -1;  // Bajar
		    }
		    else
		    {
			dat->accion = 0;   // No moverse
		    }
	  }
	munmap(direccion, sizeof(DatosMemCompartida));
	return 0;
}
