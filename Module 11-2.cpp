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

std::string encrypt_caesar(std::string str, int offset) {
	std::string result = "";
	int codeLetter_A = 65;
	int codeLetter_a = 97;
	int alphabetLength = 26;

	for (int i = 0; i < str.length(); i++) {
		int numberSymbol = (int)str[i];
		if (numberSymbol >= codeLetter_A && numberSymbol < (codeLetter_A + alphabetLength)) {
			numberSymbol -= codeLetter_A;
			numberSymbol = (numberSymbol + offset) % alphabetLength;
			if (numberSymbol < 0) numberSymbol += alphabetLength;
			numberSymbol += codeLetter_A;
		}
		if (numberSymbol >= codeLetter_a && numberSymbol < (codeLetter_a + alphabetLength)) {
			numberSymbol -= codeLetter_a;
			numberSymbol = (numberSymbol + offset) % alphabetLength;
			if (numberSymbol < 0) numberSymbol += alphabetLength;
			numberSymbol += codeLetter_a;
		}
		result += (char)numberSymbol;
	}
	return result;
}

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

std::string cut_domain_name(std::string str) {
	std::string result = "";
	int split = -1;
	for (int i = 0; i < str.length(); i++) {
		if (str[i] == '@') {
			split = i + 1;
		}
	}

	if (split == -1) {
		return result;
	}

	for (int i = split; i < str.length(); i++) {
		result += str[i];
	}
	return result;
}

bool check_name_post_box(std::string checkAddress) {
	return true;
}

bool check_domain_name(std::string checkAddress) {
	return true;
}

bool check_email (std::string checkAddress) {
	return check_name_post_box (cut_name_post_box (checkAddress)) && check_domain_name (cut_domain_name (checkAddress)) ? true : false;
}



int main() {
	std::string emailAddress;
	std::cout << "Enter email address: ";
	std::cin >> emailAddress;

	while (emailAddress.length() > 128) {
		std::cout << "The email address is too long, enter again: ";
		std::cin >> emailAddress;
	}

	if (check_email(emailAddress)) {
		std::cout << std::endl << "Yes";
	}
	else {
		std::cout << std::endl << "No";
	}

	std::cout << std::endl << cut_name_post_box(emailAddress) << std::endl << cut_domain_name(emailAddress);

}