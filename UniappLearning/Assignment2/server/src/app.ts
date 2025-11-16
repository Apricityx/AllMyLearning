import express, {Request, Response} from 'express';
import {api as v1Valid} from '@/api/v1/valid';
import {api as v1CheckAuth} from '@/api/v1/auth/check_auth';
import {api as v1GetAccessToken} from '@/api/v1/getAccessToken'
import {api as v1Register} from '@/api/v1/register'
import {logger} from '@/utils/debug';
import bodyParser from "body-parser";

const app = express();
const port = 3000;
app.use((req, res, next) => {
    res.setHeader('Access-Control-Allow-Origin', '*'); // 允许来自所有源的请求
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE');
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type, Authorization');
    // JSON
    res.setHeader('Content-Type', 'application/json');
    next();
});
app.listen(port, () => {
    logger.success(`=============================================`);
    logger.success(`||Server running at http://localhost:${port}/ ||`);
    logger.success(`=============================================`);
});

app.use("/api/v1/valid", v1Valid);
app.use("/api/v1/get_access_token", v1GetAccessToken);
app.use("/api/v1/register", v1Register)