package top.apricityx.main

fun main() {
    printDebug("Main function loaded")
    val name = "Kotlin"
    println("Hello, $name!")

    for (i in 1..5) {
        println("i = $i")
    }
    println(getVersion())

}

fun printDebug(content: String) {
//    println("Debug: $content")
// 输出黄色日志
    println("\u001B[33mDebug: $content\u001B[0m")
}

public fun getVersion(): String {
//     lambda函数
    val versionConstructor: (Int, Int) -> String = fun(big: Int, small: Int): String {
        return "$big.$small.0"
    }
    val version: () -> String = fun(): String {
        return versionConstructor(1, 4)
    }

    fun versionConstructor(big: Int, small: Int): String {
        return "$big.$small.0"
    }
    // 上两个versionConstructor的区别是，第一个是lambda函数，第二个是普通函数
    // 两者的区别是，lambda函数可以直接赋值给变量，而普通函数不行
    return versionConstructor(1, 4)

}
