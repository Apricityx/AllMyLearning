import {Router, Request, Response} from 'express';
import {consoleDebug} from '@/utils/debug';
import * as constructor from "@/utils/jsonConstructor";
import bodyParser from "body-parser";
import cors from 'cors';
import {CheckAuthentication} from "@/utils/authentication";

const logger = new consoleDebug();
export const api = Router();

// 使用中间件
api.use(bodyParser.json());
// api.use(bodyParser.urlencoded({extended: true}));
api.use(cors());

api.post('/', (req: Request, res: Response) => {
    const accessToken = req.body.accessToken
    logger.conn("BASE64: " + accessToken)
    const result = CheckAuthentication(accessToken)
    res.send(constructor.success(result))
})
