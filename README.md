# cYSP
YSP播放器C++版本。GCP前期开发工作也在此进行。本项目只包括开源部分的源码，非开源部分会上传对应的dll（如果必要的话）

0.8版本正处于早期构建阶段，暂时还不能正常使用。

# Ver0.8.0_Pre1_PT1(Build110.0)_SPOL0.6.

* 这是第一个C++版本的YSP的第一个测试版本的第一个预测版本，您将体验到数倍于Python版本YSP的运算性能与图形性能提升。具体提升幅度取决于您的CPU核心数量。
* 需要说明的是，本预测版本并不能正常使用——解释器只完成了背景控制器的识别。

新增了SPOL编辑器（SPOLDev）页面，取代第三方的SPOL编辑器。

增强了更新推送系统，程序现在会在告知可以更新时同时列出更新日志的链接（若未提供更新日志则也会标明无日志）。新的更新推送系统与老版本YSP兼容，您不必担心保留在您计算机上的老版本YSP因为升级更新推送机制而无法正常接受更新，或是在运行时崩溃。

更改了交互页面（今后称作程序主页）的外观设计。该设计是一个缓冲方案，日后会继续更改。

取消了程序执行时的SPOL语法报错，更改为在SPOLDev下启动播放前的集中报错。（暂未实装）

重新决定了在播放剧情时有哪些信息需要被推到控制台上显示。

新增了GCP模式。该模式目前只是个空壳子，后期会继续完善。

取消了YSP程序从双击SPOL文件打开时，直接进入播放页面并播放的功能。该功能将会在SPOLDev进一步开发之后于SPOLDev页面间接恢复。

经过长期观察，我们发现CrashReport内容大部分都是程序逻辑错误与SPOL引起的错误，没有其他意外错误，故取消了CrashReport报错系统。

改变了滤镜系统的算法，现在不会产生“缓存的缓存”，并且缓存文件命名与之前有差别，不能使用之前的缓存文件。上述改变均在为下一版SPOL做准备。

由于新版滤镜系统效率过高，因此现在在每次播放剧情之前都会对所有图像进行滤镜运算，并不像老版本的滤镜系统那样会跳过已经被运算过且已经缓存图像。这项更改可以杜绝老版本中更改原图后缓存图像无法自动更新的问题。

不再使用语言文件夹下的base.ini作为记录语言设置的文件。

新增记录程序统一设置的文件options.txt，部分敏感设置存储在注册表而非此文件之内。这意味着您的多个YSP程序将会共享相同的敏感设置。

新增程序设置：播放分辨率、播放窗口化、GCP模式切换（前两项现在只能通过改options实现））

允许在options.txt内通过调整Update_Channel更改更新接受通道，Auto为沿用当前通道，Pre为预览通道（内部渠道），Pub为公开通道（正式渠道）

允许在options.txt内通过调整Forced_Debugging_Info值为True在公开版本中启用内测版本的部分调试信息，这些调试信息大多为程序运行信息，于用户正常使用无益。

增强了按行跳转算法，现在会自动追加解释目标行之前的最后一个背景控制器和音乐控制器，以达到正常显示与扬声效果。

新增健康游戏忠告（仅在简体中文时显示）
