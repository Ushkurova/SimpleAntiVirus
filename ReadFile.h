#pragma once
#include "stdafx.h"
#include "SearchSigns.h"

using namespace std;

unsigned int AddSigned(signvector &data,  datasigns &signs, str &strvector, ID &id);
bool OpenSigned(const char *FileName) ;
size_t _Size (const char *FileName);

