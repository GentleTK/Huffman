#ifndef Huffman_Tree_h
#define Huffman_Tree_h

#include <stdio.h>

typedef struct
{
	unsigned int weight;
	unsigned int parent,lchild,rchild;
}HTNode, * HuffmanTree;  					//�洢���������Ľ������

typedef char * * HuffmanCode;  				//���ڴ洢�ַ����и����ַ���Ӧ�Ĺ���������

void strcpy(char *S1,char *S2)
{  
	int i = 0;
	while( S2[i] != '\0' )
	{
		S1[i] = S2[i];
		i++;
	}
	S1[i] = '\0';
}
/*
	��HT[1]��HT[t-1]���ҳ�Ȩֵ��С������S1��S2
*/
void Select(HuffmanTree HT,int t,int &s1,int &s2)
{ 
	int i = 1;
	s1 = s2 = 0;
	HT[0].weight = 65535;
	while( i <= t )			//��������Ȩֵ��С�Ľ��S1
	{ 
		if( HT[i].parent == 0 && HT[i].weight < HT[s1].weight )
			s1 = i;
		i++;
	}
	i = 1;
	while( i <= t )			//�������ҳ�S1��Ȩֵ��С�Ľ��S2
	{ 
		if( i != s1 && HT[i].parent == 0 && HT[i].weight < HT[s2].weight )
			s2 = i;
		i++;
	}
}
/*
	���ݸ����ַ���Ȩֵ�����������HT������Ӧ�Ĺ���������洢��HC��
*/
int HuffmanCoding( HuffmanTree &HT,HuffmanCode &HC,int *w,int n)
{ 
	int s1,s2,m,i,start;
	unsigned int c,f;
	HTNode * p;
	char *cd;
	if( n <= 1 ) return 0;
	m = 2 * n - 1;  												//�����������ܽ����Ϊm
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));				//����洢���������Ŀռ�
	for(p = HT + 1, i = 1; i <= n; ++i, ++p, ++w)					//������Ҷ�ӽ���weight������Ӧ��Ȩֵ��parent,lchild,rchild����Ϊ0
	{   
		p->weight = *(w+1);
		p->parent = p->lchild = p->rchild = 0; 
	}
	for( ; i <= m; ++i, ++p )										//��������Ҷ�ӽ���weight,parent,lchild,rchild����Ϊ0
	{  
		p->weight = p->parent = p->lchild = p->rchild = 0; 
	}
	for( i = n + 1; i <= m; ++i )									//���������������������Ҷ�ӽ�㸳ֵ
	{ 
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i; HT[s2].parent = i;
		HT[i].lchild = s1; HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char *));				//����ռ䣬���ڴ洢ָ��洢�����ַ���Ӧ������������ַ������ָ��
	cd = (char *)malloc(n * sizeof(char));   						//�������������������
	cd[n - 1] = '\0';  												//���������
	for( i = 1; i <= n; ++i)										//����ַ������������
	{ 
		start = n -1;   											//����������cd[]�е���ǰλ��
		for(c = i,f = HT[i].parent; f != 0; c = f, f = HT[f].parent)//��Ҷ�ӵ������������
			if(HT[f].lchild == c)
				cd[ --start ] = '0';
			else
				cd[ --start ] = '1';
			HC[i] = (char *)malloc((n - start)*sizeof(char));		//Ϊ��i���ַ��������ռ�
			strcpy(HC[i], &cd[start]);								//��cd[]�����startλ�õ�n-1λ�ø��Ƹ�HC[i]
	}
	free(cd); 														//�ͷſռ�
	return 1;
}

#endif