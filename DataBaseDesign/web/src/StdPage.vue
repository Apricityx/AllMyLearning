<script setup lang="ts">
import axios from 'axios';
import {debug} from '@/utils/debug';
import InfoContainer from "@/component/StdPage/InfoContainer.vue";
import {onMounted, ref} from "vue";
import StdAside from "@/component/StdPage/StdAside.vue";
import {checkLogin} from "@/utils/checkLogin.ts";
import {Refresh} from "@element-plus/icons-vue";

const temp_data = ref<string>('');
const get_info = () => {
    const url = "http://localhost:3000/api/v1/auth/get_info";
    const cookies: string = document.cookie;
    debug("获取到的cookies:" + cookies);

    // 从Cookie中获取accessToken
    const accessToken: string = cookies.split(';').find((item) => item.includes('accessToken'))?.split('accessToken=')[1];
    debug("获取到的accessToken:" + accessToken);

    // 发送请求
    axios.post(url, {
        accessToken: accessToken
    })
        .then(response => {
            // debug('ALL THE INFO: ' + JSON.stringify(response.data));
            temp_data.value = JSON.stringify(response.data);
        })
        .catch(error => {
            alert('请求失败，请重新登录再试');
            document.cookie = 'accessToken=; expires=Thu, 01 Jan 1970 00:00:00 GMT';
            window.location.href = './Login.html';
            debug('Error:' + error);
        });
}
// 检查是否登录
onMounted(() => {
    checkLogin(false)
    get_info();
});
</script>

<template>
    <el-container>
        <el-aside width="300px" style="border-right: 2px solid #a8a8a8;background-color:var(--el-color-primary-light-9)">
            <div>
                <StdAside :http-result="temp_data"/>
            </div>
        </el-aside>
        <el-container>
            <el-header>
                <el-button type="primary" @click="get_info" style="position: absolute;bottom: 10px;left: 10px;" plain><el-icon style="margin-right: 5px"><Refresh /></el-icon>刷新</el-button>
            </el-header>
            <el-main style="background: var(--el-color-info-light-8)">
                <div style="box-shadow: black 0 0 5px;padding: 10px">
                    <p style="text-align:center;font-weight: bold">可选导师</p>
                    <InfoContainer :httpResult="temp_data"/>
                </div>
            </el-main>
        </el-container>
    </el-container>
</template>
<style scoped>
/* 使 el-main 独立滚动 */
.el-main {
    height: calc(100vh - 60px); /* Adjust 64px based on your header/footer height */
    /*overflow-y: auto;*/
    overflow: hidden;
}

.el-header {
    border-bottom: 2px solid #a8a8a8;
    position: relative;
    transition: height 0.3s;
}
</style>
