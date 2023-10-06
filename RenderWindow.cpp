#include "RenderWindow.hpp"

#include "UIElements.hpp"

RenderWindow::RenderWindow(Scene* sc) : UIWindow("Rendering Scene") {
    this->scene = sc;
    this->showTitle = false;
    UINode* root = new UILabel("Test"); 
    this->setRootNode(root);
    root->selectable = true;
    this->initializeNavigation(root);

}
