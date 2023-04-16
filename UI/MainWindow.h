#pragma once
#include "TestingPolynoms.h"


namespace ui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//template<class T>
	//Polynom getPolynom(std::string& s);

	std::string commasToPoints(std::string& s);
	std::string pointsToCommas(std::string& s);

	/// <summary>
	/// Summary for MainWindow
	/// </summary>
	public ref class MainWindow : public System::Windows::Forms::Form
	{
	public:
		MainWindow(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainWindow()
		{
			if (components)
			{
				delete components;
			}
			delete this->exUnorderedTable;
			delete this->exOrderedTable;
			delete this->exAvlTree;
			delete this->exRbTree;
			delete this->exHashTableC;
			delete this->exHashTableOA;
		}

	private: Expression<UnorderedTable<std::string, Polynom>>* exUnorderedTable;
	private: Expression<OrderedTable<std::string, Polynom>>* exOrderedTable;
	private: Expression<AVLTree<std::string, Polynom>>* exAvlTree;
	private: Expression<RBTree<std::string, Polynom>>* exRbTree;
	private: Expression<HashTableC<std::string, Polynom>>* exHashTableC;
	private: Expression<HashTableOpenAdressing<std::string, Polynom>>* exHashTableOA;

	private: System::String^ usedContainerName = L"Тип контейнера";
	private: int numberOfSelectedContainer = 0;

	private: TestingPolynoms^ form1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ aVLtreeToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ dToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ dToolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ упорядоченнаяТаблицаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ неупорядоченнаяТаблицаToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ хештаблицаметодЦепочекToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ хештаблицаметодОткрытойАдресацииToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ тестированиеКонтейнеровToolStripMenuItem;

	protected:


	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->exAvlTree = new Expression<AVLTree<std::string, Polynom>>;
			this->exRbTree = new Expression<RBTree<std::string, Polynom>>;
			this->exHashTableC = new Expression<HashTableC<std::string, Polynom>>;
			this->exHashTableOA = new Expression<HashTableOpenAdressing<std::string, Polynom>>;
			this->exOrderedTable = new Expression<OrderedTable<std::string, Polynom>>;
			this->exUnorderedTable = new Expression<UnorderedTable<std::string, Polynom>>;

			this->form1 = gcnew TestingPolynoms;
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->aVLtreeToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dToolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->упорядоченнаяТаблицаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->неупорядоченнаяТаблицаToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->хештаблицаметодЦепочекToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->хештаблицаметодОткрытойАдресацииToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->тестированиеКонтейнеровToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(10, 27);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(293, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBox1_KeyPress);
			// 
			// textBox2  X
			// 
			this->textBox2->Location = System::Drawing::Point(33, 57);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(40, 20);
			this->textBox2->TabIndex = 2;
			this->textBox2->Text = "1";
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBox2_KeyPress);
			// 
			// textBox3  Y
			// 
			this->textBox3->Location = System::Drawing::Point(100, 57);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(40, 20);
			this->textBox3->Text = "1";
			this->textBox3->TabIndex = 3;
			this->textBox3->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBox3_KeyPress);
			// 
			// textBox4  Z
			// 
			this->textBox4->Location = System::Drawing::Point(170, 57);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(40, 20);
			this->textBox4->Text = "1";
			this->textBox4->TabIndex = 4;
			this->textBox4->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainWindow::textBox4_KeyPress);
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->textBox5->Location = System::Drawing::Point(70, 118);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(200, 20);
			this->textBox5->ReadOnly = true;
			this->textBox5->TabIndex = 9;
			this->textBox5->BorderStyle = System::Windows::Forms::BorderStyle::None;
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9));
			this->textBox6->Location = System::Drawing::Point(128, 98);
			this->textBox6->Name = L"textBox5";
			this->textBox6->Size = System::Drawing::Size(200, 25);
			this->textBox6->ReadOnly = true;
			this->textBox6->TabIndex = 9;
			this->textBox6->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->textBox6->Text = "";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 60);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(17, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"X";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(80, 60);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(17, 13);
			this->label2->TabIndex = 7;
			this->label2->Text = L"Y";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(150, 60);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(17, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Z";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(10, 120);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(17, 13);
			this->label4->TabIndex = 7;
			this->label1->MaximumSize = System::Drawing::Size(10, 0);
			this->label4->Text = L"Полином: ";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(10, 140);
			this->label5->Name = L"label4";
			this->label5->Size = System::Drawing::Size(17, 13);
			this->label5->TabIndex = 7;
			this->label5->Text = L"Подстановка: ";
			// 
			// label6
			//
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 100);
			this->label6->Name = L"label4";
			this->label6->Size = System::Drawing::Size(17, 13);
			this->label6->TabIndex = 7;
			this->label6->Text = L"Текущее выражение: ";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(220, 56);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(83, 22);
			this->button2->TabIndex = 8;
			this->button2->Text = L"Очистить";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainWindow::button2_Click);
			// 
			// menuStrip1
			// 
			this->menuStrip1->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->menuStrip1->GripStyle = System::Windows::Forms::ToolStripGripStyle::Visible;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->aVLtreeToolStripMenuItem,
					this->тестированиеКонтейнеровToolStripMenuItem
			});
			this->menuStrip1->LayoutStyle = System::Windows::Forms::ToolStripLayoutStyle::HorizontalStackWithOverflow;
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(315, 24);
			this->menuStrip1->TabIndex = 9;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// aVLtreeToolStripMenuItem
			// 
			this->aVLtreeToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {
				this->dToolStripMenuItem,
					this->dToolStripMenuItem1, this->упорядоченнаяТаблицаToolStripMenuItem, this->неупорядоченнаяТаблицаToolStripMenuItem, this->хештаблицаметодЦепочекToolStripMenuItem,
					this->хештаблицаметодОткрытойАдресацииToolStripMenuItem
			});
			this->aVLtreeToolStripMenuItem->Name = L"aVLtreeToolStripMenuItem";
			this->aVLtreeToolStripMenuItem->Size = System::Drawing::Size(107, 20);
			this->aVLtreeToolStripMenuItem->Text = this->usedContainerName;
			// 
			// dToolStripMenuItem
			// 
			this->dToolStripMenuItem->Name = L"dToolStripMenuItem";
			this->dToolStripMenuItem->Size = System::Drawing::Size(222, 22);
			this->dToolStripMenuItem->Text = L"AVL дерево";
			this->dToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::dToolStripMenuItem_Click);
			// 
			// dToolStripMenuItem1
			// 
			this->dToolStripMenuItem1->Name = L"dToolStripMenuItem1";
			this->dToolStripMenuItem1->Size = System::Drawing::Size(222, 22);
			this->dToolStripMenuItem1->Text = L"R-B дерево";
			this->dToolStripMenuItem1->Click += gcnew System::EventHandler(this, &MainWindow::dToolStripMenuItem1_Click);
			// 
			// упорядоченнаяТаблицаToolStripMenuItem
			// 
			this->упорядоченнаяТаблицаToolStripMenuItem->Name = L"упорядоченнаяТаблицаToolStripMenuItem";
			this->упорядоченнаяТаблицаToolStripMenuItem->Size = System::Drawing::Size(222, 22);
			this->упорядоченнаяТаблицаToolStripMenuItem->Text = L"Упорядоченная таблица";
			this->упорядоченнаяТаблицаToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::упорядоченнаяТаблицаToolStripMenuItem_Click);
			// 
			// неупорядоченнаяТаблицаToolStripMenuItem
			// 
			this->неупорядоченнаяТаблицаToolStripMenuItem->Name = L"неупорядоченнаяТаблицаToolStripMenuItem";
			this->неупорядоченнаяТаблицаToolStripMenuItem->Size = System::Drawing::Size(222, 22);
			this->неупорядоченнаяТаблицаToolStripMenuItem->Text = L"Неупорядоченная таблица";
			this->неупорядоченнаяТаблицаToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::неупорядоченнаяТаблицаToolStripMenuItem_Click);
			// 
			// хештаблицаметодЦепочекToolStripMenuItem
			// 
			this->хештаблицаметодЦепочекToolStripMenuItem->Name = L"хештаблицаметодЦепочекToolStripMenuItem";
			this->хештаблицаметодЦепочекToolStripMenuItem->Size = System::Drawing::Size(222, 22);
			this->хештаблицаметодЦепочекToolStripMenuItem->Text = L"Хеш-таблица CHAIN";
			this->хештаблицаметодЦепочекToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::хештаблицаметодЦепочекToolStripMenuItem_Click);
			// 
			// хештаблицаметодОткрытойАдресацииToolStripMenuItem
			// 
			this->хештаблицаметодОткрытойАдресацииToolStripMenuItem->Name = L"хештаблицаметодОткрытойАдресацииToolStripMenuItem";
			this->хештаблицаметодОткрытойАдресацииToolStripMenuItem->Size = System::Drawing::Size(222, 22);
			this->хештаблицаметодОткрытойАдресацииToolStripMenuItem->Text = L"Хеш-таблица OA";
			this->хештаблицаметодОткрытойАдресацииToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::хештаблицаметодОткрытойАдресацииToolStripMenuItem_Click);
			// 
			// тестированиеКонтейнеровToolStripMenuItem
			// 
			this->тестированиеКонтейнеровToolStripMenuItem->Name = L"тестированиеКонтейнеровToolStripMenuItem";
			this->тестированиеКонтейнеровToolStripMenuItem->Size = System::Drawing::Size(170, 20);
			this->тестированиеКонтейнеровToolStripMenuItem->Text = L"Тестирование контейнеров";
			this->тестированиеКонтейнеровToolStripMenuItem->Click += gcnew System::EventHandler(this, &MainWindow::тестированиеКонтейнеровToolStripMenuItem_Click);
			// 
			// MainWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(315, 261);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox6);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"MainWindow";
			this->Text = L"Polynomial Сalculation";
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();
		}
#pragma endregion
	
private: System::Void printResult();
private: System::Void reset();
System::Void MainWindow::addExpression();

private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) { reset(); }

private: System::Void тестированиеКонтейнеровToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) { (gcnew TestingPolynoms)->Show(); }
private: System::Void хештаблицаметодОткрытойАдресацииToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	this->usedContainerName = L"Хеш-таблица OA";
	this->numberOfSelectedContainer = 5;
	this->aVLtreeToolStripMenuItem->Text = this->usedContainerName;
}
private: System::Void хештаблицаметодЦепочекToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	this->usedContainerName = L"Хеш-таблица CHAIN";
	this->numberOfSelectedContainer = 4;
	this->aVLtreeToolStripMenuItem->Text = this->usedContainerName;
}
private: System::Void неупорядоченнаяТаблицаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	this->usedContainerName = L"Неупорядоченная..";
	this->numberOfSelectedContainer = 3;
	this->aVLtreeToolStripMenuItem->Text = this->usedContainerName;
}
private: System::Void упорядоченнаяТаблицаToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	this->usedContainerName = L"Упорядоченная..";
	this->numberOfSelectedContainer = 2;
	this->aVLtreeToolStripMenuItem->Text = this->usedContainerName;
}
private: System::Void dToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e) {
	this->usedContainerName = L"AVL дерево";
	this->numberOfSelectedContainer = 0;
	this->aVLtreeToolStripMenuItem->Text = this->usedContainerName;
}
private: System::Void dToolStripMenuItem1_Click(System::Object^ sender, System::EventArgs^ e) {
	this->usedContainerName = L"R-B дерево";
	this->numberOfSelectedContainer = 1;
	this->aVLtreeToolStripMenuItem->Text = this->usedContainerName;
}	   
private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if(e->KeyChar == '\r') addExpression();
}

private: System::Void textBox2_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == '\r') printResult();
}
private: System::Void textBox3_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == '\r') printResult();
}
private: System::Void textBox4_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == '\r') printResult();
}
};
}
