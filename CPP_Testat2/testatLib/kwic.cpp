#include "kwic.hpp"
#include "word.hpp"
//#include <istream>
#include <iostream>
#include <vector>
#include <algorithm>
namespace text {
	void kwic(std::istream& in, std::ostream& out) {
		std::string line{};
		std::vector<Word> wordsFromOneLine{};
		std::vector<std::vector<Word>> allLines{};
		while (std::getline(in, line)) {
			std::istringstream s(line);
			wordsFromOneLine.insert(wordsFromOneLine.end(),
				std::istream_iterator<std::string>(s),
				std::istream_iterator<std::string>());
			allLines.push_back(wordsFromOneLine);
			wordsFromOneLine.clear();
		}






		//Test Output
		std::for_each(allLines.begin(), allLines.end(), [&out](const std::vector<Word>& words) {
			std::for_each(words.begin(), words.end(), [&out](const std::string& str) {
				out << str << "\n";
				});
			});
	}
}