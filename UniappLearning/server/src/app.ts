import express, {Request, Response} from 'express';
import {api as v1GetNews} from '@/api/v1/get_news';
import {logger} from '@/utils/debug';

const app = express();
const port = 3000;
app.listen(port, () => {
    logger.success(`=============================================`);
    logger.success(`||Server running at http://localhost:${port}/ ||`);
    logger.success(`=============================================`);
});
app.use((req, res, next) => {
    res.setHeader('Access-Control-Allow-Origin', '*'); // 允许来自所有源的请求
    res.setHeader('Access-Control-Allow-Methods', 'GET, POST, PUT, DELETE');
    res.setHeader('Access-Control-Allow-Headers', 'Content-Type, Authorization');
    next();
});
app.use("/api/v1/get_news", v1GetNews);
