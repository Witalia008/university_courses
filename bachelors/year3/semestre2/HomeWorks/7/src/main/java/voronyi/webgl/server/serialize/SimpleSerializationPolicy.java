package voronyi.webgl.server.serialize;

import com.google.gwt.user.client.rpc.IsSerializable;
import com.google.gwt.user.client.rpc.SerializationException;
import com.google.gwt.user.server.rpc.SerializationPolicy;

import java.io.Serializable;

/**
 * Created by: witalia
 * Project name: hw7
 * Date: 15.12.14
 * Time: 9:36
 * All rights reserved.
 */
public class SimpleSerializationPolicy extends SerializationPolicy {
    @Override
    public boolean shouldDeserializeFields(Class<?> aClass) {
        return isSerializable(aClass);
    }

    @Override
    public boolean shouldSerializeFields(Class<?> aClass) {
        return isSerializable(aClass);
    }

    @Override
    public void validateDeserialize(Class<?> aClass) throws SerializationException {

    }

    @Override
    public void validateSerialize(Class<?> aClass) throws SerializationException {

    }

    private boolean isSerializable(Class<?> aClass) {
        if (aClass != null) {
            if (aClass.isPrimitive()
                    || Serializable.class.isAssignableFrom(aClass)
                    || IsSerializable.class.isAssignableFrom(aClass)) {
                return true;
            }
        }
        return false;
    }
}
