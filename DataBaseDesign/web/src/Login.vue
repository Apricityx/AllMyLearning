<script setup lang="ts">
import LoginForm from "@/component/Login/LoginForm.vue";
import {checkLogin} from "@/utils/checkLogin.ts";
import {debug} from "@/utils/debug";
import {ref} from 'vue'

checkLogin(true) // 检查登录状态
const loginFormContainer = ref<HTMLElement | null>(null);
const handleBackgroundChange = () => {
    if (loginFormContainer.value) {
        loginFormContainer.value.style.backgroundColor = 'rgb(139, 255, 153,0.2)';
        loginFormContainer.value.style.borderColor = 'rgb(139, 255, 153,0.6)';
        // loginFormContainer.value.style.marginTop = '1000px';
    }
};

</script>

<template>
    <div class="fullScreen">
        <div id="LoginFormContainer" ref="loginFormContainer">
            <p style="text-align: center;font-size: 30px;font-weight: bold">LOGIN</p>
            <LoginForm @trigger-event="handleBackgroundChange"/>
        </div>
    </div>
</template>
<style scoped>

#LoginFormContainer {
    transition: 0.5s;
    background: rgba(255, 255, 255, 0.38);
    /*background: ;*/
    width: fit-content;
    height: fit-content;
    padding: 20px;
    backdrop-filter: blur(10px);
    border-radius: 15px;
    border: 1px solid rgba(255, 255, 255, 0.6);
}

.fullScreen {
    width: 100%;
    height: 100%;
    display: flex;
    justify-content: center;
    align-items: center;
}
</style>