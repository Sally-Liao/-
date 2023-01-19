#include<iostream>
#include<cstring> 
#include<stdlib.h>
using namespace std;
const int MAXSIZE = 200; 
const int OK = 1;
const int ERROR = 0;
typedef int Status;
 
typedef struct peoNode{  
	char name[10];//姓名 
	char id[20];//身份证号 
	int planeNumber;//航班编号 
	peoNode *next;//指针域 
}peoNode,*people;//乘客结点 

typedef struct plaNode   //飞机
{
    int planeNumber;//编号 
    char startPlace[20];//起点 
    char finishPlace[20];//终点 
    int seat;//座位数 
    int sold;//已售票数 
    char startTime[20];//起飞时间 
    int price;//票价 
    plaNode *next;//指针域 
    people peo;//乘客名单域，指向乘客链表的头指针 
}plaNode,*plane;//航班结点 

//定义全局指针变量pla和peo，航班链表和乘客链表
plaNode *pla;
peoNode *peo;

//初始化乘客链表,录入乘客信息后将乘客结点插入该链表
//通过指针peo在内存中找到该节点，并将该结点的next域设为空，形成一个带头结点的空链表
Status initPeople(){
	peo = (peoNode *) malloc(sizeof(peoNode));//申请结点的空间
	peo->next = NULL;//初始长度为0的单链表 
}

//初始化航班链表,录入航班信息将航班结点插入该链表
Status initPlane(){
	pla = (plaNode *) malloc(sizeof(plaNode));//申请结点的空间
    pla->next = NULL;//初始长度为0的单链表 
} 


/*
添加航班 
生成一个新的结点s，输入航班信息，结点*p的指针域指向结点*s 
*/
Status addPlane(){
	plaNode *p = pla;
	plaNode *s; 
	s = (plaNode *) malloc(sizeof(plaNode));//给s申请空间 
	
	cout<<"请输入航班信息："<<endl;
	/*结点*s的数据域*/ 
    cout<<"请输入航班编号："<<endl;
    cin>>s->planeNumber;
    cout<<"请输入航班起点："<<endl;
    cin>>s->startPlace;
    cout<<"请输入航班终点："<<endl;
    cin>>s->finishPlace;
    cout<<"请输入座位数"<<endl;
    cin>>s->seat;
    cout<<"请输入已售票数"<<endl;
    cin>>s->sold;
    cout<<"请输入起飞时间"<<endl;
    cin>>s->startTime;
    cout<<"请输入票价"<<endl;
    cin>>s->price; 
    	
	s->next = p->next;//进入下一个结点 
	p->next = s;//将结点*p的指针域指向结点*s ，将s的信息传给p储存 
		
	
	return OK;
}

/*
//查询航班 
输入航班起点和终点,while循环在链表中查找，找到相应航班后
输出航班信息，否则输出“未找到该航班”。
*/
Status searchPlane(){
	char startplace[20];//起点 
    char finishplace[20];//终点 
    int flag = 0;//寻找航班时做标记 
    cout<<"请输入要查询的航班起点：";
	cin>>startplace;
    cout<<"请输入要查询的航班终点：";
    cin>>finishplace;
    plaNode *p;
    p = pla->next;//p指向首元结点 
    while(p != NULL){//当前结点的指针p不为空，向下找
    	if(strcmp(p->startPlace,startplace )==0 && strcmp(p->finishPlace,finishplace)==0){//p所指结点的数据域起点和终点等于定值 
    		flag = 1;
    		cout<<"航班信息为："<<endl;
			cout<<"航班编号："<<p->planeNumber<<endl;
        	cout<<"航班起点："<<p->startPlace<<endl;
        	cout<<"航班终点："<<p->finishPlace<<endl;
        	cout<<"座位数"<<p->seat<<endl;
        	cout<<"已售票数"<<p->sold<<endl;
        	cout<<"起飞时间"<<p->startTime<<endl;
        	cout<<"票价"<<p->price<<endl<<endl;;
		}
        p = p->next;//p指向下一个结点 
	}
	if(flag == 0){
		cout << "未找到该航班"<<endl;
	}
	return OK; 
}

/*修改航班
输入要修改的航班的编号，输入修改后的信息，
while循环查找，找到后直接修改数据域
*/
Status updataPlane(){
	int planenumber;//编号 
    char startplace[20];//起点 
    char finishplace[20];//终点 
    int seat;//座位数 
    int sold;//已售票数 
    char starttime[20];//起飞时间 
    int price;//票价 
    
	cout<<"请输入要修改的航班编号：";
	cin>>planenumber;
	
	cout<<"请输入航班信息："<<endl;
    cout<<"请输入航班起点："<<endl;
    cin>>startplace;
    cout<<"请输入航班终点："<<endl;
    cin>>finishplace;
    cout<<"请输入座位数"<<endl;
   	cin>>seat;
    cout<<"请输入已售票数"<<endl;
    cin>>sold;
    cout<<"请输入起飞时间"<<endl;
    cin>>starttime;
    cout<<"请输入票价"<<endl;
    cin>>price;
	struct plaNode *p;
	p = pla->next;//p指向首元结点 
	while(p != NULL){//当前结点的指针p不为空，向下找
		if(p->planeNumber == planenumber){//p所指结点的编号相等时 
			/* 直接修改p的数据域，将定值赋给p */
    		strcpy(p->startPlace,startplace);
    		strcpy(p->finishPlace,finishplace);
    		p->seat = seat;
    		p->sold = sold;
    		strcpy(p->startTime,starttime);
    		p->price = price;
		}	
		p = p->next;	//p指向下一个结点 
	} 
    
	return OK;
}

/*乘客订票
输入航班编号，乘客姓名、身份证号，while查找航班，
生成一个新的结点s，结点*p的指针域指向结点*s
*/
Status buyTicket(){
	int planenumber;//编号 
	char name[10];//姓名 
	char id[20];//身份证号
	int flag = 0;//航班满时做标记 
	cout<<"请输入航班编号："<<endl;
    cin>>planenumber;
    plaNode *p;
	p = pla->next; 
	if(p == NULL)
	{
		cout<<"未找到该航班"<<endl;
		return 0;
	}
	while(p != NULL)
	{
		
		if(p->planeNumber == planenumber){//找到航班终止循环 
			if(p->seat == p->sold ){//判断航班是否已满 
				flag = 1;
				cout<<"该航班已满，请选择其他航班！"<<endl; 
			}
			break;
		}
		p=p->next;
	}
	if(flag == 0){//航班未满 
		peoNode *q = peo,*s;
		s = (peoNode *) malloc(sizeof(peoNode));//给s申请空间 
		cout<<"请输入您的信息："<<endl;
		cout<<"请输入您的姓名："<<endl;
		cin>>s->name;
		cout<<"请输入您的身份证号："<<endl;
		cin>>s->id;
		s->planeNumber = planenumber;
		s->next = q->next;
		q->next = s;//将结点*q的指针域指向结点*s 
		cout<<"订票成功!"<<endl;
		p->sold++;//已售票数加1 
	} 
	return OK;
}

/*乘客退票
输入要退的航班编号和乘客身份证号，while循环在乘客链表中查找，
找到后，生成一个临时结点p，将结点中的信息临时保存在p中，释放结点，
在把存在p中的信息赋给q，让q指向下一个结点
*/
Status returnTicket(){
	int planenumber;//编号 
	char id[20];//身份证号
	int flag1 = 0;//寻找航班时做标记 
	int flag2 = 0;//寻找到人时做标记 
	cout<<"请输入您的航班编号："<<endl;
    cin>>planenumber;
    cout<<"请输入您的身份证号："<<endl;
    cin>>id;
	people p = peo;
	people q = p->next;
	
	while(q != NULL){
		if(q->planeNumber == planenumber){
			flag1 = 1;//找到航班 
			if(strcmp(q->id,id)==0) {
				flag2 = 1;//找到人 
				p->next = q->next;//将结点中的信息临时保存在p中
				free(q);//释放结点q 

				cout<<"退票成功！"<<endl; 
			}			
		}
		p = q;//给q赋值 
		q = q->next;//指向下一节点 
		
	}
	if(flag1 == 0){
		cout<<"未找到该航班！"<<endl;
		return 0;
	}
	if(flag2 == 0){
		cout<<"未找到该乘客信息！"<<endl;
		return 0;
	}
	return OK;
}

/*
票务信息查询
输入航班编号，while循环在乘客链表中查找，
找到后，输出乘客信息 
*/
Status searchPeople(){
	int planenumber;
	int flag = 0;
	cout<<"请输入航班号：";
	cin>>planenumber;
	cout<<"乘客信息如下："<<endl;
	struct peoNode *p;
	p = peo->next;
	while(p != NULL){
		if(p->planeNumber == planenumber){
			flag = 1;
			cout<<"姓名："<<p->name<<endl;
			cout<<"身份证号："<<p->id<<endl;
			cout<<endl;
		}
		p = p->next; //指向下一个结点 
	} 
	if(flag == 0){
		cout<<"不存在该航班或该航班无人！"<<endl; 
		return 0;
	}
	return OK;
}

void menu(){
	cout<<endl; 
	cout<<"**********************************"<<endl;
	cout<<"*****  欢迎使用机票管理系统  *****"<<endl;
	cout<<"*****     1. 添加航班信息    *****"<<endl;
	cout<<"*****     2. 查询航班信息    *****"<<endl;
	cout<<"*****     3. 修改航班信息    *****"<<endl;
	cout<<"*****     4. 客户订票        *****"<<endl;
	cout<<"*****     5. 客户退票        *****"<<endl;
	cout<<"*****     6. 票务信息查询    *****"<<endl;
	cout<<"*****     0. 退出系统        *****"<<endl;
	cout<<"**********************************"<<endl;
	cout<<endl; 
}

int main(){
	initPlane();
	initPeople();
	while(1){
		menu();
		int choice;
		cout<<"请选择：";
		cin>>choice;
		cout<<endl;
		
		switch(choice){
			case 1:
				addPlane();
				cout<<"航班信息成功录入!";
            	cout<<endl;
            	break;
            case 2:
            	searchPlane();
            	cout<<endl;
            	break;
            case 3:
            	updataPlane();
            	cout<<"航班信息修改成功!";
            	cout<<endl;
            	break;
            case 4:
            	buyTicket();
            	cout<<endl;
            	break;
            case 5:
            	returnTicket();
            	cout<<endl;
            	break;
            case 6:
            	searchPeople();
            	cout<<endl;
            	break;
            case 0:
            	exit(1);
            	break;
            default:
				break;
		} 
	}
	
	return 0;
}














