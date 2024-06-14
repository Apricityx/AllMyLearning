<script setup lang="ts">
import {ref, watch} from 'vue';
import {debug} from "@/utils/debug.ts";

const props = defineProps<{
    httpResult: string
}>();
// 接受一个 httpResult 参数，用于接受父组件传递的数据

const parsedResult = ref<any>({});
// 监听 httpResult 的变化，执行相应的代码
watch(
    () => props.httpResult,
    (newVal) => {
        if (newVal) {
            parsedResult.value = JSON.parse(newVal);
            console.log('解析后的请求结果:', parsedResult.value);
            console.log('请求结果:', newVal);
        }
    },
    {immediate: true}
);


</script>

<template>
    <el-scrollbar height="70vh">
    <el-collapse accordion>
        <el-collapse-item
            v-for="tutor in parsedResult.tutors"
            :title="tutor.TutorName"
            class="single_info_container"
        >
            <el-row class="single_info">
                <el-col :span="20" style="height: 200px">
                    <el-card style="width: 95%;height: 100%" shadow="hover">
                        <el-text class="mx-1">导师个人信息：{{ tutor.TutorInfo }}</el-text>
                    </el-card>
                </el-col>
                <el-col :span="4" style="display: flex;flex-direction: column;justify-content: space-between">
                    <el-row>
                        <el-button style="width: 100%"
                                   plain
                                   @click="tutor.Status='pending'"
                                   :disabled="tutor.Status==='pending'"
                                   :type="tutor.Status === 'pending' ? 'primary' : 'success'"
                        >{{ tutor.Status === 'pending' ? '等待通过' : '发出申请' }}
                        </el-button>
                    </el-row>
                    <el-row>
                        <el-button style="width: 100%" type="primary" plain>详细信息</el-button>
                    </el-row>
                    <el-row>
                        <el-button style="width: 100%" type="primary" plain>联系导师</el-button>
                    </el-row>
                    <el-row>
                        <el-button style="width: 100%" type="danger" :disabled="tutor.Status!=='pending'" @click="tutor.Status='Pending'">取消申请</el-button>
                    </el-row>
                </el-col>
            </el-row>
        </el-collapse-item>
    </el-collapse>
    </el-scrollbar>
</template>

<style scoped>

:deep(.el-collapse-item__header) {
    padding-left: 10px;
    font-size: 15px; /* 设置标题文字的大小 */
    /*color: red;*/
    background: var(--el-color-info-light-9);
    transition: 0.5s;
}

:deep(.el-collapse-item__header:hover){
    color: var(--el-color-primary-dark-2);
}
:deep(.is-active:hover) {
    color: #aafff2;
}
:deep(.is-active) {
    background: var(--el-color-info-light-3);
    color:white;
    transition: 0.5s;
}

:deep(.el-collapse-item:first-child) {
    > .is-active {
        border-top: 0;
        border-radius: 10px 10px 0 0;
        /*background: #000000;*/
    }

    border-top: 0;
    border-radius: 10px 10px 0 0;
}

:deep(.el-collapse-item:first-child >button) {
    border-top: 0;
    border-radius: 10px 10px 0 0;
}

:deep(.single_info) {
    border: 1px solid var(--el-color-primary-light-9);
    border-radius: 4px;
    padding: 10px;
    margin-top: 10px;
}
</style>
