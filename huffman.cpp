#include <stdio.h>
#include <stdlib.h>
#include "Huffman_Tree.h"

#define Yes 1 //若已调用过InitHuff_T()函数，或已从htfTree.txt文件读取过，则将Init_Mode置为Yes，否则置为No
#define No 0
/*
	新建英文文本信息
*/
void Create_Message()
{
	FILE * fp;
	char c;
	if((fp=fopen("text1.txt","wb"))==NULL)
	{
		printf("Can not open this file!\n");
		return;
	}
	getchar();//吸收菜单选择时所敲的回车换行符
	printf("请输入原文(回车结束!)：\n");
	do
	{
		scanf("%c",&c);
		fputc(c,fp);
	}while(c!='\n');
	fclose(fp);
}
/*
	初始化哈夫曼树，要求用户输入字符和相应权值
*/
void InitHuff_T( HuffmanTree &HT, HuffmanCode &HC, char ch[],int &n )
{ 
	int i = 1,w[100],tem,j;
	char a[20];
	FILE *save;
	printf("请输入编码字符集的大小n:");
	scanf("%d",&n);  
	while( i <= n )
	{ 
		printf("请输入第%d个字符和该字符的权值w:",i);
		fflush(stdin);
		scanf("%c%d",&ch[i],&w[i]);
		i++;
	}
	ch[i] = '\0';
	HuffmanCoding(HT,HC,w,n);  						//生成哈夫曼数及各个字符相应的哈夫曼编码，分别存在HT树和HC中
	if(( save = fopen("htfTree.txt","wb")) == NULL )
	{ 
		printf("Open file fail......\n");
		exit(0);
	}
	tem = n;  										//将字符集大小转换成字符形式写入到文件中
	j = 0;
	while( tem != 0 )
	{
		tem = tem / 10;
		j++;
	}
	tem = n;
	a[j] = '\0';
	while( tem != 0 )
	{
		a[j - 1] = (char)(tem % 10 + 48);
		tem = tem / 10;
		j--;
	}
	fputs(a,save);
	printf("%d\n",n); 
	fputc('\n',save);
	for( i = 1; i <= n; i++ )						//分别向文件和屏幕输出各个字符和相应的哈夫曼编码
	{ 
		fputc(ch[i],save);  
		printf("%c\t",ch[i]);
		fputc('\t',save);
		fputs(HC[i],save);  
		printf("%s\n",HC[i]);
		fputc('\n',save);
	}
	for(i = 1; i <= 2 * n - 1; i++ )				//将哈夫曼树各个结点的parent,lchild,rchild分别写入到文件中
	{ 
		tem = HT[i].parent;							//将i结点的parent转换成字符并写入到文件中
		if(tem == 0)
		{
			fputc(tem + 48,save);
			fputc(' ',save);
		}
		else
		{
			j = 0;
			while( tem != 0 )
			{
				tem = tem / 10;
				j++;
			}
			tem = HT[i].parent;
			a[j] = '\0';
			while( tem != 0 )
			{
				a[j - 1] = (char)(tem % 10 + 48);
				tem = tem / 10;
				j--;
			}
			fputs(a,save);
			fputc(' ',save);
		}
		
		tem = HT[i].lchild;  						//将i结点的lchild转换成字符并写入到文件中
		if(tem == 0)
		{
			fputc(tem + 48,save);
			fputc(' ',save);
		}
		else
		{
			j = 0;
			while( tem != 0 )
			{
				tem = tem / 10;
				j++;
			}
			tem = HT[i].lchild;
			a[j] = '\0';
			while( tem != 0 )
			{
				a[j - 1] = (char)(tem % 10 + 48);
				tem = tem / 10;
				j--;
			}
			fputs(a,save);
			fputc(' ',save);
		}
		
		tem = HT[i].rchild;							//将i结点的rchild转换成字符并写入到文件中
		if(tem == 0)
		{
			fputc(tem + 48,save);
			fputc('\n',save);
		}
		else
		{
			j = 0;
			while( tem != 0 )
			{
				tem = tem / 10;
				j++;
			}
			tem = HT[i].rchild;
			a[j] = '\0';
			while( tem != 0 )
			{
				a[j - 1] = (char)(tem % 10 + 48);
				tem = tem / 10;
				j--;
			}
			fputs(a,save);
			fputc('\n',save);
		}
	} 
	fclose(save);
}
/*
	根据哈夫曼编码将用户指定的txt文件中的字符编码,并将所得编码存储到用户指定的txt文件
*/
void Encoding(HuffmanTree &HT, HuffmanCode &HC, char ch[])
{ 
	FILE *ToBeTran,*CodeFile;
	char ToBeTran_Name[100],CodeFile_Name[100];
	int i;
	char c;
	printf("请输入所要进行编码的文件的文件名:");
	scanf("%s",ToBeTran_Name); 
	if(( ToBeTran = fopen(ToBeTran_Name,"rb")) == NULL )
	{ 
		printf("Open file fail......\n");
		exit(0);
	}
	printf("请输入编码后编码表示的信息所存储到的文件的文件名:");
	scanf("%s",CodeFile_Name);
	if(( CodeFile = fopen(CodeFile_Name,"wb")) == NULL )
	{
		printf("Open file fail......\n");
		exit(0);
	}
	while(!feof(ToBeTran))
	{
		c=fgetc(ToBeTran);
		for(i=1;i<=28;i++)
			if(ch[i]==c)
			{
				fputs(HC[i],CodeFile);
				printf("%c---%s\n",c,HC[i]);  //打印c相应的哈夫曼编码
				break;
			}
	}
	printf("\n");
	printf("编码成功!\n");
	fclose(ToBeTran);
	fclose(CodeFile);
}
/*
	对用户由哈夫曼编码信息表示的的编码文件进行译码，并存至到用户指定的.txt文件中
*/
void Decoding(HuffmanTree HT, char ch[] , int n)
{ 
	int p,i = 1;
	char code[1000],c;
	char CodeFile_Name[100],TextFile_Name[100];
	p = 2 * n - 1;
	FILE *CodeFile,*TextFile;
	printf("请输入所要译的文件名:");
	scanf("%s",CodeFile_Name);  
	if(( CodeFile = fopen(CodeFile_Name,"rb")) == NULL )
	{ 
		printf("Open file fail......\n");
		exit(0);
	}
	printf("请输入译后的字符存储到的文件的文件名:");
	scanf("%s",TextFile_Name);  
	if(( TextFile = fopen(TextFile_Name,"wb")) == NULL )
	{
		printf("Open file fail......\n");
		exit(0);
	}
	c = fgetc(CodeFile);
	while( c != EOF )
	{
		code[i] = c;
		i++;
		c = fgetc(CodeFile);
	}
	code[i] = '\0';  						//从文件读取字符，存储在code[]数组中
	i = 1;
	while ( code[i] != '\0' && p != 0 )		//对数组code[]中的哈夫曼编码进行译码
	{ 
		if ( code[i] == '0' )
			p=HT[p].lchild;  				//进入左分支
		else
			p = HT[p].rchild; 				//进入右分支
		if (!HT[p].lchild&& !HT[p].rchild)	//进入叶子结点
		{ 
			fputc(ch[p], TextFile);  
			printf("%c",ch[p]);    
			p = 2 * n - 1;  				//重新从树根出发进行译码
		}
		i++;
	}
	printf("\n");
	printf("译码成功!\n");
}
/*
	从文件读取哈夫曼树
*/
void ReadHuff_T( HuffmanTree &HT, HuffmanCode &HC, char ch[], int &n)
{ 
	FILE *htfTree;
	char c[100],ch1;
	int i,j,t;
	if(( htfTree = fopen("htfTree.txt","rb")) == NULL )
	{ 
		printf("Open file fail......\n");
		exit(0);
	}
	fgets(c,10,htfTree); 								//获取哈夫曼树叶子结点个数的字符串表示形式
	i = 0;   
	while( c[i] != '\n' )								//将字符串形式转换成整数形式
		i++;
	n = 0;
	for( j = 0; j < i; j++ )  
		n = 10 * n + c[j] - '0';						//求出叶子结点数n
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *)); 
	HT = (HuffmanTree)malloc((2 * n) * sizeof(HTNode));  
	i = 1;
	while( i <= n )
	{
		ch[i] = fgetc(htfTree);  						//读取字符集中的一个字符
		HC[i] = (char *)malloc((10)*sizeof(char));		//申请用于存储读取到的字符集中的字符的哈夫曼编码的空间
		fgetc(htfTree); 								//将‘\t’输出
		ch1 = fgetc(htfTree);  							//读取哈夫曼编码，存储在相应的HC[i][]数组里
		int j = 0;
		while( ch1 != '\n' )
		{
			HC[i][j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}
		HC[i][j] = '\0';
		i++;
	}
	ch[i] = '\0';
	i = 0;
	while( i < 2 * n - 1 )								//读取哈夫曼树的各个结点的parent,lchild,rchild.并赋值到哈夫曼树HT中
	{  
		ch1 = fgetc(htfTree); 							//读取parent的字符串形式,存储在c[]中，并将其转换成整数形式，赋给HT[i].parent
		j = 0;
		while( ch1 != ' ' )
		{
			c[j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}    
		HT[i+1].parent = 0;
		for(  t = 0; t < j; t++ )  
			HT[i+1].parent = 10 * HT[i+1].parent + c[t] - '0';
		ch1 = fgetc(htfTree); 							//读取lchild的字符串形式，并将其转换成整数形式，赋给HT[i].lchild
		j = 0;
		while( ch1 != ' ' )
		{
			c[j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}    
		HT[i+1].lchild = 0;
		for(  t = 0; t < j; t++ )  
			HT[i+1].lchild = 10 * HT[i+1].lchild + c[t] - '0';
		ch1 = fgetc(htfTree); 							//读取rchild的字符串形式，并将其转换成整数形式，赋给HT[i].rchild
		j = 0;
		while( ch1 != '\n' )
		{
			c[j] = ch1;
			j++;
			ch1 = fgetc(htfTree);
		}
		HT[i+1].rchild = 0;
		for(  t = 0; t < j; t++ )  
			HT[i+1].rchild = 10 * HT[i+1].rchild + c[t] - '0';
		i++;
	}
}
/*
	打印各个字符和相应的哈夫曼编码
*/
void Print_huffman(HuffmanTree &HT, HuffmanCode &HC, char ch[],int n)
{
	FILE * fp;
	if((fp=fopen("htfTree.txt","rb"))==NULL)
	{
		printf("Can not open this file!\n");
		return;
	}
	ReadHuff_T(HT,HC,ch,n);
	for( int i = 1; i <= n; i++ )
	{ 
		fputc(ch[i],fp);  
		printf("%c\t",ch[i]);
		fputc('\t',fp);
		fputs(HC[i],fp);  
		printf("%s\n",HC[i]);
		fputc('\n',fp);
	}
	fclose(fp);
}
int main()
{
	HuffmanTree HT;
	HuffmanCode HC;
	char ch[100];  
	int n,Init_Mode = No;//Init_Mode = No 表示内存中没有哈夫曼树的信息
	int sel; 
	do
	{
		printf("\n*************哈夫曼编/译码器*************\n");
		printf("*	1---初始化			*\n");
		printf("*	2---编码			*\n");
		printf("*	3---译码			*\n");
		printf("*	4---打印			*\n");
		printf("*	5---退出			*\n");
		printf("*****************************************\n");
		printf("请输入您的选择(1-5):");
		scanf("%d",&sel);   
		switch(sel)
		{
			case 1 :  
				InitHuff_T(HT,HC,ch,n);
				Init_Mode = Yes;         
				break;
			case 2 :
				if( No == Init_Mode )
					ReadHuff_T(HT,HC,ch,n);
				Create_Message();
				Encoding(HT,HC,ch);
				Init_Mode = Yes;
				break;
			case 3 :
				if( No == Init_Mode )
					ReadHuff_T(HT,HC,ch,n);
				Decoding(HT,ch,n);
				Init_Mode = Yes;
				break;
			case 4 :Print_huffman(HT,HC,ch,n);break;
			case 5 :break;
			default :printf("您的输入有错，请重新选择.\n");		
		}	 
	}while(sel!=5); 
	return 0;
}