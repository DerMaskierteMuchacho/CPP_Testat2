#include "kwic.h"
#include "word.h"
#include <istream>
#include <ostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
namespace text {
	using linesType = std::vector<Word>;
	std::vector<linesType> readInput(std::istream& in, std::ostream& out) {
		std::string oneLine{};
		std::vector<Word> wordsFromOneLine{};
		std::vector<linesType> allLines{};
		while (std::getline(in, oneLine)) {
			std::istringstream s{ oneLine };
			wordsFromOneLine.insert(wordsFromOneLine.end(),
				std::istream_iterator<Word>(s),
				std::istream_iterator<Word>());
			allLines.push_back(wordsFromOneLine);
			wordsFromOneLine.clear();
		}
		return allLines;
	}

	std::vector<linesType> createMutations(std::vector<linesType>& allLines) {
		std::vector<std::vector<Word>> mutations{};
		std::for_each(allLines.begin(), allLines.end(), [&mutations](linesType& linesType) {
			for (unsigned int i = 0; i < linesType.size(); i++) {
				linesType.push_back(linesType[0]);
				linesType.erase(linesType.begin());
				mutations.push_back(linesType);
			}
			});
		return mutations;
	}

	void printMutations(std::vector<linesType>& mutations, std::ostream& out) {
		std::for_each(mutations.begin(), mutations.end(), [&out](const linesType& linesType) {
			std::for_each(linesType.begin(), linesType.end(), [&out](const Word& word) {
				out << word << " ";
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

