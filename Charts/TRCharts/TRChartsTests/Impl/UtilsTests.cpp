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

#include <TRChartsTests/Impl/UtilsTests.hpp>

#include <TRCharts/Impl/Utils.hpp>

#include <iostream>

void Charts::Test::UtilsTests::testFormatDate(void)
{
    const std::string expected = "06 Feb 2012 00:55:00";
    tm time{};
    time.tm_mon = 1;
    time.tm_mday = 6;
    time.tm_year = 2012 - 1900;
    time.tm_min = 55;
    const std::string actual = Utils::formatDate(time, "%d %b %Y %H:%M:%S");
    TS_ASSERT_EQUALS(expected, actual);
}