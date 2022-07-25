#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <string>
#include "node.h"


void ReadFile(std::string file_name, std::vector<std::vector<int>>& grid);
void create_linked_list(Node **point, std::vector<std::vector<int>> grid);
void print_elements(Node *start);
int search_2D_array(std::vector<std::vector<int>> grid, int num);
int search_linked_list(Node **start, int num);




int main(int argc, char* argv[]) 
{
    
    std::string fname = std::string(argv[1]);
    int search_num = std::stoi(std::string(argv[2]));
    
    std::vector<std::vector<int>> grid;
    ReadFile(fname, grid);
    
    Node *head = NULL;
    create_linked_list(&head, grid);
    
    std::cout << std::endl;
    
    print_elements(head);
    
    int array_num = search_2D_array(grid, search_num);
    int linked_num = search_linked_list(&head, search_num);
    
    std::cout << std::endl;
    std::cout << "2D array search: " << array_num << " / Linked List search: " << linked_num << std::endl;
    
    return 0;
}








void ReadFile(std::string file_name, std::vector<std::vector<int>>& grid) {
    
    std::ifstream input_file(file_name);

    
    std::vector<int> new_row;

   
    std::string temp_str;

    
    while (std::getline(input_file, temp_str)) {
        
        std::istringstream ss(temp_str);
        
        double token;

        
        while (ss >> token) {
           
            new_row.push_back(token);
        }
        
        grid.push_back(new_row);
        new_row.clear();
    }
}








void create_linked_list(Node **point, std::vector<std::vector<int>> grid)
{
   //double for loop to traverse the grid
   for(int i = 0; i < grid.size(); i++)
   {
       for(int j = 0; j < grid[0].size(); j++)
       {
           //to eliminate all zeros from the 2d vector
           if(grid[i][j] != 0)
           {
                Node *temp = *point;
                Node *r; 
                
                //if the linked-list is empty
                if (temp == NULL)
                {
                    temp = new Node();
                    temp->row = i;
                    temp->col = j;
                    temp->data = grid[i][j];
                    temp->next = NULL;
                    *point = temp;
                }
                
                //if there are values in the linked list
                else
                {
                    //to traverse to the end of the linked list
                    while (temp->next != NULL)  
                        temp = temp->next;
                         
                    r = new Node();
                    r->row = i;
                    r->col = j;
                    r->data = grid[i][j];
                    r->next = NULL;
                    temp->next = r;
                }
                
                
           }
       }
   }
}




void print_elements(Node *start)
{
     Node *ptr = start;
     
     //to show what each value represents in the linked list is
     //the first value is the row postion
     //the second value is the column postion
     //the third value is the data that the node is holding
     std::cout << "(row position, column position, value): ";
     while (ptr != NULL)
     {
         std::cout << ptr->row << ", " << ptr->col << ", " << ptr->data << " ---> ";
         ptr = ptr->next;
     }
     std::cout << "NULL" << std::endl;
}


int search_2D_array(std::vector<std::vector<int>> grid, int num)
{
    int count = 0;
    for(int i = 0; i < grid.size(); i++)
    {
        for(int j = 0; j < grid[0].size(); j++)
        {
            count++;
            if(grid[i][j] == num)
            {
                return count;
            }
        }
    }
    return count;
}

int search_linked_list(Node **start, int num)
{
    int count = 0;
    Node *ptr = *start;
    while (ptr->next != NULL || num != ptr->data)
    {
        count++;
        ptr = ptr->next; 
    }
    return count;
}