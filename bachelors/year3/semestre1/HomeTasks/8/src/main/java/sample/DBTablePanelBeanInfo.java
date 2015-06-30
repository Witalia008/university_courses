package sample;

import java.beans.*;

/**
 * Created by Witalia on 01.12.2014.
 */
public class DBTablePanelBeanInfo extends SimpleBeanInfo {
    private static final int DEFAULT_PROPERTY_INDEX = -1;
    private static final int DEFAULT_EVENT_INDEX = -1;

    private static final int PROPERTIES_AVAILABLE = 5;

    private static final String[] properties = {
            "driverName",
            "serviceURI",
            "username",
            "password",
            "tableName"
    };
    private static final String[] setters = {
            "setDriverName",
            "setServiceURI",
            "setUsername",
            "setPassword",
            "setTableName"
    };

    private static final String[] getters = {
        null, null, null, null, null
    };

    @Override
    public BeanDescriptor getBeanDescriptor() {
        BeanDescriptor descriptor = new BeanDescriptor(
                DBTablePanel.class, null
        );
        return descriptor;
    }

    @Override
    public PropertyDescriptor[] getPropertyDescriptors() {
        PropertyDescriptor[] propertyDescriptors
                = new PropertyDescriptor[PROPERTIES_AVAILABLE];
        for (int i = 0; i < propertyDescriptors.length; i++) {
            try {
                propertyDescriptors[i] = new PropertyDescriptor(
                        properties[i], DBTablePanel.class,
                        getters[i], setters[i]
                );
            } catch (IntrospectionException e) {
                e.printStackTrace();
            }
        }
        return propertyDescriptors;
    }

    @Override
    public EventSetDescriptor[] getEventSetDescriptors() {
        EventSetDescriptor[] setDescriptors = new EventSetDescriptor[0];
        return setDescriptors;
    }

    @Override
    public MethodDescriptor[] getMethodDescriptors() {
        MethodDescriptor[] methodDescriptors = new MethodDescriptor[0];
        return methodDescriptors;
    }

    @Override
    public int getDefaultPropertyIndex() {
        return DEFAULT_PROPERTY_INDEX;
    }

    @Override
    public int getDefaultEventIndex() {
        return DEFAULT_EVENT_INDEX;
    }
}
