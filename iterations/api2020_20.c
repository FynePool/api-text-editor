#include <stdio.h>
#include <stdlib.h>
//#include <cstring>

#include <string.h>


typedef struct data
{
	char **line;
	int total_lines;
	struct data *next;
} DATA;

//To store the previous state
typedef struct old
{
	char **line;
	int *index;
	char *changetype;
	int total_lines;
	struct old *next;
	struct old *previous;
}PREV_STATE;

int main()
{
	int line_size = 300000;
	int characters = 300;

	//Starting initialization
	DATA *content = (DATA*) malloc(sizeof(DATA)); //Total number of operations of c and d that can be performed on data
	content->line = (char**) malloc(line_size*sizeof(char*));
	for ( int i = 0 ; i < line_size ; i++ )
	{
		content->line[i] = NULL;
	}
	content->total_lines = 0;
	content->next = NULL;;
	int start_working = 0;


	PREV_STATE *state = NULL;
	//Read from file for previous testing
	/*FILE *ptr;

	ptr = fopen("change_1_input.txt","r+");

	if ( ptr == NULL )
	{
		printf("File didn't open\n");
		return -1;
	}*/
	while ( 1 )
	{
		char opr;
		int start = 0;
		int end = 0;

		int boolvar = 0;
		char c = 'a';

		//This is input
		while ( c != '\n' )
		{
			//c = getchar();
			c = fgetc(stdin);
			if ( c == ',')
			{
				boolvar = 1;
			}
			else if ( c >= '0' && c <= '9')
			{
				if( boolvar == 0 )
				{
					start = (start * 10) + ( c - 48 );
				}
				else
				{
					end = (end * 10) + ( c - 48 );
				}
			}
			else if ( c >= 'a' && c <= 'z' )
			{
				opr = c;
			}
		}

		int total = end - start + 1;
		int itr = start;

		if ( opr == 'c' )
		{
			//IF its second read
			// We check if there is data in prev state or not
			//if not we initialize it and store data
			if ( start_working == 1 && state == NULL)
			{
				state = (PREV_STATE*) malloc (sizeof(PREV_STATE));
				state->next = NULL;
				state->previous = NULL;

				state->total_lines = total;
				state->index = (int*) malloc(total * sizeof(int));
				state->changetype = (char*) malloc(total *sizeof(char));
				state->line = (char**) malloc(total * sizeof(char*));

				for ( int i = start , j = 0 ; i <= end ; i++  , j++)
				{
					//IF the data that is to be wrriten is new
					// we simply store its index
					if ( content->line[i] == NULL )
					{
						state->changetype[j] = 'N';
						state->line[j] = NULL;
					}
					//if the data written is overwriting
					else
					{
						state->changetype[j] = 'O';
						state->line[j] = (char*) malloc(characters*sizeof(char));
					}
					state->index[j] = i;
				}
			}
			else if ( start_working == 1 && state->next == NULL )
			{
				state->next = (PREV_STATE*) malloc (sizeof(PREV_STATE));
				state->next->next = NULL;
				state->next->previous = state;

				state->next->total_lines = total;
				state->next->index = (int*) malloc(total * sizeof(int));
				state->next->changetype = (char*) malloc(total *sizeof(char));
				state->next->line = (char**) malloc(total * sizeof(char*));

				for ( int i = start , j = 0 ; i <= end ; i++  , j++)
				{
					if ( content->line[i] == NULL )
					{
						state->next->changetype[j] = 'N';
						state->next->line[j] = NULL;
					}
					else
					{
						state->next->changetype[j] = 'O';
						state->next->line[j] = (char*) malloc(characters*sizeof(char));
					}
					state->next->index[j] = i;
				}
				state = state->next;
			}
		}
		if ( opr == 'd')
		{
			if ( start_working == 1 && state == NULL)
			{
				state = (PREV_STATE*) malloc (sizeof(PREV_STATE));
				state->next = NULL;
				state->previous = NULL;

				state->total_lines = total;
				state->index = (int*) malloc(total * sizeof(int));
				state->changetype = (char*) malloc(total *sizeof(char));
				state->line = (char**) malloc(total * sizeof(char*));

				for ( int i = start , j = 0 ; i <= end ; i++  , j++)
				{
					if ( content->line[i] == NULL )
					{
						state->changetype[j] = 'D';
						state->line[j] = NULL;
					}
					else
					{
						state->changetype[j] = 'D';
						state->line[j] = (char*) malloc(characters*sizeof(char));
					}
					state->index[j] = i;
				}
			}
			else if ( start_working == 1 && state->next == NULL )
			{
				state->next = (PREV_STATE*) malloc (sizeof(PREV_STATE));
				state->next->next = NULL;
				state->next->previous = state;

				state->next->total_lines = total;
				state->next->index = (int*) malloc(total * sizeof(int));
				state->next->changetype = (char*) malloc(total *sizeof(char));
				state->next->line = (char**) malloc(total * sizeof(char*));

				for ( int i = start , j = 0 ; i <= end ; i++  , j++)
				{
					if ( content->line[i] == NULL )
					{
						state->next->changetype[j] = 'D';
						state->next->line[j] = NULL;
					}
					else
					{
						state->next->changetype[j] = 'D';
						state->next->line[j] = (char*) malloc(characters*sizeof(char));
					}
					state->next->index[j] = i;
				}
				state = state->next;
			}
		}
		//Storing the line
		if ( opr == 'c' )
		{
			//printf("Taking input\n");
			//printf("Iterator %d\n",itr);
			int total_lin = total;
			while ( total_lin != 0 )
			{
				if ( itr >= 1 && itr <= line_size - 1 )
				{
					if ( content->line[itr] == NULL )
					{
						content->line[itr] = (char*) malloc(characters*sizeof(char));
					}
					//This is input line
					//if ( fgets(content->line[itr],characters - 1 ,ptr));
					if ( fgets(content->line[itr],characters - 1 ,stdin));
				}

				itr++;
				total_lin--;
			}
			if ( end > content->total_lines )
			{
				content->total_lines = end;
			}
			//This is input
			//c = getchar();
			//c = getchar();
			c = fgetc(stdin);
			c = fgetc(stdin);

			start_working = 1;
		}
		//Deleting the specificed lines
		if ( opr == 'd' )
		{
			for ( int i = start , j = end + 1; i <= end ; i++ , j++ )
			{
				if ( content->line[j] != NULL )
				{
					strcpy(content->line[i],content->line[j]);
				}
				else
				{
					if ( content->line[i] != NULL )
					{
						content->line[i] = NULL;
					}
				}
			}
			if ( content->total_lines >= 1 )
			{
				for ( int i = content->total_lines - total ; i <= content->total_lines ; i++ )
				{
					if ( i > 0 )
					{
						//freeing the memory of deleted line
						if ( content->line[i] != NULL )
						{
							free(content->line[i]);
							content->line[i] = NULL;
						}
					}
				}
				if ( content->total_lines - total >= 1 )
				{
					content->total_lines = content->total_lines - total;
				}
			}


		}

		if ( opr == 'p' )
		{
			for ( int i = start ; i <= end ; i++ )
			{
				if ( content->line[i] == NULL || content->line[i][0] == '\0' || i == 0 )
				{
					printf(".\n");
				}
				else
				{
					printf("%s",content->line[i]);
				}
			}
		}

		if ( opr == 'q' )
		{
			break;
		}
	}
	//Freeing the memory
	while ( state != NULL )
	{
		PREV_STATE *temp = state;
		//printf("Here %d\n",temp->total_lines);
		for ( int i = 0 ; i < temp->total_lines ; i++ )
		{
			if ( temp->line[i] != NULL)
			{
				free(temp->line[i]);
			}
		}
		state = state->previous;
		free(temp->changetype);
		free(temp->index);
		free(temp);
	}
	for ( int j = 0 ; j < line_size ; j++ )
	{
		if ( content->line[j] != NULL )
		{
			free(content->line[j]);
		}

	}
	free(content->line);
	free(content);
	return 0;
}
