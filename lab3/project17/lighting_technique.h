#pragma once
#ifndef LIGHTINGTECHNIQUE_H
#define LIGHTINGTECHNIQUE_H

#include "technique.h"
#include "math_3d.h"

/*Это начало определения направленного света.
  Структура хранит 2 поля - цвет и фоновую интенсивность.*/

struct DirectionLight
{
    Vector3f Color;
    float AmbientIntensity;
};

/*Это первый пример использования класса Technique.
  LightingTechnique наследует этот класс, и представляет собой инвентарь света,
  используя основой функционал компиляции и линковки, которые предлагает базовый класс.*/

class LightingTechnique : public Technique
{
public:
    LightingTechnique();
    virtual bool Init();

    void SetWVP(const Matrix4f* WVP);
    void SetTextureUnit(unsigned int TextureUnit);
    void SetDirectionalLight(const DirectionLight& Light);

private:
    GLuint m_WVPLocation;
    GLuint m_samplerLocation;
    GLuint m_dirLightColorLocation;
    GLuint m_dirLightAmbientIntensityLocation;
};

#endif // LIGHTINGTECHNIQUE_H