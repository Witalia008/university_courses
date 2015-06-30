package univ.c3.II.oop.client;

import com.google.gwt.canvas.client.Canvas;
import com.google.gwt.user.client.Window;
import com.google.gwt.user.client.ui.*;
import com.google.gwt.core.client.EntryPoint;
import com.google.gwt.event.dom.client.ClickEvent;
import com.google.gwt.event.dom.client.ClickHandler;
import com.googlecode.gwtgl.array.Float32Array;
import com.googlecode.gwtgl.binding.*;
import net.zschech.gwt.websockets.client.MessageEvent;
import net.zschech.gwt.websockets.client.MessageHandler;
import net.zschech.gwt.websockets.client.WebSocket;

import java.util.Arrays;

/**
 * Entry point classes define <code>onModuleLoad()</code>.
 */
public class N1 implements EntryPoint {
    private static final String URL = "ws://" + Window.Location.getHost() + "/N1/geosvc";

    private WebGLRenderingContext glContext;
    private WebGLProgram shaderProgram;
    private int vertexPositionAttribute;
    private WebGLBuffer vertexBuffer;

    private HorizontalPanel inputPanel = new HorizontalPanel();
    private TextBox inputSpeed = new TextBox();
    private Button sendDataBtn = new Button("Draw");
    private WebSocket webSocket = WebSocket.create(URL);

    private static final int WIDTH = 1000;
    private static final int HEIGHT = 700;
    private float[] buffer;

    /**
     * This is the entry point method.
     */
    public void onModuleLoad() {
        inputPanel.add(inputSpeed);
        inputPanel.add(sendDataBtn);
        sendDataBtn.addClickHandler(new ClickHandler() {
            @Override
            public void onClick(ClickEvent clickEvent) {
                webSocket.send(inputSpeed.getText());
            }
        });

        webSocket.setOnMessage(new MessageHandler() {
            @Override
            public void onMessage(WebSocket webSocket, MessageEvent messageEvent) {
                String[] arr = messageEvent.getData().split(",");
                Window.alert(Arrays.toString(arr));
                buffer = new float[arr.length];
                for (int i = 0; i < buffer.length; i++) {
                    buffer[i] = Float.parseFloat(arr[i]);
                }

                setBufferData(buffer);
                drawScene();
            }
        });

        RootPanel.get("gwtGL").add(inputPanel);

        // WebGL Elements
        final Canvas webGLCanvas = Canvas.createIfSupported();
        webGLCanvas.setCoordinateSpaceHeight(HEIGHT);
        webGLCanvas.setCoordinateSpaceWidth(WIDTH);
        glContext = (WebGLRenderingContext) webGLCanvas.getContext("experimental-webgl");
        if (glContext == null) {
            Window.alert("WebGL not supported!");
            return;
        }
        glContext.viewport(0, 0, WIDTH, HEIGHT);

        RootPanel.get("gwtGL").add(webGLCanvas);

        start();
    }

    private void start() {
        initShaders();
        glContext.clearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glContext.clearDepth(1.0f);
        glContext.enable(WebGLRenderingContext.DEPTH_TEST);
        glContext.depthFunc(WebGLRenderingContext.LEQUAL);
        initBuffers();
    }

    private void drawScene() {
        glContext.clear(WebGLRenderingContext.COLOR_BUFFER_BIT
                | WebGLRenderingContext.DEPTH_BUFFER_BIT);
        float[] perspectiveMatrix = createPerspectiveMatrix(45, 1, 0.1f, 1000);

        WebGLUniformLocation uniformLocation = glContext
                .getUniformLocation(shaderProgram, "perspectiveMatrix");
        glContext.uniformMatrix4fv(uniformLocation, false, perspectiveMatrix);
        glContext.vertexAttribPointer(vertexPositionAttribute,
                3, WebGLRenderingContext.FLOAT, false, 0, 0);
        glContext.drawArrays(WebGLRenderingContext.LINE_STRIP, 0, buffer.length / 3);
    }

    private float[] createPerspectiveMatrix(int fieldOfViewVertical, float aspectRatio,
                                            float minimumClearance, float maximumClearance) {
        float top = (float) (minimumClearance * Math.tan(fieldOfViewVertical * Math.PI / 180));
        float bottom = -top;
        float left = bottom * aspectRatio;
        float right = top * aspectRatio;

        float X = 2 * minimumClearance / (right - left);
        float Y = 2 * minimumClearance / (top - bottom);
        float A = (right + left) / (right - left);
        float B = (top + bottom) / (top - bottom);
        float C = -(maximumClearance + minimumClearance) / (maximumClearance - minimumClearance);
        float D = -2 * maximumClearance * minimumClearance / (maximumClearance - minimumClearance);

        return new float[]{
                X, 0.0f, A, 0.0f,
                0.0f, Y, B, 0.0f,
                0.0f, 0.0f, C, -1.0f,
                0.0f, 0.0f, D, 0.0f
        };
    }

    private void initBuffers() {
        vertexBuffer = glContext.createBuffer();
        glContext.bindBuffer(WebGLRenderingContext.ARRAY_BUFFER, vertexBuffer);
    }

    private void setBufferData(float[] vertices) {
        glContext.bufferData(WebGLRenderingContext.ARRAY_BUFFER,
                Float32Array.create(vertices),
                WebGLRenderingContext.STATIC_DRAW);
    }

    private void initShaders() {
        WebGLShader fragmentShader = getShader(WebGLRenderingContext.FRAGMENT_SHADER,
                Shaders.INSTANCE.fragmentShader().getText());
        WebGLShader vertexShader = getShader(WebGLRenderingContext.VERTEX_SHADER,
                Shaders.INSTANCE.vertexShader().getText());

        shaderProgram = glContext.createProgram();
        glContext.attachShader(shaderProgram, fragmentShader);
        glContext.attachShader(shaderProgram, vertexShader);
        glContext.linkProgram(shaderProgram);

        if (!glContext.getProgramParameterb(shaderProgram, WebGLRenderingContext.LINK_STATUS)) {
            throw new RuntimeException("Could not initialize shaders");
        }

        glContext.useProgram(shaderProgram);

        vertexPositionAttribute = glContext.getAttribLocation(shaderProgram, "vertexPosition");
        glContext.enableVertexAttribArray(vertexPositionAttribute);
    }

    private WebGLShader getShader(int type, String source) {
        WebGLShader shader = glContext.createShader(type);

        glContext.shaderSource(shader, source);
        glContext.compileShader(shader);
        if (!glContext.getShaderParameterb(shader, WebGLRenderingContext.COMPILE_STATUS)) {
            throw new RuntimeException(glContext.getShaderInfoLog(shader));
        }
        return shader;
    }
}
