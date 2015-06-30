<html>
    <head>
        <title>My storage | Sign In/Up</title>
    </head>
    <body>
        <%
            if (request.getSession().getAttribute("username") != null) {
                response.sendRedirect("/5/storage.jsp");
            }
        %>
        <script>
            function checkFields() {
                var name = document.forms["signform"]["username"].value;
                var pass = document.forms["signform"]["password"].value;
                if (name == null || name == "") {
                    alert("Please specify username");
                    return false;
                }
                if (pass == null || pass == "") {
                    alert("Please enter password");
                    return false;
                }
                return true;
            }
        </script>
        <form name="signform" action="/5/signinup" method="post"
              onsubmit="return checkFields()">
            Username:<br/>
            <input type="text" name="username"/><br/>
            Password:<br/>
            <input type="password" name="password"><br/>
            <input type="checkbox" name="register"/>New User?<br/>
            <input type="submit" value="Sign In/Up"/>
        </form>
    </body>
</html>
