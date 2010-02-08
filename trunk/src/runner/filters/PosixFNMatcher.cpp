

#include <iostream>

#ifndef _MSC_VER
#include <fnmatch.h>
#else
#include "Win32Fnmatch.h"
#endif

#include <testngpp/runner/PosixFNMatcher.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
PosixFNMatcher::
PosixFNMatcher(const std::string& namePattern)
   : pattern(namePattern)
{
}

////////////////////////////////////////////////////
namespace
{
   const int flags = FNM_CASEFOLD; 
}

////////////////////////////////////////////////////
bool PosixFNMatcher::
matches(const std::string& name) const
{
  if(name.size() == 0)
  {
     return false;
  }

  return ::fnmatch(pattern.c_str(), name.c_str(), flags) == 0;
}

////////////////////////////////////////////////////////

void PosixFNMatcher::
dump() const
{
   std::cout << " " << pattern << " ";
   std::cout.flush();
}

TESTNGPP_NS_END