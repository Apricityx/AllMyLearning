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

interface SelfInfo {
    "tutorId": string,
    "name": string
    "email": string
    "phone": string
    "introduction": string
}

export const tutor_get_info = (tutorID: string) => {
    let selfInfo = {}
    let finalResponse = Constructor.success({
        message: "Tutor Get Info Successfully",
        stdRequests: [],
        selfInfo: selfInfo as SelfInfo
    })
    const stdRequestFromDB = db.prepare("SELECT StdData.StdID,StdData.StdInfo as introduction,Application.Status,StdData.StdName FROM Application INNER JOIN StdData ON Application.StdID = StdData.StdID WHERE Application.TutorID=?;").all(tutorID) as any
    logger.debug("Requests Info: " + JSON.stringify(stdRequestFromDB))
    const selfInfoFromDB = db.prepare("SELECT * FROM TutorData WHERE TutorID = ?").get(tutorID) as any
    logger.debug("Self Info: " + JSON.stringify(selfInfoFromDB))

    finalResponse.selfInfo = selfInfoFromDB
    finalResponse.stdRequests = stdRequestFromDB

    logger.debug("Final Response: " + JSON.stringify(finalResponse))
    return finalResponse
}