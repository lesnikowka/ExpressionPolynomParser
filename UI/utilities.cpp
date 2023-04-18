#include "MainWindow.h"
#include "TestingPolynoms.h"

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

	System::Void TestingPolynoms::addPolynom() {
		std::string name = toString(this->textBox1->Text);
		std::string polynom = toString(this->textBox2->Text);

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

	System::Void TestingPolynoms:: printPolynoms() {
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

System::Void TestingPolynoms::deletePolynom() {
	this->textBox2->Text = "";


	if (orderedTable->size()&&unorderedTable->size()&&hashTableC->getSize()&&hashTableOA->size()&&avlTree->size()&&rbTree->size()) {
		try {
			this->unorderedTable->erase(toString(textBox1->Text));
			this->orderedTable->erase(toString(textBox1->Text));
			this->avlTree->erase(toString(textBox1->Text));
			this->rbTree->erase(toString(textBox1->Text));
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

System::Void MainWindow::printResult() {
	std::vector<double> xyz(3);

	try {
		xyz[0] = std::stod(commasToPoints(toString(this->textBox2->Text)));
		xyz[1] = std::stod(commasToPoints(toString(this->textBox3->Text)));
		xyz[2] = std::stod(commasToPoints(toString(this->textBox4->Text)));
	}
	catch (Exception^ ex) {
		MessageBox::Show("Некорректные значения x, y или z", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}

	switch (this->numberOfSelectedContainer) {
	case 0:
		this->textBox5->Text = toSystemString(exAvlTree->getResult().str());
		this->label5->Text = L"Подстановка: " + Convert::ToString(exAvlTree->getResult().calculate(xyz));
		break;
	case 1:
		this->textBox5->Text = toSystemString(exRbTree->getResult().str());
		this->label5->Text = L"Подстановка: " + Convert::ToString(exRbTree->getResult().calculate(xyz));
		break;
	case 2:
		this->textBox5->Text = toSystemString(exOrderedTable->getResult().str());
		this->label5->Text = L"Подстановка: " + Convert::ToString(exOrderedTable->getResult().calculate(xyz));
		break;
	case 3:
		this->textBox5->Text = toSystemString(exUnorderedTable->getResult().str());
		this->label5->Text = L"Подстановка: " + Convert::ToString(exUnorderedTable->getResult().calculate(xyz));
		break;
	case 4:
		this->textBox5->Text = toSystemString(exHashTableC->getResult().str());
		this->label5->Text = L"Подстановка: " + Convert::ToString(exHashTableC->getResult().calculate(xyz));
		break;
	case 5:
		this->textBox5->Text = toSystemString(exHashTableOA->getResult().str());
		this->label5->Text = L"Подстановка: " + Convert::ToString(exHashTableOA->getResult().calculate(xyz));
		break;
	}
}
System::Void MainWindow::reset() {
		Expression<AVLTree<std::string, Polynom>>* newExAvlTree = new Expression<AVLTree<std::string, Polynom>>;
		Expression<RBTree<std::string, Polynom>>* newExRbTree = new Expression<RBTree<std::string, Polynom>>;
		Expression<HashTableC<std::string, Polynom>>* newExHashTableC = new Expression<HashTableC<std::string, Polynom>>;
		Expression<HashTableOpenAdressing<std::string, Polynom>>* newExHashTableOA = new Expression<HashTableOpenAdressing<std::string, Polynom>>;
		Expression<OrderedTable<std::string, Polynom>>* newExOrderedTable = new Expression<OrderedTable<std::string, Polynom>>;
		Expression<UnorderedTable<std::string, Polynom>>* newExUnorderedTable = new Expression<UnorderedTable<std::string, Polynom>>;

		this->exAvlTree = newExAvlTree;
		this->exHashTableC = newExHashTableC;
		this->exHashTableOA = newExHashTableOA;
		this->exRbTree = newExRbTree;
		this->exUnorderedTable = newExUnorderedTable;
		this->exOrderedTable = newExOrderedTable;

		this->textBox5->Text = "";
		this->textBox6->Text = "";
		this->label5->Text = "Подстановка: ";
	}

System::Void MainWindow::addExpression() {
	std::string tmp = commasToPoints(toString(this->textBox1->Text));

	try {
		this->exAvlTree->addExp(tmp);
		this->exRbTree->addExp(tmp);
		this->exOrderedTable->addExp(tmp);
		this->exUnorderedTable->addExp(tmp);
		this->exHashTableC->addExp(tmp);
		this->exHashTableOA->addExp(tmp);

		std::string tmp2;

		switch (this->numberOfSelectedContainer) {
		case 0:
			tmp2 = this->exAvlTree->getSourceString();
		case 1:
			tmp2 = this->exRbTree->getSourceString();
		case 2:
			tmp2 = this->exOrderedTable->getSourceString();
		case 3:
			tmp2 = this->exUnorderedTable->getSourceString();
		case 4:
			tmp2 = this->exHashTableC->getSourceString();
		case 5:
			tmp2 = this->exHashTableOA->getSourceString();
		}

		this->textBox6->Text = toSystemString(tmp2);

		printResult();
	}
	catch (Exception^ ex) {
		MessageBox::Show("Некорректное выражение", "Ошибка!", MessageBoxButtons::OK, MessageBoxIcon::Warning);
	}
	this->textBox1->Text = "";
	
}
}