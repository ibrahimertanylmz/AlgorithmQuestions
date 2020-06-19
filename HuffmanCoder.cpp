#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_TREE_HT 100 

struct MinHeapNode {
	char data;
	unsigned freq;
	struct MinHeapNode *left, *right;
};

struct MinHeap {
	unsigned size;
	unsigned capacity;
	struct MinHeapNode** array;
};

void minHeapify(struct MinHeap* minHeap, int index)//standart minHeapify fonksiyonu
{
	int smallest = index;
	int left = 2 * index + 1;
	int right = 2 * index + 2;

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq)
		smallest = right;

	if (smallest != index) 
	{
		struct MinHeapNode* t = minHeap->array[smallest];
		minHeap->array[smallest] = minHeap->array[index];
		minHeap->array[index] = t;
		minHeapify(minHeap, smallest);
	}
}

struct MinHeapNode* extractMin(struct MinHeap* minHeap)//minimum deðeri çýkarmak için standart fonksiyon
{
	struct MinHeapNode* temp = minHeap->array[0];
	minHeap->array[0]= minHeap->array[minHeap->size - 1];

	minHeap->size--;
	minHeapify(minHeap, 0);

	return temp;
}

void insertMinHeap(struct MinHeap* minHeap,struct MinHeapNode* minHeapNode)//minHeap'e yeni düðüm eklemek için fonksiyon
{
	minHeap->size++;
	int i = minHeap->size - 1;

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq)
	{
		minHeap->array[i] = minHeap->array[(i - 1) / 2];
		i = (i - 1) / 2;
	}
	minHeap->array[i] = minHeapNode;
}

//Huffman Tree'nin rootundan Huffmann codelarý CodewordLengths'e yazdýrmak için kullanýlan fonksiyon
void printCodewordLengths(struct MinHeapNode* root, int arr[], int top, vector<unsigned char> &codewordLengths)
{
	if (root->left) //Sol kenara 0 atanýr ve recursive bi þekilde devam edilir
	{
		arr[top] = 0;
		printCodewordLengths(root->left, arr, top + 1, codewordLengths);
	}

	if (root->right)//Sað kenara 1 atanýr ve recursive bi þekilde devam edilir
	{
		arr[top] = 1;
		printCodewordLengths(root->right, arr, top + 1, codewordLengths);
	}

	if (!(root->left) && !(root->right))//Eðer yaprak düðümü ise karakterlerden birini içerir ve CodewordLengthse yazdýrýlýr
	{
		codewordLengths[root->data] = top;
	}
}

///
int HuffmanCoder(vector<unsigned char> &data, vector<unsigned char> &codewordLengths) {

	int arr[256] = { 0 };

	for (int i = 0; i < data.size(); i++)
	{
		arr[data[i]]++;
	}

	vector<char> charArr;
	vector<int> charFreq;
	int count = 0;

	for (int i = 0; i < 256; i++)
	{
		if (arr[i] != 0) 
		{
			charArr.push_back(char(i));
			charFreq.push_back(arr[i]);
			count++;
		}
	}

	int *freqarray = new int[count];
	char *charray = new char[count];
	int noBits = 0;

	for (int i = 0; i < charArr.size(); i++)//frekanslarýn tutulduðu yeni bi arrayle birlikte deðer atamasý yapýlýr
	{
		charray[i] = charArr[i];
		freqarray[i] = charFreq[i];
	}

	int size = charArr.size() / sizeof(charray[0]);

	struct MinHeapNode *left, *right, *top;

	struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));

	minHeap->size = 0;
	minHeap->capacity = size;
	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));

	for (int i = 0; i < size; ++i)
	{
		struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
		temp->left = temp->right = NULL;
		temp->data = charray[i];
		temp->freq = freqarray[i];
		minHeap->array[i] = temp;
	}

	minHeap->size = size;

	int n = minHeap->size - 1;

	for (int i = (n - 1) / 2; i >= 0; --i)
		minHeapify(minHeap, i);

	while (minHeap->size != 1) {

		//en düþük frekanslý 2 item extract edilir
		left = extractMin(minHeap);
		right = extractMin(minHeap);

		//Yeni bir node oluþturulup iki düðümün frekanslarý toplamý frekansýna eþitlenir
		//Çýkarýlan düðümler bu yeni düðümün sað ve sol çocuklarý olarak atanýr.Düðüm min heape eklenir
		struct MinHeapNode* top = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
		top->left = top->right = NULL;
		top->data = '$';
		top->freq = left->freq + right->freq;

		top->left = left;
		top->right = right;

		insertMinHeap(minHeap, top);
	}

	struct MinHeapNode* root = extractMin(minHeap);//kalan düðüm root nodedur ve aðaç tamamlanýr

	int arr2[MAX_TREE_HT], topEl = 0;

	printCodewordLengths(root, arr2, topEl, codewordLengths);

	for (int i = 0; i < data.size(); i++)
	{
		noBits += codewordLengths[data[i]];
	}
	return noBits;
} //end-HuffmanCoder
