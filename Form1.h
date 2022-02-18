#pragma once
#include "Header.h"
#include <msclr/marshal_cppstd.h>

FileManager fm;
vector<Proto> Protos;
#define VERSION "Version: 0.01";
namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	const char* ToAnsi(String^ str)
	{
		static char buf[4096];
		pin_ptr<const wchar_t> wch = PtrToStringChars(str);
		size_t origsize = wcslen(wch) + 1;
		size_t convertedChars = 0;
		wcstombs(buf, wch, sizeof(buf));
		return buf;
	}
	string last_param_selected = "";
	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			setlocale(LC_ALL, "Russian");
			if (!fm.Init())
			{
				MessageBox::Show("please write the correct path to the server in config file");	//	"please write the correct path to the server" ,

			}

			std::stringstream path;
			path << "ServerPath : " << fm.server_path << "proto\\items";

		//	str += fm.server_path;
			ServerPathLabel->Text = gcnew String(path.str().c_str());


			
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	protected:
	private: System::Windows::Forms::SaveFileDialog^  saveFileDialog1;
	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  openToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  saveToolStripMenuItem;
	private: System::Windows::Forms::ListBox^  listBox1;
	private: System::Windows::Forms::ErrorProvider^  errorProvider1;
	private: System::Windows::Forms::ToolStripMenuItem^  closeCurrentToolStripMenuItem;
	private: System::Windows::Forms::Label^  ParamLabel;
	private: System::Windows::Forms::TextBox^  ValuesTextBox;















	private: System::Windows::Forms::ListBox^  ProtoParamList;
	private: System::Windows::Forms::Label^  CurrentFile;
	private: System::Windows::Forms::Label^  ServerPathLabel;
	private: System::Windows::Forms::Label^  ProtoName;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem1;







	private: System::ComponentModel::IContainer^  components;


	protected:

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->saveFileDialog1 = (gcnew System::Windows::Forms::SaveFileDialog());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->openToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->saveToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->closeCurrentToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->ValuesTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ParamLabel = (gcnew System::Windows::Forms::Label());
			this->ProtoParamList = (gcnew System::Windows::Forms::ListBox());
			this->CurrentFile = (gcnew System::Windows::Forms::Label());
			this->ServerPathLabel = (gcnew System::Windows::Forms::Label());
			this->ProtoName = (gcnew System::Windows::Forms::Label());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			
			
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->toolStripMenuItem1,
					this->aboutToolStripMenuItem
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1240, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";

			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->openToolStripMenuItem,
					this->saveToolStripMenuItem, this->closeCurrentToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(37, 20);
			this->toolStripMenuItem1->Text = L"File";
			// 
			// openToolStripMenuItem
			// 
			this->openToolStripMenuItem->Name = L"openToolStripMenuItem";
			this->openToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->openToolStripMenuItem->Text = L"Open";
			this->openToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::OpenFile);
			// 
			// saveToolStripMenuItem
			// 
			this->saveToolStripMenuItem->Name = L"saveToolStripMenuItem";
			this->saveToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->saveToolStripMenuItem->Text = L"Save";
			this->saveToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::SaveFile);
			// 
			// closeCurrentToolStripMenuItem
			// 
			this->closeCurrentToolStripMenuItem->Name = L"closeCurrentToolStripMenuItem";
			this->closeCurrentToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->closeCurrentToolStripMenuItem->Text = L"Close File";
			this->closeCurrentToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::CloseFileClick);
			// 
			// aboutToolStripMenuItem
			// 
			this->aboutToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem1 });
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Size = System::Drawing::Size(40, 20);
			this->aboutToolStripMenuItem->Text = L"Info";
			// 
			// aboutToolStripMenuItem1
			// 
			this->aboutToolStripMenuItem1->Name = L"aboutToolStripMenuItem1";
			this->aboutToolStripMenuItem1->Size = System::Drawing::Size(180, 22);
			this->aboutToolStripMenuItem1->Text = L"About";
			this->aboutToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::AboutClick);
			// 
			// listBox1
			// 
			this->listBox1->FormattingEnabled = true;
			this->listBox1->Location = System::Drawing::Point(12, 24);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(170, 498);
			this->listBox1->TabIndex = 1;
			this->listBox1->Click += gcnew System::EventHandler(this, &Form1::BoxItemClick);
			// 
			// errorProvider1
			// 
			this->errorProvider1->ContainerControl = this;
			// 
			// ValuesTextBox
			// 
			this->ValuesTextBox->Font = (gcnew System::Drawing::Font(L"Arial", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ValuesTextBox->Location = System::Drawing::Point(429, 157);
			this->ValuesTextBox->Name = L"ValuesTextBox";
			this->ValuesTextBox->Size = System::Drawing::Size(130, 20);
			this->ValuesTextBox->TabIndex = 2;
			this->ValuesTextBox->TextChanged += gcnew System::EventHandler(this, &Form1::ValueChanged);
			// 
			// ParamLabel
			// 
			this->ParamLabel->AutoSize = true;
			this->ParamLabel->Font = (gcnew System::Drawing::Font(L"Arial Black", 8.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->ParamLabel->Location = System::Drawing::Point(454, 139);
			this->ParamLabel->Name = L"ParamLabel";
			this->ParamLabel->Size = System::Drawing::Size(79, 15);
			this->ParamLabel->TabIndex = 3;
			this->ParamLabel->Text = L"ParamName";
			// 
			// ProtoParamList
			// 
			this->ProtoParamList->FormattingEnabled = true;
			this->ProtoParamList->Location = System::Drawing::Point(205, 24);
			this->ProtoParamList->Name = L"ProtoParamList";
			this->ProtoParamList->Size = System::Drawing::Size(181, 498);
			this->ProtoParamList->TabIndex = 19;
			this->ProtoParamList->Click += gcnew System::EventHandler(this, &Form1::ProtoParamClick);
			// 
			// CurrentFile
			// 
			this->CurrentFile->AutoSize = true;
			this->CurrentFile->Location = System::Drawing::Point(426, 49);
			this->CurrentFile->Name = L"CurrentFile";
			this->CurrentFile->Size = System::Drawing::Size(89, 13);
			this->CurrentFile->TabIndex = 20;
			this->CurrentFile->Text = L"CurrentFile: None";
			// 
			// ServerPathLabel
			// 
			this->ServerPathLabel->AutoSize = true;
			this->ServerPathLabel->Location = System::Drawing::Point(426, 24);
			this->ServerPathLabel->Name = L"ServerPathLabel";
			this->ServerPathLabel->Size = System::Drawing::Size(69, 13);
			this->ServerPathLabel->TabIndex = 21;
			this->ServerPathLabel->Text = L"ServerPath : ";
			// 
			// ProtoName
			// 
			this->ProtoName->AutoSize = true;
			this->ProtoName->Location = System::Drawing::Point(426, 117);
			this->ProtoName->Name = L"ProtoName";
			this->ProtoName->Size = System::Drawing::Size(0, 13);
			this->ProtoName->TabIndex = 22;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1240, 523);
			this->Controls->Add(this->ProtoName);
			this->Controls->Add(this->ServerPathLabel);
			this->Controls->Add(this->CurrentFile);
			this->Controls->Add(this->ProtoParamList);
			this->Controls->Add(this->ParamLabel);
			this->Controls->Add(this->ValuesTextBox);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->menuStrip1);
			this->Name = L"Form1";
			this->Text = L"Proto Editor";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void OpenFile(System::Object^  sender, System::EventArgs^  e) 
	{
		std::stringstream path;
		path << fm.server_path << "proto\\items\\";
		auto p = gcnew String(path.str().c_str());
		if (fm.server_path.empty())
			this->openFileDialog1->FileName = L"openFileDialog1";
		else
			this->openFileDialog1->FileName = "";

	//	path += "\\proto\\items\\";
		
		this->openFileDialog1->InitialDirectory = p; // p;
		this->openFileDialog1->Filter = "fopro files (*.fopro)|*.fopro";
		this->openFileDialog1->FilterIndex = 1;
		this->openFileDialog1->RestoreDirectory = true;

		if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			// read file	
			
			std::string str = msclr::interop::marshal_as<std::string>(this->openFileDialog1->FileName);
			fm.OpenFile(str);
		//	listBox1->Items->Add(openFileDialog1->FileName);
			Protos.clear();
			ProtoParamList->Items->Clear();
			listBox1->Items->Clear();
			last_param_selected.clear();

			Proto p;
			for (size_t i = 0; i < fm.Names.size(); i++)
			{

				if (fm.Params[i].empty())
				{
					if (!p.prot.empty() )
					{
						Protos.push_back(p);
						p.Clear();
					}
					continue;
				}
				if (fm.Params[i] == "Pid=" || fm.Params[i] == "ProtoId=")
				{
					p.pid = std::stoi(fm.Values[i]);
					p.name = fm.LoadProtoName(p.pid * 100 );
					p.prot = fm.Values[i];
					continue;
				}
				//if (p->pid == 0)
				//	continue;
				p.Params.push_back(fm.Params[i]);
				p.Values.push_back(fm.Values[i]);
				
			}
			for (int i = 0; i < Protos.size(); i++)
			{
				auto managed = gcnew String(Protos[i].prot.c_str());

				managed += " ";

				managed += gcnew String(Protos[i].name.c_str());

				listBox1->Items->Add(managed);
			}
			std::string s = "CurrentFile: "; 
			s += msclr::interop::marshal_as<std::string>(this->openFileDialog1->FileName);
			auto name = gcnew String(s.c_str());
			CurrentFile->Text = name; // 


			//std
			//openFileDialog1->FileName
		}
	}
	private: System::Void SaveFile(System::Object^  sender, System::EventArgs^  e) 
	{
		string path = fm.server_path;
		path += "\\proto\\items";
		auto p = gcnew String(path.c_str());
		this->saveFileDialog1->InitialDirectory = p;
		this->saveFileDialog1->Filter = "fopro files (*.fopro)|*.fopro";
		this->saveFileDialog1->FilterIndex = 1;
		this->saveFileDialog1->RestoreDirectory = true;
		this->saveFileDialog1->FileName = "";
		if (this->saveFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{

			// save file
			std::string str = msclr::interop::marshal_as<std::string>(this->saveFileDialog1->FileName);

			fm.protos = Protos;

			fm.SaveFile(str);
		}
	}
	private: System::Void BoxItemClick(System::Object^  sender, System::EventArgs^  e) 
	{
		int index = listBox1->SelectedIndex;
	//	auto value = gcnew String(Protos[index].Values[i].c_str());
		ProtoParamList->Items->Clear();
		auto pname = gcnew String(Protos[index].name.c_str());
		ProtoName->Text = pname;
		for (int i=0;i< Protos[index].Params.size();i++)
		{
			
			auto param = gcnew String(Protos[index].Params[i].substr(0, Protos[index].Params[i].length() - 1).c_str());
			ProtoParamList->Items->Add(param);

			
		}
		if (! last_param_selected.empty() )
		{
			int param_index = -1;
			for (int i = 0; i < Protos[index].Params.size(); i++)
			{
				if (Protos[index].Params[i] == last_param_selected)
				{
					param_index = i;
					ProtoParamList->SelectedIndex = i;
					break;
				}
			}
			if (param_index == -1)
			{
			//	ParamLabel->Text = "";
			//	ValuesTextBox->Text = "";
				return;
			}
				
			 //last_param_selected;
			auto value = gcnew String(Protos[index].Values[param_index].c_str());
			auto param = gcnew String(Protos[index].Params[param_index].substr(0, Protos[index].Params[param_index].length() - 1).c_str());

			auto pname = gcnew String(Protos[index].name.c_str());
			ProtoName->Text = pname;

			ParamLabel->Text = param;
			ValuesTextBox->Text = value;
		}
	}
	private: System::Void CloseFileClick(System::Object^  sender, System::EventArgs^  e) 
	{
		Protos.clear();
		ProtoParamList->Items->Clear();
		listBox1->Items->Clear();
		ProtoName->Text = "";
		last_param_selected.clear();

		std::string str = "CurrentFile: None";
		auto name = gcnew String(str.c_str());
		CurrentFile->Text = name; // 
	}
	private: System::Void ProtoParamClick(System::Object^  sender, System::EventArgs^  e) 
	{
		int index = listBox1->SelectedIndex;
		int param_index = ProtoParamList->SelectedIndex;

		last_param_selected = Protos[index].Params[param_index];

		auto value = gcnew String(Protos[index].Values[param_index].c_str());
		auto param = gcnew String(Protos[index].Params[param_index].substr(0, Protos[index].Params[param_index].length() - 1).c_str());

		ParamLabel->Text = param;
		ValuesTextBox->Text = value;
	}
	private: System::Void ValueChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		int index = listBox1->SelectedIndex;
		int param_index = ProtoParamList->SelectedIndex;
		msclr::interop::marshal_context context;
		std::string str = context.marshal_as<std::string>(ValuesTextBox->Text);

		Protos[index].Values[param_index] = str;
	}
	private: System::Void AboutClick(System::Object^  sender, System::EventArgs^  e) 
	{
		string info = "Name: FOnline Proto Editor\n";
		info += VERSION;
		info += "\nAuthor: snzhkhd";
		auto param = gcnew String(info.c_str());
		MessageBox::Show(param);
	}
};
}
