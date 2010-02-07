
#include <testngpp/runner/TaggableObjFilter.h>
#include <testngpp/runner/GeneralTagsFilter.h>
#include <testngpp/internal/Taggable.h>
#include <testngpp/runner/NameMatcher.h>
#include <testngpp/runner/InternalError.h>

TESTNGPP_NS_START

////////////////////////////////////////////////////////
struct GeneralTagsFilterImpl
{
   GeneralTagsFilterImpl(NameMatcher* matcher);

   ~GeneralTagsFilterImpl();
   NameMatcher* tagsMatcher;
};

////////////////////////////////////////////////////////
GeneralTagsFilterImpl::
GeneralTagsFilterImpl(NameMatcher* matcher)
   : tagsMatcher(matcher)
{
}
////////////////////////////////////////////////////////
GeneralTagsFilterImpl::~GeneralTagsFilterImpl()
{
   delete tagsMatcher;
}
////////////////////////////////////////////////////////
GeneralTagsFilter::
GeneralTagsFilter(NameMatcher* matcher)
   : This(new GeneralTagsFilterImpl(matcher))
{
}

////////////////////////////////////////////////////////
GeneralTagsFilter::~GeneralTagsFilter()
{
   delete This;
}

////////////////////////////////////////////////////
bool GeneralTagsFilter::
matches(const Taggable* obj) const
{
   if(obj == 0 || This->tagsMatcher)
   {
      TESTNGPP_INTERNAL_ERROR(2016);
   }
   
   const char** tags = obj->getTags();
   for(unsigned int i=0; i<obj->numberOfTags(); i++)
   {
      if(This->tagsMatcher->matches(tags[i]))
      {
         return true;
      }
   }

   return false;
}

////////////////////////////////////////////////////////
void GeneralTagsFilter::
dump() const
{
   This->tagsMatcher->dump();
}

TESTNGPP_NS_END