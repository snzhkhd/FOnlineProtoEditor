#pragma once

using namespace std;

#define INIFILE ("Config.cfg");

void Log(string str);

struct Proto
{
	int pid;
	string name;
	string prot;
	vector<string> Params;
	vector<string> Values;
	void Clear()
	{
		pid = 0;
		prot.clear();
		Params.clear();
		Values.clear();
	}
	Proto()
	{
		pid = 0;
		prot.clear();
		Params.clear();
		Values.clear();
	}
};
class FileManager
{
public:
	vector<string> Names;
	vector<string> Params;
	vector<string> Values;

	
	vector<Proto> protos;
	string file_path;

	string current_dir;

	string server_path;

	// config file 
	bool Init();

	

	// !config file

	void ClearData();
	bool OpenFile(string name);
	bool SaveFile();
	bool SaveFile(string name);
	bool SaveFile(string name, vector<Proto> pro);


	string GetValue(string Param);
	size_t GetValueIndex(string Param);
	bool SaveValue(string Param, string NewValue);

	string LoadProtoName(int pid);

	string ClearFrom(string str, char symbl);

	string GetValueForPid(int pid, string param);

	bool FileIsExist(string filePath);

	vector<string> StringSeperation(string Sourse, string delim);

	void testLoadFile();

	FileManager()
	{
		Params.clear();
		Values.clear();
	}
	~FileManager()
	{
		Params.clear();
		Values.clear();
	}
};
