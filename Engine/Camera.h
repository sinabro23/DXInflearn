#pragma once
#include "Component.h"

enum class PROJECTION_TYPE
{
	PERSPECTIVE, // 원근 투영
	ORTHOGRAPHIC, // 직교 투영
};

class Camera : public Component
{
public:
	Camera();
	virtual ~Camera();

	virtual void FinalUpdate() override;
	void Render();

private:
	PROJECTION_TYPE _type = PROJECTION_TYPE::PERSPECTIVE;

	float _near = 1.f;
	float _far = 1000.f;
	float _fov = XM_PI / 4.f; // 45도
	float _scale = 1.f; // 직교 투영에서 사용할것

	Matrix _matView = {};
	Matrix _matProjection = {};

public:
	// TEMP
	// 트랜스폼에 넘겨줄 데이터를 임시로 스태틱으로 만듦
	static Matrix S_MatView;
	static Matrix S_MatProjection;
};

