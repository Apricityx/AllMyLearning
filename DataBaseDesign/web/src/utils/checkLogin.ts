// 此ts文件通过AccessToken验证用户是否登录，当checkLogin()函数参数为1的时候，执行登录界面逻辑
import {debug} from "@/utils/debug.ts";
import {extname} from "path";
import axios from "axios";

export const checkLogin = (isLoginPage: boolean) => {// 根据是否是登录页面进行不同的操作
    debug("Checking Login Status");
    // 此函数的逻辑为：从cookie中获取accessToken，向后端发送请求，验证用户是否登录，如果accessToken验证失败则返回跳回登录页面并清除cookie
    let accessToken = "";
    if (isLoginPage) {
        debug("Login Page, Checking Login Status");
        try {
            accessToken = document.cookie.split(';').find((item) => item.trim().includes('accessToken=')).split('accessToken=')[1];
        } catch (e) {
            return;
        }
        if (accessToken === undefined) {
            debug("No AccessToken Found, Do Nothing");
        } else {
            // 向后端发送鉴权申请
            const url = 'http://localhost:3000/api/v1/auth/authentication_test';
            axios.post(url, {
                "accessToken": accessToken
            }).then((response) => {
                debug("API respond:" + JSON.stringify(response.data));
                if (!response.data.bool) {
                    debug("AccessToken Invalid, Do Noting");
                } else {
                    debug("AccessToken Valid, Redirecting to Main Page");
                    if (response.data.userType === "Std") {
                        debug("Redirecting to StdPage")
                        window.location.href = './StdPage.html';
                    } else {
                        debug("Redirecting to TutorPage")
                        window.location.href = './TutorPage.html';
                    }
                }
            }).catch((error) => {
                debug("Error: " + error);
                document.cookie = 'accessToken=; expires=Thu, 01 Jan 1970 00:00:00 UTC; path=/;';
            })

        }

        return;
    } else {
        debug("Not Login Page, Checking Login Status");
        try {
            accessToken = document.cookie.split(';').find((item) => item.trim().includes('accessToken=')).split('accessToken=')[1];
        } catch (e) {
            debug("No AccessToken Found");
            // 设置一个占位符cookie
            document.cookie = 'accessToken=; expires=Thu, 01 Jan 2080 00:00:00 UTC; path=/;';
            window.location.href = './Login.html';
        }
    }
    // 向后端发送请求
    const url = 'http://localhost:3000/api/v1/auth/test';

}
