package asp;

import conf.ServiceConfig;
import org.aspectj.lang.ProceedingJoinPoint;
import org.aspectj.lang.annotation.Around;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Pointcut;
import org.aspectj.lang.reflect.MethodSignature;

import javax.management.*;
import java.lang.management.ManagementFactory;
import java.util.Arrays;

/**
 * Created by Witalia on 01.04.2015.
 */
@Aspect
public class LoggingAspect {
    private static final ServiceConfig config;

    static {
        config = new ServiceConfig("default.log");
        try {
            MBeanServer mBeanServer = ManagementFactory.getPlatformMBeanServer();
            ObjectName objectName = new ObjectName("conf:type=ServiceConfig");
            mBeanServer.registerMBean(config, objectName);
        } catch (MalformedObjectNameException | NotCompliantMBeanException
                | MBeanRegistrationException | InstanceAlreadyExistsException e) {
            e.printStackTrace();
        }

    }

    @Pointcut("execution(@asp.LoggableMethod * *(..))")
    public void logging() {}

    @Around("logging()")
    public Object logging(ProceedingJoinPoint thisJointPoint) throws Throwable {

        long start = System.currentTimeMillis();
        Object ret = thisJointPoint.proceed();
        System.out.println("To file " + config.getLogFileName());
        config.getLogger().info(String.format(
                "#%s(%s): %s in %d ms",
                ((MethodSignature) thisJointPoint.getSignature()).getMethod().getName(),
                Arrays.toString(thisJointPoint.getArgs()),
                ret,
                System.currentTimeMillis() - start
        ));

        return ret;
    }
}
