#ifndef BOID_H
#define BOID_H

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <GLFW/glfw3.h>

using namespace std;

#define XMin 0
#define YMin 0
#define XMax 1000
#define YMax 1000

#define G 0.0006674
#define E2 0.01

class Boid
{
    public:
        double posX, posY;
        double velX, velY;
        double accX, accY;
        // double r;
        // double maxForce, maxVelocity, minVelocity;
        
    public:
    //constructor to inialize a particle
        Boid(double x, double y){
            posX = (rand() % 1000);
            posY = (rand() % 1000);
            // velX = (pow(-1, rand()%2)) * (rand() % 10);
            // velY = (pow(-1, rand()%2)) * (rand() % 10);
            // velX /= 500;
            // velY /= 500;
            velX = 0;
            velY = 0;
            accX = 0;
            accY = 0;
            // maxVelocity = 5.0;
            // minVelocity = 0.1;
            // maxForce = 0.05;

        }

        // draw the particles
        void draw(int particleIndex){
            int r = 10;
            int segments = 10;
            // glBegin( GL_TRIANGLE_FAN );
            //     glVertex2f(posX, posY);
            //     if(particleIndex == 0){
            //         glColor3f(1, 0, 0);
            //     }
            //     else{
            //         glColor3f(0, 0, 1);
            //     }
            //     for( int n = 0; n <= segments; ++n ) {
            //         float const t = 2 * M_PI * (float)n / (float)segments;
            //         glVertex2f(posX + sin(t) * r, posY + cos(t) * r);
            //     }
            // glEnd();
            glBegin(GL_QUADS);
            if(particleIndex == 0){
                glColor3f(1, 0, 0);
            }
            else{
                glColor3f(0, 0, 1);
            }
            glVertex3f(posX + 10, posY + 10, 0);
            glVertex3f(posX + 10, posY - 10, 0);
            glVertex3f(posX - 10, posY - 10, 0);
            glVertex3f(posX - 10, posY + 10, 0);
            glEnd();

        }

        void update(){
            usleep(10);
            velX += accX;
            velY += accY;
            posX += velX;
            posY += velY;
            
        }

        void applyGravity(vector<Boid> collection, int particleIndex){

            double sqDistance, force, distance;
            accX = 0.0;
            accY = 0.0;
            for(int i = 0; i < collection.size(); i++)
            {
                if (i != particleIndex) {
                    sqDistance = (collection[i].posX - posX) * (collection[i].posX - posX) + (collection[i].posY - posY) * (collection[i].posY - posY);
                    distance = sqrt(sqDistance);
                    force = (1000 * distance) / pow(sqrt(sqDistance + E2),3);
                    if(sqDistance == 0){
                        cout<<"dist 0"<<endl;
                    } else {
                        accX += force * (collection[i].posX - posX)/distance;
                        accY += force * (collection[i].posY - posY)/distance;
                    }
                }  
                            
            }
            cout<<"Acc of"<<particleIndex<<" : "<<accX<<" "<<accY<<endl;

        }

        // void limitVelocity(){
        //     double vel = sqrt((velX * velX) + (velY * velY));
        //     if (vel > maxVelocity) {
        //         velX = (velX / vel) * maxVelocity;
        //         velY = (velY / vel) * maxVelocity;
        //     }

        //     if (vel < minVelocity) {
        //         velX = (velX / vel) * minVelocity;
        //         velY = (velY / vel) * minVelocity;
        //     }
            
            
        // }

        
        void run(vector<Boid> collection, int particleIndex){
            applyGravity(collection, particleIndex);
            // limitVelocity();
            update();
            draw(particleIndex);

        }        
};



#endif