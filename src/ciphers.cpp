#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>

#include <Crypt/ciphers.hpp>

// member definitions for Crypt
Crypt::Crypt() : message("") {
	// std::cout << "Constructing Crypt with no message.\n";
}
Crypt::Crypt(const std::string &message) : message(message) {
	// std::cout << "Constructing Crypt with message: " << message << '\n';
}
Crypt::~Crypt() {
	// std::cout << "Destroying Crypt...\n";
}

// member definitions for CaesarCipher
const std::array<char, 26> CaesarCipher::alphabets = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};
unsigned int CaesarCipher::getIdx(const char &c) {
	for (unsigned int i = 0; i < alphabets.size(); ++i) {
		if (alphabets[i] == c) {
			return i;
		}
	}
	return 0;
}
CaesarCipher::CaesarCipher() : Crypt() {}
CaesarCipher::CaesarCipher(const std::string &message) : Crypt(message) {}
CaesarCipher::~CaesarCipher() {
	// std::cout << "Destroying CaesarCipher...\n";
}
std::string CaesarCipher::Encrypt() {
	if (message == "") {
		return "No message to encrypt!";
	}
	for (char& c : message) {
		if (std::binary_search(alphabets.begin(), alphabets.end(), c)) {
			c = alphabets[(getIdx(c) + 3) % alphabets.size()];
		}
	}
	return message;
}
std::string CaesarCipher::Decrypt() {
	if (message == "") {
		return "No message to decrypt!";
	}
	int idx;
	for (char& c : message) {
		if (std::binary_search(alphabets.begin(), alphabets.end(), c)) {
			idx = getIdx(c) - 3;
			c = alphabets[idx < 0 ? alphabets.size() + idx : idx];
		}
	}
	return message;
}

// member definitions for CaesarCipherExt
CaesarCipherExt::CaesarCipherExt() : CaesarCipher(), key(1u) {
	// std::cout << "Constructing CaesarCipherExt with key: " << key << '\n';
}
CaesarCipherExt::CaesarCipherExt(const std::string &message, unsigned int key)
: CaesarCipher(message), key(key) {
	// std::cout << "Constructing CaesarCipherExt with key: " << key << '\n';
}
CaesarCipherExt::~CaesarCipherExt() {
	// std::cout << "Destroying CaesarCipherExt...\n";
}
std::string CaesarCipherExt::Encrypt() {
	if (message == "") {
		return "No message to encrypt!";
	}
	for (char& c : message) {
		if (std::binary_search(alphabets.begin(), alphabets.end(), c)) {
			c = alphabets[(getIdx(c) + key) % alphabets.size()];
		}
	}
	return message;
}
std::string CaesarCipherExt::Decrypt() {
	if (message == "") {
		return "No message to decrypt!";
	}
	int idx;
	for (char& c : message) {
		if (std::binary_search(alphabets.begin(), alphabets.end(), c)) {
			idx = getIdx(c) - key;
			c = alphabets[idx < 0 ? alphabets.size() + idx : idx];
		}
	}
	return message;
}

// operator overloads for debug purposes
template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
	for (const T &x : v) {
		os << x << ' ';
	}
	return os;
}

// member definitions for RailFence
void RailFence::constructFences() {
	for (unsigned int i = 0; i < message.size(); ++i) {
		if (i % 2 == 0) {
			upperFence.push_back(message[i]);
		}
		else {
			lowerFence.push_back(message[i]);
		}
	}
}
RailFence::RailFence() : Crypt() {}
RailFence::RailFence(const std::string &message) : Crypt(message) {
	constructFences();
}
RailFence::~RailFence() {
	// std::cout << "Destroying RailFence...\n";
}
void RailFence::setMessage(const std::string &message) {
	this->message = message;
	constructFences();
}
std::string RailFence::Encrypt() {
	if (message == "") {
		return "No message to encrypt!";
	}
	std::string newMessage;
	for (const char &c : upperFence) {
		newMessage.push_back(c);
	}
	for (const char &c : lowerFence) {
		newMessage.push_back(c);
	}
	message = newMessage;
	return message;
}
std::string RailFence::Decrypt() {
	if (message == "") {
		return "No message to decrypt!";
	}
	std::string newMessage;
	unsigned int uFSize = upperFence.size(), lFSize = lowerFence.size();
	bool upperFenceGreater = uFSize > lFSize;
	unsigned int size = upperFenceGreater ? lFSize : uFSize;
	for (unsigned int i = 0; i < size; ++i) {
		newMessage.push_back(upperFence[i]);
		newMessage.push_back(lowerFence[i]);
	}
	newMessage.push_back(upperFenceGreater ? upperFence[uFSize - 1] : lowerFence[lFSize - 1]);
	message = newMessage;
	return message;
}

template<typename T>
std::ostream& operator<<(std::ostream &os, const std::set<T> &s) {
	std::for_each(s.begin(), s.end(), [&](const T &x) {
		os << x << ' ';
	});
	return os;
}

template<typename key, typename value>
std::ostream& operator<<(std::ostream &os, const std::map<key, value> &map) {
	for (auto it = map.begin(); it != map.end(); ++it) {
		os << it->first << " -> " << it->second << '\n';
	}
	return os;
}

// member definitions for MonoAlpha
const std::set<char> MonoAlpha::alphabets = {
	'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
	'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'
};
void MonoAlpha::constructMaps() {
	using clock = std::chrono::system_clock;
	unsigned seed = clock::now().time_since_epoch().count();
	std::default_random_engine generator(seed);
	std::set<char> assignedChars;
	for (const char& c : alphabets) {
		const std::set<char> currentChar = { c };
		std::vector<char> difference(alphabets.size());
		auto it = std::set_difference(
			alphabets.begin(), alphabets.end(),
			currentChar.begin(), currentChar.end(),
			difference.begin()
		);
		difference.resize(it - difference.begin());
		std::uniform_int_distribution<int> distribution(0, difference.size() - 1);
		char replacement = difference[distribution(generator)];
		if (charMap.size() > 0) {
			while (assignedChars.count(replacement) != 0) {
				replacement = difference[distribution(generator)];
			}
		}
		charMap[c] = replacement;
		reverseCharMap[replacement] = c;
		assignedChars.insert(replacement);
	}
}
MonoAlpha::MonoAlpha() : Crypt() {}
MonoAlpha::MonoAlpha(const std::string &message) : Crypt(message) {
	constructMaps();
}
MonoAlpha::~MonoAlpha() {
	// std::cout << "Destroying MonoAlpha...\n";
}
void MonoAlpha::setMessage(const std::string &message) {
	this->message = message;
	constructMaps();
}
std::string MonoAlpha::Encrypt() {
	if (message == "") {
		return "No message to encrypt!";
	}
	for (char &c : message) {
		if (charMap.count(c) != 0) {
			c = charMap.find(c)->second;
		}
	}
	return message;
}
std::string MonoAlpha::Decrypt() {
	if (message == "") {
		return "No message to decrypt!";
	}
	for (char& c : message) {
		if (charMap.count(c) != 0) {
			c = reverseCharMap.find(c)->second;
		}
	}
	return message;
}
