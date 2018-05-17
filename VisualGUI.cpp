// ConsoleApplication1.cpp : Defines the entry point for the console application.
//
//#include "stdafx.h"
#include "SERIAL.h"
#include "MyForm.h"


//using namespace std;
using namespace System;
using namespace System::Windows::Forms;
using namespace System::Windows::Forms::DataVisualization::Charting;

// application reads data from ultrasound sensor and plots it


[STAThread]
int main(array<String^>^ args)
{
	
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	radar_gui::MyForm form;
	Application::Run(%form);

	return 0;
}

void radar_gui::MyForm::receive_serial_data()
{
	
	readFile.open("C:\\Python27\\data3.txt");
	
	if (readFile.is_open()) {

		
		while (!readFile.eof()) {

			readFile >> current_angle;

			if (current_angle <= 165 && current_angle >= 15) {

				readFile >> distance;

				if (distance >= 0 && distance < 100) {

					if ( ( (current_angle > previous_angle) && (current_angle < (previous_angle + 5)) ) || ( (current_angle > (previous_angle - 5)) && (current_angle < previous_angle) ) || previous_angle == 181)
					{
						textBox1->Text = distance + "";
						chart2->Series["Series1"]->Points->AddXY(current_angle, distance);
					}
				}
				else if (distance >= 100) {
					chart2->Series["Series1"]->Points->AddXY(current_angle, 100);
				}
				
				if (current_angle == 165 || current_angle == 15) {
					//break;
				}
				previous_angle = current_angle;
			}
			else {
				readFile >> distance;

				if ((distance == previous_angle + 1) || (distance == previous_angle - 1)) {
					readFile >> distance;
				}
			}	
		}
	}
	readFile.close();
}

void radar_gui::MyForm::load_charts()
{

	chart2->Series["Series1"]->BorderWidth = 5;
	chart2->ChartAreas["area"]->AxisX->Enabled = DataVisualization::Charting::AxisEnabled::True;
	chart2->ChartAreas["area"]->AxisX->Minimum = -100;
	chart2->ChartAreas["area"]->AxisX->Maximum = 100;
	chart2->ChartAreas["area"]->AxisX->Interval = 5;
	chart2->ChartAreas["area"]->AxisY->Minimum = 0;
	chart2->ChartAreas["area"]->AxisY->Maximum = 100;
	chart2->ChartAreas["area"]->AxisY->Interval = 5;
	
}

void radar_gui::MyForm::plot()
{
	double x_coord = 0.0;
	double y_coord = 0.0;
	chart2->Series["Series1"]->Points->Clear();
	chart2->Series["Series2"]->Points->Clear();
	for (int i = 15; i < 166; i++) {
		x_coord = data[i] * cos(i * 3.1415 / 180);
		y_coord = data[i] * sin(i * 3.1415 / 180);

		if ( data[i] < 20 ) {
			chart2->Series["Series1"]->Color = Color::FromArgb(255, 255, 0, 0);
			chart2->Series["Series1"]->Points->AddXY(x_coord, y_coord);
		}
		else {
			chart2->Series["Series2"]->Color = Color::FromArgb(255, 0, 0, 255);
			chart2->Series["Series2"]->Points->AddXY(x_coord, y_coord);
		}
		

	}
	textBox1->Text = "Data Plotted!";
}

void radar_gui::MyForm::scan_180()
{
	while (!complete) {
		textBox1->Text = "Collecting Data...";
		data_string = exec("C:\\Python27\\python.exe C:\\Serial.py");
	}
	

	std::string delimiter = " ";
	int number = 1;
	size_t pos = 0;
	std::string token;
	while ((pos = data_string.find(delimiter)) != std::string::npos) {
		token = data_string.substr(0, pos);
		if (number == 0) {
			std::istringstream ss(token);
			ss >> current_angle;
			//current_angle = std::stoi(token, NULL, 10);
			number++;
		}
		else {
			std::istringstream ss2(token);
			ss2 >> data[current_angle];
			//data[current_angle] = std::stoi(token, NULL, 10);
			number = 0;
		}
		data_string.erase(0, pos + delimiter.length());
	}

	plot();

}
