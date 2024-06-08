import {join} from "path";
import {readFileSync, writeFileSync} from "fs";
import fs from "node:fs";
import path from "node:path";
import {consoleDebug} from "./debug";

const logger = new consoleDebug();
const file_dir = join(__dirname, '../serverConfig.json');
const file = readFileSync(file_dir, 'utf-8');
const file_dict = JSON.parse(file);

const Configs = {
    "database_name": "system",
    "port": 3000,
    "db_access_key": "114514",
    ...file_dict
};
// 将配置文件写入至源文件
writeFileSync(file_dir, JSON.stringify(Configs, null, 4), 'utf-8')
// 将公钥私钥需写入Configs
let privateKey = '';
let publicKey = '';
try {
    if (fs.existsSync(path.resolve(__dirname, "../keys/private.pem"))) {
        logger.debug("Private Key Loaded")
        privateKey = fs.readFileSync(path.resolve(__dirname, "../keys/private.pem"), 'utf-8');
    } else {
        logger.error("Private Key File Not Found")
    }
    if (fs.existsSync(path.resolve(__dirname, "../keys/public.pem"))) {
        logger.debug("Public Key Loaded")
        publicKey = fs.readFileSync(path.resolve(__dirname, "../keys/public.pem"), 'utf-8');
    } else {
        logger.error("Public Key File Not Found")
    }
} catch (e) {
    logger.error("Key File Read Error")
}

Configs["privateKey"] = privateKey;
Configs["publicKey"] = publicKey;
export {Configs};