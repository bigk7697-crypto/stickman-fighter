@echo off
chcp 65001 >nul
title Compilation Stickman Fighter
cls

echo =========================================
echo  COMPILATION AUTOMATIQUE COMPLETE
echo =========================================
echo.

:: Verifier Visual Studio
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS="%ProgramFiles%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    goto :found_vcvars
)
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    goto :found_vcvars
)
if exist "%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS="%ProgramFiles%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    goto :found_vcvars
)
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS="%ProgramFiles(x86)%\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    goto :found_vcvars
)
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    goto :found_vcvars
)
if exist "%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS="%ProgramFiles(x86)%\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    goto :found_vcvars
)

echo [ERREUR] Visual Studio C++ non trouve !
echo.
echo Installez Visual Studio 2019/2022 avec:
echo   - Developpement Desktop C++
echo   - CMake tools (optionnel)
echo.
echo Ou telechargez Build Tools:
echo https://visualstudio.microsoft.com/downloads/
echo.
pause
exit /b 1

:found_vcvars
echo [OK] Visual Studio trouve
echo.

:: Telecharger GLFW si pas present
if not exist external\glfw\include\GLFW\glfw3.h (
    echo [1/6] Telechargement de GLFW...
    powershell -Command "Invoke-WebRequest -Uri 'https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.bin.WIN64.zip' -OutFile 'glfw_temp.zip'"
    if not exist glfw_temp.zip (
        echo [ERREUR] Impossible de telecharger GLFW
        pause
        exit /b 1
    )
    powershell -Command "Expand-Archive -Path 'glfw_temp.zip' -DestinationPath 'external' -Force"
    move external\glfw-3.3.8.bin.WIN64 external\glfw >nul 2>&1
    del glfw_temp.zip >nul 2>&1
    echo [OK] GLFW telecharge
) else (
    echo [1/6] GLFW deja present
)

:: Telecharger GLM si pas present
if not exist external\glm\glm\glm.hpp (
    echo [2/6] Telechargement de GLM...
    powershell -Command "Invoke-WebRequest -Uri 'https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip' -OutFile 'glm_temp.zip'"
    if not exist glm_temp.zip (
        echo [ERREUR] Impossible de telecharger GLM
        pause
        exit /b 1
    )
    powershell -Command "Expand-Archive -Path 'glm_temp.zip' -DestinationPath 'external' -Force"
    move external\glm-0.9.9.8 external\glm >nul 2>&1
    del glm_temp.zip >nul 2>&1
    echo [OK] GLM telecharge
) else (
    echo [2/6] GLM deja present
)

echo.
echo [3/6] Preparation des dossiers...
if not exist build mkdir build

echo.
echo [4/6] Configuration de l'environnement MSVC...
call %VCVARS%
if errorlevel 1 (
    echo [ERREUR] Echec de vcvars64.bat
    pause
    exit /b 1
)

:: Chemins
echo [5/6] Compilation des sources...
set INCLUDES=/I"%~dp0src" /I"%~dp0external\glad\include" /I"%~dp0external\glfw\include" /I"%~dp0external\glm"
set FLAGS=/EHsc /O2 /MD /nologo

:: Compilation
echo   - main.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\main.obj" "src\main.cpp"
if errorlevel 1 goto :compile_error

echo   - Window.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\Window.obj" "src\engine\Window.cpp"
if errorlevel 1 goto :compile_error

echo   - Renderer.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\Renderer.obj" "src\engine\Renderer.cpp"
if errorlevel 1 goto :compile_error

echo   - Shader.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\Shader.obj" "src\engine\Shader.cpp"
if errorlevel 1 goto :compile_error

echo   - Mesh.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\Mesh.obj" "src\engine\Mesh.cpp"
if errorlevel 1 goto :compile_error

echo   - Camera.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\Camera.obj" "src\engine\Camera.cpp"
if errorlevel 1 goto :compile_error

echo   - Input.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\Input.obj" "src\engine\Input.cpp"
if errorlevel 1 goto :compile_error

echo   - GameObject.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\GameObject.obj" "src\game\GameObject.cpp"
if errorlevel 1 goto :compile_error

echo   - Animator.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\Animator.obj" "src\game\Animator.cpp"
if errorlevel 1 goto :compile_error

echo   - CombatSystem.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\CombatSystem.obj" "src\game\CombatSystem.cpp"
if errorlevel 1 goto :compile_error

echo   - HealthSystem.cpp...
cl %FLAGS% %INCLUDES% /c /Fo"build\HealthSystem.obj" "src\game\HealthSystem.cpp"
if errorlevel 1 goto :compile_error

echo   - glad.c...
cl /O2 /MD /nologo /I"%~dp0external\glad\include" /c /Fo"build\glad.obj" "external\glad\src\glad.c"
if errorlevel 1 goto :compile_error

echo.
echo [6/6] Linking...
link /nologo /OUT:"build\StickmanFighter.exe" ^
    "build\main.obj" ^
    "build\Window.obj" ^
    "build\Renderer.obj" ^
    "build\Shader.obj" ^
    "build\Mesh.obj" ^
    "build\Camera.obj" ^
    "build\Input.obj" ^
    "build\GameObject.obj" ^
    "build\Animator.obj" ^
    "build\CombatSystem.obj" ^
    "build\HealthSystem.obj" ^
    "build\glad.obj" ^
    "external\glfw\lib-vc2022\glfw3.lib" ^
    opengl32.lib user32.lib gdi32.lib shell32.lib

if errorlevel 1 goto :link_error

echo.
echo =========================================
echo   COMPILATION REUSSIE !
echo =========================================
echo.
echo L'executable est pret: build\StickmanFighter.exe
echo.
echo Pour jouer, double-cliquez sur:
echo   build\StickmanFighter.exe
echo.
echo Ou executez dans ce terminal:
echo   .\build\StickmanFighter.exe
echo.
pause
exit /b 0

:compile_error
echo.
echo [ERREUR] Echec de la compilation
echo Verifiez que Visual Studio est bien installe avec C++
pause
exit /b 1

:link_error
echo.
echo [ERREUR] Echec du linking
echo.
pause
exit /b 1
