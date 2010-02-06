#ifndef __TESTNGPP_POSIX_FN_MATCHER_H
#define __TESTNGPP_POSIX_FN_MATCHER_H

#include <testngpp/testngpp.h>

#include <testngpp/internal/NameMatcher.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////
struct PosixFNMatcher
   : public NameMatcher
{
   PosixFNMatcher(const std::string& namePattern);

   bool matches(const std::string& name) const;

private:

   std::string pattern;
};

////////////////////////////////////////////////////

TESTNGPP_NS_END

#endif
