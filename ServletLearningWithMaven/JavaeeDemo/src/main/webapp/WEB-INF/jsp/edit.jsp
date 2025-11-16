<%@ page contentType="text/html;charset=UTF-8" %>
<%@ taglib prefix="c" uri="http://java.sun.com/jsp/jstl/core" %>
<html>
<head><title>编辑奶茶</title></head>
<body>
<h2>编辑奶茶</h2>
<form action="${pageContext.request.contextPath}/milktea/update" method="post">
    <input type="hidden" name="id" value="${milkTea.id}"/>
    奶茶名称: <input type="text" name="name" value="${milkTea.name}"/><br/>
    价格: <input type="text" name="price" value="${milkTea.price}"/><br/>
    <input type="submit" value="保存"/>
</form>
</body>
</html>
