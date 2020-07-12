[![](https://img.shields.io/github/stars/name-longming/EmWin-SmallPhone.svg?style=social&label=Star)](https://github.com/name-longming/EmWin-SmallPhone)
[![](https://img.shields.io/github/forks/qiubaiying/EmWin-SmallPhone.svg?style=social&label=Fork)](https://github.com/name-longming/EmWin-SmallPhone)

# 📦项目总结

> 此项目基于stm32F407+FreeRTOS+EmWin+ESP8266的物联网项目

---

该项目可以通过**HOME**图标让ESP8266读取实时的温度和天气，同时也可以通过**CLOCK**图标进行计数功能（CLOCK图标还处于未完全开发完成状态），通过**Settings**图标实现背景颜色的切换，板载LED亮灭的控制，以及关机（低功耗模式）

整个项目未用到任何外部SRAM，仅通过stm32最小系统板即可以实现。<!--将stm32的资源合理运用，让DIY更加简单-->

完整项目包含：模拟IIC接口驱动AT24C02记录触摸数据，RTC用于计时等

**注：EmWin的版本为5.40**



## 🔨项目器件

该项目所需要的设备有：stm32F407最小系统板，TFT2.8寸电阻屏，ESP8266。

该项目用到的内设：串口2用作ESP8266串口通信，FSMC控制TFT屏读写，TIM2作为系统时钟<!--具体可根据项目中cubemx来配置-->

<u>推荐可以购买**普中**stm32F407最小系统板</u>（没有打广告哈，纯路人😺）



## 📄注意点

1. 使用EmWin时一定要将CRC寄存器打开（否则无法正常显示）

2. ESP8266最好建议不要使用杜邦线等直接连接，因为ESP8266在通信过程中，如不小心触碰信号线等导致通信错误会导致整个程序直接卡死

3. stm32启动文件Heap_Size可以稍微设置大一点，因为cJSON解码会占用较多的Heap内存，如果不够的话程序照样会卡死

4. ```c
   cJSON_Hooks hooks;
   hooks.malloc_fn = pvPortMalloc;
   hooks.free_fn = vPortFree;
   cJSON_InitHooks(&hooks); 
   ```

   由于FreeRTOS与cJSON申请内存空间的函数冲突，需要在使用cJSON的时候同意内存申请函数，否则cJSON会一直解码失败

5. 通电后，开发板默认为待机模式，长按PA0对应的按键3秒后，单片机才开始正常运行，关机键在**Settings**图片中



## 📄部分代码解析

```c
//FreeRTOS
Array=cJSON_GetArrayItem(Array_obj1,0);
Array_obj2=cJSON_GetObjectItem(Array,"now");		
Array_obj3=cJSON_GetObjectItem(Array_obj2,"code");//解析出JSON中天气代码，如0->晴
osDelay(1000);//实测，一定要有个延时，否则解码失败
Array_obj4=cJSON_GetObjectItem(Array_obj2,"temperature");//解析出JSON中温度，注：温度以字符串形式解析出来
printf("n\r%s\n\r",Array_obj3->valuestring);
printf("n\r%s\n\r",Array_obj4->valuestring);
strcpy(Recive,Array_obj3->valuestring);
strcpy(Recive2,Array_obj4->valuestring);
cJSON_Delete(json);	//释放内存，重中之重，一定要释放，否则程序一会就会卡死
```

```c
//设置EMWIN内存大小
#define GUI_NUMBYTES  (100*1024) //设置为100kb，可以根据需要进行更改
#define GUI_BLOCKSIZE 0X50


//GUI_X_Config
//初始化的时候调用,用来设置emwin所使用的内存
void GUI_X_Config(void)
{
	static U32 aMemory[GUI_NUMBYTES / 4];
	GUI_ALLOC_AssignMemory((U32 *)aMemory, GUI_NUMBYTES); //为存储管理系统分配一个存储块
	GUI_ALLOC_SetAvBlockSize(GUI_BLOCKSIZE); //设置存储快的平均尺寸,该区越大,可用的存储快数量越少
}
```



***如果还有哪些代码有问题，可以直接私信我，我的博客地址：[nameytg.top](http://nameytg.top)***



## 📄项目目前已知bug（持续修复）

- [ ] ESP8266读取天气时，只有在打开**HOME**界面后才会开始读取（开机默认读取一次天气），且读取一次后ESP8266将不会再继续读取天气，直到再一次打开**HOME**界面。
- [ ] **CLOCK**界面进行计时时，可以通过**TIMOUT**键进行暂停，但是每次退出**CLOCK**界面时必须让时钟暂停，否则程序将会卡死。



## 📄更新日志

| 更新时间  |   更新内容   |
| :-------: | :----------: |
| 2020.7.12 | 正式上传项目 |



## 📄未来计划

1. 通过ESP8266同服务器相连接，实现模拟聊天功能
2. 通过服务器，将该项目作为一个智能家居的控制器，用于控制所有可通信的模块



## ✅项目图片


![main](https://img-blog.csdnimg.cn/20200712140057942.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L25hbWVfbG9uZ21pbmc=,size_16,color_FFFFFF,t_70)