param(
    [switch]$Solution,
    [ValidateSet("Debug", "Release")]
    [string]$Config = "Debug",
    [switch]$Clean
)

$BuildDir = "build"
Write-Host "=== MLTooling CMake Setup ==="

if ($Clean -and (Test-Path $BuildDir)) {
    Write-Host "Removing build directory..."
    Remove-Item -Recurse $BuildDir
}

$CMakeArgs = @(
    "-S", ".",
    "-B", $BuildDir
)

if ($Solution) {
    Write-Host "Generating normal build..."

    $CMakeArgs += @(
        "-G", "Visual Studio 18 2026",
        "-A", "x64",
        "-DMLTOOLING_IDE_FILES=ON"
    )
}
else {
    Write-Host "Generating normal build..."

    $CMakeArgs += @(
        "-G", "Ninja",
        "-DMLTOOLING_IDE_FILES=OFF"
    )
}

cmake @CMakeArgs

if ($LASTEXITCODE -ne 0) {
    Write-Error "Cmake configuration failed!"
    exit 1
}

Write-Host ""
Write-Host "Building $Config..."

cmake --build $BuildDir --config $Config

if ($LASTEXITCODE -ne 0) {
    Write-Error "Build failed!"
    exit 1
}

Write-Host ""
Write-Host "Done."