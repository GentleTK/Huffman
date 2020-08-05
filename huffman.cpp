#include <stdio.h>
#include <stdlib.h>
#include "Huffman_Tree.h"

#define Yes 1 //���ѵ��ù�InitHuff_T()���������Ѵ�htfTree.txt�ļ���ȡ������Init_Mode��ΪYes��������ΪNo
#define No 0
/*
	�½�Ӣ���ı���Ϣ
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
	getchar();//���ղ˵�ѡ��ʱ���õĻس����з�
	printf("������ԭ��(�س�����!)��\n");
	do
	{
		scanf("%c",&c);
		fputc(c,fp);
	}while(c!='\n');
	fclose(fp);
}
/*
	��ʼ������������Ҫ���û������ַ�����ӦȨֵ
*/
void InitHuff_T( HuffmanTree &HT, HuffmanCode &HC, char ch[],int &n )
{ 
	int i = 1,w[100],tem,j;
	char a[20];
	FILE *save;
	printf("����������ַ����Ĵ�Сn:");
	scanf("%d",&n);  
	while( i <= n )
	{ 
		printf("�������%d���ַ��͸��ַ���Ȩֵw:",i);
		fflush(stdin);
		scanf("%c%d",&ch[i],&w[i]);
		i++;
	}
	ch[i] = '\0';
	HuffmanCoding(HT,HC,w,n);  			//���ɹ��������������ַ���Ӧ�Ĺ��������룬�ֱ����HT����HC��
	if(( save = fopen("htfTree.txt","wb")) == NULL )
	{ 
		printf("Open file fail......\n");
		exit(0);
	}
	tem = n;  					//���ַ�����Сת�����ַ���ʽд�뵽�ļ���
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
	for( i = 1; i <= n; i++ )		//�ֱ����ļ�����Ļ��������ַ�����Ӧ�Ĺ���������
	{ 
		fputc(ch[i],save);  
		printf("%c\t",ch[i]);
		fputc('\t',save);
		fputs(HC[i],save);  
		printf("%s\n",HC[i]);
		fputc('\n',save);
	}
	for(i = 1; i <= 2 * n - 1; i++ )	//������������������parent,lchild,rchild�ֱ�д�뵽�ļ���
	{ 
		tem = HT[i].parent;		//��i����parentת�����ַ���д�뵽�ļ���
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
		
		tem = HT[i].lchild;  		//��i����lchildת�����ַ���д�뵽�ļ���
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
		
		tem = HT[i].rchild;		//��i����rchildת�����ַ���д�뵽�ļ���
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
	���ݹ��������뽫�û�ָ����txt�ļ��е��ַ�����,�������ñ���洢���û�ָ����txt�ļ�
*/
void Encoding(HuffmanTree &HT, HuffmanCode &HC, char ch[])
{ 
	FILE *ToBeTran,*CodeFile;
	char ToBeTran_Name[100],CodeFile_Name[100];
	int i;
	char c;
	printf("��������Ҫ���б�����ļ����ļ���:");
	scanf("%s",ToBeTran_Name); 
	if(( ToBeTran = fopen(ToBeTran_Name,"rb")) == NULL )
	{ 
		printf("Open file fail......\n");
		exit(0);
	}
	printf("��������������ʾ����Ϣ���洢�����ļ����ļ���:");
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
				printf("%c---%s\n",c,HC[i]);  //��ӡc��Ӧ�Ĺ���������
				break;
			}
	}
	printf("\n");
	printf("����ɹ�!\n");
	fclose(ToBeTran);
	fclose(CodeFile);
}
/*
	���û��ɹ�����������Ϣ��ʾ�ĵı����ļ��������룬���������û�ָ����.txt�ļ���
*/
void Decoding(HuffmanTree HT, char ch[] , int n)
{ 
	int p,i = 1;
	char code[1000],c;
	char CodeFile_Name[100],TextFile_Name[100];
	p = 2 * n - 1;
	FILE *CodeFile,*TextFile;
	printf("��������Ҫ����ļ���:");
	scanf("%s",CodeFile_Name);  
	if(( CodeFile = fopen(CodeFile_Name,"rb")) == NULL )
	{ 
		printf("Open file fail......\n");
		exit(0);
	}
	printf("�����������ַ��洢�����ļ����ļ���:");
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
	code[i] = '\0';  				//���ļ���ȡ�ַ����洢��code[]������
	i = 1;
	while ( code[i] != '\0' && p != 0 )		//������code[]�еĹ����������������
	{ 
		if ( code[i] == '0' )
			p=HT[p].lchild;  		//�������֧
		else
			p = HT[p].rchild; 		//�����ҷ�֧
		if (!HT[p].lchild&& !HT[p].rchild)	//����Ҷ�ӽ��
		{ 
			fputc(ch[p], TextFile);  
			printf("%c",ch[p]);    
			p = 2 * n - 1;  		//���´�����������������
		}
		i++;
	}
	printf("\n");
	printf("����ɹ�!\n");
}
/*
	���ļ���ȡ��������
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
	fgets(c,10,htfTree); 					//��ȡ��������Ҷ�ӽ��������ַ�����ʾ��ʽ
	i = 0;   
	while( c[i] != '\n' )					//���ַ�����ʽת����������ʽ
		i++;
	n = 0;
	for( j = 0; j < i; j++ )  
		n = 10 * n + c[j] - '0';			//���Ҷ�ӽ����n
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *)); 
	HT = (HuffmanTree)malloc((2 * n) * sizeof(HTNode));  
	i = 1;
	while( i <= n )
	{
		ch[i] = fgetc(htfTree);  			//��ȡ�ַ����е�һ���ַ�
		HC[i] = (char *)malloc((10)*sizeof(char));	//�������ڴ洢��ȡ�����ַ����е��ַ��Ĺ���������Ŀռ�
		fgetc(htfTree); 				//����\t�����
		ch1 = fgetc(htfTree);  				//��ȡ���������룬�洢����Ӧ��HC[i][]������
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
	while( i < 2 * n - 1 )					//��ȡ���������ĸ�������parent,lchild,rchild.����ֵ����������HT��
	{  
		ch1 = fgetc(htfTree); 				//��ȡparent���ַ�����ʽ,�洢��c[]�У�������ת����������ʽ������HT[i].parent
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
		ch1 = fgetc(htfTree); 				//��ȡlchild���ַ�����ʽ��������ת����������ʽ������HT[i].lchild
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
		ch1 = fgetc(htfTree); 				//��ȡrchild���ַ�����ʽ��������ת����������ʽ������HT[i].rchild
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
	��ӡ�����ַ�����Ӧ�Ĺ���������
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
	int n,Init_Mode = No;//Init_Mode = No ��ʾ�ڴ���û�й�����������Ϣ
	int sel; 
	do
	{
		printf("\n*************��������/������*************\n");
		printf("*	1---��ʼ��			*\n");
		printf("*	2---����			*\n");
		printf("*	3---����			*\n");
		printf("*	4---��ӡ			*\n");
		printf("*	5---�˳�			*\n");
		printf("*****************************************\n");
		printf("����������ѡ��(1-5):");
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
			default :printf("���������д�������ѡ��.\n");		
		}	 
	}while(sel!=5); 
	return 0;
}

