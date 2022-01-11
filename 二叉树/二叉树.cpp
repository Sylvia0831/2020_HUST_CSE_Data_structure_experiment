/*
����:������
�༶:�Ű�1901��
ѧ�ţ�U201911658
����:2020��11��5�� 
*/ 
#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<iostream>
#include<string.h>
#include<windows.h>

using namespace std;

#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define DestroyBiTree ClearBiTree    //���ٶ���������ն�����������ͬ 

typedef char ElemType;  //�ڵ��������� 
typedef int Status;   
typedef struct BNode{
	ElemType data;
	int weight;
	struct BNode* lchild; //ָ������
	struct BNode* rchild; //ָ���ֵ� 
}BNode;
typedef BNode* BTree;  
//p_e�����ŵ�i�ö������ĵ�ǰ�ڵ��ָ�룬array�������ڶ���������� 
BTree p_e[11]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},array[11]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //������������� 
ElemType str[2000];
int ii=0,jj=0,k=0;
int num=0;
//W�������ڹ���������������Ƶ�� 
int W[100]={1000,408,191,92,45,22,28,47,99,48,51,217,103,114,57,57,592,251,123,60,28,13,15,32,15,17,8,9,4,2,1,1,2,1,1,5,63,128,64,64,32,32,341,155,75,34,16,18,41,20,21,80,186};
char ans[201],anscode[201];
int code_[31][201]={}; 
int a[100];

void menu(void);
void Visit(ElemType e);
void setBTnum(int n); //29 ���õ�ǰ��������� 
void InitBiTree(BTree *T);  //1   ��ʼ��
Status CreateBiTree(BTree *T); //3 ���������� 
void ClearBiTree(BTree *T);    //4 ��ն����� 
Status BiTreeEmpty(BTree T); //5 �жϿն����� 
Status BiTreeDepth(BTree T); //6 ����������
ElemType Root(BTree T);  //7 ��ø��ڵ� 
BTree Order_Bi(BTree T,ElemType e); //����ָ��e�ڵ��ָ��
Status Value(BTree T,ElemType *e); //8 ��õ�ǰ�ڵ��ֵ???
Status Assign(BTree T,ElemType e,ElemType value);//9��㸳ֵ 
ElemType Parent(BTree T,ElemType e); //10 ���˫�� 
ElemType GetChild(BTree T,ElemType e,int order); //11&&12 �����Һ��� 
ElemType LeftChild(BTree T,ElemType e); //11   ���� 
ElemType RightChild(BTree T,ElemType e);  //12�Һ��� 
ElemType LeftSibling(BTree T,ElemType e);  //13 ���ֵ� 
ElemType RightSibling(BTree T,ElemType e);  //(13)  //14 ���ֵ�
Status InsertChild(BTree T,BTree p,char LR,int tnum); //15�������� 
Status DeleteChild(BTree T,BTree p,char LR);//16  ɾ������ 
void PreOrderTraverse(BTree T,void(Visit)());//17 ǰ����� 
void InOrderTraverse(BTree T,void(Visit)());//18 ������� 
void PostOrderTraverse(BTree T,void(Visit)());//19 ������� 
void LevelOrderTraverse(BTree T,void(Visit)());  //20 ������� 
Status CreateHTree(BTree F,BTree *T,char string1); //31 ������������ 
void HTreeCode(char string1[]); //32  ���б��� 
void HTreeDecode(char code[]);//33  �������� 
Status StringCheck(char string1[]);//34  ����-����-���� ��� 
Status CodeCheck(char code[]);//35  ����-����-���� ��� 
 

void Visit(ElemType e){  //����ʱ��� 
    printf("%c",e);
}
void setBTnum(int n){  //29  ���������
    num = n;
}
void InitBiTree(BTree *T){   // ��ʼ�������� 
    *T = NULL;
}
Status CreateBiTree(BTree *T,char str[]){  //���������� ��ʹ��ǰ��������� 
    char ch;
    ch = str[ii++];
    if (ch == '^')  //���ch��^,��ǰ�ڵ�ΪNULL 
        *T = NULL;
    else {  
        *T = (BTree)malloc(sizeof(BNode));//����һ���ڵ�ռ� 
		if (jj==0) array[num]= *T; //����Ǹ��ڵ㣬��Ѹ�ָ�������������������У����ں������� 
		jj++; //�����jj��ȫ�ֱ��������������е��øú���ʱ���и���ֵ0 ���������жϵ�ǰ�ڵ��ǲ��Ǹ��ڵ� 
        if(!(*T)) return  OVERFLOW;  //��ֹ��� 
        (*T)->data = ch;  //�Խڵ���������и�ֵ 
        CreateBiTree(&(*T)->lchild,str);  //�ݹ鴴�������� 
        CreateBiTree(&(*T)->rchild,str); //�ݹ鴴�������� 
    }
    return OK;
}
void ClearBiTree(BTree *T){  //��ն������������ٶ�����������ͬ 
    if (*T){
        if ((*T)->lchild) ClearBiTree(&(*T)->lchild);  //ֻҪ��������Ϊ�գ��ݹ����������� 
        if ((*T)->rchild) ClearBiTree(&(*T)->rchild);  // ֻҪ��������Ϊ�գ��ݹ����������� 
        free(*T);   //�ͷſռ� 
        *T = NULL;   
    }
}
Status BiTreeEmpty(BTree T){    //�жϿն����� 
    return T==NULL ? TRUE :FALSE;  //���ڵ�Ϊ���򷵻�TRUE 
}

Status BiTreeDepth(BTree T){  //��������� 
    if (T == NULL) return 0;  //�ݹ���ڣ���ǰ�ڵ�ΪNULL 
      else return max(1+BiTreeDepth(T->lchild),1+BiTreeDepth(T->rchild));  //�ݹ������ 
}

ElemType Root(BTree T){  //�����ĸ��ڵ� 
    if (T){ 
		p_e[num] = T;   //����������������ָʾ�ĸ��ڵ���ڣ��򷵻ظ��ڵ�������� 
        return T->data;
    }
    else
        return '^';  //��������Ϊ�� 
}

Status Value(BTree T,ElemType *e){  //��õ�ǰ�ڵ� 
    *e = p_e[num]->data; //ʹ��e���� 
    return OK;
}

Status Assign(BTree T,ElemType *e,ElemType value){//�ڵ㸳ֵ 
	*e = value;  
    return OK;
}
ElemType Parent(BTree T,ElemType e){ //10 ���˫��
    int i=0,j=0;
    BTree Q[100]={};  //ʹ�ö��� 
    if (T){   //������ڵ㲻Ϊ�գ��Ѹ��ڵ�������  
        Q[j++] = T;
    }
	if (Q[i]==p_e[num]) return '^';  //���ǡ�ø��ڵ��뵱ǰ�ڵ���ͬ����˵��û��˫�ף��Ѿ��Ǹ��ڵ㣬����NULL 
    while (i<j){
        if (Q[i]){  //ֻҪ���е�ǰ�Ĳ�Ϊ�� 
            if(Q[i]->lchild){  //������� 
				if(Q[i]->lchild->data == p_e[num]->data) {  //�����ӵ�ֵǡ���뵱ǰ�ڵ��ֵ��ͬ����˵�����е�ǰ�ڵ�Ϊ�丸�ڵ� 
					p_e[num] = Q[i];
					return Q[i]->data;  //���ظ��ڵ� 
				
				}
			}
			if (Q[i]->rchild){  //����Һ��Ӵ��� 
				if(Q[i]->rchild->data == p_e[num]->data){ // ���Һ��ӵ�ֵǡ���뵱ǰ�ڵ��ֵ��ͬ����˵�����е�ǰ�ڵ�Ϊ�丸�ڵ� 
					p_e[num] = Q[i];
					return Q[i]->data;  //���ظ��ڵ� 
				} 
			}
            Q[j++] = Q[i]->lchild;  //�����Ӽ������ 
            Q[j++] = Q[i]->rchild;  //���Һ��Ӽ������ 
        }
        i++;  //����һ�� 
    }
}

ElemType LeftChild(BTree T,ElemType *e){//11   ������
    if (p_e[num]->lchild) {  //ֻҪ��ǰ�ڵ�����Ӵ��� 
        p_e[num]=p_e[num]->lchild;  //�ѵ�ǰ�ڵ��޸�Ϊ������ 
        return p_e[num]->data;  //�������� 
    }
    return '^';  //û�����ӣ�����NULL 
}


ElemType RightChild(BTree T,ElemType e){// ���Һ��ӣ�˼��ͬ�� 
    if(p_e[num]->rchild){
        p_e[num] = p_e[num]->rchild;
        return p_e[num]->data;
    }
    return '^';
}

ElemType LeftSibling(BTree T,ElemType e)  //�����ֵ� 
{ 
	int i=0,j=0;
    BTree Q[100]; //ʹ�ö��� 
    if (T){
        Q[j++] = T;   //������ڵ� 
    }
    if(Q[i]->data==p_e[num]->data) return '^'; //������ڵ��뵱ǰ�ڵ���ͬ�������ֵܣ�����NULL 
    while (i<j){
        if (Q[i]){  //������в��� 
        	if(Q[i]->rchild==p_e[num]) { //�������Ԫ�ص��Һ����뵱ǰ�ڵ���ͬ 
        		if (Q[i]->lchild) {  //�鿴�Ƿ������� 
        			p_e[num] = Q[i]->lchild;  //��������ӣ�����ҳɹ� 
        			return p_e[num]->data;  //���������ֵ� 
        		}
        		else return '^';  //���û�����ӣ�˵��û�����ֵ� 
        	}
        	if(Q[i]->lchild==p_e[num]) return '^';  //���Ҫ���ҵĽڵ�����е�ǰԪ�ص�������ȣ������Ȼû�����ֵܣ�����NULL 
            Q[j++] = Q[i]->lchild;  //���Ӽ������ 
            Q[j++] = Q[i]->rchild; //�Һ��Ӽ������ 
        }
        i++;  //����һ�� 
       
    }

}
ElemType RightSibling(BTree T,ElemType e){  //�����ֵܣ�˼��ͬ�� 
	int i=0,j=0;
    BTree Q[100];
    if (T){
        Q[j++] = T;
    }
    if(Q[i]->data==p_e[num]->data) return '^'; //������ڵ��뵱ǰ�ڵ���ͬ�������ֵܣ�����NULL 
    while (i<j){
        if (Q[i]){
        	if(Q[i]->lchild==p_e[num]) {
        		if (Q[i]->rchild) {
        			p_e[num] = Q[i]->rchild;
        			return p_e[num]->data;
        		}
        		else return '^';
        	}
        	if(Q[i]->rchild==p_e[num]) return '^';
            Q[j++] = Q[i]->lchild;
            Q[j++]=Q[i]->rchild;
        }
        i++;
    }
}
Status InsertChild(BTree T,BTree p,char LR,int tnum){  //�������� 
 BTree tp=p_e[num],temp=NULL,childtree=array[tnum];
	switch (LR){
		case 'L':{  
			if (p->lchild){  //���������������ڣ��������Ҫ�������������������  
				temp = p->lchild;
				p_e[num]->lchild = array[tnum];
				childtree->rchild = temp;
				array[tnum]= NULL;  //���������б���ɾ�� 
			}
			else {  //���������Ϊ�գ���ֱ�Ӳ��� 
				p_e[num]->lchild = array[tnum];
				array[tnum] = NULL;  //���������б���ɾ�� 
			}
			break;
		}
		case 'R':{     //˼��ͬ�� 
			if (p->rchild){  
				temp = p->rchild;
				p_e[num]->rchild = array[tnum];
				childtree->rchild = temp;
				array[tnum]= NULL;
			}
			else {
				p_e[num]->rchild = array[tnum];
				array[tnum] = NULL;
			}
			break;
		}
	}
}

Status DeleteChild(BTree T,BTree p,char LR)//16  ɾ������ 
{
	switch(LR){
		case 'L':{
			ClearBiTree(&p->lchild); //��������� 
			break;
		}
		case 'R':{
			ClearBiTree(&p->rchild);  //��������� 
			break;
		}
	}
	
}
void PreOrderTraverse(BTree T,void(Visit)(ElemType)){//ǰ����� �ݹ� 
    if(T){
        Visit(T->data);  //���ڵ� 
        PreOrderTraverse(T->lchild,Visit);  //���� 
        PreOrderTraverse(T->rchild,Visit);//�Һ��� 
    }
}
Status InOrderTraverse(BTree T,void(Visit)(ElemType)){//������� �ǵݹ� 
    BTree S[100];  //ʹ��ջ 
    int top = 0;  //ջ�� 
    do{
        while(T){  //ֻҪ��ǰ�ڵ㲻Ϊ�� 
            if(top == 100) return OVERFLOW;  //ջ��� 
            S[top++] =T; //������ջ�� 
            T= T->lchild;  //�����ӣ������������ �� �� �� �� 
        }
        if (top){  //���ջ��Ϊ�� 
            T = S[--top];  //ջ��Ԫ�ص���ջ 
            Visit(T->data);  
            T = T->rchild;  //���Һ��� 
        }
    }while(top||T);   //ֻҪ�ڵ㲻Ϊ�ջ�ջ��Ϊ�� 
    return OK;
}
void PostOrderTraverse(BTree T,void(Visit)(ElemType))//19�������� 
{
    if(T){
        PostOrderTraverse(T->lchild,Visit);  //�� 
        PostOrderTraverse(T->rchild,Visit); //�� 
        Visit(T->data);  //�� 
    }
}
void LevelOrderTraverse(BTree T,void(Visit)(ElemType)){  //������� 
    int i=0,j=0;
    BTree Q[100]={};  //ʹ�ö��� 
    if (T){
        Q[j++] = T;  //���ڵ��������� 
    }
    while (i<j){
        if (Q[i]){
            Visit(Q[i]->data);  //��� 
            Q[j++] = Q[i]->lchild; //������ 
            Q[j++] = Q[i]->rchild;  //���Һ���  ������һ��ļ���  
        }
        i++;
    }
    printf("\n");
}
Status CreateHTree(BTree F,BTree *T,char string1[]) //31������������ 
{
	char ch;
    ch = string1[ii++];  //ȡ�ַ� 
    if (ch == '^'){
    
         *T= NULL;   //Ϊ����ǰָ��ֵ��ΪNULL 
     }
    else {
        *T = (BTree)malloc(sizeof(BNode));  //���ٿռ� 
		if (jj==0) array[num]= *T;  //���ڵ�������飬���ں���ʹ�� ��jjΪȫ�ֱ��� 
		jj++;
        (*T)->data = ch;  //�����ַ� 
        (*T)->weight = W[k++];  //����Ȩֵ 
        CreateHTree(*T,&(*T)->lchild,string1);  //���������� 
        CreateHTree(*T,&(*T)->rchild,string1); //���������� 
    }

    return OK;
}
 
void HTCode(BTree T,int len){  //����Ҷ�ӽڵ���� ������code_��ά���飨ÿһ�ж�Ӧһ����ĸ�ı��룬��-1��β����27�У������ں�������ֱ��ʹ�� 
	int temp;
	if(!T) return;
	int i;
	if (!T->lchild && !T->rchild){  //ֻҪ����������������һ����Ϊ�� 
		for (int i=0;i<len;i++){
			if (T->data == ' ') temp = 0; else temp=(int)(T->data)-64;  
			code_[temp][i]=a[i];   //temp ��Ӧ26����ĸ�ֱ�Ϊ1-27�� �ո�Ϊ0
		}

	}
	else {
		a[len] = 0;  //��ֵ������0��1�ı��� 
		HTCode(T->lchild,len+1);  //�������� 
		a[len] = 1;
		HTCode(T->rchild,len+1);   //�������� 
	}
}
void HTreeCode(char string1[]) //32 ���룬�洢��anscode������ 
{	
	int k = 0;
	int length=strlen(string1);  //����ַ������� 
	int temp;
	for (int i=0;i<length;i++){  //iָʾ�ַ����ӵ�һ�������һ�� 
		int j = 0; //jָʾcode_ 
		temp = string1[i]-64;  //ת��������ʹ��code_���� 
		if(temp<0) temp = 0;  //���Ϊ�ո���tempС��0����ֵΪ0 
		while (code_[temp][j] != -1){   //ֻҪû�е����code_��ֵΪ-1�����������������о�Ϊ-1�� 
			anscode[k++] = code_[temp][j]+48;  //�ѵ�ǰcode_��Ӧ�ı������anscode�� 
			j++; 
		}
	}

}
void HTreeDecode(char code[])//33  ���� 
{
	int k=0;
	char ch;
	int len = strlen(code),i=0;
	while(i<len){  
		BTree p=array[num];
		while (p){
			if(!p->lchild && !p->rchild){ //�ȼ��뵱ǰ�ڵ� 
				ans[k++]=p->data;  //�������ans�ַ����� 
				break;
			}
			else {
				if(((int)(code[i]))-48) p=p->rchild,i++;  //���Ϊ1�����������������Ϊ0������������ 
					else p=p->lchild,i++;
			}
			
		}
	}

	
} 
Status StringCheck(char string1[])//34 ����-����-�ȶ�    
{
	//����˼�� ��Ϊ����-����-����õ����ַ�����ԭ���Ƚ�  
	HTreeCode(string1);
	char temps[201];
	for (int i=0;i<201;i++) temps[i]=anscode[i];
	for (int kk=0;kk<200;kk++) ans[kk]='\0';
	HTreeDecode(temps);
	if (!strcmp(ans,string1)) return OK;
		else return ERROR;
}
Status CodeCheck(char code[])//35����-����-�ȶ� 
{
	//����˼�� ��Ϊ����-����-����õ����ַ�����ԭ���Ƚ�  
	for (int kk=0;kk<200;kk++) ans[kk]='\0';
	HTreeDecode(code);
	HTreeCode(ans);
	if(!strcmp(anscode,code)) return OK;
		else return ERROR;
}

void menu(){
	system("cls"); 
	printf("              ********************************************************  \n\n");
	printf("              *      Menu for Function of Binary Tree     *   \n \n");
	printf("              ********************************************************  \n\n");
	printf("              -------------------------   ----------------------------   \n");
	printf("              ********************************************************     \n");
	printf("              *  0.EXIT                * *     1.IntiaBiTree         *     \n");
	printf("              ********************************************************     \n");
	printf("              *  2.DestroyBiTree       * *     3.CreateBiTree        *     \n");
	printf("              ********************************************************     \n");
	printf("              *  4.ClearBiTree         * *     5.BiTreeEmpty         *     \n");
	printf("              ********************************************************     \n");
	printf("              *  6.BiTreeDepth         * *     7.Root                *     \n");
	printf("              ********************************************************     \n");
	printf("              *  8.Value               * *     9.Assign              *     \n");
	printf("              ********************************************************     \n");
	printf("              *  10.Parent             * *     11.LeftChild          *     \n");
	printf("              ********************************************************     \n");
	printf("              *  12.RightChild         * *     13.LeftSibling        *     \n");
	printf("              ********************************************************     \n");
	printf("              *  14.RightSibling       * *     15.InsertChild        *     \n");
	printf("              ********************************************************     \n");
	printf("              *  16.DeleteChild        * *     17.PreOrderTraverse   *     \n");
	printf("              ********************************************************     \n");
	printf("              *  18.InOrderTraverse    * *     19.PostOrderTraverse  *     \n");
	printf("              ********************************************************     \n");
	printf("              *  20.LevelOrderTraverse * *     29.SetBTnum           *     \n");
	printf("              ********************************************************     \n");
	printf("              *  31.CreateHTree        * *     32.HTreeCode          *     \n");
	printf("              ********************************************************     \n");
	printf("              *  33.HTreeDecode        * *     34.StringCheck        *     \n");
	printf("              ********************************************************     \n");
	printf("              *  35.CodeCheck          * *     **********            *     \n");
	printf("              ********************************************************     \n");
	printf("              -------------------------   -----------------------------                         \n");
	printf("��ѡ����Ĳ���[0-35]:");
}
int main(){
	int xx,y,num1,num2,num3;
	ElemType ee,cure;
	BTree T =NULL;
	menu();
	scanf("%d",&xx);
	while(xx!=0){
		switch(xx){
			case 0:{
				int i=0;
				while(array[i]!=NULL){
				
					DestroyBiTree(&array[i]);
					i++;
				}
				break;
			}
			case 29:{   //  �����������  
				printf("��������Ҫ���õĶ������ı�ţ�"); 
				scanf("%d",&y);
				setBTnum(y);
				printf("���óɹ���\n");
				system("pause");
				menu();
				break;
			}
			case 1:{   //��ʼ�� 
				printf("��������ʼ���ɹ���\n");
				InitBiTree(&T);
				system("pause");
				menu(); 
				break;
			}
			case 2:{   //���ٶ�����  
				DestroyBiTree(&array[num]);
				printf("���������ٳɹ�! \n");
				system("pause");
				menu();	
				break;
			}
			case 3:{   //������ 
				printf("��������Ҫ�����Ķ�����������������У�\n");
				ii=jj=0;  //����ȫ�ֱ����ں�����ʹ�ã����и���ֵ 
				getchar();
				scanf("%[^\n]",str);
				CreateBiTree(&array[num],str);
				printf("�����������ɹ�! \n");
				system("pause");
				menu();
				break;
			}
			case 4:{  //����� 
			 
				ClearBiTree(&array[num]);
				printf("��������ճɹ�! \n");
				system("pause");
				menu();
				break;
			}
			case 5:{   //�ж����� 
				if(BiTreeEmpty(array[num])) printf("����Ϊ��\n"); else printf("������Ϊ��\n");
				system("pause");
				menu();
				break;
			}
			case 6:{  //�������   
				y = BiTreeDepth(array[num]);
				printf("�������Ϊ%d\n",y);
				system("pause");
				menu();
				
				break;
			}
			case 7:{  //���ڵ�   
				cure = Root(array[num]);
				printf("���ڵ��ֵΪ%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 8:{  //��õ�ǰ�ڵ㣬�Ըó�������趨��ʼΪ��ø��ڵ�Ϊ��ǰ�ڵ� 
				Value(array[num],&ee);
				printf("��ǰ�ڵ��ֵΪ%c\n",ee);
				system("pause"); 
				menu();
				break;
			}
			case 9:{ // �ı䵱ǰ�ڵ��ֵ
				printf("��������Ҫ�滻��ǰ�ڵ��ֵ��"); 
				getchar();
				scanf("%[^\n]",&ee);
				Assign(array[num],&(p_e[num]->data),ee);  
				printf("��ǰ�ڵ��ֵ�滻�ɹ���\n");
				system("pause");
				menu();
				break;
			}
			case 10:{ //��˫�׽ڵ� 
				cure = Parent(array[num],ee);
				if (cure =='^') printf ("��ǰ�ڵ��Ѿ��Ǹ��ڵ㣬û��˫�ף�\n"); else  printf("��ǰ�ڵ�ĸ��ڵ���%c\n",cure);
			//	printf("��ǰ�ڵ㸸�ڵ���%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 11:{ //���� 
				cure = LeftChild(array[num],&ee);
				if (cure =='^') printf ("��ǰ�ڵ�û������\n"); else  printf("��ǰ�ڵ��������%c\n",cure);
				//printf("��ǰ�ڵ��������%c\n",cure);
				system("pause");
				menu(); 
				break;
			}
			case 12:{ //�Һ���  
				cure = RightChild(array[num],ee);
				if (cure =='^') printf ("��ǰ�ڵ�û���Һ���\n"); else  printf("��ǰ�ڵ���Һ�����%c\n",cure);
			//	printf("��ǰ�ڵ���Һ�����%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 13:{ //���ֵ�  
				cure = LeftSibling(array[num],ee);
				if (cure =='^') printf ("��ǰ�ڵ�û�����ֵ�\n"); else  printf("��ǰ�ڵ�����ֵ���%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 14:{ //���ֵ� 
				cure = RightSibling(array[num],ee);
				if (cure =='^') printf ("��ǰ�ڵ�û�����ֵ�\n"); else  printf("��ǰ�ڵ�����ֵ���%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 15:{  //�������� 
				printf ("��������Ҫ����ĵ�ǰ�ڵ��������������������L or R����Ҫ����������ı�ţ��Կո������\n");
				//getchar();
				scanf("%c %d\n",&cure,&y);
				InsertChild(array[num],p_e[num],cure,y);
				printf ("��������ɹ���\n");
				system("pause");
				menu();
				break;
			}
			case 16:{ //ɾ������   
				printf ("��������ɾ����ǰ�ڵ��������������������L or R��\n");
				//getchar();
				scanf("%c\n",&cure);
				DeleteChild(array[num],p_e[num],cure);
				printf ("����ɾ���ɹ���\n");
				system("pause");
				menu();
				break;
			}
			case 17:{ //ǰ�����  
				printf ("ǰ�����Ϊ��");
				PreOrderTraverse(array[num],Visit);
				printf("\n");
				system("pause");
				menu();
				break;
			}
			case 18:{ //������� 
				printf ("�������Ϊ��");
				InOrderTraverse(array[num],Visit);
				printf("\n");
				system("pause");
				menu();
				break;
			}
			case 19:{ //�������  
				printf ("�������Ϊ��");
				PostOrderTraverse(array[num],Visit);
				printf("\n");
				system("pause");
				menu();
				break;
			}
			case 20:{ //������� 
				printf ("�������Ϊ��");
				LevelOrderTraverse(array[num],Visit);
				
				system("pause");
				menu();

				break;
			}
			case 31:{  //������������ 
				printf("��������Ҫ�����Ĺ������������У�\n");
				getchar();
				ii=jj=k=0;
				scanf("%[^\n]",str);
				for (int i=0;i<30;i++)
					for (int j=0;j<200;j++)
						code_[i][j]=-1;
				CreateHTree(NULL,&array[num],str);
				HTCode(array[num],0) ;
				printf("�������������ɹ���\n");
				system("pause");
				menu();
				break;
			}
			case 32:{  //���б���  
				printf("��������Ҫ���б�����ַ��� ��\n");
				getchar();
				scanf("%[^\n]",str);
				//cout<<str<<endl;
				//getchar();
				HTreeCode(str);
				printf("����Ľ��Ϊ");
				cout<<anscode<<endl;
				system("pause");
				menu();
				break;
			}
			case 33:{ //���н��� 
				printf("��������Ҫ���н�����ִ� ��\n");
				getchar();
				scanf("%[^\n]",str);
				//getchar();
				HTreeDecode(str);
				printf("������Ϊ ��");
				cout<<ans<<endl;
				system("pause");
				menu();
				break;
			}
			case 34:{  //����-����-���� �ȶ� 
			    
				for (int kk=0;kk<200;kk++) ans[kk]='\0';
				getchar();
				scanf("%[^\n]",str);
				if(StringCheck(str)) printf("����-����-������ƥ��\n"); else printf("����-����-���벻ƥ��\n");
				system("pause");
				menu();
				break;
			}
			case 35:{ //����-����-���� �ȶ� 
				getchar();
				char strr[200];
				scanf("%s",str);
				if(CodeCheck(str)) printf("����-����-������ƥ��\n"); else printf("����-����-���벻ƥ��\n");
				system("pause");
				menu();
				break;
			}
			
		}
		scanf("%d",&xx);
		
	}
	return 0;
}








 
 
