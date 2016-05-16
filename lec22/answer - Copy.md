Ϊ�˹۲���ļ���ȫ�����̣��������ȸ�дhello.c�û���������
```
int
main(void) {
    cprintf("Hello world!!.\n");
    cprintf("I am process %d.\n", getpid());
    cprintf("hello pass.\n");

    int	fd = open("/test", O_RDWR);
    char buffer[100];
    int res = read(fd, buffer, 100);
    cprintf("%s", res, buffer);
    return 0;
}
```
����һ��open��read����������"test"�����Ƿ���disk0�е�һ�������ļ�������Ϊ��testfile read succeed!��

Ϊ��������ļ���ȫ�������������̣�������ucore��Ӳ��������ide_read_secs���������print_stackframe������
��ȡһ�����������

ebp:0xc0349bf8 eip:0xc0100bf0 args:0xc0349c9c 0x00001000 0xc0349c48 0xc0109c72 
    kern/debug/kdebug.c:351: print_stackframe+21
ebp:0xc0349c58 eip:0xc0101ccd args:0x00000002 0x000002f8 0xc0340000 0x00000008 
    kern/driver/ide.c:159: ide_read_secs+19
ebp:0xc0349c98 eip:0xc0110c82 args:0x0000005f 0x00000001 0x80000000 0xc0347008 
    kern/fs/devs/dev_disk0.c:44: disk0_read_blks_nolock+58
ebp:0xc0349ce8 eip:0xc0110ea0 args:0xc03362b8 0xc0349d0c 0x00000000 0x0005f000 
    kern/fs/devs/dev_disk0.c:96: disk0_io+334
ebp:0xc0349d28 eip:0xc0114651 args:0xc0336340 0xc0344000 0x0000005f 0x00000000 
    kern/fs/sfs/sfs_io.c:24: sfs_rwblock_nolock+137
ebp:0xc0349d68 eip:0xc01147a4 args:0xc0336340 0xc034b000 0x0000001b 0x0000005f 
    kern/fs/sfs/sfs_io.c:90: sfs_rbuf+126
ebp:0xc0349dc8 eip:0xc0113595 args:0xc0336340 0xc0336730 0xc034b000 0x00000000 
    kern/fs/sfs/sfs_inode.c:631: sfs_io_nolock+753
ebp:0xc0349e18 eip:0xc01136c2 args:0xc0336730 0xc0349e5c 0x00000000 0x00000001 
    kern/fs/sfs/sfs_inode.c:657: sfs_io+210
ebp:0xc0349e38 eip:0xc011370e args:0xc0336730 0xc0349e5c 0x00000064 0x00000000 
    kern/fs/sfs/sfs_inode.c:669: sfs_read+31
ebp:0xc0349e88 eip:0xc010aa5b args:0x00000002 0xc034b000 0x00000064 0xc0349eac 
    kern/fs/file.c:230: file_read+238
ebp:0xc0349ec8 eip:0xc010b70d args:0x00000002 0xafffff24 0x00000064 0xc0349fdc 
    kern/fs/sysfile.c:80: sysfile_read+176
ebp:0xc0349ef8 eip:0xc010eca5 args:0xc0349f24 0x0000000a 0xc0349f48 0x00000000 
    kern/syscall/syscall.c:109: sys_read+58
ebp:0xc0349f48 eip:0xc010ee66 args:0x00000001 0xc0100328 0xc0349fbc 0xc0102c81 
    kern/syscall/syscall.c:201: syscall+117
ebp:0xc0349f78 eip:0xc0102a4c args:0xc0349fb4 0x00000000 0x00000000 0x00000023 
    kern/trap/trap.c:217: trap_dispatch+299
ebp:0xc0349fa8 eip:0xc0102c2c args:0xc0349fb4 0xafffff08 0x00800144 0xaffffed0 
    kern/trap/trap.c:307: trap+74
ebp:0xaffffed0 eip:0xc0102c81 args:0x00000066 0x00000002 0xafffff24 0x00000064 
    kern/trap/trapentry.S:24: <unknown>+0
ebp:0xaffffee8 eip:0x008006de args:0x00000002 0xafffff24 0x00000064 0x0000000c 
    user/libs/syscall.c:109: sys_read+38
ebp:0xafffff08 eip:0x00800144 args:0x00000002 0xafffff24 0x00000064 0x00050000 
    user/libs/file.c:21: read+30
ebp:0xafffff92 eip:0x00801835 args:0x00000001 0xaffffff6 0x00000001 0x00000000 
    user/hello.c:14: main+105
ebp:0xafffffc2 eip:0x00800ada args:0x00000001 0xaffffff6 0x00000000 0x00000000 
    user/libs/umain.c:31: umain+167
���ⲿ������У����ǿ�������ؿ������û�̬�������c���read�ӿڣ���ϵͳ���ýӿڣ�
�������ļ�ϵͳ�㣬�����ļ�ϵͳ�㣬��IO�ӿڲ㣬���Ӳ��������ĺ������ù�ϵ��
����������������ϸ������һ���ù��̡�
1. �û�����ͱ�׼�⣺
read() -> sys_read() -> syscall()     
syscall()�У�ͨ��int���жϽ����ں�     
2. ϵͳ���ýӿڲ㣺    
-> trap() -> trap_dispatch() -> syscall() -> sys_read()    
3. �����ļ�ϵͳ�㣺
-> sysfile_read() :�������ĺϷ���
-> file_read()	���ڽ��̵��ļ��б���Ѱ��ָ�����ļ�������дȨ�޵�
-> vop_read() :�����ļ�ϵͳread����ͳһ�ӿں���
4. ���ļ�ϵͳ�㣺
-> sfs_read()
-> sfs_io() :���ڴ��еĸ��ļ�inode�ṹ���л������
-> sfs_io_nolock() :���ݶ�д�ļ�����ʼλ�úͽ���λ�ã��ֳ�3�����ֽ��ж�д����        
��������| 4.1 �ļ���д����ʼλ�����ڵ�block
��������| -> sys_rbuf() :����Ҫ���λ�ã���д�Ƕ����block
��������| -> sfs_rwblock_nolock() ����дһ��������block
��������| 4.2 �ļ���д��λλ��֮�������block
��������| -> sys_rblock() -> sys_rwblock() ����д���������ɸ�block
��������| -> sfs_rwblock_nolock() ����дһ��������block
��������| 4.3 �ļ���д�Ľ���λ�����ڵ�block
��������| -> sys_rbuf() :����Ҫ���λ�ã���д�Ƕ����block
��������| -> sfs_rwblock_nolock() ����дһ��������block
-> dop_io()��:I/O�豸ͨ�ýӿں���
5. I/Oͨ�ýӿڲ㣺
-> disk0_io() :�������ĺϷ���
-> disk0_read_blks_nolock() ����������������������ȡ���ɸ�block
6. �豸�����㣺
-> ide_read_secs() :��ȡӲ�̵�����