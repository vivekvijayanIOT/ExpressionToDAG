#include<iostream>
#include<string>
#include "StackType.h"
using namespace std;

struct node;
int priority(char);
node* makeNode(char);
void placeOperator(StackType<node*>&, StackType<node*>&); 
int DAG(node*);
void Footer();

struct node{
	char info;
	node* left;
	node* right;
};

int main(){

	string infix; 
    StackType<char> input; 
	StackType<node*> operators; 
	StackType<node*> treenodes;
	char temp,again=' ';
	cout << "Expression to DAG" << endl;
	cout << "Program to develop a Directed Acyclic Graph using Expression" << endl;
	
	while (again!='n')
	{
		cout << endl << "Enter the mathematical expression" << endl;
		cin >> infix;
		
		for (int i=0;i<infix.length();i++){
			input.Push(infix[i]);
		}
		while(!input.IsEmpty()){
			temp=input.Top();
			input.Pop();
			
			if (isdigit(temp))  
				treenodes.Push(makeNode(temp));
			
			if (temp==')')
				operators.Push(makeNode(temp));
			
			if ((temp=='+') || (temp=='/') || (temp =='-') || (temp=='*')) {
				bool pushed = false;
				while(!pushed){
					
					if(operators.IsEmpty()){
						operators.Push(makeNode(temp));
						pushed=true;
					}
					
					else if (operators.Top()->info ==')'){
						operators.Push(makeNode(temp));
						pushed=true;
					}
					
					else if ((priority(temp)>priority(operators.Top()->info)) || (priority(temp)==priority(operators.Top()->info))){
						operators.Push(makeNode(temp));
						pushed=true;
					}
					
					else {
						placeOperator(treenodes,operators);
					}	
				}
			}
			
			if (temp=='('){
				while (operators.Top()->info!=')')
				{
					placeOperator(treenodes,operators);
				}
				operators.Pop();
			}
		}
		
		while(!operators.IsEmpty()){
			placeOperator(treenodes,operators);
		}

		int answer = DAG(treenodes.Top());
		cout << endl << "Final Answer: " << answer << endl;
		cout << endl;
		cout << "Would  you like to convert another expression? (y/n)";
		cin >> again;
	} 
	cout << endl;
	return 0;
}

int priority(char op){
	if ((op =='+') || (op =='-'))
		return 1;
	if ((op =='/') || (op =='*'))
		return 2;
}

node* makeNode(char info){
	node* childnode;
	childnode = new node;
	childnode->info = info;
	childnode->left = NULL;
	childnode->right = NULL;
	return childnode;
}

void placeOperator(StackType<node*>& treenodes, StackType<node*>& operators){
	node* operatornode = operators.Top();
	operators.Pop();
	operatornode->left = treenodes.Top();
	treenodes.Pop();
	operatornode->right = treenodes.Top();
	treenodes.Pop();
	treenodes.Push(operatornode);
}

int DAG(node* treenode){
	int x,y,z;
	if ((treenode->info) == '+'||(treenode->info) == '-'||(treenode->info) == '*'||(treenode->info) == '/') {
		x = DAG(treenode->left);
		y = DAG(treenode->right);
		if (treenode->info=='+')
			{
				z=x+y;
				cout<<"\n***************************************";
				cout<<"\nLeftNode : "<<x;
				cout<<"\nRightNode : "<<y;
				cout<<"\nRoot : + \nValue :"<<z;
			}
		else if (treenode->info=='-')
			{
				z=x-y;
				cout<<"\n***************************************";
				cout<<"\nLeftNode : "<<x;
				cout<<"\nRightNode : "<<y;
				cout<<"\nRoot : - \nValue :"<<z;
			}
		else if (treenode->info=='*')
			{
				z=x*y;
				cout<<"\n***************************************";
				cout<<"\nLeftNode : "<<x;
				cout<<"\nRightNode : "<<y;
				cout<<"\nRoot : * \nValue :"<<z;
			}
		else if (treenode->info=='/')
			{
				z=x/y;
				cout<<"\n***************************************";
				cout<<"\nLeftNode : "<<x;
				cout<<"\nRightNode : "<<y;
				cout<<"\nRoot : / \nValue :"<<z;
			}
		return z;
	}
	else return treenode->info - '0';	
}

