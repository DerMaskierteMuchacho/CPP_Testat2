#include "CppUnitTest.h"
#include "../testatLib/word.hpp"
#include "../testatLib/kwic.hpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace testat2Test
{
	TEST_CLASS(testat2Test)
	{
	public:

		TEST_METHOD(TestMethod1)
		{
			Assert::IsTrue(true);
		}
	};
}