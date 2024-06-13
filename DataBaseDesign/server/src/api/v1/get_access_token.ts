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
    // logger.debug("转化后的info" + JSON.stringify(info))
    // const result: any = db.prepare("SELECT * FROM StdData WHERE StdID = ? AND StdPasswd = ?").get(info.name, info.password)
    const loginType = info.user_type === 'Std' ? 'StdData' : 'TutorData'
    logger.debug("Login Type: " + loginType)
    // 防止注入攻击
    const result: any = db.prepare(`SELECT * FROM ${loginType} WHERE ${loginType === 'StdData' ? 'StdID' : 'TutorID'} = ? AND ${loginType === 'StdData' ? 'StdPasswd' : 'TutorPasswd'} = ?`).get(info.id, info.password)
    logger.debug("获取到数据库信息：" + JSON.stringify(result))
    logger.debug("尝试登录：用户ID：" + info.id + " 密码：" + info.password + " 登录类型：" + info.user_type)
    if (result === undefined) {
        res.send(constructor.error({"message": "Wrong Password or User ID"}))
        logger.debug("登录失败：用户ID：" + info.id + " 密码：" + info.password + " 登录类型：" + info.user_type)
        return
    } else {
        info.name = info.user_type === "Std" ? result.StdName : result.TutorName
        logger.debug("获取到用户名字 " + info.name)
        logger.debug("登录成功：用户ID：" + info.id + " 密码：" + info.password + " 登录类型：" + info.user_type)
        const rawAccessToken: string = JSON.stringify({
            "ID": info.id,
            "Passwd": info.password,
            "Type": info.user_type,
            "TimeStamp": new Date().getTime() + 1000 * 60 * 60 * 240 // 240小时过期
        })
        logger.debug("Access Token Raw Data: " + rawAccessToken)
        const accessToken = forge.util.encode64(forge.pki.publicKeyFromPem(publicKey).encrypt(rawAccessToken))
        res.send(constructor.success({"accessToken": accessToken, "name": info.name}))
    }
})
