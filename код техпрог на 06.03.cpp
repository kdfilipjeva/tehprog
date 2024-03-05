#include <iostream>
#include <vector>

class Node {
public:
    int data;
    Node* next;
};

class LinkedList {
public:
    Node* head;
    LinkedList() : head(nullptr) {}

    void addAtBeginning(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = head;
        head = newNode;
    }

    void addAtIndex(int index, int data) {
        Node* newNode = new Node();
        newNode->data = data;
        if (index == 0) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* temp = head;
            for (int i = 0; i < index - 1; i++) {
                if (temp != nullptr) {
                    temp = temp->next;
                }
            }
            if (temp != nullptr) {
                newNode->next = temp->next;
                temp->next = newNode;
            }
        }
    }

    void addAtEnd(int data) {
        Node* newNode = new Node();
        newNode->data = data;
        newNode->next = nullptr;
        if (head == nullptr) {
            head = newNode;
        } else {
            Node* temp = head;
            while (temp->next != nullptr) {
                temp = temp->next;
            }
            temp->next = newNode;
        }
    }

    void deleteFirst() {
        if (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void deleteLast() {
        if (head != nullptr) {
            if (head->next == nullptr) {
                delete head;
                head = nullptr;
            } else {
                Node* secondLast = head;
                while (secondLast->next->next != nullptr) {
                    secondLast = secondLast->next;
                }
                delete secondLast->next;
                secondLast->next = nullptr;
            }
        }
    }

    void deleteAtIndex(int index) {
        if (index == 0) {
            deleteFirst();
        } else {
            Node* temp = head;
            for (int i = 0; i < index - 1; i++) {
                if (temp != nullptr) {
                    temp = temp->next;
                }
            }
            if (temp != nullptr && temp->next != nullptr) {
                Node* toDelete = temp->next;
                temp->next = temp->next->next;
                delete toDelete;
            }
        }
    }

    void updateAtIndex(int index, int data) {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            if (temp != nullptr) {
                temp = temp->next;
            }
        }
        if (temp != nullptr) {
            temp->data = data;
        }
    }

    int findAtIndex(int index) {
        Node* temp = head;
        for (int i = 0; i < index; i++) {
            if (temp != nullptr) {
                temp = temp->next;
            }
        }
        if (temp != nullptr) {
            return temp->data;
        }
        return -1;
    }

    void printList() {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }
};

int main() {
	setlocale(LC_ALL, "Russian");
    LinkedList list;
    int data, index, choice, size;

    std::cout << "������� ���������� ��������� � ������: ";
    std::cin >> size;
    std::cout << "������� �������� ������:\n";
    for (int i = 0; i < size; i++) {
        std::cin >> data;
        list.addAtEnd(data);
    }

    do {
        std::cout << "\n�������� ��������:\n";
        std::cout << "1. �������� ������� � ������\n";
        std::cout << "2. �������� ������� �� �������\n";
        std::cout << "3. �������� ������� � �����\n";
        std::cout << "4. ������� ������ �������\n";
        std::cout << "5. ������� ��������� �������\n";
        std::cout << "6. ������� ������� �� �������\n";
        std::cout << "7. �������� ������� �� �������\n";
        std::cout << "8. ����� ������� �� �������\n";
        std::cout << "9. ������� ������\n";
        std::cout << "0. �����\n";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "������� �������: ";
            std::cin >> data;
            list.addAtBeginning(data);
            break;
        case 2:
            std::cout << "������� ������ � �������: ";
            std::cin >> index >> data;
            list.addAtIndex(index, data);
            break;
        case 3:
            std::cout << "������� �������: ";
            std::cin >> data;
            list.addAtEnd(data);
            break;
        case 4:
            list.deleteFirst();
            break;
        case 5:
            list.deleteLast();
            break;
        case 6:
            std::cout << "������� ������: ";
            std::cin >> index;
            list.deleteAtIndex(index);
            break;
        case 7:
            std::cout << "������� ������ � ����� �������: ";
            std::cin >> index >> data;
            list.updateAtIndex(index, data);
            break;
        case 8:
            std::cout << "������� ������: ";
            std::cin >> index;
            std::cout << "������� �� ������� " << index << ": " << list.findAtIndex(index) << std::endl;
            break;
        case 9:
            list.printList();
            break;
        }

        if (choice != 0 && choice != 8 && choice != 9) {
            std::cout << "������������� ���������: ";
            list.printList();
        }
    } while (choice != 0);

    return 0;
}

