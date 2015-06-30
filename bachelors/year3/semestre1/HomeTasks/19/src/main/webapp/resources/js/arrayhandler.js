/**
 * Created by Witalia on 22.11.2014.
 */
function inArray() {
    var array = [];
    var table = document.getElementById("inputTable");

    for (var i = 0; i < table.rows.length; ++i) {
        array[i] = table.rows[i].cells[0].firstChild.value;
    }

    document.getElementById("result").value = array;
}