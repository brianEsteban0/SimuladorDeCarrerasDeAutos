
EXEC = simuladorDeCarrerasDeAuto

CXX = g++

CXXFLAGS = -std=c++11

SRC = carrera.cpp

all: $(EXEC)


#Generar el archivo compilado
$(EXEC):$(SRC)
	$(CXX) $(CXXFLAGS) -o $(EXEC) $(SRC)

#Evitar conflictos con archivos llamados all
.PHONY: all

