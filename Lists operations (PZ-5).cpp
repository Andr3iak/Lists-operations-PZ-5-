#include <iostream>
#include <string>

using namespace std;


struct number {
    int set;
    number* next;
};
number* create_head() {
    number* head1 = new number;
    head1->next = nullptr;
    head1->set = 0;
    return head1;
};

void number_add(const string a, number* head) {

    int len = a.length();
    number* last_node = head;

    for (int i = len; i > 0; i -= 9) {
        int start = max(0, i - 9);
        number* part = new number;
        part->set = stoul(a.substr(start, i - start));
        part->next = nullptr;

        last_node->next = part; // добавляю части в начало, получается список младшие разряды -> старшие
        last_node = part;
    }
}


void print_number_list(number* head) {
    number* temp = head->next;
    int count = 0;
    while (temp != nullptr) {
        cout << "[" << temp->set << "] ";
        temp = temp->next;
        count++;
    }
    cout << "\nParts: " << count << "\n\n";
}



void adding(number* head_a, number* head_b, number* head_adding) {

    number* temp_a = head_a->next;
    number* temp_b = head_b->next;

    int d = 0, pow9 = 10*10*10*10*10*10*10*10*10;

    while ((temp_a != nullptr) and (temp_b != nullptr)) {
        number* temp_adding = new number;
        temp_adding->set = temp_a->set + temp_b->set + d;
        temp_adding->next = head_adding->next;
        head_adding->next = temp_adding;
        d = 0;
        if (temp_adding->set >= pow9) {
            d = temp_adding->set / pow9;
            temp_adding->set %= pow9;
        }
        temp_a = temp_a->next;
        temp_b = temp_b->next;
    }
    
    if ((temp_a == nullptr) and (temp_b != nullptr)) {
        while (temp_b != nullptr) {
            number* temp_adding = new number;
            temp_adding->set = temp_b->set + d;
            d = 0;
            if (temp_adding->set >= pow9) {
                d = temp_adding->set / pow9;
                temp_adding->set %= pow9;
            }
            temp_adding->next = head_adding->next;
            head_adding->next = temp_adding;
            temp_b = temp_b->next;
        }
        if (d != 0) {
            number* temp_adding = new number;
            temp_adding->set = d;
            temp_adding->next = head_adding->next;
            head_adding->next = temp_adding;

        }
        
    }
    else if ((temp_b == nullptr) and (temp_a != nullptr)) {
        while (temp_a != nullptr) {
            number* temp_adding = new number;
            temp_adding->set = temp_a->set+d;
            d = 0;
            if (temp_adding->set >= pow9) {
                d = temp_adding->set / pow9;
                temp_adding->set %= pow9;
            }
            temp_adding->next = head_adding->next;
            head_adding->next = temp_adding;
            temp_a = temp_a->next;
        }
        if (d != 0) {
            number* temp_adding = new number;
            temp_adding->set = d;
            temp_adding->next = head_adding->next;
            head_adding->next = temp_adding;
        }
    }
    number* temp = head_adding->next;
    cout << "Result number: ";
    while (temp != nullptr) {
        cout << temp->set;
        temp = temp->next;
    }
    cout << endl;
}

int main()
{

    string a = "1";
    string b = "9999999";

    cout << "Numbers: a: " << a << "\tb: " << b << "\n\n";

    number* head_a = create_head();
    number* head_b = create_head();

    number_add(a, head_a);
    number_add(b, head_b);

    //print_number_list(head_a);
    //print_number_list(head_b);

    number* head_adding = create_head();
    adding(head_a, head_b, head_adding);
    print_number_list(head_adding);


    return 0;
}