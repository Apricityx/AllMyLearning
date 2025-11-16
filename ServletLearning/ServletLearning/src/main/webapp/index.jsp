<%@ page import="java.text.SimpleDateFormat" %>
<%@ page import="java.util.Date" %>
<%@ page contentType="text/html; charset=UTF-8" pageEncoding="UTF-8" %>
<!DOCTYPE html>
<html>
<head>
    <title>JSP - Hello World</title>
</head>
<body>
<h1><%
    out.println("Hello World"); %>
</h1>

<p>Current Time: <%= new SimpleDateFormat("yyyy-MM-dd HH:mm:ss").format(new Date()) %></p>
<br/>
<a href="hello-servlet">Hello Servlet</a> <!-- 跳转到hello-servlet() -->
<a href="get-time">Time API</a>
</body>
</html>