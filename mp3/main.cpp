#include "List.h"
#include <iostream>

using namespace std;

int main() {
	List<int> l;
	List<int>::ListNode* ptr[10];
	for(int i = 0; i < 10; i++) {
		l.insertBack(-i + 10);
		ptrs[i] = l.tail_;
	}
	l.sort();
	for(int i = 0; i <10; i++) {
		cout << (ptrs[i]->prev ? ptrs[i]->prev->data : -1) << " " << ptrs[i]->data << " " << (ptrs[i]->next ? ptrs[i]->next->data : -1) << endl;
	}
	cout << l<<endl;
}
