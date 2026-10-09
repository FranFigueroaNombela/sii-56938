
//
// Mundo.cpp: implementation of the CMundo class.
//
//////////////////////////////////////////////////////////////////////

#include <fstream>
#include "Mundo.h"
//#include "glut.h"

#include <GL/freeglut.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Bibliotecas para trabajar con la FIFO
#include <fcntl.h>
#include <unistd.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMundo::CMundo()
{
    fd = -1;
    Init();
}

CMundo::~CMundo()
{
    // Cerrar la FIFO si se ha abierto correctamente
    if (fd >= 0)
    {
        close(fd);
    }
}

void CMundo::InitGL()
{
    // Habilitamos las luces, la renderizacion
    // y el color de los materiales
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_PROJECTION);
    gluPerspective(40.0, 800/600.0f, 0.1, 150);
}

void print(char *mensaje, int x, int y, float r, float g, float b)
{
    glDisable(GL_LIGHTING);

    glMatrixMode(GL_TEXTURE);
    glPushMatrix();
    glLoadIdentity();

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();

    gluOrtho2D(0, glutGet(GLUT_WINDOW_WIDTH),
               0, glutGet(GLUT_WINDOW_HEIGHT));

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    glColor3f(r, g, b);

    glRasterPos3f(
        x,
        glutGet(GLUT_WINDOW_HEIGHT)-18-y,
        0
    );

    int len = strlen(mensaje);

    for (int i = 0; i < len; i++)
        glutBitmapCharacter(
            GLUT_BITMAP_HELVETICA_18,
            mensaje[i]
        );

    glMatrixMode(GL_TEXTURE);
    glPopMatrix();

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();

    glEnable(GL_DEPTH_TEST);
}

void CMundo::OnDraw()
{
    // Borrado de la pantalla
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Definimos el punto de vista
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    gluLookAt(
        0.0, 0, 17,
        0.0, 0.0, 0.0,
        0.0, 1.0, 0.0
    );

    // Dibujamos las puntuaciones
    char cad[100];

    sprintf(cad, "Jugador1: %d", puntos1);
    print(cad, 10, 0, 1, 1, 1);

    sprintf(cad, "Jugador2: %d", puntos2);
    print(cad, 650, 0, 1, 1, 1);

    // Dibujamos las paredes
    for (int i = 0; i < paredes.size(); i++)
    {
        paredes[i].Dibuja();
    }

    fondo_izq.Dibuja();
    fondo_dcho.Dibuja();

    jugador1.Dibuja();
    jugador2.Dibuja();

    esfera.Dibuja();

    // Cambiar el buffer
    glutSwapBuffers();
}

void CMundo::OnTimer(int value)
{
    // Movimiento de los jugadores y la pelota
    jugador1.Mueve(0.025f);
    jugador2.Mueve(0.025f);
    esfera.Mueve(0.025f);

    // Rebotes con las paredes
    for (int i = 0; i < paredes.size(); i++)
    {
        paredes[i].Rebota(esfera);
        paredes[i].Rebota(jugador1);
        paredes[i].Rebota(jugador2);
    }

    // Rebotes con las raquetas
    jugador1.Rebota(esfera);
    jugador2.Rebota(esfera);

    // ====================================
    // PUNTO PARA EL JUGADOR 2
    // ====================================

    if (fondo_izq.Rebota(esfera))
    {
        esfera.centro.x = 0;
        esfera.centro.y = rand()/(float)RAND_MAX;

        esfera.velocidad.x =
            2 + 2*rand()/(float)RAND_MAX;

        esfera.velocidad.y =
            2 + 2*rand()/(float)RAND_MAX;

        puntos2++;

        // DEBUG: comprobar que detectamos el punto


        // Crear el mensaje para el logger
        char mensaje[128];

        snprintf(
            mensaje,
            sizeof(mensaje),
            "Jugador 2 marca 1 punto, lleva un total de %d puntos.\n",
            puntos2
        );

        // Enviar el mensaje por la FIFO
        if (fd >= 0)
        {
            ssize_t enviados = write(fd,mensaje,strlen(mensaje));

            if (puntos2 >= 3)
	{
	    printf("Fin de la partida. Gana el jugador 2.\n");
            glutLeaveMainLoop();
            return;
	}

            if (enviados < 0)
            {
                perror("Error al escribir en la FIFO");
            }
        }
    }

    // ====================================
    // PUNTO PARA EL JUGADOR 1
    // ====================================

    if (fondo_dcho.Rebota(esfera))
    {
        esfera.centro.x = 0;
        esfera.centro.y = rand()/(float)RAND_MAX;

        esfera.velocidad.x =
            -2 - 2*rand()/(float)RAND_MAX;

        esfera.velocidad.y =
            -2 - 2*rand()/(float)RAND_MAX;

        puntos1++;

        // DEBUG: comprobar que detectamos el punto


        // Crear el mensaje para el logger
        char mensaje[128];

        snprintf(
            mensaje,
            sizeof(mensaje),
            "Jugador 1 marca 1 punto, lleva un total de %d puntos.\n",
            puntos1
        );

        // Enviar el mensaje por la FIFO
        if (fd >= 0)
        {
            ssize_t enviados = write(fd,mensaje,strlen(mensaje));
            if (puntos1 >= 3)
	{
	    printf("Fin de la partida. Gana el jugador 1.\n");
            glutLeaveMainLoop();
            return;
	}

            if (enviados < 0)
            {
                perror("Error al escribir en la FIFO");
            }
        }
    }
}

void CMundo::OnKeyboardDown(unsigned char key, int x, int y)
{
    switch (key)
    {
        case 's':
            jugador1.velocidad.y = -4;
            break;

        case 'w':
            jugador1.velocidad.y = 4;
            break;

        case 'l':
            jugador2.velocidad.y = -4;
            break;

        case 'o':
            jugador2.velocidad.y = 4;
            break;
    }
}

void CMundo::Init()
{
    Plano p;

    // Pared inferior
    p.x1 = -7;
    p.y1 = -5;
    p.x2 = 7;
    p.y2 = -5;
    paredes.push_back(p);

    // Pared superior
    p.x1 = -7;
    p.y1 = 5;
    p.x2 = 7;
    p.y2 = 5;
    paredes.push_back(p);

    // Fondo izquierdo
    fondo_izq.r = 0;
    fondo_izq.x1 = -7;
    fondo_izq.y1 = -5;
    fondo_izq.x2 = -7;
    fondo_izq.y2 = 5;

    // Fondo derecho
    fondo_dcho.r = 0;
    fondo_dcho.x1 = 7;
    fondo_dcho.y1 = -5;
    fondo_dcho.x2 = 7;
    fondo_dcho.y2 = 5;

    // Jugador izquierdo
    jugador1.g = 0;
    jugador1.x1 = -6;
    jugador1.y1 = -1;
    jugador1.x2 = -6;
    jugador1.y2 = 1;

    // Jugador derecho
    jugador2.g = 0;
    jugador2.x1 = 6;
    jugador2.y1 = -1;
    jugador2.x2 = 6;
    jugador2.y2 = 1;

    // Inicializar puntuaciones
    puntos1 = 0;
    puntos2 = 0;

    // ====================================
    // CONEXION CON EL LOGGER
    // ====================================



    fd = open("/tmp/tenis_fifo", O_WRONLY);

    if (fd < 0)
    {
        perror("Error al abrir la FIFO");
    }

}
