#include"telbook.h"
int main(void)
{	
	char s;
	struct item* telbook;
	int flag = 1;

	puts("是否初始化电话本(y or n)");
	while ((s = getchar()) == '\n')
		continue;
	if (s == 'y')
	{
		telbook = init();
		menu(telbook);
	}
	else
	{
		printf("完成!\n");
	}
	return 0;
}