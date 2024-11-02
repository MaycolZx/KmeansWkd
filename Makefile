# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall
# LDFLAGS = -L${PWD}/lib/ -lglad -lglfw -lGL -lX11 -lpthread -lXrandr -lXi -ldl
LDFLAGS = -L${PWD}/lib/ -lglad -lglfw -lGL -lGLU -lglut -lX11 -lpthread -lXrandr -lXi -ldl
# LDFLAGS = -L${PWD}/lib/ -lglad -lGL -lX11 -lpthread -lXrandr -lXi -ldl
SRCDIR = src
INCDIR = include
BINDIR = bin
TARGET = mi_programa
SRCS := $(wildcard $(SRCDIR)/*.cpp)
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(BINDIR)/%.o)
DEPS := $(SRCS:$(SRCDIR)/%.cpp=$(SRCDIR)/%.d)

# Regla principal
$(BINDIR)/$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) $^ -o $@ $(LDFLAGS)

# Regla para compilar objetos
$(BINDIR)/%.o: $(SRCDIR)/%.cpp | $(BINDIR)
	$(CXX) $(CXXFLAGS) -I$(INCDIR) -c $< -o $@
	# $(CXX) $(CXXFLAGS) -I$(INCDIR) -MMD -MP -c $< -o $@

# Crear directorio binario si no existe
$(BINDIR):
	mkdir -p $(BINDIR)

-include $(DEPS)
# Limpiar archivos generados
clean:
	rm -rf $(BINDIR)

# Evitar conflictos con archivos llamados "clean"
.PHONY: clean

