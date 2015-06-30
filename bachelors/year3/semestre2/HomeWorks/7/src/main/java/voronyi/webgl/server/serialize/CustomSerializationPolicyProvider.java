package voronyi.webgl.server.serialize;

import com.google.gwt.user.server.rpc.SerializationPolicy;
import com.google.gwt.user.server.rpc.SerializationPolicyProvider;

/**
 * Created by: witalia
 * Project name: hw7
 * Date: 15.12.14
 * Time: 9:30
 * All rights reserved.
 */
public class CustomSerializationPolicyProvider implements SerializationPolicyProvider {
    @Override
    public SerializationPolicy getSerializationPolicy(String s, String s1) {
        return new SimpleSerializationPolicy();
    }
}
