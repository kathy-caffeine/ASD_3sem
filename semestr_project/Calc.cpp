#include "Calc.h"

void calc::reset_list()
{
	inf_head = nullptr;
	inf_tail = nullptr;
	size = 0;
}

calc::calc()
{
	reset_list();
}

calc::~calc() {
	if (inf_head) {
		while (inf_head->next) {
			inf_head = inf_head->next;
			delete inf_head->prev;
		}
		reset_list();
	}
}

void calc::add_first(string newElem)
{
	inf_head = new Node(newElem);
	inf_tail = inf_head;
}

void calc::push_back(string newElem) // add in the end
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		Node* tmp = new Node(newElem);
		tmp->prev = inf_tail;
		inf_tail->next = tmp;
		inf_tail = tmp;
	}
	size++;
}

void calc::read_expression() { // read formula
	bool cont = true;
	string added;
	int bracket = 0;

	if (!inf_head) {
		cin >> added;
		push_back(added);
		size = 1;
		if (added.length() == 1) {
			if (added == "(") {
				inf_tail->expression = static_cast<Node::Type>(16); 
				inf_tail->order = static_cast<Node::Priopity>(0);
				bracket++;
			}
			if (added == ")") {
				inf_tail->expression = static_cast<Node::Type>(16);
				inf_tail->order = static_cast<Node::Priopity>(0);
				bracket--;
			}
		}
		if (added[added.length() - 1] == ';') {
			cont = false;
			inf_tail->data.erase(added.length() - 1, 1);
		}
		check_type(added);
		if (inf_tail->expression == static_cast<Node::Type>(0)) {
			// incorrect input
			cout << endl << "Incorrect input. Can not identify expression." << endl;
			cont = false;
		}
	}

	while (cont) {
		cin >> added;
		if (added.length() == 1) {
			if (added == "(") {
				inf_tail->expression = static_cast<Node::Type>(16);
				inf_tail->order = static_cast<Node::Priopity>(0);
				bracket++;
			}
			if (added == ")") {
				inf_tail->expression = static_cast<Node::Type>(16);
				inf_tail->order = static_cast<Node::Priopity>(0);
				bracket--;
			}
		}
		push_back(added);
		size++;
		check_type(added);
		if (inf_tail->expression == static_cast<Node::Type>(0)) {
			// incorrect input
			cout << endl << "Incorrect input. Can not identify expression." << endl;
			break;
		}
		if (added[added.length() - 1] == ';') {
			cont = false;
			inf_tail->data.erase(added.length() - 1, 1);
		}
	}
	if (bracket == 0) {
		// incorrect input
		cout << "Incorrect input: wrong bracket amount" << endl;
	}
}

void calc::check_type(string str) {
	if (str.length() == 1) { // it could be only a sign
		if (str == "+") { inf_tail->expression = static_cast<Node::Type>(1); inf_tail->order = static_cast<Node::Priopity>(1); }
		if (str == "-") { inf_tail->expression = static_cast<Node::Type>(2); inf_tail->order = static_cast<Node::Priopity>(1); }
		if (str == "*") { inf_tail->expression = static_cast<Node::Type>(3); inf_tail->order = static_cast<Node::Priopity>(2); }
		if (str == "/") { inf_tail->expression = static_cast<Node::Type>(4); inf_tail->order = static_cast<Node::Priopity>(2); }
		if (str == "^") { inf_tail->expression = static_cast<Node::Type>(5); inf_tail->order = static_cast<Node::Priopity>(3); }
	}
	else if ((str[0] == 'p') && (str[1] == 'i')) { inf_tail->expression = static_cast<Node::Type>(17); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 'e') && (str[1] == 'p') && (str[2] == 's')) { inf_tail->expression = static_cast<Node::Type>(18); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 's') && (str[1] == 'i') && (str[2] == 'n')) { inf_tail->expression = static_cast<Node::Type>(6); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 'c') && (str[1] == 'o') && (str[2] == 's')) { inf_tail->expression = static_cast<Node::Type>(7); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 't') && (str[1] == 'g')) { inf_tail->expression = static_cast<Node::Type>(8); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 'c') && (str[1] == 't') && (str[2] == 'g')) { inf_tail->expression = static_cast<Node::Type>(9); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 'l') && (str[1] == 'n')) { inf_tail->expression = static_cast<Node::Type>(10); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 'l') && (str[1] == 'g')) { inf_tail->expression = static_cast<Node::Type>(11); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 's') && (str[1] == 'q') && (str[2] == 'r') && (str[3] == 't')) { inf_tail->expression = static_cast<Node::Type>(12); inf_tail->order = static_cast<Node::Priopity>(10); }
	else if ((str[0] == 'c') && (str[1] == 'u') && (str[2] == 'b') && (str[3] == 'e') && (str[4] == 'r')) { inf_tail->expression = static_cast<Node::Type>(13); inf_tail->order = static_cast<Node::Priopity>(10); }
	else { // chiselco
		bool dot = false, number = false, incorrect = false, minus = (str[0] =='-');
		if (minus) {
			str.erase(0, 1); // delele minus before checking
		}
		for (int i = 0; i < str.length(); i++) {
			number = ((str[i] == '0') || (str[i] == '1') || (str[i] == '2') || (str[i] == '3') || (str[i] == '4') || (str[i] == '5') || (str[i] == '6') ||
				(str[i] == '7') || (str[i] == '8') || (str[i] == '9'));
			if (!dot) dot = str[i] == '.'; // if prev symbols were not dots, check for dot
			if ((!number) || (!dot)) { // if str[i] is a letter, bracket or smth else
				incorrect = true;
				inf_tail->expression = static_cast<Node::Type>(0);
				break;
			}
		}
		if (number && dot) {
			inf_tail->expression = static_cast<Node::Type>(15);
			inf_tail->order = static_cast<Node::Priopity>(10);
			// double lol = atof(word.c_str());
			inf_tail->res = atof(inf_tail->data.c_str());
		}
		else if (number && !dot) {
			inf_tail->expression = static_cast<Node::Type>(14);
			inf_tail->order = static_cast<Node::Priopity>(10);
			inf_tail->res = (int)(inf_tail->expression);
		}
		if (minus) inf_tail->res = - inf_tail->res;
	}
}

void calc::push_front(string newElem) // add in the beginning
{
	if (size == 0) {
		add_first(newElem);
	}
	else {
		Node* tmp = new Node(newElem, inf_head);
		inf_head->prev = tmp;
		inf_head = tmp;
	}
	size++;
}

void calc::pop_back() // delete last
{
	if (size == 0) {
		throw out_of_range("Nothing to delete");
	}
	if (size == 1) {
		delete inf_head;
		reset_list();
	}
	else {
		Node* current = inf_tail->prev;
		current->next = nullptr;
		delete inf_tail;
		inf_tail = current;
		size--;
	}
}

void calc::pop_front() // delete first
{
	if (size == 0) {
		throw out_of_range("Nothing to delete");
	}
	if (size == 1) {
		delete inf_head;
		reset_list();
	}
	else {
		inf_head = inf_head->next;
		delete inf_head->prev;
		size--;
	}
}

void calc::insert(string newElem, int index) // add #index
{
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	if (index == 0) { // newElem - new head
		push_front(newElem);
	}
	else if (index == size - 1) { // newElem - new tail
		push_back(newElem);
	}
	else {
		Node* add = new Node(newElem);
		Node* tmp = inf_head;
		for (int i = 1; i < index - 1; i++) {
			tmp = tmp->next;
		} // tmp - before adding
		add->prev = tmp;
		add->next = tmp->next;
		tmp->next = add;
		size++;
	}
}

string calc::at(size_t index) const // find data from #index
{
	if (index >= size) {
		throw out_of_range("Index is greater than list size");
	}
	if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	size_t counter = 0;
	Node* current = inf_head;
	while (counter != index) {
		current = current->next;
		counter++;
	}
	return current->data;
}

void calc::remove(int index)
{
	Node* tmp = inf_head;
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	if (index == 0) { // delete head
		pop_front();
	}
	else if (index == size - 1) { // delete tail
		pop_back();
	}
	else {
		for (int i = 0; i < index; i++) {
			tmp = tmp->next;
		} // tmp should be deleted
		tmp->prev->next = tmp->next;
		tmp->next->prev = tmp->prev;
		delete tmp;
		size--;
	}
}

size_t calc::get_size() const
{
	return size;
}

void calc::print_to_console()
{
	cout << "Size is " << size << endl;
	if (size != 0) {
		Node* tmp = inf_head;
		do {
			cout << tmp->data << " ";
			tmp = tmp->next;
		} while (tmp->next);
		if(tmp) cout << tmp->data << endl;
		cout << "....." << endl;
	}
	else cout << "nothing to print" << endl;
}

void calc::clear()
{
	if (inf_head) {
		while (inf_head->next) {
			inf_head = inf_head->next;
			delete inf_head->prev;
		}
		reset_list();
	}
}

void calc::set(int index, string newElem)
{
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	else {
		Node* tmp = inf_head;
		for (int i = 0; i < index; i++) {
			tmp = tmp->next;
		}
		tmp->data = newElem;
	}
}

bool calc::isEmpty()
{
	return (inf_head == nullptr);
}

void calc::insert(calc newList, int index)
{
	if (index > size - 1) {
		throw out_of_range("Index is greater than list size");
	}
	if (index < 0) {
		throw out_of_range("Index is less than zero");
	}
	if (index == 0) {
		newList.inf_tail->next = inf_head;
		inf_head->prev = newList.inf_tail;
		inf_head = newList.inf_head;
		size = size + newList.get_size();
	}
	else if (index == size - 1) {
		inf_tail->next = newList.inf_head;
		newList.inf_head->prev = inf_tail;
		inf_tail = newList.inf_tail;
		size = size + newList.get_size();
	}
	else {
		Node* tmp = inf_head;
		int counter = index;
		while (counter)
		{
			tmp = tmp->next;
			counter--;
		} // add after tmp
		newList.inf_tail->next = tmp->next;
		tmp->next->prev = newList.inf_tail;
		tmp->next = newList.inf_head;
		newList.inf_head->prev = inf_head;
		size = size + newList.get_size();
	}
}