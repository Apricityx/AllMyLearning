<script setup lang="ts">
import {watch, ref} from 'vue';
import {SwitchButton} from '@element-plus/icons-vue'
import {ElMessageBox} from "element-plus";

const props = defineProps<{
    httpResult: string
}>();
const info = ref<any>({});
const greeting = ref<string>('');
let time_info = ''
const time_now = new Date();
const hour = time_now.getHours();
if (hour >= 0 && hour < 6) {
    time_info = '凌晨好';
} else if (hour >= 6 && hour < 12) {
    time_info = '早上好';
} else if (hour >= 12 && hour < 18) {
    time_info = '下午好';
} else {
    time_info = '晚上好';
}
watch(
    () => props.httpResult,
    (newVal) => {
        if (newVal) {
            info.value = JSON.parse(props.httpResult);
            greeting.value = time_info + '，' + info.value.selfInfo.name;
        }
    },
    {immediate: true}
);

// 登出函数
const dialogVisible = ref(false)
// ElMessageBox.confirm('Are you sure to close this dialog?')
const logoutStatus = ref(false)
const logout = () => {
    logoutStatus.value = true
    setTimeout(() => {
        document.cookie = 'accessToken=; expires=Thu, 01 Jan 1970 00:00:00 GMT';
        window.location.href = './Login.html';
    }, 1000)
}
</script>

<template>
    <el-dialog
        v-model="dialogVisible"
        title="提示"
        width="500"
        :before-close="()=>{dialogVisible = false}"
    >
        <span>确认要登出吗？</span>
        <template #footer>
            <div class="dialog-footer">
                <el-button @click="dialogVisible = false">取消</el-button>
                <el-button type="primary" @click="logout()" :loading=logoutStatus>登出</el-button>
            </div>
        </template>
    </el-dialog>
    <p style="color:white;text-align: center;font-weight: bold;font-size: 17px">{{ greeting }}</p>
    <el-button @click="dialogVisible = true" type="danger"
               style="position: absolute; bottom: 10px; left: 10px; width: 180px; margin: auto">
        <el-icon>
            <SwitchButton/>
        </el-icon>
        <p>
            退出登录
        </p>
    </el-button>
</template>

<style scoped>

</style>