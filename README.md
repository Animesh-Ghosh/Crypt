# Crypt

A WebAssembly toy project.

Implement cryptographic ciphers and use them in a web-app them to encrypt/decrypt simple texts.

**Ciphers implemented currently cannot be used to decrypt a given cipher text. Currently only encrypting plain-text and getting back the plain-text works.**

*Prerequisites: Need a C++11 compliant compiler and Emscripten toolchain. You can get the Emscripten toolchain from [here](https://github.com/emscripten-core/emsdk).*

## Building and Running

Developed using MinGW toolchain for native build. For WebAssembly, use emscripten (64-bit).

**Native:**
```PowerShell
.\mingw32-make run
```

**WebAssembly:**
1. Activate emscripten
2. Run:
```PowerShell
.\em++ --bind .\web-bindings.cpp .\ciphers.cpp -I. -std=c++11 -Wall -Wextra -pedantic -o ciphers.html
```
*Note: You can specify em++ to either generate only the JS file which loads the WASM module or you can use Emscripten's generated HTML.*

3. Serve the output files and play around with the API in the browser (either Node or Python's http.server module works).

**For Python:**
```PowerShell
python -m http.server --bind 127.0.0.1
```

**JS API:**

Classes are attached to the `Module` object. Refer to constructor declarations in `ciphers.hpp`. To use the classes:
```js
let cipher = new Module.RailFence("come home");
cipher.Encrypt();  // "cm oeoehm"
cipher.Decrypt();  // "come home"
```

**TODOs:**

- [ ] Create an interface (probably with Vue.js)
