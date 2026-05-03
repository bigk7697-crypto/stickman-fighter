# Script PowerShell pour compiler Stickman Fighter sans vcpkg
# Télécharge GLFW et GLM automatiquement

$ErrorActionPreference = "Stop"

Write-Host "=========================================" -ForegroundColor Cyan
Write-Host "  Setup & Build Stickman Fighter" -ForegroundColor Cyan
Write-Host "=========================================" -ForegroundColor Cyan

# Créer le dossier external
if (!(Test-Path "external")) {
    New-Item -ItemType Directory -Path "external" | Out-Null
}

# 1. Télécharger GLFW (source code)
$glfwUrl = "https://github.com/glfw/glfw/releases/download/3.3.8/glfw-3.3.8.zip"
$glfwZip = "external/glfw.zip"
$glfwDir = "external/glfw"

if (!(Test-Path $glfwDir)) {
    Write-Host "`n[1/5] Telechargement de GLFW..." -ForegroundColor Yellow
    Invoke-WebRequest -Uri $glfwUrl -OutFile $glfwZip
    Expand-Archive -Path $glfwZip -DestinationPath "external" -Force
    Rename-Item -Path "external/glfw-3.3.8" -NewName "glfw" -Force
    Remove-Item $glfwZip
    Write-Host "GLFW telecharge!" -ForegroundColor Green
} else {
    Write-Host "`n[1/5] GLFW deja present" -ForegroundColor Green
}

# 2. Télécharger GLM (header-only)
$glmUrl = "https://github.com/g-truc/glm/releases/download/0.9.9.8/glm-0.9.9.8.zip"
$glmZip = "external/glm.zip"
$glmDir = "external/glm"

if (!(Test-Path $glmDir)) {
    Write-Host "`n[2/5] Telechargement de GLM..." -ForegroundColor Yellow
    Invoke-WebRequest -Uri $glmUrl -OutFile $glmZip
    Expand-Archive -Path $glmZip -DestinationPath "external" -Force
    # GLM est dans un sous-dossier
    if (Test-Path "external/glm") {
        Remove-Item "external/glm" -Recurse -Force -ErrorAction SilentlyContinue
    }
    Move-Item -Path "external/glm/glm" -Destination "external/glm_include" -Force
    Remove-Item "external/glm" -Recurse -Force -ErrorAction SilentlyContinue
    Rename-Item -Path "external/glm_include" -NewName "glm" -Force
    Remove-Item $glmZip -ErrorAction SilentlyContinue
    Write-Host "GLM telecharge!" -ForegroundColor Green
} else {
    Write-Host "`n[2/5] GLM deja present" -ForegroundColor Green
}

# 3. Compiler GLFW en statique
$glfwBuildDir = "$glfwDir/build"
if (!(Test-Path "$glfwBuildDir/src/glfw3.lib")) {
    Write-Host "`n[3/5] Compilation de GLFW (statique)..." -ForegroundColor Yellow
    
    if (!(Test-Path $glfwBuildDir)) {
        New-Item -ItemType Directory -Path $glfwBuildDir | Out-Null
    }
    
    # Utiliser CMake pour generer les fichiers de build
    $cmakePath = (Get-Command cmake -ErrorAction SilentlyContinue).Source
    if (!$cmakePath) {
        Write-Host "ERREUR: CMake n'est pas installe!" -ForegroundColor Red
        Write-Host "Telechargez CMake depuis: https://cmake.org/download/" -ForegroundColor Yellow
        Write-Host "Ou installez avec: winget install Kitware.CMake" -ForegroundColor Yellow
        exit 1
    }
    
    Push-Location $glfwBuildDir
    try {
        & cmake .. -DBUILD_SHARED_LIBS=OFF -DGLFW_BUILD_EXAMPLES=OFF -DGLFW_BUILD_TESTS=OFF -DGLFW_BUILD_DOCS=OFF -DCMAKE_MSVC_RUNTIME_LIBRARY="MultiThreaded$<$<CONFIG:Debug>:Debug>" ..
        & cmake --build . --config Release
    } finally {
        Pop-Location
    }
    
    if (Test-Path "$glfwBuildDir/src/Release/glfw3.lib") {
        Copy-Item "$glfwBuildDir/src/Release/glfw3.lib" "$glfwBuildDir/src/glfw3.lib" -Force
    }
    
    Write-Host "GLFW compile!" -ForegroundColor Green
} else {
    Write-Host "`n[3/5] GLFW deja compile" -ForegroundColor Green
}

# 4. Compiler le jeu
Write-Host "`n[4/5] Compilation du jeu..." -ForegroundColor Yellow

# Creer le dossier de build
if (!(Test-Path "build")) {
    New-Item -ItemType Directory -Path "build" | Out-Null
}

# Chemins des includes
$glfwInclude = "$glfwDir/include"
$glmInclude = "$glmDir"
$gladInclude = "external/glad/include"
$srcDir = "src"

# Chemins des libs
$glfwLib = "$glfwBuildDir/src/glfw3.lib"

# Fichiers source
$sources = @(
    "$srcDir/main.cpp",
    "$srcDir/engine/Window.cpp",
    "$srcDir/engine/Renderer.cpp",
    "$srcDir/engine/Shader.cpp",
    "$srcDir/engine/Mesh.cpp",
    "$srcDir/engine/Camera.cpp",
    "$srcDir/engine/Input.cpp",
    "$srcDir/game/GameObject.cpp",
    "$srcDir/game/Animator.cpp",
    "$srcDir/game/CombatSystem.cpp",
    "$srcDir/game/HealthSystem.cpp",
    "external/glad/src/glad.c"
)

# Compiler avec cl.exe (Visual Studio)
$vsPath = & "${env:ProgramFiles(x86)}\Microsoft Visual Studio\Installer\vswhere.exe" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath 2>$null

if (!$vsPath) {
    # Essayer de trouver vcvarsall.bat
    $vcvarsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    if (!(Test-Path $vcvarsPath)) {
        $vcvarsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    }
    if (!(Test-Path $vcvarsPath)) {
        $vcvarsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    }
    if (!(Test-Path $vcvarsPath)) {
        $vcvarsPath = "${env:ProgramFiles(x86)}\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    }
    
    if (!(Test-Path $vcvarsPath)) {
        Write-Host "ERREUR: Visual Studio C++ non trouve!" -ForegroundColor Red
        Write-Host "Installez Visual Studio avec la charge de travail 'Developpement Desktop C++'" -ForegroundColor Yellow
        exit 1
    }
}

# Creer un script batch temporaire pour compiler
$compileBatch = @"
@echo off
call "$vcvarsPath"
echo Compilation avec MSVC...
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\main.obj $srcDir\main.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\Window.obj $srcDir\engine\Window.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\Renderer.obj $srcDir\engine\Renderer.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\Shader.obj $srcDir\engine\Shader.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\Mesh.obj $srcDir\engine\Mesh.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\Camera.obj $srcDir\engine\Camera.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\Input.obj $srcDir\engine\Input.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\GameObject.obj $srcDir\game\GameObject.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\Animator.obj $srcDir\game\Animator.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\CombatSystem.obj $srcDir\game\CombatSystem.cpp
cl /c /EHsc /O2 /MD /I$srcDir /I$gladInclude /I$glfwInclude /I$glmInclude /Fo.\build\HealthSystem.obj $srcDir\game\HealthSystem.cpp
cl /c /O2 /MD /I$gladInclude /Fo.\build\glad.obj external\glad\src\glad.c
echo Linking...
link /OUT:.\build\StickmanFighter.exe .\build\main.obj .\build\Window.obj .\build\Renderer.obj .\build\Shader.obj .\build\Mesh.obj .\build\Camera.obj .\build\Input.obj .\build\GameObject.obj .\build\Animator.obj .\build\CombatSystem.obj .\build\HealthSystem.obj .\build\glad.obj "$glfwLib" opengl32.lib user32.lib gdi32.lib shell32.lib
if errorlevel 1 exit 1
echo.
echo =========================================
echo  COMPILATION REUSSIE!
echo =========================================
echo Executable: .\build\StickmanFighter.exe
echo.
echo Pour lancer: .\build\StickmanFighter.exe
"@

$compileBatch | Out-File -FilePath "build_compile.bat" -Encoding ASCII

& cmd /c "build_compile.bat"

if ($LASTEXITCODE -eq 0) {
    Write-Host "`n[5/5] SUCCES!" -ForegroundColor Green
    Write-Host "`nLe jeu est compile: build\StickmanFighter.exe" -ForegroundColor Cyan
    Write-Host "`nPour jouer, executez:" -ForegroundColor White
    Write-Host "  .\build\StickmanFighter.exe" -ForegroundColor Yellow
    
    # Nettoyer
    Remove-Item "build_compile.bat" -ErrorAction SilentlyContinue
} else {
    Write-Host "`n[5/5] ECHEC de la compilation" -ForegroundColor Red
    exit 1
}
