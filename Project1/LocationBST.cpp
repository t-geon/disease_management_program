#include<cstring>
#include<iostream>
#include "LocationBST.h"
#pragma warning(disable:4996)

LocationBST::LocationBST()
{
    Root = new LocationNode;//root생성

    //광주를 root로 초기화
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
    //자료에 주어진 형식대로 LocationBST 초기화
    Root = node;//Root는 광주
    LocationNode* daegu = new LocationNode;
    LocationNode* seoul = new LocationNode;
    LocationNode* busan = new LocationNode;
    LocationNode* daejeon = new LocationNode;
    LocationNode* incheon = new LocationNode;
    LocationNode* ulsan = new LocationNode;

    //location node생성 후 각 location 이름을 초기화하고 알맞는
    char* ltemp = new char[16];
    strcpy(ltemp, "Daegu");
    daegu->SetLoc(ltemp);
    Root->SetLeft(daegu);//대구는 광주의 왼쪽

    strcpy(ltemp, "Seoul");
    seoul->SetLoc(ltemp);
    Root->SetRight(seoul);//서울은 광주의 오른쪽

    strcpy(ltemp, "Busan");
    busan->SetLoc(ltemp);
    daegu->SetLeft(busan);//부산은 대구의 왼쪽

    strcpy(ltemp, "Daejeon");
    daejeon->SetLoc(ltemp);
    daegu->SetRight(daejeon);//대전은 대구의 오른쪽

    strcpy(ltemp, "Incheon");
    incheon->SetLoc(ltemp);
    seoul->SetLeft(incheon);//인천은 서울의 왼쪽

    strcpy(ltemp, "Ulsan");
    ulsan->SetLoc(ltemp);
    seoul->SetRight(ulsan);//울산은 서울의 오른쪽

}

bool LocationBST::Insert_Patient(PatientNode* node)
{
    //QPOP
    LocationNode* cur = Root;//cur은 root로 시작

    while (cur != NULL) {
        if (!strcmp(node->GetLoc(), cur->GetLoc())) {//환자 지역과 지역노드가 같으면
            cur->GetBST()->Insert(node);//그 지역bst에 삽입
            return 1;
        }
        else if (cur->GetLoc()[0] > node->GetLoc()[0]) { cur = cur->GetLeft(); }//환자지역이 지역노드보다 작으면 cur=cur->left
        else { cur = cur->GetRight(); }//환자지역이 지역 노드보다 크면 cur=xur->right
    }
    return 0;
}

bool LocationBST::Search(char* name)
{
    //SEARCH
    //모든 지역에 이름을 전달해 찾는다.
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
    //모든 지역에 이름을 전달해 삭제한다.
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
        if (cur->GetLeft()) { q.push(cur->GetLeft()); }//queue에 cur의 left push
        if (cur->GetRight()) { q.push(cur->GetRight()); }//queue에 cur의 right push
        if (q.empty()) { return; }//빈 queue이면 종료
        cur = q.front();//cur에 queue의 제일 앞 원소 저장
        q.pop();//queue의 제일 앞 원소 pop
    }

}

void LocationBST::preorder(LocationNode* lo) {

    if (lo != NULL) {
        lo->GetBST()->Print_PRE(lo->GetBST()->GetRoot());
        preorder(lo->GetLeft());//preorder에 lo의 left전달
        preorder(lo->GetRight());//preorder에 lo의 right전달
    }
}
void LocationBST::inorder(LocationNode* lo) {
    if (lo != NULL) {
        inorder(lo->GetLeft());//inorder에 lo의 left전달
        lo->GetBST()->Print_IN(lo->GetBST()->GetRoot());
        inorder(lo->GetRight());//inorder에 lo의 right전달
    }
}
void LocationBST::postorder(LocationNode* lo) {
    if (lo != NULL) {
        postorder(lo->GetLeft());//postorder에 lo의 left전달
        postorder(lo->GetRight());//postorder에 lo의 right전달
        lo->GetBST()->Print_POST(lo->GetBST()->GetRoot());
    }
}