#include "word.hpp"

#include <cctype>
#include <string>
#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iostream>

text::Word::Word() {}

text::Word::Word(std::string const value) : w{ value } {
	if (isIllegalString(w))
		throw std::invalid_argument{ "invalid word" };
}
bool text::Word::isIllegalString(std::string const valueStr) const {
	return valueStr == "" || std::count_if(valueStr.begin(), valueStr.end(), [](char const c) {return !static_cast<bool>(std::isalpha(c)); });
}
bool text::Word::operator==(Word const& rhs) const {
	return std::equal(w.begin(), w.end(), rhs.w.begin(), rhs.w.end(), [](char c1, char c2) {
			return std::tolower(c1) == std::tolower(c2); 
			});
}
bool text::Word::operator<(Word const& rhs) const {
	return std::lexicographical_compare(w.begin(), w.end(), rhs.w.begin(), rhs.w.end(), [](char c1, char c2) {
		return std::tolower(c1) < std::tolower(c2); 
		});
}
bool text::Word::operator!=(Word const& rhs) const {
	return !(*this == rhs);
}
bool text::Word::operator>(Word const& rhs) const {
	return !(*this == rhs) && !(*this < rhs);
}
bool text::Word::operator<=(Word const& rhs) const {
	return !(*this > rhs);
}
bool text::Word::operator>=(Word const& rhs) const {
	return !(*this < rhs);
}

namespace text {
	std::istream& operator>>(std::istream& is, Word& word) {
		std::istreambuf_iterator<char> inBegin{ is };
		std::istreambuf_iterator<char> inEnd{};
		std::string wordString{};
		while (inBegin != inEnd && !isalpha(*inBegin)) {
			inBegin++;
		}
		if (inBegin == inEnd) {
			is.setstate(std::istream::failbit, true);
			return is;
		}
		while (inBegin != inEnd && isalpha(*inBegin)) {
			wordString += *inBegin;
			inBegin++;
		}
		word.w = wordString;
		return is;
	}
	/*std::istringstream& operator>>(std::istringstream& is, Word& word) {
		std::istreambuf_iterator<char> inBegin{ is };
		std::istreambuf_iterator<char> inEnd{};
		std::string wordString{};
		while (inBegin != inEnd && !isalpha(*inBegin)) {
			inBegin++;
		}
		if (inBegin == inEnd) {
			is.setstate(std::istream::failbit, true);
			return is;
		}
		while (inBegin != inEnd && isalpha(*inBegin)) {
			wordString += *inBegin;
			inBegin++;
		}
		word.w = wordString;
		return is;
	}*/
	std::ostream& operator<<(std::ostream& os, Word const& word) {
		os << word.w;
		return os;
	}
}

