#include <iostream>
#include <memory>

#include <ciphers.hpp>

int main() {
	const std::string message = R"(a very long test message...
so long that infact it can't be deciphered!)";
	std::unique_ptr<Crypt> cipher(new CaesarCipher(message));
	std::cout << cipher->Encrypt() << '\n';
	std::cout << cipher->Decrypt() << '\n';
	cipher = std::unique_ptr<Crypt>(new CaesarCipherExt(message, 5));
	std::cout << cipher->Encrypt() << '\n';
	std::cout << cipher->Decrypt() << '\n';
	cipher = std::unique_ptr<Crypt>(new RailFence(message));
	std::cout << cipher->Encrypt() << '\n';
	std::cout << cipher->Decrypt() << '\n';
	cipher = std::unique_ptr<Crypt>(new MonoAlpha(message));
	std::cout << cipher->Encrypt() << '\n';
	std::cout << cipher->Decrypt() << '\n';
	return 0;
}
