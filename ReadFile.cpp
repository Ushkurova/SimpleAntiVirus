#include "stdafx.h"
#include "SearchSigns.h"
#include "ReadFile.h"

extern char* GlobalBuf;
extern  int _max_size;
extern datasigns signs;
extern ID id;
extern str strvector;
int t=0;
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
			_data.sign_str = new char[_data.size + 1];
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

bool OpenSigned(const char *FileName) 
{
	signs.clear();
	id.clear();
	strvector.clear();
	ifstream file(FileName, std::ios::binary);
	signvector buffer;
	unsigned int count = BUFFER_SIZE, _pos = 0;
	buffer.resize(count);
	while (file.read((char*)&buffer[_pos], count)) 
	{	
		if (file.gcount()<buffer.size())
		{
			buffer.resize(file.gcount());
		}
		_pos = AddSigned(buffer, signs, strvector,id);
		memcpy(buffer.data(), &buffer[_pos], buffer.size() - _pos);
		_pos = buffer.size() - _pos;
		count = buffer.size()- _pos;
	}
	if (file.gcount()<buffer.size())
		{
			buffer.resize(file.gcount());
		}
	AddSigned(buffer, signs, strvector, id);
	file.close();
	return true;
}

size_t _Size (const char *FileName)
{
	ifstream file(FileName, std::ios::binary);
	file.seekg(0,ios::end);
	size_t size=file.tellg();
	file.close();
	return size;
}
