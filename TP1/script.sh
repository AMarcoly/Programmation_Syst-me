dd if=/dev/zero of=test.bin bs=20 count=1
1+0 records in
1+0 records out
1024 bytes (1.0 kB, 1.0 KiB) copied, 0.000787818 s, 1.3 MB/s

hexdump -C test.bin
00000000  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000010

./write_int test.bin 5 1234567890

./read_int test.bin 5
1234567890
