#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>
#include <linux/input.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/gpio.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/platform_device.h>
#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/poll.h>
#include <linux/sched.h>

#define ZLG72XX_NAME                	"zlg72xx"
#define ZLG72128_NAME		"zlg72128"                        
#define ZLG7290_NAME                	"zlg7290"
#define SET_VAL _IO('Z', 0)                    
#define GET_KEY _IO('Z', 1)
#define CONFIG_ZLG72XX_INPUT_DEVICE

unsigned int ZLG72128_ID = 1;
unsigned int ZLG7290_ID = 0;
unsigned int zlg72XX_major = 401;             
unsigned int zlg72XX_minor = 1;               

struct zlg72XX                  
{
	struct i2c_client *client;
	struct delayed_work work;
#ifdef CONFIG_ZLG72XX_INPUT_DEVICE                        
	struct input_dev *key;
#endif
	struct cdev cdev;
	int current_key;
	wait_queue_head_t readq;
	struct class *class;
#ifndef CONFIG_OF
	const struct i2c_device_id *id;
#endif
#ifdef CONFIG_OF
	const struct of_device_id *id_tree;
#endif
};

#ifdef CONFIG_ZLG72XX_INPUT_DEVICE                            
unsigned int key_value[65] = {
	0,
	KEY_D, KEY_NUMERIC_POUND, KEY_0, KEY_NUMERIC_STAR,  5,  6,  7,  8,
	KEY_C, KEY_9, KEY_8, KEY_7, 13, 14, 15, 16,
	KEY_B, KEY_6, KEY_5, KEY_4, 21, 22, 23, 24,
	KEY_A, KEY_3, KEY_2, KEY_1, 29, 30, 31, 32,
	33, 34, 35, 36, 37, 38, 39, 40,
	41, 42, 43, 44, 45, 46, 47, 48,
	49, 50, 51, 52, 53, 54, 55, 56,
	57, 58, 59, 60, 61, 62, 63, 64,
}; 
#endif

static int zlg72XX_hw_write(struct  zlg72XX *ctr_zlg72XX,  int len, size_t *retlen, char *buf)
{
	struct i2c_client *client = ctr_zlg72XX->client;                              
	int ret;
	struct i2c_msg msg[] = { 
		{ client->addr, 0, len, buf},   
	};
	ret =i2c_transfer(client->adapter, msg, 1);                                  
	if (ret < 0) 
	{
		dev_err(&client->dev, "i2c write error/n");
		return -EIO;
	}
	*retlen = len;
	return 0;
}

static int zlg72XX_hw_read(struct zlg72XX *ctr_zlg72XX , int len, size_t *retlen, char *buf)
{
	struct i2c_client *client = ctr_zlg72XX->client;
	int ret;
	struct i2c_msg msg[] = { 
		{ client->addr, 0, len, buf},   
		{ client->addr, I2C_M_RD, len, buf },
	};
	ret =i2c_transfer(client->adapter, msg, 2);                                     
	if (ret < 0) 
	{
		dev_err(&client->dev, "i2c read error/n");
		return ret;
	}
	*retlen = len;
	return 0;
}

static int zlg72XX_open(struct inode *inode, struct file *file)
{
	struct cdev* open_cdev = inode->i_cdev;
	struct zlg72XX* open_zlg72xx = container_of(open_cdev,struct zlg72XX,cdev);
	file->private_data = open_zlg72xx;
#ifndef CONFIG_ZLG72XX_INPUT_DEVICE                                                
	schedule_delayed_work(&open_zlg72xx->work, HZ / 5);
#endif	
	return 0;
}

static int zlg72XX_release(struct inode *inode, struct file *file)
{
#ifndef CONFIG_ZLG72XX_INPUT_DEVICE                                                 
	cancel_delayed_work_sync(&release_zlg72xx->work);
#endif
	return 0;
}

static void zlg72XX_work(struct work_struct *work) 
{
	struct zlg72XX *ctr_zlg72xx = container_of(work, struct zlg72XX, work.work);
	unsigned char val = 0;
	size_t len;
	unsigned char status = 0;
	
	zlg72XX_hw_read(ctr_zlg72xx, 1, &len, &status);                  	
	if(status & 0x1) 
	{                                                 	
		val = 0x1;                                           
		zlg72XX_hw_read(ctr_zlg72xx, 1, &len, &val);        	      
		if (val == 0) 
		{                                         	    
			val = 3;
			zlg72XX_hw_read(ctr_zlg72xx, 1, &len, &val);             
			if (val == 0 || val == 0xFF)
				goto out;
		}
#ifndef CONFIG_OF
		if(ctr_zlg72xx->id->driver_data == ZLG7290_ID)
		{                		
#endif	
#ifdef CONFIG_OF
		if((unsigned int *)(ctr_zlg72xx->id_tree->data) == &ZLG7290_ID)
		{
#endif
			if (val > 56) 
			{
				switch (val) 
				{                                         	
					case 0xFE: val = 57; break;
					case 0xFD: val = 58; break;
					case 0xFB: val = 59; break;
					case 0xF7: val = 60; break;
					case 0xEF: val = 61; break;
					case 0xDF: val = 62; break;
					case 0xBF: val = 63; break;
					case 0x80: val = 64; break;
				}
			}
		}
#ifndef CONFIG_OF
		if(ctr_zlg72xx->id->driver_data == ZLG72128_ID) 
		{       
#endif
#ifdef CONFIG_OF
		if((unsigned int *)(ctr_zlg72xx->id_tree->data) == &ZLG72128_ID)
		{
#endif
			switch(val)
			{
				case 0xF7: val = 28; break;         		//[3][3]
				case 0xFB: val = 27; break;			//[3][2]
				case 0xFD: val = 26; break;			//[3][1]
				case 0xFE: val = 25; break;			//[3][0]
				case 0x14: val = 20; break;			//[2][3]	
				case 0x13: val = 19; break;			//[2][2]
				case 0x12: val = 18; break;			//[2][1]
				case 0x11: val = 17; break;			//[2][0]
				case 0x0C: val = 12; break;			//[1][3]
				case 0x0B: val = 11; break;			//[1][2]
				case 0x0A: val = 10; break;			//[1][1]
				case 0x09: val =  9; break;			//[1][0]
				case 0x04: val =  4; break;			//[0][3]
				case 0x03: val =  3; break;			//[0][2]
				case 0x02: val =  2; break;			//[0][1]
				case 0x01: val =  1; break;			//[0][0]
			}
		}
#ifdef CONFIG_ZLG72XX_INPUT_DEVICE      
		input_report_key(ctr_zlg72xx->key, key_value[val], 1);        
		input_report_key(ctr_zlg72xx->key, key_value[val], 0);		   
		input_sync(ctr_zlg72xx->key);								   
#endif
		ctr_zlg72xx->current_key = val;                             
		wake_up_interruptible(&ctr_zlg72xx->readq);                 
	} 
out:
#if 1 
	schedule_delayed_work(&ctr_zlg72xx->work, HZ / 5);
#endif
}

static long zlg72XX_ioctl(struct file *file, unsigned int cmd, unsigned long arg) 
{
	struct zlg72XX* ioctl_zlg72xx = file->private_data;
	unsigned char buf[9] = {0};
	ssize_t len = 0;
	unsigned short ioctl_len = 0;
	unsigned int ioctl_flag1 = 0;
	unsigned int ioctl_flag2 = 0;
	unsigned char val[2] = {0};
	unsigned char reg[8] = {0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17};        
	int i = 0;

	switch (cmd) 
	{
	      case SET_VAL:
		if(copy_from_user(buf, (char *)arg, 9))
			ioctl_len = strlen(buf);
		for(i=0;i<ioctl_len;i++)
		{
			if(buf[i] == '.')
				ioctl_flag1 = 1;
		}
		if (ioctl_flag1 == 1)
			ioctl_len = 9;
		else 
			ioctl_len = 8;
		for(i = 0; i < ioctl_len; i++) 
		{
			if(buf[i] == '.')
			{
				val[0] = reg[i-1];
				ioctl_flag2 = 1;
			}
			if(ioctl_flag2 == 1)
				val[0] = reg[i-1];
			else
				val[0] =reg[i];
#ifndef CONFIG_OF
			if(ioctl_zlg72xx->id->driver_data == ZLG7290_ID) 
			{
#endif
#ifdef CONFIG_OF
			if((unsigned int *)(ioctl_zlg72xx->id_tree->data) == &ZLG7290_ID)
			{
#endif
				switch(buf[i]) 
				{
					case '0': val[1] = 0xFC; break;
//					case '1': val[1] = 0x0C; break;
					case '1': val[1] = 0x60; break;
					case '2': val[1] = 0xDA; break;
					case '3': val[1] = 0xF2; break;
					case '4': val[1] = 0x66; break;
					case '5': val[1] = 0xB6; break;
					case '6': val[1] = 0xBE; break;
					case '7': val[1] = 0xE0; break;
					case '8': val[1] = 0xFE; break;
					case '9': val[1] = 0xF6; break;
					case 'a':
					case 'A': val[1] = 0xEE; break;
					case 'b':
					case 'B': val[1] = 0x3E; break; 		
					case 'c':
					case 'C': val[1] = 0x9C; break;
					case 'd':
					case 'D': val[1] = 0x7A; break; 	
					case 'e':
					case 'E': val[1] = 0x9E; break;
					case 'f':
					case 'F': val[1] = 0x8E; break;
					case ' ': val[1] = 0x00; break;
					case '.':
						  if(val[1] != 0x00)
							 val[1] |= 0x01;
						  break;

					case '-': val[1] = 0x40; break;		//显示“-”，增加的内容

					case 'G': val[1] = 0xBF; break;		//显示“0.”，增加的内容
					case 'H': val[1] = 0x86; break;		//显示“1.”，增加的内容
					case 'I': val[1] = 0xDB; break;		//显示“2.”，增加的内容
					case 'J': val[1] = 0xCF; break;		//显示“3.”，增加的内容
					case 'K': val[1] = 0xE6; break;		//显示“4.”，增加的内容
					case 'L': val[1] = 0xED; break;		//显示“5.”，增加的内容
					case 'M': val[1] = 0xFD; break;	//显示“6.”，增加的内容
					case 'N': val[1] = 0x87; break;		//显示“7.”，增加的内容
					case 'O': val[1] = 0xFF; break;		//显示“8.”，增加的内容
					case 'P': val[1] = 0xEF; break;		//显示“9.”，增加的内容

					default:
						  val[1] = 0x00; break;
				}
			}
#ifndef CONFIG_OF
			if(ioctl_zlg72xx->id->driver_data == ZLG7290_ID) 
			{
#endif
#ifdef CONFIG_OF
			if((unsigned int *)(ioctl_zlg72xx->id_tree->data) == &ZLG72128_ID)
			{
#endif
				switch(buf[i]) 
				{
					case '0': val[1] = 0x3f; break;
//					case '1': val[1] = 0x30; break;
					case '1': val[1] = 0x06; break;
					case '2': val[1] = 0x5B; break;
					case '3': val[1] = 0x4F; break;
					case '4': val[1] = 0x66; break;
					case '5': val[1] = 0x6D; break;
					case '6': val[1] = 0x7D; break;
					case '7': val[1] = 0x07; break;
					case '8': val[1] = 0x7F; break;
					case '9': val[1] = 0x6F; break;
					case 'a':
					case 'A': val[1] = 0x77; break;
					case 'b':
					case 'B': val[1] = 0x7C; break; 	
					case 'c':
					case 'C': val[1] = 0x39; break;
					case 'd':
					case 'D': val[1] = 0x5E; break; 	
					case 'e':
					case 'E': val[1] = 0x79; break;
					case 'f':
					case 'F': val[1] = 0x71; break;
					case ' ': val[1] = 0x00; break;
					case '.':
						  if(val[1] != 0x00)
							 val[1] |= 0x80;
						  break;

					case '-': val[1] = 0x40; break;		//显示“-”，增加的内容

					case 'G': val[1] = 0xBF; break;		//显示“0.”，增加的内容
					case 'H': val[1] = 0x86; break;		//显示“1.”，增加的内容
					case 'I': val[1] = 0xDB; break;		//显示“2.”，增加的内容
					case 'J': val[1] = 0xCF; break;		//显示“3.”，增加的内容
					case 'K': val[1] = 0xE6; break;		//显示“4.”，增加的内容
					case 'L': val[1] = 0xED; break;		//显示“5.”，增加的内容
					case 'M': val[1] = 0xFD; break;	//显示“6.”，增加的内容
					case 'N': val[1] = 0x87; break;		//显示“7.”，增加的内容
					case 'O': val[1] = 0xFF; break;		//显示“8.”，增加的内容
					case 'P': val[1] = 0xEF; break;		//显示“9.”，增加的内容

					default:
						  val[1] = 0x00; break;
				}				
			}
			msleep(10);
			zlg72XX_hw_write(ioctl_zlg72xx, 2, &len, val);              
			}
		break;
	      case GET_KEY:
		wait_event_interruptible(ioctl_zlg72xx->readq, ioctl_zlg72xx->current_key != 0);
		if (copy_to_user((void *)arg, &ioctl_zlg72xx->current_key, 4))
			return -EFAULT;
		ioctl_zlg72xx->current_key = 0;
		break;
	}
	ioctl_flag1 = 0;
	ioctl_flag2 = 0;
	return 0;
}

static struct file_operations zlg72XX_fops = {
	.owner = THIS_MODULE,
	.open = zlg72XX_open,
	.release = zlg72XX_release,
	.unlocked_ioctl = zlg72XX_ioctl,
};

static int register_zlg72XX_device(struct zlg72XX *zlg) 
{
	int ret; 
	struct zlg72XX* register_dev_zlg72xx = zlg;
	dev_t devno = MKDEV(zlg72XX_major, zlg72XX_minor);        
	ret = register_chrdev_region(devno, 1, "led");                
	if (ret < 0) 
	{
		printk("Failed: register_chrdev_region : ret = %d\n",ret);
		return -1;
	}
	cdev_init(&register_dev_zlg72xx->cdev, &zlg72XX_fops);               
	register_dev_zlg72xx->cdev.owner = THIS_MODULE;                         
	ret = cdev_add(&register_dev_zlg72xx->cdev, devno, 1);                    
	if (ret < 0) 
	{
		unregister_chrdev_region(devno, 1);					
		printk("Failed: cdev_add\n");
		return -1;
	}
	register_dev_zlg72xx->class = class_create(THIS_MODULE, "zlg72xx-old");     
	if (register_dev_zlg72xx->class == NULL) 
	{
		printk("failed: class_create\n");	
		return -1;
	}
	device_create(register_dev_zlg72xx->class, NULL, devno, NULL, "zlg72xx");
	return 0;
}

static int unregister_zlg72XX_device(struct zlg72XX * zlg) 
{
	struct zlg72XX* unregister_dev_zlg72xx = zlg;
	dev_t devno = MKDEV(zlg72XX_major, zlg72XX_minor);          
	device_destroy(unregister_dev_zlg72xx->class, devno);                       
	class_destroy(unregister_dev_zlg72xx->class);                              
	cdev_del(&unregister_dev_zlg72xx->cdev);                                  
	unregister_chrdev_region(devno, 1);                           
	return 0;
}

#ifdef CONFIG_OF
static const struct of_device_id zlg72XX_of[] = {
	{
		.compatible = ZLG7290_NAME,
		.data = &ZLG7290_ID
	},{
		.compatible = ZLG72128_NAME,
		.data = &ZLG72128_ID
	},{
	},
};
MODULE_DEVICE_TABLE(of,zlg72XX_of);
#endif

static int zlg72XX_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
#ifdef CONFIG_ZLG72XX_INPUT_DEVICE
	struct input_dev *key_dev;                                   
	int i = 0;
#endif
	unsigned char probe_status = 3;
	size_t probe_len;
	struct zlg72XX* probe_zlg72xx;
	int ret = 0;
	if(!(probe_zlg72xx = kzalloc(sizeof(struct zlg72XX),GFP_KERNEL)))
		return -ENOMEM;
	memset(probe_zlg72xx,0,sizeof(struct zlg72XX));
	if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) 
	{
		return -ENODEV;
	} 
	probe_zlg72xx->client = client;  
	ret = zlg72XX_hw_read(probe_zlg72xx,0x1,&probe_len, &probe_status);
	if(ret < 0)
	{
		printk("driver_probe_72XX one of them doesn't %d\n",ret);
		goto err1;
	}
#ifdef CONFIG_OF
	probe_zlg72xx->id_tree = of_match_node(zlg72XX_of,probe_zlg72xx->client->dev.of_node);
	if(!probe_zlg72xx->id_tree)
		return -ENODEV;
#endif
#ifndef CONFIG_OF 
	probe_zlg72xx->id = id;                                             
#endif
	i2c_set_clientdata(client, probe_zlg72xx);                          
	init_waitqueue_head(&probe_zlg72xx->readq);
#ifdef CONFIG_ZLG72XX_INPUT_DEVICE								  
	probe_zlg72xx->key = input_allocate_device();                       
	if (probe_zlg72xx->key == NULL) 
	{
		kfree(probe_zlg72xx);
		return -ENOMEM;
	}
	key_dev = probe_zlg72xx->key;                                   
	key_dev->name = "zlg72XX";                          
	key_dev->id.bustype = BUS_HOST;
	key_dev->id.vendor = 0x0001;
	key_dev->id.product =  0x0001;
	key_dev->id.version = 0x0001;
	key_dev->evbit[0] = BIT_MASK(EV_KEY);                        
	for(i = 1; i <= 64; i++) 
	{                                  
		key_dev->keybit[BIT_WORD(key_value[i])] |= BIT_MASK(key_value[i]);
	}
	ret = input_register_device(key_dev);                          
	if (ret < 0) 
	{
		printk("Failed to register input device\n");
		goto err2;
	}
#endif
	INIT_DELAYED_WORK(&probe_zlg72xx->work, zlg72XX_work);             
#ifdef CONFIG_ZLG72XX_INPUT_DEVICE
	schedule_delayed_work(&probe_zlg72xx->work, HZ / 5);                
#endif
	ret = register_zlg72XX_device(probe_zlg72xx);
	if (ret < 0)
		goto err1;
	return 0;
err2:
#ifdef CONFIG_ZLG72XX_INPUT_DEVICE
	input_free_device(key_dev);                                 
#endif
err1:	
	kfree(probe_zlg72xx);                                               
	return ret;
}

static int zlg72XX_remove(struct i2c_client *client) 
{
	struct zlg72XX *remove_zlg72xx;
	remove_zlg72xx = (struct zlg72XX*)i2c_get_clientdata(client);
	cancel_delayed_work_sync(&remove_zlg72xx->work);                    
	unregister_zlg72XX_device(remove_zlg72xx);                                
	i2c_set_clientdata(client, NULL);                             
#ifdef CONFIG_ZLG72XX_INPUT_DEVICE
	input_unregister_device(remove_zlg72xx->key);                       
	input_free_device(remove_zlg72xx->key);
#endif
	kfree(remove_zlg72xx);                                            
	return 0;
}

static const struct i2c_device_id zlg72XX_id[] = {
	{ZLG7290_NAME, 0},
	{ZLG72128_NAME, 1},                     
	{}
};

MODULE_DEVICE_TABLE(i2c, zlg72XX_id);        

static struct i2c_driver  zlg72XX_driver= {
	.probe		= zlg72XX_probe,             
	.remove		= zlg72XX_remove,          
	.id_table	= zlg72XX_id,   
	.driver	= {
		.name	= ZLG72XX_NAME,              
		.owner	= THIS_MODULE,
		.of_match_table = of_match_ptr(zlg72XX_of),
	},
};

static int __init zlg72XX_init(void)
{
	return i2c_add_driver(&zlg72XX_driver);   
}

static void __exit zlg72XX_exit(void)
{
	i2c_del_driver(&zlg72XX_driver);          
}

module_init(zlg72XX_init);
module_exit(zlg72XX_exit);

MODULE_AUTHOR("farsight");                      
MODULE_DESCRIPTION("zlg72XX driver");         
MODULE_LICENSE("GPL");						   


