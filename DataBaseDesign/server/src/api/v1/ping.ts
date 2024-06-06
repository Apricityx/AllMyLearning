import {Router, Request, Response} from 'express';
import {consoleDebug} from '../../utils/debug';
import * as constructor from '../../utils/jsonConstructor'

const logger = new consoleDebug();
export const api = Router();

api.get('/', (req: Request, res: Response) => {
    res.setHeader('Content-Type', 'application/json');
    if (req.query.name !== undefined) {
        logger.warning(req.query.name.toString())
        res.send(`Hello, ${req.query.name}!`);
    } else {
        res.send(constructor.success("Pong!!"));
    }
});