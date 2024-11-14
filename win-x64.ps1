if ($env:OS -ne "Windows_NT")
{
    Write-Host "This script is only meant to run on Windows." -ForegroundColor Red
    exit 1
}

function Test-Command
{
    param (
        [string]$command
    )
    $result = Get-Command $command -ErrorAction SilentlyContinue
    return $result -ne $null
}

if (-not (Test-Command "git"))
{
    Write-Host "Git is not installed. Please install Git and try again." -ForegroundColor Red
    exit 1
}

if (-not (Test-Command "cmake"))
{
    Write-Host "CMake is not installed. Please install CMake and try again." -ForegroundColor Red
    exit 1
}

# Ensure Visual Studio Build Tools are installed (for MSVC compiler)
#if (-not (Test-Command "cl")) {
#    Write-Host "Visual Studio Build Tools (MSVC) are not installed. Please install them and try again." -ForegroundColor Red
#    exit 1
#}

$VcpkgDirectory = "$env:USERPROFILE\vcpkg"
if (-Not (Test-Path $VcpkgDirectory))
{
    Write-Host "Cloning vcpkg repository..." -ForegroundColor Green
    git clone https://github.com/microsoft/vcpkg.git $VcpkgDirectory
}
else
{
    Write-Host "vcpkg directory already exists." -ForegroundColor Green
}

Write-Host "Running bootstrap-vcpkg.bat..." -ForegroundColor Green
Set-Location -Path $VcpkgDirectory
.\bootstrap-vcpkg.bat

Write-Host "Integrating vcpkg with Visual Studio..." -ForegroundColor Green
.\vcpkg integrate install

Write-Host "Installing dependencies with vcpkg..." -ForegroundColor Green
.\vcpkg install

$BuildDir = "$env:GITHUB_WORKSPACE\build"
if (-Not (Test-Path $BuildDir))
{
    New-Item -Path $BuildDir -ItemType Directory
}

Write-Host "Configuring CMake..." -ForegroundColor Green
$CMakeArgs = @(
    "-B$BuildDir",
    "-DCMAKE_CXX_COMPILER=cl", # Use MSVC (cl)
    "-DCMAKE_C_COMPILER=cl", # Use MSVC (cl)
    "-DCMAKE_BUILD_TYPE=Release",
    "-DCMAKE_TOOLCHAIN_FILE=$VcpkgDirectory\scripts\buildsystems\vcpkg.cmake",
    "-S$env:GITHUB_WORKSPACE"
)
cmake @CMakeArgs

Write-Host "Building the project..." -ForegroundColor Green
cmake --build $BuildDir --config Release

Write-Host "Running tests with ctest..." -ForegroundColor Green
ctest --build-config Release --output-on-failure
