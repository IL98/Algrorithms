#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;

class Stack;

class BinaryTree{//класс дерева

public:
  struct BinaryNode{//структура узла
  int Key;
  BinaryNode* Parent;
  BinaryNode* Left;
  BinaryNode* Right;
  BinaryNode(int k){
    Key=k;
    Left=0;
    Right=0;
  }
};
  BinaryNode* root;
  BinaryTree(){
   root=NULL;
  }

  ~BinaryTree(){
    queue <BinaryNode*> q;
    if (root) q.push(root);
    while (!q.empty()){
      BinaryNode* temp=q.front();
      q.pop();
      if (temp->Left)  q.push(temp->Left);
      if (temp->Right) q.push(temp->Right);
      delete temp;
    }
  }
  friend Stack;//дружественный класс стек
  void Add_Node(int Key){//добавление нового элемента по ключу
    BinaryNode* c=new BinaryNode(Key);
    if (root==NULL){
        root=c;
        return;
    }
    BinaryNode* p=root;
    while (p->Right || p->Left){
        if (Key>=p->Key){
            if (p->Right)
                p=p->Right;
            else {
                break;
            }
        } else{
           if (p->Left)
            p=p->Left;
           else {
                break;
           }
        }
    }
    (Key >= p->Key)? p->Right=c : p->Left=c;
    c->Left=c->Right=0;
    c->Parent=p;
  };



};


class Stack{//здесь я описываю класс стек. стек у меня описан в виде динамического буфера
private:
	BinaryTree::BinaryNode** mas;
	int tail;
	int Size;
public:
	Stack(){
	    Size=110;
		tail = -1;
		mas = new BinaryTree::BinaryNode*[110];
	};
	~Stack(){
		delete[] mas;
	};
	void push(BinaryTree::BinaryNode* value){
		if (tail>=(Size-1)) grow();
		tail++;
		mas[tail] = value;
	};
	void grow(){
        BinaryTree::BinaryNode** mas1=new BinaryTree::BinaryNode*[2*Size-1];
        for(int i(0);i<Size;i++)
            mas1[i]=mas[i];
        delete [] mas;
        mas=mas1;
        Size=2*Size-1;
	}

	bool Is_Empty(){
		if (tail == -1) return true;
		else return false;
	};
    BinaryTree::BinaryNode* last(){
      return mas[tail];
    }
	BinaryTree::BinaryNode* pop(){
		if (!Is_Empty()) return  mas[tail--];
		else return 0;
	}
};

void PostOrder(int* mas,BinaryTree& Tree){//здесь у меня главный обход Post Order
    int Size=0;                           //рекурсию заменил на стек
    Stack Left;                           //также здесь я одновременно забиваю в массив ключи в порядке обхода
   BinaryTree::BinaryNode* l=Tree.root;
    while (l || !(Left.Is_Empty())){
        if (!Left.Is_Empty()){
            l=Left.pop();
         if (!(Left.Is_Empty()) && Left.last()==l->Right){
          l=Left.pop();
         } else {
          mas[Size++]=l->Key;
          l=NULL;
         }
        }
        while (l){
          Left.push(l);
          if (l->Right){
          Left.push(l->Right);
          Left.push(l);
          }
          l=l->Left;
          }
        }
}

void Action (int* mas, int n){// функция передаю массив ключей
                              // создаю дерево добавляю туда элементы и делаю Post Order
  BinaryTree Tree;
  for (int i(0);i<n;i++){
    Tree.Add_Node(mas[i]);
  }
  PostOrder(mas, Tree );

}

int main(){
  int n=0;
  scanf ("%d/n", &n);
  int* mas=new int[n];
  for (int i(0);i<n; i++){
    scanf(" %d", mas+i);
  }
  Action(mas,n);
  for (int i(0);i<n;i++){//вывожу массив
    printf("%d ",mas[i]);
  }
  delete [] mas;
  return 0;
}
