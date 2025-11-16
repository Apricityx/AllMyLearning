<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head><title>奶茶菜单</title></head>
<body>
<h2>奶茶菜单</h2>
<a href="jsp/add.jsp">新增奶茶</a>
<table border="1">
    <tr><th>ID</th><th>名称</th><th>价格</th><th>操作</th></tr>
    <c:forEach var="m" items="${milkTeas}">
        <tr>
            <td>${m.id}</td>
            <td>${m.name}</td>
            <td>${m.price}</td>
            <td>
                <a href="milktea/edit?id=${m.id}">修改</a>
                <a href="milktea/delete?id=${m.id}">删除</a>
            </td>
        </tr>
    </c:forEach>
</table>
</body>
</html>
