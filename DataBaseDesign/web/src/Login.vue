<script setup lang="ts">
import LoginForm from "@/component/Login/LoginForm.vue";
import {checkLogin} from "@/utils/checkLogin.ts";
import {debug} from "@/utils/debug";

checkLogin(true) // 检查登录状态
</script>

<template>
    <LoginForm/>
</template>

<style scoped>

</style>