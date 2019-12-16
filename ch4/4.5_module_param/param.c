#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/moduleparam.h>

// 모듈 매개변수로 사용하기 위해서는 사전에 선언되어 있어야 함

static int BUF_SIZE = 50;

static int onevalue = 1;
static char *twostring = NULL;

// module_param() 매크로
module_param(onevalue, int, 0);
module_param(twostring, charp, 0);

static int hello_init(void)
{
	printk("Hello, world [onevalue =%d twostring=%s]\n",
		onevalue, twostring);
	return 0;
}

static void hello_exit(void)
{
	printk("Goodbye, world\n");
}

module_init(hello_init);
module_exit(hello_exit);

MODULE_LICENSE("Dual BSD/GPL");