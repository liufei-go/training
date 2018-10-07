#!/usr/bin/env python2

# This code aims to optimze C++ code

import sys

#########################################################
# Declare all constants below
NA = "N.A."
#########################################################

def get_file_extension(filename):
    arr = filename.split(".")
    if len(arr) != 2:
        print "Error: invalid filename - " + filename
        return NA
    return "." + arr[1]

# Open input files
if len(sys.argv) != 3:
    print "Error: must include 2 files"
    print len(sys.argv)
    sys.exit()

firstExt = get_file_extension(sys.argv[1])
secondExt = get_file_extension(sys.argv[2])

if (firstExt == ".h" and secondExt == ".cpp"):
    hName = sys.argv[1]
    cppName = sys.argv[2]
elif (firstExt == ".cpp" and secondExt == ".h"):
    hName = sys.argv[2]
    cppName = sys.argv[1]
else:
    print "Error: must include a .h file and .cpp file"
    sys.exit()

hf = open(hName, "r")
cppf = open(cppName, "r")
hfNew = open(hName[0:-2] + "_new.h", "w")
hfNew = open(cppName[0:-4] + "_new.cpp", "w")

hfContents = hf.read()
# print hfContents
