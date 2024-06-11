<script setup lang="ts">
import {ref} from "vue";
import {debug} from "@/utils/debug";
import {watch} from 'vue';

const activeName = ref<string>('1')
const props = defineProps<{
    props: string
}>()
watch(() => props, (newVal) => {
        console.log('请求结果:', newVal);
        // 在这里执行相应的代码
});
</script>

<template>
    <el-collapse v-model="activeName" accordion>
        <el-collapse-item title="Consistency" name="1">
            {{ props }}
        </el-collapse-item>
    </el-collapse>
</template>

<style scoped>

</style>