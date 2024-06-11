<script setup lang="ts">
import axios from 'axios';
import {debug} from '@/utils/debug';
import InfoContainer from "@/component/StdPage/InfoContainer.vue";
import {onMounted, ref, provide} from "vue";

const temp_data = ref<string>('');
const get_info = () => {
    const url = "http://localhost:3000/api/v1/auth/get_info";
    const cookies: string = document.cookie
    debug("获取到的cookies:" + cookies);
// 从Cookie中获取accessToken
    const accessToken: string = cookies.split(';').find((item) => item.includes('accessToken')).split('accessToken=')[1];
    debug("获取到的accessToken:" + accessToken);
// 发送请求
    axios.post(url, {
        accessToken: accessToken
    })
        .then(response => {
            debug('ALL THE INFO: ' + JSON.stringify(response.data));
            temp_data.value = JSON.stringify(response.data);
        })
        .catch(error => {
            alert('请求失败，请重新登录再试');
            document.cookie = 'accessToken= expires=Thu, 01 Jan 1970 00:00:00 GMT';
            window.location.href = './login';
            debug('Error:' + error);
        });
}
onMounted(() => {
    get_info();
})
</script>

<template>
    <div style="border:2px solid black">
        <InfoContainer :props="temp_data"/>
    </div>
</template>

<style scoped>

</style>