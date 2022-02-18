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

	stringstream filename;
	current_dir =  _getcwd(NULL, 0);
	filename << current_dir << "\\" << INIFILE;
	
	file_path = filename.str();

	ifstream CurrentFile(file_path);
//	CurrentFile.open(filename.str());
	if (CurrentFile.is_open() )
	{
		string str;
		while (!CurrentFile.eof())
		{	// считывать данные с файла

			getline(CurrentFile, str);
			vector<string> tmp;
			tmp = StringSeperation(str, "=");
			if (tmp.size() > 1)
				server_path = tmp[1];
			CurrentFile.close();
		}
	}
	else
	{
		ofstream out(file_path);
		out << "path=" << endl;
		out.close();
	}
	return !server_path.empty();
}

void FileManager::ClearData()
{
	Names.clear();
	Params.clear();
	Values.clear();
}

bool FileManager::OpenFile(string name)
{
	ClearData();
	ifstream CurrentFile;
	CurrentFile.open(name);
	if (CurrentFile.is_open())
	{
		file_path = name;

		string str;
		while (!CurrentFile.eof())
		{	// считывать данные с файла

			getline(CurrentFile, str);
			vector<string> tmp;

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
			}
			else			// какие то параменры без значений
			{
				Names.push_back(str);
				Params.push_back("");
				Values.push_back("");
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

string FileManager::LoadProtoName(int pid)
{
	if (server_path.empty())
	{
		std::stringstream out;
		out << pid;
		return out.str();
	}

	string m = server_path;
	m += "\\text\\engl\\FOOBJ.MSG";
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
				return str;	//	str.length() -	
			}
				

		}
	}

	return "unknown";
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
