import {Router, Request, Response} from 'express';
import {consoleDebug} from '../../utils/debug';
import sqlite3 from 'better-sqlite3'; // 导入 better-sqlite3 模块
import * as path from "node:path";
import * as constructor from "../../utils/jsonConstructor";
import {Configs} from "../../utils/loadGlobalVar";
import bodyParser from "body-parser";
import cors from 'cors';
import * as fs from "node:fs"; // 导入 cors 模块
import * as forge from "node-forge";

const logger = new consoleDebug();
export const api = Router();
const db = sqlite3(path.resolve(__dirname, '../../db/' + Configs.database_name + '.db'));

// 读取本地私钥准备解密
let privateKey = '';
if (fs.existsSync(path.resolve(__dirname, "../../keys/private.pem"))) {
    // logger.debug("Private Key Loaded")
    privateKey = fs.readFileSync(path.resolve(__dirname, "../../keys/private.pem"), 'utf-8');
} else {
    // logger.error("Private Key File Not Found")
}


// 使用中间件
api.use(bodyParser.json());
// api.use(bodyParser.urlencoded({extended: true}));
api.use(cors());

api.post('/', (req: Request, res: Response) => {// console.log(req.body)
    const dataBase64 = req.body.encrypted
    logger.debug(dataBase64)
    const dataRSA = forge.util.decode64(dataBase64)
    const data = forge.pki.privateKeyFromPem(privateKey).decrypt(dataRSA)
    logger.debug(data)
    res.send(constructor.success("Success"))
})