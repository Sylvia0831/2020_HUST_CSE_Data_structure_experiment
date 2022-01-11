/*
姓名:李欣宇
班级:信安1901班
学号：U201911658
日期:2020年11月5日 
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
#define DestroyBiTree ClearBiTree    //销毁二叉树与清空二叉树操作相同 

typedef char ElemType;  //节点数据类型 
typedef int Status;   
typedef struct BNode{
	ElemType data;
	int weight;
	struct BNode* lchild; //指向左孩子
	struct BNode* rchild; //指向兄弟 
}BNode;
typedef BNode* BTree;  
//p_e数组存放第i棵二叉树的当前节点的指针，array数组用于多二叉树管理 
BTree p_e[11]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL},array[11]={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL}; //数组管理多二叉树 
ElemType str[2000];
int ii=0,jj=0,k=0;
int num=0;
//W数组用于构建哈夫曼树，是频数 
int W[100]={1000,408,191,92,45,22,28,47,99,48,51,217,103,114,57,57,592,251,123,60,28,13,15,32,15,17,8,9,4,2,1,1,2,1,1,5,63,128,64,64,32,32,341,155,75,34,16,18,41,20,21,80,186};
char ans[201],anscode[201];
int code_[31][201]={}; 
int a[100];

void menu(void);
void Visit(ElemType e);
void setBTnum(int n); //29 设置当前二叉树序号 
void InitBiTree(BTree *T);  //1   初始化
Status CreateBiTree(BTree *T); //3 创建二叉树 
void ClearBiTree(BTree *T);    //4 清空二叉树 
Status BiTreeEmpty(BTree T); //5 判断空二叉树 
Status BiTreeDepth(BTree T); //6 求二叉树深度
ElemType Root(BTree T);  //7 获得根节点 
BTree Order_Bi(BTree T,ElemType e); //返回指向e节点的指针
Status Value(BTree T,ElemType *e); //8 获得当前节点的值???
Status Assign(BTree T,ElemType e,ElemType value);//9结点赋值 
ElemType Parent(BTree T,ElemType e); //10 获得双亲 
ElemType GetChild(BTree T,ElemType e,int order); //11&&12 用于找孩子 
ElemType LeftChild(BTree T,ElemType e); //11   左孩子 
ElemType RightChild(BTree T,ElemType e);  //12右孩子 
ElemType LeftSibling(BTree T,ElemType e);  //13 左兄弟 
ElemType RightSibling(BTree T,ElemType e);  //(13)  //14 右兄弟
Status InsertChild(BTree T,BTree p,char LR,int tnum); //15插入子树 
Status DeleteChild(BTree T,BTree p,char LR);//16  删除子树 
void PreOrderTraverse(BTree T,void(Visit)());//17 前序遍历 
void InOrderTraverse(BTree T,void(Visit)());//18 中序遍历 
void PostOrderTraverse(BTree T,void(Visit)());//19 后序遍历 
void LevelOrderTraverse(BTree T,void(Visit)());  //20 层序遍历 
Status CreateHTree(BTree F,BTree *T,char string1); //31 创建哈夫曼树 
void HTreeCode(char string1[]); //32  进行编码 
void HTreeDecode(char code[]);//33  进行译码 
Status StringCheck(char string1[]);//34  编码-译码-编码 检查 
Status CodeCheck(char code[]);//35  译码-编码-译码 检查 
 

void Visit(ElemType e){  //遍历时输出 
    printf("%c",e);
}
void setBTnum(int n){  //29  设置树序号
    num = n;
}
void InitBiTree(BTree *T){   // 初始化二叉树 
    *T = NULL;
}
Status CreateBiTree(BTree *T,char str[]){  //创建二叉树 ，使用前序遍历序列 
    char ch;
    ch = str[ii++];
    if (ch == '^')  //如果ch是^,则当前节点为NULL 
        *T = NULL;
    else {  
        *T = (BTree)malloc(sizeof(BNode));//开辟一个节点空间 
		if (jj==0) array[num]= *T; //如果是根节点，则把该指针存入多二叉树数组管理中，便于后续访问 
		jj++; //这里的jj是全局变量，在主函数中调用该函数时进行赋初值0 ，作用是判断当前节点是不是根节点 
        if(!(*T)) return  OVERFLOW;  //防止溢出 
        (*T)->data = ch;  //对节点数据域进行赋值 
        CreateBiTree(&(*T)->lchild,str);  //递归创建左子树 
        CreateBiTree(&(*T)->rchild,str); //递归创建右子树 
    }
    return OK;
}
void ClearBiTree(BTree *T){  //请空二叉树，与销毁二叉树操作相同 
    if (*T){
        if ((*T)->lchild) ClearBiTree(&(*T)->lchild);  //只要左子树不为空，递归销毁左子树 
        if ((*T)->rchild) ClearBiTree(&(*T)->rchild);  // 只要右子树不为空，递归销毁右子树 
        free(*T);   //释放空间 
        *T = NULL;   
    }
}
Status BiTreeEmpty(BTree T){    //判断空二叉树 
    return T==NULL ? TRUE :FALSE;  //根节点为空则返回TRUE 
}

Status BiTreeDepth(BTree T){  //求树的深度 
    if (T == NULL) return 0;  //递归出口，当前节点为NULL 
      else return max(1+BiTreeDepth(T->lchild),1+BiTreeDepth(T->rchild));  //递归求深度 
}

ElemType Root(BTree T){  //求树的根节点 
    if (T){ 
		p_e[num] = T;   //如果多二叉树数组中指示的根节点存在，则返回根节点的数据域 
        return T->data;
    }
    else
        return '^';  //不存在则为空 
}

Status Value(BTree T,ElemType *e){  //获得当前节点 
    *e = p_e[num]->data; //使用e返回 
    return OK;
}

Status Assign(BTree T,ElemType *e,ElemType value){//节点赋值 
	*e = value;  
    return OK;
}
ElemType Parent(BTree T,ElemType e){ //10 获得双亲
    int i=0,j=0;
    BTree Q[100]={};  //使用队列 
    if (T){   //如果根节点不为空，把根节点加入队列  
        Q[j++] = T;
    }
	if (Q[i]==p_e[num]) return '^';  //如果恰好根节点与当前节点相同，则说明没有双亲，已经是根节点，返回NULL 
    while (i<j){
        if (Q[i]){  //只要队列当前的不为空 
            if(Q[i]->lchild){  //如果左孩子 
				if(Q[i]->lchild->data == p_e[num]->data) {  //且左孩子的值恰好与当前节点的值相同，则说明队列当前节点为其父节点 
					p_e[num] = Q[i];
					return Q[i]->data;  //返回父节点 
				
				}
			}
			if (Q[i]->rchild){  //如果右孩子存在 
				if(Q[i]->rchild->data == p_e[num]->data){ // 且右孩子的值恰好与当前节点的值相同，则说明队列当前节点为其父节点 
					p_e[num] = Q[i];
					return Q[i]->data;  //返回父节点 
				} 
			}
            Q[j++] = Q[i]->lchild;  //把左孩子加入队列 
            Q[j++] = Q[i]->rchild;  //把右孩子加入队列 
        }
        i++;  //后移一个 
    }
}

ElemType LeftChild(BTree T,ElemType *e){//11   找左孩子
    if (p_e[num]->lchild) {  //只要当前节点的左孩子村子 
        p_e[num]=p_e[num]->lchild;  //把当前节点修改为其左孩子 
        return p_e[num]->data;  //返回左孩子 
    }
    return '^';  //没有左孩子，返回NULL 
}


ElemType RightChild(BTree T,ElemType e){// 找右孩子，思想同上 
    if(p_e[num]->rchild){
        p_e[num] = p_e[num]->rchild;
        return p_e[num]->data;
    }
    return '^';
}

ElemType LeftSibling(BTree T,ElemType e)  //找左兄弟 
{ 
	int i=0,j=0;
    BTree Q[100]; //使用队列 
    if (T){
        Q[j++] = T;   //加入根节点 
    }
    if(Q[i]->data==p_e[num]->data) return '^'; //如果根节点与当前节点相同，则无兄弟，返回NULL 
    while (i<j){
        if (Q[i]){  //如果队列不空 
        	if(Q[i]->rchild==p_e[num]) { //如果队列元素的右孩子与当前节点相同 
        		if (Q[i]->lchild) {  //查看是否又左孩子 
        			p_e[num] = Q[i]->lchild;  //如果有左孩子，则查找成功 
        			return p_e[num]->data;  //返回其左兄弟 
        		}
        		else return '^';  //如果没有左孩子，说明没有左兄弟 
        	}
        	if(Q[i]->lchild==p_e[num]) return '^';  //如果要查找的节点与队列当前元素的左孩子相等，则其必然没有左兄弟，返回NULL 
            Q[j++] = Q[i]->lchild;  //左孩子加入队列 
            Q[j++] = Q[i]->rchild; //右孩子加入队列 
        }
        i++;  //后移一个 
       
    }

}
ElemType RightSibling(BTree T,ElemType e){  //找右兄弟，思想同上 
	int i=0,j=0;
    BTree Q[100];
    if (T){
        Q[j++] = T;
    }
    if(Q[i]->data==p_e[num]->data) return '^'; //如果根节点与当前节点相同，则无兄弟，返回NULL 
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
Status InsertChild(BTree T,BTree p,char LR,int tnum){  //插入子树 
 BTree tp=p_e[num],temp=NULL,childtree=array[tnum];
	switch (LR){
		case 'L':{  
			if (p->lchild){  //如果左子树本身存在，则将其放入要插入的子树的右子树上  
				temp = p->lchild;
				p_e[num]->lchild = array[tnum];
				childtree->rchild = temp;
				array[tnum]= NULL;  //将子树在列表中删除 
			}
			else {  //如果左子树为空，则直接插入 
				p_e[num]->lchild = array[tnum];
				array[tnum] = NULL;  //将子树在列表中删除 
			}
			break;
		}
		case 'R':{     //思想同上 
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

Status DeleteChild(BTree T,BTree p,char LR)//16  删除子树 
{
	switch(LR){
		case 'L':{
			ClearBiTree(&p->lchild); //清空左子树 
			break;
		}
		case 'R':{
			ClearBiTree(&p->rchild);  //清空右子树 
			break;
		}
	}
	
}
void PreOrderTraverse(BTree T,void(Visit)(ElemType)){//前序遍历 递归 
    if(T){
        Visit(T->data);  //根节点 
        PreOrderTraverse(T->lchild,Visit);  //左孩子 
        PreOrderTraverse(T->rchild,Visit);//右孩子 
    }
}
Status InOrderTraverse(BTree T,void(Visit)(ElemType)){//中序遍历 非递归 
    BTree S[100];  //使用栈 
    int top = 0;  //栈顶 
    do{
        while(T){  //只要当前节点不为空 
            if(top == 100) return OVERFLOW;  //栈溢出 
            S[top++] =T; //根加入栈中 
            T= T->lchild;  //找左孩子（因中序遍历是 根 左 右 ） 
        }
        if (top){  //如果栈不为空 
            T = S[--top];  //栈顶元素弹出栈 
            Visit(T->data);  
            T = T->rchild;  //找右孩子 
        }
    }while(top||T);   //只要节点不为空或栈不为空 
    return OK;
}
void PostOrderTraverse(BTree T,void(Visit)(ElemType))//19后续遍历 
{
    if(T){
        PostOrderTraverse(T->lchild,Visit);  //左 
        PostOrderTraverse(T->rchild,Visit); //右 
        Visit(T->data);  //根 
    }
}
void LevelOrderTraverse(BTree T,void(Visit)(ElemType)){  //层序遍历 
    int i=0,j=0;
    BTree Q[100]={};  //使用队列 
    if (T){
        Q[j++] = T;  //根节点加入队列中 
    }
    while (i<j){
        if (Q[i]){
            Visit(Q[i]->data);  //输出 
            Q[j++] = Q[i]->lchild; //加左孩子 
            Q[j++] = Q[i]->rchild;  //加右孩子  即把下一层的加入  
        }
        i++;
    }
    printf("\n");
}
Status CreateHTree(BTree F,BTree *T,char string1[]) //31创建哈夫曼树 
{
	char ch;
    ch = string1[ii++];  //取字符 
    if (ch == '^'){
    
         *T= NULL;   //为空则当前指针值置为NULL 
     }
    else {
        *T = (BTree)malloc(sizeof(BNode));  //开辟空间 
		if (jj==0) array[num]= *T;  //根节点加入数组，便于后续使用 ，jj为全局变量 
		jj++;
        (*T)->data = ch;  //加入字符 
        (*T)->weight = W[k++];  //加入权值 
        CreateHTree(*T,&(*T)->lchild,string1);  //构建左子树 
        CreateHTree(*T,&(*T)->rchild,string1); //构建右子树 
    }

    return OK;
}
 
void HTCode(BTree T,int len){  //所有叶子节点编码 ，存入code_二维数组（每一行对应一个字母的编码，以-1结尾，共27行），便于后续编码直接使用 
	int temp;
	if(!T) return;
	int i;
	if (!T->lchild && !T->rchild){  //只要左子树和右子树有一个不为空 
		for (int i=0;i<len;i++){
			if (T->data == ' ') temp = 0; else temp=(int)(T->data)-64;  
			code_[temp][i]=a[i];   //temp 对应26个字母分别为1-27， 空格为0
		}

	}
	else {
		a[len] = 0;  //赋值，用于0，1的编码 
		HTCode(T->lchild,len+1);  //找左子树 
		a[len] = 1;
		HTCode(T->rchild,len+1);   //找右子树 
	}
}
void HTreeCode(char string1[]) //32 编码，存储在anscode数组里 
{	
	int k = 0;
	int length=strlen(string1);  //获得字符串长度 
	int temp;
	for (int i=0;i<length;i++){  //i指示字符，从第一个到最后一个 
		int j = 0; //j指示code_ 
		temp = string1[i]-64;  //转换，便于使用code_数组 
		if(temp<0) temp = 0;  //如果为空格，则temp小于0，赋值为0 
		while (code_[temp][j] != -1){   //只要没有到最后（code_初值为-1，当编码结束后的所有均为-1） 
			anscode[k++] = code_[temp][j]+48;  //把当前code_对应的编码加入anscode中 
			j++; 
		}
	}

}
void HTreeDecode(char code[])//33  译码 
{
	int k=0;
	char ch;
	int len = strlen(code),i=0;
	while(i<len){  
		BTree p=array[num];
		while (p){
			if(!p->lchild && !p->rchild){ //先加入当前节点 
				ans[k++]=p->data;  //结果存入ans字符数组 
				break;
			}
			else {
				if(((int)(code[i]))-48) p=p->rchild,i++;  //如果为1，则找右子树，如果为0，则找左子树 
					else p=p->lchild,i++;
			}
			
		}
	}

	
} 
Status StringCheck(char string1[])//34 编码-解码-比对    
{
	//基本思想 即为编码-解码-编码得到的字符串与原串比较  
	HTreeCode(string1);
	char temps[201];
	for (int i=0;i<201;i++) temps[i]=anscode[i];
	for (int kk=0;kk<200;kk++) ans[kk]='\0';
	HTreeDecode(temps);
	if (!strcmp(ans,string1)) return OK;
		else return ERROR;
}
Status CodeCheck(char code[])//35解码-编码-比对 
{
	//基本思想 即为解码-编码-解码得到的字符串与原串比较  
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
	printf("请选择你的操作[0-35]:");
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
			case 29:{   //  设置树的序号  
				printf("请输入您要设置的二叉树的编号："); 
				scanf("%d",&y);
				setBTnum(y);
				printf("设置成功！\n");
				system("pause");
				menu();
				break;
			}
			case 1:{   //初始化 
				printf("二叉树初始化成功！\n");
				InitBiTree(&T);
				system("pause");
				menu(); 
				break;
			}
			case 2:{   //销毁二叉树  
				DestroyBiTree(&array[num]);
				printf("二叉树销毁成功! \n");
				system("pause");
				menu();	
				break;
			}
			case 3:{   //构建树 
				printf("请输入您要创建的二叉树的先序遍历序列：\n");
				ii=jj=0;  //两个全局变量在函数中使用，进行赋初值 
				getchar();
				scanf("%[^\n]",str);
				CreateBiTree(&array[num],str);
				printf("二叉树创建成功! \n");
				system("pause");
				menu();
				break;
			}
			case 4:{  //清空树 
			 
				ClearBiTree(&array[num]);
				printf("二叉树清空成功! \n");
				system("pause");
				menu();
				break;
			}
			case 5:{   //判断树空 
				if(BiTreeEmpty(array[num])) printf("该树为空\n"); else printf("该树不为空\n");
				system("pause");
				menu();
				break;
			}
			case 6:{  //树的深度   
				y = BiTreeDepth(array[num]);
				printf("树的深度为%d\n",y);
				system("pause");
				menu();
				
				break;
			}
			case 7:{  //根节点   
				cure = Root(array[num]);
				printf("根节点的值为%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 8:{  //获得当前节点，对该程序而言设定初始为获得根节点为当前节点 
				Value(array[num],&ee);
				printf("当前节点的值为%c\n",ee);
				system("pause"); 
				menu();
				break;
			}
			case 9:{ // 改变当前节点的值
				printf("请输入您要替换当前节点的值："); 
				getchar();
				scanf("%[^\n]",&ee);
				Assign(array[num],&(p_e[num]->data),ee);  
				printf("当前节点的值替换成功！\n");
				system("pause");
				menu();
				break;
			}
			case 10:{ //求双亲节点 
				cure = Parent(array[num],ee);
				if (cure =='^') printf ("当前节点已经是根节点，没有双亲！\n"); else  printf("当前节点的父节点是%c\n",cure);
			//	printf("当前节点父节点是%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 11:{ //左孩子 
				cure = LeftChild(array[num],&ee);
				if (cure =='^') printf ("当前节点没有左孩子\n"); else  printf("当前节点的左孩子是%c\n",cure);
				//printf("当前节点的左孩子是%c\n",cure);
				system("pause");
				menu(); 
				break;
			}
			case 12:{ //右孩子  
				cure = RightChild(array[num],ee);
				if (cure =='^') printf ("当前节点没有右孩子\n"); else  printf("当前节点的右孩子是%c\n",cure);
			//	printf("当前节点的右孩子是%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 13:{ //左兄弟  
				cure = LeftSibling(array[num],ee);
				if (cure =='^') printf ("当前节点没有左兄弟\n"); else  printf("当前节点的左兄弟是%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 14:{ //右兄弟 
				cure = RightSibling(array[num],ee);
				if (cure =='^') printf ("当前节点没有右兄弟\n"); else  printf("当前节点的右兄弟是%c\n",cure);
				system("pause");
				menu();
				break;
			}
			case 15:{  //插入子树 
				printf ("请输入您要插入的当前节点的左子树还是右子树（L or R）和要插入的子树的编号（以空格隔开）\n");
				//getchar();
				scanf("%c %d\n",&cure,&y);
				InsertChild(array[num],p_e[num],cure,y);
				printf ("子树插入成功！\n");
				system("pause");
				menu();
				break;
			}
			case 16:{ //删除子树   
				printf ("请输入您删除当前节点的左子树还是右子树（L or R）\n");
				//getchar();
				scanf("%c\n",&cure);
				DeleteChild(array[num],p_e[num],cure);
				printf ("子树删除成功！\n");
				system("pause");
				menu();
				break;
			}
			case 17:{ //前序遍历  
				printf ("前序遍历为：");
				PreOrderTraverse(array[num],Visit);
				printf("\n");
				system("pause");
				menu();
				break;
			}
			case 18:{ //中序遍历 
				printf ("中序遍历为：");
				InOrderTraverse(array[num],Visit);
				printf("\n");
				system("pause");
				menu();
				break;
			}
			case 19:{ //后序遍历  
				printf ("后序遍历为：");
				PostOrderTraverse(array[num],Visit);
				printf("\n");
				system("pause");
				menu();
				break;
			}
			case 20:{ //层序遍历 
				printf ("层序遍历为：");
				LevelOrderTraverse(array[num],Visit);
				
				system("pause");
				menu();

				break;
			}
			case 31:{  //构建哈夫曼树 
				printf("请输入您要创建的哈夫曼树的序列：\n");
				getchar();
				ii=jj=k=0;
				scanf("%[^\n]",str);
				for (int i=0;i<30;i++)
					for (int j=0;j<200;j++)
						code_[i][j]=-1;
				CreateHTree(NULL,&array[num],str);
				HTCode(array[num],0) ;
				printf("哈夫曼树创建成功！\n");
				system("pause");
				menu();
				break;
			}
			case 32:{  //进行编码  
				printf("请输入您要进行编码的字符串 ：\n");
				getchar();
				scanf("%[^\n]",str);
				//cout<<str<<endl;
				//getchar();
				HTreeCode(str);
				printf("编码的结果为");
				cout<<anscode<<endl;
				system("pause");
				menu();
				break;
			}
			case 33:{ //进行解码 
				printf("请输入您要进行解码的字串 ：\n");
				getchar();
				scanf("%[^\n]",str);
				//getchar();
				HTreeDecode(str);
				printf("解码结果为 ：");
				cout<<ans<<endl;
				system("pause");
				menu();
				break;
			}
			case 34:{  //编码-解码-编码 比对 
			    
				for (int kk=0;kk<200;kk++) ans[kk]='\0';
				getchar();
				scanf("%[^\n]",str);
				if(StringCheck(str)) printf("编码-解码-编码结果匹配\n"); else printf("编码-解码-编码不匹配\n");
				system("pause");
				menu();
				break;
			}
			case 35:{ //解码-编码-编码 比对 
				getchar();
				char strr[200];
				scanf("%s",str);
				if(CodeCheck(str)) printf("解码-编码-解码结果匹配\n"); else printf("解码-编码-解码不匹配\n");
				system("pause");
				menu();
				break;
			}
			
		}
		scanf("%d",&xx);
		
	}
	return 0;
}








 
 
