#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <vector>
#include <set>
#include <map>

// operator overloads and procedures for debug purposes
template<typename T>
std::ostream& operator<<(std::ostream &os, const std::vector<T> &v) {
	for (const T &x : v) {
		os << x << ' ';
	}
	return os;
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

void printMaps(const std::map<char, char>& first, const std::map<char, char>& second) {
	for (auto fit = first.begin(), sit = second.begin();
		fit != first.end() || sit != second.end();
		++fit, ++sit) {
		std::cout << fit->first << " -> " << fit->second << '\t';
		std::cout << sit->first << " -> " << sit->second << '\n';
	}
}

#endif