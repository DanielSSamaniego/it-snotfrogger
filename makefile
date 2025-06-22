# Configuración básica
GAME := game
CXX := g++
SFML := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lbox2d
INCLUDE := -Iinclude
EXE := bin/$(GAME)

# Regla principal (compila solo Main.cpp)
$(EXE): src/Main.cpp src/Button.cpp src/MusicManager.cpp src/TorreControl.cpp src/Pajaro.cpp src/ClimaControl.cpp src/DrawMap.cpp src/DrawText.cpp src/Nube.cpp src/GloboAerostatico.cpp src/Avion.cpp
	$(CXX) $^ -o $@ $(INCLUDE) $(SFML) -std=c++17

# Regla para ejecutar
run: $(EXE)
	./$(EXE)

# Regla para limpiar (solo elimina el ejecutable)
clean:
	rm -f $(EXE)

.PHONY: run clean