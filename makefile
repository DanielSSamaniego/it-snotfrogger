# Configuración básica
GAME := game
CXX := g++
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d
INCLUDE := -Iinclude
EXE := bin/$(GAME)

# Regla principal (compila solo main.cpp)
$(EXE): src/main.cpp src/boton.cpp
	$(CXX) $^ -o $@ $(INCLUDE) $(SFML) -std=c++17

# Regla para ejecutar
run: $(EXE)
	./$(EXE)

# Regla para limpiar (solo elimina el ejecutable)
clean:
	rm -f $(EXE)

.PHONY: run clean