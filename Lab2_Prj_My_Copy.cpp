/* Открыть консольное приложение.
Задать два не абстрактных класса, связанных в полиморфную иерархию:Class1(базовый) и Class2.
В главной функции программы создать несколько автоматических объектов этих типов.
Затем посредством вызова функции my_copy скопировать эти объекты в базу данных(использовать vector),
т.е.в базе данных должны оказаться копии созданных автоматических объектов.
Далее, вывести на консоль информацию о типах хранимых в БД объектах, используя typeid.
Исключить утечку памяти. */
#include <iostream>
#include <vector>
#include <typeinfo>

class Class1 
{
public:
	virtual void print() 
	{
		std::cout << "Class1" << std::endl;
	}
};

class Class2 : public Class1 
{
public:
	virtual void print() 
	{
		std::cout << "Class2" << std::endl;
	}
};

void my_copy(Class1* obj, std::vector<Class1*>& data) 
{
	Class1* copy = 0;
	if (dynamic_cast<Class2*>(obj)) 
	{
		copy = new Class2(*dynamic_cast<Class2*>(obj));
	}
	else 
	{
		copy = new Class1(*dynamic_cast<Class1*>(obj));
	}
	data.push_back(copy);
}

int main() {
	Class1 obj_1;
	Class2 obj_2;

	std::vector<Class1*> data;

	my_copy(&obj_1, data);
	my_copy(&obj_2, data);

	for (std::vector<Class1*>::iterator it = data.begin(); it != data.end(); ++it) 
	{
		std::cout << typeid(**it).name()<< std::endl;
		delete* it;
	}

	return 0;
}