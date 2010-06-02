#!/usr/bin/env python
import re
import sys

# load each line of the schedule
section = "system"
tests = dict()
with open("schedule") as f:
	for line in f:
		if line != '': # skip out empty lines
			# trim off comments and trailing whitespace
			line = re.sub(' *(#.*)$', '', line)
			if line.endswith(':'):
				section = line[:-1]
			else:
				elements = line.split(' ', 1)
				testType = elements[0]
				testName = elements[1]
				if section not in tests:
					section[tests] = []
				section[tests].append((testName, testType))

passes = 0
fails  = 0
xfails = 0
fixes  = 0

def run_test(test):
	return true

for section in tests:
	for test in section:
		if run_test(test[0]):
			if test[1] == 'XFAIL':
				fixes = fixes + 1
			else:
				passes = passes + 1
		else:
			if test[1] == 'XFAIL':
				xfails = xfails + 1
			else:
				fails = fails + 1

print ('%4d tests passed' % passes)
if fails > 0:
	print ('%4d tests failed' % fails)
if xfails > 0:
	print ('%4d expected failures' % xfails)
if passes > 0:
	print ('%4d unexpected passes' % passes)
				
if fails > 0:
	sys.exit(1)

# for each section,
#    for each test,
#       compile the test (it's name.cpp)
#       run it
#    if either fails,
#       if it's XFAIL,
#          add 1 to the XFAIL counter
#       if it's TEST,
#          add 1 to the FAIL counter
#       print the output of stderr and stdout to stderr
#    else,
#       if it's XFAIL,
#          add 1 to the FIX counter
#       else
#          add 1 to the PASS counter

# print the number of tests passed
# print the number of tests failed, if it's nonzero
# print the number of xfails, if it's nonzero
# print the number of fixes, if it's nonzero
# if the FAIL counter is greater than zero,
#   exit with status 1
# else
#   exit with status 0
