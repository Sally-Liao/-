#include<iostream>
#include<cstring> 
#include<stdlib.h>
using namespace std;
const int MAXSIZE = 200; 
const int OK = 1;
const int ERROR = 0;
typedef int Status;
 
typedef struct peoNode{  
	char name[10];//���� 
	char id[20];//���֤�� 
	int planeNumber;//������ 
	peoNode *next;//ָ���� 
}peoNode,*people;//�˿ͽ�� 

typedef struct plaNode   //�ɻ�
{
    int planeNumber;//��� 
    char startPlace[20];//��� 
    char finishPlace[20];//�յ� 
    int seat;//��λ�� 
    int sold;//����Ʊ�� 
    char startTime[20];//���ʱ�� 
    int price;//Ʊ�� 
    plaNode *next;//ָ���� 
    people peo;//�˿�������ָ��˿������ͷָ�� 
}plaNode,*plane;//������ 

//����ȫ��ָ�����pla��peo����������ͳ˿�����
plaNode *pla;
peoNode *peo;

//��ʼ���˿�����,¼��˿���Ϣ�󽫳˿ͽ����������
//ͨ��ָ��peo���ڴ����ҵ��ýڵ㣬�����ý���next����Ϊ�գ��γ�һ����ͷ���Ŀ�����
Status initPeople(){
	peo = (peoNode *) malloc(sizeof(peoNode));//������Ŀռ�
	peo->next = NULL;//��ʼ����Ϊ0�ĵ����� 
}

//��ʼ����������,¼�뺽����Ϣ����������������
Status initPlane(){
	pla = (plaNode *) malloc(sizeof(plaNode));//������Ŀռ�
    pla->next = NULL;//��ʼ����Ϊ0�ĵ����� 
} 


/*
��Ӻ��� 
����һ���µĽ��s�����뺽����Ϣ�����*p��ָ����ָ����*s 
*/
Status addPlane(){
	plaNode *p = pla;
	plaNode *s; 
	s = (plaNode *) malloc(sizeof(plaNode));//��s����ռ� 
	
	cout<<"�����뺽����Ϣ��"<<endl;
	/*���*s��������*/ 
    cout<<"�����뺽���ţ�"<<endl;
    cin>>s->planeNumber;
    cout<<"�����뺽����㣺"<<endl;
    cin>>s->startPlace;
    cout<<"�����뺽���յ㣺"<<endl;
    cin>>s->finishPlace;
    cout<<"��������λ��"<<endl;
    cin>>s->seat;
    cout<<"����������Ʊ��"<<endl;
    cin>>s->sold;
    cout<<"���������ʱ��"<<endl;
    cin>>s->startTime;
    cout<<"������Ʊ��"<<endl;
    cin>>s->price; 
    	
	s->next = p->next;//������һ����� 
	p->next = s;//�����*p��ָ����ָ����*s ����s����Ϣ����p���� 
		
	
	return OK;
}

/*
//��ѯ���� 
���뺽�������յ�,whileѭ���������в��ң��ҵ���Ӧ�����
���������Ϣ�����������δ�ҵ��ú��ࡱ��
*/
Status searchPlane(){
	char startplace[20];//��� 
    char finishplace[20];//�յ� 
    int flag = 0;//Ѱ�Һ���ʱ����� 
    cout<<"������Ҫ��ѯ�ĺ�����㣺";
	cin>>startplace;
    cout<<"������Ҫ��ѯ�ĺ����յ㣺";
    cin>>finishplace;
    plaNode *p;
    p = pla->next;//pָ����Ԫ��� 
    while(p != NULL){//��ǰ����ָ��p��Ϊ�գ�������
    	if(strcmp(p->startPlace,startplace )==0 && strcmp(p->finishPlace,finishplace)==0){//p��ָ���������������յ���ڶ�ֵ 
    		flag = 1;
    		cout<<"������ϢΪ��"<<endl;
			cout<<"�����ţ�"<<p->planeNumber<<endl;
        	cout<<"������㣺"<<p->startPlace<<endl;
        	cout<<"�����յ㣺"<<p->finishPlace<<endl;
        	cout<<"��λ��"<<p->seat<<endl;
        	cout<<"����Ʊ��"<<p->sold<<endl;
        	cout<<"���ʱ��"<<p->startTime<<endl;
        	cout<<"Ʊ��"<<p->price<<endl<<endl;;
		}
        p = p->next;//pָ����һ����� 
	}
	if(flag == 0){
		cout << "δ�ҵ��ú���"<<endl;
	}
	return OK; 
}

/*�޸ĺ���
����Ҫ�޸ĵĺ���ı�ţ������޸ĺ����Ϣ��
whileѭ�����ң��ҵ���ֱ���޸�������
*/
Status updataPlane(){
	int planenumber;//��� 
    char startplace[20];//��� 
    char finishplace[20];//�յ� 
    int seat;//��λ�� 
    int sold;//����Ʊ�� 
    char starttime[20];//���ʱ�� 
    int price;//Ʊ�� 
    
	cout<<"������Ҫ�޸ĵĺ����ţ�";
	cin>>planenumber;
	
	cout<<"�����뺽����Ϣ��"<<endl;
    cout<<"�����뺽����㣺"<<endl;
    cin>>startplace;
    cout<<"�����뺽���յ㣺"<<endl;
    cin>>finishplace;
    cout<<"��������λ��"<<endl;
   	cin>>seat;
    cout<<"����������Ʊ��"<<endl;
    cin>>sold;
    cout<<"���������ʱ��"<<endl;
    cin>>starttime;
    cout<<"������Ʊ��"<<endl;
    cin>>price;
	struct plaNode *p;
	p = pla->next;//pָ����Ԫ��� 
	while(p != NULL){//��ǰ����ָ��p��Ϊ�գ�������
		if(p->planeNumber == planenumber){//p��ָ���ı�����ʱ 
			/* ֱ���޸�p�������򣬽���ֵ����p */
    		strcpy(p->startPlace,startplace);
    		strcpy(p->finishPlace,finishplace);
    		p->seat = seat;
    		p->sold = sold;
    		strcpy(p->startTime,starttime);
    		p->price = price;
		}	
		p = p->next;	//pָ����һ����� 
	} 
    
	return OK;
}

/*�˿Ͷ�Ʊ
���뺽���ţ��˿����������֤�ţ�while���Һ��࣬
����һ���µĽ��s�����*p��ָ����ָ����*s
*/
Status buyTicket(){
	int planenumber;//��� 
	char name[10];//���� 
	char id[20];//���֤��
	int flag = 0;//������ʱ����� 
	cout<<"�����뺽���ţ�"<<endl;
    cin>>planenumber;
    plaNode *p;
	p = pla->next; 
	if(p == NULL)
	{
		cout<<"δ�ҵ��ú���"<<endl;
		return 0;
	}
	while(p != NULL)
	{
		
		if(p->planeNumber == planenumber){//�ҵ�������ֹѭ�� 
			if(p->seat == p->sold ){//�жϺ����Ƿ����� 
				flag = 1;
				cout<<"�ú�����������ѡ���������࣡"<<endl; 
			}
			break;
		}
		p=p->next;
	}
	if(flag == 0){//����δ�� 
		peoNode *q = peo,*s;
		s = (peoNode *) malloc(sizeof(peoNode));//��s����ռ� 
		cout<<"������������Ϣ��"<<endl;
		cout<<"����������������"<<endl;
		cin>>s->name;
		cout<<"�������������֤�ţ�"<<endl;
		cin>>s->id;
		s->planeNumber = planenumber;
		s->next = q->next;
		q->next = s;//�����*q��ָ����ָ����*s 
		cout<<"��Ʊ�ɹ�!"<<endl;
		p->sold++;//����Ʊ����1 
	} 
	return OK;
}

/*�˿���Ʊ
����Ҫ�˵ĺ����źͳ˿����֤�ţ�whileѭ���ڳ˿������в��ң�
�ҵ�������һ����ʱ���p��������е���Ϣ��ʱ������p�У��ͷŽ�㣬
�ڰѴ���p�е���Ϣ����q����qָ����һ�����
*/
Status returnTicket(){
	int planenumber;//��� 
	char id[20];//���֤��
	int flag1 = 0;//Ѱ�Һ���ʱ����� 
	int flag2 = 0;//Ѱ�ҵ���ʱ����� 
	cout<<"���������ĺ����ţ�"<<endl;
    cin>>planenumber;
    cout<<"�������������֤�ţ�"<<endl;
    cin>>id;
	people p = peo;
	people q = p->next;
	
	while(q != NULL){
		if(q->planeNumber == planenumber){
			flag1 = 1;//�ҵ����� 
			if(strcmp(q->id,id)==0) {
				flag2 = 1;//�ҵ��� 
				p->next = q->next;//������е���Ϣ��ʱ������p��
				free(q);//�ͷŽ��q 

				cout<<"��Ʊ�ɹ���"<<endl; 
			}			
		}
		p = q;//��q��ֵ 
		q = q->next;//ָ����һ�ڵ� 
		
	}
	if(flag1 == 0){
		cout<<"δ�ҵ��ú��࣡"<<endl;
		return 0;
	}
	if(flag2 == 0){
		cout<<"δ�ҵ��ó˿���Ϣ��"<<endl;
		return 0;
	}
	return OK;
}

/*
Ʊ����Ϣ��ѯ
���뺽���ţ�whileѭ���ڳ˿������в��ң�
�ҵ�������˿���Ϣ 
*/
Status searchPeople(){
	int planenumber;
	int flag = 0;
	cout<<"�����뺽��ţ�";
	cin>>planenumber;
	cout<<"�˿���Ϣ���£�"<<endl;
	struct peoNode *p;
	p = peo->next;
	while(p != NULL){
		if(p->planeNumber == planenumber){
			flag = 1;
			cout<<"������"<<p->name<<endl;
			cout<<"���֤�ţ�"<<p->id<<endl;
			cout<<endl;
		}
		p = p->next; //ָ����һ����� 
	} 
	if(flag == 0){
		cout<<"�����ڸú����ú������ˣ�"<<endl; 
		return 0;
	}
	return OK;
}

void menu(){
	cout<<endl; 
	cout<<"**********************************"<<endl;
	cout<<"*****  ��ӭʹ�û�Ʊ����ϵͳ  *****"<<endl;
	cout<<"*****     1. ��Ӻ�����Ϣ    *****"<<endl;
	cout<<"*****     2. ��ѯ������Ϣ    *****"<<endl;
	cout<<"*****     3. �޸ĺ�����Ϣ    *****"<<endl;
	cout<<"*****     4. �ͻ���Ʊ        *****"<<endl;
	cout<<"*****     5. �ͻ���Ʊ        *****"<<endl;
	cout<<"*****     6. Ʊ����Ϣ��ѯ    *****"<<endl;
	cout<<"*****     0. �˳�ϵͳ        *****"<<endl;
	cout<<"**********************************"<<endl;
	cout<<endl; 
}

int main(){
	initPlane();
	initPeople();
	while(1){
		menu();
		int choice;
		cout<<"��ѡ��";
		cin>>choice;
		cout<<endl;
		
		switch(choice){
			case 1:
				addPlane();
				cout<<"������Ϣ�ɹ�¼��!";
            	cout<<endl;
            	break;
            case 2:
            	searchPlane();
            	cout<<endl;
            	break;
            case 3:
            	updataPlane();
            	cout<<"������Ϣ�޸ĳɹ�!";
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














