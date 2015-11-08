#include <iostream>
using namespace std;

struct node{
	char c;
	node* next[26];
	node(char _c = '#'){
		c = _c;
	}
};

struct trie{
	node* head;
	
	trie(){
		head = new node();
	}

	void add(string s){
		node* cur = head;
		for(int i=0;i<s.length();i++){
			if(cur->next[s[i]-'a'] == NULL) cur->next[s[i]-'a'] = new node(s[i]);
			cur = cur->next[s[i]-'a'];
		}
	}

	void print(){
		node* q[100]; int qs=0,qe=1;
		q[0] = head;
		while(qs<qe){
			cout << qs << " " << q[qs]->c << endl;
			for(int i=0;i<26;i++){
				if(q[qs]->next[i] != NULL) q[qe++] = q[qs]->next[i];
			}
			qs++;
		}
	}
};

int main(){
	trie t;
	t.add("hello");
	t.add("helli");
	t.add("a");
	t.print();
}