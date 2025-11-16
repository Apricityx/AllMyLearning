import {Router} from "express";
import * as fs from "node:fs";


const data = fs.readFileSync('src/data/news.json', 'utf-8');
export const api = Router();
api.get('/', (req, res) => {
    setTimeout(() => {
        res.send({result: true});
    }, 1000)
})