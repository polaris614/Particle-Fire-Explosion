//
//  main.cpp
//  SDL Basic
//
//  Created by Lee Zheng Jun on 27/12/2020.
//  Copyright © 2020 Lee Zheng Shieng. All rights reserved.
//

#include <iostream>
#include <SDL.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include "Screen.hpp"
#include "Swarm.hpp"
using namespace std;
using namespace wind;

int main() {
    
    srand(time(NULL)); // rand() is not really random, we have to change the seed using time passed
    
    Screen screen;
    
    if(screen.init() == false) {
        cout << "Error initializing SDL." << endl;
    }
    
    Swarm swarm;
    
    
    while(true) {
        // Update particles
        // Draw particles
        
        int elapsed = SDL_GetTicks();
        
        swarm.update(elapsed);
        
        unsigned char green = (unsigned char)((1 + sin(elapsed * 0.0001)) * 128);
        unsigned char red = (unsigned char)((1 + sin(elapsed * 0.0002)) * 128);
        unsigned char blue = (unsigned char)((1 + sin(elapsed * 0.0003)) * 128);
        
        const Particle * const pParticles = swarm.getParticles();
        
        for(int i = 0; i < Swarm::NPARTICLES; i++) {
            Particle particle = pParticles[i];
            
            int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH / 2;
            int y = particle.m_y * Screen::SCREEN_WIDTH / 2 + Screen::SCREEN_HEIGHT/2;
            
            screen.setPixel(x, y, red, green, blue);
        }

        
        screen.boxBlur();
        // Draw the screen
        screen.update();
        
        // Check for messages/events
        if(screen.processEvents() == false) {
            break;
        }
        
    }
    
    screen.close();
    
    return 0;
}