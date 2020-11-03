#include "kwic.hpp"
#include "word.hpp"
//#include <istream>
#include <iostream>
#include <vector>
#include <algorithm>
namespace text {
	using linesType = std::vector<Word>;
	std::vector<linesType> readInput(std::istream& in, std::ostream& out) {
		std::string oneLine{};
		std::vector<Word> wordsFromOneLine{};
		std::vector<linesType> allLines{};
		while (std::getline(in, oneLine)) {
			std::istringstream s(oneLine);
			wordsFromOneLine.insert(wordsFromOneLine.end(),
				std::istream_iterator<std::string>(s),
				std::istream_iterator<std::string>());
			allLines.push_back(wordsFromOneLine);
			wordsFromOneLine.clear();
		}
		return allLines;
	}

	std::vector<linesType> createMutations(std::vector<linesType>& allLines) {
		std::vector<std::vector<Word>> mutations{};
		std::for_each(allLines.begin(), allLines.end(), [&mutations](linesType& linesType) {
			for (unsigned int i = 0; i < linesType.size(); i++) {
				//std::rotate(lines.begin(), lines.begin() + 1, lines.end());
				linesType.push_back(linesType[0]);
				linesType.erase(linesType.begin());
				mutations.push_back(linesType);
			}
			});
		return mutations;
	}

	void printMutations(std::vector<linesType>& mutations, std::ostream& out) {
		std::for_each(mutations.begin(), mutations.end(), [&out](const linesType& linesType) {
			std::for_each(linesType.begin(), linesType.end(), [&out](const std::string& str) {
				out << str << " ";
				});
			out << "\n";
			});
	}

	void kwic(std::istream& in, std::ostream& out) {
		std::vector<linesType> allLines = readInput(in, out);

		std::vector<linesType> mutations = createMutations(allLines);

		std::sort(mutations.begin(), mutations.end());

		printMutations(mutations, out);
	}
}

