#include <iostream>
#include <cstdio>
#include <queue>

using namespace std;

class AVL_tree{//класс АВЛ дерева
  struct Node{//структура узла
    int Height;
    int Key;
    Node* Left;
    Node* Right;
    int Size;//количество элементов в поддереве этого узла
    Node(int k){
      Key=k;
      Height=1;
      Left=Right=0;
      Size=1;
    }
  };
public:
    Node* root;
  AVL_tree(){
    root=0;
  }
  ~AVL_tree(){
    queue <Node*> q;
    if (root) q.push(root);
    while (!q.empty()){
      Node* temp=q.front();
      q.pop();
      if (temp->Left)  q.push(temp->Left);
      if (temp->Right) q.push(temp->Right);
      delete temp;
    }
  }

  void ReHeight(Node* Tree){//функция восстановления высоты вершины
    int h_r=(Tree->Right)?Tree->Right->Height:0;
    int h_l=(Tree->Left)?Tree->Left->Height:0;
    Tree->Height=std::max(h_r, h_l)+1;

  }

  int _Size(Node* tree){
    return (tree)?tree->Size:0;
  };

  void ReSize(Node* tree){//функция счета количества элементов в поддеревеб если знать счет в правом и девом поддереве
    tree->Size= _Size(tree->Left)+ _Size(tree->Right)+1;
  }

  int Height(Node* tree){
    return (tree)?tree->Height:0;
  }


  int Balance(Node* Tree){//счет баланса узла
    return (Tree->Left?Tree->Left->Height:0) - (Tree->Right?Tree->Right->Height:0);
  }


  Node* LittleLeftTurn(Node* tree){//малый левый поворот
    Node* temp=tree->Right;
    tree->Right=temp->Left;
    temp->Left=tree;
    ReHeight(tree);
    ReSize(tree);
    ReHeight(temp);
    ReSize(temp);
    return temp;
  }

  Node* LittleRightTurn(Node* tree){//мадый правый поворот

    Node* temp=tree->Left;
    tree->Left=temp->Right;
    temp->Right=tree;
    ReHeight(tree);
    ReSize(tree);
    ReHeight(temp);
    ReSize(temp);
    return temp;
  }

  Node* BigRightTurn(Node* tree){//большой левый поворот
    tree->Left=LittleLeftTurn(tree->Left);
   return LittleRightTurn(tree);
  };


  Node* BigLeftTurn(Node* tree){//большой левый поворот
    tree->Right=LittleRightTurn(tree->Right);
   return LittleLeftTurn(tree);
  }


  Node* Balancing(Node* tree){// общая балансировка узла
     if ((Balance(tree)==-2) && (Balance(tree->Right)<=0))
       return LittleLeftTurn(tree);
     if ((Balance(tree)==2) && (Balance(tree->Left)>=0) )
       return  LittleRightTurn(tree);
     if ((Balance(tree)==2) && (Balance(tree->Left)<0))
       return BigRightTurn(tree);
     if ((Balance(tree)==-2) && (Balance(tree->Right)>0))
       return BigLeftTurn(tree);
      return tree;
  }

  Node* Remove_Min(Node* temp){// удаление минимального узла из поддерева
    if (!temp->Left)
        return temp->Right;
    temp->Size--;
    temp->Left=Remove_Min(temp->Left);
    return Balancing(temp);

  }

  Node* Add(Node* temp, int k){//добавление узла
    if (!temp) {
        return new Node(k);
    }
    if (k>=temp->Key){
        temp->Right=Add(temp->Right,k);

    } else {
        temp->Left=Add(temp->Left, k);
    }
    temp->Size++;
   return  Balancing(temp);
  }

  void Number(Node* tree, int x, int& n){//подсчет места на котором стоит солдат, то есть нахождение номера по росту
    if (x==tree->Key){
        n+=_Size(tree->Right);
        return;
    }
    if (x>tree->Key){
        Number(tree->Right, x, n);
    } else {
        n+=_Size(tree->Right)+1;
        Number(tree->Left, x, n); //возможно нужны resize
    }

  }

  int Soldier_Place(Node* tree, int& n){//нахождение роста солдата по номеру который он стоит
     if (n==_Size(tree->Right)){
       return tree->Key;
     } else if (n<_Size(tree->Right)){
       return Soldier_Place(tree->Right, n);
     } else {
      n-=_Size(tree->Right)+1;
       return Soldier_Place(tree->Left, n);
     }
  }

  Node* Remove(Node* temp, int k){//удаление ключа
    if (!temp)
        return 0;
    if (temp->Key<k){
         temp->Right=Remove(temp->Right, k);
         temp->Size--;

    }
    if (temp->Key>k){
         temp->Left=Remove(temp->Left, k);
         temp->Size--;
    }
    if (temp->Key==k){
              Node* left=temp->Left;
              Node* right=temp->Right;
              delete temp;
              if (!right){
                return left;
              }
              Node* t=right;
              while (t->Left){
                t=t->Left;
              }
              t->Right=Remove_Min(right);
              t->Left=left;
              ReSize(t);
              return Balancing(t);
          }
       return Balancing(temp);

    }


};


void action(int* mas1, int* mas2, int n){//процедура в которой я обрабатываю массивы и забиваю в них номера вставляемых узлов
  AVL_tree T;                            //здесь же создаю дерево
  for (int i(0);i<n;i++){
    if (mas1[i]==1){
        T.root=T.Add(T.root, mas2[i]);
        int n(0);
        T.Number(T.root, mas2[i], n);
        mas2[i]=n;
    } else {
        int x=T.Soldier_Place(T.root, mas2[i]);
        T.root=T.Remove(T.root, x);
    }

  }
}


int main()
{
  int n;
  scanf ("%d\n",&n);
  int* mas1=new int[n];
  int* mas2=new int[n];
  for (int i(0); i< n; i++){
    scanf(" %d %d", mas1+i, mas2+i);
  }
  action(mas1, mas2, n);
  for (int i(0);i<n;i++){
    if (mas1[i]==1)
        printf("%d\n", mas2[i]);
  }
  delete [] mas1;
  delete [] mas2;
  return 0;
}
