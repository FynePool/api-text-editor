#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINESIZE 1025

struct line
{
	char* content;
	struct line* next;
};

struct history_entry
{
	struct line* text;
	int lineCount;
	struct history_entry* next;
	struct history_entry* previous;
};

struct line* currentText;
int currentLineCount;
int stepsBackInHistory = 0;
int historyEntries = 0;
struct history_entry* history;

void free_text(struct line* text)
{
	struct line* toDelete = text;
	while (text != NULL)
	{
		toDelete = text;
		text = text->next;
		free(toDelete->content);
		free(toDelete);
	}
}

void free_history_entry(struct history_entry* h)
{
	free_text(h->text);
	free(h);
}

void initialize_line(struct line** l)
{
	(*l) = (struct line*)malloc(sizeof(struct line));
	(*l)->content = NULL;
	(*l)->next = NULL;
}

void initialize_history_entry(struct history_entry** h)
{
	*h = (struct history_entry*)malloc(sizeof(struct history_entry));
	(*h)->text = NULL;
	(*h)->lineCount = 0;
	(*h)->next = (*h)->previous = NULL;
}

struct line* copy_text(struct line* destination, struct line* source)
{
	if (source == NULL)
		return NULL;
	if (destination != NULL)
		free_text(destination);
	initialize_line(&destination);
	struct line* beginning = destination;
	while (source->content != NULL)
	{
		destination->content = (char*)malloc(strlen(source->content) + 2);
		strcpy(destination->content, source->content);
		source = source->next;
		initialize_line(&destination->next);
		destination = destination->next;
	}
	return beginning;
}

void delete_recent_history()
{
	int stepsBack = stepsBackInHistory;
	struct history_entry* historyStep = history;
	while (stepsBack>0)
	{
		stepsBack--;
		historyStep = historyStep->previous;
	}
	history = historyStep;
	while (history->next != NULL)
	{
		historyStep = history->next;
		history->next = historyStep->next;
		free_history_entry(historyStep);
		historyEntries--;
	}
	stepsBackInHistory = 0;
}

void make_history_entry()
{
	struct history_entry* new_entry;
	initialize_history_entry(&new_entry);
	new_entry->previous = history;
	history->next = new_entry;
	new_entry->next = NULL;
	history = new_entry;
	new_entry->text = copy_text(new_entry->text, currentText);
	new_entry->lineCount = currentLineCount;
}

void change_lines(int start, int end)
{
	/*
	1. delete history from this point on
	2. create history entry
	3. apply change
	*/
	if (stepsBackInHistory)
		delete_recent_history();
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
		currentLineCount++;
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
	make_history_entry();
	historyEntries++;
}

void delete_lines(int start, int end)
{

	if (stepsBackInHistory)//if in history entry
		delete_recent_history();//delete all recent history entries

	struct line* current = currentText;
	if (current == NULL)
		return;
	if (start == 1)
	{
		while (start <= end && current->content != NULL)
		{
			struct line* toDelete = current;
			current = current->next;
			currentText = current;
			free(toDelete->content);
			free(toDelete);
			start++;
			currentLineCount--;
		}
	}
	else
	{
		while (start > 2 && current->content != NULL)//translate to start position
		{
			current = current->next;
			start--;
			end--;
		}
		if (start == 2)
		{
			while (start <= end && current->next->content != NULL)
			{
				struct line* toDelete = current->next;
				free(toDelete->content);
				current->next = toDelete->next;
				free(toDelete);
				start++;
				currentLineCount--;
			}
		}
	}

	make_history_entry();
	historyEntries++;
}

void print_lines(int start, int end)
{
	struct line* current = currentText;

	while (start != 1 && current != NULL && current->content != NULL)//translate to start position
	{
		current = current->next;
		start--;
		end--;
	}
	for (int i = start; i <= end; i++)
	{
		if (current == NULL || current->content == NULL)
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
	int stepsBack = stepsBackInHistory;
	struct history_entry* historyStep = history;
	while (stepsBack)
	{
		stepsBack--;
		historyStep = historyStep->previous;
	}

	while (stepsBackInHistory<historyEntries && steps)
	{
		steps--;
		stepsBackInHistory++;
		historyStep = historyStep->previous;
	}
	currentText = copy_text(currentText, historyStep->text);
	currentLineCount = historyStep->lineCount;
}

void redo(int steps)
{
	int stepsBack = stepsBackInHistory;
	struct history_entry* historyStep = history;
	while (stepsBack)
	{
		stepsBack--;
		historyStep = historyStep->previous;
	}
	while (stepsBackInHistory > 0 && steps)
	{
		steps--;
		stepsBackInHistory--;
		historyStep = historyStep->next;
	}
	currentText = copy_text(currentText, historyStep->text);
	currentLineCount = historyStep->lineCount;
}

int main()
{
	initialize_line(&currentText);
	initialize_history_entry(&history);
	make_history_entry();
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
			free_text(currentText);
			break;
		}
	}
	return 0;
}
