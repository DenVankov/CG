#include <iostream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <cmath>
#include "Shader.h"
#include "multyplyes.h"

// compile: g++ main.cpp -o start -lGL -lGLEW -lglfw

// Number of angles in bottom of piramid
#define NUMBER_OF_LINES 4

#define PIRAMID_HEIGHT 0.7f

// For key press registration:
bool keys[1024];

// For returning configuration in start state
bool ret = false;

// For changing scale and rotation in a moment
GLfloat x_rotation = 0.0f, y_rotation = 0.0f, z_rotation = 0.0f;
GLfloat scale = 1.0f;

// Function of init window and opengl
GLFWwindow* InitOpenGl(GLuint width, GLuint height);

void DestroyOpenGl(GLuint VAO, GLuint VBO, GLuint EBO);

// Initialisation of buffers and creation of figure
void InitBuffers(GLuint& VAO, GLuint& VBO, GLuint& EBO, GLuint num_of_angles);

// Main loop of drawing
void GameLoop(GLFWwindow* window, Shader& shader, GLuint VAO, GLuint VBO, GLuint EBO);

// Functions  for work with keybord
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void do_movement();

// Func for work with screen size changing
void new_func_size_callback(GLFWwindow* window, int width, int height);

// Generation of vector of vertexes of piramid
GLfloat* vertex_vector(GLuint num_of_angles);
// Void vertex_indexses(GLuint* indexis);




GLFWwindow* InitOpenGl(GLuint width, GLuint height){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

    GLFWwindow* window = glfwCreateWindow(width, height, "Lab_2 Var_18", nullptr, nullptr);
    glfwMakeContextCurrent(window);

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, new_func_size_callback);

    glewExperimental = GL_TRUE;

    glewInit();

    glViewport(0, 0, width, height);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    return window;
}

void DestroyOpenGl(GLuint VAO, GLuint VBO, GLuint EBO){
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    if(EBO){
        glDeleteBuffers(1, &EBO);
    }
    glfwTerminate();
}

void InitBuffers(GLuint& VAO, GLuint& VBO, GLuint& EBO, GLuint num_of_angles){
    GLfloat *vertices = vertex_vector(num_of_angles);
    // GLuint indices[2*3*NUMBER_OF_LINES];

    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat) * 144, vertices, GL_DYNAMIC_DRAW);

    //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // first 3 coords - position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(0);

    // second 3 coord - color
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
    glEnableVertexAttribArray(1);

    glBindVertexArray(0); // Unbind VAO
    free(vertices);
}

// EBO disabled

GLfloat* vertex_vector(GLuint num_of_angles){
    GLfloat* vertex_ans = (GLfloat*)malloc(144 * sizeof(GLfloat));
    int j = 0;
    // First triangle
    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.0;

    //Second Triangle

    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.0;

    //Third triangle
    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.0;

    //Fourth triangle
    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.0;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.0;

    //Front triangle side 1
    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;


    //side 2
    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    //side 3
    vertex_ans[j++] = 0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = 0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    //side 4
    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = 0.5;

    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0.0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    vertex_ans[j++] = -0.5;
    vertex_ans[j++] = 0;
    vertex_ans[j++] = -0.5;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = -0.2;

    vertex_ans[j++] = -0.2;
    vertex_ans[j++] = PIRAMID_HEIGHT;
    vertex_ans[j++] = 0.2;

    return vertex_ans;
}

const GLuint WIDTH = 800, HEIGHT = 600;

void new_func_size_callback(GLFWwindow* window, int width, int height){
    if(!height){
        height = 0;
    }
    glViewport(0, 0, width, height);
}

void GameLoop(GLFWwindow* window, Shader& shader, GLuint VAO, GLuint VBO, GLuint EBO){

    // model matrix
    glm::mat4 model = glm::mat4(1.0f);

    // start config of prog:
    const glm::mat4 first_conf = glm::mat4(1.0f);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
        do_movement();

        int width, height;
        glfwGetWindowSize(window, &width, &height);


        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // run shaders:
        shader.Use();

        glm::mat4 view;
        glm::mat4 projection;
        glm::mat4 rotation;

        // We use quaternions for rotate
        glm::vec4 quaternion;
        xyz_rotation_to_quaternion(quaternion, x_rotation, y_rotation, z_rotation);
        // Get rotation matrix from quaternion
        quaternion_to_matrix(rotation, quaternion);

        // Scale change matrix
        glm::mat4 scalem = glm::scale(glm::mat4(1.0f), glm::vec3(scale, scale, scale));
        // Returning in start configuration of piramid
        if(ret){
            model = first_conf;
            ret = false;
        }else{
            // Getting new model matrix from old with rotation and scale matrix:
            model = rotation * scalem * model;
        }

        // Standart view and projection matrix:
        view = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f));
        projection = glm::perspective(glm::radians(45.0f), (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.1f, 100.0f);

        // Finally matrix for multyply with vertex:
        glm::mat4 MVP = projection * view * model;

        // working with shaders
        GLint modelLoc = glGetUniformLocation(shader.Program, "MVP");
        glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(MVP));
        glBindVertexArray(VAO);

        // Without EBO  and draw triangles these method
        glDrawArrays(GL_TRIANGLES, 0, 48);
        glBindVertexArray(0);

        glfwSwapBuffers(window);
       // getchar();
    }
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
        return;
    }
    if(action == GLFW_PRESS) {
        keys[key] = true;
    }else if(action == GLFW_RELEASE){
        keys[key] = false;
    }
    return;
}

void do_movement(){
    if(keys[GLFW_KEY_UP]){
        scale = 1.04f;
    }else if(keys[GLFW_KEY_DOWN]){
        scale = 0.96f;
    }else{
        scale = 1.0f;
    }
    if(keys[GLFW_KEY_W]){
        x_rotation = glm::radians(5.0f);
    }else if(keys[GLFW_KEY_Q]){
        x_rotation = -glm::radians(5.0f);
    }else{
        x_rotation = 0.0f;
    }
    if(keys[GLFW_KEY_A]){
        y_rotation = -glm::radians(5.0f);
    }else if(keys[GLFW_KEY_S]){
        y_rotation = glm::radians(5.0f);
    }else{
        y_rotation = 0.0f;
    }
    if(keys[GLFW_KEY_Z]){
        z_rotation = -glm::radians(5.0f);
    }else if(keys[GLFW_KEY_X]){
        z_rotation = glm::radians(5.0f);
    }else{
        z_rotation = 0.0f;
    }
    if(keys[GLFW_KEY_R]){
        ret = true;
    }
}


int main()
{
    GLFWwindow* window = InitOpenGl(WIDTH, HEIGHT);

    // Get and compile shader programs:
    Shader ourShader("shaders/shader.vs", "shaders/shader.frag");

    GLuint VBO, VAO, EBO;
    InitBuffers(VAO, VBO, EBO, NUMBER_OF_LINES);

    GameLoop(window, ourShader, VAO, VBO, EBO);

    DestroyOpenGl(VAO, VBO, EBO);

    return 0;
}
