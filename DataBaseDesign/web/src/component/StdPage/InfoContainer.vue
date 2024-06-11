<script setup lang="ts">
import {ref, watch} from 'vue';
import {defineProps} from 'vue';
import {debug} from "@/utils/debug.ts";

const props = defineProps<{
    httpResult: string
}>();
// 接受一个 httpResult 参数，用于接受父组件传递的数据

const activeName = ref<string>('1');
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
    <el-collapse v-model="activeName" accordion>
        <el-collapse-item
            v-for="tutor in parsedResult.tutors"
            :title="tutor.TutorName"
        >
            <el-row>
                <el-col :span="20">
                    <div class="grid-content ep-bg-purple"/>
                    {{ tutor.TutorInfo }}
                </el-col>
                <el-col :span="4">
                    <div class="grid-content ep-bg-purple"/>
                    <el-button>123</el-button>
                </el-col>
            </el-row>
        </el-collapse-item>
    </el-collapse>
</template>

<style scoped>

:deep(.el-collapse-item__header) {
    font-size: 15px; /* 设置标题文字的大小 */
}

</style>
