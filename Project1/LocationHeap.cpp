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
        if (!strcmp(Heap[i]->GetLoc(), location)) {//같은 이름의 노드가 이미 있을 떄
            Heap[i]->SetCount(1);//해당 노드의 count를 1 증가시킨다.
            if (i != 1) {//root 외의 count가 증가한경우 재배열
                LocationHeapNode* inn = Heap[i];
                while (Heap[i / 2]->GetCount() < inn->GetCount()) {//부모보다 count가 크면
                    Heap[i] = Heap[i / 2];//부모와 자리 바꾸기
                    i /= 2;
                    if (i <= 1) { break; }
                }
                Heap[i] = inn;
            }
            return 1;
        }
    }

    //heap노드에 없는 지역의 환자이면
    LocationHeapNode* innode = new LocationHeapNode;
    innode->SetLoc(location);
    innode->SetCount(1);

    int curnode = ++size;
    while (curnode != 1 && Heap[curnode / 2]->GetCount() < innode->GetCount()) {//빈 힙이아니고 부모보다 값이 크면
        Heap[curnode] = Heap[curnode / 2];//여기 NULL이라서 오류 안나려나?
        curnode /= 2;//삽입하는 위치를 원래위치의 부모위치로
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
    while (cur) {//cur이 NULL이 아니면 반복
        flog << cur->GetCount() << "/" << cur->GetLoc() << endl;
        cout << cur->GetCount() << "/" << cur->GetLoc() << endl;
        cnum *= 2;//cum에 2를 곱해주면 왼쪽 자식의 위치가 된다.
        for (int a = cnum; a < cnum * 2; a++) { if (size >= a) { qu->push(Heap[a]); } }
        if (qu->empty()) { return; }
        cur = qu->front();//cur에 queue의 제일 앞 원소를 저장
        qu->pop();//queue에 제일 앞 원소 pop
    }
}

int LocationHeap::Getsize() {
    return size;
}
