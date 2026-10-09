# Sistemas Informáticos Industriales

# Francisco Jesús Figueroa Nombela

![UPM](https://img.shields.io/badge/UPM-ETSIDI-red)
![Curso](https://img.shields.io/badge/Curso-2026--2027-blue)
![Lenguaje](https://img.shields.io/badge/C-Programming-00599C?logo=c)
![Linux](https://img.shields.io/badge/Linux-Ubuntu-E95420?logo=ubuntu)
![Git](https://img.shields.io/badge/Git-Version%20Control-F05032?logo=git)

Material docente de la asignatura **Sistemas Informáticos Industriales** de la **Escuela Técnica Superior de Ingeniería y Diseño Industrial (ETSIDI)** de la **Universidad Politécnica de Madrid (UPM)**.

---

## 📖 Descripción

Este repositorio contiene el material utilizado en las prácticas de la asignatura **Sistemas Informáticos Industriales**, incluyendo los guiones y el código de inicio.

El objetivo de la asignatura es introducir en el desarrollo de aplicaciones para sistemas informáticos industriales, haciendo especial énfasis en el uso del lenguaje C y del sistema operativo Linux.

---

## 📚 Wiki

La documentación detallada de cada una de las prácticas se encuentra en la Wiki del repositorio.

➡️ **Acceso a la Wiki:**  
https://github.com/raquelcedazo/sistemas-informaticos-industriales/wiki

---

## 🎓 Profesorado

Asignatura impartida por el **Departamento de Ingeniería Eléctrica, Electrónica, Automática y Física Aplicada** de la **Universidad Politécnica de Madrid**:

- **Raquel Cedazo** *(coordinadora de las prácticas)*
- **David Álvarez**
- **Imanol Izcara**

---

## 🤝 Contribuciones

Este repositorio tiene finalidad exclusivamente docente.

Si detectas algún error o tienes alguna sugerencia de mejora, puedes comunicarlo al profesorado de la asignatura.

## Prácticas realizadas

### Práctica 1. Desarrollo de un juego de tenis en C++

Se ha desarrollado un juego de tenis para dos jugadores utilizando C++ y OpenGL/GLUT.

El programa incluye:
- Movimiento de la pelota y de las raquetas.
- Detección de colisiones y rebotes.
- Control de los jugadores mediante el teclado.
- Sistema de puntuación.

### Práctica 2. Comunicación entre procesos mediante FIFO

Se ha implementado un sistema de comunicación entre dos procesos independientes utilizando una tubería con nombre (*FIFO*) en Linux.

**Programas desarrollados:**

- `tenis`: ejecuta el juego y envía información cuando un jugador consigue un punto.
- `logger`: recibe los mensajes a través de la FIFO y los muestra en la terminal.

**Funciones utilizadas:**

- `mkfifo()`: creación de la tubería.
- `open()`: apertura de la FIFO para lectura o escritura.
- `write()`: envío de mensajes desde el juego.
- `read()`: recepción de mensajes en el logger.
- `close()` y `unlink()`: cierre y eliminación de la FIFO.

Además, se ha implementado la finalización automática de ambos procesos cuando uno de los jugadores alcanza tres puntos.

### Compilación y ejecución

Desde el directorio `workspace`:

```bash
cmake -S . -B build
cmake --build build
```

Para ejecutar los programas, utilizar dos terminales.

**Terminal 1 — Logger:**

```bash
./build/logger
```

**Terminal 2 — Tenis:**

```bash
./build/tenis
```

Es necesario ejecutar primero `logger`, ya que crea la FIFO que utilizará el juego.

Cuando un jugador alcance tres puntos, ambos programas finalizarán automáticamente.
