#include <iostream>

struct Link {
    int value;
    Link* next = nullptr;
};

size_t size(const Link* head) {
    int count = 0;
    const Link* curr = head;

    while (curr != nullptr) {
        count++;
        curr = curr->next;
    }
    return count;
}

size_t sum(const Link* head) {
    int sum = 0;
    const Link* curr = head;
    while (curr != nullptr) {
        sum += curr->value;
        curr = curr->next;
    }
    return sum;
}

void release(Link** phead) {
    if (*phead == nullptr) {
        return; //kończy działanie void release
    }
    Link* tmp = *phead;
    *phead = (*phead)->next;
    delete tmp;
    release(phead);
}

void reverse(Link** head) {
    if (*head == nullptr) {
        return; //kończy void reverse
    }
    Link* curr = *head;
    Link* prev = nullptr;
    Link* next = nullptr;
    while (curr != nullptr) {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    *head = prev;
}

void add(Link** phead, int val) {
    Link* n = new Link();
    n->value = val;
    n->next = *phead;
    *phead = n;
}


int main() {
    
    Link* n1 = new Link();
    Link* head = n1;
    n1->value = 9;
    add(&n1, 3);
    add(&n1, 1);
    add(&n1, 7);

    std::cout << "Lista: ";
    Link* curr = n1;
    while (curr != nullptr) {
        std::cout << curr->value << " ";
        curr = curr->next;
    }

    std::cout << std::endl << "Liczba elementów: " << size(n1) << std::endl;
    std::cout << "Suma wartości: " << sum(n1) << std::endl;


std::cout << "Lista po dodaniu elementów: ";
curr = n1;
while (curr != nullptr) {
    std::cout << curr->value << " ";
    curr = curr->next;
}
std::cout << std::endl;


    reverse(&n1);

    std::cout << "Lista po 'reverse': ";
    curr = n1;
    while (curr != nullptr) {
        std::cout << curr->value << " ";
        curr = curr->next;
    }
    std::cout << std::endl;

    release(&n1);
    std::cout << "Liczba elementów po 'release': " << size(n1) << std::endl;

    return 0;
}
