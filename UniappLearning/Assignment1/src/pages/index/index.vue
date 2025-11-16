<template>
    <v-skeleton-loader
        v-for="(item,index) in newsData as Array<{ title: string, url: string,category:string,author_name:string }>"
        :loading="Loading"
        class="mx-auto border"
        max-width="300"
        type="list-item-two-line,actions"
        style="margin: 20px"
        width="90%"
    >
        <v-responsive
            width="90%"
        >
            <v-card>
                <div style="margin: 10px">
                    <v-card-title class="text-h7">{{ item.title }}</v-card-title>
                    <div style="display: grid;grid-template-columns: auto auto">
                        <div>
                            <v-card-subtitle>
                                {{ item.author_name }}
                            </v-card-subtitle>
                            <v-card-subtitle>
                                {{ item.category }}
                            </v-card-subtitle>
                        </div>
                        <v-btn append-icon="mdi-arrow-right-bold-hexagon-outline" variant="outlined" size="small" @click="toD(item.url)">
                            <p class="text-h8">查看更多</p>
                        </v-btn>
                    </div>


                </div>
            </v-card>
        </v-responsive>
    </v-skeleton-loader>
</template>

<script setup lang="ts">
// setup中的代码会被自动注入到export default中，能在template中直接使用

import {ref} from 'vue'
import axios from "axios";
import {Config} from "@/utils/loadGlobalVar";


const Loading = ref(false)
const newsData = ref([])
axios.get(Config.address + '/api/v1/get_news').then(res => {
    newsData.value = res.data.result.data
    console.log(newsData.value)
})
const toD = (url: any) => {
    uni.navigateTo({
        url: url
    })
}
</script>
<script lang="ts">

</script>

<style>

</style>
