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

    while (cur != NULL) {//cur�� NULL�� �ƴϸ� �ݺ�
        if (strcmp(cur->GetName(), name) > 0) { cur = cur->GetLeft(); }//cur�� �̸��� ã�� �̸����� ũ�� cur=cur->left
        else if (strcmp(cur->GetName(), name) < 0) { cur = cur->GetRight(); }//cur�� �̸��� ã�� �̸����� ������ cur=cur->right
        else {//ã�� �̸��϶�
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
    if (Root == NULL) { return 0; }//BST�� ������� ��
    while (cur != NULL) {//���� ������ ��� �ݺ�, �� Ʈ���� cur�� NULL
        if (strcmp(cur->GetName(), name) == 0) { break; }
        par = cur;
        if (strcmp(cur->GetName(), name) > 0) {
            cur = cur->GetLeft();
        }
        else if (strcmp(cur->GetName(), name) < 0) {
            cur = cur->GetRight();
        }
    }
    if (cur == NULL) { return 0; }//�����ϴ� �� ��ã��

    if (cur->GetLeft() == NULL && cur->GetRight() == NULL) {//�����ϴ°� �ڽ�x
        if (par == NULL) { Root = NULL; delete cur; }//�����ϴ°� ��Ʈ
        else if (par->GetLeft() == cur) { par->SetLeft(NULL); }//�����ϴ°� �θ� ����
        else { par->SetRight(NULL); }//�����ϴ°� �θ� ������
        cur = NULL; delete cur;
        return 1;
    }

    if (cur->GetLeft() == NULL) {//�����ϴ°� �����ڽĸ� ������
        if (par == NULL) { Root = cur->GetRight(); }//�����ϴ°� ��Ʈ
        else if (par->GetLeft() == cur) { par->SetLeft(cur->GetRight()); }//�����ϴ°� �θ� ����
        else { par->SetRight(cur->GetRight()); }//�����ϴ°� �θ� ������
        cur = NULL; delete cur;
        return 1;
    }

    if (cur->GetRight() == NULL) {//�����ϴ°� ���ڽĸ� ������
        if (par == NULL) { Root = cur->GetLeft(); }//�����ϴ°� ��Ʈ
        else if (par->GetLeft() == cur) { par->SetLeft(cur->GetLeft()); }//�����ϴ°� �θ� ����
        else { par->SetRight(cur->GetLeft()); }//�����ϴ°� �θ� ������
        cur = NULL; delete cur;
        return 1;
    }

    //�����ϴ°� �ڽ� 2��
    PatientBSTNode* pprev = cur;
    PatientBSTNode* prev = cur->GetLeft();//prev�� �����Ұ� ���� �ڽ�
    PatientBSTNode* c = cur->GetLeft()->GetRight();//�����Ұ� ���ڽ��� �����ڽĿ��� ����

    while (c) {
        pprev = prev;
        prev = c;
        c = c->GetRight();
    }//c�� NULL�Ǹ� prev�� ������� ���ڽ� �� ���� ū�� ����

    if (pprev == cur) {//�ٷ� c= NULL
        prev->SetRight(cur->GetRight());
        if (par == NULL) { Root = prev; }//������� ��Ʈ�϶�
        else if (par->GetLeft() == cur) { par->SetLeft(prev); }//�����ϴ°� �θ� ����
        else { par->SetRight(prev); }//�����ϴ°� �θ� ������
        cur = NULL; delete cur;
        return 1;
    }
    else {
        pprev->SetRight(prev->GetLeft());//������� �ڽ� �� ����ū�� �ö���ϱ� ū�� ���ڽ��� �ö���� �θ𿡰� ����
        prev->SetRight(cur->GetRight());//�ö���� ����� �����ڽ��� ��������� �����ڽ�����
        prev->SetLeft(cur->GetLeft());//�ö���� ����� ���ڽ��� ��������� ���ڽ�����
        if (par == NULL) { Root = prev; }
        else if (par->GetLeft() == cur) { par->SetLeft(prev); }//�����ϴ°� �θ� ����
        else { par->SetRight(prev); }//�����ϴ°� �θ� ������
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
        Print_PRE(node->GetLeft());//Print_PRE�� node�� left����
        Print_PRE(node->GetRight());//Print_PRE�� node�� right����
    }
}

void PatientBST::Print_IN(PatientBSTNode* node)
{
    //PRINT B IN
    if (node != NULL) {

        Print_IN(node->GetLeft());//Print_IN�� node�� left����
        ofstream flog;
        flog.open("log.txt", ios::app);
        flog << node->GetName() << "/" << node->GetDisease() << endl;
        cout << node->GetName() << "/" << node->GetDisease() << endl;
        Print_IN(node->GetRight());//Print_IN�� node�� right����
    }
}

void PatientBST::Print_POST(PatientBSTNode* node)
{
    //PRINT B POST
    if (node != NULL) {
        Print_POST(node->GetLeft());//Print_POST�� node�� left����
        Print_POST(node->GetRight());//Print_POST�� node�� right����
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
        if (cur->GetLeft()) { q.push(cur->GetLeft()); }//queue�� cur�� left push
        if (cur->GetRight()) { q.push(cur->GetRight()); } // queue�� cur�� right push
        if (q.empty()) { return; }//queue�� ��������� ����
        cur = q.front();//cur�� queue�� ���� �� ���ҷ� ����
        q.pop();//queue�� ù��° ���� pop
    }
}
