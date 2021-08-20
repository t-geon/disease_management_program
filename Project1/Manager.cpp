#include "Manager.h"
#include<iostream>
#include <fstream>
#include<queue>
#include<string>
#include<cstring>
Manager::Manager()
{
    ds_queue = new queue<PatientNode*>;
    ds_bst = new LocationBST;
    ds_heap = new LocationHeap[10];
}

Manager::~Manager()
{
}

void Manager::run(const char* command)
{
    fin.open(command);//command.txt open
    flog.open("log.txt", ios::app);//log.txt open
    if (!fin)//빈 파일이면 오류 출력
    {
        flog << "File Open Error" << endl;
        return;
    }

    char cmd[32];

    while (!fin.eof())
    {
        fin.getline(cmd, 32);//command.txt 1줄 읽기
        char* tmp;
        strtok_s(cmd, " ", &tmp);//" "기준으로 앞에 문자 cmd에 저장 남은 문자 tmp의 주소에 저장
        if (!strcmp(cmd, "LOAD"))
        {
            if (LOAD()) { PrintSuccess(cmd); }//성공했으면 success출력
            else { PrintErrorCode(100); }//실패했으면 error출력
        }

        else if (!strcmp(cmd, "ADD")) {
            if (ADD(tmp)) { PrintSuccess(cmd); }//성공했으면 success출력
            else { PrintErrorCode(200); }//실패했으면 error출력
        }

        else if (!strcmp(cmd, "QPOP")) {
            if (QPOP(stoi(tmp))) { PrintSuccess(cmd); }//성공했으면 success출력
            else { PrintErrorCode(300); }//실패했으면 error출력
        }

        else if (!strcmp(cmd, "SEARCH")) {//SEARCH에 남은 문자 전달
            SEARCH(tmp);
        }

        else if (!strcmp(cmd, "PRINT")) {//PRINT에 남은 문자 전달
            PRINT(tmp);
        }

        else if (!strcmp(cmd, "BPOP")) {
            if (BPOP(tmp)) { PrintSuccess(cmd); }//성공했으면 success출력
            else { PrintErrorCode(600); }//실패했으면 error출력
        }

        else if (!strcmp(cmd, "EXIT"))
        {
            PrintSuccess(cmd);//성공했으면 success출력
            break;
        }

        else
        {
            cout << "========== ERROR ==========" << endl;
            cout << "Command Error" << endl;
            cout << "===========================" << endl << endl;

            flog << "========== ERROR ==========" << endl;
            flog << "Command Error" << endl;
            flog << "===========================" << endl << endl;
        }
    }
    fin.close();
    flog.close();
}

bool Manager::LOAD()
{
    char t[100];
    char* tn;

    //open
    ifstream fin;//fin is a variable for reading notepad
    fin.open("data.txt");//read input.txt as fin
    if (!fin.is_open()) { return 0; }//Output when file open fails
    if (ln!= 0) { return 0; }//Return 0 if load has already been done

    while (fin.eof() == 0) {
        PatientNode* p = new PatientNode;
        fin.getline(t, 100);

        //Name
        strtok_s(t, " ", &tn);
        p->SetName(t);

        //Temperature
        float tem = strtof(tn, &tn);
        p->SetTemp(tem);

        //Cough
        p->SetCough(tn[1]);


        //Location
        strtok_s(tn, " ", &tn);
        p->SetLoc(tn);

        ds_queue->push(p);
    }
    ln = 1;
    return 1;
}

bool Manager::ADD(char* patient)
{
    char* tn;
    PatientNode* p = new PatientNode;

    strtok_s(patient, " ", &tn);
    if (!strcmp(tn, "")) { return 0; }
    p->SetName(patient);

    //Temperature
    float tem = strtof(tn, &tn);
    if (!strcmp(tn, "")) { return 0; }
    p->SetTemp(tem);

    //Cough
    p->SetCough(tn[1]);
    if (tn[2] == NULL) { return 0; }
    else if (tn[3] == 0) { return 0; }


    //Location
    strtok_s(tn, " ", &tn);
    p->SetLoc(tn);

    strtok_s(tn, " ", &tn);
    if (strcmp(tn, "")) { return 0; }

    ds_queue->push(p);
    return 1;
}

bool Manager::QPOP(int n)
{
    if (ds_queue->size() < n) { return 0; }//QPOP하려는 수보다 size가 작으면 종료
    for (int i = 0; i < n; i++) {//QPOP 숫자 만큼 반복
        ds_bst->Insert_Patient(ds_queue->front());
        ds_queue->pop();
    }
    return 1;
}

bool Manager::SEARCH(char* r)
{
    if (!ds_bst->Search(r)) { PrintErrorCode(400); return 0; }//SEARCH실패하면 ERROR출력 성공하면 찾은 환자 정보출력
    return 1;
}

bool Manager::PRINT(char* tt)
{
    char* tn;
    strtok_s(tt, " ", &tn);//받아온 문자열 " "기준으로 분할

    if (!strcmp(tt, "B")) {
        if (!strcmp(tn, "")) { PrintErrorCode(500); return 0; }//입력 정보가 부족하면 error출력, 종료
        tt = strtok_s(tn, " ", &tn);
        cout << "========== " << "PRINT" << " ==========" << endl << "BST" << endl;
        flog << "========== " << "PRINT" << " ==========" << endl << "BST" << endl;
        if (!strcmp(tt, "PRE")) { ds_bst->Print_PRE(); }
        else if (!strcmp(tt, "IN")) { ds_bst->Print_IN(); }
        else if (!strcmp(tt, "POST")) { ds_bst->Print_POST(); }
        else if (!strcmp(tt, "LEVEL")) { ds_bst->Print_LEVEL(); }
        else { PrintErrorCode(500); return 0; }
        cout << "============================" << endl << endl;
        flog << "============================" << endl << endl;
    }
    else if (!strcmp(tt, "H")) {
        if (ds_heap->Getsize() == 0) { PrintErrorCode(500); return 0; }//heap이 비어있으면 error출력, 종료
        cout << "========== " << "PRINT" << " ==========" << endl;
        flog << "========== " << "PRINT" << " ==========" << endl;
        ds_heap->Print();
        cout << "============================" << endl << endl;
        flog << "============================" << endl << endl;
    }
    else { PrintErrorCode(500); return 0; }
    return 1;
}

bool Manager::BPOP(char* name)
{
    char* lo = ds_bst->Delete(name);
    if (lo != NULL) { ds_heap->Insert(lo); return 1; }
    else { return 0; }
}

void Manager::PrintErrorCode(int num)
{
    cout << "========== ERROR ==========" << endl;
    cout << num << endl;
    cout << "===========================" << endl << endl;

    flog << "========== ERROR ==========" << endl;
    flog << num << endl;
    flog << "===========================" << endl << endl;
}

void Manager::PrintSuccess(char* act)
{
    cout << "========== " << act << " ==========" << endl;
    cout << "Success" << endl;
    cout << "============================" << endl << endl;

    flog << "========== " << act << " ==========" << endl;
    flog << "Success" << endl;
    flog << "============================" << endl << endl;
}
