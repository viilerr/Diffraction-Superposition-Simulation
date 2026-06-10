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


	/// <summary>
	/// Summary for Form1
	/// </summary>
	public ref class Superposition : public System::Windows::Forms::Form
	{
	public:
		Superposition(void)
		{
			InitializeComponent();
			gridRows = 10;    // Fixed number of rows
			gridColumns = 10; // Fixed number of columns

			panel1->BackColor = System::Drawing::Color::LightGray; // panel background
			panel2->BackColor = System::Drawing::Color::LightGray; //panel background

			// Form settings
			this->Text = "Wave Superposition"; //page title
			this->DoubleBuffered = true;


			panel1->Visible = true; // when you open the page it opens panel 1 first (customizable)
			panel2->Visible = false; // panel 2 is hidden


			animationTimer = gcnew System::Windows::Forms::Timer();
			animationTimer->Interval = 30; // ~30ms for ~33 FPS
			animationTimer->Tick += gcnew System::EventHandler(this, &Superposition::OnAnimationTick);
			// Register event handler for resize
			this->Resize += gcnew EventHandler(this, &Superposition::OnResize);

			// Enable efficient painting
			this->SetStyle(ControlStyles::AllPaintingInWmPaint | ControlStyles::UserPaint | ControlStyles::ResizeRedraw, true);
			//this->SetStyle(ControlStyles::AllPaintingInWmPaint | ControlStyles::UserPaint | ControlStyles::ResizeRedraw, true);
			textBox1->BackColor = System::Drawing::Color::LightSteelBlue;
			textBox3->BackColor = System::Drawing::Color::LightSteelBlue;
			textBox5->BackColor = System::Drawing::Color::LightSteelBlue;

			textBox2->BackColor = System::Drawing::Color::PaleGreen;
			textBox4->BackColor = System::Drawing::Color::PaleGreen;
			textBox6->BackColor = System::Drawing::Color::PaleGreen;



		}


	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Superposition()
		{
			if (components)
			{
				delete components;
			}
		}
		// these are the initialised componentent so they're defined
		double amplitude1 = 1.0;
		double amplitude2 = 1.0;
		double frequency1 = 15;
		double frequency2 = 10;
		double phase1 = 3.14;
		double phase2 = 1.0;
		double time = 1.0;
		int gridRows;
		int gridColumns;

	private:
		bool animatingwave1 = false;
		double globalTimewave1 = 0.0;
		bool animatingwave2 = false;
		double globalTimewave2 = 0.0;
		Timer^ animationTimer;
	private: System::Windows::Forms::Panel^ panel1;
	private: System::Windows::Forms::CheckBox^ checkBox2;
	private: System::Windows::Forms::CheckBox^ checkBox1;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::CheckBox^ checkBox3;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::ToolTip^ toolTip1;
	private: System::Windows::Forms::ToolTip^ toolTip2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Timer^ timer1;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ customisableControlsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ preSetWavesToolStripMenuItem;
	private: System::Windows::Forms::Panel^ panel2;
	protected:




		bool drawWaves = true;
	private: System::Windows::Forms::CheckBox^ beatscheckbox;
	private: System::Windows::Forms::CheckBox^ interferencecheckbox;
	private: System::Windows::Forms::CheckBox^ standingwavecheckbox;
	protected:



	private: System::Windows::Forms::CheckBox^ checkBox5;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label16;

	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label21;



	protected:


	private: System::Windows::Forms::HScrollBar^ hScrollBar1;
	protected:
		// Resize
		void OnResize(Object^ sender, EventArgs^ e)
		{
			// Trigger a repaint of the form whenever the window is resized
			this->Invalidate();
		}


		//
		void OnPaint(PaintEventArgs^ e) override {

			// paint fucntion where it draws directy onto the background rather than using a picturebox
			Graphics^ g = e->Graphics;
			Rectangle clientRect = this->ClientRectangle;

			// Calculate cell size based on form size
			int cellWidth = (clientRect.Width) / gridColumns;
			int cellHeight = (clientRect.Height) / gridRows;

			// Create a pen to draw the grid lines
			Pen^ gridPen = gcnew Pen(Color::DimGray);

			// Draw the vertical lines of the grid
			for (int i = 0; i <= gridColumns; ++i)
			{
				g->DrawLine(gridPen, i * cellWidth, 0, i * cellWidth, clientRect.Height);
			}

			// Draw the horizontal lines of the grid
			for (int i = 0; i <= gridRows; ++i)
			{
				g->DrawLine(gridPen, 0, i * cellHeight, clientRect.Width, i * cellHeight);
			}


			// Scale the graph to fit the window for the wave to be centered
			double centerY = clientRect.Height / 2;
			double timeStep = 0.1;
			// i given each wave a colour to identify
			Pen^ penWave1 = gcnew Pen(Color::DeepSkyBlue, 2);
			Pen^ penWave2 = gcnew Pen(Color::ForestGreen, 2);
			Pen^ penSuperposition = gcnew Pen(Color::HotPink, 2);
			if (drawWaves) {
				for (double x = 1.0; x < clientRect.Width; x += 1.0)
				{
					if (this->checkBox1->Checked) // if checkbox 1 is ticked it then draws
					{
						double time1a = (x - 1) / 10.0;
						double time1b = x / 10.0;

						if (animatingwave1) { // this gives the wave motion
							time1a += globalTimewave1;
							time1b += globalTimewave1;
						}

						double y1a = centerY - wave(amplitude1, frequency1, phase1, time1a);
						double y1b = centerY - wave(amplitude1, frequency1, phase1, time1b);
						g->DrawLine(penWave1, Point(x - 1, y1a), Point(x, y1b)); // draws the line
					}
				}
				for (double x = 1.0; x < clientRect.Width; x += 1.0)
				{
					if (this->checkBox2->Checked) // if checkbox 2 is ticked it then draws
					{
						double timeA = (x - 1) / 10.0;
						double timeB = x / 10.0;

						if (animatingwave2) { // this gives the wave motion
							timeA += globalTimewave2;
							timeB += globalTimewave2;
						}

						double yA = centerY - wave(amplitude2, frequency2, phase2, timeA);
						double yB = centerY - wave(amplitude2, frequency2, phase2, timeB);

						g->DrawLine(penWave2, Point(x - 1, yA), Point(x, yB)); // draws the wave 2 line
					}
				}


				for (double x = 1.0; x < clientRect.Width; x += 1.0)
				{
					if (this->checkBox3->Checked) // if the superposition wave is ticked then it draws the wave on
					{
						double tA_base = (x - 1) / 10.0;
						double tB_base = x / 10.0;

						// Add animation for the wave animating
						double tA_wave1 = tA_base + (animatingwave1 ? globalTimewave1 : 0.0);
						double tB_wave1 = tB_base + (animatingwave1 ? globalTimewave1 : 0.0);

						double tA_wave2 = tA_base + (animatingwave2 ? globalTimewave2 : 0.0);
						double tB_wave2 = tB_base + (animatingwave2 ? globalTimewave2 : 0.0);

						// Calculate superposed y-values using updated waveSup
						double yA = centerY - waveSup(amplitude1, frequency1, phase1,
							amplitude2, frequency2, phase2,
							tA_wave1, tA_wave2);

						double yB = centerY - waveSup(amplitude1, frequency1, phase1,
							amplitude2, frequency2, phase2,
							tB_wave1, tB_wave2);

						g->DrawLine(penSuperposition, Point(x - 1, yA), Point(x, yB));  // draws the superpositon wave
					}
				}
				delete penWave1;
				delete penWave2;
				delete penSuperposition;
			}



			delete gridPen;
		}

	private: System::Windows::Forms::HScrollBar^ hScrollBar2;
	private: System::Windows::Forms::HScrollBar^ hScrollBar3;
	private: System::Windows::Forms::HScrollBar^ hScrollBar4;
	private: System::Windows::Forms::HScrollBar^ hScrollBar5;
	private: System::Windows::Forms::HScrollBar^ hScrollBar6;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;



	private: System::Void OnAnimationTick(System::Object^ sender, System::EventArgs^ e) {
		if (animatingwave1)
			globalTimewave1 += 0.1; // adjust timestep as needed
		if (animatingwave2)
			globalTimewave2 += 0.1; // adjust timestep
		Invalidate();

	}



	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
				  // these are my compnent in my designer form                
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->hScrollBar1 = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBar2 = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBar3 = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBar4 = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBar5 = (gcnew System::Windows::Forms::HScrollBar());
			this->hScrollBar6 = (gcnew System::Windows::Forms::HScrollBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->panel1 = (gcnew System::Windows::Forms::Panel());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->checkBox1 = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox3 = (gcnew System::Windows::Forms::CheckBox());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->checkBox2 = (gcnew System::Windows::Forms::CheckBox());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->interferencecheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->standingwavecheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox5 = (gcnew System::Windows::Forms::CheckBox());
			this->beatscheckbox = (gcnew System::Windows::Forms::CheckBox());
			this->toolTip1 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->toolTip2 = (gcnew System::Windows::Forms::ToolTip(this->components));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->customisableControlsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->preSetWavesToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->panel1->SuspendLayout();
			this->panel2->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			//
			//
			//
			// each of these are how i have editted the properites of the components
			// hScrollBar1
			//
			this->hScrollBar1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->hScrollBar1->LargeChange = 1;
			this->hScrollBar1->Location = System::Drawing::Point(45, 65);
			this->hScrollBar1->Name = L"hScrollBar1";
			this->hScrollBar1->Size = System::Drawing::Size(206, 26);
			this->hScrollBar1->TabIndex = 0;
			this->hScrollBar1->Value = 1;
			this->hScrollBar1->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Superposition::hScrollBar1_Scroll);
			//
			// hScrollBar2
			//
			this->hScrollBar2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->hScrollBar2->LargeChange = 1;
			this->hScrollBar2->Location = System::Drawing::Point(44, 465);
			this->hScrollBar2->Name = L"hScrollBar2";
			this->hScrollBar2->Size = System::Drawing::Size(206, 26);
			this->hScrollBar2->TabIndex = 1;
			this->hScrollBar2->Value = 1;
			this->hScrollBar2->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Superposition::hScrollBar2_Scroll);
			//
			// hScrollBar3
			//
			this->hScrollBar3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->hScrollBar3->Location = System::Drawing::Point(45, 152);
			this->hScrollBar3->Name = L"hScrollBar3";
			this->hScrollBar3->Size = System::Drawing::Size(206, 26);
			this->hScrollBar3->SmallChange = 10;
			this->hScrollBar3->TabIndex = 1;
			this->hScrollBar3->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Superposition::hScrollBar3_Scroll);
			//
			// hScrollBar4
			//
			this->hScrollBar4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->hScrollBar4->Location = System::Drawing::Point(50, 537);
			this->hScrollBar4->Name = L"hScrollBar4";
			this->hScrollBar4->Size = System::Drawing::Size(206, 26);
			this->hScrollBar4->SmallChange = 10;
			this->hScrollBar4->TabIndex = 3;
			this->hScrollBar4->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Superposition::hScrollBar4_Scroll);
			//
			// hScrollBar5
			//
			this->hScrollBar5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->hScrollBar5->LargeChange = 45;
			this->hScrollBar5->Location = System::Drawing::Point(45, 231);
			this->hScrollBar5->Maximum = 360;
			this->hScrollBar5->Name = L"hScrollBar5";
			this->hScrollBar5->Size = System::Drawing::Size(206, 26);
			this->hScrollBar5->SmallChange = 45;
			this->hScrollBar5->TabIndex = 4;
			this->hScrollBar5->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Superposition::hScrollBar5_Scroll);
			//
			// hScrollBar6
			//
			this->hScrollBar6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->hScrollBar6->LargeChange = 45;
			this->hScrollBar6->Location = System::Drawing::Point(50, 609);
			this->hScrollBar6->Maximum = 360;
			this->hScrollBar6->Name = L"hScrollBar6";
			this->hScrollBar6->Size = System::Drawing::Size(206, 26);
			this->hScrollBar6->SmallChange = 45;
			this->hScrollBar6->TabIndex = 45;
			this->hScrollBar6->Scroll += gcnew System::Windows::Forms::ScrollEventHandler(this, &Superposition::hScrollBar6_Scroll);
			//
			// label1
			//
			this->label1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(40, 118);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(97, 20);
			this->label1->TabIndex = 6;
			this->label1->Text = L"Frequency 1";
			//
			// label2
			//
			this->label2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(45, 505);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(97, 20);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Frequency 2";
			this->toolTip1->SetToolTip(this->label2, L" ");
			//
			// label3
			//
			this->label3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(45, 198);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(93, 20);
			this->label3->TabIndex = 8;
			this->label3->Text = L"Amplitude 1";
			//
			// label4
			//
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(944, 315);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(0, 20);
			this->label4->TabIndex = 9;
			//
			// label5
			//
			this->label5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(40, 275);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(67, 20);
			this->label5->TabIndex = 10;
			this->label5->Text = L"Phase 1";
			//
			// label6
			//
			this->label6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(40, 642);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(67, 20);
			this->label6->TabIndex = 11;
			this->label6->Text = L"Phase 2";
			//
			// label7
			//
			this->label7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(50, 580);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(93, 20);
			this->label7->TabIndex = 12;
			this->label7->Text = L"Amplitude 2";
			//
			// textBox1
			//
			this->textBox1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox1->Location = System::Drawing::Point(204, 192);
			this->textBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(48, 26);
			this->textBox1->TabIndex = 13;
			//
			// textBox2
			//
			this->textBox2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox2->Location = System::Drawing::Point(204, 574);
			this->textBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(48, 26);
			this->textBox2->TabIndex = 14;
			//
			// textBox3
			//
			this->textBox3->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox3->Location = System::Drawing::Point(204, 269);
			this->textBox3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(48, 26);
			this->textBox3->TabIndex = 15;
			//
			// textBox4
			//
			this->textBox4->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox4->Location = System::Drawing::Point(204, 638);
			this->textBox4->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(48, 26);
			this->textBox4->TabIndex = 16;
			//
			// textBox5
			//
			this->textBox5->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox5->Location = System::Drawing::Point(204, 112);
			this->textBox5->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(48, 26);
			this->textBox5->TabIndex = 17;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &Superposition::textBox5_TextChanged);
			//
			// textBox6
			//
			this->textBox6->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox6->Location = System::Drawing::Point(204, 505);
			this->textBox6->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(48, 26);
			this->textBox6->TabIndex = 18;
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &Superposition::textBox6_TextChanged);
			//
			// textBox7
			//
			this->textBox7->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox7->Location = System::Drawing::Point(112, 315);
			this->textBox7->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox7->Name = L"textBox7";
			this->textBox7->ReadOnly = true;
			this->textBox7->Size = System::Drawing::Size(166, 26);
			this->textBox7->TabIndex = 19;
			//
			// textBox8
			//
			this->textBox8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->textBox8->Location = System::Drawing::Point(112, 718);
			this->textBox8->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->textBox8->Name = L"textBox8";
			this->textBox8->ReadOnly = true;
			this->textBox8->Size = System::Drawing::Size(166, 26);
			this->textBox8->TabIndex = 20;
			//
			// label8
			//
			this->label8->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(3, 318);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(106, 20);
			this->label8->TabIndex = 21;
			this->label8->Text = L"Wavelength 1";
			this->toolTip1->SetToolTip(this->label8, L"Wavelength = wavespeed / Frequency ");
			//
			// label9
			//
			this->label9->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(3, 725);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(106, 20);
			this->label9->TabIndex = 22;
			this->label9->Text = L"Wavelength 2";
			this->toolTip2->SetToolTip(this->label9, L"Wavelength = wavespeed / Frequency");
			//
			// label10
			//
			this->label10->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Right));
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(108, 26);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(62, 20);
			this->label10->TabIndex = 16;
			this->label10->Text = L"Wave 1";
			this->label10->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->toolTip1->SetToolTip(this->label10, L"amplitude x sin(frequnecy x time + phase)");
			//
			// panel1
			//
			this->panel1->Controls->Add(this->button3);
			this->panel1->Controls->Add(this->button2);
			this->panel1->Controls->Add(this->button1);
			this->panel1->Controls->Add(this->checkBox1);
			this->panel1->Controls->Add(this->checkBox3);
			this->panel1->Controls->Add(this->label13);
			this->panel1->Controls->Add(this->checkBox2);
			this->panel1->Controls->Add(this->label12);
			this->panel1->Controls->Add(this->hScrollBar1);
			this->panel1->Controls->Add(this->textBox8);
			this->panel1->Controls->Add(this->label10);
			this->panel1->Controls->Add(this->hScrollBar2);
			this->panel1->Controls->Add(this->label2);
			this->panel1->Controls->Add(this->textBox2);
			this->panel1->Controls->Add(this->label7);
			this->panel1->Controls->Add(this->hScrollBar4);
			this->panel1->Controls->Add(this->textBox6);
			this->panel1->Controls->Add(this->label9);
			this->panel1->Controls->Add(this->label8);
			this->panel1->Controls->Add(this->textBox7);
			this->panel1->Controls->Add(this->label1);
			this->panel1->Controls->Add(this->textBox5);
			this->panel1->Controls->Add(this->hScrollBar3);
			this->panel1->Controls->Add(this->textBox4);
			this->panel1->Controls->Add(this->label3);
			this->panel1->Controls->Add(this->label6);
			this->panel1->Controls->Add(this->textBox3);
			this->panel1->Controls->Add(this->textBox1);
			this->panel1->Controls->Add(this->hScrollBar6);
			this->panel1->Controls->Add(this->label5);
			this->panel1->Controls->Add(this->hScrollBar5);
			this->panel1->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel1->Location = System::Drawing::Point(0, 33);
			this->panel1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->panel1->Name = L"panel1";
			this->panel1->Size = System::Drawing::Size(284, 842);
			this->panel1->TabIndex = 24;
			//
			// button3
			//
			this->button3->Location = System::Drawing::Point(58, 682);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(160, 31);
			this->button3->TabIndex = 47;
			this->button3->Text = L"Start Stop";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &Superposition::button3_Click);
			//
			// button2
			//
			this->button2->Location = System::Drawing::Point(58, 358);
			this->button2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(160, 31);
			this->button2->TabIndex = 46;
			this->button2->Text = L" Start  Stop ";
			this->toolTip1->SetToolTip(this->button2, L"Start or Stop animation");
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &Superposition::button2_Click);
			//
			// button1
			//
			this->button1->Location = System::Drawing::Point(100, 802);
			this->button1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(88, 58);
			this->button1->TabIndex = 25;
			this->button1->Text = L"Reset Values";
			this->toolTip1->SetToolTip(this->button1, L"Reset all wave values");
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Superposition::button1_Click);
			//
			// checkBox1
			//
			this->checkBox1->AutoSize = true;
			this->checkBox1->Location = System::Drawing::Point(218, 25);
			this->checkBox1->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->checkBox1->Name = L"checkBox1";
			this->checkBox1->Size = System::Drawing::Size(22, 21);
			this->checkBox1->TabIndex = 24;
			this->toolTip1->SetToolTip(this->checkBox1, L"Show on Grid");
			this->checkBox1->UseVisualStyleBackColor = true;
			this->checkBox1->CheckedChanged += gcnew System::EventHandler(this, &Superposition::checkBox1_CheckedChanged);
			//
			// checkBox3
			//
			this->checkBox3->AutoSize = true;
			this->checkBox3->Location = System::Drawing::Point(218, 765);
			this->checkBox3->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->checkBox3->Name = L"checkBox3";
			this->checkBox3->Size = System::Drawing::Size(22, 21);
			this->checkBox3->TabIndex = 27;
			this->toolTip1->SetToolTip(this->checkBox3, L"Show on Grid");
			this->checkBox3->UseVisualStyleBackColor = true;
			this->checkBox3->CheckedChanged += gcnew System::EventHandler(this, &Superposition::checkBox3_CheckedChanged);
			//
			// label13
			//
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(3, 765);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(151, 20);
			this->label13->TabIndex = 26;
			this->label13->Text = L"Wave Superposition";
			this->toolTip1->SetToolTip(this->label13, L"Wave1 + Wave 2");
			//
			// checkBox2
			//
			this->checkBox2->AutoSize = true;
			this->checkBox2->Location = System::Drawing::Point(218, 431);
			this->checkBox2->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->checkBox2->Name = L"checkBox2";
			this->checkBox2->Size = System::Drawing::Size(22, 21);
			this->checkBox2->TabIndex = 25;
			this->toolTip1->SetToolTip(this->checkBox2, L"Show on Grid");
			this->checkBox2->UseVisualStyleBackColor = true;
			this->checkBox2->CheckedChanged += gcnew System::EventHandler(this, &Superposition::checkBox2_CheckedChanged);
			//
			// label12
			//
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(111, 431);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(62, 20);
			this->label12->TabIndex = 23;
			this->label12->Text = L"Wave 2";
			this->toolTip1->SetToolTip(this->label12, L"amplitude x sin(frequnecy x time + phase)");
			//
			// panel2
			//
			this->panel2->Controls->Add(this->label14);
			this->panel2->Controls->Add(this->label11);
			this->panel2->Controls->Add(this->interferencecheckbox);
			this->panel2->Controls->Add(this->standingwavecheckbox);
			this->panel2->Controls->Add(this->checkBox5);
			this->panel2->Controls->Add(this->beatscheckbox);
			this->panel2->Dock = System::Windows::Forms::DockStyle::Left;
			this->panel2->Location = System::Drawing::Point(284, 33);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(284, 842);
			this->panel2->TabIndex = 26;
			//
			// label14
			//
			this->label14->Location = System::Drawing::Point(22, 65);
			this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(256, 60);
			this->label14->TabIndex = 31;
			this->label14->Text = L"Use this page to learn about the features of waves and their superpostion propert"
				L"ies";
			//
			// label11
			//
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(56, 25);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(169, 20);
			this->label11->TabIndex = 30;
			this->label11->Text = L"PreSet Wave features ";
			//
			// interferencecheckbox
			//
			this->interferencecheckbox->AutoSize = true;
			this->interferencecheckbox->Location = System::Drawing::Point(44, 166);
			this->interferencecheckbox->Name = L"interferencecheckbox";
			this->interferencecheckbox->Size = System::Drawing::Size(218, 24);
			this->interferencecheckbox->TabIndex = 29;
			this->interferencecheckbox->Text = L"Constructive Interference ";
			this->interferencecheckbox->UseVisualStyleBackColor = true;
			this->interferencecheckbox->CheckedChanged += gcnew System::EventHandler(this, &Superposition::constructiveinterferencecheckbox_CheckedChanged);
			//
			// standingwavecheckbox
			//
			this->standingwavecheckbox->AutoSize = true;
			this->standingwavecheckbox->Location = System::Drawing::Point(44, 358);
			this->standingwavecheckbox->Name = L"standingwavecheckbox";
			this->standingwavecheckbox->Size = System::Drawing::Size(147, 24);
			this->standingwavecheckbox->TabIndex = 28;
			this->standingwavecheckbox->Text = L"Standing waves";
			this->standingwavecheckbox->UseVisualStyleBackColor = true;
			this->standingwavecheckbox->CheckedChanged += gcnew System::EventHandler(this, &Superposition::standingwavecheckbox_CheckedChanged);
			//
			// checkBox5
			//
			this->checkBox5->AutoSize = true;
			this->checkBox5->Location = System::Drawing::Point(44, 198);
			this->checkBox5->Name = L"checkBox5";
			this->checkBox5->Size = System::Drawing::Size(210, 24);
			this->checkBox5->TabIndex = 27;
			this->checkBox5->Text = L"Destructive Interference ";
			this->checkBox5->UseVisualStyleBackColor = true;
			this->checkBox5->CheckedChanged += gcnew System::EventHandler(this, &Superposition::checkBox5_CheckedChanged);
			//
			// beatscheckbox
			//
			this->beatscheckbox->AutoSize = true;
			this->beatscheckbox->Location = System::Drawing::Point(44, 312);
			this->beatscheckbox->Name = L"beatscheckbox";
			this->beatscheckbox->Size = System::Drawing::Size(77, 24);
			this->beatscheckbox->TabIndex = 26;
			this->beatscheckbox->Text = L"Beats";
			this->beatscheckbox->UseVisualStyleBackColor = true;
			this->beatscheckbox->CheckedChanged += gcnew System::EventHandler(this, &Superposition::beatscheckbox_CheckedChanged);
			//
			// menuStrip1
			//
			this->menuStrip1->GripMargin = System::Windows::Forms::Padding(2, 2, 0, 2);
			this->menuStrip1->ImageScalingSize = System::Drawing::Size(24, 24);
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->toolStripMenuItem1 });
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(1514, 33);
			this->menuStrip1->TabIndex = 25;
			this->menuStrip1->Text = L"menuStrip1";
			//
			// toolStripMenuItem1
			//
			this->toolStripMenuItem1->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->customisableControlsToolStripMenuItem,
					this->preSetWavesToolStripMenuItem
			});
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(73, 29);
			this->toolStripMenuItem1->Text = L"Menu";
			this->toolStripMenuItem1->Click += gcnew System::EventHandler(this, &Superposition::toolStripMenuItem1_Click);
			//
			// customisableControlsToolStripMenuItem
			//
			this->customisableControlsToolStripMenuItem->Name = L"customisableControlsToolStripMenuItem";
			this->customisableControlsToolStripMenuItem->Size = System::Drawing::Size(298, 34);
			this->customisableControlsToolStripMenuItem->Text = L"Customisable Controls ";
			this->customisableControlsToolStripMenuItem->Click += gcnew System::EventHandler(this, &Superposition::customisableControlsToolStripMenuItem_Click);
			//
			// preSetWavesToolStripMenuItem
			//
			this->preSetWavesToolStripMenuItem->Name = L"preSetWavesToolStripMenuItem";
			this->preSetWavesToolStripMenuItem->Size = System::Drawing::Size(298, 34);
			this->preSetWavesToolStripMenuItem->Text = L"Pre Set Waves";
			this->preSetWavesToolStripMenuItem->Click += gcnew System::EventHandler(this, &Superposition::preSetWavesToolStripMenuItem_Click);
			//
			// label15
			//
			this->label15->Location = System::Drawing::Point(742, 89);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(524, 52);
			this->label15->TabIndex = 27;
			this->label15->Text = L"This shows constructive Interference.  The two waves are in-phase and so the ampl"
				L"itudes add to create a larger amplitude shown by the pink wave. ";
			this->label15->Visible = false;
			//
			// label16
			//
			this->label16->Location = System::Drawing::Point(746, 89);
			this->label16->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(519, 71);
			this->label16->TabIndex = 28;
			this->label16->Text = L"This shows Destructive interference where the waves are out of phase with each ot"
				L"her. This results in the overall amplitude of the wave to decrease as shown by t"
				L"he pink wave.";
			this->label16->Visible = false;
			//
			// label18
			//
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(671, 677);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(80, 20);
			this->label18->TabIndex = 30;
			this->label18->Text = L"Anti-Node";
			this->label18->Visible = false;
			//
			// label19
			//
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(559, 513);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(47, 20);
			this->label19->TabIndex = 32;
			this->label19->Text = L"Node";
			this->label19->Visible = false;
			//
			// label20
			//
			this->label20->Location = System::Drawing::Point(879, 820);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(623, 46);
			this->label20->TabIndex = 33;
			this->label20->Text = L"These nodes and anti-nodes remain in the same position when the two wavs move giv"
				L"ing the illusion the wave is not moving hence the name, standing waves";
			this->label20->Visible = false;
			//
			// label17
			//
			this->label17->Location = System::Drawing::Point(768, 79);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(611, 95);
			this->label17->TabIndex = 34;
			this->label17->Text = L"This is a Standing wave. These form when two waves of the same frequnecy and ampl"
				L"itude travel in opposite directions. They form maximum amplitude antinodes and m"
				L"inimum amplitude nodes ";
			this->label17->Visible = false;
			//
			// label21
			//
			this->label21->Location = System::Drawing::Point(744, 84);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(623, 76);
			this->label21->TabIndex = 35;
			this->label21->Text = L"The Pink wave shows beats. When waves have two slighty different frequencies and "
				L"they interfere, this creates a perception of fluctuating sound due to the amplit"
				L"udes. ";
			this->label21->Visible = false;
			//
			// Superposition
			//
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1514, 875);
			this->Controls->Add(this->label21);
			this->Controls->Add(this->label17);
			this->Controls->Add(this->label20);
			this->Controls->Add(this->label19);
			this->Controls->Add(this->label18);
			this->Controls->Add(this->label16);
			this->Controls->Add(this->label15);
			this->Controls->Add(this->panel2);
			this->Controls->Add(this->panel1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->menuStrip1);
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(3, 2, 3, 2);
			this->Name = L"Superposition";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Form 1 ";
			this->panel1->ResumeLayout(false);
			this->panel1->PerformLayout();
			this->panel2->ResumeLayout(false);
			this->panel2->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}




#pragma endregion
	private: System::Void hScrollBar1_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		frequency1 = hScrollBar1->Value; // the scroll bar value takes the value of component in the wave fucntion
		textBox5->Text = "" + hScrollBar1->Value; // the value of the scrollbar goes to the textbox
		textBox7->Invalidate();
		Invalidate();
	}
	private: System::Void hScrollBar2_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		frequency2 = hScrollBar2->Value; // the scroll bar value takes the value of component in the wave fucntion
		textBox6->Text = "" + hScrollBar2->Value; // the value of the scrollbar goes to the textbox
		textBox8->Invalidate();
		Invalidate();
	}
	private: System::Void hScrollBar3_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		amplitude1 = hScrollBar3->Value; // the scroll bar value takes the value of component in the wave fucntion
		textBox1->Text = "" + hScrollBar3->Value; // the value of the scrollbar goes to the textbox
		Invalidate();
	}
	private: System::Void hScrollBar4_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		amplitude2 = hScrollBar4->Value; // the scroll bar value takes the value of component in the wave fucntion
		textBox2->Text = "" + hScrollBar4->Value; // the value of the scrollbar goes to the textbox
		Invalidate();
	}
	private: System::Void hScrollBar5_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		phase1 = hScrollBar5->Value; // the scroll bar value takes the value of component in the wave fucntion
		textBox3->Text = "" + hScrollBar5->Value; // the value of the scrollbar goes to the textbox
		Invalidate();
	}
	private: System::Void hScrollBar6_Scroll(System::Object^ sender, System::Windows::Forms::ScrollEventArgs^ e) {
		phase2 = hScrollBar6->Value; // the scroll bar value takes the value of component in the wave fucntion
		textBox4->Text = "" + hScrollBar6->Value; // the value of the scrollbar goes to the textbox
		Invalidate();
	}
	private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e) { // this converts the value of frewuency into a wavelength value
		frequency1 = Convert::ToDouble(textBox5->Text);
		double wave1 = wavelength(frequency1); //calculates wavelgnth with the frewuency on trackbar
		textBox7->Text = wave1.ToString("F2") + " m"; // f2 means to 2 decimal places with the unit meters
		Invalidate();
	}
	private: System::Void textBox6_TextChanged(System::Object^ sender, System::EventArgs^ e) {  // this converts the value of frewuency into a wavelength value
		frequency2 = Convert::ToDouble(textBox6->Text);
		double wave2 = wavelength(frequency2);
		textBox8->Text = wave2.ToString("F2") + " m";
		Invalidate();
	}


	private: System::Void checkBox1_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {  // for wave 1
		{
			if (checkBox1->Checked) {
				// Enables the trackbars if the check box is ticked
				hScrollBar1->Enabled = true;
				hScrollBar3->Enabled = true;
				hScrollBar5->Enabled = true;


			}
			else {
				// Disables  the trackbars if check box un/ not ticked
				hScrollBar1->Enabled = false;
				hScrollBar3->Enabled = false;
				hScrollBar5->Enabled = false;
			}
		}


	}
	private: System::Void checkBox2_CheckedChanged(System::Object^ sender, System::EventArgs^ e) { // for wave two
		this->Invalidate();
		if (checkBox2->Checked) {
			// Enables the trackbars if the check box is ticked
			hScrollBar2->Enabled = true;
			hScrollBar4->Enabled = true;
			hScrollBar6->Enabled = true;


		}
		else {
			// Disables  the trackbars if check box no/ un  ticked
			hScrollBar2->Enabled = false;
			hScrollBar4->Enabled = false;
			hScrollBar6->Enabled = false;
		}

	}
	private: System::Void checkBox3_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		this->Invalidate();
	}

	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) { // reset the values for the wave fucntions
		hScrollBar1->Value = 10;
		textBox1->Text = "0";
		hScrollBar2->Value = 10;
		textBox2->Text = "0";
		hScrollBar3->Value = 10;
		textBox3->Text = "0";
		hScrollBar4->Value = 10;
		textBox4->Text = "0";
		hScrollBar5->Value = 10;
		textBox5->Text = "0";
		hScrollBar6->Value = 10;
		textBox6->Text = "0";
		textBox7->Text = "0";
		textBox8->Text = "0";
		this->Invalidate();
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {// animates wave 1
		// when button is pressed the wave either startes to move or stops moving due to the animating wave and global time
		// this changes the stop and start text on button  depending on if the wave is being animated of not
		if (animatingwave1 == false) {
			animationTimer->Start();
			globalTimewave1 = 0.0;
			animatingwave1 = true;
			button2->Text = "Stop Wave 1";
		}
		else if (animatingwave1 == true) {
			animationTimer->Stop();
			animatingwave1 = false;
			button2->Text = "Start Wave 1";
		}
		if (animatingwave1 || animatingwave2)
			animationTimer->Start();
		else
			animationTimer->Stop();


	}


	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) { // animates wave 2

		if (animatingwave2 == false) {
			animationTimer->Start();
			globalTimewave2 = 0.0;
			animatingwave2 = true;
			button3->Text = "Stop Wave 2";
		}
		else if (animatingwave2 == true) {
			animationTimer->Stop();
			animatingwave2 = false;
			button3->Text = "Start Wave 2";
		}
		if (animatingwave1 || animatingwave2)
			animationTimer->Start();
		else
			animationTimer->Stop();

	}




	private: System::Void customisableControlsToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		drawWaves = true; //enables the waves to be drawn on the screen
		panel1->Visible = true;
		panel1->BringToFront(); // brings the chosen panel to the front
		panel2->Visible = false; // only customizable showing
		panel2->Invalidate();

		//to deselect any preset wave aptterens o screen
		beatscheckbox->Checked = false;
		standingwavecheckbox->Checked = false;
		interferencecheckbox->Checked = false;
		checkBox5->Checked = false;

		//this is so when you go back to customisable it resets.
		amplitude1 = 0;
		amplitude2 = 0;
		frequency1 = 0;
		frequency2 = 0;
		phase1 = 0;
		phase2 = 0;


		hScrollBar1->Value = 0;
		hScrollBar2->Value = 0;
		textBox5->Text = "0";
		textBox6->Text = "0";

	}
	private: System::Void preSetWavesToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
		// Stop animation and disable wave drawing
		animationTimer->Stop();
		drawWaves = false;

		// Hide panel1 and show panel2
		panel1->Visible = false;
		panel2->Visible = true;

		// Bring panel2 to the front
		panel2->BringToFront();

		this->Invalidate();

	}
	private: System::Void toolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void beatscheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (beatscheckbox->Checked) {
			// Enable wave drawing
			label21->Visible = true;
			drawWaves = true;

			// Show all waves
			checkBox1->Checked = true; // Wave 1
			checkBox2->Checked = true; // Wave 2
			checkBox3->Checked = true; // Superposition

			//  parameters to create visible beats
			amplitude1 = 80;
			amplitude2 = 60;
			frequency1 = 61;
			frequency2 = 2; // small difference causes beats
			phase1 = 0;
			phase2 = 0;

			hScrollBar1->Value = 61;
			hScrollBar2->Value = 2;
			textBox5->Text = "61";
			textBox6->Text = "2";


		}
		else {
			// Uncheck all waves when checkbox is turned off
			checkBox1->Checked = false;
			checkBox2->Checked = false;
			checkBox3->Checked = false;
			label21->Visible = false;
			label4->Text = "";
		}

		Invalidate(); // Trigger redraw
	}


	private: System::Void constructiveinterferencecheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		//presset wave features
		if (interferencecheckbox->Checked) {
			drawWaves = true;
			label15->Visible = true;
			// Show all waves
			checkBox1->Checked = true; // Wave 1
			checkBox2->Checked = true; // Wave 2
			checkBox3->Checked = true; // Superposition
			// set parameters for feature
			amplitude1 = 70;
			amplitude2 = 40;
			frequency1 = 61;
			frequency2 = 61;
			phase1 = 0;
			phase2 = 0;
			// update the scroll bar ad etxt box values
			hScrollBar1->Value = 61;
			hScrollBar2->Value = 61;
			textBox5->Text = "61";
			textBox6->Text = "61";
			beatscheckbox->Checked = false;
			standingwavecheckbox->Checked = false;
			checkBox5->Checked = false;
		}
		else {
			// Uncheck all waves when checkbox is turned off
			checkBox1->Checked = false;
			checkBox2->Checked = false;
			checkBox3->Checked = false;
			label15->Visible = false;
			label4->Text = "";
		}

		Invalidate(); // Trigger redraw
	}


	private: System::Void checkBox5_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (checkBox5->Checked) {
			drawWaves = true;
			label16->Visible = true;
			// Show all waves
			checkBox1->Checked = true; // Wave 1
			checkBox2->Checked = true; // Wave 2
			checkBox3->Checked = true; // Superposition
			//set certian paramteres
			amplitude1 = 70;
			amplitude2 = 70;
			frequency1 = 61;
			frequency2 = 61;
			phase1 = 0;
			phase2 = 3.14;
			// upadate in in the extbox and scroll bar
			hScrollBar1->Value = 61;
			hScrollBar2->Value = 61;
			textBox5->Text = "61";
			textBox6->Text = "61";
			interferencecheckbox->Checked = false;
			beatscheckbox->Checked = false;
			standingwavecheckbox->Checked = false;

			beatscheckbox->Checked = false;
			standingwavecheckbox->Checked = false;
			interferencecheckbox->Checked = false;
		}
		else {
			// Uncheck all waves when checkbox is turned off
			checkBox1->Checked = false;
			checkBox2->Checked = false;
			checkBox3->Checked = false;
			label16->Visible = false;
			label4->Text = "";
		}

		Invalidate(); // Trigger redraw
	}

	private: System::Void standingwavecheckbox_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
		if (standingwavecheckbox->Checked) {
			drawWaves = true;
			label17->Visible = true;
			label18->Visible = true;
			label19->Visible = true;
			label20->Visible = true;
			// Show both waves but not superpostion for standing
			checkBox1->Checked = true; // Wave 1
			checkBox2->Checked = true; // Wave 2


			amplitude1 = 90;
			amplitude2 = 90;
			frequency1 = 63;
			frequency2 = 63;
			phase1 = 0;
			phase2 = 3.14;

			hScrollBar1->Value = 63;
			hScrollBar2->Value = 63;
			textBox5->Text = "63";
			textBox6->Text = "63";
			interferencecheckbox->Checked = false;
			beatscheckbox->Checked = false;
			checkBox5->Checked = false;


		}
		else {
			// Uncheck all waves when checkbox is turned off
			checkBox1->Checked = false;
			checkBox2->Checked = false;

			label17->Visible = false;
			label18->Visible = false;
			label19->Visible = false;
			label20->Visible = false;
			label4->Text = "";
		}

		Invalidate(); // Trigger redraw

	}
		   // functions of the waves
		   double c = 3.0e8;



		   // wave superpositon drawing
		   // adds both waves together
		   double waveSup(double amplitude1, double frequency1, double phase1, double amplitude2, double frequency2, double phase2, double  time1, double time2) {

			   return amplitude1 * sin(frequency1 * time1 + phase1) + amplitude2 * sin(frequency2 * time2 + phase2);

		   }
		   // wave fucntion used to draw waves
		   double wave(double amplitude, double frequnecy, double phase, double time) {

			   double scaledFrequency = frequnecy / 10.0; // helps with the frewquency on the screen to be more vewable
			   return  amplitude * sin(frequnecy * time + phase);


		   }

		   // fucntion to calculate the wavelngth from the frequency parameters
		   double wavelength(double frequency) {
			   double c = 3.0e8;
			   double wavelength = c / frequency;
			   return wavelength;
		   }

	};
}