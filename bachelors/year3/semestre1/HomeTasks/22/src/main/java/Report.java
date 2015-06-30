import net.sf.jasperreports.engine.*;
import net.sf.jasperreports.engine.export.JRXlsExporter;

/**
 * Created by Witalia on 26.10.2014.
 */
public class Report {
    private static final String dataDir = "target\\classes\\data";
    private JasperReport jasperReport = null;

    JasperReport getJasperReport() {
        return jasperReport;
    }

    JasperPrint getJasperPrint() {
        return jasperPrint;
    }

    private JasperPrint jasperPrint = null;

    public Report() {
        try {
            jasperReport = JasperCompileManager.compileReport(
                    dataDir + "\\ReportTemplate\\FileReadReport.jrxml");
        } catch (JRException e) {
            e.printStackTrace();
        }
    }
    public void print(Database database) {
        try {
            jasperPrint = JasperFillManager.fillReport(
                    jasperReport,
                    null,
                    database.getConnection()
            );
        } catch (JRException e) {
            e.printStackTrace();
        }
    }
    public void exportToPdf() {
        if (jasperPrint == null) {
            return;
        }
        try {
            JasperExportManager.exportReportToPdfFile(jasperPrint, dataDir + "\\report.pdf");
        } catch (JRException e) {
            e.printStackTrace();
        }
    }
    public void exportToExcel() {
        if (jasperPrint == null) {
            return;
        }
        JRXlsExporter exporter = new JRXlsExporter();
        exporter.setParameter(JRExporterParameter.JASPER_PRINT,
                jasperPrint);
        exporter.setParameter(JRExporterParameter.OUTPUT_FILE_NAME,
                dataDir + "\\report.xls");
        try {
            exporter.exportReport();
        } catch (JRException e) {
            e.printStackTrace();
        }
    }
}
