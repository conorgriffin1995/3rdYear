#include <iostream>
#include <string>

using namespace std;

struct ListNode {
	string item;
	int count;
	ListNode* next;
};
typedef ListNode* ListNodePtr;

int main() {
	ListNodePtr head;
	head = new ListNode;
	head->item = "Wilbur's brother Orville";
	head->count = 12;
	cout << head->item << " : " << head->count << endl;;


	system("pause");
}