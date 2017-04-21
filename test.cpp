#include "stdafx.h"
#include"SearchSigns.h"
#include "ReadFile.h"

using namespace std;
char FNAME[500] =  "C:\\Users\\User\\Documents\\Visual Studio 2010\\Projects\\test\\1.bin";

extern char* GlobalBuf;
extern int _max_size;

datasigns signs;
ID id;
str strvector;



int _tmain(int argc, _TCHAR* argv[])
{ 
	if (argc == 1) 
	{
		GlobalBuf=new char[_Size(FNAME)];
		char * sign="22222222";
		if ( OpenSigned(FNAME))	
		{
#if (F_SEARCH==1||F_SEARCH==4)
			{
				if(vectorSearch(signs,sign))
					cout<<"naideno "<<sign<<endl;
			}
#endif
#if (F_SEARCH==2||F_SEARCH==4)
			{
				if(vector2Search(strvector,id,sign))
					cout<<"naideno "<<sign<<endl; 
			}
#endif
#if (F_SEARCH==3||F_SEARCH==4)
			{
				if (SearchSigns(FNAME,strvector,id, sign))
					cout<<"naideno "<<sign<<endl;
			}
#endif
			delete[] GlobalBuf;

		}
	}
	else
	{
		/*	for ( ; argc != 1; argc--)
		{
		wprintf(L"%s\n", argv[argc - 1]);
		}*/

		if ((wcscmp( argv[1], L"2")) == 0)
		{
			GlobalBuf=new char[_Size(FNAME)];
			char * sign="22222222";
			if ( OpenSigned(FNAME_))	
				if(vector2Search(strvector,id,sign))
					cout<<"naideno "<<sign<<endl; 
		}
		if ((wcscmp( argv[1], L"3")) == 0)
		{	
			GlobalBuf=new char[_Size(FNAME)];
			char * sign="22222222";
			if ( OpenSigned(FNAME))	
			{
				{
					if (SearchSigns(FNAME,strvector,id, sign))
						cout<<"naideno "<<sign<<endl;
				}
			}

		}
		if ((wcscmp( argv[1], L"1")) == 0)
		{	
			GlobalBuf=new char[_Size(FNAME)];
			char * sign="22222222";
			if ( OpenSigned(FNAME_))	
			{
				{
					if (SearchSigns(FNAME,strvector,id, sign))
						cout<<"naideno "<<sign<<endl;
				}
			}

		}
		if (argc>2)
		{
			if ((wcscmp( argv[2],L"5"))==0)
			{
				char* NewFName = new char[1024];
				char *ptr = NewFName;
				cout<<"file \n";
				do {
				*ptr = getchar();
				ptr++;
				} while (*(ptr - 1) != '\n');
				*(ptr - 1) = 0;
				//cin >> NewFName;
				strcpy(FNAME, NewFName);
				delete[] NewFName;
				_tmain(1,argv);
			}
		}
	}
		system("pause");
		return 0;
	}

