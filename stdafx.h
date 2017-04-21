// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

struct DataSignFile 
{
	unsigned int ID;
	unsigned int size;
	char *   sign_str;
	friend void operator << (std::ostream &left, DataSignFile &rigth) 
	{
		left << "ID - " << std::setw(4) << rigth.ID <<
		"\tSize - " << std::setw(4) << rigth.size <<
		"\tSign - " << std::setw(10) << rigth.sign_str;
	}
};

typedef std::vector<char> signvector;
typedef std::vector<unsigned int> ID;
typedef std::vector<DataSignFile> datasigns;
typedef std::vector<char*> str;

