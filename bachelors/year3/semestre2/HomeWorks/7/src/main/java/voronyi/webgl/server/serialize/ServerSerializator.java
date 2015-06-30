package voronyi.webgl.server.serialize;

import com.google.gwt.user.client.rpc.SerializationException;
import com.google.gwt.user.server.rpc.impl.ServerSerializationStreamReader;
import com.google.gwt.user.server.rpc.impl.ServerSerializationStreamWriter;
import voronyi.webgl.shared.Serializator;

import java.io.Serializable;

/**
 * Created by: witalia
 * Project name: hw7
 * Date: 15.12.14
 * Time: 9:23
 * All rights reserved.
 */
public class ServerSerializator implements Serializator {
    @Override
    public String serialize(Serializable message) {
        String data = null;
        ServerSerializationStreamWriter writer =
                new ServerSerializationStreamWriter(new SimpleSerializationPolicy());
        try {
            writer.writeObject(message);
            data = writer.toString();
        } catch (SerializationException e) {
            e.printStackTrace();
        }
        return data;
    }

    @Override
    public Serializable deserialize(String data) {
        Serializable message = null;
        ServerSerializationStreamReader reader =
                new ServerSerializationStreamReader(
                        Thread.currentThread().getContextClassLoader(),
                        new CustomSerializationPolicyProvider()
                );
        try {
            reader.prepareToRead(data);
            message = (Serializable) reader.readObject();
        } catch (SerializationException e) {
            e.printStackTrace();
        }
        return message;
    }
}
