<template>
    <view>
        <text v-for="(num,index) in test_dict">{{ index }}：{{ num }}|</text>
    </view>
    <view class="content">
        <image class="logo" src="/static/logo.png"/>
        <view class="text-area">
            <text class="title">{{ title }}</text>
        </view>
        {{ count }}
        <v-btn @click="count+=1">
            +
        </v-btn>
        <v-btn @click="count-=1">
            -
        </v-btn>

        <v-input>123123</v-input>
    </view>
    <view>
        <v-text-field
            :rules="rules"
            hide-details="auto"
            label="Main input"
            v-model="numA"
        ></v-text-field>
        <v-text-field
            label="Another input"
            v-model="numB"
        ></v-text-field>
        <v-btn @click="console.log(parseInt(numA) + parseInt(numB))">PLUS</v-btn>
    </view>

</template>

<script setup lang="ts">
// setup中的代码会被自动注入到export default中，能在template中直接使用

import {ref} from 'vue'

const count = ref(0)
const title = ref('Hello')
const numA = ref(0 as any)
const numB = ref(0 as any)
</script>
<script lang="ts">
import axios from 'axios'
import {Config} from "@/utils/loadGlobalVar";

axios.get(Config.address + '/api/v1/get_news').then(res => {
    console.log(res.data)
})

console.log('Hello World')

// 表单验证规则
const rules = [
    (value: any) => !!value || 'Required.',
    (value: any) => (value && value.length >= 3) || 'Min 3 characters',
]
const test_dict = [111, 2222, 333, 4123, 524]
</script>

<style>
.content {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
}

.logo {
    height: 200rpx;
    width: 200rpx;
    margin-top: 200rpx;
    margin-left: auto;
    margin-right: auto;
    margin-bottom: 50rpx;
}

.text-area {
    display: flex;
    justify-content: center;
}

.title {
    font-size: 36rpx;
    color: #8f8f94;
}
</style>
