#include "iostream"
using namespace std;
template <typename T>
class List
{
public:
	int GetSize() { return Size; }     // Показать размер списка
	void clear();                      // Очистить список
	void push_front(T data);    // Добавить элемент в начало списка
	void push_back(T data);      // Добавить элемент в конец списка
	void pop_front();           // Удалить элемент из начала списка
	void pop_back();             //Удалить элемент из конца списка
	void insert(T data, int index);     // Добавить элемент по индексу
	void removeAt(int index);           // Удаление по индексу
	void PrintFromHead();      // Распечатать с начала
	List <T>();                // Конструктор 
	~List <T>();               // Деструктор
private:
	template <typename T>
	class Node                        // Описываем каждый элемент
	{
	public:
		Node(T data = T(), Node* pNext = nullptr, Node* pPrev = nullptr)   // Конструктор с присваиваниями
		{
			this->data = data;
			this->pNext = pNext;
			this->pPrev = pPrev;
		}
		T data;
		Node* pNext;
		Node* pPrev;
	};
	Node <T>* head;
	Node <T>* tail;
	int Size;
};
template <typename T>
List <T>::List()
{
	head = nullptr;      // Конструктор создает список
	tail = nullptr;
	Size = 0;
}
template <typename T>
List <T>::~List()
{
	clear();               //Деструктор вызывает clear(удаление всех элементов)
}
template<typename T>
void List<T>::clear()
{
	while (Size)
	{
		pop_front();      //Пока Size(кол-во элементов) не равно 0 - clear удаляет первые элементы(pop_front)
	}
}
template <typename T>
void List <T>::push_front(T data)
{
	if (Size == 1)
	{
		head = new Node <T>(data, head);                 // Если 1 элемент, то новый push_front двигает прошлый 
		tail->pPrev = this->head;
	}
	else if (Size > 1)
	{
		Node <T>* temp = head;
		head = new Node <T>(data, head);               // Подвигаются все элементы
		temp->pPrev = head;
	}
	else
	{
		head = tail = new Node <T>(data, head, tail);    // Если элементов не было, то начало это конец 
	}
	Size++;
}
template <typename T>
void List <T>::push_back(T data)
{
	if (Size == 1)
	{
		tail = new Node <T>(data, nullptr, tail);          // Все как и в push_front, только двигается последний элемент
		head->pNext = this->tail;
	}
	else if (Size > 1)
	{
		Node <T>* temp = tail;
		tail = new Node <T>(data, nullptr, tail);
		temp->pNext = tail;
	}
	else
	{
		head = tail = new Node <T>(data, head, tail);
	}
	Size++;
}

template <typename T>
void List <T>::pop_front()
{
	if (Size > 1)
	{
		Node <T>* temp = head;
		head = head->pNext;             // Указатель подвигается 
		delete temp;
	}
	else if (Size == 1)
	{
		Node <T>* temp = head;
		tail = head = head->pNext;
		delete temp;
	}
	Size--;
}

template <typename T>
void List <T>::pop_back()
{
	if (Size > 1)
	{
		Node <T>* temp = tail;
		tail = tail->pPrev;
		delete temp;
	}
	else if (Size == 1)
	{
		Node <T>* temp = tail;
		tail = head = tail->pPrev;
		delete temp;
	}
	Size--;
}
template <typename T>
void List <T>::insert(T data, int index)
{
	if (index == 0) push_front(data);
	else if (index == Size) push_back(data);
	else if (index<Size || index>Size) {
		cout << "Wrong index" << endl;
	}
	else if (index <= Size / 2)
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* newNode = new Node<T>(data, previous->pNext, previous);
		previous->pNext = newNode;
		Node<T>* next = newNode->pNext;        // Доходим до элемента, который стоит до того, который удаляем и перемещаем адреса
		next->pPrev = newNode;
		Size++;
	}

	else if (index > Size / 2)
	{
		Node<T>* next = this->tail;
		for (int i = Size - 1; index < i; i--)
		{
			next = next->pPrev;
		}
		Node<T>* newNode = new Node<T>(data, next, next->pPrev);
		next->pPrev = newNode;
		Node<T>* previous = newNode->pPrev;
		previous->pNext = newNode;
		Size++;
	}
}
template <typename T>
void List <T>::removeAt(int index)
{
	if (index == 0) pop_front();

	else if (index == Size) pop_back();
	else if (index<Size || index>Size) {
		cout << "Wrong index" << endl;
	}
	else if (index <= Size / 2)
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}
		Node<T>* toDelete = previous->pNext;
		previous->pNext = toDelete->pNext;           // Все как и в insert, только с удалением
		Node<T>* next = toDelete->pNext;
		delete toDelete;
		next->pPrev = previous;
		Size--;
	}
	else if (index > Size / 2)
	{
		Node<T>* next = this->tail;
		for (int i = Size - 1; index < i; i--)
		{
			next = next->pPrev;
		}
		Node<T>* toDelete = next->pPrev;
		next->pPrev = toDelete->pPrev;
		Node<T>* previous = toDelete->pPrev;
		delete toDelete;
		previous->pNext = next;

		Size--;
	}
}
template <typename T>
void List <T>::PrintFromHead()
{
	cout << "Print:" << endl;
	Node <T>* print = head;
	while (print)
	{
		cout << print->data << endl;
		print = print->pNext;
	}
	cout << endl;
}

template<typename T>
T Proverka(T value) {
	do {
		cout << "Enter a value: ";
		cin >> value;
		if (cin.fail())
		{
			cin.clear(); // Очистка буфера ввода
			cin.ignore(); // Удаление значения прерыдущего ввода из входного буфера
			cout << "Value is wrong! Enter again\n";
		}
		else
			return value;
	} while (true);
}

int main()
{
		setlocale(LC_CTYPE, "ukr");
	List<int> lst;
	int index, value = NULL, x;
	do {
		cout << "\n0: Вихiд" << endl;
		cout << "1: Додати елемент в початок списку" << endl;
		cout << "2: Додати елемент в кiнець списку" << endl;
		cout << "3: Видалити елемент з початку списку" << endl;
		cout << "4: Видалити елемент з кiнця списку" << endl;
		cout << "5: Додати елемент за iндексом" << endl;
		cout << "6: Видалення за iндексом" << endl;
		cout << "7: Роздрукувати " << endl;
		cout << "8: Очистити список" << endl;
		cout << "9: Показати розмiр списку" << endl;	
              cin >> x;
        	switch (x) {
		case 1: 
			lst.push_front(Proverka(value));
			break;
		case 2: 
			lst.push_back(Proverka(value));
			break;
		case 3: lst.pop_front();
			break;
		case 4: lst.pop_back();
			break;
		case 5: cout << "Index: ";
			cin >> index;
			lst.insert(Proverka(value), index);
			break;
		case 6: cout << "Index: ";
			cin >> index;
			lst.removeAt(index);
			break;
		case 7: lst.PrintFromHead();
			break;
		case 8: lst.clear();
			break;
		case 9: cout << "Размер: " << lst.GetSize();
			break;
		default:
			break; }
	} while (x != 0);
	system("pause");
	return 0; }
