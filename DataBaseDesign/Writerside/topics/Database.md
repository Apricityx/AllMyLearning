# 数据表

### StdData

| StdID (PK) | StdName | StdInfo | StdPasswd |
|------------|---------|---------|-----------|

```SQL
CREATE TABLE StdData(
StdID INTEGER PRIMARY KEY,
StdName TEXT,
StdInfo TEXT,
StdPasswd TEXT) 
```

#### 示例插入

```SQL
INSERT INTO StdData(StdName, StdInfo, StdPasswd)
VALUES('张三', '计算机专业，擅长算法', '123456');
```

### TutorData

| TutorID (PK) | TutorName | TutorInfo | TutorPasswd |
|--------------|-----------|-----------|-------------|

```SQL
CREATE TABLE TutorData(
TutorID INTEGER PRIMARY KEY,
TutorName TEXT,
TutorInfo TEXT,
TutorPasswd TEXT)
```

### Accepted

| StdID (FK) | TutorID (FK) | AcceptTime |
|------------|--------------|------------|

#### 创建该表

```SQL
CREATE TABLE Accepted(
StdID INTEGER,
TutorID INTEGER,
PRIMARY KEY(StdID, TutorID),
FOREIGN KEY(StdID) REFERENCES StdData(StdID),
FOREIGN KEY(TutorID) REFERENCES TutorData(TutorID),
```

- StdID 引用 StdData 的 StdID
- TutorID 引用 TutorData 的 TutorID


### Application

| StdID (FK) | TutorID (FK) |
|------------|--------------|

- StdID 引用 StdData 的 StdID
- TutorID 引用 TutorData 的 TutorID

```SQL
CREATE TABLE Application(
StdID INTEGER,
TutorID INTEGER,
PRIMARY KEY(StdID, TutorID),
FOREIGN KEY(StdID) REFERENCES StdData(StdID),
FOREIGN KEY(TutorID) REFERENCES TutorData(TutorID)) 
```

### E-R图

