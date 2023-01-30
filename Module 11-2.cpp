/*Задание 2. Проверка корректности email-адреса
Что нужно сделать
Напишите программу, которая проверяет корректность email-адреса, введённого пользователем.

Согласно международным требованиям, корректный email-адрес должен состоять из двух частей, разделённых знаком @.
Первая часть должна иметь длину не менее одного и не более 64 символов, вторая часть — не менее одного и не более 63 символов.
Из символов допускаются только английские буквы, цифры и знак «-» (дефис), а также точка. Точка не может быть первым или последним символом, а кроме того, две точки не могут идти подряд.
В первой части (которая предшествует символу @), кроме вышеперечисленных, разрешены ещё следующие символы:

!#$%&'*+-/=?^_`{|}~

Пользователь вводит строку, задающую email-адрес. Программа должна вывести слово Yes, если адрес корректен, а в противном случае — слово No.

Примеры

Корректные адреса: 
simple@example.com 
very.common@example.com 
disposable.style.email.with+symbol@example.com 
other.email-with-hyphen@example.com 
fully-qualified-domain@example.com 
user.name+tag+sorting@example.com (может на самом деле быть перенаправлен на user.name@example.com в зависимости от почтового сервиса) 
x@example.com (однобуквенная локальная часть) 
example-indeed@strange-example.com 
admin@mailserver1 
example@s.example 
mailhost!username@example.org 
user%example.com@example.org

Некорректные адреса: 
John..Doe@example.com (две точки не могут идти подряд) 
Abc.example.com (нет символа @) 
A@b@c@example.com (символ @ должен быть только один) 
a"b(c)d,e:f;g<h>i[j\k]l@example.com (есть недопустимые символы) 
1234567890123456789012345678901234567890123456789012345678901234+x@example.com (первая часть длиннее 64 символов) 
i_like_underscore@but_its_not_allow_in _this_part.example.com (во второй части есть недопустимый символ «_»)

Рекомендации
Активно используйте оператор индексации строки str[i], но помните, что индексы начинаются с нуля, а не с единицы.
Создайте отдельные функции, которые выдают первую и вторую части адреса для их последующего анализа.
Для валидации отдельных символов внутри части используйте дополнительные строки-словари, состоящие из всех корректных символов для соответствующей части.
При разработке вспомогательных функций получения первой и второй части адреса воспользуйтесь циклом, который проверяет текущий символ.

Если символ равен ‘@’, значит мы нашли границу между частями адреса.
В функции нахождения первой части в этом месте надо остановиться и вернуть все символы, что были раньше (их можно накапливать в std::string при помощи оператора +=).
Во второй функции все символы после ‘@’ тем же оператором добавляются к результату.
Строка-словарь — это строка, которая в нашем случае содержит весь английский алфавит и символы. Каждый символ адреса надо сравнить с каждым символом из этого списка «допустимых символов» в цикле.
В этом задании очень важно разбить код на отдельные функции, каждая из которых делает небольшую часть работы.*/

#include <iostream>
#include <string>

// функция вырезания части адреса до @, если @ нет возвращаем пустую строку
std::string cut_name_post_box(std::string str) {
	std::string result = "";
	for (int i = 0; i < str.length(); i++) {
		if (str[i] != '@') {
			result += str[i];
		}
		else {
			return result;
		}		
	}
	return result = "";
}

// функция вырезания части адреса после @, если @ нет возвращаем пустую строку
std::string cut_domain_name(std::string str) {
	std::string result = "";
	bool find = false;
	for (int i = 0; i < str.length(); i++) {
		if (find) {
			result += str[i];
		}
		if (str[i] == '@') {
			find = true;
		}
	}
	return result;
}

// функция проверки корректности, на вход подаём проверяемую строку, и строку-словарь разрешённых символов
bool check_address (std::string checkStr, std::string passedStr) {
	int checkStrLength = checkStr.length();
	int passedStrLength = passedStr.length();

	// проверяем две . в начале строки
	if (checkStr[0] == '.' || checkStr[checkStrLength - 1] == '.') {
		return false;
	}

	for (int i = 0; i < checkStrLength; i++) {
		// проверка двух . до конца строки
		if (checkStr[i] == '.' && checkStr[i + 1] == '.' && i < (checkStrLength - 1)) {
			return false;
		}
		// проверка допустимых символов
		if (passedStr.find(checkStr[i]) == std::string::npos) {
			return false;
		}
	}
	return true;
}

//функция проверки адреса почты
bool check_email (std::string checkAddress) {
	std::string namePostBox = cut_name_post_box(checkAddress);
	std::string domainName = cut_domain_name(checkAddress);

	if (namePostBox.length() < 1 || namePostBox.length() > 64 || domainName.length() < 1 || domainName.length() > 63) {
		return false;
	}
	//строки разрешённых символов
	std::string passedSymbolNamePostBox = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-.!#$%&'*+-/=?^_`{|}~";
	std::string passedSymbolDomainName = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890-.";

	return check_address (namePostBox, passedSymbolNamePostBox) && check_address(domainName, passedSymbolDomainName) ? true : false;
}



int main() {
	std::string emailAddress;
	std::cout << "Enter email address: ";
	std::cin >> emailAddress;

	while (emailAddress.length() > 128) {
		std::cout << "The email address is too long, enter again: ";
		std::cin >> emailAddress;
	}

	std::cout << std::endl << (check_email(emailAddress) ? "Yes" : "No");
}