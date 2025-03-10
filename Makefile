# Nombre del ejecutable final
TARGET = main.exe

# Lista de archivos fuente (.cpp)
SRCS = Main.cpp \
       ProcesadorFrutas.cpp \
       Gestor_De_Planta.cpp \
       Empleado.cpp \
       MaquinaLavadora.cpp \
       EmpleadoTecnico.cpp \
       Maquina.cpp \
       Pasteurizador.cpp

# Archivos objeto (.o) generados automáticamente
OBJS = $(SRCS:.cpp=.o)

# Compilador y flags
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# Regla principal: compilar todo
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Regla para compilar cada .cpp en .o
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Comando para limpiar (borra .o y el ejecutable)
clean:
	rm -f $(OBJS) $(TARGET)

# Evita que 'clean' sea confundido con un archivo
.PHONY: clean
