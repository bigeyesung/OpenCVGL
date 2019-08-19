//
//  main.cpp
//  OpenCVGL
//
//  Created by chenhsi on 2017/10/21.
//  Copyright © 2017年 chenhsi. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <cstdio>
#include <vector>
#include <cstdlib>
//#include <GLUT/glut.h>
// GLEW
#define GLEW_STATIC
#include <GL/glew.h>
#include<OpenGL/glext.h>
// GLFW
#include <GLFW/glfw3.h>
#include <opencv2/opencv.hpp>
// GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include <glm/mat4x4.hpp>

//#include <openvr.h>
const GLint WIDTH = 800, HEIGHT = 600;
using namespace std;
using namespace cv;
using namespace glm;

// An array of 3 vectors which represents 3 vertices
static const GLfloat g_vertex_buffer_data[] = {
//    -1.0f, -1.0f, 0.0f,
//    1.0f, -1.0f, 0.0f,
//    0.0f,  1.0f, 0.0f,
    
    -1.0f,-1.0f,-1.0f, // triangle 1 : begin
    -1.0f,-1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f, // triangle 1 : end
    1.0f, 1.0f,-1.0f, // triangle 2 : begin
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f, // triangle 2 : end
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    -1.0f,-1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    -1.0f,-1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f,-1.0f,
    1.0f,-1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f,-1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f,-1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f, 1.0f, 1.0f,
    -1.0f, 1.0f, 1.0f,
    1.0f,-1.0f, 1.0f
    
};


//每個頂點一個顏色
static const GLfloat g_color_buffer_data[] = {
         0.583f,  0.771f,  0.014f,
         0.609f,  0.115f,  0.436f,
         0.327f,  0.483f,  0.844f,
         0.822f,  0.569f,  0.201f,
         0.435f,  0.602f,  0.223f,
         0.310f,  0.747f,  0.185f,
         0.597f,  0.770f,  0.761f,
         0.559f,  0.436f,  0.730f,
         0.359f,  0.583f,  0.152f,
         0.483f,  0.596f,  0.789f,
         0.559f,  0.861f,  0.639f,
         0.195f,  0.548f,  0.859f,
         0.014f,  0.184f,  0.576f,
         0.771f,  0.328f,  0.970f,
         0.406f,  0.615f,  0.116f,
         0.676f,  0.977f,  0.133f,
         0.971f,  0.572f,  0.833f,
         0.140f,  0.616f,  0.489f,
         0.997f,  0.513f,  0.064f,
         0.945f,  0.719f,  0.592f,
         0.543f,  0.021f,  0.978f,
         0.279f,  0.317f,  0.505f,
         0.167f,  0.620f,  0.077f,
         0.347f,  0.857f,  0.137f,
         0.055f,  0.953f,  0.042f,
         0.714f,  0.505f,  0.345f,
         0.783f,  0.290f,  0.734f,
         0.722f,  0.645f,  0.174f,
         0.302f,  0.455f,  0.848f,
         0.225f,  0.587f,  0.040f,
         0.517f,  0.713f,  0.338f,
         0.053f,  0.959f,  0.120f,
         0.393f,  0.621f,  0.362f,
         0.673f,  0.211f,  0.457f,
         0.820f,  0.883f,  0.371f,
         0.982f,  0.099f,  0.879f
    
    };

// Two UV coordinatesfor each vertex.
static const GLfloat g_uv_buffer_data[] = {
    0.000059f, 1.0f-0.000004f,
    0.000103f, 1.0f-0.336048f,
    0.335973f, 1.0f-0.335903f,
    1.000023f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.336024f, 1.0f-0.671877f,
    0.667969f, 1.0f-0.671889f,
    1.000023f, 1.0f-0.000013f,
    0.668104f, 1.0f-0.000013f,
    0.667979f, 1.0f-0.335851f,
    0.000059f, 1.0f-0.000004f,
    0.335973f, 1.0f-0.335903f,
    0.336098f, 1.0f-0.000071f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.336024f, 1.0f-0.671877f,
    1.000004f, 1.0f-0.671847f,
    0.999958f, 1.0f-0.336064f,
    0.667979f, 1.0f-0.335851f,
    0.668104f, 1.0f-0.000013f,
    0.335973f, 1.0f-0.335903f,
    0.667979f, 1.0f-0.335851f,
    0.335973f, 1.0f-0.335903f,
    0.668104f, 1.0f-0.000013f,
    0.336098f, 1.0f-0.000071f,
    0.000103f, 1.0f-0.336048f,
    0.000004f, 1.0f-0.671870f,
    0.336024f, 1.0f-0.671877f,
    0.000103f, 1.0f-0.336048f,
    0.336024f, 1.0f-0.671877f,
    0.335973f, 1.0f-0.335903f,
    0.667969f, 1.0f-0.671889f,
    1.000004f, 1.0f-0.671847f,
    0.667979f, 1.0f-0.335851f
};

GLuint LoadShaders(const char * vertex_file_path,const char * fragment_file_path){
    
    // Create the shaders
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    
    // Read the Vertex Shader code from the file
    std::string VertexShaderCode;
    std::ifstream VertexShaderStream(vertex_file_path, std::ios::in);
    if(VertexShaderStream.is_open()){
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }else{
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertex_file_path);
        getchar();
        return 0;
    }
    
    // Read the Fragment Shader code from the file
    std::string FragmentShaderCode;
    std::ifstream FragmentShaderStream(fragment_file_path, std::ios::in);
    if(FragmentShaderStream.is_open()){
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }
    
    GLint Result = GL_FALSE;
    int InfoLogLength;
    
    
    // Compile Vertex Shader
    printf("Compiling shader : %s\n", vertex_file_path);
    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);
    
    // Check Vertex Shader
    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> VertexShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
        printf("%s\n", &VertexShaderErrorMessage[0]);
    }
    
    
    
    // Compile Fragment Shader
    printf("Compiling shader : %s\n", fragment_file_path);
    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);
    
    // Check Fragment Shader
    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
        glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        printf("%s\n", &FragmentShaderErrorMessage[0]);
    }
    
    
    
    // Link the program
    printf("Linking program\n");
    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
    
    // Check the program
    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
        std::vector<char> ProgramErrorMessage(InfoLogLength+1);
        glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
        printf("%s\n", &ProgramErrorMessage[0]);
    }
    
    
    glDetachShader(ProgramID, VertexShaderID);
    glDetachShader(ProgramID, FragmentShaderID);
    
    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);
    
    return ProgramID;
}


// Create and compile our GLSL program from the shaders
//GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

int main(int argc, const char * argv[]) {
    

//tutorial-5
// Data read from the header of the BMP file
unsigned char header[54]; // Each BMP file begins by a 54-bytes header
unsigned int dataPos;     // Position in the file where the actual data begins
unsigned int width, height;
unsigned int imageSize;   // = width*height*3
// Actual RGB data
unsigned char * data;
    
// Open the file
FILE * file = fopen("./test2.bmp","rb");
if (!file){printf("Image could not be opened\n"); return 0;}
    
//
if ( fread(header, 1, 54, file)!=54 )
{ // If not 54 bytes read : problem
    printf("Not a correct BMP file\n");
    return false;
}

if ( header[0]!='B' || header[1]!='M' )
{
    printf("Not a correct BMP file\n");
    return 0;
}

// Read ints from the byte array
dataPos    = *(int*)&(header[0x0A]);
imageSize  = *(int*)&(header[0x22]);
width      = *(int*)&(header[0x12]);
height     = *(int*)&(header[0x16]);

// Some BMP files are misformatted, guess missing information
if (imageSize==0)    imageSize=width*height*3; // 3 : one byte for each Red, Green and Blucomponent
if (dataPos==0)      dataPos=54; // The BMP header is done that way

// Create a buffer
data = new unsigned char [imageSize];

// Read the actual data from the file into the buffer
fread(data,1,imageSize,file);

//Everything is in memory now, the file can be closed
fclose(file);
    
    
//tutorial-2
// Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }

    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // We don't want the old OpenGL

    // Open a window and create its OpenGL context
    GLFWwindow* window; // (In the accompanying source code, this variable is global for simplicity)
    window = glfwCreateWindow( 800, 600, "Tutorial 02", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window); // Initialize GLEW

    glewExperimental=true; // Needed in core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
//----------以下才能call openGL function----------//
    // Create one OpenGL texture
    GLuint textureID;
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);


    //啟用z-buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);

    //背景顏色
    glClearColor(0.0f, 0.4f, 0.0f, 0.0f);

    //載入並編譯shader
    GLuint programID = LoadShaders( "/Users/CHENHSI/Desktop/OpenCVGL/vertex1.vert", "/Users/CHENHSI/Desktop/OpenCVGL/fragment1.frag" );

    //VAO
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

         //第一個VBO
         //儲存頂點數據
         GLuint vertexbuffer;
         //創建
         glGenBuffers(1, &vertexbuffer);
         //綁定
         glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
         //儲存數據
         glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data),
                      g_vertex_buffer_data, GL_STATIC_DRAW);

        //第二個VBO
        //儲存顏色信息
         //操作原理同上
//         GLuint colorbuffer;
//         glGenBuffers(1, &colorbuffer);
//         glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
//         glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);
    
//      //第三個VBO
//      //儲存uv信息
      GLuint uvbuffer;
      glGenBuffers(1, &uvbuffer);
      glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
      glBufferData(GL_ARRAY_BUFFER, sizeof(g_uv_buffer_data),
                   g_uv_buffer_data, GL_STATIC_DRAW);

    // position
    glm::vec3 position = glm::vec3( 0, 0, 5 );
    // horizontal angle : toward -Z
    float horizontalAngle = 3.14f;
    // vertical angle : 0, look at the horizon
    float verticalAngle = 0.0f;
    // Initial Field of View
    float initialFoV = 45.0f;
    
    float speed = 3.0f; // 3 units / second
    float mouseSpeed = 0.005f;
    
//    //創建座標變換矩陣
//    //本地   ->  世界  -> 視口    ->    齊次剪裁空間       空間變換流程
//    //     Model    View    Projection                 對應需要的矩陣
//    //透視變換
//    mat4 Projection = perspective(radians(45.0f), (float)WIDTH / HEIGHT, 0.1f, 1000.f);
//    //視口變換
//    mat4 View = lookAt(vec3(4, 3, 3), vec3(0,0,0), vec3(0,1,0));
//    //本地變換
//    mat4 Model = mat4(1.0f);
//
//    //集成本地到齊次剪裁空間的轉換
//    mat4 MVP = Projection * View * Model;

    //從shader中取出mvp (不是上面的MVP，特地用大小寫區分了)
    //方便等會傳入數據
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");//tutorial-4
    GLuint TextureID = glGetUniformLocation(programID, "myTextureSampler");




//    // This will identify our vertex buffer
//    GLuint vertexbuffer;
//    // Generate 1 buffer, put the resulting identifier in vertexbuffer
//    glGenBuffers(1, &vertexbuffer);
//    // The following commands will talk about our 'vertexbuffer' buffer
//    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
//    // Give our vertices to OpenGL.
//    glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    do{
        //每次開始時清空畫布
        //同時清空z-buffer
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Use our shader
        glUseProgram(programID);

        
        // Compute the MVP matrix from keyboard and mouse input
        
        glm::mat4 computeMatricesFromInputs();
        glm::mat4 ProjectionMatrix = gl::getProjectionMatrix();
        glm::mat4 ViewMatrix =  glm::mat4 getViewMatrix();
        glm::mat4 ModelMatrix = glm::mat4(1.0);
        glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        // Get mouse position
        int xpos, ypos;
        glfwGetMousePos(&xpos, &ypos);
        
        // Reset mouse position for next frame
        glfwSetMousePos(1024/2, 768/2);
        
        // Compute new orientation
        horizontalAngle += mouseSpeed * deltaTime * float(1024/2 - xpos );
        verticalAngle   += mouseSpeed * deltaTime * float( 768/2 - ypos );
        
        glm::vec3 direction(
                            cos(verticalAngle) * sin(horizontalAngle),
                            sin(verticalAngle),
                            cos(verticalAngle) * cos(horizontalAngle)
                            );
        
        // Right vector
        glm::vec3 right = glm::vec3(
                                    sin(horizontalAngle - 3.14f/2.0f),
                                    0,
                                    cos(horizontalAngle - 3.14f/2.0f)
                                    );
        
        // Up vector : perpendicular to both direction and right
        glm::vec3 up = glm::cross( right, direction );
        
        // Move forward
        if (glfwGetKey( GLFW_KEY_UP ) == GLFW_PRESS){
            position += direction * deltaTime * speed;
        }
        // Move backward
        if (glfwGetKey( GLFW_KEY_DOWN ) == GLFW_PRESS){
            position -= direction * deltaTime * speed;
        }
        // Strafe right
        if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
            position += right * deltaTime * speed;
        }
        // Strafe left
        if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
            position -= right * deltaTime * speed;
        }
        
        double currentTime = glfwGetTime();
        float deltaTime = float(currentTime - lastTime);
        
        float FoV = initialFoV - 5 * glfwGetMouseWheel();
        
        // Projection matrix : 45&deg; Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
        ProjectionMatrix = glm::perspective(glm::radians(FoV), 4.0f / 3.0f, 0.1f, 100.0f);
        // Camera matrix
        ViewMatrix       = glm::lookAt(
                                       position,           // Camera is here
                                       position+direction, // and looks here : at the same position, plus "direction"
                                       up                  // Head is up (set to 0,-1,0 to look upside-down)
                                       );
        
        
        //把變換矩陣送進shader
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);


        // Bind our texture in Texture Unit 0
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, textureID);
        // Set our "myTextureSampler" sampler to user Texture Unit 0
        glUniform1i(TextureID, 0);
        
        
        //把頂點信息送入shader
        //數字0對應vertex shader中的 location = 0
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );

        //把三角形顏色送入shader
        //數字0對應vertex shader中的 location = 1
//        glEnableVertexAttribArray(1);
//        glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
//        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        //把三角形uv送入shader
        //數字0對應vertex shader中的 location = 1
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        

        // Draw the triangle !
        glDrawArrays(GL_TRIANGLES, 0, 12*3); // Starting from vertex 0; 3 vertices total -> 1 triangle

        //一定要在draw call之後關閉
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);

        // Swap buffers
        //切換前後緩存，將渲染好的顯示出來
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );

    

//tutorial-3
//translate matirx
//glm::mat4 myMatrix = glm::translate(glm::mat4(), glm::vec3(10.0f, 0.0f, 0.0f));
//glm::vec4 myVector(10.0f, 10.0f, 10.0f, 0.0f);
//glm::vec4 transformedVector = myMatrix * myVector; // guess the result
//
////scale matrix
//glm::mat4 myScalingMatrix = glm::scale(2.0f, 2.0f ,2.0f);
//
//    // Output position of the vertex, in clip space : MVP * position
//    gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
    
    return 0;
    
    
}
