import {consoleDebug} from "./debug";
import fs from "node:fs";
import path from "node:path";
import {Configs} from "./loadGlobalVar";
import * as forge from "node-forge";
import sqlite3 from "better-sqlite3";
import * as Constructor from "@/utils/jsonConstructor"
import {tls} from "node-forge";


const logger = new consoleDebug();
let privateKey = '';
let publicKey = '';

interface message {
    "status": string,
    "message": string,
    "bool": boolean,
    "userType"?: string,
    "userID"?: string
}

export const CheckAuthentication = (accessToken: string): message => {
    const privateKey = Configs.privateKey;
    // 解密数据
    let data;
    try {
        const dataRSA = forge.util.decode64(accessToken);
        data = forge.pki.privateKeyFromPem(privateKey).decrypt(dataRSA);
    } catch (e) {
        logger.warning("Decryption Failed, Wrong Access Token Format");
        return {"status": "Decryption Failed", "message": "Decryption Failed", "bool": false};
    }
    const info = JSON.parse(data);
    logger.conn("Access Token Info " + JSON.stringify(info));
    // 验证Access Token是否过期
    const timeStamp = info.TimeStamp;
    const currentTime = new Date().getTime();
    if (currentTime - timeStamp > 1000 * 60 * 60 * 24) {
        logger.debug("Access Token Expired");
        return Constructor.error({"message": "Access Token Expired", "bool": false});
    }
    // 查询数据库
    const db = sqlite3(path.resolve(__dirname, `../db/${Configs.database_name}.db`));
    // 防止注入攻击
    logger.debug("尝试鉴权：用户名：" + info.ID + " 密码：" + info.Passwd + " 登录类型：" + info.Type);
    let result;
    if (info.Type === 'Std') {
        result = db.prepare("SELECT * FROM StdData WHERE StdID = ? AND StdPasswd = ?").get(info.ID, info.Passwd);
    } else if (info.Type === 'Tutor') {
        result = db.prepare("SELECT * FROM TutorData WHERE TutorID = ? AND TutorPasswd = ?").get(info.ID, info.Passwd);
    } else {
        logger.debug("鉴权失败：用户名：" + info.ID + " 密码：" + info.Passwd + " 登录类型：" + info.Type);
        result = undefined;
        return Constructor.error({"message": "Wrong User Type", "bool": false});
    }
    if (result === undefined) {
        logger.debug("鉴权失败：用户名：" + info.ID + " 密码：" + info.Passwd + " 登录类型：" + info.Type);
        return Constructor.error({"message": "Wrong Password or User Name", "bool": false});
    } else {
        logger.debug("鉴权成功：用户名：" + info.ID + " 密码：" + info.Passwd + " 登录类型：" + info.Type);
        return Constructor.success({
            "message": "Authentication Success",
            "bool": true,
            "userType": info.Type,
            "userID": info.ID
        });
    }
}