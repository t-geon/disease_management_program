#include<cstring>
#include<iostream>
#include "LocationBST.h"
#pragma warning(disable:4996)

LocationBST::LocationBST()
{
    Root = new LocationNode;//root����

    //���ָ� root�� �ʱ�ȭ
    LocationNode* gwangju = new LocationNode;
    char* ltemp = new char[16];
    strcpy(ltemp, "Gwangju");
    gwangju->SetLoc(ltemp);
    Insert_Location(gwangju);
}

LocationBST::~LocationBST()
{
    delete Root;
}

LocationNode* LocationBST::GetRoot()
{
    return Root;
}

void LocationBST::Insert_Location(LocationNode* node)
{
    //�ڷῡ �־��� ���Ĵ�� LocationBST �ʱ�ȭ
    Root = node;//Root�� ����
    LocationNode* daegu = new LocationNode;
    LocationNode* seoul = new LocationNode;
    LocationNode* busan = new LocationNode;
    LocationNode* daejeon = new LocationNode;
    LocationNode* incheon = new LocationNode;
    LocationNode* ulsan = new LocationNode;

    //location node���� �� �� location �̸��� �ʱ�ȭ�ϰ� �˸´�
    char* ltemp = new char[16];
    strcpy(ltemp, "Daegu");
    daegu->SetLoc(ltemp);
    Root->SetLeft(daegu);//�뱸�� ������ ����

    strcpy(ltemp, "Seoul");
    seoul->SetLoc(ltemp);
    Root->SetRight(seoul);//������ ������ ������

    strcpy(ltemp, "Busan");
    busan->SetLoc(ltemp);
    daegu->SetLeft(busan);//�λ��� �뱸�� ����

    strcpy(ltemp, "Daejeon");
    daejeon->SetLoc(ltemp);
    daegu->SetRight(daejeon);//������ �뱸�� ������

    strcpy(ltemp, "Incheon");
    incheon->SetLoc(ltemp);
    seoul->SetLeft(incheon);//��õ�� ������ ����

    strcpy(ltemp, "Ulsan");
    ulsan->SetLoc(ltemp);
    seoul->SetRight(ulsan);//����� ������ ������

}

bool LocationBST::Insert_Patient(PatientNode* node)
{
    //QPOP
    LocationNode* cur = Root;//cur�� root�� ����

    while (cur != NULL) {
        if (!strcmp(node->GetLoc(), cur->GetLoc())) {//ȯ�� ������ ������尡 ������
            cur->GetBST()->Insert(node);//�� ����bst�� ����
            return 1;
        }
        else if (cur->GetLoc()[0] > node->GetLoc()[0]) { cur = cur->GetLeft(); }//ȯ�������� ������庸�� ������ cur=cur->left
        else { cur = cur->GetRight(); }//ȯ�������� ���� ��庸�� ũ�� cur=xur->right
    }
    return 0;
}

bool LocationBST::Search(char* name)
{
    //SEARCH
    //��� ������ �̸��� ������ ã�´�.
    if (Root->GetBST()->Search(name)) { return 1; }//Gwangju
    else if (Root->GetLeft()->GetBST()->Search(name)) { return 1; }//Daegu
    else if (Root->GetLeft()->GetLeft()->GetBST()->Search(name)) { return 1; }//Busan
    else if (Root->GetRight()->GetBST()->Search(name)) { return 1; }//Seoul
    else if (Root->GetRight()->GetRight()->GetBST()->Search(name)) { return 1; }//Ulsan
    else if (Root->GetRight()->GetLeft()->GetBST()->Search(name)) { return 1; }//Inceon
    else if (Root->GetLeft()->GetRight()->GetBST()->Search(name)) { return 1; }//Daejeon
    return 0;
}

char* LocationBST::Delete(char* name)
{
    //BPOP
    //��� ������ �̸��� ������ �����Ѵ�.
    if (Root->GetBST()->Delete(name)) { return Root->GetLoc(); }//Gwangju
    else if (Root->GetLeft()->GetBST()->Delete(name)) { return Root->GetLeft()->GetLoc(); }//Daegu
    else if (Root->GetLeft()->GetLeft()->GetBST()->Delete(name)) { return Root->GetLeft()->GetLeft()->GetLoc(); }//Busan
    else if (Root->GetRight()->GetBST()->Delete(name)) { return Root->GetRight()->GetLoc(); }//Seoul
    else if (Root->GetRight()->GetRight()->GetBST()->Delete(name)) { return Root->GetRight()->GetRight()->GetLoc(); }//Ulsan
    else if (Root->GetRight()->GetLeft()->GetBST()->Delete(name)) { return Root->GetRight()->GetLeft()->GetLoc(); }//Inceon
    else if (Root->GetLeft()->GetRight()->GetBST()->Delete(name)) { return Root->GetLeft()->GetRight()->GetLoc(); }//Daejeon
    return 0;
}

void LocationBST::Print_PRE()
{
    //PRINT B PRE
    preorder(Root);
}

void LocationBST::Print_IN()
{
    //PRINT B IN
    inorder(Root);
}

void LocationBST::Print_POST()
{
    //PRINT B POST
    postorder(Root);
}

void LocationBST::Print_LEVEL()
{
    //PRINT B LEVEL
    queue< LocationNode*>q;
    LocationNode* cur = Root;
    while (cur) {
        cur->GetBST()->Print_LEVEL();
        if (cur->GetLeft()) { q.push(cur->GetLeft()); }//queue�� cur�� left push
        if (cur->GetRight()) { q.push(cur->GetRight()); }//queue�� cur�� right push
        if (q.empty()) { return; }//�� queue�̸� ����
        cur = q.front();//cur�� queue�� ���� �� ���� ����
        q.pop();//queue�� ���� �� ���� pop
    }

}

void LocationBST::preorder(LocationNode* lo) {

    if (lo != NULL) {
        lo->GetBST()->Print_PRE(lo->GetBST()->GetRoot());
        preorder(lo->GetLeft());//preorder�� lo�� left����
        preorder(lo->GetRight());//preorder�� lo�� right����
    }
}
void LocationBST::inorder(LocationNode* lo) {
    if (lo != NULL) {
        inorder(lo->GetLeft());//inorder�� lo�� left����
        lo->GetBST()->Print_IN(lo->GetBST()->GetRoot());
        inorder(lo->GetRight());//inorder�� lo�� right����
    }
}
void LocationBST::postorder(LocationNode* lo) {
    if (lo != NULL) {
        postorder(lo->GetLeft());//postorder�� lo�� left����
        postorder(lo->GetRight());//postorder�� lo�� right����
        lo->GetBST()->Print_POST(lo->GetBST()->GetRoot());
    }
}