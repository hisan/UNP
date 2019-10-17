执行文件和中间目标文件
中间目标文件和源文件

make clean

include<filename>


	bin:a.o b.o c.o
	a.o:a.h
	b.o:b.h
	c.o:c.h
	.PHONY
	clean:
		rm bin *.o
		
