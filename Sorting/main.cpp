/**
* Implementations of Heap sort, Selection sort,  Insertion sort, Quick sort, Merge sort, Counting sort
*
*/
#include <stdio.h>
#include <iostream>
#include <string.h>

using namespace std;


class BinaryHeap
{
private:
    int* Data;
	int Size;
	int ArrSize;+
    int* result;
public:

	BinaryHeap(int* mas, int* balance, int n)
	{
		Size = n;
		Data = mas;
		result=balance;
		ArrSize=n;
		BuildHeap();
	}

	void SiftDown(int index){
		int left = 2 * index + 1;
		int right = 2 * index + 2;
		int largest = index;
		if (left<Size && Data[left]> Data[largest]) largest = left;
		if (right<Size && Data[right]> Data[largest]) largest = right;
		if (left<Size && Data[left]== Data[largest]) if (result[left]>result[largest]) largest = left;
		if (right<Size && Data[right]== Data[largest]) if (result[right]>result[largest]) largest = right;
		if (largest != index) {
			swap(Data[index], Data[largest]);
			swap(result[index], result[largest]);
			SiftDown(largest);
		}
	}

	void BuildHeap()
	{
		for (int i = Size / 2 - 1; i >= 0; i--) {
			SiftDown(i);
		}
	}

	void GetRoot()//функция извлечения максимального элемента
	{
		if (!IsEmpty()){//проверяем, если куча непуста
			swap(Data[0], Data[Size - 1]);
			swap(result[0], result[Size - 1]);
			Size--;
			SiftDown(0);
		}
	}

	bool IsEmpty()
	{
		if (Size <= 0) return true;
		return false;
	}

    int Maximum(){// функция посчета максимального количества современников
      int maximum(0);
      int s(0);
      for (int i(0);i<ArrSize;i++){
        s+=result[i];
        if (s>maximum) maximum=s;
      }
      return maximum;
    }
};

void HeapSort(BinaryHeap Heap){
  Heap.BuildHeap();
  while (!(Heap.IsEmpty()))
    Heap.GetRoot();
}

void SelectionSort(int* mas,int n){
  int k(0);
  while (k<n-1){
   int minIndex=k;

    for (int i(k+1);i<n;i++){
      if (mas[i]<mas[minIndex]) minIndex=i;
    }
    swap(mas[k],mas[minIndex]);
    k++;
  }
}

void InsertionSort (int* mas, int n){
  for (int i(1);i<n;i++ ){
     int j=i;
     while ((mas[j]<mas[j-1]) && (j>0)){
       swap(mas[j],mas[j-1]);
       j--;
     }
  }
}

void Partition (int* mas, int* l, int* r){
  int i=(*l);
  int j=(*r);
  int pivot=mas[((*r)+(*l))/2];
  while (i<j) {
    while (mas[i]<pivot) i++;
    while (mas[j]>pivot) j--;
    if (i<=j) {
        swap(mas[i],mas[j]);
        i++;
        j--;
    }
  }
  (*l)=i;
  (*r)=j;
}

void qsort(int* mas, int l, int r){


  int x=l;
  int y=r;
  Partition(mas, &x, & y);
  if (l<y) qsort(mas, l, y);
  if (x<r) qsort(mas, x, r);
}

//Merge sort
void Merge(int* mas1, int len1, int* mas2, int len2, int* masres){
  int i=0;
  int j=0;
  while (i<len1 && j<len2) {
    if (mas1[i]<mas2[j]){
        masres[i+j]=mas1[i];
        i++;
    }
    else {
        masres[i+j]=mas2[j];
        j++;
    }

  }
  if (i==len1)
    while (j<len2) {
        masres[i+j]=mas2[j];
        j++;
    } else
    while (i<len1) {
        masres[i+j]=mas1[i];
        i++;
    }
}

void MergeSort (int* mas, int n){
  if (n<=1) return;
  MergeSort( mas, n/2);
  MergeSort (mas+ n/2, n-n/2);
  int* masres=new int[n];
  Merge(mas, n/2, mas+n/2, n-n/2, masres );
  memcpy(mas,masres, sizeof(int)*n );
  delete[] masres;
}



void CountingSort(int* mas,int n,int k){
  int* result=new int[k];
  for (int i(0);i<k; i++){
    result[i]=0;
  }
  for (int i(0);i<n; i++){
    result[mas[i]]++;
  }
  int p(0);
  for (int i(0);i<k; i++){
    for(int j(0);j<result[i];j++){
        mas[p++]=i;
    }
    if (p>n) break;
  }
  delete[] result;
}



int main(){
  int n;
  scanf("%d\n", &n);
  int* mas = new int[n];
  for (int i(0); i<n; i++)
		scanf(" %d", &mas[i]);
   qsort(mas, 0, n-1);
  for (int i(0);i<n;i++){
    printf("%d ", mas[i]);
  }
  delete[] mas;
  return 0;
}
