# API接口调用方法

## 可用API概览

```Bash
    v1
    ├── dangerous
    │   └── reset_database
    ├── get_access_token
    ├── ping
    └── auth
        └── authentication_test
```

## 普通接口

### 此类接口不涉及危险操作

<deflist collapsible="true">
    <def title="测试接口" default-state="collapsed">
        <list>
            <li>用途：请求该端口获取服务可用状态</li>
            <li>请求方式: GET</li>
            <li>请求参数: 无</li>
            <li>请求地址: v1/ping</li>
            <li>返回示例:</li>
        </list>
        <code-block lang="JSON">
        {
          &quot;message&quot;: &quot;pong&quot;,
          &quot;status&quot;: &quot;success&quot;
        }
        </code-block>
    </def>
</deflist>

<deflist collapsible="true">
    <def title="获取AccessToken接口" default-state="collapsed">
        <list>
            <li>用途：用户登录的时候，若密码正确，则根据时间戳生成一个AccessToken，返回给用户，用户在之后的请求中应当携带这个AccessToken，以便服务器验证用户身份</li>
            <li>请求方式: POST</li>
            <li>请求参数: type</li>
            <li>请求地址: v1/get_access_token</li>
            <li>返回示例:</li>
        </list>
        <code-block lang="JSON">
        {
          &quot;status&quot;: &quot;success&quot;,
          &quot;message&quot;: &quot;Access Token has been generated!&quot;,
          &quot;accessToken&quot;: &quot;eyJhbG....&quot;
        }
        </code-block>
        <p>可用的type有&quot;Std&quot;和&quot;Tutor&quot;</p>
        <list>
            <li>返回示例:</li>
        </list>
        <code-block lang="JSON">
        {
          &quot;status&quot;: &quot;success&quot;,
          &quot;message&quot;: &quot;Access Token has been generated!&quot;,
          &quot;accessToken&quot;: &quot;eyJhbG....&quot;
        } 
</code-block>
        <p>用户登录的时候，若密码正确，则根据时间戳生成一个AccessToken，返回给用户，用户在之后的请求中应当携带这个AccessToken，以便服务器验证用户身份</p>
    </def>
</deflist>

## 鉴权接口

下列的接口返回的数据涉及到个人信息，都需要进行鉴权才能获取数据，位于v1/auth路由下，所有的请求都需要包含accessToken：

```JSON
{
  "accessToken": ".....=="
}
```

<deflist collapsible="true">
    <def title="鉴权测试接口" default-state="collapsed">
        <list>
            <li>用途：测试用户的身份，返回用户的身份信息</li>
            <li>请求方式: POST</li>
            <li>请求地址: v1/auth/authentication_test</li>
            <li>请求示例</li>
        </list>
        <code-block lang="JSON">
        {
          &quot;accessToken&quot;: &quot;.....==&quot;
        }
        </code-block>
        <list>
            <li>返回示例:</li>
        </list>
        <code-block lang="JSON">
        {
          &quot;status&quot;: &quot;success&quot;,
          &quot;message&quot;: &quot;Authentication Success&quot;,
          &quot;bool&quot;: true,
          &quot;userType&quot;: &quot;Tutor&quot;
        }
        </code-block>
    </def>
</deflist>

##### 获取导师/学生信息接口 {collapsible="true"}
该接口会被两个页面调用，分别为导师页面与学生页面，返回的数据不同
导师页面

- 导师本人的个人信息
- Application表的学生申请
- Accepted表，已被接受的学生

学生页面

- 学生本人的个人信息
- Application表，已发出的申请
- Accepted表，已被接受的申请


- 请求方式: POST
- 请求参数: accessToken
- 请求地址: v1/auth/get_info
- 请求示例:

导师请求

```JSON
{
  "accessToken": ".....=="
}
```

学生请求

```JSON
{
  "accessToken": ".....=="
}
```

- 返回示例:

导师返回

```JSON
{
  "status": "success",
  "message": "Tutor Get Info Successfully",
  "stdRequests": [
    {
      "id": 1,
      "stdId": 1,
      "status": "pending | accepted | rejected",
      "stdInfo": {
        "name": "张三",
        "email": "123@456.com",
        "phone": "12345678901",
        "introduction": "我是张三"
      }
    },
    {
      "id": 2,
      "stdId": 2,
      "status": "pending | accepted | rejected",
      "stdInfo": {
        "name": "李四",
        "email": "321@654.com",
        "phone": "98765432101",
        "introduction": "我是李四"
      }
    }
  ],
  "selfInfo": {
    "tutorId": 100001,
    "name": "张三",
    "email": "123@456.com",
    "phone": "12345678901",
    "introduction": "我是张三"
  }
}
```

学生返回

```JSON
{
  "status": "success",
  "message": "Authentication Success",
  "tutor": "王导 | unset",
  "tutors": [
    {
      "name": "张导",
      "email": "123@456.com",
      "phone": "12345678901",
      "introduction": "我是张导",
      "requestStatus": "pending | accepted | rejected"
    }
  ],
  "selfInfo": {
    "name": "李四",
    "email": "4321@1234.com",
    "phone": "98765432101",
    "introduction": "我是李四"
  }
}
```

## 危险操作

<warning>下列的接口都是危险操作，位于v1/dangerous路由下，请谨慎使用
</warning>

<deflist collapsible="true">
    <def title="初始化数据库" default-state="collapsed">
        <list>
            <li>用途：初始化数据库</li>
            <li>请求方式: GET</li>
            <li>请求参数: key</li>
            <li>请求地址: v1/dangerous/reset_database?key=123456}</li>
            <li>返回示例:</li>
        </list>
        <code-block lang="JSON">
        {
          &quot;message&quot;: &quot;Database has been reset!&quot;,
          &quot;status&quot;: &quot;success&quot;
        }
        </code-block>
    </def>
</deflist>

## 非正式接口

### 下列的接口都是非正式接口，不接受GET/POST请求，仅在后端开发中使用，仅作备忘

<deflist collapsible="true">
    <def title="检查用户身份" default-state="collapsed">
        <list>
            <li>用途：检查用户的身份，返回用户的身份信息</li>
            <li>请求方式: String</li>
            <li>引入方式：</li>
        </list>
        <code-block lang="Typescript">
        import {CheckAuthentication} from "@/utils/authentication"; 
        </code-block>
        <list>
            <li>请求示例</li>
        </list>
        <code-block lang="Typescript">
        const userInfo = "...==" // Base64字符串
        const result = CheckAuthentication(userInfo) 
        </code-block>
        <list>
            <li>返回示例</li>
        </list>
        <code-block lang="JSON">
        {
          "status": "success",
          "message": "Authentication Success",
          "bool": true,
          "userType": "Tutor"
        }
        </code-block>
    </def>
</deflist>