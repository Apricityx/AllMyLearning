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
import {CheckAuthentication} from "@/utils/authentication";
import {std_get_info} from "@/utils/getInfo/stdInfo";
import {tutor_get_info} from "@/utils/getInfo/tutorInfo";

const logger = new consoleDebug();
export const api = Router();
const db = sqlite3(path.resolve(__dirname, '../../../db/' + Configs.database_name + '.db'));

// 使用中间件
api.use(bodyParser.json());
// api.use(bodyParser.urlencoded({extended: true}));
api.use(cors());

api.post('/', (req: Request, res: Response) => {
    const postMessage = req.body
    logger.conn("POST Request: " + JSON.stringify(postMessage))
    // 初始化所有参数
    const accessToken = postMessage.accessToken
    const authResult = CheckAuthentication(accessToken)
    logger.debug("AuthResult: " + JSON.stringify(authResult))
    if (authResult.status === "Decryption Failed"){
        res.send(constructor.error({"message": "Decryption Failed"}))
        return
    }
    const requestType = authResult.userType as string
    const UserID = authResult.userID as string
    logger.debug("Request Type: " + requestType + " UserID: " + UserID)
    if (accessToken === undefined || requestType === undefined || UserID === undefined) {
        res.send(constructor.error({"message": "Lack of Parameters"}))
        logger.warning("Bad AccessToken")
        return
    }
    if (requestType === "Std") {
        logger.debug("Request Type: Std" + " StdID: " + UserID)
        res.send(constructor.success(std_get_info(UserID)))
    }

})