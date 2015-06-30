package hello;

import com.jme3.app.SimpleApplication;
import com.jme3.asset.TextureKey;
import com.jme3.bullet.BulletAppState;
import com.jme3.bullet.control.RigidBodyControl;
import com.jme3.font.BitmapText;
import com.jme3.input.KeyInput;
import com.jme3.input.MouseInput;
import com.jme3.input.controls.ActionListener;
import com.jme3.input.controls.KeyTrigger;
import com.jme3.input.controls.MouseButtonTrigger;
import com.jme3.material.Material;
import com.jme3.math.Vector2f;
import com.jme3.math.Vector3f;
import com.jme3.scene.Geometry;
import com.jme3.scene.shape.Box;
import com.jme3.scene.shape.Sphere;
import com.jme3.scene.shape.Sphere.TextureMode;
import com.jme3.texture.Texture;
import com.jme3.texture.Texture.WrapMode;

/**
 * Laboratory work N1 - Cannon ball flight.
 * 
 * @author Witalia
 */
public class MyGame extends SimpleApplication {

    public static void main(String args[]) {
        MyGame app = new MyGame();
        app.start();
    }

    /** Prepare the Physics Application State (jBullet) */
    private BulletAppState bulletAppState;

    /** Prepare Materials */
    Material wallMaterial;
    Material stoneMaterial;
    Material floorMaterial;

    /** Prepare geometries and physical nodes for bricks and cannon balls. */
    private RigidBodyControl brickPhysical;
    private static final Box box;
    RigidBodyControl ballPhysical;
    private static final Sphere sphere;
    private RigidBodyControl floorPhysical;
    private static final Box floor;

    /** dimensions used for bricks and wall */
    private static final float brickLength = 0.48f;
    private static final float brickWidth = 0.24f;
    private static final float brickHeight = 0.12f;

    Vector3f gravity = new Vector3f(0, -9.816f, 0);

    static {
        /** Initialize the cannon ball geometry */
        sphere = new Sphere(32, 32, 0.4f, true, false);
        sphere.setTextureMode(TextureMode.Projected);
        /** Initialize the brick geometry */
        box = new Box(brickLength, brickHeight, brickWidth);
        box.scaleTextureCoordinates(new Vector2f(1f, .5f));
        /** Initialize the floor geometry */
        floor = new Box(1000f, 0.1f, 1000f);
        floor.scaleTextureCoordinates(new Vector2f(3, 6));
    }

    @Override
    public void simpleInitApp() {
        /** Set up Physics Game */
        bulletAppState = new BulletAppState();
        stateManager.attach(bulletAppState);
        // bulletAppState.getPhysicsSpace().enableDebug(assetManager);

        /** Configure camera to look at scene */
        cam.setLocation(new Vector3f(0, 4f, 6f));
        cam.lookAt(new Vector3f(2, 2, 0), Vector3f.UNIT_Y);
        
        /** Initialize the scene, materials, and physics space */
        initMaterials();
        initWall();
        initFloor();
        initCrossHairs();
        initKeys(); // load my custom keybinding
    }

    /** Custom Keybindings: Map named actions to inputs. */
    private void initKeys() {
        inputManager.addMapping("shoot", new MouseButtonTrigger(
                MouseInput.BUTTON_LEFT));
        
        inputManager.addMapping("Inc", new KeyTrigger(KeyInput.KEY_ADD));
        inputManager.addMapping("Dec", new KeyTrigger(KeyInput.KEY_SUBTRACT));
        inputManager.addMapping("Nul", new KeyTrigger(KeyInput.KEY_NUMPAD0), 
                new KeyTrigger(KeyInput.KEY_0));
        
        // Add the names to the action listener.
        inputManager.addListener(actionListener, "Inc", "Dec", "Nul", "shoot");
    }

    /**
     * Every time the shoot action is triggered, a new cannon ball is produced.
     * The ball is set up to fly from the camera position in the camera
     * direction.
     */
    private ActionListener actionListener = new ActionListener() {
        public void onAction(String name, boolean keyPressed, float tpf) {
            if (name.equals("shoot") && !keyPressed) {
                makeCannonBall();
            }
            if (ballPhysical != null) {
                if (name.equals("Inc")) {
                    gravity = gravity.add(new Vector3f(0, -1, 0));
                }
                if (name.equals("Dec")) {
                    gravity = gravity.add(new Vector3f(0, 1, 0));
                }
                if (name.equals("Nul")) {
                    gravity = Vector3f.ZERO;
                }
                ballPhysical.getPhysicsSpace().setGravity(gravity);
                System.out.println(gravity.getY());
            }
        }
    };

    /** Initialize the materials used in this scene. */
    public void initMaterials() {
        TextureKey keyWall, keyRock, keyPond;
        Texture texWall, texRock, texPond;
        
        wallMaterial = new Material(assetManager,
                "Common/MatDefs/Misc/Unshaded.j3md");
        keyWall = new TextureKey(
                "Textures/Terrain/BrickWall/BrickWall.jpg");
        keyWall.setGenerateMips(true);
        texWall = assetManager.loadTexture(keyWall);
        wallMaterial.setTexture("ColorMap", texWall);

        stoneMaterial = new Material(assetManager,
                "Common/MatDefs/Misc/Unshaded.j3md");
        keyRock = new TextureKey("Textures/Terrain/Rock/Rock.PNG");
        keyRock.setGenerateMips(true);
        texRock = assetManager.loadTexture(keyRock);
        stoneMaterial.setTexture("ColorMap", texRock);

        floorMaterial = new Material(assetManager,
                "Common/MatDefs/Misc/Unshaded.j3md");
        keyPond = new TextureKey("Textures/Terrain/Pond/Pond.jpg");
        keyPond.setGenerateMips(true);
        texPond = assetManager.loadTexture(keyPond);
        texPond.setWrap(WrapMode.Repeat);
        floorMaterial.setTexture("ColorMap", texPond);
    }

    /** Make a solid floor and add it to the scene. */
    public void initFloor() {
        Geometry floor_geo = new Geometry("Floor", floor);
        floor_geo.setMaterial(floorMaterial);
        floor_geo.setLocalTranslation(0, -0.1f, 0);
        this.rootNode.attachChild(floor_geo);
        
        /* Make the floor physical with mass 0.0f! */
        floorPhysical = new RigidBodyControl(0.0f);
        floor_geo.addControl(floorPhysical);
        bulletAppState.getPhysicsSpace().add(floorPhysical);
    }

    /** This loop builds a wall out of individual bricks. */
    public void initWall() {
        float startpt = brickLength / 4;
        float height = 0;
        for (int j = 0; j < 15; j++) {
            for (int i = 0; i < 6; i++) {
                Vector3f vt = new Vector3f(i * brickLength * 2 + startpt,
                        brickHeight + height, -100);
                makeBrick(vt);
            }
            startpt = -startpt;
            height += 2 * brickHeight;
        }
    }

    /** This method creates one individual physical brick. */
    public void makeBrick(Vector3f location) {
        /** Create a brick geometry and attach to scene graph. */
        Geometry brick_geo = new Geometry("brick", box);
        brick_geo.setMaterial(wallMaterial);
        rootNode.attachChild(brick_geo);
        
        /** Position the brick geometry */
        brick_geo.setLocalTranslation(location);
        
        /** Make brick physical with a mass > 0.0f. */
        brickPhysical = new RigidBodyControl(10f);
        
        /** Add physical brick to physics space. */
        brick_geo.addControl(brickPhysical);
        bulletAppState.getPhysicsSpace().add(brickPhysical);
    }

    /**
     * This method creates one individual physical cannon ball. By default, the
     * ball is accelerated and flies from the camera position in the camera
     * direction.
     */
    public void makeCannonBall() {
        /** Create a cannon ball geometry and attach to scene graph. */
        Geometry ball_geo = new Geometry("cannon ball", sphere);
        ball_geo.setMaterial(stoneMaterial);
        rootNode.attachChild(ball_geo);
        
        /** Position the cannon ball */
        ball_geo.setLocalTranslation(cam.getLocation());
        
        /** Make the ball physical with a mass > 0.0f */
        ballPhysical = new RigidBodyControl(100f);
        
        /** Add physical ball to physics space. */
        ball_geo.addControl(ballPhysical);
        bulletAppState.getPhysicsSpace().add(ballPhysical);
        
        /** Accelerate the physical ball to shoot it. */
        ballPhysical.getPhysicsSpace().setGravity(gravity);
        ballPhysical.setLinearVelocity(cam.getDirection().mult(50));
    }

    /** A plus sign used as crosshairs to help the player with aiming. */
    protected void initCrossHairs() {
        guiNode.detachAllChildren();
        guiFont = assetManager.loadFont("Interface/Fonts/Default.fnt");
        BitmapText ch = new BitmapText(guiFont, false);
        ch.setSize(guiFont.getCharSet().getRenderedSize() * 2);
        ch.setText("+"); // fake crosshairs :)
        ch.setLocalTranslation(
                // center
                settings.getWidth() / 2
                        - guiFont.getCharSet().getRenderedSize() / 3 * 2,
                settings.getHeight() / 2 + ch.getLineHeight() / 2, 0);
        guiNode.attachChild(ch);
    }
}