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

int elecnt = 0;

/*
	mempool_alloc_test() 함수는 TEle 구조체 크기의 메모리를 kmalloc() 함수를 통하여 할당
	- 할당된 구조체의 number 필드에 할당 횟수 기록
*/
void * mempool_alloc_test(gfp_t gfp_mask, void *pool_data)
{
	TEle * data;
	printk("------> mempool_alloc_test\n");

	data = kmalloc(sizeof(TEle), gfp_mask);
	if(data != NULL) data->number = elecnt++;

	return data;
}

/*
	mempool_free() 함수로 mempool_free_test() 함수를 호출
	- 할당된 메모리를 다시 해제한다
*/
void mempool_free_test(void * element, void * pool_data)
{
	printk("------> call mempool_free_test\n");
	if(element != NULL) kfree(element);
}

int mempool_init(void)
{
	mempool_t *	mp;
	TEle * element[TEST_ELEMENT];
	int lp;

	printk("Module MEMPOOL test\n");

	memset(element, 0, sizeof(element));

	/*
		mempool_create() 함수를 호출해 메모리 할당 함수인 mempool_alloc_test() 함수와
		메모리 해제 함수인 mempool_free_test() 함수를 등록한다.
		- 사전에 할당되는 메모리 객체는 MIN_ELEMENT 이다

		성공적으로 할당되면, mp 구조체 안에 메모리 풀 관리자 구조체 주소가 저장됨
		- 메모리 풀 할당과 해제 함수는 할당된 주소 mp를 넘겨 주면된다.
	*/
	printk("call mempool_create\n");
	mp = mempool_create(MIN_ELEMENT, mempool_alloc_test, 
		mempool_free_test, NULL);

	/*
		mempool_alloc() 함수를 통해 메모리를 TEST_ELEMENT 만큼 할당한다.
		- 이 때 mempool_alloc_test() 함수가 호출된다.

		할당된 메모리를 sprintf() 함수를 이용해 할당된 횟수 필드인 number 값을 버퍼에 적은 후,
		printk() 함수를 사용하여 버퍼의 내용을 출력
	*/
	printk("mempool allocate\n");
	for(lp = 0; lp<TEST_ELEMENT; lp++)
	{
		element[lp] = mempool_alloc(mp, GFP_KERNEL);
		if(element[lp] == NULL) printk("allocate fail\n");
		else
		{
			sprintf(element[lp]->string, "alloc data %d\n",
					 element[lp]->number);
			printk(element[lp]->string);
		}
	}

	/*
		TEST_ELEMENT 수 만큼 mempool_free() 함수를 호출해 element[] 구조체를 해제 한다.
	*/
	printk("mempool free\n");
	for(lp=0; lp <TEST_ELEMENT; lp++)
	{
		if(element[lp] != NULL) mempool_free(element[lp], mp);
	}

	/*
		mempool_destroy() 함수를 호출하여 메모리 관리자를 소멸시킴
	*/
	printk("call mempool_destroy\n");
	mempool_destroy(mp);

	return 0;
}

void mempool_exit(void)
{
	printk("Module MEMPOOL Test End\n");
}

module_init(mempool_init);
module_exit(mempool_exit);
MODULE_LICENSE("Dual BSD/GPL");
