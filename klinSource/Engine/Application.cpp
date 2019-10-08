//
// Created by liuyizhou on 2019/7/18.
//


#include "Application.h"


Application::Application() : isInitial_(false) {

}

Application::~Application() {

}

void Application::BaseCreateScence(Context *context, int width, int height) {
    CreateScence(context, width, height);
    isInitial_ = true;
}

