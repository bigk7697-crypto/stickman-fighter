# Stickman Fighter - Guide d'Installation

## ÉTAPE 1 : Installation des Dépendances (Windows)

### Option A : Vcpkg (Recommandé)

```powershell
# 1. Installer vcpkg
git clone https://github.com/Microsoft/vcpkg.git C:\vcpkg
.\C:\vcpkg\bootstrap-vcpkg.bat

# 2. Installer les packages
vcpkg install glfw3:x64-windows
vcpkg install glm:x64-windows

# 3. Intégrer à Visual Studio
vcpkg integrate install
```

### Option B : Visual Studio Manuel

1. Télécharger et compiler **GLFW** : https://www.glfw.org/download.html
2. Télécharger **GLM** (header-only) : https://github.com/g-truc/glm/releases
3. Générer **GLAD** : https://glad.dav1d.de/
   - Language: C/C++
   - Specification: OpenGL
   - API: gl Version 3.3
   - Profile: Core
   - Options: Generate a loader

## Compilation

### Avec CMake

```powershell
cd c:\Users\bigk7\Desktop\game
mkdir build
cd build
cmake .. -DCMAKE_TOOLCHAIN_FILE=C:\vcpkg\scripts\buildsystems\vcpkg.cmake
cmake --build . --config Release
```

### Avec build.bat (Visual Studio)

Un script `build.bat` est fourni pour compiler directement sans CMake :

```batch
build.bat
```

## Structure Finale

```
game/
├── src/
│   ├── main.cpp
│   ├── engine/
│   │   ├── Window.h/.cpp
│   │   └── Renderer.h/.cpp
│   └── game/
├── external/
│   └── glad/
├── build/
└── CMakeLists.txt
```

## Démarrage

Après compilation, l'exécutable se trouve dans `build/Release/StickmanFighter.exe` ou `build/Debug/StickmanFighter.exe`

```powershell
.\build\Release\StickmanFighter.exe
```

**Contrôles :**
- `ESC` - Quitter le programme
- La fenêtre affiche un écran bleu foncé

## Prochaine Étape

Une fois que cette fenêtre s'affiche correctement, nous passerons à l'**Étape 2** : Afficher un triangle coloré, puis un cube 3D.
