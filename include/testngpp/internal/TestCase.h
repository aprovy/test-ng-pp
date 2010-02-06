/**
    TestNG++ is a practical, easy-to-use C/C++ xUnit framework.
    Copyright (C) <2009>  <Arthur Yuan: arthur.ii.yuan@gmail.com>

    TestNG++ is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    TestNG++ is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with TestNG++.  If not, see <http://www.gnu.org/licenses/>.
**/

#ifndef __TESTNGPP_TEST_CASE_H
#define __TESTNGPP_TEST_CASE_H

#include <testngpp/testngpp.h>
#include <string>

#include <testngpp/internal/TestCaseInfoReader.h>
#include <testngpp/internal/NameMatcher.h>

TESTNGPP_NS_START

struct TestFixture;

struct TestCase
   : public TestCaseInfoReader
{
	TestCase( const std::string& nameOfCase
           , const std::string& nameOfFixture
           , TESTNGPP_NS::TestCase* testcase
           , const std::string& file
           , unsigned int line)
		: name(nameOfCase)
      , fixtureName(nameOfFixture)
      , depends(testcase)
      , fileName(file)
      , lineOfFile(line)
   {}

	virtual ~TestCase() {}

	const std::string& getName() const
	{ return name; }

	const std::string& getNameOfFixture() const
	{ return fixtureName; }

   TESTNGPP_NS::TestCase* 
   getDependedTestCase() const
   { return depends; }

	const std::string& getFileName() const
	{ return fileName; }

	const unsigned int getLineOfFile() const
	{ return lineOfFile; }

   virtual TESTNGPP_NS::TestFixture* getFixture() const = 0;

   virtual void setUp(TESTNGPP_NS::TestFixture* fixture = 0) = 0;
   virtual void tearDown() = 0;
   virtual void run(bool runDepends=false) = 0;

   virtual bool hasTags() const { return false; }

   virtual bool tagsMatch(const NameMatcher*) const { return false; }

   void runDependedTestCase()
   {
      if(depends == 0)
         return;

      depends->setUp(getFixture());
      depends->run(true);
   }

private:
	std::string name;
	std::string fixtureName;
   TESTNGPP_NS::TestCase* depends;
   std::string fileName;
	unsigned int lineOfFile;
};

TESTNGPP_NS_END

#endif
