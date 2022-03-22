# cYSP & Visindigo

cYSP播放器，以及cYSP播放器的下一代套（重）壳（构）版本Visindigo。

鉴于cYSP仅将YSP从Python翻译到C++，而YSP又是我刚刚学会一点点面向对象的小玩意的时候就开始写的东西，因此十分的具有“基础不牢地动山摇”的特点。原计划是试着在cYSP基础上直接加GPOL支持，但是目前看来并不好实现。所以现在给cYSP开了一个分支，叫做Visindigo。Visindigo在完成之后应该仅保留cYSP播放页本身以及AASPCMD解释器这两个部分的源码，其他的部分会悉数重写，重新组织程序结构。并且由于已经将原来计划的第一版的GPOL通过Python实现为PyGP，因此现在说的GPOL指的是用于将Visindigo内部函数暴露出来的GPOL字节码，相当于一种简单的接口标准。

至于后来说的要“重头弄一种脚本语言”而设想的第二版的GPOL，这玩意算是遥遥无期了，如果有的话我们会将其称之为VIL。关于VIL的相关技术通路的问题，坦白交代，我没打通。所以我现在在学习Python的解释器的相关原理。有一些用于解释的早期零散函数与内容可能并不会在本项目内更新（无论是cYSP还是Visindigo）。它们倒是可能出现在本人的另外一个项目里，也就是CommonEdit。CommonEdit的CEOperation部分有一个文件是CEScript，里面基本上就算是VIL解释器的前期工作了。

实际上，Visindigo的提出并不比CommonEdit项目要早，所以Visindigo很大程度上会吃一些CommonEdit的红利，因为CommonEdit里面收集了一些我自己写的其他轮子，可以直接拿过来给Visindigo用。

cYSP在接下来一段时间可能并不会更新，但是如果Visindigo开发的实在是太慢了，我会弄一些新功能放到cYSP里面作为缓冲。

此外，原来下方的版本更新内容不会再更了，现在用release管理更新信息
