<?xml version="1.0" encoding="UTF-8"?>

<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
    <html>
        <head>
            <title>Gems fund</title>
        </head>
        <body>
            <table border="2">
                <tr>
                    <th>ID</th>
                    <th>Name</th>
                    <th>Preciousness</th>
                    <th>Origin</th>
                    <th>Appearence</th>
                    <th>Weight</th>
                </tr>
                <xsl:for-each select="Gems/gem">
                    <tr>
                        <td><xsl:value-of select="@id"/></td>
                        <td><xsl:value-of select="name"/></td>
                        <td><xsl:value-of select="preciousness"/></td>
                        <td><xsl:value-of select="origin"/></td>
                        <td>
                            <table border="1">
                                <tr>
                                    <td>Color</td>
                                    <td>Transparency</td>
                                    <td>Engraving</td>
                                </tr>
                                <tr>
                                    <td><xsl:value-of select="visualParameters/color"/></td>
                                    <td><xsl:value-of select="visualParameters/transparency"/></td>
                                    <td>
                                        <table>
                                            <tr>
                                                <td>Type</td>
                                                <td>Number of sides</td>
                                            </tr>
                                            <tr>
                                                <td><xsl:value-of select="visualParameters/engraving/type"/></td>
                                                <td><xsl:value-of select="visualParameters/engraving/numberOfSides"/></td>
                                            </tr>
                                        </table>
                                    </td>
                                </tr>
                            </table>
                        </td>
                        <td><xsl:value-of select="value"/></td>
                    </tr>
                </xsl:for-each>
            </table>
        </body>
    </html>


</xsl:template>

</xsl:stylesheet>
