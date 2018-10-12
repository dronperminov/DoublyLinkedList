#ifndef DOUBLY_LINKED_LIST
#define DOUBLY_LINKED_LIST

template <typename T>
class DoublyLinkedList {
	struct Node {
		T value; // значение элемента списка
		Node *next; // ссылка на следующий элемент
		Node *prev; // ссылка на предыдущий элемент
	};

	Node *head; // начало списка
	Node *tail; // конец списка

	int length; // количество элементов списка

public:
	DoublyLinkedList(); // конструктор по умолчанию
	DoublyLinkedList(const DoublyLinkedList<T> &list); // конструктор копирования

	bool IsEmpty() const; // проверка списка на пустоту
	int Length() const; // получение длины списка

	T& GetFirst(); // получение первого элемента списка: O(1)
	T& GetLast(); // получение последнего элемента списка: O(1)
	T& Get(int index); // получение элемента по индексу: O(N)

	void AddFront(const T& value); // добавление в начало списка: O(1)
	void AddBack(const T& value); // добавление в конец списка: O(1)
	void InsertAt(int index, const T& value); // добавление в произвольное место списка: O(N)

	void RemoveFront(); // удаление с начала списка: O(1)
	void RemoveBack(); // удаление с конца списка: O(1)
	void RemoveAt(int index); // удаление по индексу: O(N)
	void Remove(const T& value); // удаление элементов равных value: O(N)

	void Print() const; // печать списка с начала
	void PrintBackward() const; // печать списка с конца

	~DoublyLinkedList(); // деструктор
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
	head = nullptr;
	tail = nullptr;

	length = 0;
}

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList(const DoublyLinkedList<T> &list) {
	head = nullptr;
	tail = nullptr;

	length = list.length;

	if (list.head == nullptr)
		return;
	
	for (Node *orig = list.head; orig != nullptr; orig = orig->next) {
		Node *node = new Node;

		node->value = orig->value;
		node->next = nullptr;
		node->prev = tail;

		// если список пуст
		if (tail == nullptr) {
			head = node; // то голова списка и есть этот элемент
		}
		else { // иначе вставляем в конец		
			tail->next = node;
		}

		tail = node;
	}
}

template <typename T>
bool DoublyLinkedList<T>::IsEmpty() const {
	return length == 0;
}

template <typename T>
int DoublyLinkedList<T>::Length() const {
	return length;
}

template <typename T>
T& DoublyLinkedList<T>::GetFirst() {
	// если нет элементов, бросаем исключение
	if (IsEmpty())
		throw "DoublyLinkedList::GetFirst(): list is empty";

	return head->value; // возвращаем первый элемент
}

template <typename T>
T& DoublyLinkedList<T>::GetLast() {
	// если нет элементов, бросаем исключение
	if (IsEmpty())
		throw "DoublyLinkedList::GetLast(): list is empty";

	return tail->value; // и возвращаем последнее значение
}

template <typename T>
T& DoublyLinkedList<T>::Get(int index) {
	// если индекс вне границ
	if (index < 0 || index >= length)
		throw "DoublyLinkedList::Get(index): index out of bounds"; // бросаем исключение

	Node *node = head;

	// доходим до элемента с нужным индексом
	while (node != nullptr && index) {
		index--;
		node = node->next;
	}

	return node->value; // возвращаем его значение
}

template <typename T>
void DoublyLinkedList<T>::AddFront(const T& value) {
	Node *node = new Node; // создаём элемент

	node->value = value; // сохраняем значение
	node->prev = nullptr;
	node->next = head;

	// если список пуст
	if (head == nullptr) {
		tail = node; // то хвост списка является этим элементом
	}
	else {		
		head->prev = node; // иначе вставляем в начало
	}

	head = node; // обновляем началос писка

	length++; // увеличиваем длину
}

template <typename T>
void DoublyLinkedList<T>::AddBack(const T& value) {
	Node *node = new Node;

	node->value = value;
	node->prev = tail;
	node->next = nullptr;

	// если список пуст
	if (tail == nullptr) {
		head = node; // то голова списка является этим элементом
	}
	else { // иначе вставляем в конец		
		tail->next = node;
	}

	tail = node; // обновляем конец списка

	length++; // увеличиваем длину
}

template <typename T>
void DoublyLinkedList<T>::InsertAt(int index, const T& value) {
	if (index < 0 || index >= length)
		throw "DoublyLinkedList::InsertAt(index): index out of bounds";

	// если вставляем перед нулевым элементом
	if (index == 0) {
		AddFront(value); // то вставляем в начало
		return;
	}
	
	// доходим до элемента с индексом index - 1
	Node *prev = head;

	while (index - 1) {
		index--;
		prev = prev->next;
	}

	// создаём новый элемент и вставляем его
	Node *node = new Node;

	// обновляем ссылку хвоста, если нужно
	if (prev->next == tail)
		tail->prev = node;

	node->value = value;
	node->next = prev->next;
	prev->next->prev = node;
	prev->next = node;
	node->prev = prev;

	length++; // увеличиваем длину
}

template <typename T>
void DoublyLinkedList<T>::RemoveFront() {
	// если список пуст
	if (IsEmpty())
		throw "DoublyLinkedList::RemoveFront: list is empty"; // бросаем исключение

	Node *tmp = head; // сохраняем значение текущего начала
	head = head->next; // переходим к следующему элементу
	delete tmp; // удаляем старое начало

	length--; // уменьшаем длину

	// если начало пуста
	if (head == nullptr) {
		tail = nullptr; // то и конец пуст
	}
	else {
		head->prev = nullptr; // иначе обновляем указатель на предыдущий элемент
	}
}

template <typename T>
void DoublyLinkedList<T>::RemoveBack() {
	// если список пуст
	if (IsEmpty())
		throw "DoublyLinkedList::RemoveBack: list is empty"; // бросаем исключение

	Node *tmp = tail; // сохраняем значение текущего конца
	tail = tail->prev; // переходим к предыдущему элементу
	delete tmp; // удаляем старый конец

	length--; // уменьшаем длину

	// если конец пуст
	if (tail == nullptr) {
		head = nullptr; // то и начало пусто
	}
	else {
		tail->next = nullptr; // иначе обновляем указатель на следующий элемент
	}
}

template <typename T>
void DoublyLinkedList<T>::RemoveAt(int index) {
	// если индекс находится вне границ
	if (index < 0 || index >= length)
		throw "DoublyLinkedList::RemoveAt(index): index out of bounds"; // бросаем исключение

	// если удаляем из нулевого индекса
	if (index == 0) {
		RemoveFront(); // то удаляем из начала
		return;
	}

	// если удаляем последний элемент
	if (index == length - 1) {
		RemoveBack(); // то удаляем с конца
		return;
	}

	// иначе доходим до элемента с нужным индексом
	Node *prev = nullptr;
	Node *node = head;

	while (index) {
		index--;

		prev = node;
		node = node->next;
	}

	length--; // уменьшаем длину

	Node *tmp = node; // запоминаем адрес нужного элемента
	prev->next = node->next; // подменяем указатели
	node->next->prev = prev; // минуя текущий элемент

	delete tmp; // удаляем ненужный элемент
}

template <typename T>
void DoublyLinkedList<T>::Remove(const T& value) {
	// пока нужный элемент в начале списка
	while (!IsEmpty() && head->value == value)
		RemoveFront(); // удаляем из начала

	// пока нужный элемент в конце списка
	while (!IsEmpty() && tail->value == value)
		RemoveBack(); // удаляем из конца

	// если удалять больше нечего
	if (IsEmpty())
		return; // то выходим

	// запоминаем текущее и предыдущее значения элементов списка
	Node *prev = head;
	Node *node = head->next;

	// доходим до конца списка
	while (node != nullptr) {
		if (node->value == value) { // если нашли элемент для удаления, то удаляем его
			length--; // уменьшаем длину
			
			Node *tmp = node; // сохраняем адрес текущего элемента
			prev->next = node->next; // подменяем указатели
			node->next->prev = prev; // минуя текущий элемент

			delete tmp; // удаляем ненужный элемент

			node = prev;
		}

		prev = node;
		node = node->next; // переходим к следующему элементу
	}
}

template <typename T>
void DoublyLinkedList<T>::Print() const {
	if (IsEmpty())
		std::cout << "(empty)";
	
	Node *node = head;

	while (node != nullptr) {
		std::cout << node->value << " ";

		node = node->next;
	}
}

template <typename T>
void DoublyLinkedList<T>::PrintBackward() const {
	if (IsEmpty())
		std::cout << "(empty)";

	Node *node = tail;

	while (node != nullptr) {
		std::cout << node->value << " ";

		node = node->prev;
	}
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
	while (head) {
		Node *tmp = head;
		head = head->next;
		delete tmp;
	}

	tail = nullptr;
}

#endif