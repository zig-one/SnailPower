# Arduino pro micro开发板的程序烧录问题

[清晨微风](https://blog.csdn.net/qq_29562209) 



        [Arduino](https://so.csdn.net/so/search?q=Arduino&spm=1001.2101.3001.7020) pro micro是我大二的时候买的一个开发板，当时是玩Arduino开发板之后，尝试做一个小东西，但是买回来后，不知道程序怎么下载，多种尝试也没有成功，时隔多年，在家收拾东西翻出来后，再试了一下，发现我当时想多了，没好好地去看相关的资料。

         Arduino pro micro如下图所示，淘宝现在大概20元多点一块，比我16年的时候买要贵了5块左右，怕是物价上涨了。

![](https://img-blog.csdnimg.cn/20200201201109435.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI5NTYyMjA5,size_16,color_FFFFFF,t_70)

![](https://img-blog.csdnimg.cn/20200201201428722.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI5NTYyMjA5,size_16,color_FFFFFF,t_70)

![](https://img-blog.csdnimg.cn/20200201201748763.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L3FxXzI5NTYyMjA5,size_16,color_FFFFFF,t_70)

当年我拿到这个板子，非常小一个，但是上面没看到有USB转TTL的电路（即CH340等芯片），就以为是需要外接烧录，后面发现，这个是USB-ISP直接下载， 用USB-micro数据线（安卓数据线）连上，可能需要安装一下驱动.
