#include <iostream>
using namespace std;
template<class T>
struct node{
	T data;
	node* nxt;
	node* prv;
	node(T _data){
		data = _data;
	}
	void add(node* _prv){
		prv = _prv;
		nxt = _prv->nxt;
		nxt->prv = this;
		prv->nxt = this;
	}
};

template<class T>
struct list{
	node<T>* head;
	node<T>* tail;
	list(T h, T t){
		head = new node<T>(h);
		tail = new node<T>(t);
		head->nxt = tail;
		tail->prv = head;
	}
	void add(node<T>* a, T t){
		node<T>* b = new node<T>(t);
		b->add(a);
	}
	void print(){
		node<T>* temp = head;
		while(temp!=NULL){
			cout <<temp->data << endl;
			temp = temp->nxt;
		}
	}
};

int main(){
	list<int> l (-100,100);
	cout<<1<<endl;
	l.print();

	l.add(l.head,10);
	cout<<2<<endl;
	l.print();

	l.add(l.head,9);
	cout<<3<<endl;
	l.print();

	l.add((l.tail)->prv,8);
	cout<<4<<endl;
	l.print();

	return 0;
}