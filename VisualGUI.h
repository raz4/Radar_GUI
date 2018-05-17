

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <iostream>

#include <stdexcept>
#include <array>
#include <sstream>
#include <xtgmath.h>
#include <cstdio>
#include <msclr\marshal_cppstd.h>
#include <ctime>
#include <cmath>
#include <iomanip> // stream manipulators (setw, fixed, etc.)
#include <fstream> // file i/o operations
#include <math.h> // math
#include <conio.h> // math
#include <cstring> // memset
#include <vector> // used in gauss
#include <cmath> // used in gauss
#include <algorithm>    // std::min_element, std::max_element
#include <memory>
#include <cstdio>
//#include "stdafx.h"

#pragma once

// connect to COM6 serial port
//SERIAL* SP = new SERIAL("\\\\.\\COM6");    // adjust as needed



//char incomingData[256] = "1";			// don't forget to pre-allocate memory

//int dataLength = 255;
//int readResult = 0;


//int distance[180] ;
int angle[180] ;

int data[180] = { 0 };

int distance = 0;

int current_angle = 0;

bool clear = false;

int previous_angle = 181;

bool complete = false;

std::string data_string = "0";

//std::fstream outputFile;
std::ifstream readFile;

namespace radar_gui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: 
			//Add the constructor code here
			//

			load_charts();

		}

		void receive_serial_data();

		void load_charts();

		void plot();

		std::string exec(const char* cmd) {
			textBox1->Text = "Collecting Data...";
			std::shared_ptr<FILE> pipe(_popen(cmd, "r"), _pclose);
			if (!pipe) return "ERROR";
			char buffer[128];
			std::string result = "";
			int number = 0;
			while (!feof(pipe.get())) {
				if (fgets(buffer, 128, pipe.get()) != NULL)
				{
					result += buffer;
				}
					
			}
			complete = true;
			return result;
		}

		void scan_180();

		

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Label^  label1;
	protected:
	private: System::Windows::Forms::TextBox^  textBox1;
	private: System::Windows::Forms::Timer^  timer1;
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^  chart2;
	private: System::Windows::Forms::Button^  button2;
	private: System::ComponentModel::IContainer^  components;

	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Series^  series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::Series^  series2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->chart2 = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->button2 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->BeginInit();
			this->SuspendLayout();
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(34, 47);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(40, 13);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Status:";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(92, 44);
			this->textBox1->Name = L"textBox1";
			this->textBox1->ReadOnly = true;
			this->textBox1->Size = System::Drawing::Size(82, 20);
			this->textBox1->TabIndex = 1;
			// 
			// timer1
			// 
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(37, 88);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(164, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"180 Scan";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(34, 72);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 13);
			this->label2->TabIndex = 0;
			// 
			// chart2
			// 
			chartArea1->AxisX->Interval = 10;
			chartArea1->AxisX->Maximum = 100;
			chartArea1->AxisX->Minimum = -100;
			chartArea1->AxisY->Interval = 10;
			chartArea1->AxisY->Maximum = 100;
			chartArea1->AxisY->Minimum = 0;
			chartArea1->Name = L"area";
			this->chart2->ChartAreas->Add(chartArea1);
			this->chart2->Location = System::Drawing::Point(250, 12);
			this->chart2->Name = L"chart2";
			series1->ChartArea = L"area";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Point;
			series1->Name = L"Series1";
			series2->ChartArea = L"area";
			series2->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastPoint;
			series2->Name = L"Series2";
			this->chart2->Series->Add(series1);
			this->chart2->Series->Add(series2);
			this->chart2->Size = System::Drawing::Size(753, 389);
			this->chart2->TabIndex = 8;
			this->chart2->Text = L"chart2";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(37, 137);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(164, 23);
			this->button2->TabIndex = 9;
			this->button2->Text = L"Clear Graph";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click_1);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1039, 448);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->chart2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->chart2))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

private: System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e) {
	timer1->Stop();
	receive_serial_data();
	timer1->Start();
}
private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {

	complete = false;
	scan_180();

}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {


}
private: System::Void button3_Click(System::Object^  sender, System::EventArgs^  e) {

	

}
private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e) {

	//load_charts();

}
private: System::Void button2_Click_1(System::Object^  sender, System::EventArgs^  e) {

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	SECURITY_ATTRIBUTES SA = { 0 };

	SA.nLength = sizeof(SECURITY_ATTRIBUTES);
	SA.bInheritHandle = TRUE;
	char text2[] = "C:\\data3.txt";
	wchar_t wtext3[100];
	mbstowcs(wtext3, text2, strlen(text2) + 1);//Plus null
	LPWSTR ptr2 = wtext3;
	HANDLE hFileOut = ::CreateFile(ptr2, GENERIC_WRITE,
		FILE_SHARE_WRITE,
		&SA,
		OPEN_ALWAYS,
		FILE_ATTRIBUTE_NORMAL,
		0);
	ZeroMemory(&si, sizeof(si));
	si.cb = sizeof(si);
	si.cb = sizeof(STARTUPINFO);
	si.dwFlags = STARTF_USESTDHANDLES;
	si.hStdOutput = hFileOut;
	ZeroMemory(&pi, sizeof(pi));
	//BOOL WINAPI CreateProcess;

	//std::string text1 = "C:\\Python27\\python.exe Serial.py > data.txt";
	//const char* text2 = text1.c_str();
	//char* final = new char[text1.length() + 1];
	//strcpy(final, text2);

	char text[] = "C:\\Python27\\python.exe C:\\Serial2.py";
	wchar_t wtext[100];
	mbstowcs(wtext, text, strlen(text) + 1);//Plus null
	LPWSTR ptr = wtext;

	CreateProcess(NULL, ptr, NULL, NULL, FALSE, NULL, NULL, NULL, &si, &pi);
	system("C:\\Python27\\python.exe C:\\Serial2.py > text4.txt");
	::CloseHandle(pi.hThread);
	::CloseHandle(pi.hProcess);
	::CloseHandle(hFileOut);
}


};
}
