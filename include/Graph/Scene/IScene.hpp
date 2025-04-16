/*
** Pokemon Primal
** File description:
** IScene
*/

#ifndef ISCENE_HPP_
#define ISCENE_HPP_

#pragma once

class IScene {
public:
    IScene() = default;
    ~IScene() = default;
    virtual void draw() = 0;
protected:
private:
    
};

#endif /* !ISCENE_HPP_ */
