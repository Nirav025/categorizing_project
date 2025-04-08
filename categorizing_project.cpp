#include <iostream>
using namespace std;

// Node structure for Linked List
struct Node {
    int data;
    Node* next;
};

// Linked List class
class LinkedList {
    Node* head;

    // Helper functions for merge sort
    Node* mergeSort(Node* head);
    Node* merge(Node* left, Node* right);

public:
    LinkedList() { head = NULL; }

    void insert(int val);
    void display();
    void sortList(); // Merge sort
    void binarySearch(int val);

    Node* getHead() { return head; }
    void setHead(Node* newHead) { head = newHead; }
};

// Insert at end
void LinkedList::insert(int val) {
    Node* newNode = new Node{val, NULL};
    if (!head) {
        head = newNode;
    } else {
        Node* temp = head;
        while (temp->next)
            temp = temp->next;
        temp->next = newNode;
    }
}

// Display list
void LinkedList::display() {
    if (!head) {
        cout << "List is empty.\n";
        return;
    }
    Node* temp = head;
    cout << "Linked List: ";
    while (temp) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

// Merge two sorted lists
Node* LinkedList::merge(Node* a, Node* b) {
    if (!a) return b;
    if (!b) return a;

    Node* result = NULL;

    if (a->data <= b->data) {
        result = a;
        result->next = merge(a->next, b);
    } else {
        result = b;
        result->next = merge(a, b->next);
    }
    return result;
}

// Merge sort
Node* LinkedList::mergeSort(Node* h) {
    if (!h || !h->next)
        return h;

    // Find the middle
    Node* slow = h;
    Node* fast = h->next;

    while (fast && fast->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* mid = slow->next;
    slow->next = NULL;

    Node* left = mergeSort(h);
    Node* right = mergeSort(mid);

    return merge(left, right);
}

// Sort list using Merge Sort
void LinkedList::sortList() {
    head = mergeSort(head);
    cout << "List sorted using Merge Sort.\n";
}

// Binary Search in Linked List (by copying to array)
void LinkedList::binarySearch(int val) {
    int arr[100], n = 0;
    Node* temp = head;
    while (temp) {
        arr[n++] = temp->data;
        temp = temp->next;
    }

    int low = 0, high = n - 1, mid;
    bool found = false;

    while (low <= high) {
        mid = (low + high) / 2;
        if (arr[mid] == val) {
            found = true;
            break;
        } else if (arr[mid] < val) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    if (found)
        cout << val << " found in the list.\n";
    else
        cout << val << " not found in the list.\n";
}

// Main Program (Menu)
int main() {
    LinkedList list;
    int choice, val;

    do {
        cout << "\n======== MENU ========\n";
        cout << "1. Insert element into Linked List\n";
        cout << "2. Display Linked List\n";
        cout << "3. Sort using Merge Sort\n";
        cout << "4. Binary Search\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter value: ";
                cin >> val;
                list.insert(val);
                break;

            case 2:
                list.display();
                break;

            case 3:
                list.sortList();
                break;

            case 4:
                cout << "Enter value to search: ";
                cin >> val;
                list.binarySearch(val);
                break;

            case 5:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }

    } while (choice != 5);

    return 0;
}
