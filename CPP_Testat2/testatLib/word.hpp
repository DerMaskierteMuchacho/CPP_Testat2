#ifndef WORD_HPP_
#define WORD_HPP_

#include <string>
#include <sstream>

namespace text {
	class Word {
		std::string w{ };

		bool isIllegalString(std::string const) const;

	public:
		explicit Word();
		explicit Word(std::string const);
		bool operator==(Word const&) const;
		bool operator!=(Word const&) const;
		bool operator<(Word const&) const;
		bool operator>(Word const&) const;
		bool operator<=(Word const&) const;
		bool operator>=(Word const&) const;

		//friend std::istringstream& operator>>(std::istringstream&, Word&);
		friend std::istream& operator>>(std::istream&, Word&);
		friend std::ostream& operator<<(std::ostream&, Word const&);
		operator std::string() const { return w; };
		//std::string ToString() { return w; };

	};
}

#endif /* WORD_HPP_ */
