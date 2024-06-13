// import {fileURLToPath, URL} from 'node:url'
import AutoImport from 'unplugin-auto-import/vite'
import Components from 'unplugin-vue-components/vite'
import {ElementPlusResolver} from 'unplugin-vue-components/resolvers'
import {defineConfig} from 'vite'
import vue from '@vitejs/plugin-vue'
import {resolve} from 'path'
import Pages from 'vite-plugin-pages'

export default defineConfig({
    plugins: [
        vue(),
        AutoImport({
            resolvers: [ElementPlusResolver()],
        }),
        Components({
            resolvers: [ElementPlusResolver()],
        }),
    ],
    resolve: {
        alias: {
            '@': resolve(__dirname, 'src')
        }
    },
    build: {
        rollupOptions: {
            input: {
                login: resolve(__dirname, 'src/views/Login.html'),
                StdPage: resolve(__dirname, 'src/views/StdPage.html'),
                TutorPage: resolve(__dirname, 'src/views/TutorPage.html')
            }
        }
    },
    base: './',// 设置为相对路径
    server: {
        port: 3001,
    }
})
