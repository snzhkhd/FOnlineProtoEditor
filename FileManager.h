#pragma once
#include <msclr/marshal_cppstd.h>
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

//////////////////////////////// CONFIG
	string server_path;
	// 0 = engl, 1 = russ
	int Lang = 0;

	// config file 
	bool Init();

	bool SaveConfig();
//////////////////////////////// !CONFIG
	int MaxBarValue = 0;
	int progress = 0;

	// !config file

	void ClearData();
	bool OpenFile(string name);
	bool SaveFile();
	bool SaveFile(string name);
	bool SaveFile(string name, vector<Proto> pro);


	void SetFileSize(string name);

	string GetValue(string Param);
	size_t GetValueIndex(string Param);
	bool SaveValue(string Param, string NewValue);


	// protos func
	string LoadProtoName(int pid);
	string GetProtoType(int pid, Proto p);
	string GetProtoType(Proto p);

	int GetProtoTypeIndex(Proto p);

	string GetStringType(int type);

	const char* ToAnsi(System::String^ str);
	string utf8_to_string(const char *utf8str);

	System::String^ ToClrString(const char* str);
	System::String^ ToClrString(string& str);
	std::string UTF8to1251(std::string const& utf8);
	string ClearFrom(string str, char symbl);

	string GetValueForPid(int pid, string param);

	bool FileIsExist(string filePath);

	vector<string> StringSeperation(string Sourse, string delim);

	void testLoadFile();


/////////////////////////////

	void AddToFavour();
	void DeleteFromFavour();

////////////////////////////	

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
