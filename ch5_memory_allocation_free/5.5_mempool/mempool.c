#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mempool.h>

#define MIN_ELEMENT		4
#define TEST_ELEMENT	4

typedef struct
{
	int number;
	char string[128];
}TEle;

int mempool_init(void)
{
	mempool_t *	mp;
	TEle * element[TEST_ELEMENT];
	int lp;

	printk("Module MEMPOOL test\n");

	memset(element, 0, sizeof(element));

	printk("call mempool_create\n");
	mp = mempool_create(MIN_ELEMENT, mempool_alloc_test, 
		mempool_free_test, NULL);

	printk("mempool allocate\n");
	for(lp = 0; lp<TEST_ELEMENT; lp++)
	{
		
	}
}

module_init(mempool_init);
module_exit(mempool_exit);
MODULE_LICENSE("Dual BSD/GPL");
