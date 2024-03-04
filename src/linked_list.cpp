#include <iostream>
using namespace std;

// Defines an object that can be linked to others of the same type
template <class T>
class Linkable {
	public:
		T *next;
		virtual ~Linkable() {}
		virtual void link(T *node) = 0;
};


// A Node with an integer value
class Node {
	public:
		int value;

		// Constructor
		Node(int val) {
			value = val;
		}

		// Print a node's value to std::cout
		void print() {
			cout << value << "\n";
		}
};

/** 
 * T must extend Linkable and Node 
 */
template <class T> class List {
	protected:
		// This allows for implementations to have different behavior 
		// when creating a node.
		virtual T *create_node(int value) = 0;

	public:
		// First element of the list
		T *head;

		// Destructor
		virtual ~List() {
			T *prev = head;
			T *curr = head->next;
			while(curr) {
				delete prev;
				prev = curr;
				curr = prev->next;
			}
			delete prev; // Free the last remaining node
		}

		// Adds an element to the end of the list
		void enqueue(int value) {
			// Create a new node using our protected created_node() method
			T *n = create_node(value);

			// If the list is empty, set the head to the new node
			if(head == nullptr) {
				head = n;
				return;
			}

			// Otherwise traverse the nodes until we reach the end of the list
			// Maintain a pointer to the current node
			// and the next node
			T *curr = head;
			T *next = head->next;
			while(next) {
				// Move to the next node
				curr = curr->next;
				// Peek the next node; if curr->next is a nullptr
				// this loop will exit
				next = curr->next;
			}

			// Curr is the last element of the list, so we link our new node here
			curr->link(n);
		};

		// Prints the value of each node to std::cout
		void print() {
			T *curr = head;
			while(curr) {
				cout << curr->value << " ";
				curr = curr->next;
			}
			cout << "\n";
		};
};


// A node that is linkable in one direction
class SLNode : public Node, public Linkable<SLNode> {
	public:
		SLNode(int val) : Node(val) {
			value = val;
		}
		void link(SLNode *node) {
			next = node;
		};
};

// A singly-linked list
class SList : public List<SLNode> {
	protected:
		SLNode *create_node(int val) {
			return new SLNode(val);
		}
};

// A node that is linkable bi-directionally
class DLNode : public Node, public Linkable<DLNode> {
	protected:
		DLNode *prev;
	public:
		DLNode(int val): Node(val) {
			value = val;
		}

		void link(DLNode *_next) {
			next = _next;
			_next->prev = this;
		}

		DLNode *get_prev() {
			return prev;
		}
};

// A doubly-linked list
class DList : public List<DLNode> {
	protected:
		DLNode *create_node(int val) {
			return new DLNode(val);
		}
};

int main() {
	SList *s_list = new SList();
	DList *d_list = new DList();

	for(int i = 1; i <= 5; i++) {
			s_list->enqueue(i);
			d_list->enqueue(i);
	}

	cout << "Singly Linked List:" << "\n";
	s_list->print();
	cout << "Doubly Linked List:" << "\n";
	d_list->print();

	cout << "Traverse our DLL forward and backwards:" << "\n";
	DLNode *curr = d_list->head;
	DLNode *next = d_list->head->next;

	while(next) {
		cout << curr->value << " ";
		curr = next;
		next = curr->next;
	}

	while(curr) {
		cout << curr->value << " ";
		curr = curr->get_prev();
	}
	cout << "\n";

	delete s_list;
	delete d_list;

	return 0;
}
