#include <ciphers.hpp>
#include <emscripten/bind.h>

using namespace emscripten;

EMSCRIPTEN_BINDINGS(my_module) {
	class_<CaesarCipher>("CaesarCipher")
		.constructor<const std::string&>()
		.function("Encrypt", &CaesarCipher::Encrypt)
		.function("Decrypt", &CaesarCipher::Decrypt)
		;
	class_<CaesarCipherExt>("CaesarCipherExt")
		.constructor<const std::string&, unsigned int>()
		.function("Encrypt", &CaesarCipherExt::Encrypt)
		.function("Decrypt", &CaesarCipherExt::Decrypt)
		;
	class_<RailFence>("RailFence")
		.constructor<const std::string&>()
		.function("Encrypt", &RailFence::Encrypt)
		.function("Decrypt", &RailFence::Decrypt)
		;
	class_<MonoAlpha>("MonoAlpha")
		.constructor<const std::string&>()
		.function("Encrypt", &MonoAlpha::Encrypt)
		.function("Decrypt", &MonoAlpha::Decrypt)
		;
}
