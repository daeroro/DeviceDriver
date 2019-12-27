#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/errno.h>
#include <linux/types.h>
#include <linux/fcntl.h>

#define	CALL_DEV_NAME	"calldev"
#define CALL_DEV_MAJOR	3

int call_open(struct inode * inode, struct file * filp)
{
	/*
		call_open() 함수는 디바이스 파일에 의해 디바이스 드라이버의 부 번호를 전달 받음
		
		MINOR 매크로를 이용해 부 번호만 추출하여 표시
	*/
	int num = MINOR(inode->i_rdev);

	printk("call open -> minor : %d\n", num);

	return 0;
}

loff_t call_llseek(struct file * filp, loff_t off, int whence)
{
	printk("call llseek -> off : %08X, whence : %08X\n", off, whence);

	return 0x23;
}

ssize_t call_read(struct file * filp, char * buf, size_t count,
					loff_t * f_pos)
{
	printk("call read -> buf : %08X, count : %08X\n", buf, count);
	return 0x33;
}

ssize_t call_write(struct file * filp, const char * buf, size_t count,
					loff_t * f_pos)
{
	printk("call write -> buf : %08X, count : %08X\n", buf, count);
	return 0x43;
}

/*
	디바이스 파일에 read(), write() 함수로 처리할 수 없는 내용을 처리하는 ioctl문

	- 디바이스 드라이버에서는 매개변수의 최대개수가 3 
*/
long call_ioctl(struct file * filp, unsigned int cmd, unsigned long arg)
{
	printk("call ioctl -> cmd : %08X, arg : %08X \n", cmd, arg);
	return 0x53;
}

int call_release(struct inode * inode, struct file * filp)
{
	printk("call release \n");
	return 0;
}

struct file_operations call_fops = 
{
	.owner 				= THIS_MODULE,
	.llseek				= call_llseek,
	.read				= call_read,
	.write				= call_write,
	.unlocked_ioctl		= call_ioctl,
	.open				= call_open,
	.release 			= call_release,
};

int call_init(void)
{
	int result;

	printk("call call_init\n");

	/*
		register_chrdev() 함수를 이용해 문자 디바이스 드라이버를 커널에 등록

		CALL_DEV_MAJOR로 정의된 240을 주 번호로, 
		CALL_DEV_NAME의 문자열을 디바이스 드라이버명으로 등록
		마지막 매개변수에는 디바이스 드라이버 file_operations 구조체 변수인 call_fops 주소를 대입
	*/
	result = register_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME, &call_fops);

	/*
		정상적으로 등록되지 않으면 0 보다 작은 값 -> 그 값을 반환값으로 사용하여 종료
	*/

	if(result < 0) return result;

	return 0;
}

void call_exit(void)
{
	printk("call call_exit\n");

	/*
		unregister_chrdev() 함수를 이용해 커널에 등록된 문자형 디바이스 드라이버를 제거
	*/
	unregister_chrdev(CALL_DEV_MAJOR, CALL_DEV_NAME);
}

/*
	insmod를 이용해 call_dev.ko를 커널에 삽입하면
	call_dev.c에 선언된 module_init 매크로에서 정의한 call_init() 함수가 호출됨
*/
module_init(call_init);
module_exit(call_exit);

MODULE_LICENSE("Dual BSD/GPL");
