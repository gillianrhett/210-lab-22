
#include <iostream>
using namespace std;
const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
    private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;
    
    public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }
    
    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return; // Empty list
        
        Node* temp = head;
        while (temp && temp->data != value) // traverse the list until value found or end
            temp = temp->next;
        
        if (!temp) return; // Value not found
        
        if (temp->prev) { // if temp isn't the head
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }
        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) return;
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    void pop_front() {
        if (head) {
            Node* newHead = head->next;
            newHead->prev = nullptr;
            delete head;
            head = newHead;
        }
        else
            cout << "The list is already empty." << endl;
    }

    void pop_back() {
        if(tail) {
            Node* newTail = tail->prev;
            newTail->next = nullptr;
            delete tail;
            tail = newTail;
        }
        else
            cout << "The list is already empty." << endl;
    }

    void delete_pos(int pos) { // delete the item at index #pos; head is 0
        if (pos < 0) {
            cout << "Invalid index." << endl;
            return;
        }
        if (!head) { 
            cout << "The list is already empty." << endl; 
        }
        else { // the list is not empty
            if (pos == 0) { // special case: delete the head
                pop_front();
            }
            else { // the item to delete is not the head
                Node* current = head;
                int i = 0;
                while (current && i < pos) {
                    current = current->next;
                    i++;
                }
                if (!current->next) { // we have reached the end of the list
                    if (i != pos) // the chosen position is greater than the last index
                        cout << "Invalid index." << endl;
                    else { // we are at the last item
                        pop_back();
                    }
                }
                else { // the item to delete is in the middle
                    Node* predecessor = current->prev;
                    Node* successor = current->next;
                    predecessor->next = successor;
                    successor->prev = predecessor;
                    delete current;
                }
            }
        }
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
DoublyLinkedList list;
    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR-MIN_NR+1) + MIN_NR);
    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();
    
    // I added this code to demo my new functions
    cout << "Deleting the 4th item (index 3)..." << endl;
    list.delete_pos(3);
    cout << "List forward: ";
    list.print();
    cout << "Deleting the head (uses pop_front)..." << endl;
    list.delete_pos(0);
    cout << "List forward: ";
    list.print();
    cout << "Deleting the tail (uses pop_back)..." << endl;
    list.delete_pos(size - 3); // tail's index is size - 3 because I deleted 2 items
    cout << "List forward: ";
    list.print();
    
    // original code:
    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: ";
    list.print();
    return 0;
}
