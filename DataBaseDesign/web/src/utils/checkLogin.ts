// 此ts文件通过AccessToken验证用户是否登录，当checkLogin()函数参数为1的时候，执行登录界面逻辑
import {debug} from "@/utils/debug.ts";
import {extname} from "path";
import axios from "axios";

const foo = (fun: any) => {
    let accessToken = "";
    try {
        accessToken = document.cookie.split(';').find((item) => item.trim().includes('accessToken=')).split('accessToken=')[1];
        debug("AccessToken Found: " + accessToken);
    } catch (e) {
        fun({data: {bool: false}});
        return;
    }
    // 向后端发送鉴权申请
    const url = 'http://localhost:3000/api/v1/auth/authentication_test';
    axios.post(url, {
        "accessToken": accessToken
    }).then((response) => {
        fun(response)
    }).catch((error) => {
        debug("Error: " + error);
        debug("No AccessToken Found");
        // 设置一个占位符cookie
        document.cookie = 'accessToken=; expires=Thu, 01 Jan 2080 00:00:00 UTC; path=/;';
        window.location.href = './Login.html';
    })
    return;
}

export const checkLogin = (isLoginPage: boolean) => {// 根据是否是登录页面进行不同的操作
    debug("Checking Login Status");
    // 此函数的逻辑为：从cookie中获取accessToken，向后端发送请求，验证用户是否登录，如果accessToken验证失败则返回跳回登录页面并清除cookie
    if (isLoginPage) {
        debug("Login Page, Checking Login Status");
        foo((response: any) => {
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
        })
    } else {
        debug("Not Login Page, Checking Login Status");
        foo((response: any) => {
            debug("API respond:" + JSON.stringify(response.data));
            if (!response.data.bool) {
                debug("AccessToken Invalid, Redirecting to Login Page");
                window.location.href = './Login.html';
            } else {
                debug("AccessToken Valid, Do Nothing");
            }
        })
    }
}
