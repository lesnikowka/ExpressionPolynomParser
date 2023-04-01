#include "MyForm.h"
#include "MyForm1.h"

namespace ui {

	std::string toString(System::String^ s) {
		std::string result;

		result = msclr::interop::marshal_as<std::string>(s);

		return result;
	}

	System::String^ toSystemString(std::string s) {
		System::String^ result = msclr::interop::marshal_as<System::String^>(s);
		return result;
	}

	std::string commasToPoints(std::string& s) {
		std::string result;
		for (auto i : s) {
			if (i == ',') result += ".";
			else result += i;
		}
		return result;
	}

	std::string pointsToCommas(std::string& s) {
		std::string result;
		for (auto i : s) {
			if (i == '.') result += ",";
			else result += i;
		}
		return result;
	}

	System::Void MyForm1::addPolynom() {
		std::string name = toString(this->textBox1->Text);
		std::string polynom = toString(this->textBox2->Text);

		this->textBox1->Text = "";
		this->textBox2->Text = "";

		if (name.size() && polynom.size()) {
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
		else {
			MessageBox::Show("Поля \"имя\" и \"полином\" должны быть заполнены", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
}

	System::Void MyForm1:: printPolynoms() {
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
	this->richTextBox1->Text += "\r\nR-B дерево:\r\n";
	for (auto i : *(this->rbTree)) {
		this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
	}
	this->richTextBox1->Text += "\r\nХеш таблица с разрешением коллизий методом цепочек:\r\n";
	for (auto i : *(this->hashTableC)) {
		this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
	}
	this->richTextBox1->Text += "\r\nХеш таблица с разрешением коллизий методом открытой адресации:\r\n";
	for (auto i : *(this->hashTableOA)) {
		this->richTextBox1->Text += toSystemString(i.first) + ": " + toSystemString(i.second.str()) + "\r\n";
	}
}

System::Void MyForm1::deletePolynom() {
	this->textBox2->Text = "";

	if ((orderedTable->size())) {
		try {
			this->unorderedTable->erase(toString(textBox1->Text));
			this->orderedTable->erase(toString(textBox1->Text));
			this->avlTree->erase(toString(textBox1->Text));
			//this->rbTree->erase(toString(textBox1->Text));
			this->hashTableC->erase(toString(textBox1->Text));
			this->hashTableOA->erase(toString(textBox1->Text));
		}
		catch (System::Exception^ ex) {
			MessageBox::Show("Элемент не найден", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
		}
	}
	else {
		MessageBox::Show("Контейнеры уже пусты!", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
}
}