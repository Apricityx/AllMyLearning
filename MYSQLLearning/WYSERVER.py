import pymysql
import cryptography

db = pymysql.connect(host="pve.zwtsvx.xyz", port=1128, user="root", passwd="20050125@Wy")
cursor = db.cursor()
cursor.execute("use autoemail")
