#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include<ctime>

using namespace std;
using std::string;

typedef struct ListNode
{
    int nVal;
    struct ListNode *pNext, *pLast;
} Lnode, *LinkList;

typedef struct List
{
    LinkList Head; // 指向链表节点的指针
    LinkList Tail;
} nodelist,*Listpoint;

// 头插法
bool insertNode(LinkList plist, int nVal)
{
    // if(nVal)return false;
    LinkList p = plist, s;
    if (plist == NULL)
        return false;
    s = (LinkList)malloc(sizeof(Lnode));
    s->nVal = nVal;
    s->pNext = p->pNext;

    s->pLast = p;
    s->pNext->pLast = s;

    p->pNext = s;
    return true;
}
// 头删除
bool deleteNode(LinkList plist)
{
    LinkList p = plist, q;
    if (plist->pNext == NULL)
        return false;
    q = p->pNext;
    q->pLast->pNext = q->pNext;
    if (q->pNext!=NULL){
        q->pNext->pLast = q->pLast;
    }
    free(q);
    return true;
}


/******************************************************************/

// 双向遍历
void traverse(Listpoint myList, int dir)
{
    /*合法性验证*/
    try
    {
        if (dir != 0 && dir != 1)
        {
            throw runtime_error("dir  should be 0 or 1 !");
        }
        if (myList->Head->pNext == NULL)
        {
            throw runtime_error("list  is null !");
        }
    }
    catch (runtime_error e)
    {
        cout << e.what() << endl;
        exit(1);
    }
    cout << "dir:" << dir << endl;
     if(dir==0){
        LinkList p = myList->Head->pNext;
        while (p != NULL)
        {
            cout << "p val:" << p->nVal << endl;
            p = p->pNext;
        }
     }
     else if(dir==1){
        for(LinkList p=myList->Tail;p->nVal!=NULL;p=p->pLast){
            cout << "p val:" << p->nVal << endl;
        }
     }

}

// 初始化链表
void initList(Listpoint &myList, int length)
{
    srand(time(0));
    LinkList pHead = (LinkList)malloc(sizeof(Lnode));
    LinkList pPre = (LinkList)malloc(sizeof(Lnode));
    LinkList p = (LinkList)malloc(sizeof(Lnode));

    pHead->nVal = NULL;
    pHead->pLast = NULL;
    pPre = pHead;

    for (int i = 0; i < length; i++)
    {
        p = (LinkList)malloc(sizeof(Lnode));
        //p->nVal = i + 1;
        p->nVal = rand() % 100;
        //cout << "p->nVal" << p->nVal << endl;
        p->pNext = NULL;
        p->pLast = pPre;
        pPre->pNext = p;
        pPre = p;
    }
    myList->Head = pHead;
    myList->Tail = pPre;
}

//添加节点
bool addNode(Listpoint &plist,int nVal){
    if(plist==NULL){
        cout<<"list not exist"<<endl;
        return false;
        }

    ListNode *s=new ListNode;
    s->nVal=nVal;
    s->pNext=NULL;

    plist->Tail->pNext=s;
    s->pLast=plist->Tail;
    plist->Tail=plist->Tail->pNext;
    return true;
}

//删除节点
bool delNode(Listpoint &plist){
    if(plist->Head==plist->Tail){
        cout<<"list is empty,delete failed"<<endl;
        return false;
    }
    ListNode *s=new ListNode;
    s=plist->Tail;

    plist->Tail=plist->Tail->pLast;
    plist->Tail->pNext=NULL;

    free(s);
    return true;
}

//链表保存到文件
void savelist(Listpoint myList){
    std::ofstream outFile("data.txt");
    if (outFile.is_open()){
        for(LinkList p=myList->Head->pNext;p!=NULL;p=p->pNext){
            outFile<<p->nVal<<endl;
        }
        outFile.close();
    }
    else{
        cout<<"write failed"<<endl;
        return;
    }
}

//从数据文件中读取数据并创建链表
void readlist(Listpoint myList){
    std::ifstream inFile("data.txt");
    int nVal;
    std::string string;
    ListNode *s=new ListNode;

    if(inFile.is_open()){
        myList->Tail=myList->Head;
        while (getline(inFile,string))
        {
            //cout<<stoi(string)<<endl;
            addNode(myList,stoi(string));
        }
    }
    else{
        cout<<"read failed"<<endl;
        return;
    }
}

//添加节点(指定索引)
bool addNode_index(Listpoint &myList,int nVal,int index){
    if(index<=0){
        cout<<"illegal add index"<<endl;
        return false;
    }
    LinkList pIndex = myList->Head;
    int i=0;
    while (pIndex && i<index){//get pIndex
        pIndex=pIndex->pNext;
        i++;
    }
    if (pIndex==NULL)//index>=len+1
    {    
        if(i==index){//index==len+1
            addNode(myList,nVal);//第11
            return true;
        }
        else{//index>len+1
            cout<<"illegal add index"<<endl;
            return false;
        }
    }
    LinkList pAssert = new Lnode;
    pAssert->nVal=nVal;

    pAssert->pLast=pIndex->pLast;//将pAssert插入pIndex之前
    pIndex->pLast->pNext=pAssert;
    pAssert->pNext=pIndex;
    pIndex->pLast=pAssert;
    return true;
}

//删除节点(指定索引)
bool delNode_index(Listpoint &myList,int index){
    if(index<=0){
        cout<<"illegal delete index"<<endl;
        return false;
    }
    LinkList pIndex=myList->Head;
    int i=0;
    while (i<index && pIndex->pNext)//get pIndex
    { 
        pIndex=pIndex->pNext;
        i++;
    }
    if(i<index){//index>len
        cout<<"illegal delete index"<<endl;
        return false;
    }
    if(pIndex->pNext==NULL){//index==len
        delNode(myList);
        return true;
    }
    else{//index<len
        pIndex->pLast->pNext=pIndex->pNext;
        pIndex->pNext->pLast=pIndex->pLast;
        free(pIndex);
        return true;
    }
}

int main()
{
    //LinkList p0, pListHead, pListTail, p;
    Listpoint myList=new List;
    Listpoint readformfileList=new List;

    initList(myList, 10);
    traverse(myList, 0);

    delNode(myList);
    traverse(myList, 0);

    delNode_index(myList,9);
    traverse(myList, 0);
    delNode_index(myList,1);
    traverse(myList, 0);

    addNode(myList,100);
    traverse(myList, 0);

    addNode_index(myList,100,1);
    traverse(myList, 0);
    addNode_index(myList,100,10);

    traverse(myList, 0);
    traverse(myList, 1);

    savelist(myList);

    readlist(myList);
    traverse(myList, 0);

    cout << "hello vscode" << endl;
    return 0;
}