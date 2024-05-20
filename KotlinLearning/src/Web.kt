package com.example

import io.ktor.application.*
import io.ktor.features.*
import io.ktor.http.*
import io.ktor.response.*
import io.ktor.routing.*
import io.ktor.server.engine.*
import io.ktor.server.netty.*

fun main() {
    embeddedServer(Netty, port = 3000) {
        install(DefaultHeaders)
        install(CallLogging)

        routing {
            get("/api/v1/") {
                call.respondText("""{"message": "Hello"}""", ContentType.Application.Json)
            }
        }
    }.start(wait = true)
}
