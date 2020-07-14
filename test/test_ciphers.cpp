#include <string>
#include <iostream>
#include <memory>

#include <BugEye/BugEye3.h>
#include <Crypt/ciphers.hpp>

static const unsigned int TESTS = 100;

static auto test = bugeye::test("Test for ciphers").plan(TESTS * 4) = [] {
	const std::string message = R"(a very long test message...
so long that infact it can't be deciphered!)";
	std::unique_ptr<Crypt> cipher;

	for (unsigned int i = 0; i < TESTS; ++i) {
		bugeye::subtest("Sub-test for CaesarCipher") = [&] {
			cipher = std::unique_ptr<Crypt>(new CaesarCipher(message));
			cipher->Encrypt();
			IS(cipher->Decrypt(), message);
		};

		const unsigned int maxOffset = 26;
		bugeye::subtest("Sub-test for CaesarCipherExt").plan(maxOffset) = [&] {
			for (unsigned int i = 1; i <= maxOffset; ++i) {
				cipher = std::unique_ptr<Crypt>(new CaesarCipherExt(message, i));
				cipher->Encrypt();
				IS(cipher->Decrypt(), message);
			}
		};

		bugeye::subtest("Sub-test for RailFence") = [&] {
			cipher = std::unique_ptr<Crypt>(new RailFence(message));
			cipher->Encrypt();
			IS(cipher->Decrypt(), message);
		};

		bugeye::subtest("Sub-test for MonoAlpha") = [&] {
			cipher = std::unique_ptr<Crypt>(new MonoAlpha(message));
			cipher->Encrypt();
			IS(cipher->Decrypt(), message);
		};
	}
};
