<%@ page contentType="text/html;charset=UTF-8" %>
<html>
<head><title>新增奶茶</title></head>
<body>
<h2>新增奶茶</h2>
<form action="${pageContext.request.contextPath}/milktea/add" method="post">
    奶茶名称: <input type="text" name="name"/><br/>
    价格: <input type="text" name="price"/><br/>
    <input type="submit" value="添加"/>
</form>
</body>
</html>
