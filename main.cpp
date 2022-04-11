#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <QList>

typedef uint64_t Uint64;
typedef int64_t Sint64;
typedef uint32_t Uint32;
typedef int32_t Sint32;
typedef uint16_t Uint16;
typedef int16_t Sint16;
typedef uint8_t Uint8;
typedef int8_t Sint8;

//ВООТ ОН ПРОЕКТ В КУУУТЕЕЕ КОМПИЛИТСЯЯ! А БЕЗ ЧЁТКОГО ТЗ РЕЗУЛЬТАТ -- ХЕРАК ХЕРАК И В ПРОДАКШН!!!!

//ПРОЕКТ ЧИТАЕТ ФАЙЛЫ ИЗ СВОЕЙ ПАПКИ. ЧТОБЫ ОН ЗАРАБОТАЛ, НЕОБХОДИМО QT УКАЗАТЬ, ЧТО ЭКЗЕШНИК НАДО СОВАТЬ В ПАПКУ ПРОЕКТА. ПОЧЕМУ-ТО В НАСТРОЙКАХ ЭТО НЕ СОХРАНЯЕТСЯ ПРИ ПЕРЕНОСЕ НА ДРУГОЙ КОМП. ЕСЛИ ЭТО СДЕЛАТЬ, ТО ВСЁ ЗАРАБОТАЕТ. НАДО ПОМЕНЯТЬ КАТАЛОГ СБОРКИ. РАБОЧУЮ ДИРЕКТОРИЮ ТОЖЕ НАДО ТКНУТЬ В ПАПКУ ПРОЕКТА.

using namespace std;

struct mark_data
{
	char* subject_name;
	vector<int> marks;
};

struct mark_data_node
{
	mark_data_node* next;
	mark_data_node* prev;
	mark_data data;
};

class Student //8th task
{

private:
	mark_data_node* HEAD;
	mark_data_node* TAIL;

public:
	Student()
	{
		HEAD = nullptr;
		TAIL = nullptr;
	}

	~Student()
	{

	}

	void add_mark(char* subject_name, int mark)
	{
		mark_data_node* cur_node = HEAD;

		while(strcmp(subject_name, cur_node->data.subject_name) != 0 && cur_node != nullptr)
		{
			cur_node = cur_node->next;
		}

		//now we are at the node we need

		if(cur_node != nullptr)
		{
			cur_node->data.marks.push_back(mark);
		}
	}

	void add_subject(char* subject_name)
	{
		mark_data_node* temp = new mark_data_node();

		if(HEAD == nullptr)
		{
			HEAD = temp;
			TAIL = temp;

			HEAD->data.subject_name = (char*)malloc(sizeof(char) * (strlen(subject_name)));
			HEAD->next = nullptr;
			HEAD->prev = nullptr;
			strcpy(HEAD->data.subject_name, subject_name);
			return;
		}

		temp->next = nullptr;
		temp->prev = TAIL;
		temp->prev->next = temp;
		TAIL = temp;

		temp->data.subject_name = (char*)malloc(sizeof(char) * (strlen(subject_name)));
		strcpy(temp->data.subject_name, subject_name);
	}

	double calculate_av_mark()
	{
		mark_data_node* cur_node = HEAD;

		int subj_num = 0;

		double sum = 0;

		while(cur_node != nullptr)
		{
			double temp = 0;

			if(cur_node->data.marks.size() > 0)
			{
				for(int i = 0; i < cur_node->data.marks.size(); ++i)
				{
					temp += cur_node->data.marks[i];
				}

				temp /= (double)cur_node->data.marks.size();
			}

			sum += temp;

			cur_node = cur_node->next;
			subj_num++;
		}

		sum /= (double)subj_num;
		return sum;
	}

	void print_student_data()
	{
		mark_data_node* cur_node = HEAD;

		cout << "\n\nData:\n\n";

		while(cur_node != nullptr)
		{
			//cout << "sdfsdf";
			cout << cur_node->data.subject_name;

			cout <<  ", average mark: ";

			double temp = 0;
			double av_mark = 0;

			if(cur_node->data.marks.size() > 0)
			{
				for(int i = 0; i < cur_node->data.marks.size(); ++i)
				{
					temp += cur_node->data.marks[i];
				}

				av_mark = (double)temp / ((double)cur_node->data.marks.size());
			}

			cout << av_mark << "\n";
			cur_node = cur_node->next;
		}
	}
};

void freq_of_symbols(FILE* out, FILE* in) //1st task
{
	int freqs[256];

	for(int i = 0; i < 256; ++i)
	{
		freqs[i] = 0;
	}

	char c = 0;

	while(fscanf(in, "%c", &c) != EOF)
	{
		freqs[(Uint8)c]++;
	}

	for(int i = 0; i < 256; ++i)
	{
		fprintf(out, "%c\t%d\n", (char)i, freqs[i]);
	}
}

void to_binary(int in, FILE* out) //2nd task
{
	for(int i = 31; i >= 0; --i)
	{
		fprintf(out, "%c", ((1 << i) & in) ? '1' : '0');
		printf("%c", ((1 << i) & in) ? '1' : '0');
	}
}

const char hex_numbers[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

char* binary_to_hex(FILE* in) //3rd task
{
	char c = 0;
	int num_length = 0;

	char chars[64];

	for(int i = 0; i < 63; ++i)
	{
		chars[i] = 0;
	}

	static char result[16];

	while(fscanf(in, "%c", &c) != EOF)
	{
		chars[num_length] = c;
		num_length++;
	}

	for(int i = 0; i < num_length; i += 4)
	{
		int temp = 0;

		for(int j = 0; j < 4; ++j)
		{
			temp |= (((chars[i + j] == 0x30) ? 0 : 1) << j);
		}

		result[i / 4] = hex_numbers[temp];
	}

	return result;
}

void write_pine_tree(int num_of_rows) //4th task
{
	for(int i = 0; i < num_of_rows; ++i)
	{
		for(int j = 0; j < num_of_rows - 1 - i; ++j)
		{
			cout << " ";
		}

		for(int j = 0; j < 2 * i + 1; ++j)
		{
			cout << "*";
		}

		cout << "\n";
	}
}

QList<double> matrix_rows_average(int** matrix, int cols, int rows) //5th task
//прототип QList<double>(*func)(int**, int, int)
{
	QList<double> aver;

	for(int i = 0; i < rows; ++i)
	{
		double av = 0.0;

		for(int j = 0; j < cols; ++j)
		{
			av += matrix[i][j];
		}

		aver.append(av / cols);
	}

	return aver;
}

struct Node
{
	Node* prev;
	Node* next;
	char* string;
	int size;
};

struct linklist
{
	Node* HEAD;
	Node* TAIL;
};

void linked_list_write_to_file(FILE* out, Node* TAIL, Node* HEAD) //6th task
{
	fprintf(out, "%s\n", "From tail");

	Node* cur_node = TAIL;

	int num_of_elements = 0;

	do
	{
		num_of_elements++;
		cur_node = cur_node->prev;
	}
	while(cur_node->prev != nullptr);

	cur_node = TAIL;

	while(cur_node != nullptr)
	{
		fprintf(out, "%d\t\"%s\"\t%d\n", num_of_elements, cur_node->string, cur_node->size);
		num_of_elements--;
		cur_node = cur_node->prev;
	}

	//===================================

	fprintf(out, "\n%s\n", "From head");

	cur_node = HEAD;

	num_of_elements = 0;

	while(cur_node != nullptr)
	{
		fprintf(out, "%d\t\"%s\"\t%d\n", num_of_elements, cur_node->string, cur_node->size);
		num_of_elements++;
		cur_node = cur_node->next;
	}
}

void linked_list_paste_element(Node* HEAD, Node* el, const int index) //7th task
{
	Node* cur_node = HEAD;
	int cur_index = 0;

	while(cur_index < index && cur_node != nullptr)
	{
		cur_node = cur_node->next;
		cur_index++;
	}

	//now we are at the node AFTER which we want to past our new node

	el->next = cur_node->next;
	el->prev = cur_node;

	cur_node->next->prev = el;
	cur_node->next = el;

	//cout << "Prev string " << el->prev->string << " Next string " << el->next->string;
}

int matrix[16] = {
	2, 3, 44, 6,
	4, 4, 0, -55,
	-8, 5, 4, 1,
	0, 1, 2, 3,
};

int main()
{
	FILE* in;
	FILE* out;

	in = fopen("1.txt", "r");
	out = fopen("1_result.txt", "w");

	freq_of_symbols(out, in);

	fclose(in);
	fclose(out);

	out = fopen("2_result.txt", "w");

	to_binary(0xffeeddcc, out);

	fclose(out);

	cout << "\n\n";

	in = fopen("3.txt", "r");

	char* nums = binary_to_hex(in);

	nums[16] = '\0';

	cout << nums;

	fclose(in);

	cout << "\n\n";

	write_pine_tree(10);

	cout << "\n\n";

	int** mat = (int**)malloc(sizeof(int*) * 4);

	for(int i = 0; i < 4; ++i)
	{
		mat[i] = (int*)malloc(4 * sizeof(int));
	}

	for(int i = 0; i < 16; ++i)
	{
		mat[i / 4][i & 3] = matrix[i];
	}

	QList<double> avers = matrix_rows_average(mat, 4, 4);

	for(int i = 0; i < 4; ++i)
	{
		cout << avers[i] << "\t";
	}

	cout << "\n\n";

	for(int i = 0; i < 4; ++i)
	{
		free(mat[i]);
	}

	free(mat);

	//================================================
	//Behold the linked list

	linklist list;

	list.HEAD = (Node*)malloc(sizeof(Node));
	list.HEAD->string = (char*)malloc(6);

	strcpy(list.HEAD->string, "HEAD");
	list.HEAD->size = strlen(list.HEAD->string);

	Node* cur_node = list.HEAD;

	for(int i = 0; i < 10; ++i)
	{
		Node* new_node = (Node*)malloc(sizeof(Node));

		cur_node->next = new_node;

		new_node->next = nullptr;

		new_node->prev = cur_node;

		cur_node = new_node;

		cur_node->string = (char*)malloc(10);
		char buffer[30];
		strcpy(cur_node->string, itoa(rand(), buffer, 10));
		cur_node->size = strlen(cur_node->string);
	}

	list.TAIL = cur_node;
	strcpy(cur_node->string, "TAIL");
	cur_node->size = strlen(cur_node->string);

	list.HEAD->prev = nullptr;
	list.TAIL->next = nullptr;

	out = fopen("6_result.txt", "w");

	linked_list_write_to_file(out, list.TAIL, list.HEAD);

	cur_node = list.HEAD; //delete the list

	while(cur_node->next != nullptr)
	{
		cur_node = cur_node->next;

		//cout << "Next: " << cur_node->next << " Prev: " << cur_node->prev << " String: " << cur_node->string << "\n";

		free(cur_node->prev->string);
		free(cur_node->prev);
	}

	fclose(out);

	//================================================
	//Behold another linked list

	linklist list2;

	list2.HEAD = (Node*)malloc(sizeof(Node));
	list2.HEAD->string = (char*)malloc(6);

	strcpy(list2.HEAD->string, "HEAD");
	list2.HEAD->size = strlen(list2.HEAD->string);

	cur_node = list2.HEAD;

	for(int i = 0; i < 10; ++i)
	{
		Node* new_node = (Node*)malloc(sizeof(Node));

		cur_node->next = new_node;

		new_node->next = nullptr;

		new_node->prev = cur_node;

		cur_node = new_node;

		cur_node->string = (char*)malloc(10);
		char buffer[30];
		strcpy(cur_node->string, itoa(rand(), buffer, 10));
		cur_node->size = strlen(cur_node->string);
	}

	list2.TAIL = cur_node;
	strcpy(cur_node->string, "TAIL");
	cur_node->size = strlen(cur_node->string);

	list2.HEAD->prev = nullptr;
	list2.TAIL->next = nullptr;

	cout << "\n\nLinked list before new element is pasted:\n\n";

	cur_node = list2.HEAD;

	while(cur_node != nullptr)
	{
		cout << "\"" << cur_node->string << "\" " << cur_node->size << "\n";
		cur_node = cur_node->next;
	}

	Node* new_element = (Node*)malloc(sizeof(Node));

	new_element->next = nullptr;
	new_element->prev = nullptr;
	new_element->string = (char*)malloc(strlen("I'm a new element somewhere in the linked list"));
	strcpy(new_element->string, "I'm a new element somewhere in the linked list");

	new_element->size = strlen("I'm a new element somewhere in the linked list");

	linked_list_paste_element(list2.HEAD, new_element, 5);

	cout << "\n\nLinked list after new element is pasted:\n\n";

	cur_node = list2.HEAD;

	while(cur_node != nullptr)
	{
		cout << "\"" << cur_node->string << "\" " << cur_node->size << "\n";
		cur_node = cur_node->next;
	}

	cur_node = list2.HEAD; //delete the list

	while(cur_node->next != nullptr)
	{
		cur_node = cur_node->next;

		//cout << "Next: " << cur_node->next->string << " Prev: " << cur_node->prev->string << " String: " << cur_node->string << "\n";

		free(cur_node->prev->string);
		free(cur_node->prev);
	}

	//Классы нужны только в том случае, когда на разработку приложения пущены силы более одного человека и оона длится более одного года. Они сильно замедляют написание кода, усложняют его понимание, а производительность летит от значения, близкого к таковому у ассемблерного кода, к чертям вниз. Я видел замечательный проект с абстрактными классами, где было 10, КАРЛ, уровней наследования.

	cout << "\n\n";

	Student stud;
	stud.add_subject("M(a/e)th");
	stud.add_mark("M(a/e)th", 6);
	stud.add_mark("M(a/e)th", 666);

	stud.print_student_data();

	stud.add_mark("M(a/e)th", 66);

	stud.print_student_data();

	stud.add_subject("Programming");

	stud.add_mark("Programming", 6); //here
	stud.add_mark("Programming", -666);
	stud.add_mark("M(a/e)th", 66);

	stud.print_student_data();

	cout << "\n\nav. mark: " << stud.calculate_av_mark();
}
