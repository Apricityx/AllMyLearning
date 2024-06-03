import {Router, Request, Response} from 'express';
import {consoleDebug} from '../../utils/debug';
import sqlite3 from 'better-sqlite3'; // 导入 better-sqlite3 模块
import * as path from "node:path";
import * as constructor from "../../utils/jsonConstructor";
import {Configs} from "../../utils/loadGlobalVar";

const logger = new consoleDebug();
export const api = Router();
const db = sqlite3(path.resolve(__dirname, '../../db/' + Configs.database_name + '.db'));
