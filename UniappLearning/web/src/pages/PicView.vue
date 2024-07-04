<script setup lang="ts">
import axios from 'axios'
import {ref} from 'vue'

const url = ref('https://meme.3sqrt7.com/api/image')
const nextPic = () => {
    url.value = ''
    const random = Math.floor(Math.random() * 1000)
    url.value = 'https://meme.3sqrt7.com/api/image?index=' + random
}
</script>

<template style="overflow: hidden">
    <view>
        <div class="ImgContainer">
            <v-img
                style="box-shadow: black 0 0 10px 1px;border-radius: 5px"
                height="fit-content"
                lazy-src="../../static/img/Loading2.jpg"
                max-height="90%"
                max-width="90%"
                :src="url"
            >
                <template v-slot:placeholder>
                    <div class="d-flex align-center justify-center fill-height">
                        <v-progress-circular
                            color="grey-lighten-4"
                            indeterminate
                        ></v-progress-circular>
                    </div>
                </template>
            </v-img>

            <!--            <v-btn>下一张</v-btn>-->
        </div>
    </view>
    <div class="NextButton" @click="nextPic()">
        <v-fab icon="$vuetify" width="50" height="50">
            <v-icon icon="mdi-skip-next-outline"></v-icon>
            <v-progress-circular
                color="grey-lighten-4"
                indeterminate
                style="display: none"
            ></v-progress-circular>
        </v-fab>
    </div>
</template>


<style scoped lang="scss">
.NextButton {
    width: 50px;
    height: 50px;
    position: fixed;
    bottom: 10%;
    right: 5%;
    //left: 50%;
    //transform: translateX(-50%);
}

.ImgContainer {
    display: flex;
    align-items: center;
    justify-content: center;
    height: 85vh;
}
</style>
