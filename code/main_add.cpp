#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include "node.h"

void ReadFile(std::string file_name, std::vector<std::vector<int>>& grid);
void create_linked_list(Node **point, std::vector<std::vector<int>> grid);
void print_elements(Node *start);

Node* add_matrix(Node* a, Node* b)
{
    // res will have the sum.
    Node* res = NULL;
    Node* tmpa = a;

    // Go over all the nodes in a that are also in b, and add them
    while (a) {
        Node* tmpb = b;
        double sum = a->data;
        bool found = false;
        while (tmpb) {
            if (tmpb->row == a->row && tmpb->col == a->col) {
                sum += tmpb->data;
                found = true;
                break;
            }
            tmpb = tmpb->next;
        }

        if (sum == 0) {
            a = a->next;
            continue;
        }

        Node* r = new Node();
        *r = *a;
        r->data = sum;

        r->next = res;
        res = r;
        a = a->next;
    }

    a = tmpa;

    // Go over all nodes in b that are not in a, copy
    // those b nodes into the sum.
    while (b) {
        Node* tmpa = a;
        bool found = false;
        while (tmpa) {
            if (tmpa->row == b->row && tmpa->col == b->col) {
                found = true;
                break;
            }
            tmpa = tmpa->next;
        }

        if (found) {
            b = b->next;
            continue;
        }

        Node* r = new Node();
        *r = *b;

        r->next = res;
        res = r;
        b = b->next;
    }

    return res;
}

int main(int argc, char* argv[])
{

    std::string fname = std::string(argv[1]);
    std::vector<std::vector<int>> grid;
    ReadFile(fname, grid);

    Node *head = NULL;
    create_linked_list(&head, grid);


    std::string fname2 = std::string(argv[2]);
    std::vector<std::vector<int>> grid2;
    ReadFile(fname2, grid2);
    Node* head2 = NULL;
    create_linked_list(&head2, grid2);


    print_elements(head);
    print_elements(head2);

    Node* sum = add_matrix(head, head2);
    print_elements(sum);

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
     std::cout << "(row position, column position, value) ";
     while (ptr != NULL)
     {
         std::cout << ptr->row << ", " << ptr->col << ", " << ptr->data << " ---> ";
         ptr = ptr->next;
     }
     std::cout << "NULL" << std::endl;
}
