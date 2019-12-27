# character device driver example

< 문자 디바이스 드라이버 동작 >
* 커널은 디바이스 파일에 기록된 디바이스 타입과 주 번호를 이용해
 -> 커널에 등록된 디바이스 드라이버 함수를 연결함
- 문자 디바이스 드라이버를 관리하는 구조체 : chrdevs[] (fs/char_dev.c)

![char_device_struct](https://github.com/daeroro/DeviceDriver/blob/master/ch6_character_device_driver/6.4_char_device_driver_example/char_device_struct.png)

- struct cdev * cdev (include/linux/cdev.h)

![cdev](https://github.com/daeroro/DeviceDriver/blob/master/ch6_character_device_driver/6.4_char_device_driver_example/cdev.png)

- file_operations 구조체 ops 필드 (include/linux/fs.h)
: 응용 프로그램이 디바이스 파일에 적용한 저수준 파일 입출력 함수에 대응하는 디바이스 드라이버 함수 주소를 지정하는 필드

![file_operations](https://github.com/daeroro/DeviceDriver/blob/master/ch6_character_device_driver/6.4_char_device_driver_example/file_operations.png)

1) 응용 프로그램에서 open() 함수로 디바이스 파일을 열어 타입 정보와 주 번호를 얻음
2) chrdevs 배열에 등록된 디바이스 드라이버 인덱스를 찾음
-> 이 구조체는 저수준 파일 입출력에 대응하는 함수를 설정한 내용을 담고 있음


< 문자 디바이스 드라이버의 등록과 해제 및 구성 >

- 문자 디바이스 드라이버를 등록한다는 것은 file_operations 구조체 변수를 등록한다는 의미
- linux/fs.h 를 포함시켜야
- **register_chrdev()** : 디바이스를 등록
- **unregister_chrdev()** : 등록된 디바이스를 제거	

```c
int register_chrdev(unsigned int major, const char *name, struct file_operations * fops)
```

- major(주 번호) : 응용 프로그램에서 디바이스 파일을 이용해 디바이스 드라이버를 찾을 때 사용
- name(디바이스 드라이버 이름) : proc 파일 시스템이나 오류 정보를 커널에 나타내기 위해 사용, 문자 디바이스 드라이버를 제거할 대 구별자로도 사용
- fops(file_operations 구조체 변수 주소)
- 반환값
: major 값을 0으로 주었으면 등록된 주 번호값이 반환
: major 값을 고정된 번호로 주면 0 반환
: 등록 실패시 0보다 작은 값 반환


```c
int unregister_chrdev(unsigned int major, const char * name)
```

- major(주 번호), name(디바이스 드라이버 이름)
- 반환값
	: 정상 제거 시 0 반환
	: 실패 시 0보다 작은 값 반환

