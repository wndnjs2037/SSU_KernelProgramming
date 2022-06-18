#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/module.h>
#include <linux/io.h>
#include <linux/uaccess.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DCLab");
MODULE_DESCRIPTION("Raspberry Pi GPIO LED Device Module");

#define BCM_IO_BASE 0xFE000000 /* Raspberry Pi 4의 I/O Peripherals 주소 */
#define GPIO_BASE (BCM_IO_BASE + 0x200000) /* GPIO 컨트롤러의 주소 */
#define GPIO_SIZE (256) /* 0x7E2000B0 – 0x7E2000000 + 4 = 176 + 4 = 180 */

/* GPIO 설정 매크로들 (이전 시간 배웠던 것 참조) */
#define GPIO_IN(g) (*(gpio+((g)/10)) &= ~(7<<(((g)%10)*3))) /* 입력 설정 */
#define GPIO_OUT(g) (*(gpio+((g)/10)) |= (1<<(((g)%10)*3))) /* 출력 설정 */
#define GPIO_SET(g) (*(gpio+7) = 1<<g) /* 비트 설정 */
#define GPIO_CLR(g) (*(gpio+10) = 1<<g) /* 설정된 비트 해제 */
#define GPIO_GET(g) (*(gpio+13)&(1<<g)) /* 현재 GPIO의 비트에 대한 정보 획득 */

/* 디바이스 파일의 주 번호와 부 번호 */
#define GPIO_MAJOR 200 //이 번호 안쓰고 자동으로 할당받아도 됨
#define GPIO_MINOR 0 //이 번호 안쓰고 자동으로 할당받아도 됨
#define GPIO_DEVICE "gpioled" // 디바이스 디바이스 파일의 이름
#define GPIO_LED 18 // LED 사용을 위한 GPIO의 번호

volatile unsigned *gpio; // I/O 접근을 위한 volatile 변수
static char msg[BLOCK_SIZE] = {0,}; // 유저프로그램이 쓴 값을 저장하는데 사용

/* 입출력 함수를 위한 선언 */
static int gpio_open(struct inode *, struct file*);
static ssize_t gpio_read(struct file *, char *, size_t, loff_t *);
static ssize_t gpio_write(struct file *, const char *, size_t, loff_t *);
static int gpio_close(struct inode *, struct file *);

/* 유닉스 입출력 함수들의 처리를 위한 구조체 */
static struct file_operations gpio_fops = {
.owner = THIS_MODULE,
.read = gpio_read,
.write = gpio_write,
.open = gpio_open,
.release = gpio_close,
};

struct cdev gpio_cdev;
struct class *myclass;
struct device *mydevice;

int main(int argc, char **argv)
{
	int gno, i, mem_fd;
	void *gpio_map;
		
	if(argc < 2) {
		printf("Usage : %s GPIO_NO\n", argv[0]);
		return -1;
	}
	
	gno = atoi(argv[1]);
	/* /dev/mem 디바이스 열기 */
	if ((mem_fd = open("/dev/mem", O_RDWR | O_SYNC) ) < 0) {
		perror("open() /dev/mem\n");
		return -1;
	}

	/* GPIO와 mmap */
	gpio_map = mmap(NULL, GPIO_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, mem_fd, GPIO_BASE);
	if (gpio_map == MAP_FAILED) {
		printf("[Error] mmap() : %d\n", (int)gpio_map);
		perror -1;
	}
}


int init_module(void)
{
	/* 문자 디바이스를 등록한다. */
	/* 문자 디바이스를 위한 구조체를 초기화한다. */
	/* 문자 디바이스를 추가한다. */
	/* 문자 디바이스 파일을 생성한다. (나중에 유저가 해도 됨) */

	/* 장치파일 생성 부분 */
	myclass = class_create(THIS_MODULE, "mycharclass");
	if(IS_ERR(myclass)){
		unregister_chrdev_region(gpio_cdev, 1);
		retrun PTR_ERR(myclass);
	}

	mydevice = device_create(myclass, NULL, gpio_cdev, NULL, "mydevicefile");
	if(IS_ERR(mydevice)){
		class_destroy(myclass);
		unregister_chrdev_region(gpio_cdev, 1);
		return PTR_ERR(mydevice);
	}

	/* 사용할 메모리를 할당한다. */
	map = ioremap(GPIO_BASE, GPIO_SIZE);

	gpio = (volatile unsigned int *)map;
}

void cleanup_module(void)
{
	/* 문자 디바이스의 등록을 해제한다. */
	/* 문자 디바이스의 구조체를 해제한다. */

	kfree(gpio);
	cdev_del(gpio_cdev);
	device_destroy(myclass, gpio_cdev);
	class_destroy(myclass);
	unregister_chrdev_region(gpio_cdev, 1);
	
	
	/* 매핑된 메모리를 삭제한다. */
	if (gpio) {
		iounmap(gpio);
				}
}

static int gpio_open(struct inode *inod, struct file *file)
{

	printk("%s\n", __FUNCTION__);
	printk("%s\n", GPIO_MAJOR);
	printk("%s\n", GPIO_MINOR);

	return 0;
}

static int gpio_close(struct inode *inod, struct file *file)
{
	printk("%s\n", __FUNCTION__);
	printk("%s\n", GPIO_MAJOR);
	printk("%s\n", GPIO_MINOR);

	return 0;

}

static ssize_t gpio_read(struct file *inode, char *buff, size_t len, loff_t *off)
{
	if((buf == NULL) || ( len < 0))
		return -EINVAL
	
}

static ssize_t gpio_write(struct file *inode, const char *buff, size_t len, loff_t *off)
{
	if((buf == NULL) || ( len < 0))
		return -EINVAL

}

