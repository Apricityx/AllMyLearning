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
    "tutorId": string,
    "name": string
    "email": string
    "phone": string
    "introduction": string
    "requestStatus": "pending" | "accepted" | "rejected"
}

interface TutorFromDB {
    TutorID: string,
    TutorName: string,
    TutorEmail: string,
    Phone: string,
    TutorInfo: string
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
        tutors: [],
        selfInfo: selfInfo
    }
    let tutors_data = db.prepare(`SELECT * FROM TutorData`).all()
    for (let i = 0; i < tutors_data.length; i++) {
        let tutor = tutors_data[i] as TutorFromDB
        // logger.debug("Tutor: " + JSON.stringify(tutor))
        // 是否有申请 -> 申请状态
        let request = db.prepare(`SELECT IsAccepted FROM Application WHERE StdID = ? AND TutorID = ?`).get(stdID, tutor.TutorID)
        // @ts-ignore
        let request_status = request.IsAccpeted
        if (request_status === undefined) {
            request_status = "Unset"
        } else {
            request_status = request_status === "True" ? "accepted" : "rejected"
        }
        let tutorInfo: Tutors = {
            tutorId: tutor.TutorID,
            name: tutor.TutorName,
            email: tutor.TutorEmail,
            phone: tutor.Phone,
            introduction: tutor.TutorInfo,
            requestStatus: request_status
        }
        // @ts-ignore
        finalResponse.tutors.push(tutorInfo)
    }
    return finalResponse
}