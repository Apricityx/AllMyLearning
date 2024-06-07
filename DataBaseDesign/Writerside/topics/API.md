# API接口调用方法

```Bash
    v1
    ├── dangerous
    │   ├── reset_database?key={KEY}
    │   └── vue.config.js
    └── ping
```

## 普通接口

### 此类接口不涉及危险操作

##### 测试接口 {collapsible="true"}

- 请求方式: GET
- 请求参数: 无
- 请求地址: v1/ping
- 返回示例:

```JSON
{
  "message": "pong",
  "status": "success"
}
```

##### 获取AccessToken接口 {collapsible="true"}

- 请求方式: POST
- 请求参数: 无
- 请求地址: v1/get_access_token
- 请求示例

```JSON
{
  "name": "222023321062100",
  "password": "062100",
  "type": "Std"
}
```

可用的type有"Std"和"Tutor"

- 返回示例:

```JSON
{
  "status": "success",
  "message": "Access Token has been generated!",
  "accessToken": "eyJhbG...."
} 
```

用户登录的时候，若密码正确，则根据时间戳生成一个AccessToken，返回给用户，用户在之后的请求中应当携带这个AccessToken，以便服务器验证用户身份

## 危险操作

### 下列的接口都是危险操作，请谨慎使用

##### 初始化数据库 {collapsible="true"}

- 请求方式: GET
- 请求参数: key
- 请求地址: v1/dangerous/reset_database?key={key}}
- 返回示例:

```JSON
{
  "message": "Database has been reset!",
  "status": "success"
}
```