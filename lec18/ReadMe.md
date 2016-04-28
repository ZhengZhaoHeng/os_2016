#程序说明

1. 对于这个问题，我们将读者的进入和离开两个动作分别抽象为一个线程，而这个Reading Room
就是这些线程共享的资源，Reading Room的属性包括空闲座位数、在座读者数和等待读者数

2. 我们使用Linux下的pthread来实现多线程机制

3. 对于信号量机制，我们使用pthread提供的sem_wait()和sem_post()接口，其功能分别相当于课件上
的P操作和V操作

4. 对于管程机制，我们使用pthread提供的pthread_cond_wait()和pthread_cond_signal()接口，分别相当于
课件上的wait()和signal()操作
