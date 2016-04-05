// LABUnittest.cpp : Defines the entry point for the console application.
//
#include "StdAfx.h"
#include "../LucidApplicationBuilder/condat.h"

#include <cppunit/plugin/TestPlugIn.h>

char workDir[WORK_DIR_SIZE];
long int ConData::uniqueidgenerator=0;

// Implements all the plug-in stuffs, WinMain...
CPPUNIT_PLUGIN_IMPLEMENT();

