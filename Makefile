# Nombre del ejecutable final
TARGET = main.exe

# Lista de archivos fuente (.cpp)
SRCS = MainAPP.cpp \
       ProcesadorFrutas.cpp \
       Gestor_De_Planta.cpp \
       Empleado.cpp \
       MaquinaLavadora.cpp \
       Tienda.cpp \
       EmpleadoTecnico.cpp \
       Maquina.cpp \
       Distribucion.cpp \
       EmpleadoOperario.cpp \
       Envasadora.cpp

# Archivos objeto (.o) generados automaticamente
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
