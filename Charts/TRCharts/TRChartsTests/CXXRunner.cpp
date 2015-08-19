/*******************************************************************************
 * Copyright 2015 Thomson Reuters
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *******************************************************************************/
/* Generated file, do not edit */

#ifndef CXXTEST_RUNNING
#define CXXTEST_RUNNING
#endif

#define _CXXTEST_HAVE_STD
#include <cxxtest/TestListener.h>
#include <cxxtest/TestTracker.h>
#include <cxxtest/TestRunner.h>
#include <cxxtest/RealDescriptions.h>
#include <cxxtest/TestMain.h>
#include <cxxtest/ErrorPrinter.h>

int runCXXTests( int argc, char *argv[] ) {
 int status;
    CxxTest::ErrorPrinter tmp;
    CxxTest::RealWorldDescription::_worldName = "cxxtest";
    status = CxxTest::Main< CxxTest::ErrorPrinter >( tmp, argc, argv );
    return status;
}
bool suite_Charts_Test_UtilsTests_init = false;
#include <TRChartsTests/Impl/UtilsTests.hpp>

static Charts::Test::UtilsTests suite_Charts_Test_UtilsTests;

static CxxTest::List Tests_Charts_Test_UtilsTests = { 0, 0 };
CxxTest::StaticSuiteDescription suiteDescription_Charts_Test_UtilsTests( "TRCharts/TRChartsTests/Impl/UtilsTests.hpp", 16, "Charts::Test::UtilsTests", suite_Charts_Test_UtilsTests, Tests_Charts_Test_UtilsTests );

static class TestDescription_suite_Charts_Test_UtilsTests_testFormatDate : public CxxTest::RealTestDescription {
public:
 TestDescription_suite_Charts_Test_UtilsTests_testFormatDate() : CxxTest::RealTestDescription( Tests_Charts_Test_UtilsTests, suiteDescription_Charts_Test_UtilsTests, 19, "testFormatDate" ) {}
 void runTest() { suite_Charts_Test_UtilsTests.testFormatDate(); }
} testDescription_suite_Charts_Test_UtilsTests_testFormatDate;

#include <cxxtest/Root.cpp>
const char* CxxTest::RealWorldDescription::_worldName = "cxxtest";
