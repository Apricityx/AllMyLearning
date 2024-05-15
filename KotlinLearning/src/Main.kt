fun main() {
    debug("Main function loaded")
    val name = "Kotlin"
    println("Hello, $name!")

    for (i in 1..5) {
        println("i = $i")
    }
}

fun debug(content: String) {
//    println("Debug: $content")
// 输出黄色日志
    println("\u001B[33mDebug: $content\u001B[0m")
}
