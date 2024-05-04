<script setup lang="ts">
// import HelloWorld from './components/HelloWorld.vue'
// import TheWelcome from './components/TheWelcome.vue'
// import {Button as TinyButton} from '@opentiny/vue'
// import { Input as TinyInput} from '@opentiny/vue'
import type {ComponentSize, FormRules} from 'element-plus'
import {reactive, ref} from 'vue'
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
      <el-form-item label="用户类型" prop="user_type">
        <el-radio-group v-model="form.type">
          <el-radio value="Sponsor">用户</el-radio>
          <el-radio value="Venue">管理员</el-radio>
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
.el-radio__label{
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
  background-image: linear-gradient(to right, #085078 0%, #4f91a5 51%, #085078  100%);
  margin: 10px;
  padding: 15px 45px;
  transition: 0.5s;
  background-size: 200% auto;
  color: #29c1fa;
  box-shadow: 0 0 20px #000000;
  border-radius: 10px;
}
#main:hover{
  color: #fff;
  text-decoration: none;
}
</style>

<script lang="ts"> // 表单校验
// import {ref} from "vue";

// import {reactive} from "vue";

// import {JSEncrypt} from "jsencrypt";

const LoginForm = ref<FormInstance>()
import {FormInstance} from "element-plus";
import {parseJsonText} from 'typescript';

const form = reactive({
  name: '',
  password: '',
  remember: false,
  type: 'Sponsor',
})
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
        user_type: [
          {required: false, message: '请选择用户类型', trigger: 'submit'},
        ],
      },
    };
  },
  methods: {
    submitForm(formEl: FormInstance | undefined) { // ts语法，规定传入参数的类型要么是FormInstance，要么是undefined
      if (!formEl) return
      formEl.validate((valid, fields) => {
        if (valid) {
          console.log('submit!')
          let name = form.name
          let password = form.password
          let dict = {
            'name': name,
            'password': password
          }
          console.log(JSON.stringify(dict))
          // RAS加密
          let publicKey = 'MFwwDQYJKoZIhvcNAQEBBQADSwAwSAJBAMIaVSLTStb7Fcbk+kwEFk1xyP76wkXJALcaX4fUpPfeZtRw55CFVQR2QwLYrT1GiM8iyPl23+pZi/uoKj03kx8CAwEAAQ=='
          let encrypt = new JSEncrypt()
          encrypt.setPublicKey(publicKey)
          let encrypted = encrypt.encrypt(JSON.stringify(dict))
          console.log(encrypted)
          // 输出当前目录
          // let route:any = document.scripts;
          // route = route[route.length - 1].src.substring(0, route[route.length - 1].src.lastIndexOf("/") + 1);
          // console.log(route)
          // 发送POST请求
          fetch('http://localhost/api/login.php', {
            method: 'POST',
            headers: {
              'Content-Type': 'application/json',
            },
            body: JSON.stringify({'encrypted': encrypted}),
          }).then(response => response.json()).then(data => {
            console.log(JSON.stringify(data))
            if (data['status'] === 'success') {
              console.log('登录成功')
              alert('登录成功')
              document.cookie = 'user_information=' + encrypted
            } else {
              alert('登录失败')
              console.log('登录失败')
            }
          })
        } else {
          console.log('error submit!')
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
