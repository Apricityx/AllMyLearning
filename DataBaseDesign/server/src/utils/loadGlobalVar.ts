import {join} from "path";
import {readFileSync, writeFileSync} from "fs";

const file_dir = join(__dirname, '../serverConfig.json');
const file = readFileSync(file_dir, 'utf-8');
const file_dict = JSON.parse(file);

const Configs = {
    "database_name": "system",
    "port" : 3000,
    "db_access_key": "114514",
    ...file_dict
};
// 将配置文件写入至源文件
writeFileSync(file_dir, JSON.stringify(Configs, null, 4), 'utf-8')
export {Configs};