<script setup lang="ts">
import axios from 'axios'
import {ref} from 'vue'
</script>

<template style="overflow: hidden">
    <view>
        <div class="ImgContainer">
            <v-card width="100%">
                <v-img
                    height="fit-content"
                    lazy-src="../../static/img/Loading.jpg"
                    max-width="500"
                    src="https://meme.3sqrt7.com/api/image"
                >
                </v-img>
                <!--            <v-btn>下一张</v-btn>-->
            </v-card>
        </div>
    </view>
    <div class="NextButton">
        <v-fab icon="$vuetify" width="50" height="50">
            <v-icon icon="mdi-access-point-off"></v-icon>
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
    right: 10%;
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
