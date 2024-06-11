<script setup lang="ts">
import {ref, watch} from 'vue';
import {defineProps} from 'vue';

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
            // 在这里执行相应的代码
        }
    },
    {immediate: true}
);
</script>

<template>
    <el-collapse v-model="activeName" accordion>
        <el-collapse-item
            v-for="tutor in parsedResult"
            :key="tutor.TutorID"
            :title="tutor.TutorName"
            :name="tutor.TutorID.toString()"
        >
            <div>
                <p>Tutor Info: {{ tutor.TutorInfo }}</p>
                <p>Status: {{ tutor.Status }}</p>
            </div>
        </el-collapse-item>
    </el-collapse>
</template>

<style scoped>
</style>
