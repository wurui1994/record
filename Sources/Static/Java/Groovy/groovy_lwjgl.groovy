// JAVA_OPTS=-XstartOnFirstThread groovy groovy_lwjgl.groovy
// ref:https://blog.csdn.net/chiduokui9989/article/details/100852400

@GrabResolver(name='aliyun', root='https://maven.aliyun.com/repository/public')

@Grab(group="org.lwjgl", module="lwjgl", version="latest.release")
@Grab(group="org.lwjgl", module="lwjgl-opengl", version="latest.release")
@Grab(group="org.lwjgl", module="lwjgl-glfw", version="latest.release")

//Windows 
@Grab(group="org.lwjgl", module="lwjgl", version="latest.release",classifier="natives-windows")
@Grab(group="org.lwjgl", module="lwjgl-opengl", version="latest.release",classifier="natives-windows")
@Grab(group="org.lwjgl", module="lwjgl-glfw", version="latest.release",classifier="natives-windows")
//Linux  
@Grab(group="org.lwjgl", module="lwjgl", version="latest.release",classifier="natives-linux")
@Grab(group="org.lwjgl", module="lwjgl-opengl", version="latest.release",classifier="natives-linux")
@Grab(group="org.lwjgl", module="lwjgl-glfw", version="latest.release",classifier="natives-linux")   
//macOS  
@Grab(group="org.lwjgl", module="lwjgl", version="latest.release",classifier="natives-macos-arm64")
@Grab(group="org.lwjgl", module="lwjgl-opengl", version="latest.release",classifier="natives-macos-arm64")
@Grab(group="org.lwjgl", module="lwjgl-glfw", version="latest.release",classifier="natives-macos-arm64")   

import org.lwjgl.*;
import org.lwjgl.glfw.*;
import org.lwjgl.opengl.*;

import static org.lwjgl.glfw.Callbacks.*;
import static org.lwjgl.glfw.GLFW.*;
import static org.lwjgl.opengl.GL11.*;
import static org.lwjgl.system.MemoryStack.*;
import static org.lwjgl.system.MemoryUtil.*;
//
println(System.getProperty("os.name"));
//
if ( !glfwInit() )
    throw new IllegalStateException("Unable to initialize GLFW");

final int width = 640;
final int height = 480;

glfwWindowHint(GLFW_VISIBLE, GLFW_FALSE);
long window = glfwCreateWindow(width, height, "Hello World!", NULL, NULL);
if ( window == NULL )
    throw new RuntimeException("Failed to create the GLFW window");

monitor = glfwGetPrimaryMonitor();
mode = glfwGetVideoMode(monitor);
printf("%d %d\n",mode.width(),mode.height());
glfwSetWindowPos(window, (int)(mode.width()/2 - width/2), (int)(mode.height()/2 - height/2));

glfwMakeContextCurrent(window);
glfwSwapInterval(1);
glfwShowWindow(window);

GL.createCapabilities();
// Set the clear color
glClearColor(0.2f, 0.3f, 0.3f, 0.0f);

while ( !glfwWindowShouldClose(window) )
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the framebuffer
    glfwSwapBuffers(window); // swap the color buffers
    // Poll for window events. The key callback above will only be
    // invoked during this call.
    glfwPollEvents();
}

glfwDestroyWindow(window);
glfwTerminate();
