# Makefile para compilar los ejercicios del Laboratorio 05

CC = gcc
CFLAGS = -Wall -Wextra -g -std=c99
TARGETS = ejercicio5 ejercicio7

all: $(TARGETS)

ejercicio5: ejercicio5.c graph.h
	$(CC) $(CFLAGS) -o ejercicio5 ejercicio5.c

ejercicio7: ejercicio7.c graph.h stack.h
	$(CC) $(CFLAGS) -o ejercicio7 ejercicio7.c

# Ejecutar pruebas
test: all
	@echo "=== Ejecutando Ejercicio 5 con grafo ejemplo A ==="
	./ejercicio5 grafo_ejemplo_a.txt
	@echo ""
	@echo "=== Ejecutando Ejercicio 5 con grafo ejercicio 3 ==="
	./ejercicio5 grafo_ej3.txt
	@echo ""
	@echo "=== Ejecutando Ejercicio 7 ==="
	./ejercicio7

# Limpiar archivos compilados
clean:
	rm -f $(TARGETS) *.o

# Compilar el documento LaTeX
pdf:
	@echo "Compilando documento LaTeX..."
	@echo "Copia Lab05_Informe.tex a Overleaf para compilar"

.PHONY: all test clean pdf