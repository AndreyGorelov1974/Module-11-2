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

std::string decrypt_caesar(std::string str, int offset) {
	return encrypt_caesar(str, -offset);
}



int main() {
	std::string inputText;
	std::cout << "Enter the text: ";
	std::getline(std::cin, inputText);

	int offsetSymbol;
	std::cout << "Enter the character offset: ";
	std::cin >> offsetSymbol;

	int modeNumber;
	std::cout << "Enter the mode number, 0 - encrypt, 1 - decrypt: ";
	std::cin >> modeNumber;

	while (modeNumber < 0 || modeNumber > 1) {
		std::cout << "Enter correct mode number: ";
		std::cin >> modeNumber;
	}


	if (modeNumber == 0) {
		std::cout << encrypt_caesar(inputText, offsetSymbol);
	}
	else {
		std::cout << decrypt_caesar(inputText, offsetSymbol);

	}



}