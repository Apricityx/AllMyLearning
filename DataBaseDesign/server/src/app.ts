import express, {Request, Response} from 'express';
import {consoleDebug} from './utils/debug';
import {api as v1DangerousResetDatabase} from "./api/v1/dangerous/resetDatabase";
import {api as v1Ping} from "./api/v1/ping";

const app = express();
const port = 3000;
const logger = new consoleDebug();
logger.warning('Server started!');

// 路由
app.use('/v1/dangerous/reset_database', v1DangerousResetDatabase);
app.use('/v1/ping', v1Ping);
app.listen(port, () => {
    logger.success(`=============================================`);
    logger.success(`||Server running at http://localhost:${port}/ ||`);
    logger.success(`=============================================`);
});
