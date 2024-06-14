import {Router, Request, Response} from 'express';
import {consoleDebug} from '@/utils/debug';
import sqlite3 from 'better-sqlite3'; // 导入 better-sqlite3 模块
import * as path from "node:path";
import * as constructor from "../../../utils/jsonConstructor";
import {Configs} from "@/utils/loadGlobalVar";

const logger = new consoleDebug();
export const api = Router();
// 创建数据库连接
const db = sqlite3(path.resolve(__dirname, `../../../db/${Configs.database_name}.db`));
api.get('/', (req: Request, res: Response) => {
        db.prepare('DROP TABLE IF EXISTS application').run();
        res.setHeader('Content-Type', 'application/json');
        try {
            // 检查请求参数是否合法
            const key: string = req.query.key as string;
            // const database_name = req.query.database_name as string;
            if (key === undefined) {
                logger.debug("Wrong request: Lack of parameters");
                res.send(constructor.error({"message": "Bad request"}));
                return;
            }

            logger.debug("接收到密钥：" + key);
            if (key === Configs.db_access_key) {
                try {
                    db.prepare('DROP TABLE IF EXISTS Application').run();
                    db.prepare('DROP TABLE IF EXISTS Accepted').run();
                    db.prepare('DROP TABLE IF EXISTS TutorData').run();
                    db.prepare('DROP TABLE IF EXISTS StdData').run();
                    db.prepare('CREATE TABLE StdData(' +
                        'StdID INTEGER PRIMARY KEY AUTOINCREMENT,' +
                        'StdName TEXT,' +
                        'StdInfo TEXT,' +
                        'StdPasswd TEXT,' +
                        'StdEmail TEXT,' +
                        'StdPhone INTEGER)').run();
                    db.prepare("INSERT INTO StdData(StdID,StdName, StdInfo, StdPasswd)" +
                        "VALUES(222023321062100,'王小华','王小华，现为知名大学计算机科学与技术学院的硕士研究生，师从李晓明教授。她于2022年获得本校计算机科学与技术专业的学士学位，并以优异的成绩考取了研究生。', '062100');").run();
                    for (let i = 0; i < 50; i++) {
                        db.prepare("INSERT INTO StdData(StdName, StdInfo, StdPasswd) VALUES(?,?,?)").run('学生' + i, '未填写', "0" + (62101 + i).toString());
                    }

                    db.prepare('CREATE TABLE TutorData(' +
                        'TutorID INTEGER PRIMARY KEY AUTOINCREMENT,' +
                        'TutorName TEXT,' +
                        'TutorInfo TEXT,' +
                        'TutorEmail TEXT,' +
                        'TutorPasswd TEXT)').run();

                    db.prepare("INSERT INTO TutorData(TutorID, TutorName, TutorInfo, TutorPasswd)" +
                        "VALUES(100000,'李晓明" + "','研究方向：人工智能、机器学习、大数据分析，现任职于知名大学的计算机科学与技术学院，担任教授和博士生导师。他于2005年获得本校计算机科学与技术博士学位，随后前往美国麻省理工学院（MIT）进行博士后研究。在MIT期间，他参与了多个国家级人工智能项目，并在顶级学术期刊上发表了多篇高影响力论文。'," + (100000).toString() + ");").run();
                    for (let i = 0; i < 50; i++) {
                        db.prepare("INSERT INTO TutorData(TutorName, TutorInfo, TutorPasswd)" +
                            "VALUES('导师" + i + "','未填写'," + (100001 + i).toString() + ");").run();
                    }

                    db.prepare('CREATE TABLE Accepted(' +
                        'StdID INTEGER,' +
                        'TutorID INTEGER,' +
                        'PRIMARY KEY(StdID, TutorID),' +
                        'FOREIGN KEY(StdID) REFERENCES StdData(StdID),' +
                        'FOREIGN KEY(TutorID) REFERENCES TutorData(TutorID))').run();

                    db.prepare('CREATE TABLE Application(' +
                        'StdID TEXT,' +
                        'TutorID TEXT,' +
                        'Status TEXT,' +
                        'PRIMARY KEY(StdID, TutorID),' +
                        'FOREIGN KEY(StdID) REFERENCES StdData(StdID),' +
                        'FOREIGN KEY(TutorID) REFERENCES TutorData(TutorID))'
                    ).run();
                    db.prepare("INSERT INTO Application(StdID, TutorID, Status) VALUES(222023321062100, 100000, 'Pending')").run();
                    db.prepare("INSERT INTO Application(StdID, TutorID, Status) VALUES(222023321062102, 100000, 'Pending')").run();
                    db.prepare("INSERT INTO Application(StdID, TutorID, Status) VALUES(222023321062103, 100000, 'Pending')").run();
                    db.prepare("INSERT INTO Application(StdID, TutorID, Status) VALUES(222023321062104, 100001, 'Pending')").run();
                    db.prepare("INSERT INTO Application(StdID, TutorID, Status) VALUES(222023321062104, 100000, 'Rejected')").run();

                    res.send(constructor.success({"message": "Database has been reset!"}))
                    logger.debug("Database has been reset!")
                } catch
                    (e) {
                    logger.error("Failed to reset database: " + e);
                    res.send(constructor.error({"message": "Failed to reset database"}))
                    return
                }
            } else {
                res.send(constructor.error({"message": "Wrong key"}));
            }
        } catch
            (error) {
            logger.error("请求错误：缺少参数");
            res.send(constructor.error({"message": "Bad request"}));
        }
    }
)
;
