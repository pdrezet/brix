<xsl:stylesheet version="1.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
<xsl:template match="/"><table>
<h2>Summary</h2>
  <tr>
   <td>Total Tests</td>
   <td><xsl:value-of select="TestRun/Statistics/Tests"/></td>
  </tr>
  <tr>
   <td>Failures Total</td>
   <td><xsl:value-of select="TestRun/Statistics/FailuresTotal"/></td>
  </tr>
  <tr>
   <td>Errors</td>
   <td><xsl:value-of select="TestRun/Statistics/Errors"/></td>
  </tr>
  <tr>
   <td>Failures</td>
   <td><xsl:value-of select="TestRun/Statistics/Failures"/></td>
  </tr>
 </table>
<h2>Detail</h2>
 <table>
  <tr>
   <th>Test Id</th>
   <th>Test Name</th>
   <th>Pass?</th>
  </tr>
  <xsl:for-each select="TestRun//Test">
  <xsl:sort select="@id" data-type="number"/>
   <tr>
   <td><xsl:value-of select="@id"/></td>
   <td><xsl:value-of select="Name"/></td>
   <td>
    <xsl:if test="parent::FailedTests">N</xsl:if>
    <xsl:if test="parent::SuccessfulTests">Y</xsl:if>
   </td>
   </tr>
  </xsl:for-each>
 </table>
 </xsl:template>
</xsl:stylesheet>