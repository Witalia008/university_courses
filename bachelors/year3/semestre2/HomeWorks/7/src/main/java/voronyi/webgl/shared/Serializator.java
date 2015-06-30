package voronyi.webgl.shared;

import java.io.Serializable;

/**
 * Created by: witalia
 * Project name: hw7
 * Date: 15.12.14
 * Time: 9:24
 * All rights reserved.
 */
public interface Serializator {
    String serialize(Serializable message);
    Serializable deserialize(String data);
}
