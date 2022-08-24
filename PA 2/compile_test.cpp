#include "array_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"
#include "array_list.h"
#include "doubly_linked_list.h"
#include "stack.h"
#include "queue.h"

int main() {
    {
        ArrayList<int> list;
        list.size();
        list.insert(0, 0);
        list.operator[](0) = 0;
        list.remove(0);
        
        ArrayList<ArrayList<int>> list_list;
        list_list.insert(0, list);
    }
    
    {
        ArrayList<char*> list;
        list.size();
        list.insert(0, new char[1]{'\0'});
        delete[] list[0];
        list.operator[](0) = new char[1]{'\0'};
        {
            ArrayList<char*> copy = list;
            copy.remove(0);
            copy = list;
        }
        delete[] list[0];
        list.remove(0);
    }
    
    {
        DoublyLinkedList<int> list;
        list.size();
        list.insert(0, 0);
        list.operator[](0) = 0;
        list.remove(0);
        
        DoublyLinkedList<DoublyLinkedList<int>> list_list;
        list_list.insert(0, list);
    }
    
    {
        DoublyLinkedList<char*> list;
        list.size();
        list.insert(0, new char[1]{'\0'});
        delete[] list[0];
        list.operator[](0) = new char[1]{'\0'};
        {
            DoublyLinkedList<char*> copy = list;
            copy.remove(0);
            copy = list;
        }
        delete[] list[0];
        list.remove(0);
    }
    
    {
        Stack<int> stack;
        stack.push(0);
        stack.top() = 0;
        stack.pop();
        
        Stack<Stack<int>> stack_stack;
        stack_stack.push(stack);
    }
    
    {
        Stack<char*> stack;
        stack.push(new char[1]{'\0'});
        delete[] stack.top();
        stack.top() = new char[1]{'\0'};
        {
            Stack<char*> copy = stack;
            copy.pop();
            copy = stack;
        }
        delete[] stack.top();
        stack.pop();
    }
    
    {
        Queue<int> queue;
        queue.enqueue(0);
        queue.front() = 0;
        queue.dequeue();
        
        Queue<Queue<int>> queue_queue;
        queue_queue.enqueue(queue);
    }
    
    {
        Queue<char*> queue;
        queue.enqueue(new char[1]{'\0'});
        delete[] queue.front();
        queue.front() = new char[1]{'\0'};
        {
            Queue<char*> copy = queue;
            copy.dequeue();
            copy = queue;
        }
        delete[] queue.front();
        queue.dequeue();
    }
    
    
}
