#!/bin/sh

appledoc --keep-undocumented-objects --repeat-first-par no --keep-undocumented-members --create-html --keep-intermediate-files --ignore ".m" --ignore ".mm" --project-name "TRCharts" --project-company "Thomson Reuters" --company-id "com.thomsonreuters" --output ./Documentation/ObjC TRChartsObjc/TRChartsObjC