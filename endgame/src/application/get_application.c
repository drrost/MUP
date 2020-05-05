//
// Created by Rostyslav Druzhchenko on 04.05.2020.
//

#include <application.h>
#include <stdlib.h>

App *get_application() {
    static App *application = 0;
    if (application == 0) {
        application = (App *) malloc(sizeof(App));
    }
    return application;
}
