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

#include <testngpp/AssertionFailure.h>

TESTNGPP_NS_START

//////////////////////////////////////////////////////////
AssertionFailure::AssertionFailure(const std::string& file
   , unsigned int line, const std::string& msg)
	: fileName(file), lineNumber(line), errMsg(msg)
{}

//////////////////////////////////////////////////////////
AssertionFailure::~AssertionFailure()
{}

//////////////////////////////////////////////////////////
bool operator==(const AssertionFailure& lhs, const AssertionFailure& rhs) 
{
   return lhs.getFileName() == rhs.getFileName() &&
          lhs.getLineOfFile() == rhs.getLineOfFile() &&
          lhs.what() == rhs.what();
}
//////////////////////////////////////////////////////////
const std::string& AssertionFailure::getFileName() const
{
   return fileName;
}

//////////////////////////////////////////////////////////
unsigned int AssertionFailure::getLineOfFile() const
{
   return lineNumber;
}

//////////////////////////////////////////////////////////
const std::string& AssertionFailure::what() const
{
	return errMsg;
}

//////////////////////////////////////////////////////////

TESTNGPP_NS_END

