// 欢迎使用SPS语言！SPS是JS+SPOL的混合语言，您可以在JS脚本中嵌入SPOL文本
// 在享受SPOL便捷的同时可以进行更加复杂的操作

// 此 import 语句格式固定，用于激活嵌入的 SPOL 代码
// 格式为：import {主文件名_SPOL} from "__story__/主文件名_SPOL.js"
// 如果你变更了主文件名，那么请修改此处的 import 语句
import {main_SPOL} from "__story__/main_SPOL.js"

// 此处的 main 函数是 SPS 的入口函数，SPS 会在启动时自动调用此函数
// 如果你还不会JS，那么请不要修改此处的代码，直接在下方的 SPOL 代码块中编写你的 SPOL 代码即可
export function main(){
    SPOL.print("Hello, world!") // SPOL.print() 函数用于在控制台输出信息，
    SPOL.loadStory(main_SPOL.PartA) // SPOL.loadStory() 函数用于加载 SPOL 文本，也就是下方的嵌入 SPOL 代码
}

// 以下是嵌入的 SPOL 代码，他们必须被包裹在 /*SPOL 和 SPOL*/ 之间
// 在SPOL代码块中，您可以像以前一样使用 SPOL 语言

/*SPOL
/SPOL0.10.0
# 请注意下面这个-->，他现在是SPOL的文段标记，而不是以前的大分支控制器
# 这个标记在上文的SPOL.loadStory()函数中被用到了
-->PartA
>>>:秋风起，望长空青邃。天雨落，不知故人几时归。
SPOL*/ 