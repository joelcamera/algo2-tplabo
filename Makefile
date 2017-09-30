# Compilador
CC=g++

# flags de compilacion
CFLAGS= -g -Wall

# flags de linkeo
LDFLAGS=

# Agregar aca los directorios a incluir en la compilacion
INCDIR=

# Agregar aca los archivos .cpp a compilar
SOURCES=tests.cpp

# Objetos que seran generados
OBJECTS=$(SOURCES:.cpp=.o)

# Nombre del ejecutable a generar
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $@

clean:
	rm -rf $(EXECUTABLE) $(OBJECTS)

.cpp.o:
	$(CC) -I$(INCDIR) $(CFLAGS) $< -c -o $@
