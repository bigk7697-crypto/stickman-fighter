@echo off
setlocal

:: Configuration
set PROJECT_NAME=StickmanFighter
set SRC_DIR=src
set BUILD_DIR=build
set EXTERNAL_DIR=external

:: Détection de Visual Studio
set VSWHERE="%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist %VSWHERE% (
    for /f "usebackq tokens=*" %%i in (`%VSWHERE% -latest -property installationPath`) do set VS_PATH=%%i
    set VCVARSALL="%VS_PATH%\VC\Auxiliary\Build\vcvarsall.bat"
) else (
    echo Visual Studio non trouve. Utilisez CMake ou installez VS2019/2022.
    exit /b 1
)

echo =========================================
echo  Compilation Stickman Fighter
echo =========================================
echo.

:: Charger l'environnement Visual Studio
call %VCVARSALL% x64

:: Créer le dossier build
if not exist %BUILD_DIR% mkdir %BUILD_DIR%

:: Chercher les includes de vcpkg
if exist C:\vcpkg\installed\x64-windows\include (
    set VCPKG_INCLUDE=C:\vcpkg\installed\x64-windows\include
    set VCPKG_LIB=C:\vcpkg\installed\x64-windows\lib
) else (
    echo vcpkg non trouve. Installez glfw3 et glm avec vcpkg.
    echo Ou modifiez ce script avec vos chemins.
    exit /b 1
)

echo Compilation des fichiers...
echo.

:: Compiler
echo Compiling main.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\main.obj %SRC_DIR%\main.cpp
if errorlevel 1 goto error

echo Compiling Window.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\Window.obj %SRC_DIR%\engine\Window.cpp
if errorlevel 1 goto error

echo Compiling Renderer.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\Renderer.obj %SRC_DIR%\engine\Renderer.cpp
if errorlevel 1 goto error

echo Compiling Shader.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\Shader.obj %SRC_DIR%\engine\Shader.cpp
if errorlevel 1 goto error

echo Compiling Mesh.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\Mesh.obj %SRC_DIR%\engine\Mesh.cpp
if errorlevel 1 goto error

echo Compiling Camera.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\Camera.obj %SRC_DIR%\engine\Camera.cpp
if errorlevel 1 goto error

echo Compiling Input.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\Input.obj %SRC_DIR%\engine\Input.cpp
if errorlevel 1 goto error

echo Compiling GameObject.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\GameObject.obj %SRC_DIR%\game\GameObject.cpp
if errorlevel 1 goto error

echo Compiling Animator.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\Animator.obj %SRC_DIR%\game\Animator.cpp
if errorlevel 1 goto error

echo Compiling CombatSystem.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\CombatSystem.obj %SRC_DIR%\game\CombatSystem.cpp
if errorlevel 1 goto error

echo Compiling HealthSystem.cpp...
cl /c /EHsc /O2 /MD /I%SRC_DIR% /I%EXTERNAL_DIR%\glad\include /I%VCPKG_INCLUDE% /Fo%BUILD_DIR%\HealthSystem.obj %SRC_DIR%\game\HealthSystem.cpp
if errorlevel 1 goto error

echo Compiling glad.c...
cl /c /O2 /MD /I%EXTERNAL_DIR%\glad\include /Fo%BUILD_DIR%\glad.obj %EXTERNAL_DIR%\glad\src\glad.c
if errorlevel 1 goto error

echo.
echo Linking...
link /OUT:%BUILD_DIR%\%PROJECT_NAME%.exe %BUILD_DIR%\main.obj %BUILD_DIR%\Window.obj %BUILD_DIR%\Renderer.obj %BUILD_DIR%\Shader.obj %BUILD_DIR%\Mesh.obj %BUILD_DIR%\Camera.obj %BUILD_DIR%\Input.obj %BUILD_DIR%\GameObject.obj %BUILD_DIR%\Animator.obj %BUILD_DIR%\CombatSystem.obj %BUILD_DIR%\HealthSystem.obj %BUILD_DIR%\glad.obj glfw3.lib opengl32.lib user32.lib gdi32.lib shell32.lib /LIBPATH:%VCPKG_LIB%
if errorlevel 1 goto error

echo.
echo =========================================
echo  Compilation REUSSIE!
echo =========================================
echo Executable: %BUILD_DIR%\%PROJECT_NAME%.exe
echo.
echo Pour lancer:
echo   %BUILD_DIR%\%PROJECT_NAME%.exe
goto end

:error
echo.
echo =========================================
echo  ERREUR DE COMPILATION
echo =========================================
exit /b 1

:end
endlocal
