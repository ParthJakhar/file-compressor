#include <iostream>
#include <fstream>
#include <stack>
#include <string>
using namespace std;

class Node {
public:
    string data;
    Node* next;

    Node(string data) {
        this->data = data;
        this->next = NULL;
    }
};

void display(Node*);

class Editor {
public:
    void add_line(Node* &root) {
        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        if (root == NULL) {
            root = new Node(line);
            return;
        }

        Node* root_ref = root;
        while (root_ref->next != NULL) {
            root_ref = root_ref->next;
        }

        Node* temp = new Node(line);
        root_ref->next = temp;
    }

    void add_line_at(Node* &root) {
        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        int line_no;
        cout << "Enter index to insert at: ";
        cin >> line_no;
        cin.ignore();

        Node* temp = new Node(line);

        if (line_no == 1) {
            temp->next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;
        for (int i = 1; i < line_no - 1; i++) {
            root_ref = root_ref->next;
        }

        temp->next = root_ref->next;
        root_ref->next = temp;
    }

    void add_line_at(Node* &root, int line_no) {
        string line;
        cout << "Enter the line to insert:" << endl;
        getline(cin, line, '\n');

        Node* temp = new Node(line);

        if (line_no == 1) {
            temp->next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;
        for (int i = 1; i < line_no - 1; i++) {
            root_ref = root_ref->next;
        }

        temp->next = root_ref->next;
        root_ref->next = temp;
    }

    void add_line_at(Node* &root, int line_no, string line) {
        Node* temp = new Node(line);

        if (line_no == 1) {
            temp->next = root;
            root = temp;
            return;
        }

        Node* root_ref = root;
        for (int i = 1; i < line_no - 1; i++) {
            root_ref = root_ref->next;
        }

        temp->next = root_ref->next;
        root_ref->next = temp;
    }

    void replace_line(Node* &root) {
        int line_no;
        cout << "Enter the line number to replace: ";
        cin >> line_no;
        cin.ignore();

        delete_line(root, line_no);
        add_line_at(root, line_no);
    }

    void interchange_lines(Node* &root) {
        int index1, index2;
        cout << "Enter the index for line 1: ";
        cin >> index1;
        cout << "Enter the index for line 2: ";
        cin >> index2;

        Node* root_ref = root;
        for (int i = 1; i < index1; i++) {
            root_ref = root_ref->next;
        }
        string line1 = root_ref->data;

        root_ref = root;
        for (int i = 1; i < index2; i++) {
            root_ref = root_ref->next;
        }
        string line2 = root_ref->data;

        add_line_at(root, index1, line2);
        delete_line(root, index1 + 1);
        add_line_at(root, index2, line1);
        delete_line(root, index2 + 1);
    }

    void delete_line(Node* &root) {
        int line_no;
        cout << "Enter line number to delete: ";
        cin >> line_no;

        if (line_no == 1) {
            Node* temp = root;
            root = root->next;
            delete temp;
            return;
        }

        Node* root_ref = root;
        for (int i = 1; i < line_no - 1; i++) {
            root_ref = root_ref->next;
        }

        Node* temp = root_ref->next;
        root_ref->next = temp->next;
        delete temp;
    }

    void delete_line(Node* &root, int line_no) {
        if (line_no == 1) {
            Node* temp = root;
            root = root->next;
            delete temp;
            return;
        }

        Node* root_ref = root;
        for (int i = 1; i < line_no - 1; i++) {
            root_ref = root_ref->next;
        }

        Node* temp = root_ref->next;
        root_ref->next = temp->next;
        delete temp;
    }

    void open_file(Node* &root) {
        ifstream file("sample.txt");
        if (!file) {
            cout << "File couldn't open successfully." << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (root == NULL) {
                root = new Node(line);
                continue;
            }
            Node* root_ref = root;
            while (root_ref->next != NULL) {
                root_ref = root_ref->next;
            }
            Node* temp = new Node(line);
            root_ref->next = temp;
        }
        file.close();
        cout << "File opened successfully." << endl;
    }

    void save_file(Node* &root) {
        ofstream file("input.txt");

        Node* root_ref = root;
        while (root_ref != NULL) {
            file << root_ref->data << endl;
            root_ref = root_ref->next;
        }
        cout << "File saved successfully." << endl;
        file.close();
    }

    void push_root(Node* root, stack<Node*> &st) {
        Node* head = NULL;
        while (root != NULL) {
            if (head == NULL) {
                head = new Node(root->data);
                root = root->next;
                continue;
            }

            Node* head_ref = head;
            while (head_ref->next != NULL) {
                head_ref = head_ref->next;
            }
            Node* temp = new Node(root->data);
            head_ref->next = temp;
            root = root->next;
        }
        st.push(head);
    }

    void undo(Node* &root, stack<Node*> &st) {
        if (st.size() > 1) {
            st.pop();
            root = st.top();
        } else {
            cout << "\nUNDO unavailable..." << endl;
        }
    }

    void display(Node* root) {
        cout << "Current text:" << endl;
        int i = 0;
        while (root != NULL) {
            cout << ++i << "> " << root->data << endl;
            root = root->next;
        }
        cout << endl;
    }

    void search_word(Node* root) {
  string word;
  cout << "Enter the word to search: ";
  cin >> word;

  int line_no = 1;
  bool found = false;
  while (root != NULL) {
    if (root->data.find(word) != string::npos) {
      cout << "Word found at line " << line_no << ":" << endl;
      cout << root->data << endl; // Print the entire line
      found = true;
    }
    root = root->next;
    line_no++;
  }

  if (!found) {
    cout << "Word not found in any line." << endl;
  }
} 
    void begin(Node* &root) {
        open_file(root);

        stack<Node*> st;
        push_root(root, st);

        int select;
        while (1) {
            cout << "Enter your Selection:" << endl;
            cout << "1. Insert line" << endl;
            cout << "2. Insert line at index" << endl;
            cout << "3. Replace a line" << endl;
            cout << "4. Interchange two lines" << endl;
            cout << "5. Delete line" << endl;
            cout << "6. UNDO" << endl;
            cout << "7. Display text file" << endl;
            cout << "8. Save File" << endl;
            cout << "9. Search for a word" << endl;
            cout << "-1. Exit" << endl;
            cout << ">> ";

            cin >> select;
            cin.ignore();

            switch (select) {
                case 1:
                    add_line(root);
                    push_root(root, st);
                    break;
                case 2:
                    add_line_at(root);
                    push_root(root, st);
                    break;
                case 3:
                    replace_line(root);
                    break;
                case 4:
                    interchange_lines(root);
                    break;
                case 5:
                    delete_line(root);
                    break;
                case 6:
                    undo(root, st);
                    break;
                case 7:
                    display(root);
                    break;
                case 8:
                    save_file(root);
                    break;
                case 9:
                    search_word(root);
                    break;
                case -1:
                    cout << "Editor exited...";
                    return;
            }
        }
    }
};

int main() {
    Node* root = NULL;
    Editor a;
    a.begin(root);
    return 0;
}
