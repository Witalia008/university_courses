/**
 * Created by Witalia on 22.11.2014.
 */
function createRows() {
    var desLen = document.getElementById("num").value;
    var table = document.getElementById("inputTable");
    var tblLen = table.rows.length;

    for (var i = tblLen; i > desLen; --i) {
        table.deleteRow(i - 1);
    }

    for (var i = tblLen; i < desLen; ++i) {
        var row = table.insertRow(i);

        var inputField = document.createElement("input");
        inputField.type = "text";

        row.appendChild(inputField);
    }
}
function inArray() {
    var array = [];
    var table = document.getElementById("inputTable");

    for (var i = 0; i < table.rows.length; ++i) {
        array[i] = table.rows[i].firstChild.value;
    }

    document.getElementById("result").value = array;
}