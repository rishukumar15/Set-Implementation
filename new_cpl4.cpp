#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Node { 
public: 
    string data; 
    Node* next; 
}; 

typedef struct hash_tag
{
	bool exist;
	Node* head; 
}hash;

typedef struct set_tag
{
	hash hash1[113];
	int  size;
}set;

set create()
{
	set s1;
	s1.size=0;
	int i;
	for(i=0;i<113;i++)
	{
		s1.hash1[i].exist = false;
		s1.hash1[i].head = NULL;
	}
	return s1;
}

bool is_empty(set T)
{
	if(T.size==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool is_element_of(string s,set T)
{
	bool retval;
	int sum=0,i,d;
	for(i=0;i<s.size();i++)
	{
		sum += (int)s[i];
	}
	d= sum%113;
	if(is_empty(T))
	{
		retval = false;

	}
	else
	{
		if(!(T.hash1[d].exist))
		{
			retval = false;
		}
		else
		{
			int f=0;
			Node* ptr;
			ptr = T.hash1[d].head;
			while(ptr!= NULL && f==0)
			{
				if(ptr->data == s)
				{
					f=1;
				}
				ptr = ptr->next;
			}
			if(f==1)
			{
				retval = true;	
			} 
			else
			{
				retval = false;
			}
		}
	}
	return retval;
}

void add(set* S,string x)
{
	set s1;
	s1 = *S;
	if(!(is_element_of(x,s1)))
	{
		int sum,i,d;
		sum=0;
		for(i=0;i<x.size();i++)
		{
			sum += (int)x[i];
		}
		d=sum%113;
		Node *ptr;
		if(s1.hash1[d].exist)
		{
			Node *lptr;
			ptr = S->hash1[d].head;
			while(ptr->next!=NULL)
			{
				ptr=ptr->next;
			}
			lptr = new Node();
			lptr->data = x;
			lptr->next = NULL;
			ptr->next=lptr;
			S->size++;
		}
		else
		{
			S->hash1[d].exist=true;
			S->hash1[d].head = new Node();
			S->hash1[d].head->data = x;
			S->hash1[d].head->next = NULL;
			S->size++;	
		}
	}
}

void remove(set* S,string x)
{
	set s1;
	s1 = *S;
	if(is_element_of(x,s1))
	{
		int sum,i,d;
		sum=0;
		for(i=0;i<x.size();i++)
		{
			sum += (int)x[i];
		}
		d=sum%113;
		int f=0;
		Node *ptr,*prev;
		ptr = S->hash1[d].head;
		prev = NULL;
		while(ptr!=NULL && f==0)
		{
			if(ptr->data == x)
			{
				if(prev==NULL)
				{
					S->hash1[d].head = ptr->next;
					free(ptr);
					f=1;
				}
				else
				{
					prev->next=ptr->next;
					free(ptr);
					f=1;
				}
				S->size--;
				cout << "Data removed successfully" << "\n";
			}
			else
			{
				prev=ptr;
				ptr=ptr->next;
			}
		}
    }
}

set build(string input[], int a)
{
	int i,j,sum,d;
	string s;
	set s1;
	s1 = create();
	for(i=0;i<a;i++)
	{
		s = input[i];
		if(!(is_element_of(s,s1)))
		{
			sum=0;
			for(j=0;j<s.size();j++)
			{
				sum += (int)s[j];
			}
			d=sum%113;
			Node *ptr;
			if(s1.hash1[d].exist)
			{
				Node *lptr;
				ptr = s1.hash1[d].head;
				while(ptr->next != NULL)
				{
					ptr=ptr->next;
				}
				lptr = new Node();
				lptr->data = s;
				lptr->next = NULL;
				ptr->next=lptr;
				s1.size++;
			}
			else
			{
				s1.hash1[d].exist=true;
				ptr = s1.hash1[d].head;
				ptr = new Node();
				ptr->data = s;
				ptr->next = NULL;
				s1.hash1[d].head = ptr;
				s1.size++;	
			}
		}
	}
	return s1;
}

Node* enumerate(set S)
{
	int length = S.size;
	Node *set_ptr,*lptr,*temp,*ptr;
	set_ptr = NULL;
	int i,count=0;
	for(i=0;i<113 && count<S.size;i++)
	{
		if(S.hash1[i].exist)
		{
			lptr = S.hash1[i].head;
			while(lptr!=NULL)
			{
				temp = new Node();
				temp->data = lptr->data;
				temp->next = NULL;
				if(set_ptr == NULL)
				{
					set_ptr = temp;
					ptr = set_ptr;	
				}
				else
				{
					ptr->next=temp;	
					ptr=ptr->next;
				}
				lptr=lptr->next;
				count++;	
			}
		}
	}
	return set_ptr;
}

int set_size(set T)
{
	return T.size;
}

void Print_set(set S)
{
	if(S.size>0)
	{
	
		int i;
		Node* enumerate_list,*p;
		enumerate_list = enumerate(S);
		p = enumerate_list;
		cout << "set  consists elements:" << "\n";
		while(p!=NULL)
		{
			cout << p->data << " ";
			p=p->next;	
		}
		cout << "\n";
	}
	else
	{
		int i;
		cout << "set is NULL or empty" << "\n";
		for(i=0;i<113;i++)
		{
			S.hash1[i].exist = false;
			S.hash1[i].head = NULL;
		}	
	}
}

bool is_subset(set S,set T)
{
	Node* list;
	list = enumerate(S);
	int i,f=0;
	string st;
	while(list!=NULL && f==0)
	{
		st = list->data;
		if(!(is_element_of(st,T)))
		{
			f=1;
		}
		list=list->next;
	}
	if(f==0)
	{
		return true;
	}
	else
	{
		return false;
	}
}


set intersection(set S,set T)
{
	set intersect;
	intersect = create();
	if(S.size < T.size)
	{
		string st;
		Node *list;
		list = enumerate(S);
		while(list!=NULL)
		{
			st = list->data;
			if(is_element_of(st,T))
			{
				add(&intersect,st);
			}
			list=list->next;
		}
		
	}
	else
	{
		string st;
		Node *list;
		list = enumerate(T);
		while(list!=NULL)
		{
			st = list->data;
			if(is_element_of(st,S))
			{
				add(&intersect,st);
			}
			list=list->next;
		}	
	}
	return intersect;
}

set Union(set S,set T)
{
	set unionl;
	unionl = create();
	Node *list1,*list2;
	string st;
	list1 = enumerate(S);
	list2 = enumerate(T);
	while(list1!=NULL)
	{
		st=list1->data;
		add(&unionl,st);
		list1=list1->next;
	}
	while(list2!=NULL)
	{
		st=list2->data;
		add(&unionl,st);
		list2=list2->next;
	}
	return unionl;	
}


set Difference(set S,set T)
{
	set differ;
	differ = create();
	Node* temp;
	temp = enumerate(S);
	string st;
	while(temp!=NULL)
	{
		st=temp->data;
		if(!(is_element_of(st,T)))
		{
			add(&differ,st);
		}
		temp=temp->next;
	}
	return differ;
}


int main()
{
	set S,T;
	string s;
	int a,i,change,f;
	cout << "Enter the no of data to be entered for set 'S' " << "\n";
	cin >> a;
	string input[a];
	cout << "Enter the datas" << "\n";
	for(i=0;i<a;i++)
	{
		cin >> input[i];
	};
	S = build(input,a);
	cout << "size of set S is :" << set_size(S) << "\n";
	Print_set(S);
	f=0;
	while(f==0)
	{
		cout << "Print 1 to add, 2 to remove elements in the set or 0 to continue" << "\n";
		cin >> change;
		string elem;
		if(change==1)
		{
			cout << "Enter the data to be added" << "\n";
			cin >> elem;
			add(&S,elem);
			cout << "The size of set S is now: " << S.size << "\n";
			Print_set(S);
		}
		else if(change==2)
		{
			cout << "Enter the data to be deleted" << "\n";
			cin >> elem;
			if(is_empty(S))
			{
				cout << "set is empty" << "\n";
			}
			else
			{
				remove(&S,elem);
				cout << "The size of set S is now: " << S.size << "\n";
				Print_set(S);
			}
			
		}
		else
		{
			f=1;
		}
	}
	cout << "Enter the no of data to be entered for set 'T' " << "\n";
	cin >> a;
	string input1[a];
	cout << "Enter the datas" << "\n";
	for(i=0;i<a;i++)
	{
		cin >> input1[i];
	}
	T = build(input1,a);
	cout << "size of set T is :" << set_size(T) << "\n";
	Print_set(T);
	f=0;
	while(f==0)
	{
		cout << "Print 1 to add, 2 to remove elements in the set or 0 to continue" << "\n";
		cin >> change;
		if(change==1)
		{
			cout << "Enter the data to be added" << "\n";
			string elem;
			cin >> elem;
			add(&T,elem);
			cout << "The size of set T is now: " << T.size << "\n";
			Print_set(T);
		}
		else if(change==2)
		{
			cout << "Enter the data to be deleted" << "\n";
			string elem;
			cin >> elem;
			if(is_empty(T))
			{
				cout << "set is empty" << "\n";
			}
			else
			{
				remove(&T,elem);
				cout << "The size of set T is now: " << T.size << "\n";
				Print_set(T);
			}
		}
		else
		{
			f=1;
		}
	}
	int option,flag=0;
	while(flag==0)
	{
		cout << "Enter 1 for 'UNION', 2 for 'INTERSECTION', 3 for 'DIFFERENCE', 4 for 'SUBSET' and 0 to 'STOP'" << "\n";
		cin >> option;
		if(option==1)
		{
			set union_set;
			union_set = Union(S,T);
			cout << "Union of set S and T are:" << "\n";
			Print_set(union_set);
			cout << "size of union set is: " << union_set.size << "\n";
		}
		else if(option==2)
		{
			set intersect;
			intersect =  intersection(S,T);
			if(intersect.size == 0)
			{
				cout << "Intersection is NULL" << "\n";
			}
			else
			{
				cout << "Intersection of set S and T are :" << "\n";
				Print_set(intersect);
				cout << "size of intersection set is: " << intersect.size << "\n";
			}
		}
		else if(option==3)
		{
			cout << "Difference of set S and T i.e S-T is : " << "\n";
			set differ;
			differ = Difference(S,T);
			Print_set(differ);
			cout << "size of difference set of S and T is: " << differ.size << "\n";
			cout << "Difference of set T and S i.e T-S is : " << "\n";
			set differ1;
			differ1 = Difference(T,S);
			Print_set(differ1);
			cout << "size of difference set of T and S is: " << differ1.size << "\n"; 	
		}
		else if(option==4)
		{
			int f1=0,f2=0;
			bool ans;
			ans = is_subset(S,T);
			if(ans==true)
			{
				f1=1;
				cout << "set S is a Subset of set T" << "\n"; 
			}
			else
			{
				cout << "set S is not a subset of set T" << "\n";
			}
			ans = is_subset(T,S);
			if(ans==true)
			{
				f2=1;
				cout << "set T is a Subset of set S" << "\n"; 
			}
			else
			{
				cout << "set T is not a subset of set S" << "\n";
			}
			if(f1==1 && f2==1)
			{
				cout << "Both set S and set T are equal" << "\n";
			}
		}
		else
		{
			flag=1;
		}
	}
	return 0;
}
