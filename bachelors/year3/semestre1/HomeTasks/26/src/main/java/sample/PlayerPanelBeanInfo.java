package sample;

import java.beans.*;

/**
 * Created by Witalia on 28.11.2014.
 */
public class PlayerPanelBeanInfo extends SimpleBeanInfo {
    private static final int DEFAULT_PROPERTY_INDEX = -1;
    private static final int DEFAULT_EVENT_INDEX = -1;

    @Override
    public BeanDescriptor getBeanDescriptor() {
        BeanDescriptor beanDescriptor = new BeanDescriptor(
                PlayerPanel.class, null
        );
        return beanDescriptor;
    }

    @Override
    public PropertyDescriptor[] getPropertyDescriptors() {
        PropertyDescriptor[] propertyDescriptors = new PropertyDescriptor[1];

        try {
            propertyDescriptors[0] = new PropertyDescriptor(
                    "mediaURL",
                    PlayerPanel.class, null,
                    "setMediaURL"
            );
        } catch (IntrospectionException e) {
            e.printStackTrace();
        }
        return propertyDescriptors;
    }

    @Override
    public EventSetDescriptor[] getEventSetDescriptors() {
        EventSetDescriptor[] eventSetDescriptors = new EventSetDescriptor[0];
        return eventSetDescriptors;
    }

    @Override
    public MethodDescriptor[] getMethodDescriptors() {
        MethodDescriptor[] methodDescriptors = new MethodDescriptor[0];
        return methodDescriptors;
    }

    @Override
    public int getDefaultEventIndex() {
        return DEFAULT_EVENT_INDEX;
    }

    @Override
    public int getDefaultPropertyIndex() {
        return DEFAULT_PROPERTY_INDEX;
    }
}
