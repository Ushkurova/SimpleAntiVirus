#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>


using namespace std;
#define BUFFER_SIZE 1024

const char* FNAME=  "C:\\Users\\User\\Documents\\Visual Studio 2010\\Projects\\test\\1.bin";

#define FNAME_ "C:\\Users\\User\\Documents\\Visual Studio 2010\\Projects\\test\\1.bin"

struct DataSignFile;

typedef std::vector<char> signvector;
typedef std::vector<unsigned int> ID;
typedef std::vector<DataSignFile> datasigns;
typedef std::vector<char*> str;

static datasigns signs;
static ID id;
static str strvector;
int _max_size=-1;
char* GlobalBuf;

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

unsigned int AddSigned(signvector &data,  datasigns &signs, str &strvector, ID &id) 
{
	DataSignFile _data;
	unsigned int _pos = 0;
	do 
	{
		if (_pos + 8 >= data.size()) 
		{
			break;
		}
		_data.ID = data[_pos];
		_data.size = data[_pos + 4];
		if (_max_size<data[_pos + 4])
			_max_size=data[_pos + 4];
		if (_data.size > data.size() - _pos) 
		{
			break;
		}
		if (_data.size > 0) 
		{
			_data.sign_str = new char[_data.size+1];
			memcpy(_data.sign_str, &data[_pos + 8], _data.size);
			_data.sign_str[_data.size] = 0;
			cout << _data;
			cout << endl;
			_pos += _data.size + 8;
			strvector.push_back(_data.sign_str);
			id.push_back(_data.ID);
			signs.push_back(_data);
		}
		else 
		{
			_pos += 8;
		}
	} 
	while (true);
	return _pos;
}

bool vector2Search(str &strvector, ID &id, char * sign)
{	int i=-1;
	for (auto it = strvector.begin(); it < strvector.end(); it++,i++) 
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


bool OpenSigned(const char *FileName) 
{
	signs.clear();
	ifstream file(FileName, std::ios::binary);
	signvector buffer;
	unsigned int count = BUFFER_SIZE, _pos = 0;
	buffer.resize(count);
	while (file.read((char*)&buffer[_pos], count)) 
	{
		_pos = AddSigned(buffer, signs, strvector,id);
		memcpy(buffer.data(), &buffer[_pos], BUFFER_SIZE - _pos);
		_pos = BUFFER_SIZE - _pos;
		count = BUFFER_SIZE - _pos;
	}
	AddSigned(buffer, signs,strvector,id);
	file.close();
	return true;
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
	for ( ; *ptr_buf!=0;ptr_buf+=strlen(ptr_buf)+5) 
	{
		if (strstr(sign, ptr_buf))
		{
			return true;
		}
	}
/*	ofstream fp("C:\\Users\\User\\Documents\\Visual Studio 2010\\Projects\\test\\13.bin", std::ios::binary);
	fp.write(buf,size);
	fp.close();*/
	return false;
}

size_t _Size (const char *FileName)
{
	ifstream file(FileName, std::ios::binary);
	file.seekg(0,ios::end);
	size_t size=file.tellg();
	file.close();
	return size;
}

int _tmain(int argc, _TCHAR* argv[])
{ 
	GlobalBuf=new char[_Size(FNAME_)];
	char * sign="456";
	if ( OpenSigned(FNAME))	
		/*if(vectorSearch(signs,sign))
			cout<<"naideno "<<sign<<endl;*/
	if(vector2Search(strvector,id,sign))
		cout<<"naideno "<<sign<<endl;
	if (SearchSigns(FNAME,strvector,id, sign))
		cout<<"naideno "<<sign<<endl;
	delete[] GlobalBuf;
	system("pause");
	return 0;
}

