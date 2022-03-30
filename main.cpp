#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <process.h>
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

using namespace std;

struct mark_data
{
	char* subject_name;
	Uint32 subject_name_length;
	vector<Uint8> marks;
};

struct mark_data_node
{
	mark_data_node* next;
	mark_data_node* prev;
	mark_data data;
};

class Student
{

private:
	mark_data_node* HEAD;
	mark_data_node* TAIL;

public:
	Student()
	{

	}

	~Student()
	{

	}

	void add_mark(char* subject_name, Uint8 mark)
	{
		mark_data_node* cur_node = HEAD;

		if(strcmp(subject_name, HEAD->data.subject_name) == 0)
		{
			HEAD->data.marks.push_back(mark);
			return;
		}

		else
		{
			while(strcmp(subject_name, cur_node->data.subject_name) != 0)
			{
				cur_node = cur_node->next;
			}

			//now we are at the node we need

			cur_node->data.marks.push_back(mark);
		}
	}

	void add_subject(char* subject_name)
	{
		mark_data_node* temp = (mark_data_node*)malloc(sizeof(mark_data_node));

		if(HEAD == nullptr)
		{
			HEAD = TAIL = temp;
			HEAD->data.subject_name = (char*)malloc(sizeof(char) * (strlen(subject_name) + 1));
			strcpy(HEAD->data.subject_name, subject_name);
			return;
		}

		temp->next = nullptr;
		temp->prev = TAIL;
		TAIL = temp;

		temp->data.subject_name = (char*)malloc(sizeof(char) * (strlen(subject_name) + 1));
		strcpy(temp->data.subject_name, subject_name);
	}

	void calculate_av_mark(char* subject_name)
	{
		mark_data_node* cur_node = HEAD;

		if(strcmp(subject_name, HEAD->data.subject_name) == 0)
		{
			int temp = 0;

			for(int i = 0; i < cur_node->data.marks.size(); ++i)
			{
				temp += cur_node->data.marks[i];
			}

			cout << (double)temp / (double)cur_node->data.marks.size();

			return;
		}

		else
		{
			while(strcmp(subject_name, cur_node->data.subject_name) != 0)
			{
				cur_node = cur_node->next;
			}

			//now we are at the node we need

			int temp = 0;

			for(int i = 0; i < cur_node->data.marks.size(); ++i)
			{
				temp += cur_node->data.marks[i];
			}

			cout << (double)temp / (double)cur_node->data.marks.size();
		}
	}

	void print_student_data()
	{
		mark_data_node* cur_node = HEAD;

		do
		{
			for(int i = 0; i < strlen(cur_node->data.subject_name); ++i)
			{
				cout << cur_node->data.subject_name[i];
			}

			cout <<  ", average mark: ";

			int temp = 0;
			int av_mark = 0;

			for(int i = 0; i < cur_node->data.marks.size(); ++i)
			{
				temp += cur_node->data.marks[i];
			}

			av_mark = (double)temp / (double)cur_node->data.marks.size();

			cout << av_mark << "\n";
			cur_node = cur_node->next;
		}
		while(cur_node->next != nullptr);
	}
};

void freq_of_symbols(FILE* out, FILE* in)
{
	int freqs[256];

	for(int i = 0; i < 255; ++i)
	{
		freqs[i] = 0;
	}

	char c = 0;

	while(fscanf(in, "%c", &c) != EOF)
	{
		freqs[(Uint8)c]++;
	}

	for(int i = 0; i < 255; ++i)
	{
		fprintf(out, "%c\t%d\n", (char)i, freqs[i]);
	}
}

void to_binary(int in, FILE* out)
{
	for(int i = 31; i >= 0; --i)
	{
		fprintf(out, "%c", ((1 << i) & in) ? '1' : '0');
	}
}

const char hex_numbers[16] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

char* binary_to_hex(FILE* in)
{
	char c = 0;
	int num_length = 0;

	char chars[64];
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
			temp |= (((chars[(i / 4) + j] == 0x30) ? 0 : 1) << j);
		}

		result[i / 4] = hex_numbers[temp];
	}

	return result;
}

void write_pine_tree(int num_of_rows)
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

int* matrix_rows_average(int** matrix, int cols, int rows)
{
	static int* av_list = (int*)malloc(sizeof(int) * rows);

	for(int i = 0; i < rows; ++i)
	{
		int av = 0;

		for(int j = 0; j < cols; ++j)
		{
			av += matrix[i][j];
		}

		av_list[i] = av / cols;
	}

	return av_list;
}

struct Node
{
	Node* prev;
	Node* next;
	char* string;
	int size;
};

void linked_list_write_to_file(FILE* out, Node* TAIL)
{
	Node* cur_node = TAIL;

	int num_of_elements = 0;

	do
	{
		num_of_elements++;
		cur_node = cur_node->prev;
	}
	while(cur_node->prev != nullptr);

	cur_node = TAIL;

	do
	{
		fprintf(out, "%d\t%s\t%d\n", num_of_elements, cur_node->string, cur_node->size);
		num_of_elements--;
		cur_node = cur_node->prev;
	}
	while(cur_node->prev != nullptr);
}

void linked_list_paste_element(Node* HEAD, Node* el, const int index)
{
	Node* cur_node = HEAD;
	int cur_index = 0;

	while(cur_index <= index)
	{
		cur_node = cur_node->next;
	}

	//now we are at the node AFTER which we want to past our new node

	el->next = cur_node->next;
	el->prev = cur_node;

	cur_node->next->prev = el;
	cur_node->next = el;
}

int main()
{
	cout << "test\n\n";

	write_pine_tree(40);
}
