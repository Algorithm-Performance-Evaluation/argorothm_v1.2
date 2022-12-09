#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<memory.h>

typedef struct Point
{
	char preason[300];
	char mreason[300];
	int point;
}Point;

typedef struct element
{
	int number;
   	char name[10];
   	Point point;
}element;

typedef struct TreeNode
{
   element key;
   struct TreeNode* left;
   struct TreeNode* right;
}TreeNode;

int compare(element e1, element e2)
{
	if(e1.number > e2.number)
	{
		return -1;
	}
	else if(e1.number < e2.number)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

void display(TreeNode* p)
{
	if(p!=NULL)
	{
		display(p->left);
		printf("\n*-----------------------*\n");
		printf("\n학번: %d\n",p->key.number);
		printf("\n이름: %s\n",p->key.name);
		printf("\n상점: %d\n",p->key.point.point);
		printf("\n최근상점 받은 이유 : %s\n",p->key.point.preason);
		printf("\n최근별점 받은 이유 : %s\n",p->key.point.mreason);
		printf("\n*-----------------------*\n");
		display(p->right);
	}
} 

//이진탐색트리 탐색함수
TreeNode* search(TreeNode* root, element key)
{
	TreeNode* p = root;
	while(root!=NULL)
	{
		if(compare(key,p->key)==0)
		{
			return p;
		}
		else if(compare(key,p->key)==-1)
		{
			p=p->left;
		}
		else
		{
			p=p->right;
		}
	}
	
	return p;
} 

TreeNode* new_node(element item)
{
	TreeNode* temp = (TreeNode*)malloc(sizeof(TreeNode));//노드 동적할당
	
	temp->key = item;
	temp->left = temp->right = NULL; 
	printf("학생 등록 완료");
	return temp;
}

TreeNode* insert_node(TreeNode* node, element key)
{
	if(node==NULL)
	{
		return new_node(key);
	}
	else if (compare(key,node->key)==-1)
	{ 
		node->left = insert_node(node->left,key);
	}
	else if (compare(key,node->key)==1)
	{
		node->right = insert_node(node->right,key);
	}
	else
	{
		printf("이미 있는 학생입니다.");
	}
	
	return node;
}

//이진 탐색 트리와 키가 주어지면 키가 저장된 노드를 삭제하고 새로운 루트노드반환 
TreeNode* delete_node(TreeNode* root, element key){
	if(root==NULL)
	{
		return root;
	}
	if (compare(key,root->key)==-1)
	{ 
		root->left = delete_node(root->left,key);
	}
	if (compare(key,root->key)==1) 
	{
		root->right = delete_node(root->right,key);
	}
	else
	{
		if(root->left==NULL)
		{
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
		else
		{
			TreeNode* temp = root->left;
			free(root);
			return temp;
		}
	}
	
	return root;
}

void menu()
{
	printf("\n*------------ 상벌점 시스템 -----------*\n");
	printf("\n\t1 : 학생 등록\n");
	printf("\n\t2 : 학생 삭제\n");
	printf("\n\t3 : 상점 추가\n");
	printf("\n\t4 : 별점 추가\n");
	printf("\n\t5 : 학생 검색\n");
  	printf("\n\t6 : 학생 리스트\n");
	printf("\n\t7 : 종료\n");
	printf("\n*-----------------------*\n");
	printf("\n메뉴 입력 >> ");
}

int main()
{
	int command;
  	int pluspoint, minuspoint;
	element e;
	TreeNode* root = NULL;
	TreeNode* r = NULL;
	TreeNode* tmp;
	do
	{
		menu();
		
		scanf("%d",&command);
		e.number = NULL;
		e.point.point = NULL;
		switch(command)
		{
			case 1:
				printf("학생 이름: ");
				scanf("%s", e.name);
				printf("학번:");
				scanf(" %d",&e.number);
				e.point.point = 0;
				root =  insert_node(root, e);
				break; 
				
			case 2:
				printf("학번: ");
				scanf("%d",&e.number);
				tmp = search(root,e);//탐색함수 실행
				if(tmp!= NULL)
				{
					root = delete_node(root,e);// 삭제 함수 실행
					printf(">> 삭제 완료");
				}
				else
				{
					printf(">> 학생을 찾을 수 없습니다.");
					break;
				}
				break;
				 
			case 3:
				printf("학번: ");
				scanf("%d",&e.number);
        		printf("추가 할 점수: ");
        		scanf("%d", &pluspoint);
        		
				tmp = search(root,e);//탐색함수 실행
				if(tmp!= NULL)
				{
					tmp->key.point.point = tmp->key.point.point + pluspoint;
				}
				else
				{
					printf(">> 그런 학생 없습니다.");
				}
				
				printf("이유: ");
        		scanf("%s", &tmp->key.point.preason);
				break;
				
			case 4:
				printf("학번: ");
				scanf("%d",&e.number);
        		printf("벌점 점수: ");
        		scanf("%d", &minuspoint);
				tmp = search(root,e);//탐색함수 실행
				if(tmp!=NULL)
				{
					tmp->key.point.point = tmp->key.point.point - minuspoint;
				}
				else
				{
					printf(">> 그런 학생 없습니다.");
				}
				printf("이유: ");
        		scanf("%s", &tmp->key.point.mreason);
				break;
				
			case 5:
				printf("학번: ");
				scanf("%d",&e.number);
				tmp = search(root,e);//탐색함수 실행
				if(tmp!= NULL)
				{
					printf("\n*-----------------------*\n");
					printf("\n학번: %d\n",tmp->key.number);
					printf("\n이름: %s\n",tmp->key.name);
					printf("\n상점: %d\n",tmp->key.point.point);
					printf("\n최근 상점 받은 이유 : %s\n",tmp->key.point.preason);
					printf("\n최근 별점 받은 이유 : %s\n",tmp->key.point.mreason);
					printf("\n*-----------------------*\n");
				}
				else
				{
					printf(">> 그런 학생 없습니다.");
				}
				break;
				
      		case 6:
          		display(root);
          		printf("\n");
          		break;
		}	 	
	}while(command!=7);
	
	printf(">종료되었습니다.");
	
	return 0; 
}


