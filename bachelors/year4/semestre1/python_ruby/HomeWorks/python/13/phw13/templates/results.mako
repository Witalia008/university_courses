<form method="post" action="/hello/search">
    <label for="srch">Search request:</label>
    <input id="srch" name="search_string" type="text" value="${query}">
    <input type="submit" value="Search">
</form>

Estimated number of results: ${estCount}<br/>
Showing: ${count}<br/>

<table>
    <tr>
        <th>Title</th>
        <th>Desctiprion</th>
        <th>Url</th>
    </tr>
% for hit in hits:
    <tr>\
        <td>${hit['title']|n}</td>\
        <td>${hit['content']|n}</td>\
        <td><a href="${hit['url']}">Link</a></td>
    </tr>\
% endfor
</table>

<a href="${moreUrl}">More results</a><br/>
<a href="/hello/index">To Index</a>