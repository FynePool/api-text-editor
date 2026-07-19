#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LINESIZE 1024
struct line
{
	char* content;
	struct line* next;
};

struct history_entry
{
	struct line* text;
	int lineCount;
	struct history_entry* previous;
};

struct line* currentText;
int currentLineCount;
struct history_entry* history;

void make_history_entry()
{

}

void initialize_line(struct line** l)
{
	*l = (struct line*)malloc(sizeof(struct line));
	(*l)->content = NULL;
	(*l)->next = NULL;
}

void change_lines(int start, int end)
{
	/*
	1. delete history from this point on
	2. create history entry
	3. apply change
	*/
	if (currentLineCount)
		make_history_entry();
	struct line* current = currentText;

	while (start != 1 && current->content != NULL)//translate to start position
	{
		current = current->next;
		start--;
		end--;
	}
	for (int i = start; i <= end; i++)
	{
		char* newLine = (char*)malloc(LINESIZE);
		if (fgets(newLine, LINESIZE, stdin));
		if (current->content != NULL)
		{
			free(current->content);
		}
		current->content = (char*)malloc(strlen(newLine) + 1);
		strcpy(current->content, newLine);
		free(newLine);
		if (current->next == NULL)
		{
			initialize_line(&(current->next));
		}
		current = current->next;
	}
	char c;
	c = fgetc(stdin);
	c = fgetc(stdin);
}

void delete_lines(int start, int end)
{

}

void print_lines(int start, int end)
{
	struct line* current = currentText;

	while (start != 1 && current->content != NULL)//translate to start position
	{
		current = current->next;
		start--;
		end--;
	}
	for (int i = start; i <= end; i++)
	{
		if (current->content == NULL)
			printf(".\n");
		else
		{
			printf("%s", current->content);
			current = current->next;
		}
	}
}

void undo(int steps)
{

}

void redo(int steps)
{

}

int main()
{
	initialize_line(&currentText);
	history = (struct history_entry*)malloc(sizeof(struct history_entry));
	while (1)
	{
		int foundComma = 0;
		int start = 0, end = 0;
		char c = '.', opr;
		//read command
		while (c != '\n')
		{
			c = fgetc(stdin);
			if (c == ',')
			{
				foundComma = 1;
			}
			else if (c >= '0' && c <= '9')
			{
				if (foundComma == 0)
				{
					start = (start * 10) + (c - 48);
				}
				else
				{
					end = (end * 10) + (c - 48);
				}
			}
			else if (c >= 'a' && c <= 'z')
			{
				opr = c;
			}
		}

		if (opr == 'c')
			change_lines(start, end);
		if (opr == 'd')
			delete_lines(start, end);
		if (opr == 'p')
			print_lines(start, end);
		if (opr == 'u')
			undo(start);
		if (opr == 'r')
			redo(start);
		if (opr == 'q')
		{
			break;
		}
	}
	return 0;
}
