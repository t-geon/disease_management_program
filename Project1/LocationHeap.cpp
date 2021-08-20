#include "LocationHeap.h"
#include<cstring>
#include<iostream>
#pragma warning(disable:4996)

LocationHeap::LocationHeap()
{
    Heap = new LocationHeapNode * [10];
    size = 0;
}

LocationHeap::~LocationHeap()
{
    delete Heap;
}

bool LocationHeap::Insert(char* location)
{
    //BPOP
    for (int i = 1; i < size + 1; i++) {
        if (!strcmp(Heap[i]->GetLoc(), location)) {//���� �̸��� ��尡 �̹� ���� ��
            Heap[i]->SetCount(1);//�ش� ����� count�� 1 ������Ų��.
            if (i != 1) {//root ���� count�� �����Ѱ�� ��迭
                LocationHeapNode* inn = Heap[i];
                while (Heap[i / 2]->GetCount() < inn->GetCount()) {//�θ𺸴� count�� ũ��
                    Heap[i] = Heap[i / 2];//�θ�� �ڸ� �ٲٱ�
                    i /= 2;
                    if (i <= 1) { break; }
                }
                Heap[i] = inn;
            }
            return 1;
        }
    }

    //heap��忡 ���� ������ ȯ���̸�
    LocationHeapNode* innode = new LocationHeapNode;
    innode->SetLoc(location);
    innode->SetCount(1);

    int curnode = ++size;
    while (curnode != 1 && Heap[curnode / 2]->GetCount() < innode->GetCount()) {//�� ���̾ƴϰ� �θ𺸴� ���� ũ��
        Heap[curnode] = Heap[curnode / 2];//���� NULL�̶� ���� �ȳ�����?
        curnode /= 2;//�����ϴ� ��ġ�� ������ġ�� �θ���ġ��
    }
    Heap[curnode] = innode;
}

void LocationHeap::Print()
{
    //PRINT H
    int cnum = 1;
    Heap[size + 1] = NULL;
    queue< LocationHeapNode*>* qu = new queue<LocationHeapNode*>;
    LocationHeapNode* cur = Heap[cnum];
    ofstream flog;
    flog.open("log.txt", ios::app);

    if (size != 0) {
        flog << "Heap" << endl;
        cout << "Heap" << endl;
    }
    else { return; }
    while (cur) {//cur�� NULL�� �ƴϸ� �ݺ�
        flog << cur->GetCount() << "/" << cur->GetLoc() << endl;
        cout << cur->GetCount() << "/" << cur->GetLoc() << endl;
        cnum *= 2;//cum�� 2�� �����ָ� ���� �ڽ��� ��ġ�� �ȴ�.
        for (int a = cnum; a < cnum * 2; a++) { if (size >= a) { qu->push(Heap[a]); } }
        if (qu->empty()) { return; }
        cur = qu->front();//cur�� queue�� ���� �� ���Ҹ� ����
        qu->pop();//queue�� ���� �� ���� pop
    }
}

int LocationHeap::Getsize() {
    return size;
}
