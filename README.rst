简介
====

AMetal是芯片级的裸机软件包，定义了跨平台的通用接口（使得基于AMetal的应用程序可以和具体硬件完全分离,实现跨平台复用），并提供了一系列驱动及常用的软件服务。
 
在MCU产业快速发展的今天，芯片厂商推出了越来越多的MCU。不同厂商、型号之间，MCU外设可能千差万别，例如，对于UART，不同芯片所对应的寄存器含义、波特率计算方法，中断处理方法等可能全然不同，这给广大嵌入式开发人员带来了诸多烦恼（例如，出于芯片资源、芯片供货情况等种种原因，产品需要更换使用的芯片，此时，底层大部分操作硬件的程序以及与之关联的应用程序可能都需要全部推翻重写）。实际上，对于同类外设，虽然底层差异性很大，但用途却是基本相同的，无论何种芯片上的UART外设，其提供的核心功能无非是发送串口数据或接收串口数据。为此，AMetal 对同一类外设进行了抽象，基于外设功能设计了相应的通用接口（也称之为标准接口），使得不同厂商、型号的MCU外设都能以通用接口操作。换言之，AMetal为用户提供了与具体芯片无关、仅与外设功能相关的通用接口，屏蔽了不同芯片底层的差异性。如果用户基于通用接口开发应用程序，将使得应用程序与具体芯片无关，非常容易跨平台（不同芯片对应的AMetal平台）复用。

对于同类外设，除标准功能外，不同芯片可能会提供一些非常特殊的功能，这些功能无法标准化，极少情况下，用户可能需要使用到这些功能，AMetal也提供了直接操作寄存器的接口，用户可直接使用这部分接口操作寄存器，实现特殊功能。特别地，直接操作寄存器的接口非常简单，往往以内联函数的形式提供，效率很高，某些特殊的应用可能对内存占用、运行效率等有极高的要求，则也可以选择使用直接操作寄存器的接口。
 
对于上层操作系统而言，例如，AWorks、Linux等，对各个外设都需要编写驱动。在编写特定操作系统下的驱动时，必须要熟悉特定的驱动框架及操作系统调用，这往往会花费开发人员相当大的精力。对于同一个外设而言，如果要支持多个操作系统，就需要编写多个驱动，其实，驱动底层对硬件的操作是有相通之处的。如果这部分驱动基于AMetal通用接口编写，那么，驱动将与具体芯片无关，只要AMetal支持了该芯片，为上层操作系统编写的驱动也就支持了该芯片。

芯片支持情况
-------------

下表为目前AMetal所支持的芯片（及对应的开发板）信息，相关评估板硬件资料获取：https://www.zlg.cn/ametal/article/index.html

    +----------------+------------------------+----------------+----------------------------+
    |      厂商      |          芯片          |     board      |             备注           |  
    +================+========================+================+============================+
    |                | ZLG116（Cotex-M0内核） |  am116_core    |                            | 
    |                +------------------------+----------------+----------------------------+
    |                | ZLG126（Cotex-M0内核） |  am126_core    |                            |
    |                +------------------------+----------------+----------------------------+
    |                | ZML166（Cotex-M0内核） |  am166_core    |                            |
    |                +------------------------+----------------+----------------------------+
    |                | ZML165（Cotex-M0内核） |  am165_core    |                            |
    |      ZLG       +------------------------+----------------+----------------------------+
    |                | ZLG217（Cotex-M3内核） |  am217_core    |                            | 
    |                +------------------------+----------------+----------------------------+
    |                | ZLG227（Cotex-M3内核） |  am227_core    |                            |
    |                +------------------------+----------------+----------------------------+
    |                | ZLG237（Cotex-M3内核） |  am237_core    |                            | 
    |                +------------------------+----------------+----------------------------+
    |                | ZMF159（Cotex-M3内核） |  am159_core    |                            |
    |                +------------------------+----------------+----------------------------+
    |                | ZSN700（Cotex-M0+内核）|  am700_core    |                            | 
    +----------------+------------------------+----------------+----------------------------+
    |                |HC32L19x（Cotex-M0+内核)|  aml19x_core   |                            | 
    |                +------------------------+----------------+----------------------------+
    |                |HC32L17x（Cotex-M0+内核)|  aml17x_core   |                            |
    |                +------------------------+----------------+----------------------------+
    |                |HC32L13x（Cotex-M0+内核)|  aml13x_core   |                            |
    |     HDSC       +------------------------+----------------+----------------------------+
    |                |HC32F19x（Cotex-M0+内核)|  amf19x_core   |                            | 
    |                +------------------------+----------------+----------------------------+
    |                |HC32F17x（Cotex-M0+内核)|  amf17x_core   |                            |
    |                +------------------------+----------------+----------------------------+
    |                |HC32F03x（Cotex-M0+内核)|  amf03x_core   |                            | 
    |                +------------------------+----------------+----------------------------+
    |                |HC32F07x（Cotex-M0+内核)| hc32f07x_core  |                            | 
    |                +------------------------+----------------+----------------------------+
    |                |HC32L07x（Cotex-M0+内核)|  hc32l07x_core |                            | 
    |                +------------------------+----------------+----------------------------+
    |                |HC32F46x（Cotex-M4内核) | hc32f46x_core  |                            | 
    +----------------+------------------------+----------------+----------------------------+
    |                |MM32L073（Cotex-M0内核) |  mm32l073_core |                            |
    |   MM32         +------------------------+----------------+----------------------------+
    |                |MM32L373（Cotex-M3内核) | mm32l373_core  |                            |  
    +----------------+------------------------+----------------+----------------------------+
    |    ST          |STM32F103（Cotex-M3内核)| stm32f103_core |                            |
    +----------------+------------------------+----------------+----------------------------+
    |   HK32         |HK32F103（Cotex-M3内核) | hk32f103_core  |                            |
    +----------------+------------------------+----------------+----------------------------+
    |                | LPC824（Cotex-M0+内核）|  am824_core    |                            |
    |                |                        +----------------+----------------------------+
    |                |                        |  am824ble      |  am824_core + 蓝牙         |
    |      NXP       |                        +----------------+----------------------------+
    |                |                        |  am824zb       |  am824_core + zigbee       |
    |                +------------------------+----------------+----------------------------+
    |                | LPC845（Cotex-M0+内核）|  am845_core    |                            |    
    +----------------+------------------------+----------------+----------------------------+
    |                | KL26（Cotex-M0+内核）  |  amks16z_core  |                            |   
    |                |                        +----------------+----------------------------+
    |   FREESCALE    |                        |  amks16rfid    |  amks16z_core + 2天线RFID  |
    |                |                        +----------------+----------------------------+
    |                |                        |  amks16rfid-8  |  amks16z_core + 8天线RFID  |
    +----------------+------------------------+----------------+----------------------------+



    **注意**：同一芯片可能对应几个不同的硬件评估板，它们的差异较小，复用了该芯片下绝大部分代码。它们通常仅仅是配置不同，比如不同board上LED对应的GPIO引脚不同，评估板仅供参考，在实际应用中，若用户仅使用了相应芯片，而board是自定义的，则可以将芯片对应的任意一个board作为模板，稍作改动即可使用。


驱动组件支持情况
-------------

下表为目前AMetal所支持的驱动组件信息：

    +----------------+------------------------+--------------------------------------------------------------+
    |      组件      |       芯片设备         |     简要说明                                                 | 
    +================+========================+==============================================================+
    |    LED组件     |            LED         | GPIO驱动、HC595驱动；                                        |
    +----------------+------------------------+--------------------------------------------------------------+
    |    ADC组件     |        CS1237          | 24位ADC驱动；                                                |
    +----------------+------------------------+--------------------------------------------------------------+
    |                | 有源蜂鸣器             |  GPIO驱动；                                                  |
    |  蜂鸣器组件    +------------------------+--------------------------------------------------------------+
    |                | 无源蜂鸣器             |  PWM驱动；                                                   |
    +----------------+------------------------+--------------------------------------------------------------+
    |                | 8段数码管              | GPIO驱动、HC595驱动等；                                      |
    | 数码管组件     +------------------------+--------------------------------------------------------------+
    |                |ZLG72128                |数码管&键盘管理芯片（I2C），可管理12位数码管和32个按键；      |
    +----------------+------------------------+--------------------------------------------------------------+
    |  HC595组件     |74HC595                 |GPIO驱动、SPI驱动；                                           |
    +----------------+------------------------+--------------------------------------------------------------+
    |EEprom驱动组件  |AT24C02                 |EEprom驱动（I2C）；                                           |
    +----------------+------------------------+--------------------------------------------------------------+
    |针式打印机组件  |M150-2机头              |驱动M150-2打印机，适用于出租车、小票打印等；                  |
    +----------------+------------------------+--------------------------------------------------------------+
    |手势检测组件    |GS200                   |UART驱动,支持多种手势动作检测；                               |
    +----------------+------------------------+--------------------------------------------------------------+
    |雨量检测组件    |RS200                   |UART驱动，可检测大雨小雨中雨等；                              |
    +----------------+------------------------+--------------------------------------------------------------+
    |磁旋钮组件      |MK100                   |UART驱动,支持多种动作检测；                                   |
    +----------------+------------------------+--------------------------------------------------------------+
    |系统监控组件    |CAT823                  |带看门狗和手动复位的系统监控器；                              |
    +----------------+------------------------+--------------------------------------------------------------+
    |                |ZLG9021                 |蓝牙透传（UART）；                                            |
    | BLE组件        +------------------------+--------------------------------------------------------------+
    |                |ZLG52810                |蓝牙5.0透传（UART）；                                         |
    +----------------+------------------------+--------------------------------------------------------------+
    | ZigBee组件     |ZM516X                  |ZigBee透传（UART）；                                          |
    +----------------+------------------------+--------------------------------------------------------------+
    |指纹识别组件    |TS10x                   |指纹模组，UART控制；                                          |
    +----------------+------------------------+--------------------------------------------------------------+
    |NVRAM组件       |EEPROM                  |EEPROM存储设备（I2C）；                                       |
    +----------------+------------------------+--------------------------------------------------------------+
    |接口转换组件    |SC16IS7xx               |I2C转UART；                                                   |
    +----------------+------------------------+--------------------------------------------------------------+
    |I2C组件         |                        |模拟I2C（GPIO驱动）；                                         |
    +----------------+------------------------+--------------------------------------------------------------+
    |SPI组件         |                        |模拟SPI（GPIO驱动）；                                         |
    +----------------+------------------------+--------------------------------------------------------------+
    |                |OLED（SSD1306）         |液晶驱动（SPI/I2C）；                                         |
    |                +------------------------+--------------------------------------------------------------+
    |  液晶驱动组件  |LCD（ILI9341）          |液晶驱动（SPI）；                                             |
    |                +------------------------+--------------------------------------------------------------+
    |                |LCD（ST7735）           |液晶驱动（SPI/I2C）；                                         |
    +----------------+------------------------+--------------------------------------------------------------+
    |                |独立按键                |GPIO驱动；                                                    |
    |                +------------------------+--------------------------------------------------------------+
    |  按键检测组件  |矩阵键盘                |GPIO行列式驱动；                                              |
    |                +------------------------+--------------------------------------------------------------+
    |                |ZLG72128                |数码管&键盘管理芯片（I2C），可管理12位数码管和32个按键；      |
    +----------------+------------------------+--------------------------------------------------------------+
    |                |ISI25xx系列             |IS25系列SPI FLASH芯片，如IS25LP064等（SPI）；                 |
    |                +------------------------+--------------------------------------------------------------+
    | FLASH驱动组件  |MX25xx系列              |旺宏公司的MX25系列SPI FLASH芯片，如MX25L1606E等（SPI）；      |
    |                +------------------------+--------------------------------------------------------------+
    |                |FM25CLxx系列            |铁电随机存取存储器（SPI）；                                   |
    +----------------+------------------------+--------------------------------------------------------------+
    |                |FM175XX                 |NFC无线读卡，支持常见的Mifare卡，以及一系列A类卡和B类卡；     |
    |                +------------------------+--------------------------------------------------------------+
    | 无线读卡组件   |ZLG600                  |无线读卡模块，UART控制；                                      |
    |                +------------------------+--------------------------------------------------------------+
    |                |ZSN603                  |I2C/UART方式通信，集成TypeB、SAM 、PLUS CPU卡等的操作命令；   |
    +----------------+------------------------+--------------------------------------------------------------+
    |                |DS1302                  |实时时钟（I2C驱动），带闹钟、时钟输出等功能；                 |
    |                +------------------------+--------------------------------------------------------------+
    |                |PCF85063                |实时时钟（I2C驱动），带闹钟、时钟输出等功能；                 |
    |   RTC组件      +------------------------+--------------------------------------------------------------+
    |                |RX8025SA                |实时时钟（I2C驱动），带闹钟、时钟输出等功能；                 |
    |                +------------------------+--------------------------------------------------------------+
    |                |RX8025T                 |实时时钟（I2C驱动），带闹钟、时钟输出等功能；                 |
    +----------------+------------------------+--------------------------------------------------------------+
    |                |LM75                    |温度传感器（I2C驱动）；                                       |
    |                +------------------------+--------------------------------------------------------------+
    |                |PT100                   |温度传感器；                                                  |
    |                +------------------------+--------------------------------------------------------------+
    |                |DS18B20                 |温度传感器（单总线）；                                        |
    |                +------------------------+--------------------------------------------------------------+
    |                |MPL3115A2               |气压温度传感器（I2C驱动）；                                   |
    |                +------------------------+--------------------------------------------------------------+
    |                |SHT20                   |温湿度传感器（I2C驱动）；                                     |
    |                +------------------------+--------------------------------------------------------------+
    |                |SHTC1                   |温湿度传感器（I2C驱动）；                                     |
    |                +------------------------+--------------------------------------------------------------+
    |                |HTS221                  |温湿度传感器（I2C驱动）；                                     |
    |                +------------------------+--------------------------------------------------------------+
    |                |BME280                  |压力温湿度传感器（I2C驱动）；                                 |
    |                +------------------------+--------------------------------------------------------------+
    |                |LPS22HB                 |压力与温度传感器（I2C驱动）；                                 |
    | 传感器         +------------------------+--------------------------------------------------------------+
    |                |BMP280                  |压力与温度传感器（I2C驱动）；                                 |
    |                +------------------------+--------------------------------------------------------------+
    |                |BMA253                  |三轴加速度传感器（I2C驱动）；                                 |
    |                +------------------------+--------------------------------------------------------------+
    |                |LSM6DSL                 |三轴加速度传感器（I2C驱动）；                                 |
    |                +------------------------+--------------------------------------------------------------+
    |                |ADXL375                 |三轴加速度传感器；                                            |
    |                +------------------------+--------------------------------------------------------------+
    |                |FXOS8700CQ              |六轴传感器（I2C驱动）；                                       |
    |                +------------------------+--------------------------------------------------------------+
    |                |LIS3MDL                 |三轴磁传感器（I2C驱动）；                                     |
    |                +------------------------+--------------------------------------------------------------+
    |                |MMC5883MA               |三轴磁传感器（I2C驱动）；                                     |
    |                +------------------------+--------------------------------------------------------------+
    |                |MAG311                  |三轴磁力与温度传感器（I2C驱动）；                             |
    |                +------------------------+--------------------------------------------------------------+
    |                |BMG160                  |三轴角速率传感器（I2C驱动）；                                 |
    |                +------------------------+--------------------------------------------------------------+
    |                |BH1730FVC               |光照强度传感器（I2C驱动）；                                   |	
    |                +------------------------+--------------------------------------------------------------+
    |                |TMD26353M               |Proximity（I2C驱动）；                                        |	
    |                +------------------------+--------------------------------------------------------------+
    |                |TSL25603M               |Ambient Light Sensor（I2C驱动）；                             |	
    |                +------------------------+--------------------------------------------------------------+
    |                |TMD27504M               |ALS+Prox（I2C驱动）；                                         |	
    |                +------------------------+--------------------------------------------------------------+
    |                |TCS34303                |Color传感器（I2C驱动）；                                      |	
    |                +------------------------+--------------------------------------------------------------+
    |                |TMD37024VCM             |Color+Prox（I2C驱动）；                                       |	
    |                +------------------------+--------------------------------------------------------------+
    |                |AS7262-BLGT             |可见光谱 sensor（I2C驱动）；                                  |	
    |                +------------------------+--------------------------------------------------------------+
    |                |AS7341-DLGM             |可见光谱 sensor（I2C驱动）；                                  |	
    |                +------------------------+--------------------------------------------------------------+
    |                |AS7421-ZLGT             |可见光谱 sensor（I2C驱动）；                                  |	
    |                +------------------------+--------------------------------------------------------------+
    |                |TMF8801-1BM             |TOF（I2C驱动）；                                              |	
    |                +------------------------+--------------------------------------------------------------+
    |                |AS6214-AWLT-S           |Temperature（I2C驱动）；                                      |	
    |                +------------------------+--------------------------------------------------------------+
    |                |TMG49037                |Gesture+Color+ALS+Prox（I2C驱动）；                           |	
    |                +------------------------+--------------------------------------------------------------+
    |                |AS5600                  |Magnetic Angle（I2C驱动）；                                   |	  
    +----------------+------------------------+--------------------------------------------------------------+	

特点
------

* 将外设操作标准化，避免上层软件、驱动的再次开发；
* 能独立运行的软件包，全部开源，提供工程模板与DEMO程序，可在此基础上开发应用程序；
* 不依赖操作系统服务；
* 尽可能将外设的所有特性开放出来；
* 尽可能浅地对外设进行封装，把效率放在第一位；
* 用户不用看芯片手册也能使用。
  
快速入门
----------

* 模板工程位于 ametal/board/{board_name}/project_template 目录下。例如：硬件板 am116_core 对应的 keil5 模板工程位于：ametal/board/am116_core/project_template/project_keil5/template_am116_core.uvprojx。可以直接打开后使用。

    **注意**：ZLG 相关芯片的 keil pack 包位于：ametal/tools/keil_pack。

* 示例工程位于 ametal/board/{board_name}/project_example 目录下。默认为LED闪烁的demo，通过修改调用的demo函数，可以运行其他demo，如 SPI、ADC、EEPROM 等等。

* TODO:
