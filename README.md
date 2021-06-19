# 多功能小键盘

### 固件开源地址： [https://github.com/panyihang/MiniKeyboard](https://github.com/panyihang/MiniKeyboard)

## 1 简介

#### 使用ch55x (ch551 / ch552 / ch554)单片机，使用ch55xarduino实现USB HID，不仅完全兼容普通的数字小键盘，还有更多扩展功能。

## 2 知识点

#### （1）学习键盘的设计思路和方法；

#### （2）了解CH552的外围；

#### （3）使用arduino写程序；

#### （4）学习使用立创EDA设计原理图及PCB图；

#### （5）学习PCB板的组成及工厂生产流程；

## 3 板载资源介绍

#### （1）一个16P的TYPE-C接口；

#### （2）17颗机械轴；

#### （3）两颗LED,用于指示当前的模式；

## 4.1 单片姬外围

#### ch55x的外围没什么好说的，采用5V输入，根据Datasheet分别在5V和3V3处加俩退耦电容即可

#### 下载电路也十分简洁，启动时把DP拉低即可进入下载模式

## 4.2 按键阵列

#### 为了确保各个按键没有冲突，采用的这种接线方法有点费IO，开源平台上有个大佬有个更精妙的方式实现了64键的全键无冲，这边其实用不着

## 4.3 LED

#### 由于仅剩下1个IO，所以运用了一个IO控制两颗LED

#### 众所周知，GPIO有三种状态，即高低电平和高阻，因此使用了一个NMOS来实现

* 当IO为低电平时，NMOS关断，LED4亮起 ；
* IO为高电平时，NMOS导通，LED3亮起 ；
* IO为高阻时，两颗LED都不亮；
* IO配置为PWM，当频率足够高时可以近似看为两颗LED同时亮起；
![深度截图_选择区域_20210529001217.png](https://image.lceda.cn/pullimage/gUFyceD73ZDXwc74twV9qBtIvAH2wXwUBM6L4beh.png)

## 5.PCB绘制

#### 这块板子扯线没什么难度，注意两层之间走线基本是垂直的即可

## 6.焊接

#### 先在焊盘上一点锡浆，把元件都放上去

![IMG_20210528_170913.jpg](https://image.lceda.cn/pullimage/ZtxzlJMMWyc3KbX30Z7fFLVWjS1iRdmkD1IYOTqV.jpeg)

#### 风枪开370度，风速2，吹十秒左右即可

![IMG_20210528_175521.jpg](https://image.lceda.cn/pullimage/UMAJgxEJhBoXYd6GylAKIKWmbEf9jcLTjblspzaU.jpeg)

#### 上电测试，插入TYPE-C线，可以正常识别（下载模式）

![深度截图_选择区域_20210528172627.png](https://image.lceda.cn/pullimage/L8f2ynnxthY1AtV0EaQXY6GxFQ7BRni8Vyf0j16y.png)

#### 焊上茶轴

![IMG_20210529_120824.jpg](https://image.lceda.cn/pullimage/zNaUDnT0baXXFtQhRGfB2nHIB2T6Fi83ML0iUaeo.jpeg)

## 7.代码

### 7.1 按键扫描的思路

#### 根据按键阵列，我们先在A1-A5中依次拉低这些IO，每拉低一个IO，就把A6-A9配置为输入上拉模式，依次扫描记录

![深度截图_选择区域_20210529002624.png](https://image.lceda.cn/pullimage/gzLCinBafKvQ9E9IExZqqHYdBMjPDO0euhT9EsaH.png)

### 7.2 软件滤波

#### 考虑到了可能出现的噪音，进行一次滤波和按键模拟

![深度截图_选择区域_20210529003253.png](https://image.lceda.cn/pullimage/mDFkLS6wtf0Xn1lbqIDA8hPQ8PnLniaqL1obmhHU.png)
![深度截图_选择区域_20210529003755.png](https://image.lceda.cn/pullimage/Sz0zf7eAY4FadctQkoqCTZi9bmvoYyi9pJu3cQeS.png)

### 7.3 模式切换（已删除）

#### 这边的模式切换采用的是对数组进行偏移来实现的

![深度截图_选择区域_20210529003831.png](https://image.lceda.cn/pullimage/2LUhk6QLqnQ8OUI8PwLRlX955MLHJE136Wo0FCCc.png)

## 8.固件现存的问题

* ch55xarduino疑似无法将引脚配置为高阻态，pinMode设为INPUT，实际为高电平，无法实现两个LED同时熄灭，不影响使用

### 由于模式切换导致了一些问题，现已删除模式切换功能，以下BUG均解决

* 在已经按下其他按键的情况下切换模式，会导致OS认为该按键一直被按下，按下任意键即可恢复
* 按键矩阵的(A1,A7)按下第一次扫描后会被识别为(A1,A6)，该问题较为严重，建议暂时屏蔽掉这个按键，原因还没查出来

# 9.外观

![IMG_20210530_164039.jpg](https://image.lceda.cn/pullimage/1Z4TaLq18ibr7d9AfoAaq3n8IRxRvgrEfoqre5WO.jpeg)

![IMG_20210530_163805.jpg](https://image.lceda.cn/pullimage/HDKuAUA0n76fAEmHoXIIvAFA9mrKF3CeOTD7Hx1F.jpeg)

### 底座使用另一块板子用热熔胶粘在一起

### <del>考虑到隔壁jp出了白嫖3d打印的活动，后续可能会画外壳</del>

2021/6/15 隔壁玩不起了，没法白嫖3d打印了，外壳就不画了

# 10.踩过的坑

### 0.0.9的ch55xrduino linux版本有一处路径异常（或者是打包有遗漏），编译报错找不到avr-objcopy，Arch系解决方法如下

`sudo pacman -S avr-gcc`

`vim /home/[YOUR-USER-NAME]/.arduino15/packages/CH55xDuino/hardware/mcs51/0.0.9/platform.txt`

第41行

`compiler.tools.path=xxxxxxxxxxxxx`

改为

`compiler.tools.path=/usr/bin`

保存退出即可

### window版没法用自带的下载工具烧录程序，好像是权限的问题？反正没有解决，可以导出hex然后用官方给的烧录软件烧录

- - -

<br>
<br>
<br>
最后吐槽两句，黑轴的手感是真的不行，到底是哪个b说黑轴适合打游戏

原神官服54级老咸鱼了，UID:163114852，欢迎来骚扰~

- - -
