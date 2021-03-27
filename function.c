#include"telbook.h"
int arrnum = 2; 
//插入函数
struct item* insert(struct item* N, int x)
{
	int i = 0;
	//插入位置溢出
	if (x<1 || x>MAXPERSON)
	{
		puts("插入位置不合法!");
		exit(1);
	}
	//插入位置在边界
	else if (x == MAXPERSON)
	{
		int i;
		int s;
		struct item* p;
		//arrnum初始为2,初始化后加1
		p = (struct item*)malloc(sizeof(struct item) * MAXPERSON * arrnum);
		arrnum++;
		//数据移动到新数组
		for (i = 0;i < x;i++)
		{
			*N = *p;
			N++;
			p++;
		}
		free(N);
		//判断输入是否有错误
		s = get(&p[x-1]);
		if (!s)
		{
			puts("输入错误！");
			exit(1);
		}
		return p;
	}
	//插入位置在一到九十九
	else
	{
		int s = 1;
		//判断输入是否有错误
		s = get(&N[x-1]);
		if (!s)
		{
			puts("输入错误！");
			exit(1);
		}
	}
}
//初始化函数
struct item* init(void)
{
	struct item* N;
	puts("初始化电话本");
	N = (struct item*)malloc(sizeof(struct item)*MAXPERSON);
	if (N)
		puts("初始化成功！");
	else
	{
		puts("初始化错误！");
		exit(1);
	}
	return N;
}
//输入函数，不判断数组下标，提供互动
int  get(struct item* L)
{
	printf("请输入姓名:\n");
	s_gets(L->name, MAXSIZE);
	//name初始化为0，输入成功就不是0，下同
	if (L->name[0])
	{
		puts("姓名输入成功！");
	}
	else
	{
		printf("\n姓名输入错误！\n");
		return 0;
	}
	puts("现在请输入电话号码:");
	s_gets(L->telnumber, TELSIZE);
	if (L->telnumber[0])
	{
		puts("电话号码输入成功！");
	}
	else
	{
		puts("电话号码输入错误！");
		return 0;
	}
	return 1;
}
//删除函数，判断数组下标
int delete (struct item* N, int x)
{
	int i;
	struct item* p;
	checknum(x);
	p = &N[x-1];
	printf("\n开始删除第%d位电话本联系人的姓名\n",x);
	for (i = 0;i < MAXSIZE;i++)
		p->name[i] = '\0';
	puts("开始删除电话号码\n");
	for (i = 0; i < TELSIZE; i++)
		p->telnumber[i] = '\0';
	//或memset(p->name,0,sizeof(p->name));

	//检测名字或号码的最后一位是否清零
	if (p->name[MAXSIZE - 1] && p->telnumber[TELSIZE - 1])
	{
		puts("\n删除失败！\n");
		return 0;
	}
	else
		puts("删除成功!");
		return 1;
}
//修改函数，判断结构数组下标
int revise(struct item* N, int x)
{
	int s;

	printf("\n开始修改第%d位电话本联系人\n", x);
	checknum(x);
	s = get(&N[x-1]);
	//用输入函数判断是否修改成功
	if (!s)
	{
		puts("\n修改错误！\n");
		exit(1);
	}
}

//通过位置查找联系人
struct item* checkbyloaction(struct item* N, int x)
{
	struct item* p;
	checknum(x);
	p = &N[x-1];
	if (p)
		printf("第%d位联系人，查找成功！", x);
	else
		return 0;
	
	if (p->name[0] && p->telnumber[0])
	{
		printf("该项联系人是%s\n", p->name);
		printf("%s的电话号码是%s\n", p->name, p->telnumber);
	}
	else
		puts("\n该项无联系人");
	return p;
}

//通过名字查找联系人
struct item* checkname(struct item* N)
{
	char name[MAXSIZE];
	int i = 1;
	struct item* p;
	p = &N[0]; //指针定向

	//读取待比较的名字
	puts("请输入名字");
	s_gets(name, MAXSIZE);

	while (strcmp(p->name, name) != 0 && i <= MAXPERSON)
	{
		p++;
		i++;
	}
if (p && i<= MAXPERSON)
	{
		puts("查找成功！");
		printf("第%d位联系人%s的电话号码是%s\n",i, 
			p->name, p->telnumber);
		return p;
	}
	else
	{
		puts("无此联系人!");
		return 0;
	}
}

//通过电话号码查找联系人
struct item* checktelnum(struct item* N)
{
	char telnum[TELSIZE];
	int i = 1;
	struct item* p;
	p = &N[0];

	//读取待比较的电话号码
	puts("请输入电话号码");
	s_gets(telnum,TELSIZE);

	while (strcmp(p->telnumber,telnum) != 0 && i <= MAXPERSON)
	{
		p++;
		i++;
	}
	if (p && i <= MAXPERSON)
	{
		puts("查找成功！");
		printf("电话号码为%s的联系人是%s，为第%d位联系人\n",
			p->telnumber,p->name, i);
		return p;
	}
	else
	{
		puts("无此联系人!");
		return 0;
	}
}

//输入并检查字符串
char* s_gets(char* st, int n)
{
	char* ret_val;
	int i = 0;

	ret_val = fgets(st, n, stdin);
	if (ret_val)
	{
		while (st[i] != '\n' && st[i] != '\0')
			i++;
		if (st[i] == '\n')
			st[i] = '\0';
		else
		{
			while (getchar() != '\n')
				continue;
		}
	}
	return ret_val;
}

//打印函数，打印所有联系人
void print(struct item* N)
{
	int flag = 0;
	int i = 1;
	struct item* p;
	p = &N[0];
	puts("开始打印全部联系人");
	while (p && i <= MAXPERSON)
	{
		if (p->telnumber[0] >= '0' && p->telnumber[0] <= '9')
		{
			printf("第%d位联系人，%s,电话号码是%s\n",
				i, p->name, p->telnumber);
			flag = 1;
		}
		else
		{
			//避免重复打印
			if(flag)
				puts("该位无联系人！");
			flag = 0;
		}
		p++;
		i++;
	}
	printf("打印完成!\n");
	return 0;
}

//检查输入的位置是否合法
void checknum(int x)
{
	//x大于100时，只有数组扩充后才能修改
	if (x < 1 ||
		(x > MAXPERSON && arrnum == 2) || x>MAXPERSON*arrnum)
	{
		puts("修改位置不合法！");
		exit(1);
	}
}

//菜单函数，提供选择界面和跳转和更高级的互动
int menu(struct item* N)
{
	char mark[15] = "**************";
	char s;

	printf("\n\n\n\n\n");
	printf("%+20s菜单界面%-20s\n\n",mark,mark);
	printf("%+20s插入联系人按\"a\"%-20s\n\n",mark,mark);
	printf("%+20s删除联系人按\"b\"%-20s\n\n", mark, mark);
	printf("%+20s修改联系人按\"c\"%-20s\n\n", mark, mark);
	printf("%+20s用位置查找联系人按\"d\"%-20s\n\n", mark, mark);
	printf("%+20s用名字查找联系人按\"e\"%-20s\n\n", mark, mark);
	printf("%+20s用电话号码查找联系人按\"f\"%-20s\n\n", mark, mark);
	printf("%+20s打印全部联系人按\"g\"%-20s\n\n", mark, mark);
	printf("%+20s退出菜单按\"n\"%-20s\n\n", mark, mark);

	printf("\n请输入您的操作:\n");
	while ((s = getchar()) == '\n')
		continue;

	while (1)
	{
		switch (s)
		{
		case 'a':
		{
			int i = 1;
			puts("\n您要新建第几位联系人:");
			if (scanf("%d", &i) == 0)
			{
				puts("输入错误！");
				free(N);
				exit(1);
			}
			getchar();
			flag = insert(N, i);
			menu(N);//输入n时结束
			break;
		}
		case 'b':
		{
			int i = 0;
			puts("\n您要删除第几位联系人:");
			if (scanf("%d",&i) == 0)
			{
				puts("输入错误，请重试！");
				free(N);
				exit(1);
			}
			getchar();
			delete(N, i);
			menu(N);
			break;
		}
		case 'c':
		{
			int i = 0;
			puts("\n您要修改第几位联系人:");
			if (scanf("%d", &i) == 0)
			{
				puts("输入错误，请重试！");
				free(N);
				exit(1);
			}
			getchar();
			revise(N, i);
			menu(N);
			break;
		}
		case 'd':
		{
			int i = 0;
			puts("开始查找");
			puts("请输入联系人的位数:");
			if (scanf("%d", &i) == 0)
			{
				puts("输入错误,请重试!");
				free(N);
				exit(1);
			}
			getchar();
			checkbyloaction(N, i);
			menu(N);
			break;
		}
		case 'e':
		{
			puts("开始查找");
			getchar();
			checkname(N);
			menu(N);
			break;
		}
		case 'f':
		{
			puts("开始查找");
			getchar();
			checktelnum(N);
			menu(N);
			break;
		}
		case 'g':
		{
			print(N);
			menu(N);
			break;
		}
		case 'n':
		{
			puts("再见！");
			free(N);
			exit(1);
		}
		default:
		{
			puts("操作输入错误!\n");
			exit(1);
		}
		}
	}
}