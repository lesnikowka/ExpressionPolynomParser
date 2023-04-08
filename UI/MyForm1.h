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
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
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
			this->button3 = (gcnew System::Windows::Forms::Button());
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
			this->textBox1->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm1::textBox1_KeyPress);
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

			this->button3->Location = System::Drawing::Point(509, 8);
			this->button3->Name = L"button1";
			this->button3->Size = System::Drawing::Size(75, 23);
			this->button3->TabIndex = 2;
			this->button3->Text = L"Удалить";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm1::button3_Click);
			// 
			// textBox2 POLYNOM
			// 
			this->textBox2->Location = System::Drawing::Point(239, 10);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(169, 20);
			this->textBox2->TabIndex = 3;
			this->textBox2->Text = "";
			this->textBox2->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm1::textBox2_KeyPress);
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
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Window;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->richTextBox1->Location = System::Drawing::Point(15, 40);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->Size = System::Drawing::Size(565, 276);
			this->richTextBox1->TabIndex = 7;
			this->richTextBox1->Text = L"";
			// 
			// MyForm1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(592, 331);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->textBox1);
			this->Name = L"Тестирование контейнеров";
			this->Text = L"Тестирование контейнеров";
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Load += gcnew System::EventHandler(this, &MyForm1::MyForm1_Load);
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void addPolynom();

	private: System::Void printPolynoms();

	private: System::Void deletePolynom();

	private: System::Void MyForm1_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		addPolynom();
		printPolynoms();
	}

private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
	deletePolynom();
	printPolynoms();
}
private: System::Void textBox2_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == '\r') {
		addPolynom();
		printPolynoms();
	}
}
private: System::Void textBox1_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
	if (e->KeyChar == '\r') {
		addPolynom();
		printPolynoms();
	}
}
};
}
