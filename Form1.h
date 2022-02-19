#pragma once
#include "Header.h"


FileManager fm;
vector<Proto> Protos;

#define VERSION "Version: 0.03";
namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	std::string last_param_selected;
	

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
		
	public:
		int progress;
	private: System::ComponentModel::BackgroundWorker^  backgroundWorker1;
	public:
		bool IsLoaded = false;
		void ChangeLang()
		{

			this->ServerPathLabel->Text = (fm.Lang == 0 ? L"ServerPath : " : L"Ïóòü ê ñåðâåðó : ");
			this->closeCurrentToolStripMenuItem->Text = (fm.Lang == 0 ? L"Close File" : L"Çàêðûòü ôàéë");
			this->saveToolStripMenuItem->Text = (fm.Lang == 0 ? L"Save" : L"Ñîõðàíèòü");
			this->openToolStripMenuItem->Text = (fm.Lang == 0 ? L"Open" : L"Îòêðûòü");
			this->toolStripMenuItem1->Text = (fm.Lang == 0 ? L"File" : L"Ôàéë");
			this->CurrentFile->Text = (fm.Lang == 0 ? "CurrentFile: None" : "Ôàéë íå çàãðóæåí");
			this->ServerPathLabel->Text = (fm.Lang == 0 ? L"ServerPath : " : L"Ïóòü ê ñåðâåðó : ");

			fm.SaveConfig();

			std::string str = msclr::interop::marshal_as<std::string>(this->openFileDialog1->FileName);
			if (str.empty())
				return;

			fm.OpenFile(str);
			Protos.clear();
			ProtoParamList->Items->Clear();
			last_param_selected.clear();
			

			Proto p;
			for (size_t i = 0; i < fm.Names.size(); i++)
			{

				if (fm.Params[i].empty())
				{
					if (!p.prot.empty())
					{
						Protos.push_back(p);
						p.Clear();
					}
					continue;
				}
				if (fm.Params[i] == "Pid=" || fm.Params[i] == "ProtoId=")
				{
					p.pid = std::stoi(fm.Values[i]);
					p.name = fm.LoadProtoName(p.pid * 100);
					p.prot = fm.Values[i];
					continue;
				}

				p.Params.push_back(fm.Params[i]);
				p.Values.push_back(fm.Values[i]);

			}
			
			for (int i = 0; i < Protos.size(); i++)
			{
				auto managed = gcnew String(Protos[i].prot.c_str());

				managed += " ";

				managed += gcnew String(Protos[i].name.c_str());

				AlltreeView->Nodes[fm.GetProtoTypeIndex(Protos[i])]->Nodes->Add(managed);
			//	listBox1->Items->Add(managed);
			}
			std::string s = "CurrentFile: ";
			string path = fm.server_path;
			path += "\\proto\\items";

			string file = msclr::interop::marshal_as<std::string>(this->openFileDialog1->FileName);
			s += file.substr(path.length(), file.length());
			auto name = gcnew String(s.c_str());
			CurrentFile->Text = name;

		}

		
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
			setlocale(LC_ALL, "Russian");
			if (!fm.Init())
				MessageBox::Show("please write the correct path to the server in config file");	//	"please write the correct path to the server" ,
			
			std::stringstream path;
			path << "ServerPath : " << fm.server_path << "proto\\items";
			ServerPathLabel->Text = gcnew String(path.str().c_str());
			
			ChangeLang();
			
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
	private: System::Windows::Forms::Label^  DiscriptionLabel;
	private: System::Windows::Forms::ToolStripMenuItem^  langToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  rusToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  engToolStripMenuItem;
private: System::Windows::Forms::TreeView^  FavourtreeView;

private: System::Windows::Forms::Label^  FavouritesLabel;
private: System::Windows::Forms::Button^  buttonDelete;
private: System::Windows::Forms::Button^  buttonAddTo;
private: System::Windows::Forms::TreeView^  AlltreeView;
private: System::Windows::Forms::Label^  Debuglabel;
private: System::Windows::Forms::ProgressBar^  progressBar;

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
			this->langToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->rusToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->engToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->errorProvider1 = (gcnew System::Windows::Forms::ErrorProvider(this->components));
			this->ValuesTextBox = (gcnew System::Windows::Forms::TextBox());
			this->ParamLabel = (gcnew System::Windows::Forms::Label());
			this->ProtoParamList = (gcnew System::Windows::Forms::ListBox());
			this->CurrentFile = (gcnew System::Windows::Forms::Label());
			this->ServerPathLabel = (gcnew System::Windows::Forms::Label());
			this->ProtoName = (gcnew System::Windows::Forms::Label());
			this->DiscriptionLabel = (gcnew System::Windows::Forms::Label());
			this->FavouritesLabel = (gcnew System::Windows::Forms::Label());
			this->FavourtreeView = (gcnew System::Windows::Forms::TreeView());
			this->buttonAddTo = (gcnew System::Windows::Forms::Button());
			this->buttonDelete = (gcnew System::Windows::Forms::Button());
			this->AlltreeView = (gcnew System::Windows::Forms::TreeView());
			this->Debuglabel = (gcnew System::Windows::Forms::Label());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->backgroundWorker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->menuStrip1->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->errorProvider1))->BeginInit();
			this->SuspendLayout();
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
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {
				this->openToolStripMenuItem,
					this->saveToolStripMenuItem, this->closeCurrentToolStripMenuItem, this->langToolStripMenuItem
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
			// langToolStripMenuItem
			// 
			this->langToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->rusToolStripMenuItem,
					this->engToolStripMenuItem
			});
			this->langToolStripMenuItem->Name = L"langToolStripMenuItem";
			this->langToolStripMenuItem->Size = System::Drawing::Size(124, 22);
			this->langToolStripMenuItem->Text = L"Lang";
			// 
			// rusToolStripMenuItem
			// 
			this->rusToolStripMenuItem->Name = L"rusToolStripMenuItem";
			this->rusToolStripMenuItem->Size = System::Drawing::Size(95, 22);
			this->rusToolStripMenuItem->Text = L"russ";
			this->rusToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::LangRuClick);
			// 
			// engToolStripMenuItem
			// 
			this->engToolStripMenuItem->Name = L"engToolStripMenuItem";
			this->engToolStripMenuItem->Size = System::Drawing::Size(95, 22);
			this->engToolStripMenuItem->Text = L"eng";
			this->engToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::LangEngClick);
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
			this->aboutToolStripMenuItem1->Size = System::Drawing::Size(107, 22);
			this->aboutToolStripMenuItem1->Text = L"About";
			this->aboutToolStripMenuItem1->Click += gcnew System::EventHandler(this, &Form1::AboutClick);
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
			this->ParamLabel->Size = System::Drawing::Size(0, 15);
			this->ParamLabel->TabIndex = 3;
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
			this->ProtoName->Location = System::Drawing::Point(426, 202);
			this->ProtoName->Name = L"ProtoName";
			this->ProtoName->Size = System::Drawing::Size(0, 13);
			this->ProtoName->TabIndex = 22;
			// 
			// DiscriptionLabel
			// 
			this->DiscriptionLabel->AutoSize = true;
			this->DiscriptionLabel->Location = System::Drawing::Point(426, 220);
			this->DiscriptionLabel->MaximumSize = System::Drawing::Size(200, 200);
			this->DiscriptionLabel->Name = L"DiscriptionLabel";
			this->DiscriptionLabel->Size = System::Drawing::Size(0, 13);
			this->DiscriptionLabel->TabIndex = 25;
			// 
			// FavouritesLabel
			// 
			this->FavouritesLabel->AutoSize = true;
			this->FavouritesLabel->Location = System::Drawing::Point(978, 24);
			this->FavouritesLabel->Name = L"FavouritesLabel";
			this->FavouritesLabel->Size = System::Drawing::Size(56, 13);
			this->FavouritesLabel->TabIndex = 27;
			this->FavouritesLabel->Text = L"Favourites";
			// 
			// FavourtreeView
			// 
			this->FavourtreeView->Location = System::Drawing::Point(981, 49);
			this->FavourtreeView->Name = L"FavourtreeView";
			this->FavourtreeView->Size = System::Drawing::Size(211, 462);
			this->FavourtreeView->TabIndex = 28;
			// 
			// buttonAddTo
			// 
			this->buttonAddTo->Location = System::Drawing::Point(925, 49);
			this->buttonAddTo->Name = L"buttonAddTo";
			this->buttonAddTo->Size = System::Drawing::Size(50, 23);
			this->buttonAddTo->TabIndex = 29;
			this->buttonAddTo->Text = L"->";
			this->buttonAddTo->UseVisualStyleBackColor = true;
			this->buttonAddTo->Click += gcnew System::EventHandler(this, &Form1::AddToFavourClick);
			// 
			// buttonDelete
			// 
			this->buttonDelete->Location = System::Drawing::Point(925, 79);
			this->buttonDelete->Name = L"buttonDelete";
			this->buttonDelete->Size = System::Drawing::Size(50, 23);
			this->buttonDelete->TabIndex = 30;
			this->buttonDelete->Text = L"<-";
			this->buttonDelete->UseVisualStyleBackColor = true;
			this->buttonDelete->Click += gcnew System::EventHandler(this, &Form1::DeleteToFavourClick);
			// 
			// AlltreeView
			// 
			this->AlltreeView->BackColor = System::Drawing::SystemColors::Control;
			this->AlltreeView->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->AlltreeView->Location = System::Drawing::Point(0, 24);
			this->AlltreeView->Name = L"AlltreeView";
			this->AlltreeView->Size = System::Drawing::Size(199, 498);
			this->AlltreeView->TabIndex = 31;
			this->AlltreeView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &Form1::SelectNodeTree);
			// 
			// Debuglabel
			// 
			this->Debuglabel->AutoSize = true;
			this->Debuglabel->Location = System::Drawing::Point(523, 346);
			this->Debuglabel->Name = L"Debuglabel";
			this->Debuglabel->Size = System::Drawing::Size(35, 13);
			this->Debuglabel->TabIndex = 32;
			this->Debuglabel->Text = L"label1";
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(404, 488);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(546, 23);
			this->progressBar->TabIndex = 33;
		//	this->progressBar->Visible = false;
			// 
			// backgroundWorker1
			// 
			this->backgroundWorker1->WorkerReportsProgress = true;
			this->backgroundWorker1->WorkerSupportsCancellation = true;
			this->backgroundWorker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::ProgressBar);
			this->backgroundWorker1->ProgressChanged += gcnew System::ComponentModel::ProgressChangedEventHandler(this, &Form1::backgroundWorker1_ProgressChanged);
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1240, 523);
			this->Controls->Add(this->progressBar);
			this->Controls->Add(this->Debuglabel);
			this->Controls->Add(this->AlltreeView);
			this->Controls->Add(this->buttonDelete);
			this->Controls->Add(this->buttonAddTo);
			this->Controls->Add(this->FavourtreeView);
			this->Controls->Add(this->FavouritesLabel);
			this->Controls->Add(this->DiscriptionLabel);
			this->Controls->Add(this->ProtoName);
			this->Controls->Add(this->ServerPathLabel);
			this->Controls->Add(this->CurrentFile);
			this->Controls->Add(this->ProtoParamList);
			this->Controls->Add(this->ParamLabel);
			this->Controls->Add(this->ValuesTextBox);
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
			this->openFileDialog1->FileName = L"";

	//	path += "\\proto\\items\\";
		
		this->openFileDialog1->InitialDirectory = p; // p;
		this->openFileDialog1->Filter = L"fopro files (*.fopro)|*.fopro";
		this->openFileDialog1->FilterIndex = 1;
		this->openFileDialog1->RestoreDirectory = true;

		if (this->openFileDialog1->ShowDialog() == System::Windows::Forms::DialogResult::OK)
		{
			std::string str = msclr::interop::marshal_as<std::string>(this->openFileDialog1->FileName);
			// setup progress bar
			fm.SetFileSize(str);
			progressBar->Maximum = fm.MaxBarValue;
			progressBar->Value = 0;
			
			Debuglabel->Text = progressBar->Maximum.ToString();

			//	run_progress();
			backgroundWorker1->RunWorkerAsync(1);
			// read file
			fm.OpenFile(str);
			Protos.clear();
			ProtoParamList->Items->Clear();
			last_param_selected.clear();
			AlltreeView->Nodes->Clear();
			



			//		this->progressBar->Visible = true;
						// progress bar thread
			progressBar->Maximum = (int)fm.Names.size();
			progressBar->Value = 0;
			fm.progress = 0;

			Proto p;
			for (size_t i = 0; i < fm.Names.size(); i++)
			{

				if (fm.Params[i].empty())
				{
					if (!p.prot.empty() )
					{
						Protos.push_back(p);

						fm.progress++;

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

				p.Params.push_back(fm.Params[i]);
				p.Values.push_back(fm.Values[i]);
				
			}
			AlltreeView->Nodes->Clear();
			FavourtreeView->Nodes->Clear();
			for (int i = 0; i < 13; i++)
			{
				auto pname = gcnew String(fm.GetStringType(i).c_str());
				AlltreeView->Nodes->Add(pname);
				FavourtreeView->Nodes->Add(pname);
			}
			// progress bar thread
			progressBar->Maximum = (int)Protos.size();
			progressBar->Value = 0;
			fm.progress = 0;

			for (int i = 0; i < Protos.size(); i++)
			{
				Proto pr = Protos[i];
				if (pr.pid == 0 )
					continue;
				auto managed = gcnew String(pr.prot.c_str());
				managed += " ";
				managed += gcnew String(pr.name.c_str());

				AlltreeView->Nodes[fm.GetProtoTypeIndex(pr)]->Nodes->Add(managed);

				fm.progress++;
				

			}
			IsLoaded = true;
			backgroundWorker1->CancelAsync();
			

			std::string s = (fm.Lang == 0 ? "CurrentFile: " : "Ôàéë : ");;
			string path = fm.server_path;
			path += "\\proto\\items";

			string file = msclr::interop::marshal_as<std::string>(this->openFileDialog1->FileName);
			s += file.substr(path.length() , file.length() );
			auto name = gcnew String(s.c_str());
			CurrentFile->Text = name;
			
		}
	}
	private: System::Void SaveFile(System::Object^  sender, System::EventArgs^  e) 
	{
		string path = fm.server_path;
		path += "\\proto\\items";
		auto p = gcnew String(path.c_str());
		this->saveFileDialog1->InitialDirectory = p;
		this->saveFileDialog1->Filter = L"fopro files (*.fopro)|*.fopro";
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
	private: System::Void CloseFileClick(System::Object^  sender, System::EventArgs^  e) 
	{
		Protos.clear();
		ProtoParamList->Items->Clear();
		AlltreeView->Nodes->Clear();
		ProtoName->Text = "";
		DiscriptionLabel->Text = "";
		ParamLabel->Text = "";
		ValuesTextBox->Text = "";
		last_param_selected.clear();

		AlltreeView->Nodes->Clear();
		FavourtreeView->Nodes->Clear();
		for (int i = 0; i < 13; i++)
		{
			auto pname = gcnew String(fm.GetStringType(i).c_str());
			AlltreeView->Nodes->Add(pname);
			FavourtreeView->Nodes->Add(pname);
		}

		std::string str = (fm.Lang == 0 ? "CurrentFile: None" : "Ôàéë íå çàãðóæåí");
		auto name = gcnew String(str.c_str());
		CurrentFile->Text = name; 
	}
	private: System::Void ProtoParamClick(System::Object^  sender, System::EventArgs^  e) 
	{

		if (!AlltreeView->SelectedNode )
			return;
		int index = AlltreeView->SelectedNode->Index;
		int param_index = ProtoParamList->SelectedIndex;

		last_param_selected = Protos[index].Params[param_index];

		auto value = gcnew String(Protos[index].Values[param_index].c_str());
		auto param = gcnew String(Protos[index].Params[param_index].substr(0, Protos[index].Params[param_index].length() - 1).c_str());

		ParamLabel->Text = param;
		ValuesTextBox->Text = value;
	}
	private: System::Void ValueChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		if (!AlltreeView->SelectedNode)
			return;
		int index = AlltreeView->SelectedNode->Index;
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
	private: System::Void LangRuClick(System::Object^  sender, System::EventArgs^  e) 
	{
		fm.Lang = 1;
		ChangeLang();
	}
	private: System::Void LangEngClick(System::Object^  sender, System::EventArgs^  e) 
	{
		fm.Lang = 0;
		ChangeLang();
	}
	private: System::Void AddToFavourClick(System::Object^  sender, System::EventArgs^  e) 
	{
		//int index = listBox1->SelectedIndex;
		//auto pname = gcnew String(Protos[index].name.c_str());

		//auto managed = gcnew String(Protos[index].prot.c_str());
		//managed += " ";
		//managed += gcnew String(Protos[index].name.c_str());
		

		
	//	FavourtreeView->Nodes[0]->Nodes->Add("b");
	//	Favour->Items->Add(managed);

	}
	private: System::Void DeleteToFavourClick(System::Object^  sender, System::EventArgs^  e) 
	{

	}
	private: System::Void SelectNodeTree(System::Object^  sender, System::Windows::Forms::TreeViewEventArgs^  e) 
	{
		if (!AlltreeView->SelectedNode )
			return;
		bool bInTree = false;

		if (AlltreeView->SelectedNode->Level == 0 )
			return;

		int index = this->AlltreeView->SelectedNode->Index;
		//	index = AlltreeView->SelectedNode->Index;

		ProtoParamList->Items->Clear();

		auto pname = gcnew String(Protos[index].name.c_str());

		ProtoName->Text = pname;
		DiscriptionLabel->Text = gcnew String(fm.LoadProtoName(Protos[index].pid * 100 + 1).c_str());

		for (int i = 0; i < Protos[index].Params.size(); i++)
		{

			auto param = gcnew String(Protos[index].Params[i].substr(0, Protos[index].Params[i].length() - 1).c_str());
			ProtoParamList->Items->Add(param);


		}
		if (!last_param_selected.empty())
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
				return;

			//last_param_selected;
			auto value = gcnew String(Protos[index].Values[param_index].c_str());
			auto param = gcnew String(Protos[index].Params[param_index].substr(0, Protos[index].Params[param_index].length() - 1).c_str());

			auto pname = gcnew String(Protos[index].name.c_str());
			ProtoName->Text = pname;

			ParamLabel->Text = param;
			ValuesTextBox->Text = value;
		}
	}
	
	private: System::Void ProgressBar(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) 
	{
		
		while (true)
		{
			if (backgroundWorker1->CancellationPending || IsLoaded ) //if it was cancelled
			{
				e->Cancel = true;
				break;
			}
			if (progressBar->Value != fm.progress)
				backgroundWorker1->ReportProgress(1);

			  //reporting progress
		//	this->Thread::Sleep(1000);   //wait for 1 second
		}
		
	}
	private: System::Void backgroundWorker1_ProgressChanged(System::Object^  sender, System::ComponentModel::ProgressChangedEventArgs^  e) 
	{
		progressBar->Value = fm.progress;//e->ProgressPercentage;
//		progressBar->PerformStep();
	}
};
}
