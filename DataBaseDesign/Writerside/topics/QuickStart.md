# 快速上手

#### 目录结构

```Bash
    DataBaseDesign
    ├── Vue
    │   ├── public
    │   ├── src
    │   │   ├── assets
    │   │   ├── components
    │   │   ├── router
    │   │   ├── store
    │   │   ├── views
    │   │   ├── App.vue
    │   │   └── main.js
    │   ├── .browserslistrc
    │   ├── .eslintrc.js
    │   ├── babel.config.js
    │   ├── package.json
    │   └── vue.config.js
    ├── server
    │   ├── config
    │   ├── controller
    │   ├── middleware
    │   ├── model
    │   ├── public
    │   ├── routes
    │   ├── app.js
    │   ├── package.json
    │   └── server.js
    ├── .gitignore
    ├── README.md
    └── package.json
```

此项目采用yarn作为包管理工具，若未安装yarn，请先安装yarn
理论上也可以用npm作相关操作

#### 安装服务端

```Bash
    yarn install
```

#### 启动服务端

在server目录下执行

```Bash
    yarn dev
```