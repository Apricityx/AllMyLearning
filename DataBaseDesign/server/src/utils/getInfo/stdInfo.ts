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
import * as stream from "node:stream";

const logger = new consoleDebug();
const db = sqlite3(path.resolve(__dirname, '../../db/' + Configs.database_name + '.db'));

interface Tutors {
    "TutorID": string,
    "TutorName": string
    "TutorInfo": string
    "TutorEmail": string,
    "Status": string
}

export const std_get_info = (stdID: string) => {
    let selfInfo = {
        name: "",
        email: "",
        phone: "",
        introduction: ""
    }
    let finalResponse = {
        message: "Student Get Info Successfully",
        status: "success",
        tutor: "unset",
        tutors: [] as Tutors[],
        selfInfo: selfInfo
    }
    const selfInfoFromDB = db.prepare("SELECT * FROM StdData WHERE StdID = ?").get(stdID) as any
    if (selfInfoFromDB === undefined) {
        finalResponse.message = "Student Not Found"
        finalResponse.status = "error"
        return finalResponse
    }
    selfInfo.name = selfInfoFromDB.StdName
    selfInfo.email = selfInfoFromDB.StdEmail
    selfInfo.phone = selfInfoFromDB.Phone
    selfInfo.introduction = selfInfoFromDB.StdInfo

    // 如果Accepted表中有该学生的数据，则填写tutor
    const selectInfoFromDB = db.prepare("SELECT * FROM Accepted WHERE StdID = ?").get(stdID) as any
    const isAccepted: boolean = selectInfoFromDB !== undefined
    // logger.debug("Is Accepted: " + isAccepted)
    if (selectInfoFromDB !== undefined) {
        // logger.debug("Tutor: " + JSON.stringify(selectInfoFromDB))
        finalResponse.tutor = selectInfoFromDB.TutorID
        return finalResponse
    } else {
        // 合并表，填写tutors
        const tutorsFromDB: Tutors[] = db.prepare("SELECT TutorData.TutorID,TutorData.TutorName,TutorData.TutorInfo,Status FROM TutorData LEFT JOIN Application ON TutorData.TutorID = Application.TutorID AND Application.StdID = ?;").all(stdID) as Tutors[];
        logger.debug("Tutors: " + JSON.stringify(tutorsFromDB))
        finalResponse.tutors = tutorsFromDB
        logger.debug("最终返回数据：" + JSON.stringify(finalResponse))
        return finalResponse
    }
}