import {Router, Request, Response} from 'express';
import {consoleDebug} from '../../utils/debug';
import * as constructor from '../../utils/jsonConstructor'

const logger = new consoleDebug();
export const api = Router();

api.get('/', (req: Request, res: Response) => {
    res.setHeader('Content-Type', 'application/json');
    res.send(constructor.success({"message": "pong"}));
});