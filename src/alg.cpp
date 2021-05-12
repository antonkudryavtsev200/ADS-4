// Copyright 2021 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <cassert>
 
template<typename T>
class TQueue
{
private:
	T* arr; // массив с данными
	int size; // максимальное количество элементов в очереди (размер массива)
	int begin, // начало очереди
		end; // конец очереди
	int count; // счетчик элементов
public:
	TQueue(); // конструктор по умолчанию
	~TQueue(); // деструктор

	void push(const T&); // добавить элемент в очередь
	T pop(); // удалить элемент из очереди
	T get() const; // прочитать первый элемент
	bool isEmpty() const; // пустая ли очередь?
	bool isFull() const; // заполнен ли массив?
};
// конструктор по умолчанию
template<typename T>
TQueue<T>::TQueue() :
	size(100),
	begin(0), end(0), count(0)
{
	// дополнительный элемент поможет нам различать конец и начало очереди
	arr = new T[size + 1];
}
// деструктор класса Queue
template<typename T>
TQueue<T>::~TQueue()
{
	delete[] arr;
}
// функция добавления элемента в очередь
template<typename T>
void TQueue<T>::push(const T& item)
{
	// проверяем, ести ли свободное место в очереди
	assert(count < size);
	if (count != 0 && item.prior > arr[count - 1].prior) 
	{
		arr[end++] = item;
		count++;
		for (int i = 1; i < count; i++)
			if (arr[count - i].prior > arr[count - (i + 1)].prior) 
			{
				T dub = arr[count - i];
				arr[count - i] = arr[count - (i + 1)];
				arr[count - (i + 1)] = dub;
			}
	}
	else {
		arr[end++] = item;
		count++;
	}
	if (end > size)
		end -= size + 1;
	arr[end++] = item;
	count++;
	// проверка кругового заполнения очереди
	if (end > size)
	{
		end -= size + 1; // возвращаем end на начало очереди
	}
}
	
// функция удаления элемента из очереди
template<typename T>
T TQueue<T>::pop()
{
	// проверяем, есть ли в очереди элементы
	assert(count > 0);
	T item = arr[begin++];
	count--;
	// проверка кругового заполнения очереди
	if (begin > size)
		begin -= size + 1; // возвращаем begin на начало очереди
	return item;
}
// функция чтения элемента на первой позиции
template<typename T>
T TQueue<T>::get() const
{
	// проверяем, есть ли в очереди элементы
	assert(count > 0);
	return arr[begin];
}
// функция проверки очереди на пустоту
template<typename T>
bool TQueue<T>::isEmpty() const
{
	return count == 0;
}
// функция проверки очереди на заполненность
template<typename T>
bool TQueue<T>::isFull() const
{
	return count == size;
}
//В качестве типа данных T, используемого очередью, возьмем структуру SYM :
struct SYM
{
	char ch;
	int prior;
};
#endif
