obj-m += hello.o

all:
	make -C /lib/modules/5.0.1/build M=$(PWD) modules

clean:
	make -C /lib/modules/5.0.1/build M=$(PWD) clean
