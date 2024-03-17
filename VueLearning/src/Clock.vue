<script>
let raw_message = 'Hello Vue!!'
export default {
    data() {
        return {
            raw_message: raw_message,
            currentTime: '',
        };
    },
    mounted() { //这里的代码会在页面加载后执行
        this.updateTime();
        setInterval(() => {
            this.updateTime();
        }, 1000);
    },
    methods: {
        updateTime() {
            const now = new Date();
            this.currentTime = now.toLocaleTimeString()
        },
        formatTime(time) {
            return time;
        },
    }
};

//每1s将time改为当前时间
</script>

<template>
    <div class="greetings" onclick="this.style.display = 'none'">
        <h1>{{ raw_message }}</h1>
        <h2>当前时间为<span style="color:red">{{ currentTime }}</span></h2>
        <div style="display:none"></div> <!--动态属性值-->
    </div>
</template>

<style scoped>
.greetings {
    transition: 1s;
    position: fixed;
    backdrop-filter: blur(1px);
    width: fit-content;
    margin: 0 auto;
    border-radius: 15px;
    padding: 10px;
    background: linear-gradient(-45deg, rgba(255, 0, 0, 0.25), rgba(231, 60, 126, 0.06), rgba(35, 166, 213, 0.26), rgba(35, 213, 171, 0.3)) 0 0 / 250% 250%;
    text-align: center;
}

.greetings:hover {
    transition: 1s;
    background: linear-gradient(-45deg, rgba(255, 0, 0, 0.25), rgba(231, 60, 126, 0.06), rgba(35, 166, 213, 0.26), rgba(35, 213, 171, 0.3)) 0 0 / 100% 100%;
    background-position-y: 100%;
}
</style>