import {Router, Request, Response} from 'express';
import {consoleDebug} from '@/utils/debug';
import sqlite3 from 'better-sqlite3'; // 导入 better-sqlite3 模块
import * as path from "node:path";
import * as constructor from "@/utils/jsonConstructor";
import {Configs} from "@/utils/loadGlobalVar";
import bodyParser from "body-parser";
import cors from 'cors';
import * as fs from "node:fs"; // 导入 cors 模块
import * as forge from "node-forge";

const logger = new consoleDebug();
export const api = Router();
const db = sqlite3(path.resolve(__dirname, '../../db/' + Configs.database_name + '.db'));

// 读取本地私钥准备解密
const privateKey = Configs.privateKey;
const publicKey = Configs.publicKey;
// 使用中间件
api.use(bodyParser.json());
// api.use(bodyParser.urlencoded({extended: true}));
api.use(cors());

api.post('/', (req: Request, res: Response) => {// console.log(req.body)
    const dataBase64: string = req.body.encrypted
    // logger.conn("BASE64: " + dataBase64)
    const dataRSA: string = forge.util.decode64(dataBase64)
    const data: string = forge.pki.privateKeyFromPem(privateKey).decrypt(dataRSA)
    logger.conn("Login Info " + data)
    const info = JSON.parse(data)
    // const result: any = db.prepare("SELECT * FROM StdData WHERE StdID = ? AND StdPasswd = ?").get(info.name, info.password)
    const loginType = info.user_type === 'Std' ? 'StdData' : 'TutorData'
    logger.debug("Login Type: " + loginType)
    const result: any = db.prepare(`SELECT * FROM ${loginType} WHERE ${loginType === 'StdData' ? 'StdID' : 'TutorID'} = ? AND ${loginType === 'StdData' ? 'StdPasswd' : 'TutorPasswd'} = ?`).get(info.name, info.password)
    // 防止注入攻击
    logger.debug("尝试登录：用户名：" + info.name + " 密码：" + info.password + " 登录类型：" + info.type)
    if (result === undefined) {
        res.send(constructor.error({"message": "Wrong Password or User Name"}))
        logger.debug("登录失败：用户名：" + info.name + " 密码：" + info.password + " 登录类型：" + info.type)
        return
    } else {
        logger.debug("登录成功：用户名：" + info.name + " 密码：" + info.password + " 登录类型：" + info.type)
        const rawAccessToken = JSON.stringify({
            "ID": info.name,
            "Passwd": info.password,
            "Type": info.user_type,
            "TimeStamp": new Date().getTime()
        })
        logger.debug("Access Token Raw Data: " + rawAccessToken)
        const accessToken = forge.util.encode64(forge.pki.publicKeyFromPem(publicKey).encrypt(rawAccessToken))
        res.send(constructor.success({"accessToken": accessToken}))
    }
})
