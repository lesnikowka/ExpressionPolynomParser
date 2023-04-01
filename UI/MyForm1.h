#pragma once
#include "polynom.h"
#include "expression.h"
#include "AVL-tree.h"
#include "hash-table(chaining).h"
#include "hash-table(open-adressing).h"
#include  "Red-Black-trees.h"
#include "ordered-table.h"
#include "unordered-table.h"
#include <msclr/marshal_cppstd.h>
#include <string>


namespace ui {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	std::string toString(System::String^ s);
	System::String^ toSystemString(std::string s);

	/// <summary>
	/// Сводка для MyForm1
	/// </summary>
	public ref class MyForm1 : public System::Windows::Forms::Form
	{
	public:
		MyForm1(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm1()
		{
			if (components)
			{
				delete components;
			}

			delete unorderedTable;
			delete orderedTable;
			delete avlTree;
			delete rbTree;
			delete hashTableC;
			delete hashTableOA;
		}

	private: UnorderedTable<std::string, Polynom>* unorderedTable;
	private: OrderedTable<std::string, Polynom>* orderedTable;
	private: AVLTree<std::string, Polynom>* avlTree;
	private: RBTree<std::string, Polynom>* rbTree;
	private: HashTableC<std::string, Polynom>* hashTableC;
	private: HashTableOpenAdressing<std::string, Polynom>* hashTableOA;

	private: System::Windows::Forms::TextBox^ textBox1;
	protected:
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RichTextBox^ richTextBox1;

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->unorderedTable = new UnorderedTable<std::string, Polynom>;
			this->orderedTable = new OrderedTable<std::string, Polynom>;
			this->avlTree = new AVLTree<std::string, Polynom>;
			this->rbTree = new RBTree<std::string, Polynom>;
			this->hashTableC = new HashTableC<std::string, Polynom>;
			this->hashTableOA = new HashTableOpenAdressing<std::string, Polynom>;

			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// textBox1  NAME
			// 
			this->textBox1->Location = System::Drawing::Point(53, 10);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(118, 20);
			this->textBox1->TabIndex = 0;
			this->textBox1->Text = "";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(424, 8);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Добавить";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm1::button1_Click);
			// 
			// textBox2 POLYNOM
			// 
			this->textBox2->Location = System::Drawing::Point(239, 10);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(169, 20);
			this->textBox2->TabIndex = 3;
			this->textBox2->Text = "";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 12);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Имя:";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(177, 13);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(56, 13);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Полином:";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(15, 44);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(484, 23);
			this->button2->TabIndex = 6;
			this->button2->Text = L"Вывести все полиномы:";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm1::button2_Click);
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Window;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Location = System::Drawing::Point(15, 83);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(480, 236);
			this->richTextBox1->TabIndex = 7;
			this->richTextBox1->Text = L"";
			this->richTextBox1->TextChanged += gcnew System::EventHandler(this, &MyForm1::richTextBox1_TextChanged);
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(507, 331);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->textBox1);
			this->Name = L"Тестирование контейнеров";
			this->Text = L"Тестирование контейнеров";
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		std::string name = toString(this->textBox1->Text);
		std::string polynom = toString(this->textBox2->Text);


		try {
			Polynom p(polynom);

			this->unorderedTable->emplace(name, p);
			this->orderedTable->emplace(name, p);
			this->avlTree->emplace(name, p);
			this->rbTree->emplace(name, p);
			this->hashTableC->emplace(name, p);
			this->hashTableOA->emplace(name, p);

		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Некорректный полином", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		this->richTextBox1->Text = "";

		this->richTextBox1->Text += "\r\nНеупорядоченная таблица:\r\n";
		for (auto i : *(this->unorderedTable)) {
			this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
		}
		this->richTextBox1->Text += "\r\nУпорядоченная таблица:\r\n";
		for (auto i : *(this->orderedTable)) {
			this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
		}
		this->richTextBox1->Text += "\r\nAVL дерево:\r\n";
		for (auto i : *(this->avlTree)) {
			this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
		}
		//this->richTextBox1->Text += "\r\nR-B дерево:\r\n";
		//for (auto i : *(this->rbTree)) {
		//	this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
		//}
		//this->richTextBox1->Text += "\r\nХеш таблица с разрешением коллизий методом цепочек:\r\n";
		//for (auto i : *(this->hashTableC)) {
		//	this->richTextBox1->Text += toSystemString(i.key) + ": " + toSystemString(i.elem.str()) + "\r\n";
		//}
		this->richTextBox1->Text += "\r\nХеш таблица с разрешением коллизий методом открытой адресации:\r\n";
		for (auto i : *(this->hashTableOA)) {
			this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
		}
	}
	private: System::Void richTextBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	};
}
