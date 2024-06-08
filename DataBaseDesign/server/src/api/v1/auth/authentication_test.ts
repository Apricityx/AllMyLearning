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
import {isAuthenticated} from "@/utils/authentication";

const logger = new consoleDebug();
export const api = Router();
const db = sqlite3(path.resolve(__dirname, '../../../db/' + Configs.database_name + '.db'));

// 使用中间件
api.use(bodyParser.json());
// api.use(bodyParser.urlencoded({extended: true}));
api.use(cors());

api.post('/', (req: Request, res: Response) => {
    const userInfo = req.body.accessToken
    logger.conn("BASE64: " + userInfo)
    const result = isAuthenticated(userInfo)
    res.send(constructor.success({"message": result}))
})
