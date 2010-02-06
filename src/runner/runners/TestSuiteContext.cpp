
#include <vector>

#include <testngpp/Error.h>
#include <testngpp/ExceptionKeywords.h>

#include <testngpp/internal/TestSuiteDesc.h>

#include <testngpp/runner/TestSuiteLoader.h>
#include <testngpp/runner/TestResultCollector.h>
#include <testngpp/runner/TagsFilters.h>
#include <testngpp/runner/TestFilter.h>
#include <testngpp/runner/TestFixtureContext.h>
#include <testngpp/runner/TestSuiteDescEntryNameGetter.h>

#include <testngpp/runner/TestSuiteContext.h>
#include <testngpp/runner/InternalError.h>
 
TESTNGPP_NS_START
 
/////////////////////////////////////////////////////////////////
namespace
{
   const std::string testngppTestSuiteDescGetter("___testngpp_test_suite_desc_getter");
}

/////////////////////////////////////////////////////////////////

struct TestSuiteContextImpl
   : public TestSuiteDescEntryNameGetter
{
   TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter);

   ~TestSuiteContextImpl();

   std::string getDescEntryName() const
   { return testngppTestSuiteDescGetter; }

private:

   void load( const std::string& path );
   void loadFixtures( TagsFilters* tagsFilter 
                    , const TestFilter* filter);

   void unloadFixtures();

private:

   TestSuiteLoader* suiteLoader; // Y
   TestResultCollector* resultCollector; //X
public:

   std::vector<TestFixtureContext*> fixtures;
   TestSuiteDesc* suite; //X
};

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::
TestSuiteContextImpl
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter)
      : suiteLoader(loader)
      , resultCollector(collector)
{
   load(path);
   loadFixtures(tagsFilter, filter);
}

/////////////////////////////////////////////////////////////////
TestSuiteContextImpl::
~TestSuiteContextImpl()
{
   unloadFixtures();
   suiteLoader->unload();
   delete suiteLoader;
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
loadFixtures
   ( TagsFilters* tagsFilter 
   , const TestFilter* filter)
{
   for(unsigned int i=0; i<suite->getNumberOfTestFixtures(); i++)
   {
      TestFixtureDesc* fixture = suite->getTestFixture(i);
      if(filter->isFixtureMatch((const TestFixtureInfoReader*)fixture))
      {
         TestFixtureContext* fixtureContext = \
            new TestFixtureContext(fixture, tagsFilter);

         fixtures.push_back(fixtureContext);
      }
   }
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
unloadFixtures()
{
   std::vector<TestFixtureContext*>::iterator i = \
      fixtures.begin();

   for(; i != fixtures.end(); i++)
   {
      delete (*i);
   }

   fixtures.clear();
}

/////////////////////////////////////////////////////////////////
void
TestSuiteContextImpl::
load( const std::string& path )
{
   const StringList searchingPaths;

   __TESTNGPP_TRY
   {
      suite = suiteLoader->load(searchingPaths, path, this);
   }
   __TESTNGPP_CATCH(std::exception& e)
   {
      resultCollector->addError("test suite \"" + path + "\" can't be loaded : " + e.what());
   }
   __TESTNGPP_END_TRY
}

/////////////////////////////////////////////////////////////////
TestSuiteDesc* 
TestSuiteContext::
getSuite() const
{
   return This->suite;
}

/////////////////////////////////////////////////////////////////
unsigned int 
TestSuiteContext::
numberOfFixtures() const
{
   return This->fixtures.size();
}

/////////////////////////////////////////////////////////////////
TestFixtureContext* 
TestSuiteContext::
getFixture(unsigned int index) const
{
   if(index >= This->fixtures.size())
   {
      TESTNGPP_INTERNAL_ERROR(2017);
   }

   return This->fixtures[index];
}

/////////////////////////////////////////////////////////////////
TestSuiteContext::
TestSuiteContext
      ( TestSuiteLoader* loader
      , const std::string& path
      , TestResultCollector* collector
      , TagsFilters* tagsFilter
      , const TestFilter* filter
      )
      : This( new TestSuiteContextImpl
               ( loader
               , path
               , collector
               , tagsFilter
               , filter)
      )
{
}
            
/////////////////////////////////////////////////////////////////
TestSuiteContext::
~TestSuiteContext()
{
   delete This;
}

/////////////////////////////////////////////////////////////////
TESTNGPP_NS_END
