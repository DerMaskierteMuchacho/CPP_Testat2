#include "../testatLib/word.hpp"
#include "../testatLib/kwic.hpp"

#include "cute/cute.h"
#include "cute/ide_listener.h"
#include "cute/xml_listener.h"
#include "cute/cute_runner.h"
#include <iostream>
#include <sstream>

using text::Word;
using text::kwic;

std::string testKwic(std::istream& input)
{
	std::ostringstream output{};
	text::kwic(input, output);
	return output.str();
}

void testKwicSimple()
{
	std::istringstream input{ "Test function you must" };
	auto res = testKwic(input);
	ASSERT_EQUAL("function you must Test \nmust Test function you \nTest function you must \nyou must Test function \n", res);
}

void testKwicSampleTest()
{
	std::istringstream input{ "this is a test" };
	auto res = testKwic(input);
	ASSERT_EQUAL("a test this is \nis a test this \ntest this is a \nthis is a test \n", res);
}

void testKwicSampleTest2()
{
	std::istringstream input{ "this is another test" };
	auto res = testKwic(input);
	ASSERT_EQUAL("another test this is \nis another test this \ntest this is another \nthis is another test \n", res);
}

void testWordSimpleInput() {
	std::istringstream input{ "simpleInput" };
	std::ostringstream output{};
	Word w{};
	input >> w;
	output << w;
	ASSERT_EQUAL("simpleInput", output.str());
}

void testWordDefault() {
	std::ostringstream output{};
	Word const w{};
	output << w;
	ASSERT_EQUAL("", output.str());
}

void testWordNoneInput() {
	std::istringstream input{};
	std::ostringstream output{};
	Word w{};
	output << w;
	ASSERT_EQUAL((bool)input, true);
	ASSERT_EQUAL("", output.str());
}

void testWordEmptyConstructor() {
	ASSERT_THROWS(Word w{ "" }, std::invalid_argument);
}

void testWordComplexInput() {
	std::istringstream input{ "compl33tely ~ weird !!?!! 4matted in_put" };
	std::ostringstream output{};
	Word w{};
	input >> w;
	output << w;
	ASSERT_EQUAL("compl", output.str());
	input >> w;
	output << w;
	ASSERT_EQUAL("compltely", output.str());
	input >> w;
	output << w;
	ASSERT_EQUAL("compltelyweird", output.str());
	input >> w;
	output << w;
	ASSERT_EQUAL("compltelyweirdmatted", output.str());
	input >> w;
	output << w;
	ASSERT_EQUAL("compltelyweirdmattedin", output.str());
	input >> w;
	output << w;
	ASSERT_EQUAL("compltelyweirdmattedinput", output.str());
	input >> w;
	output << w;
	ASSERT_EQUAL("compltelyweirdmattedinputput", output.str());
}

void testWordEqual() {
	Word const w1{ "t" };
	Word const w2{ "t" };
	ASSERT_EQUAL(true, w1 == w2);
}

void testWordNotEqual() {
	Word const w1{ "t" };
	Word const w2{ "b" };
	ASSERT_EQUAL(true, w1 != w2);
}

void testWordLower() {
	Word const w1{ "a" };
	Word const w2{ "B" };
	ASSERT_EQUAL(true, w1 < w2);
}

void testWordLowerEqual1() {
	Word const w1{ "a" };
	Word const w2{ "A" };
	ASSERT_EQUAL(true, w1 <= w2);
}

void testWordLowerEqual2() {
	Word const w1{ "a" };
	Word const w2{ "B" };
	ASSERT_EQUAL(true, w1 <= w2);
}

void testWordGreater() {
	Word const w1{ "B" };
	Word const w2{ "a" };
	ASSERT_EQUAL(true, w1 > w2);
}

void testWordGreaterEqual1() {
	Word const w1{ "A" };
	Word const w2{ "a" };
	ASSERT_EQUAL(true, w1 >= w2);
}

void testWordGreaterEqual2() {
	Word const w1{ "B" };
	Word const w2{ "a" };
	ASSERT_EQUAL(true, w1 >= w2);
}

void testKWICEmpty() {
	std::istringstream input{ "" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("", output.str());
}

void testKWICOneLineOneWord() {
	std::istringstream input{ "a" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("a \n", output.str());
}

void testKWICOneLineTwoWord() {
	std::istringstream input{ "a b" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("a b \nb a \n", output.str());
}

void testKWICTwoLineOneWord() {
	std::istringstream input{ "a\nb" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("a \nb \n", output.str());
}

void testKWICTwoLineOneWordSort() {
	std::istringstream input{ "b\na" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("a \nb \n", output.str());
}

void testKWICTwoLineTwoWord() {
	std::istringstream input{ "a c\nb d" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("a c \nb d \nc a \nd b \n", output.str());
}

void testKWICTwoLineTwoWordSorted() {
	std::istringstream input{ "a b\nc d" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("a b \nb a \nc d \nd c \n", output.str());
}

void testKWICTwoLineTwoWordComplex() {
	std::istringstream input{ "ab bb\nca ba" };
	std::ostringstream output{};
	kwic(input, output);
	ASSERT_EQUAL("ab bb \nba ca \nbb ab \nca ba \n", output.str());
}

bool runAllTests(int argc, char const* argv[]) {
	cute::suite s{};
	s.push_back(CUTE(testKwicSimple));
	s.push_back(CUTE(testKwicSampleTest));
	s.push_back(CUTE(testKwicSampleTest2));
	s.push_back(CUTE(testWordSimpleInput));
	s.push_back(CUTE(testWordDefault));
	s.push_back(CUTE(testWordNoneInput));
	s.push_back(CUTE(testWordEmptyConstructor));
	s.push_back(CUTE(testWordComplexInput));
	s.push_back(CUTE(testWordEqual));
	s.push_back(CUTE(testWordNotEqual));
	s.push_back(CUTE(testWordLower));
	s.push_back(CUTE(testWordLowerEqual1));
	s.push_back(CUTE(testWordLowerEqual2));
	s.push_back(CUTE(testWordGreater));
	s.push_back(CUTE(testWordGreaterEqual1));
	s.push_back(CUTE(testWordGreaterEqual2));
	s.push_back(CUTE(testKWICEmpty));
	s.push_back(CUTE(testKWICOneLineOneWord));
	s.push_back(CUTE(testKWICOneLineTwoWord));
	s.push_back(CUTE(testKWICTwoLineOneWord));
	s.push_back(CUTE(testKWICTwoLineOneWordSort));
	s.push_back(CUTE(testKWICTwoLineTwoWord));
	s.push_back(CUTE(testKWICTwoLineTwoWordSorted));
	s.push_back(CUTE(testKWICTwoLineTwoWordComplex));
	cute::xml_file_opener xmlfile(argc, argv);
	cute::xml_listener<cute::ide_listener<>> lis(xmlfile.out);
	auto const runner = cute::makeRunner(lis, argc, argv);
	bool const success = runner(s, "AllTests");
	return success;
}

int main(int argc, char const* argv[]) {
	int exitState = runAllTests(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
	if (exitState == EXIT_SUCCESS) {
		std::cout << "!!!All tests passed!!!";
	}
	else {
		std::cout << "--- Some tests failed---";
	}
	return exitState;
}