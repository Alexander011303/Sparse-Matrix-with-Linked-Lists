#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "node.h"

void ReadFile(std::string file_name, std::vector<std::vector<int>>& grid);
void create_linked_list(Node **point, std::vector<std::vector<int>> grid);
void print_elements(Node *start);
std::vector<std::vector<int>> multiply( std::vector<std::vector<int>> grid, int num);
std::vector<std::vector<int>> multiply( std::vector<std::vector<int>> grid1, std::vector<std::vector<int>> grid2);



int main(int argc, char* argv[]) 
{
    
    std::string fname = std::string(argv[1]);
    std::string fname2 = std::string(argv[2]);
    
    std::vector<std::vector<int>> grid;
    std::vector<std::vector<int>> grid2;
    ReadFile(fname, grid);
    ReadFile(fname2, grid2);
    
    //std::vector<std::vector<int>> grid = multiply(grid, 9);
    std::vector<std::vector<int>> newgrid = multiply(grid, grid2);
    
    Node *head = NULL;
    create_linked_list(&head, newgrid);
    
    
    print_elements(head);
    
    
    
    
    return 0;
}

std::vector<std::vector<int>> multiply( std::vector<std::vector<int>> grid, int num){
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[0].size(); j++){
            grid[i][j] *= num;
        }
    }
    
    return grid;
    
}

std::vector<std::vector<int>> multiply( std::vector<std::vector<int>> grid1, std::vector<std::vector<int>> grid2){
    int r1 = grid1.size();
    int c1 = grid1[0].size();
    int r2 = grid2.size();
    int c2 = grid2[0].size();
    
    std::vector<int> row (c2, 0);
    std::vector<std::vector<int>> r (r1, row);
    
    for (int i = 0; i < r1; i++) {
        for (int j = 0; j < c2; j++) {
 
            for (int k = 0; k < r2; k++) {
                r[i][j] += grid1[i][k] * grid2[k][j];
            }
        }
    }
    return r;
    
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
     std::cout << "(row position, column position, value) ";
     while (ptr != NULL)
     {
         std::cout << ptr->row << ", " << ptr->col << ", " << ptr->data << " ---> ";
         ptr = ptr->next;
     }
     std::cout << "NULL" << std::endl;
}