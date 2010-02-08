
#ifndef __TESTNGPP_TEST_CASE_RUNNER_RESULT_COLLECTOR_H
#define __TESTNGPP_TEST_CASE_RUNNER_RESULT_COLLECTOR_H

#include <string>
#include <iostream>

#include <testngpp/testngpp.h>

#include <testngpp/runner/TestResultCollector.h>
#include <testngpp/internal/TestSuiteInfoReader.h>
#include <testngpp/internal/TestFixtureInfoReader.h>
#include <testngpp/internal/TestCaseInfoReader.h>

#include <testngpp/AssertionFailure.h>

TESTNGPP_NS_START

struct TestCaseRunnerResultReporter
	: public TestResultCollector
{

	TestCaseRunnerResultReporter(TestCaseResultCollector* caseReporter)
		: reporter(caseReporter)
	{
	}

	~TestCaseRunnerResultReporter()
	{
		delete reporter;
	}

	void addCaseCrash(const TestCaseInfoReader* testcase)
	{
		reporter->addCaseCrash(testcase);
	}

	void addCaseError(const TestCaseInfoReader* testcase, const std::string& msg)
	{
		reporter->addCaseError(testcase, msg);
	}

	void addCaseFailure(const TestCaseInfoReader* testcase, const AssertionFailure& failure)
	{
		reporter->addCaseFailure(testcase, failure);
	}

	void addCaseSkipped(const TestCaseInfoReader* testcase)
	{
		reporter->addCaseSkipped(testcase);
	}

	void startTestCase(const TestCaseInfoReader* testcase)
	{
		reporter->endTestCase(testcase);
	}

    void endTestCase(const TestCaseInfoReader* testcase)
	{
		reporter->endTestCase(testcase);
	}

	//////////////////////////////////////////////////////
	void startTestFixture(TestFixtureInfoReader* fixture)
	{
	}
	void endTestFixture(TestFixtureInfoReader* fixture)
	{
	}

	void addFixtureError(TestFixtureInfoReader* fixture, const std::string& error)
	{
	}
	void addFixtureFailure(TestFixtureInfoReader* fixture, const AssertionFailure& failure) 
	{
		std::cerr << "fixuture failure : " << fixture->getName() 
			<< " : " << failure.what() << std::endl;
	}

	void startTestSuite(TestSuiteInfoReader* suite)
	{
	}
	void endTestSuite(TestSuiteInfoReader* suite) 
	{
	}
	void addSuiteError(TestSuiteInfoReader*, const std::string& error)
	{
		std::cerr << "suite error : " << error << std::endl;
	}

	void startTest() 
	{
	}
	void endTest()
	{
	}

	void addError(const std::string& error)
	{
		std::cerr << "test error : " << error << std::endl;
	}

private:
    TestCaseResultCollector* reporter;
};

TESTNGPP_NS_END

#endif
