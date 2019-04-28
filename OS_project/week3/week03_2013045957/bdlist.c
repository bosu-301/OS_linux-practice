#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/module.h>
#include <linux/slab.h>

struct birthday {
	int day;
  	int month;
  	int year;
  	struct list_head list;
};

static LIST_HEAD(birthday_list);

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

int simple_init(void) {
 	printk("INSTALL MODULE: bdlist\n");
	struct birthday *bd1;
	bd1 = createBirthday(1,1,1994);
	list_add_tail(&bd1->list, &birthday_list);
	
	struct birthday *bd2;
	bd2 = createBirthday(2,2,1997);
	list_add_tail(&bd2->list, &birthday_list);
	


	struct birthday *cursor;
  	list_for_each_entry(cursor, &birthday_list, list){	
    		printk("NODE DATA: %d.%d.%d\n", cursor->day, cursor->month, cursor->year);
	}
 	return 0;
}

void simple_exit(void) {
	if(list_empty(&birthday_list)){
		printk("LIST IS EMPTY\n");
		return;
	}
   	printk("REMOVE MODULE: bdlist\n");				
  	struct birthday *cur_node;
	struct list_head *cursor, *next;
  	list_for_each_safe(cursor, next, &birthday_list) {		
		cur_node = list_entry(cursor, struct birthday, list);
		printk("DEL NODE DATA: %d.%d.%d\n", cur_node->day, cur_node->month, cur_node->year);
	
		list_del(cursor);						
		kfree(cur_node);						
  	}
  	return;
}

module_init(simple_init);
module_exit(simple_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("make a list of birthdays and print");
MODULE_AUTHOR("Lee jinsol_2013045957");
