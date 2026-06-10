#pragma once
#include <cmath>
#include <iostream>
#include <vector>
namespace CppCLRWinFormsProject {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Drawing2D;
	using namespace System::Collections::Generic;
	public ref class Diffraction : public System::Windows::Forms::Form
	{
	public:
		Diffraction(void)
		{
			InitializeComponent();
			this->DoubleBuffered = true;
			this->Text = "Multiple-Slit Diffraction Simulation";
			this->BackColor = Color::White;
			this->ResizeRedraw = true;
			this->slitHeight = 10e-6;
			this->wavelength = 30e-9;
			this->timer1->Start();
			ToolTip^ toolTip = gcnew ToolTip();
			toolTip->SetToolTip(trackBar1, "Set the wavelength of the wave in nanometers.");
			toolTip1->SetToolTip(this->textBox1, "Enter a custom wavelength in nanometers.");
			toolTip1->SetToolTip(this->textBox2, "Enter a custom slit height in micrometers.");
			toolTip1->SetToolTip(this->button3, "Apply the custom wavelength.");
			toolTip1->SetToolTip(this->button4, "Apply the custom slit height.");
			toolTip1->SetToolTip(this->button2, "Add another slit to the barrier. More slits produce sharper fringes.");
			toolTip1->SetToolTip(this->button1, "Restart the simulation.");
			toolTip1->SetToolTip(this->trackBar3, "Set the distance between slits in micrometers.");
			toolTip1->SetToolTip(this->trackBar2, "Set the slit height in micrometers.");
			toolTip1->SetToolTip(this->label1, "Wavelength-distance between wave peaks. Equation: d·sin(theta) = n·lambda ");
			toolTip1->SetToolTip(this->label4, "Slit spacing-distance between adjacent slits in a double-slit setup. Larger spacing produces narrower pattern. ");
			toolTip1->SetToolTip(this->label2, "Slit height affects diffraction spread vertically.");
		}


	protected:
		~Diffraction()
		{
			if (components)
			{
				delete components;
			}

		}

	private:System::Windows::Forms::TrackBar^ trackBar1; //trackbar to chage wavelength
	private: System::ComponentModel::IContainer^ components;
	private: System::Windows::Forms::TrackBar^ trackBar2;  //trackbar to change slit width
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TrackBar^ trackBar3;
	private: System::Windows::Forms::Label^ label4;
		   Button^ toggleSecondSlitButton;
#pragma region Windows Form Designer generated code
		   double phaseShift = 0.0;
		   double slitHeight;
		   double wavelength;
		   double time;
		   bool showSecondSlit = false;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox2;

	private: System::Windows::Forms::Button^ button4;



		   void InitializeComponent(void)
		   {
			   this->components = (gcnew System::ComponentModel::Container());
			   this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			   this->trackBar2 = (gcnew System::Windows::Forms::TrackBar());
			   this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->trackBar3 = (gcnew System::Windows::Forms::TrackBar());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->button3 = (gcnew System::Windows::Forms::Button());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->button4 = (gcnew System::Windows::Forms::Button());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->BeginInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->BeginInit();
			   this->SuspendLayout();
			   //
			   // trackBar1
			   //
			   this->trackBar1->Location = System::Drawing::Point(49, 46);
			   this->trackBar1->Margin = System::Windows::Forms::Padding(2);
			   this->trackBar1->Maximum = 200;
			   this->trackBar1->Minimum = 30;
			   this->trackBar1->Name = L"trackBar1";
			   this->trackBar1->Size = System::Drawing::Size(137, 56);
			   this->trackBar1->TabIndex = 1;
			   this->trackBar1->TickFrequency = 10;
			   this->trackBar1->Value = 30;
			   this->trackBar1->Scroll += gcnew System::EventHandler(this, &Diffraction::trackBar1_Scroll);
			   //
			   // trackBar2
			   //
			   this->trackBar2->Location = System::Drawing::Point(49, 136);
			   this->trackBar2->Margin = System::Windows::Forms::Padding(2);
			   this->trackBar2->Maximum = 100;
			   this->trackBar2->Minimum = 10;
			   this->trackBar2->Name = L"trackBar2";
			   this->trackBar2->Size = System::Drawing::Size(126, 56);
			   this->trackBar2->TabIndex = 2;
			   this->trackBar2->Value = 10;
			   this->trackBar2->Scroll += gcnew System::EventHandler(this, &Diffraction::trackBar2_Scroll);
			   //
			   // timer1
			   //
			   this->timer1->Interval = 10;
			   this->timer1->Tick += gcnew System::EventHandler(this, &Diffraction::timer1_Tick);
			   //
			   // label1
			   //
			   this->label1->AutoSize = true;
			   this->label1->Location = System::Drawing::Point(75, 104);
			   this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(75, 16);
			   this->label1->TabIndex = 3;
			   this->label1->Text = L"wavelength";
			   this->toolTip1->SetToolTip(this->label1, L"Equation for wave: y(x,t) = A * sin(2π(x / λ - t / T))");
			   //
			   // label2
			   //
			   this->label2->AutoSize = true;
			   this->label2->Location = System::Drawing::Point(85, 185);
			   this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(62, 16);
			   this->label2->TabIndex = 4;
			   this->label2->Text = L"slit height";
			   //
			   // button1
			   //
			   this->button1->Location = System::Drawing::Point(72, 436);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(75, 23);
			   this->button1->TabIndex = 5;
			   this->button1->Text = L"refresh";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &Diffraction::button1_Click);
			   //
			   // button2
			   //
			   this->button2->Location = System::Drawing::Point(78, 232);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(75, 23);
			   this->button2->TabIndex = 6;
			   this->button2->Text = L"add slit";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &Diffraction::ToggleSecondSlit);
			   //
			   // label3
			   //
			   this->label3->AutoSize = true;
			   this->label3->Location = System::Drawing::Point(82, 271);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(68, 16);
			   this->label3->TabIndex = 7;
			   this->label3->Text = L"double slit";
			   //
			   // trackBar3
			   //
			   this->trackBar3->Location = System::Drawing::Point(55, 308);
			   this->trackBar3->Maximum = 100;
			   this->trackBar3->Minimum = 10;
			   this->trackBar3->Name = L"trackBar3";
			   this->trackBar3->Size = System::Drawing::Size(104, 56);
			   this->trackBar3->TabIndex = 8;
			   this->trackBar3->Value = 10;
			   this->trackBar3->Scroll += gcnew System::EventHandler(this, &Diffraction::trackBar3_Scroll);
			   //
			   // label4
			   //
			   this->label4->AutoSize = true;
			   this->label4->Location = System::Drawing::Point(75, 358);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(74, 16);
			   this->label4->TabIndex = 9;
			   this->label4->Text = L"slit spacing";
			   //
			   // textBox1
			   //
			   this->textBox1->Location = System::Drawing::Point(231, 46);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(55, 22);
			   this->textBox1->TabIndex = 10;

			   //
			   // button3
			   //
			   this->button3->Location = System::Drawing::Point(220, 97);
			   this->button3->Name = L"button3";
			   this->button3->Size = System::Drawing::Size(75, 23);
			   this->button3->TabIndex = 11;
			   this->button3->Text = L"set value";
			   this->button3->UseVisualStyleBackColor = true;
			   this->button3->Click += gcnew System::EventHandler(this, &Diffraction::button3_Click);
			   //
			   // textBox2
			   //
			   this->textBox2->Location = System::Drawing::Point(231, 149);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(55, 22);
			   this->textBox2->TabIndex = 12;

			   //
			   // button4
			   //
			   this->button4->Location = System::Drawing::Point(220, 185);
			   this->button4->Name = L"button4";
			   this->button4->Size = System::Drawing::Size(75, 23);
			   this->button4->TabIndex = 13;
			   this->button4->Text = L"set value";
			   this->button4->UseVisualStyleBackColor = true;
			   this->button4->Click += gcnew System::EventHandler(this, &Diffraction::button4_Click);
			   //
			   // Diffraction
			   //
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(1509, 675);
			   this->Controls->Add(this->button4);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->button3);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->trackBar3);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->button1);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->trackBar2);
			   this->Controls->Add(this->trackBar1);
			   this->Margin = System::Windows::Forms::Padding(2);
			   this->Name = L"MyForm";
			   this->Text = L"Diffraction Simulation";
			   this->Load += gcnew System::EventHandler(this, &Diffraction::MyForm_Load);
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar2))->EndInit();
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar3))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

	protected:
		virtual void OnPaint(PaintEventArgs^ e) override
		{
			Graphics^ g = e->Graphics;
			g->SmoothingMode = Drawing2D::SmoothingMode::AntiAlias;
			Rectangle clientRect = this->ClientRectangle;
			double pixelWavelength = wavelength * 1e9;
			int centerY = clientRect.Height / 2;
			int centerX = clientRect.Width / 2;
			int width = this->ClientSize.Width;
			int height = this->ClientSize.Height;
			float slitX = width / 2.0f;
			double lambda = trackBar1->Value;
			double speed = 2.0;
			int totalHeight = this->ClientSize.Height;
			int slitPixelHeight = trackBar2->Value;
			int lineWidth = 4;
			int slitSpacing = trackBar3->Value;
			int centerSlitY = this->ClientSize.Height / 2;
			int totalSlitHeight = slitPixelHeight;
			int wavelengthPx = trackBar1->Value;
			int numSources = Math::Max(2, slitPixelHeight / 10);
			double spacing = (double)slitPixelHeight / (numSources - 1);
			Pen^ inputPen = gcnew Pen(Color::Blue);
			Pen^ diffractionPen = gcnew Pen(Color::Red);
			Brush^ slitBrush = Brushes::Black;
			//draw incoming straight wavefronts
			for (double shiftedX = fmod(phaseShift, lambda); shiftedX < centerX; shiftedX += lambda) {
				g->DrawLine(inputPen, (float)shiftedX, 0.0f, (float)shiftedX, (float)height);
			}

			if (showSecondSlit)
			{
				totalSlitHeight += 10 + slitPixelHeight; // spacing + second slit
			}

			g->FillRectangle(Brushes::Black, Rectangle(centerX - lineWidth / 2, 0, lineWidth, totalHeight));

			// first slit
			int firstSlitTop = centerSlitY - totalSlitHeight / 2;
			g->FillRectangle(Brushes::White, Rectangle(centerX - lineWidth / 2, firstSlitTop, lineWidth, slitPixelHeight));

			//  second slit
			if (showSecondSlit)
			{
				int slitSpacing = trackBar3->Value;
				int secondSlitTop = firstSlitTop + slitPixelHeight + slitSpacing;
				g->FillRectangle(Brushes::White, Rectangle(centerX - lineWidth / 2, secondSlitTop, lineWidth, slitPixelHeight));
			}

			List<int>^ slitCenters = gcnew List<int>(); //storin center positions
			slitCenters->Add(centerY);


			if (showSecondSlit)
			{
				int secondCenterY = centerSlitY + slitPixelHeight + slitSpacing;
				slitCenters->Add(secondCenterY);
			}

			for (int s = 0; s < slitCenters->Count; ++s)
			{
				int currentCenterY = slitCenters[s];
				Color waveColor = (s == 0) ? Color::Red : Color::Green;

				for (int i = 0; i < numSources; ++i)
				{
					double sourceY = currentCenterY - slitPixelHeight / 2.0 + i * spacing;

					for (int r = 0; r < this->ClientSize.Width - centerX; r += wavelengthPx)
					{
						int radius = r + (int)(phaseShift) % wavelengthPx;
						if (radius <= 0 || radius > this->ClientSize.Width) continue;

						Rectangle circleBounds(centerX + 1 - radius, sourceY - radius, 2 * radius, 2 * radius);
						g->DrawArc(gcnew Pen(waveColor, 1), circleBounds, -40, 80);
					}
				}
			}
		}

	private: System::Void trackBar1_Scroll(System::Object^ sender, System::EventArgs^ e) {
		wavelength = trackBar1->Value * 1e-9;
		label1->Text = "wavelength: " + (trackBar1->Value + "nm");
		this->Invalidate();

	}
	private: System::Void trackBar2_Scroll(System::Object^ sender, System::EventArgs^ e) {
		slitHeight = trackBar2->Value * 1e-6;
		label2->Text = "slit height: " + (trackBar2->Value + "µm");
		this->Invalidate();
	}
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		phaseShift += 0.5;
		this->Invalidate();
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		trackBar1->Value = 30;
		label1->Text = "wavelength";
		trackBar2->Value = 10;
		label2->Text = "slit height";
		trackBar3->Value = 10;
		showSecondSlit = false;
		label4->Text = "slit spacing";
		textBox1->Text = "";
		textBox2->Text = "";
		this->Invalidate();
	}
	private: System::Void ToggleSecondSlit(System::Object^ sender, System::EventArgs^ e) {
		showSecondSlit = !showSecondSlit;
		this->Invalidate();
	}
	private: System::Void trackBar3_Scroll(System::Object^ sender, System::EventArgs^ e) {
		int slitSpacing = trackBar3->Value;
		label4->Text = "slit spacing:" + (trackBar3->Value + "µm");
		this->Invalidate();
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		double newWavelength = Convert::ToDouble(textBox1->Text);
		if (newWavelength > 0) {
			trackBar1->Value = (int)newWavelength;
			wavelength = newWavelength;
			Invalidate();

		}
	}

	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {

		double newSlitHeight = Convert::ToDouble(textBox2->Text);
		if (newSlitHeight > 0) {
			trackBar2->Value = (int)newSlitHeight;
			wavelength = newSlitHeight;
			Invalidate();

		}
	}

	};
}