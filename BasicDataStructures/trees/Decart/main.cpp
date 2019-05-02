#include <iostream>
#include <stdio.h>
#include <queue>

using namespace std;
class Stack;

class BinaryTree{//класс наивного дерева поиска

public:
  struct BinaryNode{//структура узла дерева
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
  friend Stack;
  void Add_Node(int Key){//добавление элемента по ключу
    BinaryNode* c=new BinaryNode(Key);
    if (root==NULL){
        root=c;
        root->Left=0;
        root->Right=0;
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
    c->Left=c->Right=NULL;
    c->Parent=p;
  };
  int Height(BinaryNode* tree){//высота узла
    int m1,m2;
    if (!tree)
        return 0;
    m1=Height(tree->Left);
    m2=Height(tree->Right);
    return std::max(m1,m2)+1;

  }


};


class Stack{//здесь я описываю класс стек. стек у меня описан в виде динамического буфера
private:
	BinaryTree::BinaryNode** mas;
	int tail;
	int Size;
public:
	Stack(){
	    Size=1;
		tail = -1;
		mas = new BinaryTree::BinaryNode*[1];
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



class DecartTree{//класс декартово дерево

 public:
struct Node{//структура узла
  int Key;
  int Priority;
  Node* left;
  Node* right;
  Node (int key, int y){
   Key=key;
   Priority=y;
   left=0;
   right=0;
  }
 };

  Node* root;
  DecartTree(){
   root=0;
  }
  ~DecartTree(){
    queue <Node*> q;
    if (root) q.push(root);
    while (!q.empty()){
      Node* temp=q.front();
      q.pop();
      if (temp->left)  q.push(temp->left);
      if (temp->right) q.push(temp->right);
      delete temp;
    }
  }
void Split(Node* Tree,Node *&Left, Node *&Right,int Key ){
   if (!Tree){
      Left=Right=0;
   } else if (Tree->Key>Key){
            Split(Tree->left,Left,Tree->left, Key);
            Right=Tree;
         } else {
         Split(Tree->right, Tree->right, Right, Key);
         Left=Tree;
     }
  }
Node* Merge(Node* Tree1,Node* Tree2){
  if (!Tree1) return Tree2;
  if (!Tree2) return Tree1;
  if (Tree1->Priority >= Tree2->Priority){
     Tree1->right=Merge(Tree1->right, Tree2);
     return Tree1;
  } else {
     Tree2->left=Merge(Tree2->left,Tree1);
     return Tree2;
  }
}
void Add(int x, int y){//добавление узла в декартово дерево по ключу и приоритету
  Node* temp=new Node(x,y);
  Insert(root, temp);
}
  void Insert(Node* &tree, Node* temp){//вставка узла
    if (!tree){
        tree=temp;
        return;
    }
    if (temp->Priority>tree->Priority){
        Split(tree, temp->left, temp->right, temp->Key);
        tree=temp;
    } else {
        if (temp->Key>=tree->Key)
         Insert(tree->right, temp);
        else Insert(tree->left, temp);
    }
  }
int Height(Node* Tree){//поиск высоты
  int m1,m2;
  if (!Tree) return 0;
  m1=Height(Tree->right);
  m2=Height(Tree->left);
  return std::max(m1, m2)+1;
}
};



int Differ_Height(int* mas1,int* mas2,int n ){//главная функция измерения разности высот



 BinaryTree B;
 DecartTree D;
 for (int i(0);i<n;i++){
   D.Add(mas1[i],mas2[i]);
   B.Add_Node(mas1[i]);
  }
  return B.Height(B.root)-D.Height(D.root);
}


int main(){
  int n;
  scanf("%d/n", &n);
  int* mas1=new int[n];
  int* mas2=new int[n];
  for (int i(0); i<n; i++){
    scanf(" %d %d/n", mas1+i, mas2+i);
  }
  printf("%d",Differ_Height(mas1,mas2, n));
  delete [] mas1;
  delete [] mas2;
  return 0;
}
