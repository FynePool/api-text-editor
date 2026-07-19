#include <stdio.h>
#include <stdlib.h>
//#include <cstring>

#include <string.h>


typedef struct data
{
	char **line;
	int total_lines;
} DATA;


int main()
{

	DATA *content = (DATA*) malloc(100* sizeof(DATA));//Total number of operations of c and d that can be performed on data
	for ( int i = 0 ; i < 100 ; i++ )
	{
		content[i].line = (char**) malloc(100*sizeof(char*));
		for ( int j = 0 ; j < 100 ; j++ )
		{
			content[i].line[j] = (char*) malloc(250*sizeof(char));
		}
	}

	int current_index = 0;
	int total_index = 0;

	char prev_opr = 'n';
	char input[20];
	char ignore[2];
	while ( 1 )
	{
		int start = 0;
		int end = 0;
		int total;
		char opr;
		fscanf(stdin,"%s",input);
		//fscanf(ptr,"%s",input);
		int started = 1;
		for ( int i = 0 ; i < 20 ; i++ )
		{
			if ( input[i] >= '0' && input[i] <= '9')
			{
				if ( started == 1 )
				{
					start = (start * 10) + ( input[i] - 48 );
				}
				else
				{
					end = (end * 10) + ( input[i] - 48 );
				}
			}
			else if ( input[i] == ',' )
			{
				started = 0;
			}
			else if ( input[i] >= 'a' && input[i] <= 'z' )
			{
				opr = input[i];
				break;
			}
		}
		total = end - start + 1;
		ignore[0] = fgetc(stdin);
		//ignore[0] = fgetc(ptr);

		//Reading the previous data into new index and changing it according to current operation
		if ( opr == 'c' )
		{
			content[current_index].total_lines = 1;
			if ( current_index > 0 && ( start != 0 || end != 0 ))
			{
				content[current_index].total_lines = content[current_index - 1].total_lines;
				for ( int i = 1 ; i <= content[current_index].total_lines ; i++ )
				{
					strcpy(content[current_index].line[i],content[current_index-1].line[i]);
				}
			}
		}
		//Delete operation implementation
		if ( opr == 'd' )
		{

			content[current_index].total_lines = 1;
			//Getting the previous lines into next array index
			if ( current_index > 0 && ( start != 0 || end != 0 ) )
			{
				content[current_index].total_lines = content[current_index - 1].total_lines;
				for ( int i = 1 , j = end + 1 ; j <= content[current_index].total_lines ; i++ , j++ )
				{
					strcpy(content[current_index].line[i],content[current_index-1].line[j]);
				}
				content[current_index].total_lines = content[current_index].total_lines - end;
			}
			else
			{
				content[current_index].total_lines = 0;
			}
			total_index = current_index;

		}
		//Current content
		if ( opr == 'c' )
		{
			//Reading the lines from files into new array
			while ( start <= end )
			{
				fgets(content[current_index].line[start], 250, stdin);
				//fgets(content[current_index].line[start], 250, ptr);
				++start;
			}

			//Checking if the value of end of added line is greater than curent value of total lines, then setting the value to this
			if ( content[current_index].total_lines < end )
			{
				content[current_index].total_lines = end;
			}

			//Ignoring the dot
			fgets(ignore, 2, stdin);
			//fgets(ignore, 2, ptr);

			total_index = current_index;
		}
		//Printing
		else if ( opr == 'p' )
		{
			for ( int i = 0 , start_line = 1 ; i < total ; i++ , start_line++ )
			{
				if ( start_line > content[current_index - 1].total_lines || start == 0)
				{
					printf(".\n");
				}
				else
				{
					printf("%s",content[current_index - 1].line[start]);
				}
				start++;
			}
		}
		else if ( opr == 'r' )
		{
			while ( current_index < total_index && start > 0 )
			{
				current_index++;
				start--;
			}
		}
		else if ( opr == 'u')
		{
			while ( current_index > 0  && start > 0 )
			{
				current_index--;
				start--;
			}
		}
		if ( opr == 'c' || opr == 'd' )
		{
			total_index++;
			current_index++;
		}
		else if ( opr == 'q' )
		{
			break;
		}
	}

	return 0;
}
