<script setup lang="ts">
import {ref, watch} from 'vue';
import {debug} from "@/utils/debug.ts";

const props = defineProps<{
    httpResult: string
}>();
// 接受一个 httpResult 参数，用于接受父组件传递的数据

const parsedResult = ref<any>({});
const stdRequestInfo = ref<any>([])
// 监听 httpResult 的变化，执行相应的代码
watch(
    () => props.httpResult,
    (newVal) => {
        if (newVal) {
            let temp = JSON.parse(newVal)
            parsedResult.value = temp;
            stdRequestInfo.value = temp.stdRequests;
            console.log('解析后的请求结果:', parsedResult.value);
            console.log('请求结果:', newVal);
        }
    },
    {immediate: true}
);

</script>

<template>
    <el-scrollbar height="70vh">
        <el-card
            v-for="requestInfo in stdRequestInfo"
            style="margin-bottom: 40px"
            class="Std_card"
        >
            <template #header>
                <div class="card-header">
                    <span>{{ requestInfo.StdName }}</span>
                </div>
            </template>
            <div class="CardContainer">
                <el-descriptions title="学生信息"
                                 style="box-shadow: var(--el-box-shadow-light);padding:10px;margin-bottom:10px;border-radius: 10px">
                    <el-descriptions-item label="学号" width="25%">{{ requestInfo.StdID }}</el-descriptions-item>
                    <el-descriptions-item label="手机" width="20%">18883861911</el-descriptions-item>
                    <el-descriptions-item label="学生简介">{{ requestInfo.introduction }}
                    </el-descriptions-item>
                </el-descriptions>
                <div style="display: flex;flex-direction: row;justify-content: space-between">
                    <el-button @click="requestInfo.Status = 'Accepted'" type="success" style="width: 50%" plain
                               :disabled="requestInfo.Status==='Accepted'?true:requestInfo.Status === 'Rejected'">
                        {{
                            requestInfo.Status === "Pending" ? "接受申请" : requestInfo.Status === "Accepted" ? "已同意" : "已拒绝"
                        }}
                    </el-button>
                    <el-button
                        @click="requestInfo.Status === 'Accepted'?requestInfo.Status = 'Pending':requestInfo.Status = 'Rejected'"
                        type="danger" style="width: 50%" plain
                        :disabled="requestInfo.Status==='Rejected'"
                    >
                        {{
                            requestInfo.Status === "Pending" ? "拒绝申请" : requestInfo.Status === "Accepted" ? "退选学生" : "已拒绝"
                        }}
                    </el-button>
                </div>
            </div>
        </el-card>
    </el-scrollbar>
</template>

<style scoped>

:deep(.el-collapse-item__header) {
    padding-left: 10px;
    font-size: 15px; /* 设置标题文字的大小 */
    background: var(--el-color-info-light-7);
    transition: 0.5s;
}

:deep(.is-active) {
    background: var(--el-color-info-light-3);
    transition: 0.5s;
}

:deep(.el-collapse-item:first-child) {
    > .is-active {
        border-top: 0;
        border-radius: 10px 10px 0 0;
        background: #000000;
    }

    border-top: 0;
    border-radius: 10px 10px 0 0;
}

:deep(.el-collapse-item:first-child >button) {
    border-top: 0;
    border-radius: 10px 10px 0 0;
}

:deep(.single_info) {
    border: 1px solid #ebeef5;
    border-radius: 4px;
    padding: 10px;
    margin-top: 10px;
}

</style>
