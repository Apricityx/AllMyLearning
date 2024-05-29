import express, {Request, Response} from 'express';
import {consoleDebug} from './utils/debug';

const app = express();
const port = 3000;
const logger = new consoleDebug();
logger.warning('Server started!');
app.get('/', (req: Request, res: Response) => {
    res.setHeader('Content-Type', 'application/json');
    if (req.query.name !== undefined) {
        logger.warning(req.query.name.toString())
        res.send(`Hello, ${req.query.name}!`);
    } else {
        res.send('Hello, World!');
    }
});

app.listen(port, () => {
    console.log(`Server running at http://localhost:${port}/`);
});
