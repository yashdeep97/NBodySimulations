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
        double potentialEnergy;
        // double r;
        // double maxForce, maxVelocity, minVelocity;
        
    public:
    //constructor to inialize a particle
        Boid(double x, double y){
            posX = (rand() % 1000);
            posY = (rand() % 1000);
            velX = 0;
            velY = 0;

            // posX = x;
            // posY = y;
            // velX = pow(-1, (rand() % 2)) * (rand() % 100);
            // velY = pow(-1, (rand() % 2)) * (rand() % 100);

            accX = 0;
            accY = 0;

            potentialEnergy = 0.0;
            // maxVelocity = 5.0;
            // minVelocity = 0.1;
            // maxForce = 0.05;

        }

        // draw the particles
        void draw(int particleIndex){
            int r = 3;
            int segments = 10;
            glBegin( GL_TRIANGLE_FAN );
                glVertex2f(posX, posY);
                // if(particleIndex == 0){
                //     glColor3f(1, 0, 0);
                // }
                // else{
                //     glColor3f(0, 0, 1);
                // }
                for( int n = 0; n <= segments; ++n ) {
                    float const t = 2 * M_PI * (float)n / (float)segments;
                    glVertex2f(posX + sin(t) * r, posY + cos(t) * r);
                }
            glEnd();
            // glBegin(GL_QUADS);
            // if(particleIndex == 0){
            //     glColor3f(1, 0, 0);
            // }
            // else{
            //     glColor3f(0, 0, 1);
            // }
            // glVertex3f(posX + 10, posY + 10, 0);
            // glVertex3f(posX + 10, posY - 10, 0);
            // glVertex3f(posX - 10, posY - 10, 0);
            // glVertex3f(posX - 10, posY + 10, 0);
            // glEnd();

        }

        double update(){
                    
            velX += accX*0.001;
            velY += accY*0.001;
            posX += velX*0.001;
            posY += velY*0.001;

            double K = ((velX*velX) + (velY*velY))/2;
            return K;
            
        }

        // return potential energy
        void applyGravity(vector<Boid> collection, int particleIndex){

            double sqDistance, force, distance;
            accX = 0.0;
            accY = 0.0;
            potentialEnergy = 0.0;
            for(int i = 0; i < collection.size(); i++)
            {
                if (i != particleIndex) {
                    sqDistance = (collection[i].posX - posX) * (collection[i].posX - posX) + (collection[i].posY - posY) * (collection[i].posY - posY);
                    distance = sqrt(sqDistance);
                    force = (10000) / (sqDistance + E2);
                    if(sqDistance < 10){
                        // cout<<"dist 0"<<endl;
                    } else {
                        accX += force * (collection[i].posX - posX)/distance;
                        accY += force * (collection[i].posY - posY)/distance;
                    }
                    // if (distance != 0) {
                    //     potentialEnergy -= (10000.0 / (double)distance);
                    // }
                    
                }  
                            
            }
            // return potentialEnergy;
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

        
        double run(vector<Boid> collection, int particleIndex){
            applyGravity(collection, particleIndex);
            // cout<<"U: "<<U<<endl;
            // limitVelocity();
            double momentum = update();
            draw(particleIndex);
            return (momentum);
        }        
};



#endif