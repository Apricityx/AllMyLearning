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

![E-R.png](E-R.png)