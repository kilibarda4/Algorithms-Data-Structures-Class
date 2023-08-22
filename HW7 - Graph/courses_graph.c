#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdbool.h>
//Nebojsa Kilibarda
//Topological Sort algorithm used for a list of courses

#define MAX_COURSE_LEN 31
#define MAX_LINE_LEN 1001
#define MAX_FILE_LEN 31
#define MAX_NUM_COURSES 101
#define WHITE 0
#define GREY 1
#define BLACK 2

struct struct_graph{
    int vertices;
    int **edges; //matrix representation
};
typedef struct struct_graph* graphPT;

void DFS_visit(graphPT g, int u, int* color, int* predecessor, int* result, int* num_black);
int get_index(char* str, char courses[MAX_NUM_COURSES][MAX_COURSE_LEN], int num_courses);
void print_adjacency_matrix(graphPT graph);
int** array_allocate(int rows_and_cols);
void free_array(graphPT graph);
int* DFS(graphPT g);

int main()
{
    char filename[MAX_FILE_LEN];
    char line[MAX_LINE_LEN];
    char courses[MAX_NUM_COURSES][MAX_COURSE_LEN];
    char c;
    char* token;
    int number_of_courses = 0;
    int prerequisite_course = 0;
    int i = 0;

    printf("This program will create a topologically ordered list ");
    printf("of courses based on their prerequisites.\n");
    printf("Enter filename: ");
    scanf("%s%c", filename, &c);

    FILE* fp = fopen(filename, "r");
    if(!fp)
    {
        printf("File I/O error.\n");
        return 1;
    }

    while(fgets(line, MAX_LINE_LEN, fp))
    {
        number_of_courses++;
        token = strtok(line, " \n");
        strcpy(courses[i], token);
        printf("Vertex %d, %s\n", i, courses[i]);
        i++;
    }

    graphPT graph = malloc(sizeof(struct struct_graph));
    graph->vertices = number_of_courses;
    graph->edges = array_allocate(graph->vertices);

    fseek(fp, 0L, SEEK_SET); //go back to the beginning of the file

    i = 0;
    while (fgets(line, MAX_LINE_LEN, fp)) 
    {
        //if the first tokenization matches an entry in courses
        //it means there's no prerequisites for that course
        //otherwise add it to the matrix
        token = strtok(line, "\n");
        if (strcmp(token, courses[i])) //note: there is no ! so comparing for inequality
        {
            token = strtok(line, " ");
            while (token) 
            {
                token = strtok(NULL, " \n");
                if( token )
                {
                    prerequisite_course = get_index(token, courses, number_of_courses);
                    if( prerequisite_course != -1 )
                    {
                    graph->edges[prerequisite_course][i] = 1;
                    }
                }
            }
        } 
        i++;
    }

    print_adjacency_matrix(graph);
    int* result_array = DFS(graph);

    printf("Order in which to take courses:\n");
    for (int i = 0; i < graph->vertices; i++)
    {
        printf("%d. - %s (corresponds to vertex %d)\n", i+1, courses[result_array[i]], result_array[i]);
    }

    free_array(graph);
    free(result_array);
    fclose(fp);
}

void DFS_visit(graphPT graph, int u, int* color, int* predecessor, int* result, int* num_black)
{
    // Set color of vertex u to gray to mark it as discovered
    color[u] = GREY;

    for (int i = 0; i < graph->vertices; i++)
    {
        if(graph->edges[u][i] && color[i] == WHITE)
        {
            predecessor[i] = u;
            DFS_visit( graph, i, color, predecessor, result, num_black);
        }
        else if(graph->edges[u][i] && color[i] == GREY)
        {
            printf("At least one cycle was detected. ");
            printf("There is no possible ordering.\n");
            return;
        }
    }
    color[u] = BLACK;
    ( *num_black )++; //puts the results in desired order
    result[graph->vertices - *num_black] = u;
}

//Depth first search
//returns the result array that gets updated in DFS_Visit
//in desired order
int* DFS(graphPT graph)
{
    // arrays to store the color, predecessor of each array
    // and a result array
    int* color = (int*) calloc(graph->vertices, sizeof(int));
    int* predecessor = (int*) calloc(graph->vertices, sizeof(int));
    int* result = calloc(graph->vertices, sizeof(int));
    int num_black = 0;

    for (int i = 0; i < graph->vertices; i++)
    {
        color[i] = WHITE;  // Initialize all vertices to white
        predecessor[i] = -1;
    }
    // Visit all vertices in the graph that are still undiscovered
    for (int u = 0; u < graph->vertices; u++) 
    {
        if ( color[u] == WHITE ) 
        {
            DFS_visit( graph, u, color, predecessor, result, &num_black);
        }
    }
    free( color );
    free( predecessor );
    return result;
}

//retrieve index of courses array that matches current token
//or say it was not possible and return -1
int get_index(char* file_token, char courses[MAX_NUM_COURSES][MAX_COURSE_LEN], int num_courses)
{
    for(int i = 0; i < num_courses; i++)
    {
        if(!strcmp(courses[i], file_token))
        {
            return i;
        }
    }
    printf("Could not locate index\n");
    return -1;
}

int** array_allocate(int rows_and_cols) 
{
  int** array_ptr = (int**) calloc( rows_and_cols, sizeof(int*) );
  for(int i = 0; i < rows_and_cols; i++) 
  {
    array_ptr[i] = (int*) calloc( rows_and_cols, sizeof(int) );
  }
  return array_ptr;
}

void free_array(graphPT graph)
{
    for(int i = 0; i < graph->vertices; i++)
    {
        free( graph->edges[i] );
    }
    free( graph->edges );
    free( graph );
}

void print_adjacency_matrix(graphPT graph)
{
    printf("   |");
    int i;
    for(i = 0; i < graph->vertices; i++)
    {
        printf("%3d|", i);
    }
    printf("\n");

    int number_of_dashes = graph->vertices*4 + 4;
    for(i = 0; i < number_of_dashes; i++)
    {
        printf("-");
    }
    printf("\n");
    for(i = 0; i < graph->vertices; i++)
    {
        printf("%3d|", i);
        for(int j = 0; j < graph->vertices; j++)
        {
            printf("%3d|", graph->edges[i][j]);
        }
        printf("\n");
    }
}