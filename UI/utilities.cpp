#include "MyForm.h"
#include "MyForm1.h"

namespace ui {

	std::string toString(System::String^ s) {
		std::string result;

		//for (size_t i = 0; i < s->Length; i++) {
		//	result += static_cast<System::IConvertible^>(s->Substring(i, 1))->ToChar(System::Globalization::CultureInfo::CurrentCulture);
		//}

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

	//template<class T>
	//Polynom getPolynom(std::string& s) {
	//	Expression<T> ex(s);
	//
	//	if (!ex.isCorrect()) {
	//		throw gcnew System::Exception(L"Некорректное выражение");
	//	}
	//
	//	return ex.getResult();
	//}
}