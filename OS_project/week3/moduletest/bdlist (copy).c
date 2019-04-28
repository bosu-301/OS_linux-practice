#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>


struct birthday{
	int day;
	int month;
	int year;
	struct list_head list;
};

LIST_HEAD(birthday_list);

//kernel memory allocation & fill the data at struct birthday
struct birthday *createBirthday(int day, int month, int year){
	// Write code~~~~~
	struct birthday *br;

	br = kmalloc(sizeof(struct birthday), GFP_KERNEL);
	
	if(!br){
		printk("failed\n");
		return NULL;
	}
	
	br->day = day;
	br->month = month;
	br->year = year;

	printk("done\n");
	return br;
}

//insert each list_head th birthday_list
int __init simple_init(void){
	printk(KERN_INFO "Loading Module: BDLIST ....\n");
	
	// Write code ~~~~~
	struct birthday *bd1;
	bd1 = createBirthday(1,1,1994);
//	INIT_LIST_HEAD(&bd1->list)

	list_add_tail(&bd1->list, &birthday_list);
	
	struct birthday *bd2;
	bd2 = createBirthday(2,2,1997);
	list_add_tail(&bd2->list, &birthday_list);
	
	struct birthday *cursor;
	list_for_each_entry(cursor, &birthday_list, list){
		printk(cursor->day," ",cursor->month," ",cursor->year,"\n");
	
	}
	return 0;
	
}



void simple_exit(void){

	//Write code~~~~~
	printk("Removing Module:BDLIST....\n");

}


//referenced by  'https://soulabi.tistorky.com/9'

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simplej Module");
MODULE_AUTHOR("HAPPY_JS");









