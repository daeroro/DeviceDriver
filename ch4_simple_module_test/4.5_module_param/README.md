# module parameter

#### source file
- param.c

#### compile
- make

#### module execute
- sudo insmod param.ko onevalue=0x27 twostring="module parameter"

#### module delete
- sudo rmmod param

#### kernel messege
- dmesg

#### __문제점__
- insmod 할 때 dmesg를 찍어보면 module만 twostring에 들어간 것을 확인  
![dmesg](https://github.com/daeroro/DeviceDriver/blob/master/ch4/4.5_module_param/parameter_dmesg.png)
