<script setup lang="ts">
import {watch, defineProps, ref} from 'vue';

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
</script>

<template>
    <p style="text-align: center;font-weight: bold;font-size: 17px">{{ greeting }}</p>
</template>

<style scoped>

</style>