# Buddy System


---

##接口
使用线段树实现了Lec05中描述的Buddy System，在程序中，为用户提供了以下两个接口：

        int malloc(int size)
这个函数提供了申请大小为size内存空间的接口，在使用中，我们会分配2的幂次方大小的内存，并返回首地址。

        void free(int ptr)
这个函数提供了释放起始地址为ptr的内存段的接口。

---
##设计
具体实现采用线段树实现，模拟了一个1KB的内存空间分配，为了保证效率，最小的内存粒度为32Byte。在每个线段树结点中，都存在empty和full两个指针，分别标识该段是否全空，或者被整段地分配出去，便于释放内存时判断。

每当产生malloc请求时，就会在线段树中搜索满足要求的内存段，并返回首地址，同时更新沿路结点的empty指针。

每当产生free请求时，会在线段树中遍历，找到对应的内存段，修改full指针，并更新沿路结点的empty指针。

---
##测试用例
在源程序的main函数中，提供了一组测试用例：

   	printf("%d\n", malloc(512));
    printf("%d\n", malloc(128));
	printf("%d\n", malloc(256));
	printf("%d\n", malloc(128));
	free(640);
	free(512);
	printf("%d\n", malloc(200));

    



