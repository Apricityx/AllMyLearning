<script setup lang="ts">
import {h, reactive, ref} from "vue";
import LoginForm from "@/component/Login/LoginForm.vue";
import {ComponentSize, ElMessage, FormInstance,} from 'element-plus'
import {debug} from "@/utils/debug";
import JSEncrypt from "jsencrypt";
import {resolve} from "path";
import 'element-plus/dist/index.css'
import {checkLogin} from "@/utils/checkLogin.ts";
// 创建一个响应式变量

// 定义组件大小
const formSize = ref<ComponentSize>('default')
const FormRef = ref<FormInstance>()
// FormRef 是一个引用，用于引用表单实例
const isSubmitting = ref(false)

// 定义消息提示框
const openVn = () => {
    ElMessage({
        message: h('p', {style: 'line-height: 1; font-size: 14px'}, [
            h('span', null, 'Message can be '),
            h('i', {style: 'color: teal'}, 'VNode'),
        ]),
    })
}

// 定义Form
const form = reactive({
    id: '',
    password: '',
    remember: false,
    user_type: '', // 确保属性名为 user_type
})

// 获取记住密码的信息
const userInfo = document.cookie.split('; ').find(row => row.startsWith('userRemember'))
debug("获取到的userInfo：" + userInfo)
if (userInfo) {
    const userInfoBase64 = userInfo.split('=')[1]
    const userInfoJson = atob(userInfoBase64)
    const userInfoDict = JSON.parse(userInfoJson)
    debug("获取到的userInfoDict：" + userInfoDict)
    form.id = userInfoDict['id']
    form.password = userInfoDict['password']
    form.user_type = userInfoDict['user_type']
    form.remember = true
}


interface FormRules {
    id: any
    password: any
    user_type: any
    remember: any
}

// 创建接口，用于定义表单数据的类型

const ruleFrom = reactive<FormRules>({
    id: '',
    password: '',
    remember: false,
    user_type: '', // 确保属性名为 user_type
})

// <FormRules> 是刚才定义的接口，用于定义表单的验证规则

// 定义表单验证规则
const rules = reactive(<FormRules>{
    id: [
        {required: true, message: '请输入姓名', trigger: 'blur'},
    ],
    password: [
        {required: true, message: '请输入密码', trigger: 'blur'},
        {min: 6, message: '密码长度不能少于6位', trigger: 'blur'},
    ],
    user_type: [
        {required: true, message: '请选择用户类型', trigger: 'submit'},
    ],
    remember: [
        {required: true, message: '请选择是否记住密码', trigger: 'submit'},
    ],
})


const onSubmit = async (Form: FormInstance) => {
    debug("Submit Triggered")
    await Form.validate((valid, fields) => {
        if (valid) {
            debug('submit!')
            const id = form.id
            const password = form.password
            const dict = {
                'id': id,
                'password': password,
                'user_type': form.user_type,
            }

            if (form.remember) {
                const dictBase64 = btoa(JSON.stringify(dict))
                document.cookie = 'userRemember=' + dictBase64
                debug('记住密码触发')
            } else {
                document.cookie = 'userRemember=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
            }

            const publicKey = "MIICCgKCAgEA4vVjhCKuq6JOUmje/hz7B9IQYTLNsXwY365RIJNdLwHdhY/q3qBSTWOpUeh2I8BdYuFVnAqWqZGfDfXSKjRCrxKMKMRXl87DsTStDcJz5hRgGPK++C61cnbQSRfeVvp4WfJn/iFusaxi6NwJJA56xThrnA5gYcbaZ49VLjE9HNmwf2Jz+SApyed4g1ec5vK2x4W/PBOD3/JABYZ3uWKPfYvlBIURe9fUj378eIOO+r6Cb/KrZPW+CcBTfVmLdPCwLYqmlT1L1hM13mm+5gbA3RE2wTn7Rd3AEPuJEeYdG/nytNSMsOCkNuVtgZuEg7dCbhUqRdQJw6OpO24Q//x2lENl6+qaWe43ZDKo1M8vVfquQI2mZRmZ6TDfaEFGT6c0dAqSXWteH2tpB/YHX5Z3rrdtDk4fLIg9V5zQbeNceSdBq59lNU2Uq3Qp+E8JR/ZttpdLgSfe9KGDuh+Xftwg1jea0Emsrqsw/DKx4xnf2RkAFY6F+0del+JFnEH15CbiN/pWxkQ0kMZHq3S27NKTvFEGGEjxMz5UZFlMhAZvTpei8bQ9f2JnHHR7YkjZSO+Szhi4QlsMomy64Udw6R4mHuMSA6jS8Y7S4dYWgEfahvIOm87PQ5BetJW55FrdfrllKIwH6gxfZ+zp5qVw8NTbDPYzDqixCJymXRBQ7FV9iN0CAwEAAQ=="
            const encrypt = new JSEncrypt()
            encrypt.setPublicKey(publicKey)
            const encrypted = encrypt.encrypt(JSON.stringify(dict)) as string
            debug(encrypted)
            isSubmitting.value = true
            fetch('http://localhost:3000/api/v1/get_access_token', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/json',
                },
                body: JSON.stringify({'encrypted': encrypted}),
            }).then(response => response.json()).then(data => {
                isSubmitting.value = false
                debug("收到respond" + JSON.stringify(data))
                debug("收到AccessToken数据：" + JSON.stringify(data))
                if (data['status'] === 'success') {
                    debug('登录成功')
                    ElMessage({
                        message: `欢迎，${data.name}`,
                        type: 'success',
                    })
                    // alert('登录成功')
                    // debug("接受到数据：" + data)
                    document.cookie = 'accessToken=' + data['accessToken']
                    setTimeout(() => {
                        checkLogin(true)
                    }, 2000)
                } else {
                    ElMessage({
                        message: '登录失败，请检查账户名密码后重试',
                        type: 'warning',
                    })
                    debug('登录失败')
                }
            }).catch(error => {
                isSubmitting.value = false
                console.error('Error:', error)
            });
        } else {
            debug('error submit!')
        }
    }).then(() => {
        debug("Submit Done")
    })
}


</script>

<template>
    <el-form :rules="rules" :model="form" label-width="auto" style="max-width: 600px" ref="FormRef"
             size="large">
        <el-form-item label="用户名" prop="id">
            <el-input v-model="form.id"/>
        </el-form-item>
        <el-form-item label="密码" prop="password">
            <el-input v-model="form.password"/>
        </el-form-item>
        <el-form-item label="用户类型" prop="user_type">
            <el-radio-group v-model="form.user_type">
                <el-radio value="Std">学生</el-radio>
                <el-radio value="Tutor">导师</el-radio>
            </el-radio-group>
        </el-form-item>

        <el-form-item label="记住密码">
            <el-switch v-model="form.remember"/>
        </el-form-item>
        <el-form-item>
            <el-button type="primary" @click="onSubmit(FormRef)" :loading="isSubmitting">提交</el-button>
        </el-form-item>
    </el-form>
</template>

<style scoped>

</style>