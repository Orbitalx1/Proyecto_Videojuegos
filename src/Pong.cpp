#include <GL/glut.h>
#include <math.h>

// Dimensiones
const int Ancho = 800;
const int Altura = 600;

// Posiciones de jugadores y pelota inicio
float jugador1 = 0.0f;
float jugador2 = 0.0f;
float PelotitaX = 0.0f, PelotitaY = 0.0f;
float PelotitaDirX = 0.01f, PelotitaDirY = 0.01f; 

#define PI 3.1415926535898
GLint circle_points = 100;

// Función para dibujar un círculo
void MyCircle2f(GLfloat centerx, GLfloat centery, GLfloat radius) {
    glBegin(GL_POLYGON);
    for (int i = 0; i < circle_points; i++) {
        float angle = 2.0f * PI * i / circle_points;
        glVertex2f(centerx + radius * cos(angle), centery + radius * sin(angle));
    }
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    // Porteria izquierda, Jugador Izquierda
    glPushMatrix();
    glTranslatef(-0.9f, jugador1, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.2f);
        glVertex2f(0.05f, 0.2f);
        glVertex2f(0.05f, -0.2f);
        glVertex2f(-0.05f, -0.2f);
    glEnd();
    glPopMatrix();
    
    // Porteria derecha, Jugador Derecha
    glPushMatrix();
    glTranslatef(0.9f, jugador2, 0.0f);
    glBegin(GL_QUADS);
        glVertex2f(-0.05f, 0.2f);
        glVertex2f(0.05f, 0.2f);
        glVertex2f(0.05f, -0.2f);
        glVertex2f(-0.05f, -0.2f);
    glEnd();
    glPopMatrix();

    // Dibujar pelota (círculo)
    glPushMatrix();
    glTranslatef(PelotitaX, PelotitaY, 0.0f);
    glColor3f(1.0f, 0.0f, 0.0f); // Color rojo
    MyCircle2f(0.0f, 0.0f, 0.05f); // Dibujar círculo de radio 0.05
    glPopMatrix();
    glutSwapBuffers();
}

void update(int value) {
    PelotitaX += PelotitaDirX;
    PelotitaY += PelotitaDirY;

    // Colisión con los bordes superior e inferior
    if (PelotitaY > 1.0f || PelotitaY < -1.0f) {
        PelotitaDirY = -PelotitaDirY; 
    }

    // Reiniciar pelota si sale por los lados
    if (PelotitaX > 1.0f || PelotitaX < -1.0f) {
        PelotitaX = 0.0f;
        PelotitaY = 0.0f; 
    }

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

void keyboard(unsigned char key, int x, int y) {
    switch (key) {
        case 'w': // Mover jugador 1 hacia arriba
            if (jugador1 < 0.8f) jugador1 += 0.1f;
            break;
        case 's': // Mover jugador 1 hacia abajo
            if (jugador1 > -0.8f) jugador1 -= 0.1f;
            break;
        case 'o': // Mover jugador 2 hacia arriba
            if (jugador2 < 0.8f) jugador2 += 0.1f;
            break;
        case 'l': // Mover jugador 2 hacia abajo
            if (jugador2 > -0.8f) jugador2 -= 0.1f;
            break;
    }
    glutPostRedisplay(); // Actualizar la pantalla
}

void init() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(Ancho, Altura);
    glutCreateWindow("Pong");
    
    init();
    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(0, update, 0); 
    glutMainLoop();
    return 0;
}