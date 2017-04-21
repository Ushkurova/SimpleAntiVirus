#include "stdafx.h"
#include "SearchSigns.h"

using namespace std;
extern char* FNAME;
char* GlobalBuf;
int _max_size=-1;

bool vector2Search(str &strvector, ID &id, char * sign)
{	int i=-1;
	for (auto it = strvector.begin(); it < strvector.end(); it++) 
	{
		if (strstr(sign, *it._Ptr)) 
		{
			return true;
		}
	}
		return false;
}


bool vectorSearch(datasigns &signs, char * sign)
{
	char **ptr_sign = (char**)&signs[0], **end = (char**)signs.end()._Ptr;
	ptr_sign += 2;
	for ( ; ptr_sign < end; ptr_sign += 3) 
	{
		if (strstr(sign, *ptr_sign))
		{
			return true;
		}
	}
		return false;
}
 

bool SearchSigns(const char *FileName,str &strvector, ID &id, char * sign)
{
	
	char* ptr_buf=GlobalBuf;
	char ** ptr_str=(char**)strvector.data();
	char** end = (char**)strvector.end()._Ptr;
	auto itid = id.begin();
	for (; ptr_str < end; ptr_str++, itid++) 
	{	*(int*)ptr_buf = *itid._Ptr;	
		ptr_buf+=4;
		strcpy(ptr_buf,*ptr_str);	
		ptr_buf += strlen(ptr_buf) + 1;
	}
	for (size_t i=0;i<5;++i,ptr_buf++)
		*ptr_buf=0;
	ptr_buf=GlobalBuf;
	ptr_buf+=4;
	for ( ; *ptr_buf!=0;ptr_buf+=strlen(ptr_buf)+5) 
	{
		if (strstr(sign,ptr_buf))
		{
			return true;
		}
	}
	return false;
}

