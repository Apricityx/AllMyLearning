<template>
    <view>
        <li v-for="fruit in fruits">{{fruit.name}}
        </li>
    </view>
</template>
<script setup lang="ts">
    const fruits=[
        {
           name:"Apple",
           price:"27$"
        },
        {
            name:"Purple",
            price:"23$"
        },
        {
            name:"WaterWomen",
            price:"12$"
        }
    ]
    console.log("Learning 1!")
</script>


<style scoped lang="scss">

</style>
