package conf;

import org.apache.log4j.FileAppender;
import org.apache.log4j.Logger;
import org.apache.log4j.SimpleLayout;

import java.io.IOException;

/**
 * Created by Witalia on 02.04.2015.
 */
public class ServiceConfig implements ServiceConfigMBean {
    private String logFileName;
    private Logger logger = Logger.getLogger(ServiceConfig.class);

    public ServiceConfig(String logFileName) {
        setLogFileName(logFileName);
    }

    @Override
    public String getLogFileName() {
        return logFileName;
    }

    @Override
    public void setLogFileName(String fileName) {
        this.logFileName = fileName;

        logger.removeAllAppenders();
        try {
            SimpleLayout layout = new SimpleLayout();
            FileAppender appender = new FileAppender(layout, logFileName, false);
            logger.addAppender(appender);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public Logger getLogger() {
        return logger;
    }
}
