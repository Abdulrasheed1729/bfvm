if (Test-Path -Path ".\build") {
    cmake --build build --target clean
}

cmake -S . -B build -Wno-dev

cmake --build build

cd build\

Write-Host "Changing to the build directory"
try{
ctest.exe --rerun-failed --output-on-failure
} catch {
Write-Host "Okay, something went wrong!"
}
Write-Host "Build run successfully"

cd ..
