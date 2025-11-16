<template>
    <div style="display: flex; flex-direction: column;justify-content: center; align-items: center; height: 93vh;">
        <div class="DivContainer">
            <p class="text-h1" style="margin-bottom: 5%;color:#000000">
                LOGIN
            </p>
            <v-sheet class="mx-auto" max-width="300">
                <v-form ref="form" validate-on="submit lazy" @submit.prevent="submit" :disabled="formDisable"
                        style="width: 300px">
                    <v-text-field
                        v-model="state.userName"
                        label="User name"
                        :rules="nameRules"
                        required
                    ></v-text-field>
                    <v-text-field
                        v-model="state.passWord"
                        label="Password"
                        type="password"
                        :rules="[(v) => !!v || 'Password is required',(v)=>v.length>=6||'Password must be at least 6 characters']"
                        required
                    ></v-text-field>
                    <v-btn
                        :loading="loading"
                        class="mt-2"
                        :text="submitButtonText"
                        type="submit"
                        block
                        ref="submitButton"
                        :prepend-icon="submitResult?'mdi-check':''"
                        :disabled="formDisable"
                    ></v-btn>

                </v-form>
                <v-btn
                    class="mt-2"
                    text="Register"
                    type="submit"
                    block
                    ref="submitButton"
                    :disabled="formDisable"
                    @click="goRegister"
                ></v-btn>
            </v-sheet>
        </div>
    </div>
</template>

<script setup lang="ts">
import {ref, reactive} from 'vue'
import axios from "axios";
import {Config} from "@/utils/loadGlobalVar";
import type {Raw} from "@vue/runtime-core";
import JSEncrypt from "jsencrypt";

const loading = ref(false)
const initialState = {
    userName: '',
    passWord: '',
    checkbox: null,
}

const state = reactive({
    ...initialState,
})

const nameRules = [
    (v: any) => !!v || 'Name is required',
    (v: any) => (v && v.length <= 10) || 'Name must be less than 10 characters',
]

const form = ref()
const submitButton = ref()
const submitResult = ref()
const submitButtonText = ref('Submit')
const formDisable = ref(false)

const submit = async () => {
    loading.value = true
    const valid = await form.value.validate().then((valid: any) => {
        if (valid.valid) {
            return true
        } else {
            loading.value = false
            return false
        }
    })
    if (valid) {
        formDisable.value = true;

        interface RawRequestData {
            "userName": string,
            "passWord": string
        }

        const rawRequestData: RawRequestData = {
            "userName": state.userName,
            "passWord": state.passWord
        }
        const publicKey = "MIICCgKCAgEA4vVjhCKuq6JOUmje/hz7B9IQYTLNsXwY365RIJNdLwHdhY/q3qBSTWOpUeh2I8BdYuFVnAqWqZGfDfXSKjRCrxKMKMRXl87DsTStDcJz5hRgGPK++C61cnbQSRfeVvp4WfJn/iFusaxi6NwJJA56xThrnA5gYcbaZ49VLjE9HNmwf2Jz+SApyed4g1ec5vK2x4W/PBOD3/JABYZ3uWKPfYvlBIURe9fUj378eIOO+r6Cb/KrZPW+CcBTfVmLdPCwLYqmlT1L1hM13mm+5gbA3RE2wTn7Rd3AEPuJEeYdG/nytNSMsOCkNuVtgZuEg7dCbhUqRdQJw6OpO24Q//x2lENl6+qaWe43ZDKo1M8vVfquQI2mZRmZ6TDfaEFGT6c0dAqSXWteH2tpB/YHX5Z3rrdtDk4fLIg9V5zQbeNceSdBq59lNU2Uq3Qp+E8JR/ZttpdLgSfe9KGDuh+Xftwg1jea0Emsrqsw/DKx4xnf2RkAFY6F+0del+JFnEH15CbiN/pWxkQ0kMZHq3S27NKTvFEGGEjxMz5UZFlMhAZvTpei8bQ9f2JnHHR7YkjZSO+Szhi4QlsMomy64Udw6R4mHuMSA6jS8Y7S4dYWgEfahvIOm87PQ5BetJW55FrdfrllKIwH6gxfZ+zp5qVw8NTbDPYzDqixCJymXRBQ7FV9iN0CAwEAAQ=="
        const encrypt = new JSEncrypt()
        encrypt.setPublicKey(publicKey)
        const requestData = {
            "encrypted": encrypt.encrypt(JSON.stringify(rawRequestData)) as string
        }
        console.log(JSON.stringify(requestData))
        axios.post(Config.address + '/api/v1/get_access_token', requestData).then((res: any) => {
            interface result {
                state: number,
                accessToken: string,
            }

            const response: result = res.data
            console.log(response)
            if (response.state === 200) {
                loading.value = false
                submitResult.value = true
                submitButtonText.value = 'Success'
                formDisable.value = true;
            } else {
                loading.value = false
                submitResult.value = false
                submitButtonText.value = 'Failed'
                setTimeout(() => {
                    submitButtonText.value = 'Submit'
                }, 2000)
                formDisable.value = false;
            }
        }).catch((err: any) => {
            console.log(err)
        })
    }
}
const goRegister = () => {
    uni.navigateTo({
        url: '/pages/Register',
        animationType: 'pop-in'
    })
}
</script>

<style>
body {
    margin: 0;
    padding: 0;
    background-image: url("@/static/img/bg.jpg");
    background-repeat: no-repeat;
    background-size: cover;
}
</style>
<style scoped>
.DivContainer {
    padding: 5%;
    border-radius: 10px;
    background: rgba(255, 255, 255, 1);
    backdrop-filter: blur(5px);
    margin-bottom: 30px;
    opacity: 0.9;
}
</style>