CXX = g++
CXXFLAGS = -std=c++17 -O2 -I./src -I./external/glad/include -I/mingw64/include
LDFLAGS = -L/mingw64/lib -lglfw3 -lopengl32 -lgdi32 -luser32 -lshell32

SRCS = src/main.cpp \
       src/engine/Window.cpp \
       src/engine/Renderer.cpp \
       src/engine/Shader.cpp \
       src/engine/Mesh.cpp \
       src/engine/Camera.cpp \
       src/engine/Input.cpp \
       src/game/GameObject.cpp \
       src/game/Animator.cpp \
       src/game/CombatSystem.cpp \
       src/game/HealthSystem.cpp \
       external/glad/src/glad.c

OBJS = $(SRCS:.cpp=.o)
TARGET = StickmanFighter.exe

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRCS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "Compilation terminée ! Lancez avec: ./$(TARGET)"

clean:
	rm -f $(TARGET)

# Sous Windows avec MSYS2:
# mingw32-make
