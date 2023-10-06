#include "OpenSceneWindow.hpp"

#include "SceneCatalog.hpp"
#include "RenderWindow.hpp"

OpenSceneWindow::OpenSceneWindow() : UIWindow("Open Scene") {
    UIVerticalLayout* root = new UIVerticalLayout();
    UILabel* title = new UILabel("Select Scene");
    root->addChild(title);
    UIVerticalLayout* sceneList = new UIVerticalLayout();
    root->addChild(sceneList);
    for (SceneBuilder s : SceneCatalog::builtinScenes) {
        UILabel* sceneName = new UILabel(s.name);
        sceneName->onSelect = [this, s](){
            Scene* sceneToLoad = s();
            UISystem::openWindow(new RenderWindow(sceneToLoad));
            UISystem::closeWindow(this);
        };
        sceneName->selectable = true;
        sceneList->addChild(sceneName);
    } 
    this->setRootNode(root);
    this->initializeNavigation(sceneList);
}