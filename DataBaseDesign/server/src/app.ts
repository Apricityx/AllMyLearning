import {Configs} from './utils/loadGlobalVar';
import {readFileSync} from 'fs';
import {join} from 'path';
import express, {Request, Response} from 'express';
import {consoleDebug} from './utils/debug';
import {api as v1DangerousResetDatabase} from "./api/v1/dangerous/resetDatabase";
import {api as v1Ping} from "./api/v1/ping";
import {api as v1SubmitApplication} from "./api/v1/submit_application";
import {api as v1GetAccessToken} from "./api/v1/get_access_token";
import {api as v1AuthenticationTest} from "./api/v1/auth/authentication_test";

// 加载全局配置
const file_dir = join(__dirname, './serverConfig.json');
const file = readFileSync(file_dir, 'utf-8');
const file_dict = JSON.parse(file);

// 基本信息初始化
const app = express();
const port = Configs.port;
const logger = new consoleDebug();
logger.warning('Server started!');

// 路由
app.use('/api/v1/dangerous/reset_database', v1DangerousResetDatabase);
app.use('/api/v1/ping', v1Ping);
app.use('/', v1Ping);
app.use('/api/v1/submit_application', v1SubmitApplication);
app.use('/api/v1/get_access_token', v1GetAccessToken);
app.use('/api/v1/auth/authentication_test', v1AuthenticationTest);
app.listen(port, () => {
    logger.success(`=============================================`);
    logger.success(`||Server running at http://localhost:${port}/ ||`);
    logger.success(`=============================================`);
});