ebp:0xc0349d68 eip:0xc0100bf0 args:0xc0336340 0xc034b000 0xc0349da8 0xc0109d2e 
    kern/debug/kdebug.c:351: print_stackframe+21
ebp:0xc0349dc8 eip:0xc01132a9 args:0xc0336340 0xc0336730 0xc034b000 0x0000001b 
    kern/fs/sfs/sfs_inode.c:555: sfs_io_nolock+10
ebp:0xc0349e18 eip:0xc01136c2 args:0xc0336730 0xc0349e5c 0x00000000 0x00000001 
    kern/fs/sfs/sfs_inode.c:657: sfs_io+210
ebp:0xc0349e38 eip:0xc011370e args:0xc0336730 0xc0349e5c 0x00000049 0x0000001b 
    kern/fs/sfs/sfs_inode.c:669: sfs_read+31
ebp:0xc0349e88 eip:0xc010aa56 args:0x00000002 0xc034b000 0x00000049 0xc0349eac 
    kern/fs/file.c:230: file_read+238
ebp:0xc0349ec8 eip:0xc010b708 args:0x00000002 0xafffff3f 0x00000049 0xc0349fdc 
    kern/fs/sysfile.c:80: sysfile_read+176
ebp:0xc0349ef8 eip:0xc010eca0 args:0xc0349f24 0x0000000a 0xc0349f80 0x00000000 
    kern/syscall/syscall.c:109: sys_read+58
ebp:0xc0349f48 eip:0xc010ee61 args:0x00000001 0xc0100328 0xc0349fbc 0xc0102c7c 
    kern/syscall/syscall.c:201: syscall+117
ebp:0xc0349f78 eip:0xc0102a47 args:0xc0349fb4 0x00000000 0x00000000 0x00000023 
    kern/trap/trap.c:217: trap_dispatch+299
ebp:0xc0349fa8 eip:0xc0102c27 args:0xc0349fb4 0xafffff08 0x00800144 0xaffffed0 
    kern/trap/trap.c:307: trap+74
ebp:0xaffffed0 eip:0xc0102c7c args:0x00000066 0x00000002 0xafffff24 0x00000064 
    kern/trap/trapentry.S:24: <unknown>+0
ebp:0xaffffee8 eip:0x008006de args:0x00000002 0xafffff24 0x00000064 0x0000000c 
    user/libs/syscall.c:109: sys_read+38
ebp:0xafffff08 eip:0x00800144 args:0x00000002 0xafffff24 0x00000064 0x00050000 
    user/libs/file.c:21: read+30
ebp:0xafffff92 eip:0x00801835 args:0x00000001 0xaffffff6 0x00000001 0x00000000 
    user/hello.c:14: main+105
ebp:0xafffffc2 eip:0x00800ada args:0x00000001 0xaffffff6 0x00000000 0x00000000 
    user/libs/umain.c:31: umain+167
