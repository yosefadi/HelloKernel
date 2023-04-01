
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/fs.h>
#include <asm/uaccess.h>	/* for put_user */

int init_module(void);
void cleanup_module(void);
static int device_openNIM(struct inode *, struct file *);
static int device_openName(struct inode *, struct file *);
static int device_release(struct inode *, struct file *);
static ssize_t device_readNIM(struct file *, char *, size_t, loff_t *);
static ssize_t device_readNama(struct file *, char *, size_t, loff_t *);
static ssize_t device_write(struct file *, const char *, size_t, loff_t *);

#define SUCCESS 0
#define DEVICE_NAME "HelloKernel"	/* Dev name as it appears in /proc/devices   */
#define BUF_LEN 80		/* Max length of the message from the device */

static int MajorNIM;		/* Major number assigned to our device driver */
static int MajorNama;
static char msg[BUF_LEN];	/* The msg the device will give when asked */
static char *msg_Ptr;

static struct file_operations fops1 = {
	.read = device_readNIM,
	.write = device_write,
	.open = device_openNIM,
	.release = device_release
};

static struct file_operations fops2 = {
	.read = device_readNama,
	.write = device_write,
	.open = device_openName,
	.release = device_release
};

int init_module(void)
{
        MajorNIM = register_chrdev(0, DEVICE_NAME, &fops1);
		MajorNama = register_chrdev(0, DEVICE_NAME, &fops2);

	if (MajorNIM < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", MajorNIM);
	  return MajorNIM;
	}
	if (MajorNama < 0) {
	  printk(KERN_ALERT "Registering char device failed with %d\n", MajorNama);
	  return MajorNama;
	}

	printk(KERN_INFO "Major NIM :  %d. \n", MajorNIM);
	printk(KERN_INFO "Major Nama : %d. \n", MajorNama);
	printk(KERN_INFO "the driver, create a dev file with\n");
	printk(KERN_INFO "'mknod /dev/HelloNIM c %d 0'.\n", MajorNIM);
	printk(KERN_INFO "'mknod /dev/HelloName c %d 0'.\n", MajorNama);
	printk(KERN_INFO "Try various minor numbers. Try to cat and echo to\n");
	printk(KERN_INFO "the device file.\n");
	printk(KERN_INFO "Remove the device file and module when done.\n");

	return SUCCESS;
}

void cleanup_module(void)
{
  unregister_chrdev(MajorNIM, DEVICE_NAME);
  unregister_chrdev(MajorNama, DEVICE_NAME);

}


static int device_openNIM(struct inode *inode, struct file *file)
{
  	sprintf(msg, "Hello Again, 20/456105/TK/50235! May your day be blessed!\n");
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

static int device_openName(struct inode *inode, struct file *file)
{
	sprintf(msg, "Hello, Yosef Adi Sulistyo. Have a nice day!\n");
	msg_Ptr = msg;
	try_module_get(THIS_MODULE);

	return SUCCESS;
}

static int device_release(struct inode *inode, struct file *file)
{	
	module_put(THIS_MODULE);

	return 0;
}

static ssize_t device_readNIM(struct file *filp,	/* see include/linux/fs.h   */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
	
	int bytes_readNIM = 0;

	
	if (*msg_Ptr == 0)
		return 0;

	while (length && *msg_Ptr) {

		put_user(*(msg_Ptr++), buffer++);

		length--;
		bytes_readNIM++;
	}

	
	return bytes_readNIM;
}

static ssize_t device_readNama(struct file *filp,	/* see include/linux/fs.h   */
			   char *buffer,	/* buffer to fill with data */
			   size_t length,	/* length of the buffer     */
			   loff_t * offset)
{
	
	int bytes_readNama = 0;

	if (*msg_Ptr == 0)
		return 0;

	while (length && *msg_Ptr) {

		put_user(*(msg_Ptr++), buffer++);

		length--;
		bytes_readNama++;
	}

	return bytes_readNama;
}

static ssize_t
device_write(struct file *filp, const char *buff, size_t len, loff_t * off)
{
	printk(KERN_ALERT "Sorry, this operation isn't supported.\n");
	return -EINVAL;
}

MODULE_LICENSE("AGPL");
MODULE_AUTHOR("Yosef Adi Sulistyo");
MODULE_DESCRIPTION("A simple character device driver");