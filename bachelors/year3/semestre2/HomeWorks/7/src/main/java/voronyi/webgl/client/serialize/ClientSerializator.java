package voronyi.webgl.client.serialize;

import com.google.gwt.core.client.GWT;
import com.google.gwt.user.client.rpc.SerializationException;
import com.google.gwt.user.client.rpc.SerializationStreamFactory;
import com.google.gwt.user.client.rpc.SerializationStreamReader;
import com.google.gwt.user.client.rpc.SerializationStreamWriter;
import voronyi.webgl.client.MessageService;
import voronyi.webgl.shared.Serializator;

import java.io.ObjectInputStream;
import java.io.Serializable;

/**
 * Created by: witalia
 * Project name: hw7
 * Date: 15.12.14
 * Time: 9:13
 * All rights reserved.
 */
public class ClientSerializator implements Serializator {

    @Override
    public String serialize(Serializable message) {
        String data = null;
        try {
            SerializationStreamFactory factory = GWT.create(MessageService.class);
            SerializationStreamWriter writer = factory.createStreamWriter();
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
        try {
            SerializationStreamFactory factory = GWT.create(MessageService.class);
            SerializationStreamReader reader = factory.createStreamReader(data);
            message = (Serializable) reader.readObject();
        } catch (SerializationException e) {
            e.printStackTrace();
        }
        return message;
    }
}
