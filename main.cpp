#include <stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<math.h>

#define MAXQSIZE 100 //队列可能达到的最大长度
static int i = 1;



typedef struct QNode
{
	int bianhao;//队内成员取到的号码
	struct QNode* next;
}QNode, * QueuePtr;
typedef struct Queue
{
	QueuePtr front;//队头指针
	QueuePtr rear;//队尾指针
	int size;
}Queue;//创建链式队列

void initQueue(Queue* q)//队列的初始化
{
	QNode *p;
	p=(QNode*)malloc(sizeof(QNode));
	q->front = q->rear = p;
	if (!q->front)//初始化失败退出
	{
		return;
	}
	q->front->next = NULL;
	p->next=NULL;
}




int isEmpty(Queue *Q)
{
	return (Q->rear-Q->front+MAXQSIZE)%MAXQSIZE;
}

struct VIPInfo 
{
    int number;
    int password;
};
struct VIPInfo vip_info[] = {// 合法的VIP卡号和密码
    {100, 1111},
    {200, 2222},
    {300, 3333},
    {400, 4444},
    {500, 5555}
};
// 预设的系统查询卡号和密码
const int system_query_card_number = 000;
const int system_query_password = 1111;


Queue s,s1, s2, s3;//创建一个总队列，三个分队列窗口

//入队操作
 void EnQueue(Queue *s,int x)
 {
     //声明一个节点类型的指针变量用来存储要入队的元素
     QNode *p;
     p=(QNode*)malloc(sizeof(QNode));
     if(!p)
	 {
        printf("内存分配失败\n\n");
        return;
     }
     p->bianhao=x;        //指针指向的节点的数据域存放x
     p->next=NULL;     //指针指向的节点的指针域置为空
     s->rear->next=p;   //将队列的尾指针的指针域next指向指针p所指的节点
     s->rear=p;         //将队列的尾指针向后移一位，指向刚入队的节点的位置
 }

int  DeQueue(Queue* q, int e)//队列删除
{
	if (q->front == q->rear)
	{//队列为空队列
		return 1;
	}
	QNode* p = (QNode*)malloc(sizeof(QNode));
	p = q->front->next;
	e = p->bianhao;
	q->front->next = p->next;
	if (q->rear == p)
	{
		q->rear = q->front;
	}
	q->size--;
	free(p);
}

void vip(Queue* q, int i)//vip头插法
{
	QNode* p = (QNode*)malloc(sizeof(QNode));
	if (q->front == q->rear)
	{
		p->bianhao = i;
		p->next = NULL;
		q->rear->next = p;
		q->rear = p;
	}
	else
	{
		p->bianhao = i;
		p->next = q->front->next;
		q->front->next = p;
	}
}




void mainmenu() //主菜单
{
    printf("\n**********欢迎光临中国银行股份有限公司泰山分行**********\n");
    printf("\n                                                     \n");
    printf("          1      顾客到达\n");
    printf("          2      顾客离开\n");
    printf("          3      查看业务办理\n");
    printf("          4      查看排队情况\n");
    printf("          5      系统查询\n");
    printf("          6      退出\n\n");
    printf("          提示：请按回车键进行下一步操作\n");
    printf("\n                                                     \n");
    printf("*******************************************************\n");
    printf("请输入：");

	int number;
    scanf("%d",&number);
    switch(number)
    {
        case 1:
        {
            arrivemenu();
			mainmenu();
			break;
        }
        case 2:
        {
            leavemenu();
			mainmenu();
			break;
        }
        case 3:
        {
            nowmenu();
			mainmenu();
			break;
        }
		case 4:
		{
			nowpeoplemenu();
		}
		case 6:
		{
			exit(0);
		}
    }
}

void arrivemenu() //顾客到达界面菜单
{
    printf("**********顾客到达界面**********\n\n");
    printf("请输入你的客户类型:VIP顾客请按1；普通顾客请按2.\n");
    int num;
    printf("请输入：");
    scanf("%d",&num);
    switch(num)
    {
        case 1:
        {
            printf("\n请输入您的卡号：");
            int idn,ids;
            scanf("%d",&idn);
            printf("\n请输入您的密码：");
            scanf("%d",&ids);
            //缺打开文件对照账号密码
            vipmenu(idn,ids);
        }
        case 2:
        {
            ordinarymenu();
        }
    }
}

int vipmenu(int inputNumber, int inputPassword) //VIP菜单
{
	int size = sizeof(vip_info) / sizeof(vip_info[0]);
    for (int i = 0; i < size; i++) {
        if (vip_info[i].number == inputNumber && vip_info[i].password == inputPassword) 
		{
            printf("尊敬的VIP顾客您好，请您直接到VIP区办理业务！\n"); // VIP账户验证成功
            return 1;
        }
    }
    printf("您的输入有误\n");
    return 0; // 账户验证失败
}


void vip1()   //VIP顾客输入密码
{
    int inputNumber, inputPassword;
    printf("请输入您的卡号：");
    scanf("%d", &inputNumber);
    printf("请输入您的密码：\n");
    scanf("%d", &inputPassword);
    if (!vipmenu(inputNumber, inputPassword))
    {
        return vip1(); 
    }
}


void ordinarymenu()//选择窗口插入
{
	if(s1.front == s1.rear)
	{
		EnQueue(&s1,s1.size);
	}
	while(s1.front != s1.rear)
	{
		if(s2.front == s2.rear)
		{
			EnQueue(&s2,s2.size);
		}
	}
	while((s1.front != s1.rear)&&(s2.front != s2.rear))
	{
		if(s3.front == s3.rear)
		{
			EnQueue(&s3,s3.size);
		}
	}
	s.size++;
	printf("尊敬的普通顾客，您的业务号为%d",s.size);
	int a = s.size % 3;
	if((s1.front != s1.rear)&&(s2.front != s2.rear)&&(s3.front != s3.rear))
	{
		if(a==1)
		{
			EnQueue(&s1,s1.size);
		}
		if(a==2)
		{
			EnQueue(&s2,s2.size);
		}
		if(a==3)
		{
			EnQueue(&s3,s3.size);
		}
	}
	mainmenu();
}

void leavemenu()  //顾客离开界面菜单
{
    int customer_num, counter_no, score;
    printf("**********顾客离开页面**********\n\n");
    printf("请输入离开顾客的编号：");
    scanf("%d", &customer_num);
    printf("为了改善服务质量，请您对我们的服务进行评价。谢谢！\n");
    printf("请输入您所办理业务的柜台号（1-3）： ");
    scanf("%d", &counter_no);
	printf("您所办理业务的柜台号为%d.\n", counter_no);
    printf("请输入您的评分(1-5)：\n");
    printf("1分......非常不满意;\n2分......不满意;\n3分......一般满意;\n4分......比较满意;\n5分......非常满意\n");
    printf("请输入: ");
    scanf("%d", &score);

	int satisfaction_scores[50],satisfaction_counts[50];// 更新柜台的评分和次数
    satisfaction_scores[counter_no - 1] += score;
    satisfaction_counts[counter_no - 1]++;
    float average_satisfaction = satisfaction_scores[counter_no - 1] / satisfaction_counts[counter_no - 1];
	printf("您的评分为%d。\n", score);
    printf("%d号柜台的平均满意度为%.2f。感谢您的评分，谢谢！\n", counter_no, average_satisfaction);

    mainmenu(); // 返回主菜单
}

void nowmenu()    //业务查询界面菜单（查看现在窗口的人）
{
     printf("**********业务查询页面**********\n\n");
    printf("正在办理业务的顾客编号为：\n");
    printf("一号柜台          二号柜台          三号柜台\n"); 
    if (!isEmpty(&s1) && s1.front->next) 
	{
        printf("%d号顾客           ", s1.front->next->bianhao);
    } 
	else 
	{
        printf("                   ");
    }

    if (!isEmpty(&s2) && s2.front->next) 
	{
        printf("%d号顾客           ", s2.front->next->bianhao);
    } 
	else 
	{
        printf("                   ");
    }

    if (!isEmpty(&s3) && s3.front->next) 
	{
        printf("%d号顾客           ", s3.front->next->bianhao);
    } 
	else 
	{
        printf("                   ");
    }
    printf("\n");
}

void nowpeoplemenu()  //查询排队人数
{
	int a;
	a = s.size % 3;
	printf("**********排队查询页面**********\n\n");
	printf("正在等候办理业务的顾客编号为：%d ",s.front->next->bianhao);
	printf("您的前面一共有%d人在排队，请您稍后！",a);
	mainmenu();
}



int main()
{
    mainmenu();
   

    




    return 0;
}
