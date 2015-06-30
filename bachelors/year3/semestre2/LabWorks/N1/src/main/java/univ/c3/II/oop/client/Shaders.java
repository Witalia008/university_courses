package univ.c3.II.oop.client;

import com.google.gwt.core.client.GWT;
import com.google.gwt.resources.client.ClientBundle;
import com.google.gwt.resources.client.TextResource;

/**
 * Created by witalia on 13.12.14.
 */
public interface Shaders extends ClientBundle {
    public static Shaders INSTANCE = GWT.create(Shaders.class);

    @Source(value = "shaders/fragment-shader.glsl")
    TextResource fragmentShader();

    @Source(value = "shaders/vertex-shader.glsl")
    TextResource vertexShader();
}
