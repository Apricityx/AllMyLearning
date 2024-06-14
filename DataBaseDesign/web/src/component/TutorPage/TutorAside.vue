<script setup lang="ts">
import {watch, ref} from 'vue';
import {SwitchButton} from '@element-plus/icons-vue'
import {ElMessageBox} from "element-plus";

const props = defineProps<{
    httpResult: string
}>();
const info = ref<any>({});
const greeting = ref<string>('');
const introduction = ref<string>('');
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
            introduction.value = info.value.selfInfo.TutorInfo;
            greeting.value = time_info + '，' + info.value.selfInfo.TutorName;
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
    <p style="color:#000000;text-align: center;font-weight: bold;font-size: 17px">{{ greeting }}</p>
    <el-card style="width: 99%;height: 100%;user-select: none" shadow="hover">
        <el-divider/>
        <el-text class="mx-1">个人简介：
            <p>{{ introduction }}</p>
        </el-text>
        <el-divider/>
        <div style="display: flex;justify-content: center;align-items: center">
            <el-button>
                修改简介
            </el-button>
        </div>
    </el-card>

    <el-button @click="dialogVisible = true" type="danger"
               style="position: absolute; bottom: 10px; left: 60px; width: 180px; margin: auto;">
        <div style="display: flex;flex-direction: row;justify-content: space-between;align-items: flex-start">
            <el-icon>
                <SwitchButton/>
            </el-icon>
            <span>
            退出登录
            </span>
        </div>
    </el-button>
</template>

<style scoped>

</style>