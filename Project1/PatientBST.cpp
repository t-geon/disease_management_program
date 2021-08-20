#include<cstring>
#include<iostream>
#include "PatientBST.h"
#pragma warning(disable:4996)

PatientBST::PatientBST()
{
    Root = NULL;
}

PatientBST::~PatientBST()
{
}

PatientBSTNode* PatientBST::GetRoot()
{
    return Root;
}

bool PatientBST::Insert(PatientNode* node)
{
    //QPOP
    char di;
    if (node->GetCough() == 'Y' && node->GetTemp() >= 37.5) { di = '+'; }
    else { di = '-'; }

    PatientBSTNode* cur = Root;
    PatientBSTNode* prev = NULL;

    while (cur != NULL) {
        prev = cur;
        if (strcmp(cur->GetName(), node->GetName()) > 0) { cur = cur->GetLeft(); }
        else if (strcmp(cur->GetName(), node->GetName()) < 0) { cur = cur->GetRight(); }


        else { cout << "duplicared" << endl; return 0; }
    }

    cur = new PatientBSTNode;
    cur->SetName(node->GetName());
    cur->SetDisease(di);
    if (Root != NULL) {
        if (strcmp(prev->GetName(), node->GetName()) > 0) {
            prev->SetLeft(cur);
            return 1;
        }
        else if (strcmp(prev->GetName(), node->GetName()) < 0) {
            prev->SetRight(cur);
            return 1;
        }
    }
    else {
        Root = cur;
        return 1;
    }
    return 0;
}


bool PatientBST::Search(char* name)
{
    //SEARCH
    PatientBSTNode* cur = Root;
    if (cur == NULL) { return 0; }

    while (cur != NULL) {//cur이 NULL이 아니면 반복
        if (strcmp(cur->GetName(), name) > 0) { cur = cur->GetLeft(); }//cur의 이름이 찾는 이름보다 크면 cur=cur->left
        else if (strcmp(cur->GetName(), name) < 0) { cur = cur->GetRight(); }//cur의 이름이 찾는 이름보다 작으면 cur=cur->right
        else {//찾는 이름일때
            ofstream flog;
            flog.open("log.txt", ios::app);
            cout << "========== " << "SEARCH" << " ==========" << endl;
            flog << "========== " << "SEARCH" << " ==========" << endl;
            flog << name << "/" << cur->GetDisease() << endl;
            cout << name << "/" << cur->GetDisease() << endl;
            cout << "============================" << endl << endl;
            flog << "============================" << endl << endl;
            return 1;
        }
    }
    return 0;
}

bool PatientBST::Delete(char* name)
{
    //BPOP
    PatientBSTNode* cur = Root;
    PatientBSTNode* par = NULL;
    if (Root == NULL) { return 0; }//BST가 비어있을 때
    while (cur != NULL) {//같지 않으면 계속 반복, 빈 트리면 cur에 NULL
        if (strcmp(cur->GetName(), name) == 0) { break; }
        par = cur;
        if (strcmp(cur->GetName(), name) > 0) {
            cur = cur->GetLeft();
        }
        else if (strcmp(cur->GetName(), name) < 0) {
            cur = cur->GetRight();
        }
    }
    if (cur == NULL) { return 0; }//삭제하는 거 못찾음

    if (cur->GetLeft() == NULL && cur->GetRight() == NULL) {//삭제하는거 자식x
        if (par == NULL) { Root = NULL; delete cur; }//삭제하는게 루트
        else if (par->GetLeft() == cur) { par->SetLeft(NULL); }//삭제하는거 부모 왼쪽
        else { par->SetRight(NULL); }//삭제하는거 부모 오른쪽
        cur = NULL; delete cur;
        return 1;
    }

    if (cur->GetLeft() == NULL) {//삭제하는거 오른자식만 있을때
        if (par == NULL) { Root = cur->GetRight(); }//삭제하는게 루트
        else if (par->GetLeft() == cur) { par->SetLeft(cur->GetRight()); }//삭제하는거 부모 왼쪽
        else { par->SetRight(cur->GetRight()); }//삭제하는거 부모 오른쪽
        cur = NULL; delete cur;
        return 1;
    }

    if (cur->GetRight() == NULL) {//삭제하는거 왼자식만 있을때
        if (par == NULL) { Root = cur->GetLeft(); }//삭제하는게 루트
        else if (par->GetLeft() == cur) { par->SetLeft(cur->GetLeft()); }//삭제하는거 부모 왼쪽
        else { par->SetRight(cur->GetLeft()); }//삭제하는거 부모 오른쪽
        cur = NULL; delete cur;
        return 1;
    }

    //삭제하는거 자식 2개
    PatientBSTNode* pprev = cur;
    PatientBSTNode* prev = cur->GetLeft();//prev는 삭제할거 왼쪽 자식
    PatientBSTNode* c = cur->GetLeft()->GetRight();//삭제할거 왼자식의 오른자식에서 시작

    while (c) {
        pprev = prev;
        prev = c;
        c = c->GetRight();
    }//c이 NULL되면 prev에 삭제노드 왼자식 중 가장 큰거 저장

    if (pprev == cur) {//바로 c= NULL
        prev->SetRight(cur->GetRight());
        if (par == NULL) { Root = prev; }//삭제노드 루트일때
        else if (par->GetLeft() == cur) { par->SetLeft(prev); }//삭제하는거 부모 왼쪽
        else { par->SetRight(prev); }//삭제하는거 부모 오른쪽
        cur = NULL; delete cur;
        return 1;
    }
    else {
        pprev->SetRight(prev->GetLeft());//삭제노드 자식 중 가장큰에 올라오니까 큰애 왼자식을 올라오는 부모에게 연결
        prev->SetRight(cur->GetRight());//올라오는 노드의 오른자식을 삭제노드의 오른자식으로
        prev->SetLeft(cur->GetLeft());//올라오는 노드의 왼자식을 삭제노드의 왼자식으로
        if (par == NULL) { Root = prev; }
        else if (par->GetLeft() == cur) { par->SetLeft(prev); }//삭제하는거 부모 왼쪽
        else { par->SetRight(prev); }//삭제하는거 부모 오른쪽
        cur = NULL; delete cur;
        return 1;
    }
    return 0;
}

void PatientBST::Print_PRE(PatientBSTNode* node)
{
    //PRINT B PRE
    if (node != NULL) {
        ofstream flog;
        flog.open("log.txt", ios::app);
        flog << node->GetName() << "/" << node->GetDisease() << endl;
        cout << node->GetName() << "/" << node->GetDisease() << endl;
        Print_PRE(node->GetLeft());//Print_PRE에 node의 left전달
        Print_PRE(node->GetRight());//Print_PRE에 node의 right전달
    }
}

void PatientBST::Print_IN(PatientBSTNode* node)
{
    //PRINT B IN
    if (node != NULL) {

        Print_IN(node->GetLeft());//Print_IN에 node의 left전달
        ofstream flog;
        flog.open("log.txt", ios::app);
        flog << node->GetName() << "/" << node->GetDisease() << endl;
        cout << node->GetName() << "/" << node->GetDisease() << endl;
        Print_IN(node->GetRight());//Print_IN에 node의 right전달
    }
}

void PatientBST::Print_POST(PatientBSTNode* node)
{
    //PRINT B POST
    if (node != NULL) {
        Print_POST(node->GetLeft());//Print_POST에 node의 left전달
        Print_POST(node->GetRight());//Print_POST에 node의 right전달
        ofstream flog;
        flog.open("log.txt", ios::app);
        flog << node->GetName() << "/" << node->GetDisease() << endl;
        cout << node->GetName() << "/" << node->GetDisease() << endl;
    }
}

void PatientBST::Print_LEVEL()
{
    //PRINT B LEVEL
    queue< PatientBSTNode*>q;
    PatientBSTNode* cur = Root;
    while (cur) {
        ofstream flog;
        flog.open("log.txt", ios::app);
        flog << cur->GetName() << "/" << cur->GetDisease() << endl;
        cout << cur->GetName() << "/" << cur->GetDisease() << endl;
        if (cur->GetLeft()) { q.push(cur->GetLeft()); }//queue에 cur의 left push
        if (cur->GetRight()) { q.push(cur->GetRight()); } // queue에 cur의 right push
        if (q.empty()) { return; }//queue가 비어있으면 종료
        cur = q.front();//cur은 queue의 제일 앞 원소로 저장
        q.pop();//queue의 첫번째 원소 pop
    }
}
