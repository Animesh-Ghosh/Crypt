#include <string>
#include <iostream>
#include <memory>

#include <BugEye/BugEye3.h>
#include <ciphers.hpp>

static auto test = bugeye::test("Test for ciphers") = [] {
	const std::string message = R"(a very long test message...
so long that infact it can't be deciphered!)";

	std::cout << "Testing CaesarCipher:\n";
	std::unique_ptr<Crypt> cipher(new CaesarCipher(message));
	cipher->Encrypt();
	IS(cipher->Decrypt(), message);

	std::cout << "Testing CaesarCipherExt:\n";
	for (unsigned int i = 1; i <= 26; ++i) {
		cipher = std::unique_ptr<Crypt>(new CaesarCipherExt(message, 5));
		cipher->Encrypt();
		IS(cipher->Decrypt(), message);
	}

	std::cout << "Testing RailFence cipher:\n";
	cipher = std::unique_ptr<Crypt>(new RailFence(message));
	cipher->Encrypt();
	IS(cipher->Decrypt(), message);

	std::cout << "Testing MonoAlpha cipher:\n";
	cipher = std::unique_ptr<Crypt>(new MonoAlpha(message));
	cipher->Encrypt();
	IS(cipher->Decrypt(), message);
};
