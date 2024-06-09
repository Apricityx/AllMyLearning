import {Router, Request, Response} from 'express';
import {consoleDebug} from '@/utils/debug';
import sqlite3 from 'better-sqlite3'; // 导入 better-sqlite3 模块
import * as path from "node:path";
import * as Constructor from "@/utils/jsonConstructor";
import {Configs} from "@/utils/loadGlobalVar";
import bodyParser from "body-parser";
import cors from 'cors';
import * as fs from "node:fs"; // 导入 cors 模块
import * as forge from "node-forge";
import {CheckAuthentication} from "@/utils/authentication";

const logger = new consoleDebug();
const db = sqlite3(path.resolve(__dirname, '../../db/' + Configs.database_name + '.db'));

interface OneStd {
    "name": string
    "email": string
    "phone": string
    "introduction": string
}

interface OneRequest {
    "id": 1,
    "stdId": 1,
    "status": "pending" | "accepted" | "rejected"
    "stdInfo": OneStd
}

export const tutor_get_info = (stdID: string) => {
    let selfInfo = {}
    let finalResponse = Constructor.success({
        message: "Tutor Get Info Successfully",
        stdRequests: [],
        selfInfo: selfInfo
    })
}