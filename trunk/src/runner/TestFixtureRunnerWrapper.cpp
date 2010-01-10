
#include <testngpp/Error.h>
#include <testngpp/ExceptionKeywords.h>

#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestFixtureDesc.h>

#include <testngpp/runner/TestFixtureRunnerWrapper.h>
#include <testngpp/runner/TestFixtureRunner.h>
#include <testngpp/runner/TestFixtureResultCollector.h>
#include <testngpp/runner/InternalError.h>


TESTNGPP_NS_START

/////////////////////////////////////////////////////////////////
TestFixtureRunnerWrapper::TestFixtureRunnerWrapper(TestFixtureRunner* runner)
	: fixtureRunner(runner)
{
}

/////////////////////////////////////////////////////////////////
TestFixtureRunnerWrapper::~TestFixtureRunnerWrapper()
{
    delete fixtureRunner;
}

/////////////////////////////////////////////////////////////////
void TestFixtureRunnerWrapper::run(TestFixtureDesc* desc
     , TestFixtureResultCollector* collector
     , const TestCaseFilter* filter)
{
   collector->startTestFixture(desc);

   __TESTNGPP_TRY
   {
      fixtureRunner->run(desc, collector, filter);
   }
   __TESTNGPP_CATCH(Error& e)
   {
      collector->addFixtureError(desc, e.what());
   }
   __TESTNGPP_CATCH_ALL
   {
      collector->addFixtureError(desc, "Unknown Error");
   }
   __TESTNGPP_END_TRY

   collector->endTestFixture(desc);
}

TESTNGPP_NS_END
