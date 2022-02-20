#include "stdafx.h"
#include "Header.h"
#include "FileManager.h"


// функция для тестов 
void FileManager::testLoadFile()
{

	stringstream filename;
	filename << _getcwd(NULL, 0) << "\\" << "weapon.fopro";
	if (OpenFile(filename.str()))
	{
		file_path += "_w";
		if (SaveFile())
		{
			Log("file is saved");
			return;
		}
		Log("file is not saved");
		return;
	}
	Log("file is not open!");
}



bool FileManager::Init()
{
	LoadFavourites();

	stringstream filename;
	current_dir =  _getcwd(NULL, 0);
	filename << current_dir << "\\" << INIFILE;
	
	file_path = filename.str();

	ifstream CurrentFile(file_path);
	if (CurrentFile.is_open() )
	{
		string str;
			getline(CurrentFile, str);
			vector<string> tmp;
			// path=
			tmp = StringSeperation(str, "=");
			if (tmp.size() > 1)
				server_path = tmp[1];
			tmp.clear();

			// Lang=
			getline(CurrentFile, str);
			tmp = StringSeperation(str, "=");
			if (tmp.size() > 1)
			{
				if (tmp[1] == "0")
					Lang = 0;
				else
					Lang = 1;
			}
			CurrentFile.close();
	}
	else
	{
		ofstream out(file_path);
		out << "path=" << endl;
		out.close();
	}
	return !server_path.empty();
}

bool FileManager::SaveConfig()
{

	stringstream filename;
	current_dir = _getcwd(NULL, 0);
	filename << current_dir << "\\" << INIFILE;

	ifstream config(filename.str());
	if (config.is_open())
	{
		
		vector<string> Vec;
		while (!config.eof())
		{

			string str;
			stringstream file;

			config >> str;
			//getline(config, str);
			if (str.substr(0, 4) == "Lang")
			{
				file << "Lang=" << Lang;
				str = file.str();
			}
			Vec.push_back(str);
		}
		config.close();

		ofstream ofs(filename.str());
		for (vector<std::string>::const_iterator it = Vec.begin(); it != Vec.end(); ++it)
			ofs << *it << endl;

		ofs.close();
		return true;
	}

	return false;
}

void FileManager::DeleteFavour(int pid)
{

	for (int i = 0; i < Favourites.size(); i++)
	{
		if (Favourites[i].pid == pid)
		{
			Favourites[i].pid = -1;
			
			break;
		}
	}

	typedef vector<int> IntContainer;
	typedef IntContainer::iterator  IntIterator;

	IntIterator j = find(FavouritesPids.begin(), FavouritesPids.end(), pid);
	if (j != FavouritesPids.end())
		FavouritesPids.erase(j);

}

void FileManager::LoadFavourites()
{
	stringstream filename;
	current_dir = _getcwd(NULL, 0);
	filename << current_dir << "\\" << FAVOURFILE;
	ifstream config(filename.str());
	if (config.is_open())
	{
		vector<string> Vec;
		while (!config.eof())
		{
			string str;
			getline(config, str);
			if (!str.empty())
				FavouritesPids.push_back( atoi(str.c_str()) );
		}
	}
}

void FileManager::SaveFavourites()
{
	stringstream filename;
	current_dir = _getcwd(NULL, 0);
	filename << current_dir << "\\" << FAVOURFILE;
	ofstream ofs(filename.str());
	for (int i = 0; i < FavouritesPids.size(); i++)
	{
		ofs << FavouritesPids[i] << endl;
	}

	ofs.close();
}

void FileManager::ClearData()
{
	Names.clear();
	Params.clear();
	Values.clear();
	Favourites.clear();
}

bool FileManager::ListLoad()
{
	if (server_path.empty())
		return false;
	string m = server_path;
	if (file.empty())
		m += "\\proto\\items\\items.lst";
	m = file;
	ifstream CurrentFile;
	CurrentFile.open(m);
	if (CurrentFile.is_open())
	{
		while (!CurrentFile.eof())
		{	// считывать данные с файла

			string str;
			getline(CurrentFile, str);

			progress = 0;

			string path = server_path;
			path += "\\proto\\items\\"+ str;
			OpenFile(path);
			
			progress++;
		}
		
	}
	CurrentFile.close();
	Loaded = true;
	return true;
}

bool FileManager::OpenFile(string name)
{
//	ClearData();
	ifstream CurrentFile;
	CurrentFile.open(name);
	if (CurrentFile.is_open())
	{
		file_path = name;
		progress = 0;
		string str;
		while (!CurrentFile.eof())
		{	// считывать данные с файла

			getline(CurrentFile, str);
			vector<string> tmp;
			curent_load = str;
			if (str.c_str() == "\n")	// переносы строк тоже сохраняем
			{
				Names.push_back("\n");
				Params.push_back("");
				Values.push_back("");
			
				continue;
			}

			tmp = StringSeperation(str, "=");
			if (tmp.size() >= 2)	// параметры и значения
			{
				Names.push_back("");
				Params.push_back(tmp[0] + "=");
				Values.push_back(tmp[1]);
				progress++;
			}
			else			// какие то параменры без значений
			{
				
				Names.push_back(str);
				Params.push_back("");
				Values.push_back("");
				progress++;
			}

			// чистим массив от уже загруженных данных
			tmp.clear();
		}
		
		CurrentFile.close();	// закрывает
		return true;
	}
	CurrentFile.close();
	return false;
}

bool FileManager::SaveFile()
{
	if (file_path.empty())
		return false;
	ofstream out(file_path);
	for (size_t i = 0; i < Params.size(); i++)	// тупа сохраняем как есть, ибо уже всё отформатировано как надо при загрузке
		out << Names[i] << Params[i].c_str() << Values[i].c_str() << endl;

	out.close();
	return true;
}
bool FileManager::SaveFile(string name)
{
	ofstream out(name);
	for (size_t i = 0; i < protos.size(); i++)
	{
		out << "[Proto]" << endl;

		out << "ProtoId=" << protos[i].pid << endl;

		for (int j = 0; j < protos[i].Params.size(); j++)
			out << protos[i].Params[j] << protos[i].Values[j] << endl;

		out << endl;
	}
	out.close();
	return true;
}
bool FileManager::SaveFile(string name, vector<Proto> pro)
{
	ofstream out(name);
	for (size_t i = 0; i < pro.size(); i++)
	{
		out << "[Proto]" << endl;

		out << "ProtoId=" << pro[i].pid << endl;

		for (int j=0;i<pro[i].Params.size();i++)
		{
			out << pro[i].Params[j] << endl;
			out << pro[i].Values[j] << endl;
		}
		out << endl;
	}
	out.close();
	return false;
}
void FileManager::SetFileSize(string name)
{
	ifstream File;
	File.open(name);
	if (File.is_open())
	{
		file_path = name;
		File.seekg(0, ios::end);
		long size = (long)File.tellg();
		File.seekg(0, ios::beg);
		MaxBarValue = size;
		File.close();
	}

}
// поиск значения по имени
string FileManager::GetValue(string Param)
{
	for (size_t i = 0; i < Params.size(); i++)
		if (Params[i] == Param)
			return Values[i];

	return "not_found";
}
// поиск значения по имени и возврат его индекса
size_t FileManager::GetValueIndex(string Param)
{
	for (size_t i = 0; i < Params.size(); i++)
		if (Params[i] == Param)
			return i;
	return -1;
}
// изменение значений
bool FileManager::SaveValue(string Param, string NewValue)
{
	size_t index = GetValueIndex(Param);
	if (index == -1)
		return false;
	Values[index] = NewValue;
	return true;
}

string FileManager::utf8_to_string(const char *utf8str)
{
	// UTF-8 to wstring
	wstring_convert<codecvt_utf8<wchar_t>> wconv;
	wstring wstr = wconv.from_bytes(utf8str);
	// wstring to string
	vector<char> buf(wstr.size());
	use_facet<ctype<wchar_t>>(locale(".1252")).narrow(wstr.data(), wstr.data() + wstr.size(), '?', buf.data());
	return string(buf.data(), buf.size());
}

const char* FileManager::ToAnsi(System::String^ str)
{
	static char buf[4096];
	pin_ptr<const wchar_t> wch = PtrToStringChars(str);
	size_t origsize = wcslen(wch) + 1;
	size_t convertedChars = 0;
	wcstombs(buf, wch, sizeof(buf));
	return buf;
}

System::String^ FileManager::ToClrString(const char* str)
{
	System::String^ res = System::String(str).ToString();
	return res;
}

System::String^ FileManager::ToClrString(string& str)
{
	return ToClrString(str.c_str());
}


string FileManager::LoadProtoName(int pid)
{
	if (server_path.empty())
	{
		std::stringstream out;
		out << pid;
		return  out.str();
	}

	string m = server_path;
	if(Lang == 0)
		m += "\\text\\engl\\FOOBJ.MSG";
	else
		m += "\\text\\russ\\FOOBJ.MSG";
	ifstream MsgFile(m);
	string token;
	//	CurrentFile.open(filename.str());
	if (MsgFile.is_open())
	{
		std::stringstream out;
		out << pid;
		token = "{";
		token += out.str();
		token += "}";

		while (!MsgFile.eof())
		{	// считывать данные с файла
			string str;
			getline(MsgFile, str);
			if (str.substr(0, token.length()) == token)
			{
				str = ClearFrom(str.substr(token.length() + 3, str.length()), '}');
				return UTF8to1251(str.c_str());
			}
				

		}
	}

	return "unknown";
}

string FileManager::GetProtoType(int pid, Proto p)
{
	for (int i = 0; i < p.Params.size(); i++)
	{
		if (p.Params[i] == "Type=")
			return GetStringType( atoi( p.Values[i].c_str()));
	}

	return string();
}

string FileManager::GetProtoType(Proto p)
{
	
	return GetProtoType(p.pid, p);
}

int FileManager::GetProtoTypeIndex(Proto p)
{
	for (int i = 0; i < p.Params.size(); i++)
	{
		if (p.Params[i] == "Type=")
			return CLAMP(atoi(p.Values[i].c_str()),0, 14 );
	}
	return 0;
}
/*
#define  ITEM_TYPE_TILE   (0)
#define  ITEM_TYPE_ARMOR   (1)
#define  ITEM_TYPE_DRUG   (2)
#define  ITEM_TYPE_WEAPON   (3)
#define  ITEM_TYPE_AMMO   (4)
#define  ITEM_TYPE_MISC   (5)
#define  ITEM_TYPE_MISC2   (6)
#define  ITEM_TYPE_KEY   (7)
#define  ITEM_TYPE_CONTAINER   (8)
#define  ITEM_TYPE_DOOR   (9)
#define  ITEM_TYPE_GRID   (10)
#define  ITEM_TYPE_GENERIC   (11)
#define  ITEM_TYPE_WALL   (12)

*/
string FileManager::GetStringType(int type)
{
	vector<string> types = {"NONE", "ARMOR", "DRUG", "WEAPON", "AMMO", "MISC", "CAR ", "KEY" , "CONTAINER", "DOOR", "GRID" , "GENERIC", "WALL", "MAX_TYPES"};

	if (type > types.size())
		type = 14;
	if (type < 0)
		type = 0;
	return types[type];
}


// перекодирует все однобайтовые символы, а из двубайтовых только русские буквы
std::string FileManager::UTF8to1251(std::string const& utf8)
{
	std::string s1251;
	for (int i = 0; i < utf8.size(); ++i)
	{
		int b1 = (unsigned char)utf8[i];
		if ((b1 >> 5) == 6)
		{
			int b2 = (unsigned char)utf8[i + 1];
			if ((b1 == 208) && (b2 >= 144 && b2 <= 191))
			{
				s1251 += (char)(b2 + 48);
			}
			else if ((b1 == 209) && (b2 >= 128 && b2 <= 143))
			{
				s1251 += (char)(b2 + 112);
			}
			else if ((b1 == 208) && (b2 == 129))
			{
				s1251 += (char)(b2 + 39);
			}
			else if ((b1 == 209) && (b2 == 145))
			{
				s1251 += (char)(b2 + 39);
			}
			++i;
		}
		else if ((b1 >> 7) == 0)
		{
			s1251 += b1;
		}
	}
	return s1251;
}


string FileManager::ClearFrom(string str, char symbl)
{
	string final = "";
	for (int i = 0; i < str.length(); i++)
	{
		if (str[i] == symbl)
			continue;
		final += str[i];
	}
	return final;
}

string FileManager::GetValueForPid(int pid, string param)
{
	string p;
	p += pid;
	size_t index = GetValueIndex(p);
	if (index > -1)
	{
		for (size_t i = index; i < Params.size(); i++)
		{
			if (Params[i].empty())
				return "empty";
			if (Params[i] == param)
				return Params[i];
		}
	}
	return "not found";
}

bool FileManager::FileIsExist(string filePath)
{
	ifstream fin(filePath.c_str());

	if (fin.is_open())
	{
		return true;
		fin.close();
	}
	fin.close();
	return false;
}
// делитель строки
vector<string> FileManager::StringSeperation(string Sourse, string delim)
{
	char  buf2[135], *ptr, *longCommand = &Sourse[0];
	vector<string> com;
	for (ptr = strtok(longCommand, delim.c_str()); ptr != NULL; ptr = strtok(NULL, delim.c_str()))
	{
		strcpy(buf2, ptr);
		com.push_back(ptr);
	}
	return com;
}

void Log(string str)
{
	std::cout << str << endl;
}
