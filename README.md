# Crypt

A WebAssembly toy project.

## Building and Running

Developed using MinGW toolchain for native build. For WebAssembly, use emscripten (64-bit).

Native:
```PowerShell
.\mingw32-make run
```

WebAssembly:
```PowerShell
em++ --bind web-bindings.cpp ciphers.cpp -I. -std=c++11 -Wall -Wextra -pedantic
```
