#ifndef CIPHERS_HPP
#define CIPHERS_HPP

#include <string>
#include <array>
#include <vector>
#include <set>
#include <map>

// abstract base class with pure virtual methods to be overloaded
// for each type of cipher that inherits from this class
class Crypt {
protected:
	std::string message;  // message string which will be mutated
public:
	Crypt();
	Crypt(const std::string &message);
	virtual ~Crypt();  // for polymorphism (public virtual destructor)
	virtual void setMessage(const std::string &message) {
		this->message = message;
	};

	// pure virtual method declarations, to be overriden
	virtual std::string Encrypt() = 0;
	virtual std::string Decrypt() = 0;
};

// Caesar cipher which moves characters by 3 values
class CaesarCipher : public Crypt {
protected:
	static const std::array<char, 26> alphabets;
	// helper method to get index of a character (all lower case)
	// protected so as to be used by derived class as well
	unsigned int getIdx(const char &c);
public:
	CaesarCipher();
	CaesarCipher(const std::string &message);
	~CaesarCipher();
	std::string Encrypt();
	std::string Decrypt();
};

// extended Caesar cipher which moves characters any given amount of value
class CaesarCipherExt : public CaesarCipher {
protected:
	const unsigned int key;
public:
	CaesarCipherExt();
	CaesarCipherExt(const std::string &message, unsigned int key);
	~CaesarCipherExt();
	std::string Encrypt();
	std::string Decrypt();
};

// Rail fence cipher
class RailFence : public Crypt {
private:
	std::vector<char> upperFence, lowerFence;
	void constructFences();
public:
	RailFence();
	RailFence(const std::string &message);
	~RailFence();
	void setMessage(const std::string &message);
	std::string Encrypt();
	std::string Decrypt();
};

class MonoAlpha : public Crypt {
private:
	static const std::set<char> alphabets;
	std::map<char, char> charMap, reverseCharMap;
	void constructMaps();
public:
	MonoAlpha();
	MonoAlpha(const std::string &message);
	~MonoAlpha();
	void setMessage(const std::string &message);
	std::string Encrypt();
	std::string Decrypt();
};

#endif
