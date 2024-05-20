//import io.ktor.application.*
//import io.ktor.features.ContentNegotiation
//import io.ktor.gson.gson
//import io.ktor.http.ContentType
//import io.ktor.http.HttpStatusCode
//import io.ktor.response.respond
//import io.ktor.routing.get
//import io.ktor.routing.routing
//import io.ktor.server.engine.embeddedServer
//import io.ktor.server.netty.Netty
//
//data class Message(val message: String)
//
//fun main() {
//    embeddedServer(Netty, port = 3000) {
//        install(ContentNegotiation) {
//            gson {
//                setPrettyPrinting()
//            }
//        }
//
//        routing {
//            get("/api/v1/") {
//                val message = Message("Hello")
//                call.respond(HttpStatusCode.OK, message)
//            }
//        }
//    }.start(wait = true)
//}
