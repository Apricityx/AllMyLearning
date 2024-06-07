<script setup lang="ts">
import type {ComponentSize, FormRules} from 'element-plus'
import {reactive, ref, watch} from 'vue'
import JSEncrypt from 'jsencrypt'

</script>
<!--从外部引入js-->
<template>
    <div id="main"
         style="width: fit-content;padding: 50px 100px;border-radius: 25px">
        <h1>LOGIN</h1>
        <el-form :rules="formRules" :model="form" label-width="auto" style="max-width: 600px" ref="LoginForm"
                 size="large">
            <el-form-item label="用户名" prop="name">
                <el-input v-model="form.name"/>
            </el-form-item>
            <el-form-item label="密码" prop="password">
                <el-input v-model="form.password"/>
            </el-form-item>
            <el-form-item label="用户类型" prop="type">
                <el-radio-group v-model="form.type">
                    <el-radio value="Std">学生</el-radio>
                    <el-radio value="Tutor">导师</el-radio>
                </el-radio-group>
            </el-form-item>

            <el-form-item label="记住密码">
                <el-switch v-model="form.remember"/>
            </el-form-item>
            <el-form-item>
                <el-button type="primary" @click="submitForm(LoginForm)">提交</el-button>
            </el-form-item>
        </el-form>
    </div>
</template>

<style>

.demo-input .tiny-input {
    width: 250px;
}

.el-form-item__label {
    color: #ffffff;
}

.el-radio__label {
    color: #ffffff;
}

#app {
    height: 97vh;
    display: flex;
    flex-direction: row;
    justify-content: center;
    align-content: center;
}

.btn-grad {
    margin: 10px;
    padding: 15px 45px;
    text-align: center;
    text-transform: uppercase;
    transition: 0.5s;
    background-size: 200% auto;
    color: white;
    box-shadow: 0 0 20px #eee;
    border-radius: 10px;
    display: block;
}

.btn-grad:hover {

}

#main {
    height: fit-content;
    background-image: linear-gradient(to right, #085078 0%, #4f91a5 51%, #085078 100%);
    margin: 10px;
    padding: 15px 45px;
    transition: 0.5s;
    background-size: 200% auto;
    color: #29c1fa;
    box-shadow: 0 0 20px #000000;
    border-radius: 10px;
}

#main:hover {
    color: #fff;
    text-decoration: none;
}
</style>
<script lang="ts"> // 表单校验
// import {ref} from "vue";

// import {reactive} from "vue";

// import {JSEncrypt} from "jsencrypt";
// DEBUG函数

function debug(content: any) {
    console.log(content)
}


// signOut方法

function signOut() {
    document.cookie = 'accessToken=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
}


signOut()

const LoginForm = ref<FormInstance>()
import {FormInstance} from "element-plus";
import {parseJsonText} from 'typescript';

const form = reactive({
    name: '',
    password: '',
    remember: false,
    type: 'User',
});

// 获取记住密码的信息
// 记住密码的信息在cookie中，键为userInfo
const userInfo = document.cookie.split('; ').find(row => row.startsWith('userRemember'))
debug("获取到的userInfo：" + userInfo)
if (userInfo) {
    const userInfoBase64 = userInfo.split('=')[1]
    const userInfoJson = atob(userInfoBase64)
    const userInfoDict = JSON.parse(userInfoJson)
    debug("获取到的userInfoDict：" + userInfoDict)
    form.name = userInfoDict['name']
    form.password = userInfoDict['password']
    form.type = userInfoDict['type']
    form.remember = true
}
// 监听remember变化
watch(() => form.remember, (newValue) => {
    if (!newValue) {
        document.cookie = 'userRemember=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
        debug('取消记住密码勾选')
    } else {
        debug('记住密码勾选')
        const dict = {
            'name': form.name,
            'password': form.password,
            'type': form.type,
        }
        const dictBase64 = btoa(JSON.stringify(dict))
        document.cookie = 'userRemember=' + dictBase64
    }
});


export default {
    data() { // 表单模型
        return {
            form: {
                name: '',
                password: '',
            },
            formRules: {
                name: [
                    {required: true, message: '请输入姓名', trigger: 'blur'},
                ],
                password: [
                    {required: true, message: '请输入密码', trigger: 'blur'},
                    {min: 6, message: '密码长度不能少于6位', trigger: 'blur'},
                ],
                type: [
                    {required: true, message: '请选择用户类型', trigger: 'submit'},
                ],
            },
        };
    },
    methods: {
        submitForm(formEl: FormInstance | undefined) { // ts语法，规定传入参数的类型要么是FormInstance，要么是undefined
            if (!formEl) return
            formEl.validate((valid, fields) => {
                if (valid) {
                    debug('submit!')
                    const name = form.name
                    const password = form.password
                    const dict = {
                        'name': name,
                        'password': password,
                        'type': form.type,
                    }

                    // 如果记住密码，将信息存入cookie
                    let saveInfo = (infoDict: any) => {
                        if (form.remember) {
                            const dictBase64 = btoa(JSON.stringify(dict))
                            document.cookie = 'userRemember=' + dictBase64
                            debug('记住密码触发')
                        } else {
                            document.cookie = 'userRemember=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
                        }
                    }
                    saveInfo(dict)

                    // RAS加密
                    let publicKey = "MIICCgKCAgEA4vVjhCKuq6JOUmje/hz7B9IQYTLNsXwY365RIJNdLwHdhY/q3qBSTWOpUeh2I8BdYuFVnAqWqZGfDfXSKjRCrxKMKMRXl87DsTStDcJz5hRgGPK++C61cnbQSRfeVvp4WfJn/iFusaxi6NwJJA56xThrnA5gYcbaZ49VLjE9HNmwf2Jz+SApyed4g1ec5vK2x4W/PBOD3/JABYZ3uWKPfYvlBIURe9fUj378eIOO+r6Cb/KrZPW+CcBTfVmLdPCwLYqmlT1L1hM13mm+5gbA3RE2wTn7Rd3AEPuJEeYdG/nytNSMsOCkNuVtgZuEg7dCbhUqRdQJw6OpO24Q//x2lENl6+qaWe43ZDKo1M8vVfquQI2mZRmZ6TDfaEFGT6c0dAqSXWteH2tpB/YHX5Z3rrdtDk4fLIg9V5zQbeNceSdBq59lNU2Uq3Qp+E8JR/ZttpdLgSfe9KGDuh+Xftwg1jea0Emsrqsw/DKx4xnf2RkAFY6F+0del+JFnEH15CbiN/pWxkQ0kMZHq3S27NKTvFEGGEjxMz5UZFlMhAZvTpei8bQ9f2JnHHR7YkjZSO+Szhi4QlsMomy64Udw6R4mHuMSA6jS8Y7S4dYWgEfahvIOm87PQ5BetJW55FrdfrllKIwH6gxfZ+zp5qVw8NTbDPYzDqixCJymXRBQ7FV9iN0CAwEAAQ=="
                    let encrypt = new JSEncrypt()
                    encrypt.setPublicKey(publicKey)
                    let encrypted = encrypt.encrypt(JSON.stringify(dict))
                    debug(encrypted)
                    // 输出当前目录
                    // let route:any = document.scripts;
                    // route = route[route.length - 1].src.substring(0, route[route.length - 1].src.lastIndexOf("/") + 1);
                    // console.log(route)
                    // 发送POST请求
                    fetch('http://localhost:3000/api/v1/get_access_token', {
                        method: 'POST',
                        headers: {
                            'Content-Type': 'application/json',
                        },
                        body: JSON.stringify({'encrypted': encrypted}),
                    }).then(response => response.json()).then(data => {
                        debug(JSON.stringify(data))
                        if (data['status'] === 'success') {
                            debug('登录成功')
                            alert('登录成功')
                            document.cookie = 'accessToken=' + encrypted
                        } else {
                            alert('登录失败')
                            debug('登录失败')
                        }
                    }).catch(error => console.error('Error:', error));
                } else {
                    debug('error submit!')
                }
            })
        },
    },
};

// const submitForm = async (formEl: FormInstance | undefined) => {
//     if (!formEl) return
//     await formEl.validate((valid, fields) => {
//         if (valid) {
//             console.log('submit!')
//             console.log()
//         } else {
//             console.log('error submit!')
//         }
//     })
// }
</script>
